#ifndef ALARM_CLIENT_H
#define ALARM_CLIENT_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



struct AlarmMonitorStruct;
#define NO_OF_ALARM_SOURCE_IDENTITIES 32

typedef struct AlarmClientStruct
{
	AlarmSource					source;
	AlarmSourceIdentity			identity; 
								// uniquely identifies this client, within all clients that generate this alarm condition
								// values 0 to NO_OF_ALARM_SOURCE_IDENTITIES-1 are valid

	Bool						initialState;
	Bool						active;	// initial state is FALSE

	struct AlarmMonitorStruct*	monitor;  //the alarm monitor of which this is a client. May be NULL 
} AlarmClient;


void InitialiseAlarmClient(AlarmClient* client, 
			AlarmSource source, AlarmSourceIdentity identity, 
			struct AlarmMonitorStruct* monitor,  // may be NULL
			Bool initialState);
	// identity uniquely identifies this client, within all clients that generate this alarm condition
	// values 0 to NO_OF_ALARM_SOURCE_IDENTITIES-1 are valid 

#define ResetAlarmClient(client) UpdateAlarmState((client),(client)->initialState)

// UpdateAlarmState may be called by the monitored entity 
// either when the activity of a alarm changes 
// or periodically, whether the alarm has changed or not
void UpdateAlarmState(AlarmClient* client, Bool active);  

#ifdef __cplusplus
}
#endif


#endif
