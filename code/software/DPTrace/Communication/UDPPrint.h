/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/development/ctonksWork/utilities/ToPTrace/Communication/UDPPRintfMain.cpp $
 * $Revision: #8 $
 * $Date: 2014/09/10 $
 */

#ifndef UDP_PRINT_H
#define UDP_PRINT_H

#include "UDP.hpp"
#include "..\Interface\DerivedTraceHost.h"
#include "..\Interface\Thread.h"

#define MAX_PRINTF_MESSAGE_SIZE 1024
#define SENTENCE_BUFFER_SIZE MAX_PRINTF_MESSAGE_SIZE*5

#define DataOfMoudleSys		0							//模块直接输出的消息格式
#define DataOfCMTestSys		DataOfMoudleSys+1			//模块通过新工装系统的输出消息格式，添加有字段号；
#define _DPTraceProduct		DataOfMoudleSys				//选择哪个产品数据

typedef enum
{
	GenrealMaskOffset=0,
	SyncFlagOffset=1,
	WorkStateOffset,
	RunstateOffset,
	PhaseValueOffset,
	DACValueOffset,
	FactorOffset,
	HoldCntOffset,
	RunhourOffset,
	factor4daysOffset,
	H_24HphaseOffset,
	MDACOffset,
	AgingOffset,
	CM55AddressOffset,
	LockAgingOffset,
	XadjustfactorOffset,
	YDACAverHourOffset,
	ZDACAver30sOffset,
	DACAver30sOffset,
	dptelOffset,
	LockSec00_SecOffeset,
#if _DPTraceProduct==DataOfCMTestSys
	CMtestprj_AddrOffeset,
	CMtestprj_SecOffeset,
#endif
	NumbersOfCM55KeyDatat
}CM55KeyDataOffset;


extern bool continueReadingFromFile;
extern ttThread* fileReader;
extern ttThread* requestThread;
extern Semtech::UDP::Port port;
extern bool encrWritten;
extern bool decrWritten;

unsigned int RequestPrintFromTarget(ttThread* thread);

bool PrintDecrypted(uint8* buffer, uint16 size, bool firstLine, bool& debugLine, bool live);

bool PrintEncrypted(uint8* buffer, uint16 size);

void ReformatOutput(uint8* buffer);

void ParseTitleLine(uint8* buffer, uint16 size);

void ReformatDmOutput(uint8* buffer);

wxString ValidateParameters(uint8* buffer,uint8 returndelimssnoffset);

void SendDataToTraces(const char* buffer, const unsigned long& loggedTime, const bool& fromFile, const std::vector<ttDerivedTraceHost*>* const extraListeners=NULL);

unsigned int ReadFromFile(ttThread* thread, void* extra);

void StartWaiting(const wxString& message);

void StopWaiting();

int GUIUDPprint(const wxString& input_address, const wxString& input_period, const wxString& input_file, bool* StartedFlag, const bool& input_printAll, bool startedAutomatically, const unsigned long& systems);

bool OpenExistingFile(const wxString& filename);
unsigned int ReadOpenedEncrypted(const wxString &input_period, const bool &input_printAll);
unsigned int ReadOpenedDecrypted();

namespace Files
{
	extern bool saved;
	extern wxString encrFileName;
	extern wxString decrFileName;
	extern wxString openFileName;
	extern HANDLE decrFile;
	extern HANDLE encrFile;
	extern bool openedEncrypted;
}

#endif