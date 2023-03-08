/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Main.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Main.h"

#include "DerivedTraceHost.h"
#include "Macros.h"
#include "Options.h"
#include "SystemSelect.h"
#include "View_ArrangeGraphs.h"
#include "Workarea.h"
#include "wxInteractiveImage.h"
#include "../resource.h"
#include "../version.h"
#include "../Communication/Security.h"
#include "../Communication/UDP.hpp"
#include "../Communication/UDPPrint.h"

#include "ToPSyncInterfaceTypes.h"

#include <wx/apptrait.h>
#include <wx/cmdline.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/tokenzr.h>
#include <wx/msw/msvcrt.h>

#include <Commctrl.h>
#include <fstream>

#define KEY_RECENT_FILE "Recent file"

wxRegKey registryBase(wxRegKey::HKCU,"Software\\Semtech\\ToPTrace"); // Used for preferences

bool runningGui = true;
bool verbose = false;

unsigned short graphArrangement_method = arrangeRatio;
unsigned short graphArrangement_columns = 2;
unsigned short graphArrangement_rows = 4;
double         graphArrangement_ratio = 2.0;

wxChar localeDecimalPoint = '.';
wxString localeJunkNumberChars = "[:space:]\n\r\t";
static bool keepLogging = false;
static bool parametersPopulated = false;
static std::vector<wxString> desiredParameters;
static bool isSemtech = false;
static bool startedAutomatically = false;

/**************
  ToPTraceApp
**************/

#ifdef TT_CONSOLE

int _tmain(int argc, _TCHAR* argv[])
{
	return wxEntry(argc,argv);
}

#endif // TT_CONSOLE

IMPLEMENT_APP(ToPTraceApp)

bool ToPTraceApp::OnInit()
{
	SetAppName(__TargetName);
	SetVendorName("Dapu");

	#ifdef _DEBUG
		wxCrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		#ifdef INCLUDE_CRT_LEAKS
		// Also check for leaks in the C runtime，，检测是否内存泄漏
			wxCrtSetDbgFlag(_CRTDBG_CHECK_CRT_DF);
		#endif
	#endif
	isSemtech = IsSemtech();		//全局变量
	m_param_address = wxEmptyString;
	m_param_file = wxEmptyString;
	m_param_period = "1";
	m_param_start = false;
	m_param_printAll = isSemtech;
	m_param_minimise = false;
	m_param_maximise = false;
	m_param_systems = 0;

	/** Locale settings **/
	wxChar buf[256];
	buf[0] = wxT('\0');
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, buf, WXSIZEOF(buf))) localeJunkNumberChars <<  buf[0];
	buf[0] = wxT('\0');
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, buf, WXSIZEOF(buf))) localeDecimalPoint = buf[0];

	runningGui = GetConsoleWindow()==NULL;
	if (!runningGui)
	{ // Ensure stderr will be used for error outputs
		wxMessageOutput* oldOutput = wxMessageOutput::Set(new wxMessageOutputStderr());
		delete oldOutput;
	}

	#ifndef TT_CONSOLE
		if (!runningGui)
		{ // Trying to run GUI version from console doesn't work well
			wxMessageOutput* msgOut = wxMessageOutput::Get();
			if (msgOut) msgOut->Output("\nThis program will run in graphical mode only. For console use, please execute DPTrace.com.");
			runningGui = true;
		}
	#endif

    if (!wxApp::OnInit()) return false;

	if (runningGui)
	{ // GUI
		
		wxInitAllImageHandlers();
		
		{ // Retrieve options
			wxRegKey regKey(registryBase,REGKEY_BASE);
			if (!regKey.Exists()) regKey.Create();

			if (regKey.HasValue(REGKEY_GA_METHOD))
			{
				long value = 2;
				regKey.QueryValue(REGKEY_GA_METHOD,&value);
				graphArrangement_method = (unsigned short)value;
			}

			if (regKey.HasValue(REGKEY_GA_COLUMNS))
			{
				long value = 2;
				regKey.QueryValue(REGKEY_GA_COLUMNS,&value);
				graphArrangement_columns = (unsigned short)value;
			}

			if (regKey.HasValue(REGKEY_GA_ROWS))
			{
				long value = 4;
				regKey.QueryValue(REGKEY_GA_ROWS,&value);
				graphArrangement_rows = (unsigned short)value;
			}

			if (regKey.HasValue(REGKEY_GA_RATIO))
			{
				wxString value = wxEmptyString;
				regKey.QueryValue(REGKEY_GA_RATIO,value);
				if (!value.IsEmpty())
				{
					double x,y;
					if (sscanf(value,"%lf:%lf",&x,&y)==2)
					{
						graphArrangement_ratio = x / y;
					}
				}
			}
		}

		ToPTraceFrame* frame = new ToPTraceFrame(
			m_param_address,
			m_param_file,
			m_param_period,
			m_param_start,
			m_param_printAll,
			m_param_systems
		);
		if (m_param_maximise)
		{
			frame->Maximize();
		}
		else if (m_param_minimise)
		{
			frame->Iconize();
		}
		frame->Show(true);

		return true; // Program will continue

	}
	else
	{ // Console

		//AllocConsole();
		keepLogging = true;

		GUIUDPprint(
			m_param_address,
			m_param_period,
			m_param_file,
			&keepLogging,
			m_param_printAll,
			true,
			m_param_systems
		);

		return false; // End of program

	}
}

void ToPTraceApp::OnInitCmdLine(wxCmdLineParser &parser)
{
	wxString versionTitle = wxString::Format("\nDPTrace %li.%li",Version::MAJOR,Version::MINOR);
	if (!wxString(Version::STATUS).IsEmpty()) versionTitle << " (" << Version::STATUS << ")";
	if (Version::DEVELOPMENT)
	{
		versionTitle << wxString::Format(" (Build: %li)",Version::BUILDS_COUNT);
	}
	else
	{
		versionTitle << " - A Logging and Plotting Utility for DPSync";
	}
	versionTitle << "\n";
	versionTitle << wxString('=',versionTitle.Length()-2);
	versionTitle << "\n";
	versionTitle << "by Dapu Wireless, Sensing & Timing\n";
	versionTitle << "\n";
	versionTitle << wxString::FromUTF8("Copyright \302\251 ") << Version::YEAR << " Dapu Corporation\n";
	int day = (int)strtol(Version::DATE,NULL,10);
	int month = (int)strtol(Version::MONTH,NULL,10);
	wxString months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	versionTitle << wxString::Format(
		"Version: %li.%li.%li%s  Built: %i %s %s\n",
		Version::MAJOR,
		Version::MINOR,
		Version::BUILD,
		Version::STATUS_SHORT,
		day,
		months[month-1].c_str(),
		Version::YEAR
	);
	versionTitle << "\n";
	versionTitle << "Web:    http://www.dptel.com\n";
	versionTitle << "E-mail: DPSync@dptel.com\n";
	parser.SetLogo(versionTitle);

	parser.AddUsageText(" ");
	parser.AddOption("d", "device",    "IP address of the target DPSync device.");
	parser.AddOption("f", "file",      "Path and name of the output file.");
	parser.AddOption("p", "period",    "Period between updates from DPSync.");
	parser.AddOption("c", "systems",   "Hexadecimal mask of DPSync systems to be retrieved.");
	if (isSemtech)
	{
		parser.AddSwitch("n", "noDapu", "Do not print any Dapu-only columns.");
	}
	parser.AddUsageText(" ");
	parser.AddSwitch("s", "start",     "Begin the logging immediately.");
	parser.AddOption("t", "plot",      "Columns to plot, in the format \"col1\";\"col2\".");
	#ifdef TT_CONSOLE
		parser.AddSwitch("v", "verbose", "Print output to this window.");
	#else
		parser.AddSwitch("max", "maximise", "Maximise the window.");
		parser.AddSwitch("min", "minimise", "Minimise the window.");
	#endif
	parser.AddSwitch("h", "help",      "Show this help message.", wxCMD_LINE_OPTION_HELP);
}

bool ToPTraceApp::OnCmdLineParsed(wxCmdLineParser &parser)
{
	wxString errors = wxEmptyString;

	if (runningGui)
	{ // GUI
		m_param_start = parser.Found("s");
		if (m_param_start && !parser.Found("d"))
		{ // Cannot run automatically without an address
			errors << "\nLogging cannot start without a device address. Please enter one and press Start.";
			m_param_start = false;
		}
		m_param_maximise = parser.Found("max");
		m_param_minimise = parser.Found("min");
		#ifdef TT_CONSOLE
			if (parser.Found("v"))
			{ // Cannot be verbose in GUI mode
				errors << "\nCannot print logs to screen if the GUI is active. Logs will only be sent to a file, if a filename is supplied.";
			}
		#endif
	}
	else
	{ // Console
		if (!parser.Found("d"))
		{
			errors << "\nError: A device address must be specified when run from the console.";
		}
		verbose = parser.Found("v");
		if (!verbose && !parser.Found("f"))
		{ // Cannot continue if there's nowhere for the logs to go
			errors << "\nError: A filename must be specified. Alternatively, specify /v to print to console directly.";
		}
	}
	
	wxString param;
	if (parser.Found("d",&param)) m_param_address = param;
	if (parser.Found("f",&param)) m_param_file = param;
	if (parser.Found("p",&param)) m_param_period = param;
	if (parser.Found("c",&param)) param.ToULong(&m_param_systems,16);
	if (isSemtech) m_param_printAll = !parser.Found("n");

	if (!errors.empty())
	{
		if (!runningGui) errors = parser.GetUsageString() + errors;
		wxMessageOutput* msgOut = wxMessageOutput::Get();
		if (msgOut) msgOut->Output(errors);
		if (!runningGui)
		{ // Can't recover from errors if it's in the console
			return false;
		}
	}

	if (parser.Found("t",&param))
	{ // Columns to plot
		wxStringTokenizer columns(param,";",wxTOKEN_STRTOK);
		wxString column;
		bool alreadyGot;
		while (columns.HasMoreTokens())
		{
			column = columns.GetNextToken();
			alreadyGot = false;
			for (std::vector<wxString>::iterator i=desiredParameters.begin(); i!=desiredParameters.end(); ++i)
			{
				if (column.IsSameAs(*i,false))
				{ // Already got this column
					alreadyGot = true;
					break;
				}
			}
			if (!alreadyGot) desiredParameters.push_back(column);
		}
	}

	return true;
}

bool ToPTraceApp::OnCmdLineError(wxCmdLineParser &parser)
{
	return wxApp::OnCmdLineError(parser);
}

bool ToPTraceApp::OnCmdLineHelp(wxCmdLineParser &parser)
{
	return wxApp::OnCmdLineHelp(parser);
}

/****************
  ToPTraceFrame
****************/
const long ToPTraceFrame::ID_CM55Address = wxNewId();
const long ToPTraceFrame::ID_SYSTEMS_BOX = wxNewId();
const long ToPTraceFrame::ID_SYSTEMS_BUTTON = wxNewId();
const long ToPTraceFrame::ID_INITIATOR = wxNewId();				//start按钮
const long ToPTraceFrame::ID_PARAMETERS_LIST = wxNewId();
const long ToPTraceFrame::ID_PARAMETERS_PLOT = wxNewId();
const long ToPTraceFrame::ID_MENU_ARRANGE = wxNewId();
const long ToPTraceFrame::ID_CHANGETITLE_START = wxNewId();
const long ToPTraceFrame::ID_CHANGETITLE_END = wxNewId();

BEGIN_EVENT_TABLE(ToPTraceFrame, wxFrame)
	EVT_MENU           ( wxID_EXIT,            ToPTraceFrame::OnQuit             )
	EVT_MENU           ( ID_MENU_ARRANGE,      ToPTraceFrame::OnMenuSelect       )
	EVT_MENU           ( wxID_ABOUT,           ToPTraceFrame::OnAbout            )
	EVT_MENU           ( wxID_SAVE,            ToPTraceFrame::OnSave             )
	EVT_MENU           ( wxID_OPEN,            ToPTraceFrame::OnOpen             )
    EVT_LISTBOX        ( ID_PARAMETERS_LIST,   ToPTraceFrame::OnChecklistSelect  )
    EVT_LISTBOX_DCLICK ( ID_PARAMETERS_LIST,   ToPTraceFrame::OnChecklistCommand )
	EVT_SIZE           (                       ToPTraceFrame::OnSize             )
    EVT_CHAR_HOOK      (                       ToPTraceFrame::OnChar             )
	EVT_CHECKBOX       ( ID_SYSTEMS_BOX,       ToPTraceFrame::OnSystemsBox       )
	EVT_BUTTON         ( ID_SYSTEMS_BUTTON,    ToPTraceFrame::OnSystemsButton    )
    EVT_BUTTON         ( ID_INITIATOR,         ToPTraceFrame::OnOpen/*OnInitiate*/         )		//start按钮执行的函数
    EVT_BUTTON         ( ID_PARAMETERS_PLOT,   ToPTraceFrame::OnPlot             )
	EVT_COMBOBOX       ( ID_CM55Address,	   ToPTraceFrame::OnPlot             )
	EVT_CLOSE          (                       ToPTraceFrame::OnClose            )
	EVT_MENU           ( ID_CHANGETITLE_START, ToPTraceFrame::OnChangeTitleStart )
	EVT_TEXT_ENTER     ( ID_CHANGETITLE_END,   ToPTraceFrame::OnChangeTitleEnd   )
END_EVENT_TABLE()

ToPTraceFrame* ToPTraceFrame::m_instance;

ToPTraceFrame::ToPTraceFrame(			//构造函数
		const wxString &address,
		const wxString &file,
		const wxString &period,
		const bool &start,
		const bool &printAll,
		const unsigned long &systems
	)
	: wxFrame(
		NULL,
		wxID_ANY,
		__TargetName,
		wxDefaultPosition,
		wxSize(600,400),
		wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU | wxMAXIMIZE_BOX | wxRESIZE_BORDER
	),
	m_thread_logging(NULL),
	m_thread_drawing(NULL),
	m_thread_destroying(NULL),
	m_traceArea(NULL),
	m_WindowCreated(false),
	m_specialTitle(wxEmptyString),
	m_titleDialog(NULL),
	m_systems(systems)
{
	m_instance = this;
	m_running_logging = false;
	m_isWaiting = false;
	SetMinSize(wxSize(600,400));

	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));

	/** Menu bar **/

	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* menu = new wxMenu();
	menu->Append(wxID_OPEN, "&Open...\tCtrl+O", "Opens an existing DPTrace file.");
	menu->Append(wxID_SAVE, "&Save as...\tCtrl+S", "Saves the current data to file.");
	menu->Enable(wxID_SAVE, false);
	menu->AppendSeparator();
	menu->Append(wxID_EXIT,"E&xit\tAlt+F4","Quits DPTrace.");
	menuBar->Append(menu,"&File");
	menu = new wxMenu();
	menu->Append(ID_MENU_ARRANGE,"&Arrange Graphs...","Specifies how graphs will be arranged in the window.");
	menuBar->Append(menu,"&View");
	menu = new wxMenu();
	menu->Append(wxID_ABOUT,"&About\tF1","Displays program information.");
	menuBar->Append(menu,"&Help");
	SetMenuBar(menuBar);

	/** Status bar **/

    CreateStatusBar();

	/** CONTENTS **/

	m_panel = new wxPanel(this,wxID_ANY);

	m_wholeArea = new wxBoxSizer(wxHORIZONTAL);
	m_formArea = new wxBoxSizer(wxVERTICAL);

	/** Form **/

	wxFlexGridSizer* fillerFlex = new wxFlexGridSizer(isSemtech ? 4 : 3,2,6,3);
	fillerFlex->Add(
		new wxStaticText(m_panel,wxID_ANY,"CM55 address:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_form_address = new wxComboBox(m_panel,ID_CM55Address,"0-00",wxDefaultPosition,wxSize(80, -1),0,NULL,wxCB_DROPDOWN|wxCB_READONLY)
	);
	fillerFlex->Add(
		new wxStaticText(m_panel,wxID_ANY,"Logging period:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	// Textbox & suffix
		wxBoxSizer* filler = new wxBoxSizer(wxHORIZONTAL);
		filler->Add(
			m_form_period = new wxTextCtrl(m_panel,wxID_ANY,period),
			wxSizerFlags(1)
		);
		m_form_period->SetMinSize(wxSize(75, -1));
		filler->AddSpacer(5);
		filler->Add(
			new wxStaticText(m_panel,wxID_ANY,"s"),
			wxSizerFlags().Border(wxTOP,3)
		);
	fillerFlex->Add(filler, wxSizerFlags().Expand().Border(wxRIGHT,-1));
	if (isSemtech)
	{
		fillerFlex->Add(
			new wxStaticText(m_panel,wxID_ANY,"Decrypt all columns:"),
			wxSizerFlags().Border(wxTOP,3)
		);
		fillerFlex->Add(
			m_form_printAll = new wxCheckBox(m_panel,wxID_ANY,wxEmptyString),
			wxSizerFlags().Border(wxTOP,3)
		);
		if (printAll) m_form_printAll->SetValue(true);
	}
	fillerFlex->Add(
		new wxStaticText(m_panel,wxID_ANY,"Choose systems:"),
		wxSizerFlags().Border(wxTOP,isSemtech ? 8 : 3)
	);
	filler = new wxBoxSizer(wxHORIZONTAL);
	filler->Add(
		m_form_systems_box = new wxCheckBox(m_panel,ID_SYSTEMS_BOX,wxEmptyString),
		wxSizerFlags().Border(wxTOP,isSemtech ? 8 : 3)
	);
	filler->AddSpacer(6);
	filler->Add(
		m_form_systems_button = new wxButton(m_panel,ID_SYSTEMS_BUTTON,"Choose..."),
		wxSizerFlags().Border(wxTOP,isSemtech ? 3 : -2)
	);
	fillerFlex->Add(filler);
	if (m_systems>0)
	{
		m_form_systems_box->SetValue(true);
	}
	else
	{
		m_form_systems_button->Enable(false);
	}
	m_formArea->Add(fillerFlex);
	m_formArea->AddSpacer(12);

	filler = new wxBoxSizer(wxHORIZONTAL);
	filler->Add(
		m_initiator = new wxButton(m_panel,ID_INITIATOR,"Open File...")
	);
	m_formArea->Add(filler, wxSizerFlags().Right());
	
	/** Waiting indicator **/

	m_formArea->Add(
		m_waiting_separator = new wxStaticLine(m_panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL),
		wxSizerFlags().Expand().Border(wxTOP|wxBOTTOM,12)
	);
	m_waiting_separator->Show(false);
	m_formArea->Add(
		m_waiting_text = new wxStaticText(m_panel,wxID_ANY,"Waiting for DPSync...")
	);
	m_waiting_text->Show(false);
	m_formArea->Add(
		m_waiting_gauge = new wxGauge(m_panel,wxID_ANY,100,wxDefaultPosition,wxSize(16,16)),
		wxSizerFlags().Expand().Border(wxTOP,3)
	);
	m_waiting_gauge->Show(false);
	m_waiting_gauge->SetIndeterminateMode();
	
	/** Trace options **/

	m_formArea->Add(
		m_parameters_separator = new wxStaticLine(m_panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL),
		wxSizerFlags().Expand().Border(wxTOP|wxBOTTOM,12)
	);
	m_parameters_separator->Show(false);
	m_formArea->Add(
		m_parameters_list = new wxCheckListBox(m_panel,ID_PARAMETERS_LIST),
		wxSizerFlags(1).Expand()
	);
	m_parameters_list->Show(false);
	m_formArea->Add(
		m_parameters_none = new wxStaticText(m_panel,wxID_ANY,"No traceable data.")
	);
	m_parameters_none->Show(false);
	m_formArea->Add(
		m_parameters_plot = new wxButton(m_panel,ID_PARAMETERS_PLOT,"Trace Selected"),
		wxSizerFlags().Right().Border(wxTOP,6).FixedMinSize()
	);
	m_parameters_plot->Show(false);

	m_wholeArea->Add(m_formArea, wxSizerFlags().Border(wxALL,10).Expand());

	m_wholeArea->Add(
		m_trace_window = new ttEmptyFrame(m_panel,"Logging has not been started."),
		wxSizerFlags(1).Expand()
	);

	m_WindowCreated = true;

	m_panel->SetSizer(m_wholeArea);
	
	m_form_address->SetFocus();
	SetDefaultItem(m_initiator);

	wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_CTRL, 'T', ID_CHANGETITLE_START);

    wxAcceleratorTable accel(1, entries);
    SetAcceleratorTable(accel);

	if (start)
	{ // Start automatically
		startedAutomatically = true;
		wxCommandEvent newEvent;
		OnInitiate(newEvent);
	}
}

ToPTraceFrame::~ToPTraceFrame()
{
	if (m_thread_logging!=NULL) m_thread_logging->DisassociateMainPointer(&m_thread_logging);
	if (m_thread_drawing!=NULL) m_thread_drawing->DisassociateMainPointer(&m_thread_drawing);
	if (m_titleDialog=NULL) delete m_titleDialog;
}

ToPTraceFrame* ToPTraceFrame::GetInstance()
{
	return m_instance;
}

void ToPTraceFrame::OnSize(wxSizeEvent &event)
{
	if (!m_WindowCreated) return;

	ArrangeTraces(false,&event.GetSize());
	event.Skip();
}

void ToPTraceFrame::OnChar(wxKeyEvent &event)
{
	if (event.GetKeyCode()==WXK_ESCAPE)
	{ // Terminate something

		wxCommandEvent newEvent;
		if (m_running_logging)
		{ // Stop logging
			OnInitiate(newEvent);
		}
	}

	else
	{
		event.Skip();
	}
}

void ToPTraceFrame::OnClose(wxCloseEvent &event)
{
	if (m_running_logging)
	{
		wxMessageDialog warningBox(
			this,
			"Data is being logged. Are you sure you want to quit?",
			"Stop Logging",
			wxYES_NO|wxICON_WARNING
		);
		// Give them the option to cancel the operation
		if (warningBox.ShowModal()!=wxID_YES) {
			event.Veto();
			return;
		}
	}

	bool performSave = !Files::saved && (!Files::decrFileName.IsEmpty() || !Files::encrFileName.IsEmpty());
	if (performSave)
	{ // Check to see if files should be saved
		wxMessageDialog warningBox(
			this,
			"The data has not been saved. Do you wish to do so?", "Save Data",
			wxYES_NO|wxCANCEL|wxICON_QUESTION
		);
		int response = warningBox.ShowModal();
		if (response==wxID_CANCEL)
		{
			event.Veto();
			return;
		}
		else if (response!=wxID_YES)
		{
			performSave = false;
		}
	}

	if (performSave)
	{ // Save the files
		// Stop any current activity
		if (m_running_logging)
		{
			ResetAfterLogging();
		}

		// Present save prompt. If this fails, cancel the closure
		if (!SaveFiles())
		{
			event.Veto();
			return;
		}
	}

	// Hide, to give the impression of an immediate response
	Show(false);

	// Terminate threads
 	m_running_logging = false;
	if (requestThread!=NULL) requestThread->Terminate();
	if (m_thread_logging!=NULL) m_thread_logging->Terminate();
	if (m_thread_drawing!=NULL) m_thread_drawing->Terminate();
	// Wait for them to end
	if (m_thread_logging!=NULL) m_thread_logging->WaitForTermination(5000);
	if (m_thread_drawing!=NULL) m_thread_drawing->WaitForTermination(5000);
	if (requestThread!=NULL) requestThread->WaitForTermination(5000);
	// Disassociate them
	m_thread_logging = NULL;
	m_thread_drawing = NULL;
	requestThread = NULL;
	ClearTraces();

	if (!performSave && !Files::saved)
	{ // Delete the temporary files, if they've not been saved
		if (!Files::decrFileName.IsEmpty())
		{ // Delete the decrypted file.
			DeleteFile(Files::decrFileName);
		}
		if (!Files::encrFileName.IsEmpty())
		{ // Delete the encrypted file
			DeleteFile(Files::encrFileName);
		}
	}

	m_instance = NULL;

	Destroy();
}

void ToPTraceFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void ToPTraceFrame::OnSystemsBox(wxCommandEvent &event)
{
	m_form_systems_button->Enable(event.IsChecked());
}

void ToPTraceFrame::OnSystemsButton(wxCommandEvent &event)
{
	ttSystemSelect* dialog = new ttSystemSelect(this,&m_systems);
	dialog->ShowModal();
	dialog->Destroy();
}

void ToPTraceFrame::OnInitiate(wxCommandEvent &event)
{
	if (!m_running_logging)
	{ // Start the logging
		
		/// HANDLE PREVIOUS RUN

		if (!Files::saved && (!Files::decrFileName.IsEmpty() || !Files::encrFileName.IsEmpty()))
		{ // Check to see if files should be saved
			wxMessageDialog warningBox(
				this,
				"The previous data has not been saved. Do you wish to do so?", "Save Data",
				wxYES_NO|wxCANCEL|wxICON_QUESTION
			);
			int response = warningBox.ShowModal();
			if (response==wxID_CANCEL)
			{ // Do not start the run
				return;
			}
			else if (response!=wxID_YES)
			{ // Delete the temporary files
				if (!Files::decrFileName.IsEmpty())
				{ // Delete the decrypted file.
					CloseHandleSafely(Files::decrFile)
					DeleteFile(Files::decrFileName);
				}
				if (!Files::encrFileName.IsEmpty())
				{ // Delete the encrypted file
					CloseHandleSafely(Files::encrFile)
					DeleteFile(Files::encrFileName);
				}
			}
			else
			{ // Present save prompt. If this fails, cancel the closure
				if (!SaveFiles())
				{
					return;
				}
			}
		}

		///	SANITISE INPUT

		// Address
		{
			Semtech::IP::Address testAddress;
			if (m_form_address->GetValue().empty() || !Semtech::IP::ReadAddress(m_form_address->GetValue().c_str(),testAddress))
			{	//adress不符合正确规范时
				wxMessageDialog warningBox(
					this,
					"The IP address entered is invalid. DPTrace needs a properly formatted IP address to continue.",
					"Bad IP Address",
					wxOK|wxICON_WARNING
				);
				warningBox.ShowModal();
				return;
			}
		}

		// Period
		{
			float testPeriod;								//默认周期为1
			if (sscanf(m_form_period->GetValue().c_str(),"%f",&testPeriod)!=1 || testPeriod<0.0)//填错为负数时，自动更新为1
			{
				m_form_period->SetValue("1");
			}
		}

		/// CONTINUE

		SetStatusText("Running");					//左下方状态显示
		m_initiator->SetLabelText("Stop");			//这是那个按钮
		//m_form_address->Enable(false);				//禁止用户输入
		m_form_address->Enable(true);
		m_form_period->Enable(false);
		GetMenuBar()->Enable(wxID_OPEN, false);
		GetMenuBar()->Enable(wxID_SAVE, false);
		if (isSemtech) m_form_printAll->Enable(false);
		m_form_systems_box->Enable(false);
		m_form_systems_button->Enable(false);		//....
		SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_GRAPHING));	//更新图标
		m_originalTitle = "*" + m_form_address->GetValue() + " - "+__TargetName;	//窗口标题* adress -DPTrace
		if (m_specialTitle.IsEmpty())
		{
			SetTitle(m_originalTitle);							//具体写入标题
		}
		else
		{
			SetTitle(m_originalTitle + " - " + m_specialTitle);
		}

		Freeze();												

		// Create back-up list of selected graphs for re-selection after their validity's been established
		wxArrayString names = m_parameters_list->GetStrings();
		for (wxArrayString::iterator i=names.begin(); i!=names.end(); ++i)
		{
			if (m_parameters_list->IsChecked(i-names.begin()))
			{
				desiredParameters.push_back(*i);		//压入
			}
		}

		parametersPopulated = false;
		parametersValidated = false;
		StartWaiting("Waiting for DPSync...");
		m_parameters_separator->Show(false);
		m_parameters_list->Clear();
		m_parameters_list->Show(false);
		m_parameters_none->Show(false);
		m_parameters_plot->Show(false);

		ClearTraces();

		Thaw();			//与freeze成对

		#ifdef __WXDEBUG__
			m_thread_logging = new ttThread(threadLogging,RunThreadLogging,&m_thread_logging);
			m_thread_drawing = new ttThread(threadDrawing,RunThreadDrawing,&m_thread_drawing);
		#else
			m_thread_logging = new ttThread(RunThreadLogging,&m_thread_logging);		//创建两个线程
			m_thread_drawing = new ttThread(RunThreadDrawing,&m_thread_drawing);
		#endif
		m_running_logging = true;
		m_thread_logging->Run();
		m_thread_drawing->Run();

	}
	else
	{ // Terminate the logging
		ResetAfterLogging();
	}
}

void ToPTraceFrame::OnChecklistSelect(wxCommandEvent &event)
{
	int erm=0;
	int selected = event.GetSelection();
	m_parameters_list->Check(selected,!m_parameters_list->IsChecked(selected));
	m_parameters_list->SetSelection(-1);
}

void ToPTraceFrame::OnChecklistCommand(wxCommandEvent &event)
{
	if (m_parameters_plot->GetLabelText()!="Cancel")
	{
		OnPlot(event);
	}
}

void ToPTraceFrame::OnPlot(wxCommandEvent &event)
{
	static	uint8 lastcm55address=-1;
	uint8	isnewaddress=0;
	if(event.GetId()==ID_CM55Address)
	{
		if(lastcm55address==m_form_address->GetSelection())
		{
			isnewaddress=0;
		}else
		{
			isnewaddress=1;		//选择了新位号
			lastcm55address=m_form_address->GetSelection();
			ClearTraces();		//这句很重要，不然绘图容易出BUG
		}
		traces.clear();
		
	}
	if (m_parameters_plot->GetLabelText()!="Cancel")
	{ // Change plotting selection
		unsigned int nextExistingIndex = 0;
		bool newTraces = false;
		bool tracesToDelete = false;
	
		traces_mutex.Lock();
		parameters_mutex.Lock();
		Freeze();

		for (std::vector<ttParameter>::iterator i=parameters.begin(); i!=parameters.end(); ++i)
		{
			if (m_parameters_list->IsChecked(i-parameters.begin()))
			{ // Checked - we want a trace
				if (parameterListeners[i->columnOffset]==NULL || isnewaddress==1)
				{ // Create it
					traces.insert(traces.begin()+nextExistingIndex, new ttTraceWindow(m_panel,i));
					parameterListeners[i->columnOffset] = traces[nextExistingIndex];
					newTraces = true;
				}
				else
				{ // We already have a trace, so nothing to do
				}
				++nextExistingIndex;
			}
			else
			{ // Not checked - we don't want a trace
				if (parameterListeners[i->columnOffset]!=NULL)
				{ // We have a trace, so get rid of it
					m_mutex_destroying.Lock();
					m_traces_destroying.push_back(parameterListeners[i->columnOffset]);
					m_mutex_destroying.Unlock();
					DisassociateTrace(traces.begin()+nextExistingIndex);
					tracesToDelete = true;
				}
				else
				{ // Don't have one, so nothing to do
				}
			}
		}

		if (tracesToDelete)
		{ // Spin off thread to destroy some traces, as this thread can't afford to hang around for their processing to end cleanly
			m_mutex_destroying.Lock();
			if (m_thread_destroying==NULL)
			{ // No existing thread destroying things, so must initiate one
				#ifdef __WXDEBUG__
					m_thread_destroying = new ttThread(threadDestroying,RunThreadDestroying);
				#else
					m_thread_destroying = new ttThread(RunThreadDestroying);
				#endif
				m_thread_destroying->Run();
			}
			m_mutex_destroying.Unlock();
		}

		if (newTraces)
		{ // Read back data from file for new traces
			continueReadingFromFile = true;
			m_parameters_plot->SetLabelText("Cancel");
			#ifdef __WXDEBUG__
				fileReader = new ttThread(threadReading,ReadFromFile,&continueReadingFromFile,&fileReader);
			#else
				fileReader = new ttThread(ReadFromFile,&continueReadingFromFile,&fileReader);
			#endif
			fileReader->Run();
		}

		ArrangeTraces(true);

		Thaw();
		parameters_mutex.Unlock();
		traces_mutex.Unlock();

	}
	else
	{ // Cancel file read
		bool tracesToDelete = false;
		continueReadingFromFile = false;
		if (fileReader!=NULL) fileReader->Terminate();
		if (fileReader!=NULL) fileReader->WaitForTermination(5000);
		fileReader = NULL;
			
		traces_mutex.Lock();
		parameters_mutex.Lock();
		Freeze();

		m_parameters_plot->SetLabelText("Trace Selected");

		// Destroy incomplete plots
		std::vector<ttTraceWindow*>::iterator trace = traces.begin();
		for (std::vector<ttParameter>::iterator i=parameters.begin(); i!=parameters.end(); ++i)
		{
			if (parameterListeners[i->columnOffset]!=NULL)
			{ // There's a trace, so see if we should delete it
				if ((*trace)->WaitingForData())
				{
					m_mutex_destroying.Lock();
					m_traces_destroying.push_back(*trace);
					m_mutex_destroying.Unlock();
					DisassociateTrace(trace);
					tracesToDelete = true;
					m_parameters_list->Check(parameters.begin()-i,false);
				}
				else
				{
					++trace;
				}
			}
		}

		if (tracesToDelete)
		{ // Spin off thread to destroy some traces, as this thread can't afford to hang around for their processing to end cleanly
			m_mutex_destroying.Lock();
			if (m_thread_destroying==NULL)
			{ // No existing thread destroying things, so must initiate one
				#ifdef __WXDEBUG__
					m_thread_destroying = new ttThread(threadDestroying,RunThreadDestroying);
				#else
					m_thread_destroying = new ttThread(RunThreadDestroying);
				#endif
				m_thread_destroying->Run();
			}
			m_mutex_destroying.Unlock();
		}

		ArrangeTraces(true);

		Thaw();
		parameters_mutex.Unlock();
		traces_mutex.Unlock();
	}
}

void ToPTraceFrame::OnAbout(wxCommandEvent &event)
{
	wxDialog* aboutBox = new wxDialog(this,wxID_ANY,"About DPTrace",wxDefaultPosition,wxDefaultSize,wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX);
	wxBoxSizer* s_outer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* s_inner = new wxBoxSizer(wxVERTICAL);

	s_inner->Add(
		new wxInteractiveImage(
			aboutBox,
			wxID_ANY,
			imageLogo,sizeof(imageLogo),wxBITMAP_TYPE_PNG,
			wxDefaultPosition,
			wxSize(323+4,93+4),
			wxBORDER_SUNKEN
		)
	);
	s_inner->AddSpacer(6);

	wxString versionTitle = wxString::Format("DPTrace %li.%li",Version::MAJOR,Version::MINOR);
	if (!wxString(Version::STATUS).IsEmpty()) versionTitle << " (" << Version::STATUS << ")";
	if (Version::DEVELOPMENT) versionTitle << wxString::Format(" (Build: %li)",Version::BUILDS_COUNT);
	wxStaticText* tempText = new wxStaticText(
		aboutBox,
		wxID_ANY,
		versionTitle
	);
	wxFont boldFont = tempText->GetFont();
	boldFont.SetWeight(wxFONTWEIGHT_BOLD);
	tempText->SetFont(boldFont);
	s_inner->Add(tempText);
	s_inner->AddSpacer(3);

	versionTitle.erase();
	versionTitle << wxString::FromUTF8("Copyright \xC2\xA9 ") << Version::YEAR << " Dapu Corporation";
	s_inner->Add(
		new wxStaticText(
			aboutBox,
			wxID_ANY,
			versionTitle
		)
	);
	s_inner->AddSpacer(6);

	int day = (int)strtol(Version::DATE,NULL,10);
	int month = (int)strtol(Version::MONTH,NULL,10);
	wxString months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	s_inner->Add(
		new wxStaticText(
			aboutBox,
			wxID_ANY,
			wxString::Format(
				"Version: %li.%li.%li%s  Built: %i %s %s",
				Version::MAJOR,
				Version::MINOR,
				Version::BUILD,
				Version::STATUS_SHORT,
				day,
				months[month-1].c_str(),
				Version::YEAR
			)
		)
	);
	s_inner->AddSpacer(6);

	wxBoxSizer* s_lower = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* fillerStatic = new wxStaticBoxSizer(wxVERTICAL,aboutBox,"Contact");
	fillerStatic->AddSpacer(3);
	wxFlexGridSizer* fillerFlex = new wxFlexGridSizer(2,2,6,3);
	fillerFlex->Add(
		new wxStaticText(aboutBox,wxID_ANY,"Web:"),
		wxSizerFlags().Border(wxLEFT,3)
	);
	fillerFlex->Add(
		new wxStaticText(aboutBox,wxID_ANY,"http://www.dptel.com"),
		wxSizerFlags().Border(wxRIGHT,1)
	);
	fillerFlex->Add(
		new wxStaticText(aboutBox,wxID_ANY,"E-mail:"),
		wxSizerFlags().Border(wxLEFT,3)
	);
	fillerFlex->Add(
		new wxStaticText(aboutBox,wxID_ANY,"DPSync@dptel.com"),
		wxSizerFlags().Border(wxRIGHT,1)
	);
	fillerStatic->Add(fillerFlex, wxSizerFlags().Expand().Border(wxLEFT|wxBOTTOM|wxRIGHT,6));
	fillerStatic->AddSpacer(1);
	s_lower->Add(fillerStatic, wxSizerFlags());
	s_lower->AddStretchSpacer(1);

	s_lower->Add(
		new wxButton(aboutBox,wxID_CANCEL,"OK"),
		wxSizerFlags().Bottom().Border(wxLEFT,12)
	);

	s_inner->Add(s_lower, wxSizerFlags().Expand());

	s_outer->Add(s_inner, wxSizerFlags().Border(wxALL,10).Expand());

	aboutBox->SetSizer(s_outer);
	s_outer->Layout();
	s_outer->Fit(aboutBox);

	CentreChildOnParent(this,aboutBox);
	aboutBox->ShowModal();
	aboutBox->Destroy();
}

void ToPTraceFrame::OnMenuSelect(wxCommandEvent &event)
{
	if (event.GetId()==ID_MENU_ARRANGE)
	{
		ArrangeGraphsDialog* dialog = new ArrangeGraphsDialog(this);
		dialog->ShowModal();
		dialog->Destroy();
	}
}

void ToPTraceFrame::OnChangeTitleStart(wxCommandEvent &event)
{
	if (m_titleDialog==NULL)
	{
		m_titleDialog = new wxDialog(this,wxID_ANY,"Change title");
		m_titleControl = new wxTextCtrl(m_titleDialog,ID_CHANGETITLE_END,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
		long extraStyle = m_titleDialog->GetExtraStyle();
		m_titleDialog->SetExtraStyle( extraStyle - wxWS_EX_BLOCK_EVENTS );
	}
	m_titleDialog->Show(true);
}

void ToPTraceFrame::OnChangeTitleEnd(wxCommandEvent &event)
{
	if (m_titleDialog!=NULL)
	{
		m_specialTitle = m_titleControl->GetValue();
		if (m_specialTitle.IsEmpty())
		{
			SetTitle(m_originalTitle);
		}
		else
		{
			SetTitle(m_originalTitle + " - " + m_specialTitle);
		}

		m_titleDialog->Show(false);
	}
}

extern unsigned int SaveFileBySelected();

void ToPTraceFrame::OnSave(wxCommandEvent& event)
{
	if (!m_running_logging)
	{
		//SaveFiles();
		SaveFileBySelected();
	}
}

void ToPTraceFrame::OnOpen(wxCommandEvent& event)
{
	if (!m_running_logging)
	{

		/// HANDLE PREVIOUS RUN

		if (!Files::saved && (!Files::decrFileName.IsEmpty() || !Files::encrFileName.IsEmpty()))
		{ // Check to see if files should be saved
			wxMessageDialog warningBox(
				this,
				"The previous data has not been saved. Do you wish to do so?", "Save Data",
				wxYES_NO|wxCANCEL|wxICON_QUESTION
			);
			int response = warningBox.ShowModal();
			if (response==wxID_CANCEL)
			{ // Do not open a file
				return;
			}
			else if (response!=wxID_YES)
			{ // Delete the temporary files
				if (!Files::decrFileName.IsEmpty())
				{ // Delete the decrypted file.
					CloseHandleSafely(Files::decrFile)
					DeleteFile(Files::decrFileName);
				}
				if (!Files::encrFileName.IsEmpty())
				{ // Delete the encrypted file
					CloseHandleSafely(Files::decrFile)
					DeleteFile(Files::encrFileName);
				}
			}
			else
			{ // Present save prompt. If this fails, cancel the opening routine
				if (!SaveFiles())
				{
					return;
				}
			}
		}

		/// SELECT FILE

		wxString directory = wxEmptyString;
		if (!m_LastFile.IsEmpty())
		{ // Use locally noted directory (in case last operation failed and they'd like to try again in the same place)
			directory = m_LastFile;
		}
		else
		{ // Get it from registry
			if (registryBase.HasValue(KEY_RECENT_FILE)) registryBase.QueryValue(KEY_RECENT_FILE, directory);
		}
		directory = directory.BeforeLast('\\')+"\\";
		wxFileDialog tempDialog(
			this,
			wxEmptyString, directory, wxEmptyString,
			"DPTrace Data Files (*.txt;*.dat)|*.txt;*.dat",
			wxFD_OPEN
		);
		if (tempDialog.ShowModal()==wxID_OK)
		{
			wxString fileName = tempDialog.GetPath();
			m_LastFile = fileName; // Store recent file now no matter what
			registryBase.SetValue(KEY_RECENT_FILE, fileName); // Store recent directory & file in registry

			if (!OpenExistingFile(fileName))
			{ // File could not be interpreted
				return;
			}

			/// CONTINUE
			
			SetStatusText("");
			//m_initiator->SetLabelText("Stop");
			m_originalTitle = (Files::saved ? "" : "*") + fileName.AfterLast('\\') + " - "+__TargetName;
			if (m_specialTitle.IsEmpty())
			{
				SetTitle(m_originalTitle);
			}
			else
			{
				SetTitle(m_originalTitle + " - " + m_specialTitle);
			}

			Freeze();

			// Create back-up list of selected graphs for re-selection after their validity's been established
			wxArrayString names = m_parameters_list->GetStrings();
			for (wxArrayString::iterator i=names.begin(); i!=names.end(); ++i)
			{
				if (m_parameters_list->IsChecked(i-names.begin()))
				{
					desiredParameters.push_back(*i);
				}
			}

			parametersPopulated = false;
			parametersValidated = false;
			StartWaiting("Loading file...");
			m_parameters_separator->Show(false);
			m_form_address->Clear();
			m_parameters_list->Clear();
			m_parameters_list->Show(false);
			m_parameters_none->Show(false);
			m_parameters_plot->Show(false);

			ClearTraces();

			Thaw();

			// Interpet the file line by line
			
			//m_parameters_plot->SetLabelText("Cancel");
			#ifdef __WXDEBUG__
				m_thread_opening = new ttThread(threadOpening, RunThreadOpening, &m_thread_opening);
			#else
				m_thread_opening = new ttThread(RunThreadOpening, &m_thread_opening);
			#endif
			m_thread_opening->Run();
		}
	}
	GetMenuBar()->Enable(wxID_SAVE, true);
}

void ToPTraceFrame::ResetAfterLogging()
{
	m_running_logging = false;
	if (m_thread_logging!=NULL)
	{
		m_thread_logging->DisassociateMainPointer(&m_thread_logging);
		m_thread_logging->Terminate();
	}
	if (m_thread_drawing!=NULL)
	{
		m_thread_drawing->DisassociateMainPointer(&m_thread_drawing);
		m_thread_drawing->Terminate();
	}
	port.Close();

	Freeze();
	
	GetMenuBar()->Enable(wxID_OPEN, true);
	if (encrWritten || decrWritten)
	{ // Something exists to save
		// Leave the title as it is
		// Enable the save function
		GetMenuBar()->Enable(wxID_SAVE, true);
		// Update status bar if it's not populated with an error message
		if (GetStatusBar()->GetStatusText()=="Running")
		{
			SetStatusText("Data not yet saved.");
		}
	}
	else
	{ // Nothing to save, and there's nothing to show
		// Reset the title
		m_originalTitle = __TargetName;
		if (m_specialTitle.IsEmpty())
		{
			SetTitle(m_originalTitle);
		}
		else
		{
			SetTitle(m_originalTitle + " - " + m_specialTitle);
		}
		// Keep the save function disabled
		// Update status bar if it's not populated with an error message
		if (GetStatusBar()->GetStatusText()=="Running")
		{
			SetStatusText("DPSync returned no data.");
		}
	}
	m_form_address->Enable(true);
	m_form_period->Enable(true);
	if (isSemtech) m_form_printAll->Enable(true);
	m_form_systems_box->Enable(true);
	m_form_systems_button->Enable(m_form_systems_box->GetValue());
	m_initiator->SetLabelText("Open File...");
	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));
	m_initiator->SetFocus();
	if (!parametersPopulated)
	{
		m_parameters_separator->Show(false);
	}
	StopWaiting(false,true);
	m_formArea->Layout();

	Thaw();

	m_thread_logging = NULL;
	m_thread_drawing = NULL;

	traces_mutex.Lock();
	for (std::vector<ttTraceWindow*>::iterator i=traces.begin(); i!=traces.end(); ++i)
	{
		(*i)->Render(true);
	}
	traces_mutex.Unlock();
}

void ToPTraceFrame::ResetAfterOpening()
{
	if (m_thread_opening!=NULL)
	{
		m_thread_opening->DisassociateMainPointer(&m_thread_opening);
		m_thread_opening->Terminate();
	}

	Freeze();
	
	GetMenuBar()->Enable(wxID_OPEN, true);
	if (decrWritten)
	{ // Something exists to save
		// Leave the title as it is
		// Enable the save function
		GetMenuBar()->Enable(wxID_SAVE, true);
		// Update status bar
		SetStatusText(Files::openedEncrypted ? "Decrypted data not yet saved." : "");
	}
	else
	{ // Nothing to save, and there's nothing to show
		// Reset the title
		m_originalTitle = __TargetName;
		if (m_specialTitle.IsEmpty())
		{
			SetTitle(m_originalTitle);
		}
		else
		{
			SetTitle(m_originalTitle + " - " + m_specialTitle);
		}
		// Keep the save function disabled
		// Update status bar
		SetStatusText("Decryption returned no data.");
	}
	m_form_address->Enable(true);
	m_form_period->Enable(true);
	if (isSemtech) m_form_printAll->Enable(true);
	m_form_systems_box->Enable(true);
	m_form_systems_button->Enable(m_form_systems_box->GetValue());
	m_initiator->SetLabelText("Open File...");
	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));
	m_initiator->SetFocus();
	if (!parametersPopulated)
	{
		m_parameters_separator->Show(false);
	}
	StopWaiting(false,true);
	m_formArea->Layout();

	Thaw();
}

unsigned int ToPTraceFrame::RunThreadLogging(ttThread* thread)		//线程1
{
	if (m_instance==NULL || m_instance->m_thread_logging==NULL || GetCurrentThreadId()!=m_instance->m_thread_logging->GetId()) return -1;

	m_instance->m_thread_logging->EnterWorkingZone();

	m_instance->DoLogging();		//记录

	if (m_instance!=NULL && m_instance->m_thread_logging!=NULL) m_instance->m_thread_logging->LeaveWorkingZone();
	return 0;
}

unsigned int ToPTraceFrame::RunThreadDrawing(ttThread* thread)
{
	if (m_instance==NULL || m_instance->m_thread_drawing==NULL || GetCurrentThreadId()!=m_instance->m_thread_drawing->GetId()) return -1;

	m_instance->m_thread_drawing->EnterWorkingZone();
	while (m_instance!=NULL && m_instance->m_thread_drawing!=NULL && m_instance->m_thread_drawing->KeepRunning())
	{
		m_instance->DoDrawing();
	}
	if (m_instance!=NULL && m_instance->m_thread_drawing!=NULL) m_instance->m_thread_drawing->LeaveWorkingZone();
	return 0;
}

unsigned int ToPTraceFrame::RunThreadDestroying(ttThread* thread)
{
	if (m_instance==NULL || m_instance->m_thread_destroying==NULL || GetCurrentThreadId()!=m_instance->m_thread_destroying->GetId()) return -1;

	m_instance->m_thread_destroying->EnterWorkingZone();

	m_instance->DoDestroying();

	if (m_instance!=NULL && m_instance->m_thread_destroying!=NULL) m_instance->m_thread_destroying->LeaveWorkingZone();
	return 0;
}

unsigned int ToPTraceFrame::RunThreadOpening(ttThread* thread)
{
	if (m_instance==NULL || m_instance->m_thread_opening==NULL || GetCurrentThreadId()!=m_instance->m_thread_opening->GetId()) return -1;

	m_instance->m_thread_opening->EnterWorkingZone();

	m_instance->DoOpening();

	if (m_instance!=NULL && m_instance->m_thread_opening!=NULL) m_instance->m_thread_opening->LeaveWorkingZone();
	return 0;
}

void ToPTraceFrame::DoLogging()			//记录
{
	GUIUDPprint(		//GUI UDP print
		m_form_address->GetValue(),		//addr
		m_form_period->GetValue(),		//period
		wxEmptyString,					//inputfile
		&m_running_logging,				//
		(isSemtech && m_form_printAll->GetValue()),//alldata
		startedAutomatically,
		m_form_systems_box->GetValue() ? m_systems : 0	//
	);
	startedAutomatically = false;

	if (m_running_logging==true)
	{ // Didn't stop because it was asked to by the program, so instead tell the program that it's stopped
		wxMutexGuiEnter();
		ResetAfterLogging();
		wxMutexGuiLeave();
	}
}

void ToPTraceFrame::DoDrawing()
{
	traces_mutex.Lock();
	for (std::vector<ttTraceWindow*>::iterator i=traces.begin(); i!=traces.end(); ++i)
	{
		(*i)->Render();
	}
	traces_mutex.Unlock();

	Sleep(1000);
}

void ToPTraceFrame::DoDestroying()
{
	for (;;)
	{
		m_mutex_destroying.Lock();

		if (m_traces_destroying.empty())
		{ // Terminate this thread
			m_thread_destroying = NULL;
			m_mutex_destroying.Unlock();
			break;
		}

		delete *(m_traces_destroying.begin());
		m_traces_destroying.erase(m_traces_destroying.begin());

		m_mutex_destroying.Unlock();
	}
}

void ToPTraceFrame::DoOpening()
{
	if (Files::openedEncrypted)
	{
		ReadOpenedEncrypted(m_form_period->GetValue(), (isSemtech && m_form_printAll->GetValue()));
	}
	else
	{
		ReadOpenedDecrypted();
	}

	//if (continueReadingFromFile==true)
	{ // Didn't stop because it was asked to by the program, so instead tell the program that it's stopped
		wxMutexGuiEnter();
		ResetAfterOpening();
		wxMutexGuiLeave();
	}
}

void ToPTraceFrame::StartWaiting(const wxString &message)
{
	if (m_instance==NULL || m_instance->m_isWaiting) return;
	
	if (!wxIsMainThread()) wxMutexGuiEnter();
	m_instance->Freeze();
	m_instance->m_waiting_separator->Show(true);
	m_instance->m_waiting_text->SetLabelText(message);
	m_instance->m_waiting_text->Show(true);
	m_instance->m_waiting_gauge->Show(true);
	m_instance->m_formArea->Layout();
	m_instance->Thaw();
	::SendMessage(
		GetHwndOf(m_instance->m_waiting_gauge),
		(UINT)PBM_SETMARQUEE,
		(WPARAM)TRUE,
		(LPARAM)30
	);
	if (!wxIsMainThread()) wxMutexGuiLeave();
	m_instance->m_isWaiting = true;
}

void ToPTraceFrame::StopWaiting(const bool &standalone, const bool &force)
{
	if (m_instance==NULL || !m_instance->m_isWaiting || (!force && !parametersPopulated)) return;

	if (standalone && !wxIsMainThread()) wxMutexGuiEnter();
	::SendMessage(
		GetHwndOf(m_instance->m_waiting_gauge),
		(UINT)PBM_SETMARQUEE,
		(WPARAM)FALSE,
		(LPARAM)30
	);
	if (standalone) m_instance->Freeze();
	m_instance->m_waiting_gauge->Show(false);
	m_instance->m_waiting_text->Show(false);
	m_instance->m_waiting_separator->Show(false);
	if (standalone)
	{
		m_instance->m_formArea->Layout();
		m_instance->Thaw();
		if (!wxIsMainThread()) wxMutexGuiLeave();
	}
	m_instance->m_isWaiting = false;
}

//默认选择展示的曲线
void ToPTraceFrame::InitChecklistParameters()
{
// 	m_parameters_list->Check(PhaseValueOffset);
// 	m_parameters_list->Check(DACValueOffset);
// 	m_parameters_list->Check(H_24HphaseOffset);
// 	m_parameters_list->Check(MDACOffset);
// 	m_parameters_list->Check(LockAgingOffset);

	desiredParameters.push_back("PhaseValue");
	desiredParameters.push_back("DACValue");
	desiredParameters.push_back("MDAC");
	desiredParameters.push_back("Aging");

}

void ToPTraceFrame::PopulateParameters()
{
	if (!parametersPopulated && parametersValidated)
	{ // Populate & show the checklist
		wxMutexGuiEnter();
		parameters_mutex.Lock();
		Freeze();
		StopWaiting(false,true);
		m_parameters_separator->Show(true);

		//在这儿对parameters重新赋为想要的值
		if (parameters.empty())
		{ // Aren't any to plot
			m_parameters_none->Show(true);
			m_trace_window->SetMessage("No traceable data.");
		}
		else
		{ // List them
			m_trace_window->SetMessage("No traces selected.");
			for (std::vector<ttParameter>::iterator i=parameters.begin(); i!=parameters.end(); ++i)
			{
				if (i->detailsIndex==-1)
				{
					m_parameters_list->Append(i->name);
				}
				else
				{
					m_parameters_list->Append(parameterDetails[i->detailsIndex].nameFriendly);
				}

				// Is this a parameter we already want to trace?
				for (std::vector<wxString>::iterator j=desiredParameters.begin(); j!=desiredParameters.end(); ++j)
				{
					// Check against raw and friendly name
					if (j->IsSameAs(i->name,false) || (i->detailsIndex!=-1 && j->IsSameAs(parameterDetails[i->detailsIndex].nameFriendly,false)))
					{
						m_parameters_list->Check(i-parameters.begin());
					}
				}
			}
			m_parameters_list->Show(true);
			m_parameters_plot->Show(true);
		}
		desiredParameters.clear();
		m_formArea->Layout();
		Thaw();
		parameters_mutex.Unlock();
		parametersPopulated = true;
		wxMutexGuiLeave();
		wxCommandEvent* newEvent = new wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED,ID_PARAMETERS_PLOT);
		QueueEvent(newEvent);
	}
}

void ToPTraceFrame::ClearTraces()
{
	// Destroy auxiliary hosts
	derivedListeners_mutex.Lock();
	while (!derivedListeners.empty())
	{
		derivedListeners[0]->Close();
	}
	derivedListeners_mutex.Unlock();

	traces_mutex.Lock();
	for (std::vector<ttTraceWindow*>::iterator i=traces.begin(); i!=traces.end(); )
	{
		EraseTrace(i); // 'i' will be changed by the function
	}
	ArrangeTraces(false);
	traces_mutex.Unlock();
}

void ToPTraceFrame::EraseTrace(std::vector<ttTraceWindow*>::iterator &entry)
{
	delete (*entry);
	entry = traces.erase(entry);
}

void ToPTraceFrame::DisassociateTrace(std::vector<ttTraceWindow*>::iterator &entry)
{ // Renders a ttTraceWindow safe for asynchronous destruction
	(*entry)->PrepareForDestruction();
	(*entry)->Show(false);
	if (m_traceArea!=NULL) m_traceArea->Detach(*entry);
	entry = traces.erase(entry);
}

void ToPTraceFrame::ArrangeTraces(const bool &force, wxSize* areaSize)
{
	int cols,rows;
	CalculateTraceGrid(cols,rows,areaSize);

	Freeze();

	if (m_traceArea!=NULL)
	{ // Check if it needs rearranging - DOES NOT ACCOUNT FOR EMPTY 'CELLS', e.g. five traces arranged in a 3*2 grid
		if (
			!force
			&& m_traceArea->GetColWidths().size()==cols
			&& m_traceArea->GetRowHeights().size()==rows
			&& m_traceArea->GetItemCount()==traces.size()
		)
		{ // Trace sizer already contains the right number of plots
			Thaw();
			return;
		}
		// Start from scratch
		m_wholeArea->Remove(m_traceArea);
		m_traceArea = NULL;
	}

	if (!traces.empty())
	{ // Create & populate the trace area
		m_trace_window->Show(false);
		m_traceArea = new wxFlexGridSizer(rows,cols,0,0);
		for (int i=0; i<cols; ++i)
		{
			m_traceArea->AddGrowableCol(i,1);
		}
		for (int i=0; i<rows; ++i)
		{
			m_traceArea->AddGrowableRow(i,1);
		}

		for (std::vector<ttTraceWindow*>::iterator i=traces.begin(); i!=traces.end(); ++i)
		{
			m_traceArea->Add(
				(*i),
				wxSizerFlags(1).Expand()
			);
		}

		m_wholeArea->Add(m_traceArea, wxSizerFlags(1).Expand());
	}
	else
	{
		m_trace_window->Show(true);
	}
	if (areaSize==NULL)
	{ // Not called from size event, so must be refreshed now
		m_wholeArea->Layout();
	}

	Thaw();
}

void ToPTraceFrame::CalculateTraceGrid(int &x, int &y, wxSize* areaSize)
{
	if (traces.empty())
	{
		x = y = 0;
		return;
	}
	if (areaSize==NULL)
	{
		areaSize = &GetClientSize();
	}

	switch (graphArrangement_method)
	{
		case arrangeRows:
			y = wxMin(graphArrangement_rows,traces.size());
			x = (int)ceil((double)traces.size() / (double)y);
			break;
		case arrangeColumns:
			x = wxMin(graphArrangement_columns,traces.size());
			y = (int)ceil((double)traces.size() / (double)x);
			break;
		default:
			{
				/**
				  Equation for the number of columns is:
					sqr( ( [grid's aspect ratio] / [desired graph aspect ratio] ) * [number of graphs] )
				  Then round that (up OR down as appropriate).
				**/
				double columns = pow(
					(
						(
							(double)(areaSize->x-214)
							/
							(double)areaSize->y
						)
						/
						graphArrangement_ratio
					)
					*
					(double)traces.size()
					,
					0.5
				);

				if (columns-floor(columns) < 0.5)
				{
					x = (int)floor(columns);
				}
				else
				{
					x = (int)ceil(columns);
				}

				y = (int)ceil((double)traces.size() / (double)x);
			}
			break;
	}
}

bool ToPTraceFrame::IsLogging()
{
	return m_running_logging;
}

void ToPTraceFrame::DoneReadingFile()
{
	m_parameters_plot->SetLabelText("Trace Selected");
}

void ToPTraceFrame::SetFilename(const wxString &newName)
{
	if (m_instance==NULL) return;
}

void ToPTraceFrame::SetError(const wxString &error)
{
	SetStatusText(error);
	if (!IsActive()) RequestUserAttention(wxUSER_ATTENTION_ERROR);
}

bool ToPTraceFrame::SaveFiles()
{
	if (Files::decrFileName.IsEmpty() && Files::encrFileName.IsEmpty())
	{
		wxMessageBox("There are no data files to save.", "Error");
		return false;
	}

	wxString directory = wxEmptyString;
	if (!m_LastFile.IsEmpty())
	{ // Use locally noted directory (in case last operation failed and they'd like to try again in the same place)
		directory = m_LastFile;
	}
	else
	{ // Get it from registry
		if (registryBase.HasValue(KEY_RECENT_FILE)) registryBase.QueryValue(KEY_RECENT_FILE, directory);
	}
	directory = directory.BeforeLast('\\')+"\\";
	wxFileDialog tempDialog(
		this,
		wxEmptyString, directory, wxEmptyString,
		Files::decrFileName.IsEmpty() ? "Encrypted Data File (*.dat)|*.dat" : "Decrypted Data File (*.txt)|*.txt",
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT
	);
	if (tempDialog.ShowModal()==wxID_OK)
	{
		wxString fileName = tempDialog.GetPath();
		m_LastFile = fileName; // Store recent file now no matter what
		
		// Remove the file extension
		if (fileName.Length()>4)
		{
			wxString tail = fileName.SubString(fileName.Length()-4, fileName.Length()-1);
			if (tail.IsSameAs(".txt", false) || tail.IsSameAs(".dat", false))
			{
				fileName = fileName.SubString(0, fileName.Length()-5);
			}
		}
	
		wxString newDecr = fileName+".txt";
		wxString newEncr = fileName+".dat";

		if (!Files::decrFileName.IsEmpty())
		{ // Move (if the 'unsaved' temporary file) or copy (if the already saved by the user) the decrypted file.
			if (
				(!Files::saved && !MoveFileEx(Files::decrFileName, newDecr, MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))
				|| (Files::saved && !CopyFile(Files::decrFileName, newDecr, FALSE))
			) {
				wxMessageBox("The decrypted file could not be saved.", "Error");
				return false;
			}
		}
		else
		{
			newDecr.Clear();
		}
		if (!Files::encrFileName.IsEmpty())
		{ // Move (if the 'unsaved' temporary file) or copy (if the already saved by the user) the encrypted file
			if (
				(!Files::saved && !MoveFileEx(Files::encrFileName, newEncr, MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))
				|| (Files::saved && !CopyFile(Files::encrFileName, newEncr, FALSE))
			) {
				wxMessageBox("The encrypted file could not be saved.", "Error");
				return false;
			}
		}
		else
		{
			newEncr.Clear();
		}

		// Update file parameters
		Files::saved = true;
		Files::decrFileName = newDecr;
		Files::encrFileName = newEncr;

		// Update GUI
		if (m_originalTitle[0]=='*')
		{ // Remove asterisk from title
			m_originalTitle.Replace("*", "", false);
			if (m_specialTitle.IsEmpty())
			{
				SetTitle(m_originalTitle);
			}
			else
			{
				SetTitle(m_originalTitle + " - " + m_specialTitle);
			}
		}
		if (Files::decrFileName.IsEmpty())
		{ // Only saved encrypted file
			SetStatusText("Dapu debug data only saved to \""+Files::encrFileName.AfterLast('\\')+'"');
		}
		else
		{ // Decrypted file was saved
			SetStatusText("Saved to \""+Files::decrFileName.AfterLast('\\')+'"');
		}

		registryBase.SetValue(KEY_RECENT_FILE, fileName); // Only store recent directory & file in registry if successful

		return true;
	}

	return false;
}

/***************
  ttEmptyFrame
***************/

ttEmptyFrame::ttEmptyFrame(wxWindow* parent, const wxString &message)
	: wxPanel(
		parent,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxBORDER_SUNKEN
	)
{
	wxBoxSizer* outer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* inner = new wxBoxSizer(wxVERTICAL);
	inner->Add(
		m_message = new wxStaticText(this,wxID_ANY,message),
		wxSizerFlags().Centre()
	);
	outer->Add(inner, wxSizerFlags(1).Centre());
	SetSizer(outer);
}

void ttEmptyFrame::SetMessage(const wxString &message)
{
	m_message->SetLabelText(message);
}