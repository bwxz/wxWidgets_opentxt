#ifndef GRANT_MONITOR_H
#define GRANT_MONITOR_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "HysteresisController.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	// Configuration
	uint32						requestedDurationSecs;  
	uint16						ticksPerSecond; 
	LogMessagePeriod			requestedLogPeriod;
	LogMessagePeriod			acceptableLogPeriod;
	
	uint16						configuredRequestThreshold;  // request renewal this number of ticks before expiry 
	uint16						requestRepeatPeriodTicks;  // repeat renewal request after this number of ticks

	// Operation
	uint16						increaseInRequestedPeriod;	//due to grant refusals
	LogMessagePeriod			grantedLogPeriod;
	sint32						currentRequestThreshold;
	sint32						ticksRemaining;	// until grant expires
	Bool						requestingGrant; // grant may not have been given
	AlarmClient					refusedRequestAlarm;
	AlarmClient					ignoredRequestAlarm;
} GrantMonitor;


void InitialiseGrantMonitor(GrantMonitor* monitor, 
				uint32 requestedDuration, uint16 requestRepeatThreshold, uint16 requestRepeatPeriod,
				LogMessagePeriod requestedLogPeriod, LogMessagePeriod acceptableLogPeriod,
				AlarmSource refusedGrantAlarmSource, AlarmSource ignoredGrantAlarmSource,
				AlarmSourceIdentity identity, struct AlarmMonitorStruct* alarmMonitor,
				ElapsedTime tickPeriod);
	// the monitor will ask that the grant be renewed when the remaining time is less than requestThreshold (in secs)

void ReinitialiseGrantMonitor(GrantMonitor* monitor, 
				uint32 requestedDuration, uint16 requestRepeatThreshold, uint16 requestRepeatPeriod,
				LogMessagePeriod requestedLogPeriod, LogMessagePeriod acceptableLogPeriod);

void ResetGrantMonitor(GrantMonitor* monitor);


void EnableGrantRequestsGM(GrantMonitor* monitor, Bool enable); //enable FALSE is disable

void GrantGivenGM(GrantMonitor* monitor, LogMessagePeriod logPeriod, uint32 duration);

void GrantCancelledGM(GrantMonitor* monitor);
void GrantRefusedGM(GrantMonitor* monitor);
Bool GrantMonitorTick(GrantMonitor* monitor); //returns true if the grant should be renewed.  Repeats once per second
#define GrantIsActiveGM(monitor) ((monitor)->ticksRemaining > 0)
#define GrantSituationIsGoodGM(monitor) (GrantIsActiveGM(monitor) || !(monitor)->requestingGrant)
#define GrantRequested(monitor) ((monitor)->requestingGrant)
#define GrantedLogPeriodGM(monitor) ((monitor)->grantedLogPeriod)
#define IdealLogPeriodGM(monitor) ((monitor)->requestedLogPeriod)  //what we want
#define LogPeriodInGrantRequestMessageGM(monitor)  (IdealLogPeriodGM(monitor) + (monitor)->increaseInRequestedPeriod) //what we ask for 
#define AcceptableLogPeriodGM(monitor) ((monitor)->acceptableLogPeriod)
uint32 GrantRemainingGM(GrantMonitor const* monitor);
#define RequestedGrantDurationGM(monitor) ((monitor)->requestedDurationSecs)
void SetRequestedLogPeriodGM(GrantMonitor* monitor, LogMessagePeriod requestedLogPeriod);
void SetAcceptableLogPeriodGM(GrantMonitor* monitor, LogMessagePeriod acceptableLogPeriod);
void SetRequestedDurationGM(GrantMonitor* monitor, uint32 requestedDuration);
void SetRequestRepeatPeriodGM(GrantMonitor* monitor,uint16 requestRepeatPeriod);
void SetRequestRepeatThresholdGM(GrantMonitor* monitor,uint16 requestThreshold);


#ifdef __cplusplus
}
#endif

#endif
