/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Communication/UDPPRintfMain.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "..\..\common\MSCppHeapAllocDebug.h"
#include <algorithm>
#include "UDPPrint.h"

#include "Security.h"
#include "..\Interface\Macros.h"
#include "..\Interface\Main.h"
#include "..\Interface\Options.h"
#include "..\Interface\Trace.h"

#include <IEEE1588Time.h>
#include <ReadWriteUtilities.h>
#include <ToPSyncControlDriverMessages.h>

#include <wx/msgdlg.h>
#include <wx/regex.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/tokenzr.h>

#include <errno.h>
#include <Shlobj.h>
#include <Shlwapi.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace Semtech;

#define MAX_WORD_LENGTH 80
#define LOG_MARKER "LOG"

#define PTP_GENERAL_PORT 320
#define TARGET_PRINT_REQUEST_PORT 323  // on target
#define MULTICAST_PRINT_SEND_PORT 323  // on PC

#define PTP_MULTICAST_ADDRESS "224.0.1.129"
#define SEMTECH_MGT_MESSAGE_VERSION 0xF0
#define UNACKNOWLEDGED_COMMAND 15
#define MESSAGE_TYPE UNACKNOWLEDGED_COMMAND
#define UDP_DESTINATION 0
#define POLL_PERIOD 10
#define TIMEOUT_PERIOD (5 * POLL_PERIOD)
#define MAX_FILENAME_LENGTH 50

// Files namespace
bool Files::saved = false;
wxString Files::encrFileName;
wxString Files::decrFileName;
wxString Files::openFileName;
HANDLE Files::decrFile = INVALID_HANDLE_VALUE;
HANDLE Files::encrFile = INVALID_HANDLE_VALUE;
bool Files::openedEncrypted;

//#define soft "3"+$ProjectName

//data shared by threads
UDP::Port port;
IP::Address targetAddress;
float printPeriod = 1.0f;
bool delayMeasurementSlave = false;
bool printingAllColumns = false;
unsigned long systemsDebugged = 0;

static SYSTEMTIME timePrecise;
static time_t     timeRough;
static unsigned long    timeInitial;
static wxMutex    fileMutex;
static std::vector<wxString> cm55adrresses;

ttThread*  requestThread = NULL;
bool continueReadingFromFile = false;
bool isWaiting = false;
ttThread* fileReader = NULL;
bool encrWritten;
bool decrWritten;
bool decrStopped;

const double minBelievableDelay = 0;
const double maxBelievableDelay = 0.25;
const sint32 slaveOffsetLimitNs = 30;
const uint32 nsResolution = 8;

wxString publicFieldsTemp[] = {
	"Time",
	"Phase",
	"Port",
	"CM state",
	"MS pkt delay",
	"MS noise",
	"MS filter",
	"MS unlocked filter",
	"SM pkt delay",
	"SM noise",
	"SM filter",
	"SM unlocked filter",
	"Locked",
	"LD mean gradient",
	"LD int phase",
	"FreqT",
	"FreqC",
	"FreqF",
	"Holdover valid",
	"FreqH",
	"Suppress",
	"Stable phase lag",
	"Stable freq offset",
	"Ticks to VM timeout",
	"Missing dly rq",
	"Ver "
};


wxString CM55KeyData[NumbersOfCM55KeyDatat]={
	"GenrealMask"	,
	"SyncFlag"		,"WorkState"	,"Runstate"		,"PhaseValue",
	"DACValue"		,"Factor"		,"HoldCnt"		,"Runhour",
	"factor4days"	,"H_24Hphase"	,"MDAC"			,"Aging",
	"Number"		,"LockAging"	,"adjustfactor"	,"DACAverHour",
	"DACAver30s"	,"dptel"		,"LockSec00-Sec*55"
#if	(_DPTraceProduct==DataOfCMTestSys)	
	,"CMtestprj_AddrOffeset",
	"CMtestprj_SecOffeset"
#endif
};

std::vector<wxString> publicFields(publicFieldsTemp, publicFieldsTemp + sizeof(publicFieldsTemp)/sizeof(wxString));
std::vector<int> publicFieldOffsets;

void OutputError(const wxString &error)
{
	if (runningGui)
	{
		ToPTraceFrame::GetInstance()->SetError(error);
	}
	else
	{
		std::cerr << "Error: " << error << std::endl;
	}
}

unsigned int RequestPrintFromTarget(ttThread* thread)
{
	if (requestThread==NULL || GetCurrentThreadId()!=requestThread->GetId()) return -1;

	DebugPrintUnacknowledgedMsg msg;
        memset(&msg, 0, sizeof(msg));
	uint32 printPeriodMS = uint32(printPeriod * 1000);
	bool printTitle = true;

	if (printPeriodMS == 0)
		printPeriodMS = 1;

	while(requestThread!=NULL && requestThread->KeepRunning())
	{
		uint8 data[MAX_PRINTF_MESSAGE_SIZE];
		uint8* ptr = data;

		// Create message 
		InitialiseTopSyncMessageHeader(&msg.header,
                                   TOPSYNC_CONTROL_MESSAGE_SET_ID,
                                   systemsDebugged==0 ? DEBUG_PRINT_UNACKNOWLEDGED_MSG_LENGTH : DEBUG_PRINT_UNACKNOWLEDGED_MSG_LENGTH+4,
                                   DEBUG_PRINT_UNACKNOWLEDGED_MSG,
                                   0,
                                   0,
                                   TRUE,
                                   TOPSYNC_CNFG_SUCCESS,
                                   0);
        
		msg.printTopLine  = static_cast<Bool>(printTitle);
        msg.timeoutPeriod = TIMEOUT_PERIOD;
        msg.printPeriodMs = printPeriodMS;
		msg.printMask = systemsDebugged;
		
		WriteDebugPrintUnacknowledgedMsg(&ptr, &msg);
		if (systemsDebugged!=0)
		{
			WriteInteger(&ptr,msg.printMask,4);
		}

		port.Send(targetAddress,data,ptr-data);
		Sleep(POLL_PERIOD * 1000);

		printTitle = false;
	}

	return 0;
}

bool PrintEncrypted(uint8* buffer, uint16 size)
{
	if (size<9)
	{ // If it's 8 bytes long then it's just a linefeed character. Ie nothing
		return false; // There's nothing to write, so this failed
	}

	if(Files::encrFile!=INVALID_HANDLE_VALUE)
	{
        //always write fixed length buffer size to make it easier to read in again
		DWORD written;
		WriteFile(Files::encrFile, (const char*)buffer, size, &written, NULL);
	}

	return true; // Success
}

bool PrintDecrypted(uint8* buffer, uint16 size, bool firstLine, bool& debugLine, bool live)
{
	double timeFull = 0.0;
	if (live)
	{ // Live feed from ToPSync - estimate time of record with time of arrival/processing
		time(&timeRough);
		GetLocalTime(&timePrecise);
		timeFull = (double)timeRough + ((double)(timePrecise.wMilliseconds)/1000.0);
		if (timeInitial==0.0) timeInitial = timeFull;
	}
	else
	{ // Decrypting from a file, which has no timestamps. Use the interval as a timebase
		timeFull = (double)timeRough + ((double)(timePrecise.wMilliseconds)/1000.0);
	}

	wxMutexLocker fileLocker(fileMutex);

	if (size>3 && strstr((char*)buffer, "DBG")==(char*)buffer)
	{ // Line begins with 'DBG' - a debug line. Print it?

		debugLine = true;

		if (!printingAllColumns)
		{ // Do not print this line if the user isn't authorised
			return false;
		}
		// Otherwise it will be printed

	}
	else
	{ // A normal line

		debugLine = false;

		if (firstLine)
		{ // Determine device type & obtain headings
			unsigned long dummyUint;
			signed long dummyInt;
			double dummyFloat;

			int numFieldsParsed = sscanf(
				(const char*)buffer, "%u \t%u \t%u \t%u \t%u \t%u \t%u \t%u \t%e \t%d \t%d \t%u \t%u \t%u \t%u \t%d \t%u \t%u \t%u \t%u",
				&dummyUint, &dummyUint, &dummyUint, &dummyUint, &dummyUint, &dummyUint, &dummyUint, &dummyUint, &dummyFloat, &dummyInt, &dummyInt,
				&dummyUint, &dummyUint, &dummyUint,  &dummyUint, &dummyInt, &dummyUint,&dummyUint, &dummyUint, &dummyUint);
			if (numFieldsParsed>=8)
			{ // It's some flavour of Delay Measurement
				parameters_mutex.Lock();

				delayMeasurementSlave = true;
				wxString headings = "Local Time\tMS Time\tSM Time\tMS Delay\tSM Delay";
				ttParameter newEntry;
				newEntry.columnOffset = 0; newEntry.name = "MS Time"; newEntry.detailsIndex = 0;
				parameters.push_back(newEntry);
				newEntry.columnOffset = 1; newEntry.name = "SM Time"; newEntry.detailsIndex = 1;
				parameters.push_back(newEntry);
				newEntry.columnOffset = 2; newEntry.name = "MS Delay"; newEntry.detailsIndex = 2;
				parameters.push_back(newEntry);
				newEntry.columnOffset = 3; newEntry.name = "SM Delay"; newEntry.detailsIndex = 3;
				parameters.push_back(newEntry);
				if (numFieldsParsed>=11)
				{ // Time correction is present
					headings << "\tMS Corr Delay\tSM Corr Delay\tMS Corr Field\tSM Corr Field\tPhase Error\tGM Clock Class\tTime Source\tGM Clock Accuracy\
                            \tGM Clock Variance\tPriority1\tPriority2\tLocal Steps Removed\tCurrent UTC Offset\tFlag\tPTP Leapsecond 61\tPTP Leapsecond 59\tPTP UTC Reasonable\
                            \tPTP Timescale\tTime traceable\tFrequency traceable\tPTP Alternate master\tPTP Two Step\tPTP Unicast";
					newEntry.columnOffset = 4; newEntry.name = "MS Corr Delay"; newEntry.detailsIndex = 4;
					parameters.push_back(newEntry);
					newEntry.columnOffset = 5; newEntry.name = "SM Corr Delay"; newEntry.detailsIndex = 5;
					parameters.push_back(newEntry);
					newEntry.columnOffset = 6; newEntry.name = "MS Corr Field"; newEntry.detailsIndex = 6;
					parameters.push_back(newEntry);
					newEntry.columnOffset = 7; newEntry.name = "SM Corr Field"; newEntry.detailsIndex = 7;
					parameters.push_back(newEntry);
					newEntry.columnOffset = 8; newEntry.name = "Phase Error"; newEntry.detailsIndex = 8;
					parameters.push_back(newEntry);
					
				}
				headings << "\n";
				if (Files::decrFile!=INVALID_HANDLE_VALUE)
				{
					DWORD written;
					WriteFile(Files::decrFile, (const char*)headings.c_str(), headings.Length(), &written, NULL);
				}
				if (verbose)
				{
					std::cout << headings.c_str();
				}
				parametersValidated = true; // No need to interpret the first lot - they will be valid numerical values
				// Repopulate complete list of columns with NULL pointers to start with
				parameterListeners.clear();
				parameterListeners.resize(parameters.size(), NULL);
				firstLine = false; // The first line from ToPSync will actually be the second line in the output

				parameters_mutex.Unlock();

				if (runningGui && live)
				{
					ToPTraceFrame::GetInstance()->PopulateParameters();
				}
			}
			else
			{
				// Determined that it's not a delay measurement slave. So if we're printing all columns, we don't need the encrypted .dat file
				if (printingAllColumns)
				{
					CloseHandleSafely(Files::encrFile)
					DeleteFile(Files::encrFileName);
					Files::encrFileName.Clear();
				}

				parameters_mutex.Lock();
				ParseTitleLine(buffer, size);
				parameters_mutex.Unlock();
			}

			if (wxString(buffer).IsEmpty()) return false; // Nothing to print, so failed
		}

		if (!firstLine) // Explicit second IF instead of an ELSE because the flag may have changed in the previous block
		{ // Obtain values
			static int erroCount=0;
			if( (buffer[0]+ buffer[1]+ buffer[2])>=170 )//innoraml两字母+一数字>=A+A+1=179;normal两数字+<=9+9+.=57+46+57=160
			{
				erroCount=erroCount+1;
				if(erroCount<=20)
				{
					return TRUE;//这个地方肯要改一下，分的更细些，表明原因，按道理应该返回False的,add by wjh

				}//连续超过20次，说明本身数据就有问题，所以让它No Treaceable Data
			}
			else
			{
				erroCount=0;
				if (delayMeasurementSlave)
				{ // Calculate and print the columns
					ReformatDmOutput(buffer);
				}
				else
				{ // Read the columns
					ReformatOutput(buffer);
					if (!parametersValidated)
					{
						ValidateParameters(buffer,0);
						if (runningGui && live)
						{
							ToPTraceFrame::GetInstance()->PopulateParameters();
						}
					}
				}

				if (wxString(buffer).IsEmpty()) return false; // Nothing to print, so failed

				SendDataToTraces((const char*)buffer,timeFull,false);
			}
		}
	} // endif normal line

	wxString output;
	if (firstLine)
	{
		output << "Local Time\t";
	}
	else
	{
		output << wxString::Format("%u.%03hu\t", (unsigned long)timeRough, (unsigned short)(timePrecise.wMilliseconds));
	}
	output << buffer;
	
	if (Files::decrFile!=INVALID_HANDLE_VALUE)
	{
		DWORD written;
		WriteFile(Files::decrFile, (const char*)(output.c_str()), output.Length(), &written, NULL);
	}
	verbose = true;
	if (verbose)
	{
		std::cout << output.c_str() << std::endl;
	}

	if (!live && !firstLine)
	{ // Decrypting from a file, which has no timestamps. Use the interval as a timebase
		// Increase time for next iteration, only if it got this far (i.e. only if the line was printed)
		double nextTime = timeFull + printPeriod;
		timeRough = int(nextTime);
		timePrecise.wMilliseconds = (nextTime - timeRough) * 1000.0;
	}

	return true; // Successful
}

static bool CreateDirectories(const wxString &path)
{
	char* tempPath = NULL;
	tempPath = _fullpath(NULL,path,0);
	wxString fullPath = wxString(tempPath);
	delete tempPath;

	// Check it exists
	DWORD dirAttributes = GetFileAttributes(fullPath);
	if (dirAttributes!=INVALID_FILE_ATTRIBUTES)
	{ // It already exists. Ensure it's a directory
		if ((dirAttributes & FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY)
		{ // It is a directory, so everything's fine
			return true;
		}
		else
		{ // It's not a directory, so this will fail
			return false;
		}
	}
	else
	{ // Create directories recursively as necessary
		if (SHCreateDirectory(NULL,fullPath)==ERROR_SUCCESS)
		{ // Directories created successfully
			return true;
		}
		else
		{ // Couldn't create directory
			return false;
		}
	}
}

int GUIUDPprint(const wxString &input_address, const wxString &input_period, const wxString &input_file, bool* StartedFlag, const bool &input_printAll, bool startedAutomatically, const unsigned long &systems)
{
	IP::Address localAddress;
	memset(&localAddress,0,sizeof(localAddress));
	bool localAddressSet = false;
	uint8 interfaceNumber = IP::unknownInterface;
	bool firstLine = true;

	/// IP ADDRESS

	if (input_address.empty())
	{
		OutputError("Unable to read DPSync address");
		return -60;
	}
	if (!IP::ReadAddress(input_address.c_str(),targetAddress))
	{
		OutputError("Unable to parse Target address");				//无法解析目标地址
		return -70;
	}
	IP::SetPortNumber(targetAddress,TARGET_PRINT_REQUEST_PORT);		//IP和端口号323

	/// PERIOD

	if (sscanf(input_period.c_str(),"%f",&printPeriod)!=1)			//
	{
		OutputError("Unable to read print period");
		return -110;
	}

	/// SYSTEMS

	systemsDebugged = systems;

	/// FILES

	wxString baseFileName = wxEmptyString;
	if (!input_file.empty())		//非空时
	{
		if (input_file.Length()>4)
		{
			wxString tail = input_file.SubString(input_file.Length()-4, input_file.Length()-1);
			if (tail.IsSameAs(".txt",false) || tail.IsSameAs(".dat",false))
			{
				baseFileName = input_file.SubString(0, input_file.Length()-5);
			}
		}
		if (baseFileName.empty()) baseFileName = input_file;
	}
	else if (!verbose)
	{ // Make up a filename (if we need a file at all)
		SYSTEMTIME datetime;
		GetLocalTime(&datetime);
		baseFileName << "ToPTrace__" << input_address;
		baseFileName << wxString::Format(
			"__%04u-%02u-%02u_%02u-%02u-%02u",
			datetime.wYear,
			datetime.wMonth,
			datetime.wDay,
			datetime.wHour,
			datetime.wMinute,
			datetime.wSecond
		);
		if (runningGui)
		{ // GUI runs without specifying a filename or directory. The directory will be the local apps directory (Semtech\ToPTrace is automatically appended)
			baseFileName = wxStandardPaths::Get().GetUserLocalDataDir() + "\\" + baseFileName;
			ToPTraceFrame::SetFilename(baseFileName+".txt");
		}
	}

	if (!baseFileName.empty())
	{

		DWORD creationError = ERROR_SUCCESS;
		bool isRelative = (PathIsRelative(baseFileName)==TRUE);
		baseFileName.Replace("/","\\"); // Ensure correct path convention is applied，确保转化成正确的路径

		// Create output directory (relative to current working directory)
		if (CreateDirectories(baseFileName.BeforeLast('\\')))
		{ // If directory could be created (or already existed) go ahead and try to put the file there

			// Prepare filenames
			Files::decrFileName = baseFileName + ".txt";
			Files::encrFileName = baseFileName + ".dat";

			// Ensure filenames are okay
			if (GetFileAttributes(Files::decrFileName)!=INVALID_FILE_ATTRIBUTES || GetFileAttributes(Files::encrFileName)!=INVALID_FILE_ATTRIBUTES)
			{ // Filename already used - append a numerical suffix and try again
				unsigned long suffix = 1;
				while (suffix!=0)
				{	
					Files::decrFileName = baseFileName + wxString::Format(" (%lu).txt",suffix);
					Files::encrFileName = baseFileName + wxString::Format(" (%lu).dat",suffix);
					if (GetFileAttributes(Files::decrFileName)==INVALID_FILE_ATTRIBUTES && GetFileAttributes(Files::encrFileName)==INVALID_FILE_ATTRIBUTES) break;
					++suffix;
				}
			}

			Files::decrFile = CreateFile(Files::decrFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			if (Files::decrFile==INVALID_HANDLE_VALUE) creationError = GetLastError();

		}
		else
		{ // Could not create directory, so behave as if the file couldn't be written due to insufficient privileges
			Files::decrFile = INVALID_HANDLE_VALUE;
			creationError = ERROR_ACCESS_DENIED;
		}

		if (Files::decrFile==INVALID_HANDLE_VALUE)
		{ // File or directory couldn't be created
			if (creationError==ERROR_ACCESS_DENIED)
			{ // Can't open due to insufficient privileges

				/* Under certain circumstances we should silently switch to the user's directory (My Documents\ToPTrace). This will be when either:
				   a) run automatically, as it might be trying to write to the Network Manager directory; or,
				   b) the program's run from its actual location and the desired path is below this.
				   Either of those will result in failure on Win7 because Program Files is admin-only. The user needn't have to worry about that.
				   Otherwise they're deliberately writing somewhere to which they have no access, so they should be informed. */

				bool outputWithinProgramDir = false;
				wxString outputAbsolute;
				char tempDir[MAX_PATH];
				_getcwd(tempDir,MAX_PATH);
				wxString workingDir(tempDir);
				workingDir << "\\";
				wxString programDir = wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\') + "\\";
				{
					char* tempPath = NULL;
					tempPath = _fullpath(NULL,baseFileName,0);
					outputAbsolute = tempPath;
					delete tempPath;
				}
				if (outputAbsolute.StartsWith(programDir)) outputWithinProgramDir = true;

				if ((workingDir!=programDir || !outputWithinProgramDir) && !startedAutomatically)
				{ // User specified a directory to which they had insufficient privileges. Give them the option to try elsewhere
					if (runningGui)
					{
						wxMessageDialog warningBox(
							ToPTraceFrame::GetInstance(),
							"You do not have sufficient privileges to write to the directory\n"+outputAbsolute.BeforeLast('\\')+"\nWould you like to save the file to your Documents folder instead?",
							"Insufficient Privileges",
							wxYES_NO|wxICON_WARNING
						);
						if (warningBox.ShowModal()!=wxID_YES)
						{
							OutputError("Insufficient privileges to access directory");
							return -50;
						}
					}
					else
					{
						OutputError("Insufficient privileges to access directory\n"+outputAbsolute.BeforeLast('\\'));
						return -50;
					}
				}

				// Change working directory
				{
					wxString toptraceDir = wxStandardPaths::Get().GetDocumentsDir();
					toptraceDir << "\\ToPTrace";

					// Create ToPTrace user directory
					if (!CreateDirectories(toptraceDir))
					{
						OutputError("Could not create output directory");
						return -50;
					}

					_chdir(toptraceDir);
				}

				if (workingDir==programDir && outputWithinProgramDir)
				{ // If run from the program's directory (and not set to write outside that area), maintain relative to the ToPTrace user directory
					baseFileName  = outputAbsolute.Right(outputAbsolute.Length()-programDir.Length());
					if (runningGui) ToPTraceFrame::SetFilename(baseFileName+".txt");
					if (!CreateDirectories(baseFileName.BeforeLast('\\')))
					{
						OutputError("Could not create output directory");
						return -50;
					}
				}
				else
				{ // Otherwise just use the filename, storing it directly in the ToPTrace user directory
					baseFileName = baseFileName.AfterLast('\\');
					if (runningGui) ToPTraceFrame::SetFilename(baseFileName+".txt");
				}

				// Prepare filenames
				Files::decrFileName = baseFileName + ".txt";
				Files::encrFileName = baseFileName + ".dat";

				// Ensure filenames are okay
				if (GetFileAttributes(Files::decrFileName)!=INVALID_FILE_ATTRIBUTES || GetFileAttributes(Files::encrFileName)!=INVALID_FILE_ATTRIBUTES)
				{ // Filename already used - append a numerical suffix and try again
					unsigned long suffix = 1;
					while (suffix!=0)
					{
						Files::decrFileName = baseFileName + wxString::Format(" (%lu).txt",suffix);
						Files::encrFileName = baseFileName + wxString::Format(" (%lu).dat",suffix);
						if (GetFileAttributes(Files::decrFileName)==INVALID_FILE_ATTRIBUTES && GetFileAttributes(Files::encrFileName)==INVALID_FILE_ATTRIBUTES) break;
						++suffix;
					}
				}

				// Try again
				Files::decrFile = CreateFile(Files::decrFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
				if (Files::decrFile==INVALID_HANDLE_VALUE)
				{ // Still can't write
					OutputError("Unable to open file");
					return -50;
				}

			}
			else
			{ // Can't open for some other reason
				OutputError("Unable to open file");
				return -50;
			}
		}
		Files::encrFile = CreateFile(Files::encrFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Files::encrFile==INVALID_HANDLE_VALUE)
		{
			OutputError("Unable to open file");
			CloseHandleSafely(Files::decrFile)
			return -50;
		}

	}

	Files::saved = false;

	/// OTHER PREPARATIONS

	// Decide if we're printing all columns decoded (includes a second check for the Semtech file)；；决定是否将所有的栏目译码
	printingAllColumns = (input_printAll && IsSemtech());

	// Attempt to get encryption key, otherwise use default.；；//encryption：加密
	uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS];
	if(GetEncryptionKey(encryptionKey) == true)
	{
		SetTEAEncryptionKey(encryptionKey);						//加密代码
	}

	// Reset globals
	delayMeasurementSlave = false;
	timeInitial = 0.0;
	parametersValidated = false;
	parameters.clear();
	publicFieldOffsets.clear();
	encrWritten = false;
	decrWritten = false;
	decrStopped = false;

	/// RUN

	if (!port.Open(0,interfaceNumber))
	{
		OutputError("Unable to open port");
		return -70;
	}
	else
	{ // Set timeout periods
		int value = 1000; // Send timeout = 1s
		setsockopt(port.GetSocket(),SOL_SOCKET,SO_SNDTIMEO,(char*)&value,sizeof(value));
		value = ( 1000 * (int)ceil(printPeriod) ) + 5000; // Receive timeout = period + 5s
		setsockopt(port.GetSocket(),SOL_SOCKET,SO_RCVTIMEO,(char*)&value,sizeof(value));
	}

	// Declare message receipt entities
	IP::Address source;
	uint8 receivedBytes[SENTENCE_BUFFER_SIZE];

	// Send a message to terminate any existing request
	{
		DebugPrintUnacknowledgedMsg msg;
		memset(&msg, 0, sizeof(msg));
		uint32 printPeriodMS = uint32(printPeriod * 1000);
		uint8 data[MAX_PRINTF_MESSAGE_SIZE];
		uint8* ptr = data;

		/* Create message */
		InitialiseTopSyncMessageHeader(&msg.header,
                                   TOPSYNC_CONTROL_MESSAGE_SET_ID,
                                   DEBUG_PRINT_UNACKNOWLEDGED_MSG_LENGTH,
                                   DEBUG_PRINT_UNACKNOWLEDGED_MSG,
                                   0,
                                   0,
                                   TRUE,
                                   TOPSYNC_CNFG_SUCCESS,
                                   0);
        
		msg.printTopLine  = FALSE;
        msg.timeoutPeriod = 1;
        msg.printPeriodMs = printPeriodMS;
		msg.printMask = 0;
		
		WriteDebugPrintUnacknowledgedMsg(&ptr, &msg);

		port.Send(targetAddress,data,ptr-data);
		
		if (!runningGui)
		{
			std::cout << "Waiting for DPSync...";
		}

		// Clear input buffer of any messages from the old request. This will loop until the previous request has timed out
		while (port.Receive(source, receivedBytes, MAX_PRINTF_MESSAGE_SIZE)>0)
		{
		}

		if (!runningGui)
		{
			std::cout << " Done.\n\n";
		}
	}

	if (!runningGui && !baseFileName.empty())
	{
		char* tempPath = NULL;
		tempPath = _fullpath(NULL,Files::decrFileName,0);
		std::cout << "Saving to \""+wxString(tempPath)+"\"\n\n";
		delete tempPath;
	}

	// Start request thread
	#ifdef __WXDEBUG__
		requestThread = new ttThread(threadReceiving,RequestPrintFromTarget,&requestThread);
	#else
		requestThread = new ttThread(RequestPrintFromTarget,&requestThread);
	#endif
	requestThread->Run();

	// Continuously retrieve messages
	while (*StartedFlag)
	{
		int numBytesReceived = port.Receive(source, receivedBytes, MAX_PRINTF_MESSAGE_SIZE);
		if (numBytesReceived > 0 && numBytesReceived <=MAX_PRINTF_MESSAGE_SIZE)
		{
			StopWaiting();

			if (Files::encrFile!=INVALID_HANDLE_VALUE)
			{
				if (PrintEncrypted(receivedBytes, numBytesReceived))
				{ // Something was written to the encrypted file (or it's irrelevant)
					encrWritten = true;
				}
				else
				{ // There was nothing to write to encrypted (or decrypted) file - terminate the process
					// Close encrypted file
					CloseHandleSafely(Files::encrFile)
					if (!encrWritten)
					{ // Nothing was ever written to the file, so it can be deleted
						DeleteFile(Files::encrFileName);
						Files::encrFileName.Clear();
					}
					else
					{

					}
				}
			}

			if (!decrStopped)
			{
				bool debugLine = false;

				DecryptBurst(receivedBytes, numBytesReceived);

				if (PrintDecrypted(receivedBytes, numBytesReceived, firstLine, debugLine, true))
				{ // Something was written to the decrypted file
					decrWritten = true;
				}
				else if (!debugLine)
				{ // There was nothing to write to decrypted file - close it. However, debug lines may not end the decrypted stream even if they're not printed
					decrStopped = true; // Note that we're no longer writing or printing decrypted data
					fileMutex.Lock();
					if (Files::decrFile!=INVALID_HANDLE_VALUE)
					{
						// Close decrypted file
						CloseHandleSafely(Files::decrFile)
						if (!decrWritten)
						{ // Nothing was ever written to the file, so it can be deleted
							DeleteFile(Files::decrFileName);
							Files::decrFileName.Clear();
						}
					}
					fileMutex.Unlock();
					if (decrWritten)
					{ // Something was printed in the past, at least
						if (!runningGui) std::cout << "DPSync stopped returning printable data.";
					}
					else
					{ // Absolutely nothing was printed
						if (!runningGui) std::cout << "DPSync returned no printable data.";
						// Declare parameters confirmed so that the GUI, if it exists, will state there's nothing traceable
						parametersValidated = true;
					}
					if (verbose)
					{ // We're printing to screen, and having to unencrypted data means the printing will stop. Explain this
						if (Files::encrFile==INVALID_HANDLE_VALUE)
						{ // We're only printing to screen, which means this process serves no further purpose - terminate it
							break;
						}
						else
						{
							std::cout << " Nothing further will be printed.";
						}
					}
				}
			}

			fileMutex.Lock();
			if (!verbose && Files::encrFile==INVALID_HANDLE_VALUE && Files::decrFile==INVALID_HANDLE_VALUE)
			{ // Both files have been closed, so terminate the process
				fileMutex.Unlock();
				break;
			}
			fileMutex.Unlock();

			firstLine = false;
		}
		else
		{ // Print error if Receive came back with nothing (unless it was terminated deliberately)
			if (*StartedFlag)
			{
				StartWaiting("DPSync lost. Waiting for response...");
			}
			else
			{
				break;
			}
		}
	}

	/// CLEAN UP

	if (requestThread!=NULL)
	{
		requestThread->DisassociateMainPointer(&requestThread);
		requestThread->Terminate();
		requestThread = NULL;
	}

	CloseHandleSafely(Files::decrFile)
	CloseHandleSafely(Files::encrFile)

	// Delete unused files if they haven't already been
	if (!decrWritten && !Files::decrFileName.IsEmpty())
	{
		DeleteFile(Files::decrFileName);
		Files::decrFileName.Clear();
	}
	if (!encrWritten && !Files::encrFileName.IsEmpty())
	{
		DeleteFile(Files::encrFileName);
		Files::encrFileName.Clear();
	}
	return 0;
}

int GetParameterDetails(const wxString &name)
{
	for (int i=0; i<KNOWN_FIELDS; ++i)
	{
		if (name.IsSameAs(parameterDetails[i].nameRaw,false)) return i;
	}

	return -1;
}

int GetParameterDetailsFriendly(const wxString &name)
{
	for (int i=0; i<KNOWN_FIELDS; ++i)
	{
		if (name.IsSameAs(parameterDetails[i].nameFriendly, false)) return i;
	}

	return -1;
}

void ParseTitleLine(uint8* buffer, uint16 size)
{
	wxString line(buffer);
	line.Trim();
	wxStringTokenizer fields(line,"\t\n",wxTOKEN_STRTOK);
	wxString field;
	wxString tempString;
	int i = -1;

	wxString newLine = wxEmptyString;
	int detailsIndex;

	if (printingAllColumns)
	{ // List all columns

		while (fields.HasMoreTokens())
		{
			++i;
			field = fields.GetNextToken();
		
			if (field.EndsWith('#',&tempString))
			{
				field = tempString;
			}
			else if (field.StartsWith('#',&tempString))
			{
				field = tempString;
			}

			// Get details
			detailsIndex = GetParameterDetails(field);
			// Append to the new title line
			if (!newLine.empty()) newLine << "\t";
			newLine << (detailsIndex!=-1 ? parameterDetails[detailsIndex].nameFriendly : field);
			// Save for the tracing routines
			ttParameter newEntry = {i, field, detailsIndex};
			parameters.push_back(newEntry);

		}

	}
	else
	{ // If not printing everything, identify public columns

		bool found = false;

		while (fields.HasMoreTokens())
		{
			++i;
			found = false;
			field = fields.GetNextToken();
		
			if (field.EndsWith('#',&tempString))
			{ // Must include

				field = tempString;
				found = true;

			}
			else
			{ // Search through list of public fields

				for (std::vector<wxString>::iterator publicField=publicFields.begin(); publicField!=publicFields.end(); ++publicField)
				{
					// Use strncmp so we only match on the first few character (equal to the length of the known field
					// Allows the 'Version Rxxx' field to match on just 'Ver'
					if (strncmp(field.Lower().c_str(), publicField->Lower().c_str(), publicField->Length())==0)
					{
						found = true;
						break;
					}
				}

			}

			if (found)
			{ // Want this field
				// Note we want values in this column
				publicFieldOffsets.push_back(i);
				// Get details
				detailsIndex = GetParameterDetails(field);
				// Append to the new title line
				if (!newLine.empty()) newLine << "\t";
				newLine << (detailsIndex!=-1 ? parameterDetails[detailsIndex].nameFriendly : field);
				// Save for the tracing routines
				ttParameter newEntry = {publicFieldOffsets.size()-1, field, detailsIndex};
				parameters.push_back(newEntry);
			}

		}

	}

	// Copy new string into original buffer
	if (!newLine.empty()) newLine << "\n";
	memcpy(buffer, newLine.c_str(), wxMin(newLine.Length(),SENTENCE_BUFFER_SIZE));
	buffer[newLine.Length()] = '\0';

	// Repopulate complete list of columns with NULL pointers to start with
	parameterListeners.clear();
	parameterListeners.resize(parameters.size(), NULL);

}

void ParseTitleLineOpened(uint8* buffer)
{
	wxString line(buffer);
	line.Trim();
	wxStringTokenizer fields(line,",\n",wxTOKEN_STRTOK);	//分隔符是\t\n,表明是有\t,\n或者\t\n都会被分割
	wxString field[NumbersOfCM55KeyDatat]={
		"GenrealMask",
		"SyncFlag","WorkState","Runstate","PhaseValue","DACValue","Factor","HoldCnt","Runhour","factor4days","H_24Hphase",
		"MDAC","Aging","Number","SumRealDAC","Rad-X","RadY","RadZ","DACAver30s","dptel","LockSec00-Sec*55"
#if (_DPTraceProduct==DataOfCMTestSys)		
		,"CMtestprj_AddrOffeset",
		"CMtestprj_SecOffeset"
#endif
		};
	wxString tempString;
	int i = -1;

	wxString newLine = wxEmptyString;
	int detailsIndex;
#if 0
	while (fields.HasMoreTokens())		//生成表头，并插入到容器parameters中
	{
		++i;
		field = fields.GetNextToken();
		
		// Get details
		detailsIndex = GetParameterDetailsFriendly(field);//
		// Save for the tracing routines
		ttParameter newEntry = {i, field, detailsIndex};
		parameters.push_back(newEntry);

	}
#endif
	for(i=0;i<=18;i++)
	{
		ttParameter newEntry = {i, field[i], -1};
		parameters.push_back(newEntry);
	}
	// Repopulate complete list of columns with NULL pointers to start with
	parameterListeners.clear();
	parameterListeners.resize(parameters.size(), NULL);
}

void ReformatOutput(uint8* buffer)
{
	if (!printingAllColumns)
	{ // If not printing everything, must select public columns
		wxString line(buffer);
		line.Trim();
		wxStringTokenizer fields(line,"\t\n",wxTOKEN_STRTOK);
		wxString field;
		wxString newLine = wxEmptyString;
		int i = -1;

		while (fields.HasMoreTokens())
		{

			++i;
			field = fields.GetNextToken();

			for (std::vector<int>::iterator publicFieldOffset=publicFieldOffsets.begin(); publicFieldOffset!=publicFieldOffsets.end(); ++publicFieldOffset)
			{
				if (i==(*publicFieldOffset))
				{ // It's in a column we want
					if (!newLine.empty()) newLine << "\t";
					newLine << field;
					break;
				}
			}

		}

		// Copy new string into original buffer
		if (!newLine.empty()) newLine << "\n";
		memcpy(buffer, newLine.c_str(), wxMin(newLine.Length(),SENTENCE_BUFFER_SIZE));
		buffer[newLine.Length()] = '\0';
	}
}

void ReformatDmOutput(uint8* buffer)
{
	IEEE1588Time masterSendTime,slaveReceiveTime,slaveSendTime,masterReceiveTime;
	double phase,delaySM,delayMS;
	sint32 timeCorrectionNsMS,timeCorrectionNsSM;
	uint16 clockClass,timeSource,accuracy;
	uint8 priority1,priority2;
	uint16 variance,stepRemoved,flag,readFlag;
	sint16 utcOffset;
	memzero(&masterSendTime);
	memzero(&slaveReceiveTime);
	memzero(&slaveSendTime);
	memzero(&masterReceiveTime);
	int itemsRead = sscanf((char*)buffer,"%u \t%u \t%u \t%u \t%u \t%u \t%u \t%u \t%e \t%d \t%d \t%u \t%u \t%u \t%u \t%d \t%u \t%u \t%u \t%u",
		&masterSendTime.count.seconds,    &masterSendTime.count.nanoseconds,
		&slaveReceiveTime.count.seconds,  &slaveReceiveTime.count.nanoseconds,
		&slaveSendTime.count.seconds,     &slaveSendTime.count.nanoseconds,
		&masterReceiveTime.count.seconds, &masterReceiveTime.count.nanoseconds,
		&phase,
		&timeCorrectionNsMS,              &timeCorrectionNsSM,
		&variance,&priority1,&priority2,&stepRemoved,&utcOffset,&flag,&timeSource,&accuracy,&clockClass
	);

	if (itemsRead>=8)
	{ // Got at least the basics
		IEEE1588Time ieeeDelayMS = Subtract1588Time(&slaveReceiveTime, &masterSendTime);
		IEEE1588Time ieeeDelaySM = Subtract1588Time(&masterReceiveTime, &slaveSendTime);

		readFlag = flag;
		if (itemsRead>=11)
		{ // Got the time correction info too
			IEEE1588Time ieeeDelayCorMS = AddNsToIEEE1588Time(&ieeeDelayMS, -timeCorrectionNsMS);
			IEEE1588Time ieeeDelayCorSM = AddNsToIEEE1588Time(&ieeeDelaySM, -timeCorrectionNsSM);

			delayMS = (double)ieeeDelayCorMS.count.seconds+((double)ieeeDelayCorMS.count.nanoseconds / NANO_SECONDS_PER_SECOND);
			delaySM = (double)ieeeDelayCorSM.count.seconds+((double)ieeeDelayCorSM.count.nanoseconds / NANO_SECONDS_PER_SECOND);
			
			sprintf((char*)buffer,"%lu.%09lu\t%lu.%09lu\t%.8e\t%.8e\t%.8e\t%.8e\t%.8e\t%.8e\t%.8e\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%d\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\n",
				masterSendTime.count.seconds, masterSendTime.count.nanoseconds,
				slaveSendTime.count.seconds,  slaveSendTime.count.nanoseconds,

				(double)ieeeDelayMS.count.seconds +	((double)ieeeDelayMS.count.nanoseconds / NANO_SECONDS_PER_SECOND),
				(double)ieeeDelaySM.count.seconds +	((double)ieeeDelaySM.count.nanoseconds / NANO_SECONDS_PER_SECOND),

				(double)ieeeDelayCorMS.count.seconds +	((double)ieeeDelayCorMS.count.nanoseconds / NANO_SECONDS_PER_SECOND),
				(double)ieeeDelayCorSM.count.seconds +	((double)ieeeDelayCorSM.count.nanoseconds / NANO_SECONDS_PER_SECOND),

				(double)timeCorrectionNsMS / NANO_SECONDS_PER_SECOND,
				(double)timeCorrectionNsSM / NANO_SECONDS_PER_SECOND,
				(delaySM - delayMS)/2.0,
				clockClass,timeSource,accuracy,variance,
				priority1,priority2,stepRemoved,utcOffset,flag,
				((uint8)(readFlag>>8) & 0x1),
				((uint8)(readFlag>>9) & 0x1),
				((uint8)(readFlag>>10) & 0x1),
				((uint8)(readFlag>>11) & 0x1),
				((uint8)(readFlag>>12) & 0x1),
				((uint8)(readFlag>>13) & 0x1),
				((uint8)(readFlag) & 0x1),
				((uint8)(readFlag >>1) & 0x1),
				((uint8)(readFlag >>2) & 0x1)
			);
		}
		else
		{ // Just print the basics
			sprintf((char*)buffer,"%lu.%09lu\t%lu.%09lu\t%.8e\t%.8e\n",
				masterSendTime.count.seconds, masterSendTime.count.nanoseconds,
				slaveSendTime.count.seconds,  slaveSendTime.count.nanoseconds,

				(double)ieeeDelayMS.count.seconds +	((double)ieeeDelayMS.count.nanoseconds / NANO_SECONDS_PER_SECOND),
				(double)ieeeDelaySM.count.seconds +	((double)ieeeDelaySM.count.nanoseconds / NANO_SECONDS_PER_SECOND)
			);
		}
	}
}

wxString ValidateParameters(uint8* buffer,uint8 returndelimssnoffset)
{
	wxString input(buffer);
	wxStringTokenizer fields(input,",\t\n",wxTOKEN_STRTOK);	//第二个参数为分割的意思，用以分割的符号
	wxString field;
	double fieldValue;
	wxString tokenvalue[19];
	parameters_mutex.Lock();

	std::vector<ttParameter>::iterator parameter = parameters.begin();
	while (parameter!=parameters.end())
	{
		if (fields.HasMoreTokens())
		{ // Interpret field
			field = fields.GetNextToken();
			tokenvalue[parameter->columnOffset]=field;
			if (field.ToCDouble(&fieldValue))	//没关系，locksec也不需要显示
			{ // Valid numerical value, so leave it in the list
				++parameter;
			}
			else
			{ // Can't be interpreted as a number, so can't be used
				parameter = parameters.erase(parameter);
			}
		}
		else
		{ // Column contains no data, so can't be a valid parameter
			parameter = parameters.erase(parameter);
		}
	}
	parametersValidated = true;

	parameters_mutex.Unlock();
	return tokenvalue[returndelimssnoffset];
}


void splitCM55KeyData(/*const char**/const wxString buffer,wxString *tokenvalue)
{
	wxString input(buffer);
	wxStringTokenizer fields(input,",\n",wxTOKEN_STRTOK);	//第二个参数为分割的意思，用以分割的符号
	wxString field;
	uint8 i =0;

	while (fields.HasMoreTokens())		
	{
		field = fields.GetNextToken();
		tokenvalue[i]=field;
		++i;
	}
}

bool ValidateCM55KeyData(/*const char**/const wxString buffer,wxString *tokenvalue,uint8 returndelimssnoffset=0,wxString cm55address="")
{
	wxString input(buffer);
	wxStringTokenizer fields(input,",\n",wxTOKEN_STRTOK);	//第二个参数为分割的意思，用以分割的符号
	wxString field;
	uint8 i =0;

#if (_DPTraceProduct==DataOfCMTestSys)
	if(input.BeforeLast(',').AfterLast(',')!=cm55address){ return false;}
	//if(fields.GetLastDelimiter()==input.c_str())	{}

	while (fields.HasMoreTokens())		
	{
		field = fields.GetNextToken();
		tokenvalue[i]=field;

// 		if(i==returndelimssnoffset)				//运行到位号的判断位置
// 		{
// 			if(tokenvalue[i]==cm55address){/*break;*/}	//是所需找的位号数据
// 			else{return false;}
// 		}

		++i;
	}
#else
	while (fields.HasMoreTokens())		
	{
		field = fields.GetNextToken();
		tokenvalue[i]=field;

		if(i==returndelimssnoffset)				//运行到位号的判断位置
		{
			if(tokenvalue[i]==cm55address){}	//是所需找的位号数据
			else{return false;}
		}

		++i;
	}
#endif

	if(i<returndelimssnoffset)	return false;

	return true;
}

bool ISvalueHasChanged(double value)
{
	static double lastvalue=0.1;
	if(lastvalue==value)
	{
		return false;
	}else
	{
		lastvalue=value;
		return true;
	}
}

void SendDataTocm55Traces(wxString* buffer, const unsigned long &loggedTime, const bool &fromFile, const std::vector<ttDerivedTraceHost*>* const extraListeners)
{
	long x = /*(double)*/(loggedTime-/*timeInitial*/0);
	if(x<0)	return;
// 	wxString input(buffer);
// 	wxStringTokenizer fields(buffer,",\n",wxTOKEN_STRTOK);
// 	wxString field;
 	double fieldValue;

	traces_mutex.Lock();
	parameters_mutex.Lock();
	if (fromFile)					//取数据出来
	{ // Write straight to storage, if it's waiting for it
		size_t j = 0;
		for (std::vector<ttTraceWindow*>::iterator i=parameterListeners.begin(); i!=parameterListeners.end() && (j<NumbersOfCM55KeyDatat); ++i, ++j)
		{
			//field = fields.GetNextToken();
			if (buffer[j].ToCDouble(&fieldValue))
			{ // Valid value
				if ((*i)!=NULL && (*i)->WaitingForData())
				{ // Send to associated trace
					(*i)->WriteToStore(x, fieldValue);
				}
				if (extraListeners!=NULL)
				{ // Write to derived trace hosts as well
					for (size_t k=0; k<extraListeners->size(); ++k)
					{
						if (extraListeners->at(k)->GetColumnOffset()==j)
						{ // Listener is interested in this specific column
							extraListeners->at(k)->ReceiveData(x, fieldValue);
						}
					}
				}
			}
		}
	}
	else
	{ // Write to buffer
// 		for (std::vector<ttTraceWindow*>::iterator i=parameterListeners.begin(); i!=parameterListeners.end() && fields.HasMoreTokens(); ++i)
// 		{
// 			field = fields.GetNextToken();
// 			if ((*i)!=NULL && field.ToCDouble(&fieldValue))
// 			{
// 				(*i)->WriteToBuffer(x, fieldValue);
// 			}
// 		}
	}
	parameters_mutex.Unlock();
	traces_mutex.Unlock();
}

void SendDataToTraces(const char* buffer, const unsigned long &loggedTime, const bool &fromFile, const std::vector<ttDerivedTraceHost*>* const extraListeners)
{
	long x = /*(double)*/(loggedTime-timeInitial);
	if(x<0)	return;
	wxString input(buffer);
	wxStringTokenizer fields(input,",\n",wxTOKEN_STRTOK);
	wxString field;
	double fieldValue;

	traces_mutex.Lock();
	parameters_mutex.Lock();
	if (fromFile)					//取数据出来
	{ // Write straight to storage, if it's waiting for it
		size_t j = 0;
		for (std::vector<ttTraceWindow*>::iterator i=parameterListeners.begin(); i!=parameterListeners.end() && fields.HasMoreTokens(); ++i, ++j)
		{
			field = fields.GetNextToken();
			if (field.ToCDouble(&fieldValue))
			{ // Valid value
				if ((*i)!=NULL && (*i)->WaitingForData())
				{ // Send to associated trace
					(*i)->WriteToStore(x, fieldValue);
				}
				if (extraListeners!=NULL)
				{ // Write to derived trace hosts as well
					for (size_t k=0; k<extraListeners->size(); ++k)
					{
						if (extraListeners->at(k)->GetColumnOffset()==j)
						{ // Listener is interested in this specific column
							extraListeners->at(k)->ReceiveData(x, fieldValue);
						}
					}
				}
			}
		}
	}
	else
	{ // Write to buffer
		for (std::vector<ttTraceWindow*>::iterator i=parameterListeners.begin(); i!=parameterListeners.end() && fields.HasMoreTokens(); ++i)
		{
			field = fields.GetNextToken();
			if ((*i)!=NULL && field.ToCDouble(&fieldValue))
			{
				(*i)->WriteToBuffer(x, fieldValue);
			}
		}
	}
	parameters_mutex.Unlock();
	traces_mutex.Unlock();
}

#if 0
/******
     * 读出文件的最后n行
     *
     * @param file 文件
     * @param num  第几行
     * @return
******/
static List<String> readLastNLine(File file, int num) 
{
    if (num == 0) 
	{
        return null;
    }
    //判断该文件是否存在，可读
    if (!file.exists() || file.isDirectory() || !file.canRead()) 
	{
        return null;
    }
    List<String> result = new ArrayList<>();
    //行数
    int count = 0;
    //很多中读取模式，选择只读模式
    RandomAccessFile read = null;
    try {
        read = new RandomAccessFile(file, "r");
        //读取文件长度
        long length = read.length();
        //判断长度
        if (length == 0L) {
            return null;
        } else {
            //因为是倒数，所以从最大值开始读起
            long next = length - 1;
            //当下一个大于0，则代表文章有内容
            while (next > 0) {
                next--;
                //开始读取
                read.seek(next);
                //如果读取到\n代表是读取到一行
                if (read.readByte() == '\n') {
                    //使用readLine获取当前行
                    String line = read.readLine();
                    //保存结果
                    result.add(line);
                    //行数统计，如果到达了指定的行数，就跳出循环
                    count++;
                    if (count == num) {
                        break;
                    }
                }
            }
            //next为0，代表长度为1
            if (next == 0) {
                read.seek(0);
                result.add(read.readLine());
            }
        }
 
    } catch (IOException e) {
        e.printStackTrace();
    } finally {
        //关闭文件
        if (read != null) {
            try {
                read.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    return result;
}
 
 
//  public static void main(String[] args) {
//         File file = new File("test.txt");
//         List<String> result1 = readLastNLine(file, 0);
//         System.out.println("===================");
//         if (null != result1 && result1.size() > 0) {
//             for (int i = result1.size() - 1; i >= 0; i--) {
//                 System.out.println(result1.get(i));
//             }
//         }
//     }
#endif

float zerolimit(float fdata,float zerodata,float holdaging)
{
	if(fabs(fdata)>zerodata )
	{
		return fdata;
	}else
	{
		if(fabs(holdaging)>= 0.000001)
		{
			return fdata;
		}else
		{
			return 0;
		}
	}
}

unsigned int SaveFileBySelected()
{
	// Note derived hosts which want data
	std::vector<ttDerivedTraceHost*> extraListeners;
	derivedListeners_mutex.Lock();
	for (size_t i=0; i<derivedListeners.size(); ++i)
	{
		if (derivedListeners[i]->WaitingForData())
		{
			extraListeners.push_back(derivedListeners[i]);
		}
	}
	derivedListeners_mutex.Unlock();

	/// SWITCHING TO READING MODE

	fileMutex.Lock();

	// Prepare temporary file
	wxString tempPath;
	wxString tempName;
// 	wchar_t tempName[MAX_PATH];
// 	GetTempPath(MAX_PATH, tempPath);
// // 	GetTempFileName(tempPath, wxString("ToPTrace"), 0, tempName);
// 	CloseHandleSafely(Files::decrFile) // Main file's handle will be used for the temporary file
// 		Files::decrFile = CreateFile(tempName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Prepare main file

	std::fstream decrFileStream((const char*)Files::decrFileName.c_str(), std::ios_base::in);

	tempPath=Files::decrFileName.BeforeLast('\\')+'\\';
	tempName=Files::decrFileName.AfterLast('\\');
	fileMutex.Unlock();

	/// READING FILE
	std::string line;
	wxString wxLine;
	wxStringTokenizer fields;
	unsigned long loggedTime;
	wxString linetokenvalue[NumbersOfCM55KeyDatat];
	wxString savefilename[100];
	uint8	 savefilenameflag[100]={0};
	uint8 savefilename_number=0;
	uint32	 cmtimesecs=0;
	uint16   mod_10min_cmtimesecs=0;		//对cmtimesecs取余600
	uint16   last_mod_10min_cmtimesecs=0;	//上次对cmtimesecs取余600的值
	FILE * fp[100];

	SYSTEMTIME sys; 														
	GetLocalTime( &sys );
#if (_DPTraceProduct==DataOfCMTestSys)
	wxString selectcm55address=cm55adrresses.at(ToPTraceFrame::GetInstance()->GetCM55address()->GetSelection());

	for (std::vector<wxString>::iterator it=cm55adrresses.begin(); it!=cm55adrresses.end(); ++it)	
	{
		savefilename_number=atoi((*it).After('-'));
		if(savefilename_number>=90){savefilename_number=90;}
		savefilename[savefilename_number]=tempPath+(*it)+wxString::Format("HWUT10minInterval_%4d-%02d-%02d__%02d-%02d-%02d",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond)+".txt";
		fp[savefilename_number]=fopen(savefilename[savefilename_number],"a+t");
		if(fp[savefilename_number]==NULL){wxMessageBox("files open error!", "error");savefilenameflag[savefilename_number]=0;}
		else{savefilenameflag[savefilename_number]=1;}
	}

	while ( std::getline(decrFileStream,line))	//读数据
	{
		wxLine = line;
		if(wxLine.size()<165)	continue;			//去除意外的乱码
		
		//得到位号
		selectcm55address=wxLine.BeforeLast(',').AfterLast(',').After('-');	//提取出的当前地址
		savefilename_number=atoi(selectcm55address);
 		if(savefilename_number>=90){savefilename_number=90;}

		//得到产品上电时间
		selectcm55address=wxLine.BeforeLast('*').AfterLast(',').Before('-');
		cmtimesecs=atoi(selectcm55address);

		wxLine=wxLine+"\n";

		mod_10min_cmtimesecs=cmtimesecs%600;

		//每隔10min存储一次数据
		if(last_mod_10min_cmtimesecs>=mod_10min_cmtimesecs && savefilenameflag[ savefilename_number])
		{fprintf(fp[savefilename_number],wxLine.c_str());}
		else{
			//wxMessageBox(wxString::Format("error in-%d",savefilename_number), "ok1");	//捕获到0
			//continue;
		}
		last_mod_10min_cmtimesecs=mod_10min_cmtimesecs;
	}

	for (std::vector<wxString>::iterator it=cm55adrresses.begin(); it!=cm55adrresses.end(); ++it)	
	{
		savefilename_number=atoi((*it).After('-'));
 		if(savefilename_number>=90){savefilename_number=90;}
// 		savefilename[savefilename_number]=tempPath+(*it)+wxString::Format("HWUT_%4d-%02d-%02d__%02d-%02d-%02d",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond)+".txt";
// 		fp[savefilename_number]=fopen(savefilename[savefilename_number],"a+t");
		fclose(fp[savefilename_number]);
	}
	fileMutex.Unlock();
	wxMessageBox("data files save 10min-interval ok.", "ok");
	return 1;
#else
	savefilename[0]=tempPath+tempName.BeforeFirst('.')+wxString::Format("_HoldReslutData.txt")/*+".txt"*/;
	fp[0]=fopen(savefilename[0],"a+t");
	if(fp[0]==NULL)	{wxMessageBox("files open error!", "error");savefilenameflag[0]=0;}
	else{savefilenameflag[0]=1;}
	
	fprintf(fp[0],wxString::Format("H24\tH24(us)\taging\tfactor\t位号\n"));

	decrFileStream.seekg(0, std::ios::end);
	std::ios::pos_type ss = decrFileStream.tellg();
	long nFilesize = (long)ss;
	if(nFilesize>10000)
	{
		decrFileStream.seekg(-10000,std::ios::end);	//读最后20000数据
	}else
	{
		decrFileStream.seekg(0,std::ios::beg);
	}

	while ( std::getline(decrFileStream,line))	
	{
		wxLine = line;
		wxLine=line.erase(0,4);
		if(wxLine.size()<105)	continue;			//去除意外的乱码
		wxLine=wxLine.AfterFirst(',')/*.AfterFirst(',')*//*.BeforeLast(',')*/;

		fields.SetString(wxLine,",\t",wxTOKEN_STRTOK);
		splitCM55KeyData(wxLine,linetokenvalue);		//分隔数据
// 		savefilename_number=atoi(linetokenvalue[CM55AddressOffset]);
		//根据时间判断是指标1还是指标2测试
		linetokenvalue[LockSec00_SecOffeset].BeforeFirst('-').ToCULong(&cmtimesecs);
		if(cmtimesecs>40*3600)	//超过40h的测试指标2测试
		{
			//指标2,aging<0.2=0
			fprintf(fp[0],linetokenvalue[PhaseValueOffset]+
				wxString::Format("\t%.2f\t%.2f\t", atoi(linetokenvalue[PhaseValueOffset])/160.0 , zerolimit(atof(linetokenvalue[DACAver30sOffset])/100.0,0.2,atof(linetokenvalue[AgingOffset])) )+
				linetokenvalue[factor4daysOffset]+"\t"+linetokenvalue[CM55AddressOffset]+"\n");

		}else
		{
			//指标1,aging<0.4=0
			fprintf(fp[0],linetokenvalue[H_24HphaseOffset]+
				wxString::Format("\t%.2f\t%.2f\t",atoi(linetokenvalue[H_24HphaseOffset])/160.0,zerolimit(atof(linetokenvalue[DACAver30sOffset])/100.0,0.4,atof(linetokenvalue[AgingOffset])) )+
				linetokenvalue[FactorOffset]+"\t"+linetokenvalue[CM55AddressOffset]+"\n");
		}

	}
	fclose(fp[savefilename_number]);
	wxMessageBox(tempName+" data is ok", "ok");
	return 1;
#endif
}

unsigned int ReadFromFile(ttThread* thread, void* extra)
{
	thread->EnterWorkingZone();

	bool* continueReading = (bool*)extra;

	// Note derived hosts which want data
	std::vector<ttDerivedTraceHost*> extraListeners;
	derivedListeners_mutex.Lock();
	for (size_t i=0; i<derivedListeners.size(); ++i)
	{
		if (derivedListeners[i]->WaitingForData())
		{
			extraListeners.push_back(derivedListeners[i]);
		}
	}
	derivedListeners_mutex.Unlock();

	/// SWITCHING TO READING MODE

		fileMutex.Lock();

		// Prepare temporary file
		wchar_t tempPath[MAX_PATH];
		wchar_t tempName[MAX_PATH];
		GetTempPath(MAX_PATH, tempPath);
		GetTempFileName(tempPath, wxString("ToPTrace"), 0, tempName);
		CloseHandleSafely(Files::decrFile) // Main file's handle will be used for the temporary file
		Files::decrFile = CreateFile(tempName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		// Prepare main file
		std::fstream decrFileStream((const char*)Files::decrFileName.c_str(), std::ios_base::in);

		fileMutex.Unlock();

	/// READING FILE
		std::string line;
		wxString wxLine;
		wxStringTokenizer fields;
		unsigned long loggedTime;
		wxString selectcm55address=cm55adrresses.at(ToPTraceFrame::GetInstance()->GetCM55address()->GetSelection());
		wxString linetokenvalue[NumbersOfCM55KeyDatat];
//		uint8* afterStartchar;
		while (*continueReading && std::getline(decrFileStream,line))	//读数据
		{
			if(line.size()<100)	continue;		//滤除掉cm65打印出来的信息
			wxLine=line.erase(0,4);
			wxLine=wxLine.AfterFirst(',')/*.AfterFirst(',')*//*.BeforeLast(',')*/;

#if (_DPTraceProduct==DataOfCMTestSys)			
			if(!ValidateCM55KeyData(/*(const char *)*/wxLine/*.c_str()*/,linetokenvalue,CMtestprj_AddrOffeset/*CM55AddressOffset*/,selectcm55address))	continue;//比较 同时提取数据
#else		
			fields.SetString(wxLine,",\t",wxTOKEN_STRTOK);
			if(!ValidateCM55KeyData(/*(const char *)*/wxLine/*.c_str()*/,linetokenvalue,CM55AddressOffset,selectcm55address))	continue;//比较 同时提取数据
#endif

			if(!linetokenvalue[LockSec00_SecOffeset].BeforeFirst('-').ToCULong(&loggedTime)) continue;		//提取时间
			SendDataTocm55Traces(linetokenvalue, loggedTime, true, &extraListeners);
		}

	/// SWITCHING TO WRITING MODE
		fileMutex.Lock();

		// Prepare temporary file
		CloseHandleSafely(Files::decrFile)
		HANDLE tempFile = CreateFile(tempName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
		// Prepare main file
		decrFileStream.close();
		Files::decrFile = CreateFile(Files::decrFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		// Transfering from temporary to main
		DWORD bytesRead,bytesWritten,position;
		BYTE transferBuffer[4096];
		position = SetFilePointer(Files::decrFile, 0, NULL, FILE_END);
		while (ReadFile(tempFile, transferBuffer, sizeof(transferBuffer), &bytesRead, NULL) && bytesRead > 0)
		{
			WriteFile(Files::decrFile, transferBuffer, bytesRead, &bytesWritten, NULL);
		}
		// Deleting temporary
		CloseHandleSafely(tempFile)
		DeleteFile(tempName);

		fileMutex.Unlock();

		// Don't bother updating graphs if the process was cancelled
		if (!*continueReading)
		{
			thread->LeaveWorkingZone();
			return 0;
		}

		traces_mutex.Lock();
		for (std::vector<ttTraceWindow*>::iterator i=traces.begin(); i!=traces.end(); ++i)
		{
			(*i)->DataReady();
		}
		traces_mutex.Unlock();
		// Finalise derived trace hosts as well
		for (size_t i=0; i<extraListeners.size(); ++i)
		{
			extraListeners[i]->DoneReadingFile();
		}

		ToPTraceFrame::GetInstance()->DoneReadingFile();
		
	thread->LeaveWorkingZone();
	return 0;
}

void StartWaiting(const wxString &message)
{
	if (runningGui)
	{

		ToPTraceFrame::StartWaiting(message);

	}
	else
	{

		static unsigned int cyclerPos = 0;
		if (!isWaiting)
		{ // Print the message
			std::cout << message << '\n';
		}
		else
		{ // Erase last character to replace it with next in the cycle
			std::cout << '\b';
		}
		switch (cyclerPos)
		{
			case 1:
				std::cout << '/';
				break;
			case 2:
				std::cout << '-';
				break;
			case 3:
				std::cout << '\\';
				break;
			default:
				std::cout << '|';
				break;
		}
		++cyclerPos;
		if (cyclerPos>3) cyclerPos = 0;
		isWaiting = true;

	}
}

void StopWaiting()
{
	if (runningGui)
	{

		ToPTraceFrame::StopWaiting();

	}
	else
	{

		if (!isWaiting) return;
		std::cout << '\b' << "Reacquired.\n";
		isWaiting = false;

	}
}

bool OpenExistingFile(const wxString& filename)
{
	Files::openedEncrypted = false;
	std::fstream fileStream((const char*)filename.c_str(), std::ios_base::in|std::ios_base::binary);

	// See if file is encrypted - attempt to read a couple of blocks of data
	if(0)
	{
		char buffer[17];
		buffer[16] = '\0';
		wxRegEx encodedCharacters("[^A-Za-z0-9 \\t#]", wxRE_ADVANCED);//^表示非字母、数字或者\t的存在；^表示取否定
		fileStream.read(buffer, 16);
		if (encodedCharacters.Matches(wxString(buffer)))	//的确存在，则是加密文件
		{ // Unreadable characters were found, so it's likely encrypted
			Files::openedEncrypted = true;
			// Perform a decryption of just this first chunk to see if that will work
			DecryptBurst((uint8*)buffer, 16);
			if (encodedCharacters.Matches(wxString(buffer)))
			{ // Still unreadable, so it's either an invalid file or the encryption key is wrong
				return false;
			}
		}
	}

	// Record filenames
	Files::openFileName = filename;
	Files::encrFileName.Clear();
	Files::decrFileName.Clear(); // Until it's created and populated with the decrypted output (if reading from encrypted file)
	Files::saved = !Files::openedEncrypted; // The file is considered not saved if it's a encrypted file, because a new decrypted file is generated that can optionally be saved

	return true;
}

unsigned int ReadOpenedEncrypted(const wxString &input_period, const bool &input_printAll)
{
	char blockBuffer[MIN_ENCRYPTION_BLOCK_BYTES];
	char blockBufferDecrypted[MIN_ENCRYPTION_BLOCK_BYTES+1];
	blockBufferDecrypted[MIN_ENCRYPTION_BLOCK_BYTES] = '\0';
	char encrBuffer[SENTENCE_BUFFER_SIZE];
	char decrBuffer[SENTENCE_BUFFER_SIZE];
	size_t encrLength;
	bool reachingEndOfLine; // Note final part of line, where the newline and null characters are
	bool startOfLine; // Note start of the next line, for escaping nested loops
	bool firstLine = true; // First line flag, dropped after the first line is interpreted

	// Reset globals
	delayMeasurementSlave = false;
	timeInitial = 0.0;
	timeRough = 0;
	timePrecise.wMilliseconds = 0;
	parametersValidated = false;
	parameters.clear();
	publicFieldOffsets.clear();
	encrWritten = false;
	decrWritten = false;
	decrStopped = false;

	// Copy options from UI
	if (sscanf(input_period.c_str(), "%f", &printPeriod)!=1)
	{ // Default to 1s print period if not specified
		printPeriod = 1.0;
	}
	printingAllColumns = (input_printAll && IsSemtech());
	
	// Prepare the temporary decrypted file
	wchar_t tempPath[MAX_PATH];
	wchar_t tempName[MAX_PATH];
	GetTempPath(MAX_PATH, tempPath);
	GetTempFileName(tempPath, wxString("ToPTrace"), 0, tempName);
	Files::decrFileName = tempName;
	Files::decrFile = CreateFile(tempName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Read from the encrypted file, splitting the encrypted data by newlines (each block must be decrypted to find these newlines)
	std::fstream fileStream((const char*)Files::openFileName.c_str(), std::ios_base::in|std::ios_base::binary);
	// Get first block of data
	fileStream.read(blockBuffer, MIN_ENCRYPTION_BLOCK_BYTES);
	while (true)
	{
		encrLength = 0;
		reachingEndOfLine = false;
		startOfLine = false;
		while (true)
		{
			// Check for terminating characters
			memcpy(blockBufferDecrypted, blockBuffer, MIN_ENCRYPTION_BLOCK_BYTES);
			DecryptBurst((uint8*)blockBufferDecrypted, MIN_ENCRYPTION_BLOCK_BYTES);
			for (size_t i=0; i<MIN_ENCRYPTION_BLOCK_BYTES; ++i)
			{
				if (blockBufferDecrypted[i]=='\0' || blockBufferDecrypted[i]=='\n')
				{ // Newlines and nulls signify an end of line. However, we want to capture all contiguus blocks containing them, so carry on
					reachingEndOfLine = true;
					break;
				}
				else
				{
					if (reachingEndOfLine)
					{ // A non-terminating character has been discovered in a block after a block with a terminating character - this must be the start of a new line
						startOfLine = true;
						break;
					}
				}
			}
			if (startOfLine)
			{ // This block is the start of a new line, so don't add it to the buffer or request a new block
				break;
			}

			// Add to the end of the line
			memcpy(&encrBuffer[encrLength], blockBuffer, MIN_ENCRYPTION_BLOCK_BYTES);
			memcpy(&decrBuffer[encrLength], blockBufferDecrypted, MIN_ENCRYPTION_BLOCK_BYTES);
			encrLength += MIN_ENCRYPTION_BLOCK_BYTES;

			if (fileStream.eof()) break;

			// Read next block from file
			fileStream.read(blockBuffer, MIN_ENCRYPTION_BLOCK_BYTES);
		}

		bool debugLine = false;
		if (PrintDecrypted((uint8*)decrBuffer, encrLength, firstLine, debugLine, false))
		{ // Something was written to the decrypted file
			decrWritten = true;
		}
		else if (!debugLine)
		{ // There was nothing to write to decrypted file - close it and give up. However, debug lines may not end the decrypted stream even if they're not printed
			fileMutex.Lock();
			if (Files::decrFile!=INVALID_HANDLE_VALUE)
			{
				// Close decrypted file
				CloseHandleSafely(Files::decrFile)
				if (!decrWritten)
				{ // Nothing was ever written to the file, so it can be deleted
					DeleteFile(Files::decrFileName);
					Files::decrFileName.Clear();
				}
			}
			fileMutex.Unlock();
			if (!decrWritten)
			{ // Absolutely nothing was printed
				if (!runningGui) std::cout << "The file contains no printable data.";
				// Declare parameters confirmed so that the GUI, if it exists, will state there's nothing traceable
				parametersValidated = true;
				break;
			}
			if (verbose)
			{ // We're printing to screen, and having to unencrypted data means the printing will stop. Explain this
				if (Files::encrFile==INVALID_HANDLE_VALUE)
				{ // We're only printing to screen, which means this process serves no further purpose - terminate it
					break;
				}
				else
				{
					std::cout << " Nothing further will be printed.";
				}
			}
		}

		firstLine = false;

		if (fileStream.eof()) break;
	}

	CloseHandleSafely(Files::decrFile)

	ToPTraceFrame::GetInstance()->PopulateParameters();

	return 0;
}

unsigned int ReadOpenedDecrypted()
{
	uint8 lineBuffer[SENTENCE_BUFFER_SIZE];
	size_t lineLength;
	size_t linnumber=0;
	bool firstLine = true; // First line flag, dropped after the title line is interpreted
	uint8* afterLocalTime; // Pointer to string after the 'Local Time' column
	wxString validcm55address;
	// Resetting globals
	parametersValidated = false;
	parameters.clear();
	publicFieldOffsets.clear();
	encrWritten = false;
	decrWritten = false;
	decrStopped = false;

	// Read from the decryted file, determining the parameters and which ones are plottable；；plottable可画曲线的
	std::fstream fileStream((const char*)Files::openFileName.c_str(), std::ios_base::in|std::ios_base::binary);
	uint8 *lineBufferptr=lineBuffer;
	while (!fileStream.eof())
	{
		fileStream.getline((char*)lineBuffer, SENTENCE_BUFFER_SIZE-1);	//读行内容，且最多读5KB数据
		lineLength = fileStream.gcount();
		lineBuffer[lineLength++] = '\n'; // Append newline which was stripped by getline()
		linnumber++;
		// Handle line

		// Is it a debug line?
		if (lineLength>3 && strstr((char*)lineBuffer, "DBG")==(char*)lineBuffer)
		{ // Line begins with 'DBG' - a debug line. Do not use it for analysis
			continue;
		}
		if(lineLength<100 || linnumber<=50)		//从第100行后开始读，这个值修改从节目传入可设置
		{
			continue;
		}
		lineBufferptr=lineBuffer;
		while( (*lineBufferptr)==0)
		{
			lineBufferptr=lineBufferptr+2;
		}
		// Determine where the 'Local Time' column ends
//		afterLocalTime = (uint8*)strchr((char*)lineBuffer, ',') + 1;
		if (firstLine)					//可以直接不需要firstline了
		{ // Interpret the title line
			afterLocalTime = (uint8*)strchr((char*)lineBuffer+4, 0x2c/*','*/) + 1;//0x2c=','的ascall码值；strchr遇到\0就结束了！
			//afterLocalTime = (uint8*)strchr((char*)afterLocalTime, ',') + 1;
			if(*(afterLocalTime-2)=='P' && *(afterLocalTime-3)=='D' && *(afterLocalTime-4)=='P')
			{
				parameters_mutex.Lock();
				//afterLocalTime = (uint8*)strchr((char*)afterLocalTime, ',') + 1;		//再去掉1个，分隔符的数据
				ParseTitleLineOpened(afterLocalTime);
				parameters_mutex.Unlock();
				firstLine = false;
			}else
			{
				firstLine = true;
			}

		}
		else
		{ // Interpret the first data line
			afterLocalTime = (uint8*)strchr((char*)lineBuffer+4, ',') + 1;
			//afterLocalTime = (uint8*)strchr((char*)afterLocalTime, ',') + 1;		//再去掉1个，分隔符的数据


			if (!parametersValidated)
			{
				wxString(afterLocalTime).AfterLast(',').BeforeFirst('-').ToCULong(&timeInitial);		//这么说timeInitial是100个点后的值，用它做时间基准则可能有问题！！
				ValidateParameters(afterLocalTime,0);
				// 					Files::decrFileName = Files::openFileName;
				cm55adrresses.clear();
			}
			wxString stringtakenizor[NumbersOfCM55KeyDatat];
#if (_DPTraceProduct==DataOfCMTestSys)
			validcm55address=((wxString)afterLocalTime).BeforeLast(',').AfterLast(',');		//UT测试板，倒数第二列为位号
#else
			ValidateCM55KeyData(/*(const char *)*/afterLocalTime,stringtakenizor,CM55AddressOffset,CM55KeyData[NumbersOfCM55KeyDatat-1]);
			validcm55address=stringtakenizor[CM55AddressOffset];
#endif

			if(std::find(cm55adrresses.begin(),cm55adrresses.end(),validcm55address) == cm55adrresses.end())	//not find
			{
				cm55adrresses.push_back(validcm55address);
			}else
			{
				if(linnumber>=150)
				{
					std::sort(cm55adrresses.begin(),cm55adrresses.end());
					for (std::vector<wxString>::iterator it=cm55adrresses.begin(); it!=cm55adrresses.end(); ++it)	
					{
						ToPTraceFrame::GetInstance()->GetCM55address()->AppendString(*it);
					}
					ToPTraceFrame::GetInstance()->GetCM55address()->SetSelection(0);	//应该触发一个绘图函数事件
					decrWritten = true;

					//触发绘图函数事件
					if (runningGui)
					{
						ToPTraceFrame::GetInstance()->InitChecklistParameters();
						ToPTraceFrame::GetInstance()->PopulateParameters();
					}
					break;
				}
			}
		}

	}

	// Note decrypted filename so future graphs can access it to read back data
 	Files::decrFileName = Files::openFileName;

	return 0;
}