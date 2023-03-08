#ifndef VISIBLE_MASTER_DIRECTION_H
#define VISIBLE_MASTER_DIRECTION_H

#include "General.h"
#include "GrantMonitor.h"
#include "IEEE1588Messages.h"
#include "SequenceNumberChecker.h"
#include "ExecutionMonitor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
	struct VisibleMasterStruct*		master;
	Bool							active;
	Bool							acceptMulticastTimingMessages;
	Bool							enableUnicastGrantRequests;
	Direction						direction;
	ExecutionMonitor				messageReceptionMonitor; // finds whether enough sync or delayResponse messages are being received
	ExecutionMonitor				followupReceptionMonitor; // finds whether enough sync or delayResponse messages are being received
	GrantMonitor					grantMonitor;

	LogMessagePeriod				logExpectedUpdatePeriod;  


	SequenceNumberChecker			timingMessageSequenceNumberMonitor;
	LogMessagePeriod				logReceivedMulticastTimeUpdatePeriod;  // received from multicast sync messages

	// time of next timing message - only used for delay requests
	sint16							fastTicksUntilNextTimingMessage;  // only used for delay requests
	float							fastTicksPerTimingMessage;
	uint16							previousFastTicksUntilNextTimingMessage;

	//variables to keep mean delay request rate correct
	float							timingMessagesPerSlowTickPeriod;
	float							extraTimingMessagesNeeded;
	uint16							timingMessagesSentThisSlowTick;
	Bool							firstMessageOfSlowTickPeriod;
	Bool							forcedGrant;
	LogMessagePeriod				delayReqLogPeriod;
} VisibleMasterDirection;


void InitialiseVisibleMasterDirection(VisibleMasterDirection* vmd, 
		struct VisibleMasterStruct* master, Direction direction,
		AlarmSource refusedGrantAlarmSource, AlarmSource ignoredGrantAlarmSource, 
		AlarmSource unfulfilledGrantAlarmSource0, AlarmSource unfulfilledGrantAlarmSource1,
		AlarmSourceIdentity identity, struct AlarmMonitorStruct* alarmMonitor);

void CreateVisibleMasterDirection(VisibleMasterDirection* vmd);
	// when a new VisibleMaster is found

void ResetVisibleMasterDirection(VisibleMasterDirection*);

Bool DelayInformationReceivedVMD(VisibleMasterDirection* direction,
			MessageHeader const* header,
			MessageType messageType,
			LogMessagePeriod  logUpdatePeriod); // UNDEFINED_LOG_PERIOD if not carried in message


void SetActiveVMD(VisibleMasterDirection* vmd, Bool active, Bool grantNecessary);
#define ActiveVMD(vmd) ((vmd)->active)
#define SetVisibleMasterDirectionRequestedGrantDuration(vmd,d) SetRequestedDurationGM(&(vmd)->grantMonitor,(d))
#define SetVisibleMasterDirectionRequestedLogPeriod(vmd,p) SetRequestedLogPeriodGM(&(vmd)->grantMonitor,(p))
#define SetVisibleMasterDirectionAcceptableLogPeriod(vmd,p) SetAcceptableLogPeriodGM(&(vmd)->grantMonitor,(p))

#define SetAcceptMulticastTimingMessagesVMD(vmd,a) ((vmd)->acceptMulticastTimingMessages = (a))
#define SetEnableUnicastGrantRequestsVMD(vmd,a) ((vmd)->enableUnicastGrantRequests = (a))

#define SetVisibleMasterDirectionGrantRequestThreshold(vmd,t) SetRequestRepeatThresholdGM(&(vmd)->grantMonitor,(t))
#define SetVisibleMasterDirectionGrantRepeatPeriod(vmd,p) SetRequestRepeatPeriodGM(&(vmd)->grantMonitor,(p))


void SlowTickVisibleMasterDirection(VisibleMasterDirection* vmd);

void FastTickVisibleMasterDirection(VisibleMasterDirection* vmd);

#define LogTimingPeriodVMD(vmd) ((vmd)->logExpectedUpdatePeriod)
//assume active if in forced grant state as we are pretending grants are working
#define TimingMessageGrantIsActiveVMD(vmd) (GrantIsActiveGM(&(vmd)->grantMonitor) || (vmd)->forcedGrant)
Bool TimingMessageGrantIsFulfilledVMD(VisibleMasterDirection* vmd);
#define TimingMessageGrantIsRequestedVMD(vmd) GrantRequested(&(vmd)->grantMonitor)

Bool TimingMessageGrantSituationGoodVMD(VisibleMasterDirection const* vmd); // grant given or grant not needed


ElapsedTime TimingPeriodVMD(VisibleMasterDirection const* direction);


#define VisibleMasterDirectionTimeUpdatePeriodHasBeenGranted(vmd, logPeriod, durationInSecs) GrantGivenGM(&(vmd)->grantMonitor, logPeriod, durationInSecs)

#define VisibleMasterDirectionTimingMessagesCancelled(vmd) GrantCancelledGM(&(vmd)->grantMonitor)
#define RequestTimingMessagesVMD(vmd, enable) RequestGrantGM(&(vmd)->grantMonitor, enable);
#define IsSequenceNumberAcceptableVMD(vmd,n) IsSequenceNumberAcceptable(&(vmd)->timingMessageSequenceNumberMonitor, (n))

Bool TimingMessageAcceptableVMD(VisibleMasterDirection const* direction, MessageHeader const* header);
void EnableForcedGrantVMD(VisibleMasterDirection *direction, LogMessagePeriod delayReqLogPeriod, Bool enable);

#ifdef __cplusplus
}
#endif

#endif


