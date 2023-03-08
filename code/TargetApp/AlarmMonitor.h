#ifndef ALARM_MONITOR_H
#define ALARM_MONITOR_H

#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct AlarmSourceArrayStruct
{
	uint32 array[ALARM_SOURCE_WORDS];
}AlarmSourceArray;


typedef enum
{
	alarmModeLevel,
	alarmModeSticky,
	alarmModeChangeDetect
}AlarmMode;


typedef enum
{
	alarmPolarity0,
	alarmPolarity1
}AlarmPolarity;

typedef enum
{
	activeDriveOff,
	activeDriveOn
}AlarmActiveDriveControl;

typedef enum
{
	alarmPin0ff,
	alarmPinOn,
	alarmPinHiZ
}AlarmPinState;


/*AlarmStateArray is defined in ToPSyncInterfaceTypes*/
typedef struct AlarmStateStruct
{
	AlarmStateArray set;	/*client alarm state - also used to store alarmCurrentValue for transitory mode*/
	AlarmStateArray mask;	/*client mask*/
	AlarmStateArray alarmRequest;
	AlarmStateArray alarmResetRequest; /*don't allow users direct access to alarmRequest as we only want to clear the requestBits on a tick*/
	AlarmStateArray alarmDetectedSticky;
} AlarmState;


typedef struct AlarmMonitorStruct
{
	AlarmState		alarms[numberOfAlarmTypes];
	Bool			globalAlarmActive;
	AlarmSourceArray activeAlarms;
	AlarmMode		mode;
	AlarmPolarity 	polarity;
	AlarmActiveDriveControl driveControl;
} AlarmMonitor;


#define SetAlarmStateHigh(ptr, alarmId, clientId) (ptr->alarms[alarmId].set.array[clientId / BITS_IN_ALARM_WORD] |= (1 << (clientId % BITS_IN_ALARM_WORD)))
#define SetAlarmStateLow(ptr, alarmId, clientId) (ptr->alarms[alarmId].set.array[clientId / BITS_IN_ALARM_WORD] &= ~(1 << (clientId % BITS_IN_ALARM_WORD)))

#define MaskAlarmState(ptr, alarmId, clientId) (ptr->alarms[alarmId].mask.array[clientId / BITS_IN_ALARM_WORD] |= (1 << (clientId % BITS_IN_ALARM_WORD)))
#define UnMaskAlarmState(ptr, alarmId, clientId) (ptr->alarms[alarmId].mask.array[clientId / BITS_IN_ALARM_WORD] &= ~(1 << (clientId % BITS_IN_ALARM_WORD)))

#define SetBitHigh(arrayStruct, id) (arrayStruct.array[id / BITS_IN_ALARM_WORD] |= (1 << (id % BITS_IN_ALARM_WORD)) )
#define SetBitLow(arrayStruct, id) (arrayStruct.array[id / BITS_IN_ALARM_WORD] &= ~(1 << (id % BITS_IN_ALARM_WORD)) )


void InitialiseAlarmMonitor(AlarmMonitor* monitor);

void UpdateAlarmStateAM(AlarmMonitor* monitor, AlarmClient const* client);
	// called only by AlarmClient

Bool AlarmSetAM(AlarmMonitor * monitor);//returns true if one or more alarms are active
//void WriteAlarmStateToPinAM(AlarmMonitor* monitor); // must be called each tick

Bool AlarmSourceSetAM(AlarmMonitor const* monitor, AlarmSource alarmSource); //returns true if the alarmSource is active

void EnableAlarmSourceAM(AlarmMonitor* monitor, AlarmSource alarmSource, Bool enable);
void EnableAlarmAM(AlarmMonitor* monitor, AlarmSource alarmSource, AlarmSourceIdentity alarmSourceIdentity, Bool enable);
void SetAlarmSourceClientsAM(AlarmMonitor* monitor, AlarmSource alarmSource, AlarmStateArray array);
void GetAlarmSourceClientsAM(AlarmMonitor* monitor, AlarmSource alarmSource, AlarmStateArray *array);
void GetAlarmSourceRequestsAM(AlarmMonitor *monitor, AlarmSource alarmSource, AlarmStateArray *arrayOfRequests);
void SetAlarmSourceRequestsAM(AlarmMonitor *monitor, AlarmSource alarmSource, AlarmStateArray arrayOfRequests);

Bool GetAlarmSourceActive(AlarmMonitor* monitor, AlarmSource alarmSource);

Bool AlarmSourceEnabledAM(AlarmMonitor* monitor, AlarmSource alarmSource);
Bool AlarmEnabledAM(AlarmMonitor* monitor, AlarmSource alarmSource, AlarmSourceIdentity alarmSourceIdentity);

uint32 AlarmClientSetAM(AlarmMonitor* monitor, AlarmSource alarmSource, Bool masked);
void AlarmClientSetArrayAM(AlarmMonitor* monitor, AlarmSource alarmSource, Bool masked, AlarmStateArray *arrayOfSets);


#ifdef __cplusplus
}
#endif

#endif
