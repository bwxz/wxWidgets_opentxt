#ifndef UNICAST_MASTER_CONTROLLER_H
#define UNICAST_MASTER_CONTROLLER_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "GrantMonitor.h"
#include "ExecutionMonitor.h"
#include "SampleDivider.h"
#include "ToPSyncTypes.h"
#include "IEEE1588Messages.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	struct PtpPortStruct*			port; //NULL when record is unused
	GrantMonitor					grantMonitor;
	ExecutionMonitor				messageReceptionMonitor; // finds whether enough announce messages are being received

	PortId							grantorId;
	TransmissionProtocolAddress		grantorAddress;  
} UnicastMasterRecord;

typedef struct
{
	UnicastMasterRecord*	store;
	UnicastMasterRecord*	end;
	UnicastMasterRecord*	next;
	SampleDivider			sampleDivider;

} UnicastMasterController;


//Master controller functions
void InitialiseUnicastMasterController(UnicastMasterController* controller, uint16 size,  
			struct AlarmMonitorStruct* alarmMonitor,
			ElapsedTime elementTickPeriod, ElapsedTime tickPeriod);

void ResetUnicastMasterController(UnicastMasterController* controller);

void TickUnicastMasterController(UnicastMasterController* controller);

void UMCAnnounceMessageReceived(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		TransmissionProtocolAddress const* address, PortId const* id);

Bool AddToUnicastMasterController(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		TransmissionProtocolAddress const* address, PortId const* id);
	// EITHER address OR id may be NULL

Bool AddToUnicastMasterControllerAtIndex(UnicastMasterController* controller,
		struct PtpPortStruct* port,
		TransmissionProtocolAddress const* address, PortId const* id, uint8 index);
	// EITHER address OR id may be NULL

Bool RemoveFromUnicastMasterController(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		TransmissionProtocolAddress const* address, PortId const* id);
	// EITHER address OR id may be NULL

Bool RemoveFromUnicastMasterControllerExactMatch(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		TransmissionProtocolAddress const* address, PortId const* id);

Bool RemoveFromUnicastMasterControllerAtIndex(UnicastMasterController* controller, uint8 index);


//not used void RemoveAPortFromUnicastMasterController(UnicastMasterController* controller,
//												struct PtpPortStruct const* port);

void UnicastMasterControllerGrantGiven(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		PortId const* id, TransmissionProtocolAddress const* address, 
		LogMessagePeriod logMessagePeriod, uint32 duration);
	// EITHER address OR id may be NULL

void UnicastMasterControllerGrantCancelled(UnicastMasterController* controller, 
		struct PtpPortStruct* port,
		PortId const* id, TransmissionProtocolAddress const* address);
	// EITHER address OR id may be NULL

void UMCPtpPortRequestedAnnounceDetailsHaveChanged(UnicastMasterController* controller, struct PtpPortStruct* port);
void UMCPtpPortRequestedAnnounceConfigDetailsHaveChanged(UnicastMasterController* controller, struct PtpPortStruct* port);


UnicastMasterRecord* FindNextUnicastMasterControllerElement(UnicastMasterController* controller,
		struct PtpPortStruct const* port,
		TransmissionProtocolAddress const* address, PortId const* id,
		UnicastMasterRecord const* previous);
	// port and any later parameter may be NULL
	// if previous is NULL the first matching element is returned
	// otherwise the first matching elment after previous is returned

UnicastMasterRecord* FindNextUnicastMasterControllerElementExactMatch(UnicastMasterController* controller,
		struct PtpPortStruct const* port,
		TransmissionProtocolAddress const* address, PortId const* id,
		UnicastMasterRecord const* previous);

UnicastMasterRecord* FindUnicastMasterControllerElementAtIndex(UnicastMasterController* controller, uint8 index);


void UMCEnableGrantRequests(UnicastMasterController* controller, struct PtpPortStruct const* port,
		TransmissionProtocolAddress const* address, PortId const* id, Bool enable);

void UMCEnableGrantRequestsAtIndex(UnicastMasterController* controller, Bool enable, uint8 index);

//Master record functions - called only by Master controller
void InitialiseUnicastMasterRecord(UnicastMasterRecord* record, 
	uint32 requestedDuration, uint16 requestRepeatThreshold, uint16 requestRepeatPeriod, 
	LogMessagePeriod requestedLogPeriod, LogMessagePeriod acceptableLogPeriod,
	uint8 identity, struct AlarmMonitorStruct* alarmMonitor,
	ElapsedTime tickPeriod);
// the controller will ask that the grant be renewed when the remaining time is less than requestThreshold (in secs)

void ResetUnicastMasterRecord(UnicastMasterRecord* record);
Bool EnableUnicastMasterRecord(UnicastMasterRecord* record, 
			struct PtpPortStruct* port,
			TransmissionProtocolAddress const* address, PortId const* id);
	// EITHER address OR id may be NULL


void UnicastMasterRecordTick(UnicastMasterRecord* record);
void UnicastMasterGrantGiven(UnicastMasterRecord* record, LogMessagePeriod logMessagePeriod, uint32 duration);
void UnicastMasterRecordGrantCancelled(UnicastMasterRecord* record);
void UpdateRecordGrantRequestParameters(UnicastMasterRecord* record, struct PtpPortStruct* port);
void UpdateRecordGrantRequestConfigParameters(UnicastMasterRecord* record, struct PtpPortStruct* port);
void UpdateRecordReinitialiseGrantRequestParameters(UnicastMasterRecord* record, struct PtpPortStruct* port, LogMessagePeriod ideal,
		LogMessagePeriod required, uint32 duration);

void DeleteUnicastMasterRecord(UnicastMasterRecord* record);
#define UnicastMasterRecordEnabled(record) ((record)->port != NULL)
void UnicastMasterRecordEnableGrantRequests(UnicastMasterRecord* record, Bool enable);

#ifdef __cplusplus
}
#endif

#endif

