#ifndef SMPTE_DATA_H
#define SMPTE_DATA_H

#include "SystemManagementMessageHandler.h"
#include "SampleDivider.h"
#include "TLVIdentities.h"
#include "TwoLevelAddress.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WORD_SIZE 4
#define SMPTE_DATA_SIZE 42
#define SMPTE_MAX_LOG_PERIOD 3
#define SMPTE_MIN_LOG_PERIOD -2


typedef struct SmpteDataStruct
{
	uint32			defaultSystemFrameRateNumerator;
	uint32			defaultSystemFrameRateDenominator;
	uint8			masterLockingStatus;
	uint8			timeAddressFlags;
	sint32			currentLocalOffset;
	sint32			jumpSeconds;
	uint32			timeOfNextJumpMSB;   //48 bit number
	uint16			timeOfNextJumpLSB;   //
	uint32			timeOfNextJamMSB;   // 48 bits used
	uint16			timeOfNextJamLSB;   //
	uint32			timeOfPrevJamMSB;   // 48 bits used
	uint16			timeOfPrevJamLSB;   //
	sint32			prevJamLocalOffset;
	uint8			daylightSaving;
	uint8			leapSecondJump;
}SmpteData;


typedef struct SmpteSendDataStruct
{
	Bool			enable;
	sint8			sendPeriod; //of data
	ElapsedTime		tickPeriod;
	SampleDivider	sampleDivider;
	Bool			sendTheDataNow;
}SmpteSendData;



typedef struct SmpteReceiveDataStruct
{
	Bool		dataIsNew;
	Bool		dataHasBeenReadByBCMaster;
	ElapsedTime timeSinceLastTlv;
	ElapsedTime tlvTimeout;
	AlarmClient	alarmTooFewSMTLVs;
	AlarmClient alarmNewSMTLVData;
}SmpteReceiveData;



typedef struct SmpteControlStruct
{
	SmpteData			data;
	SmpteSendData		send;
	SmpteReceiveData 	receive;
}SmpteControl;

void InitialiseSmpteData(SmpteControl* smpte, uint8 portLocalid, AlarmMonitor *monitor, ElapsedTime tickPeriod);

void ResetSmpteData(SmpteControl* smpte);
Bool SmpteDataReceived(SmpteControl* smpte, TwoLevelAddress const* sourceAddress, PortId const* sourceId, uint16 lengthInBytes, uint8 const **data);
Bool TickSmpteDataSend(SmpteControl* smpte);
Bool SmpteDataIsThere(SmpteControl * const control);
Bool SmpteDataHasChanged(SmpteControl * const control, SmpteData *newData);
void SmpteSetPeriod(SmpteControl *control, sint8 logPeriod);
void SmpteUpdateAlarmStateTooFewTlvs(SmpteControl *control, Bool active);
void SmpteUpdateAlarmStateNewDataTlv(SmpteControl *control, Bool active);
void SmpteTooFewTlvsAlarmTick(SmpteControl *control);

#ifdef __cplusplus
}
#endif

#endif
