#ifndef EVENT_MESSAGE_CONTROLLER_H
#define EVENT_MESSAGE_CONTROLLER_H

#include "TransmissionProtocol.h"
#include "ToPSyncTypes.h"
#include "Socket.h"
#include "SystemConfiguration.h"
#include "AlarmMonitor.h"
#include "ApplicationInfrastructureInterface.h"

#ifdef _ARC
  #include <mqx.h>
  #include <mutex.h>
#else
  typedef struct { int dummy; } MUTEX_STRUCT;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_EVENT_MESSAGE_LENGTH 128


typedef enum{
	alarmInitStatus,
	alarmWaitingForChangeStatus,
	alarmSendingActiveStatus,
	alarmSendingInactiveStatus,
	alarmErrorStatus
}EventMessageAlarmControllerStatus;


typedef enum{
	restartInitStatus,
	restartReceivedAckStatus,
	restartTimedOutStatus,
	restartErrorStatus
}EventMessageRestartControllerStatus;


typedef struct
{
	ElapsedTime tickPeriod;
	uint32 ticksToTimeout;
	uint32 ticksToPrint;
	uint32 printPeriodTicks;
	Bool 	infiniteTimeout;
} EventMessageTimingStruct;


typedef struct
{
	Bool   enabled;
	EventMessageAlarmControllerStatus state;
	EventMessageTimingStruct	timing;
	EnhancedTransmissionProtocolAddress destination;
    Bool previousAlarmSet;
	AlarmSourceArray previousActiveAlarms;
	uint8 printBuffer[MAX_EVENT_MESSAGE_LENGTH];
} AlarmMessageControllerStruct;



typedef struct
{
	Bool   configuredForUse;
	Bool   enabled;
	EventMessageRestartControllerStatus state;
	EventMessageTimingStruct	timing;
	EnhancedTransmissionProtocolAddress destination;
	uint8 printBuffer[MAX_EVENT_MESSAGE_LENGTH];
} RestartMessageControllerStruct;


typedef struct
{
	AlarmMessageControllerStruct alarmController;
	RestartMessageControllerStruct restartController;

	// transport specific parameters
	NetworkInterfaceId networkInterfaceId;
	uint32 mHomeIndex;
	uint16 myUdpPort;
	SocketHandle socketHandle; //udp only
    uint8 networkProtocol;	// ipv4 or ipv6

	/* Eventually the entire module should be semaphore protected with it's own semaphore rather than relying
	 * on the big data lock. But for now the semaphore just protects the message buffer. This buffer used to
	 * exist in targetprintf() on the stack, but putting 1KB on the stack can cause stack overflows, as was
	 * found to be the case. Putting it here instead. The reason semaphore protection is added is because not
	 * all tasks use the big data lock, so can't rely on this for concurrency protection any more. */
	MUTEX_STRUCT mutex;
} EventMessageController;

void InitialiseEventMessageController(EventMessageController* ctl, ElapsedTime tickPeriod);
void OpenEventMessagePrintPort(EventMessageController* ctl);

void EventMessageControllerAlarmTick(EventMessageController* ctl);
void SetEventMessageAlarmPeriod(EventMessageController* ctl, uint8 printPeriod);
void EnableEventMessageAlarmControllerPort(EventMessageController* ctl, EnhancedTransmissionProtocolAddress const* sourceAddress);
void EnableEventMessageAlarmController(EventMessageController* ctl, Bool enable, uint32 timeout);
Bool ReadyToPrintEventAlarmMessage(EventMessageController* ctl);
void SendEventMessageControllerAlarmMsg(EventMessageController* ctl);


void EventMessageControllerRestartTick(EventMessageController* ctl);
void SetEventMessageRestartPeriod(EventMessageController* ctl, uint8 printPeriod);
void EnableEventMessageRestartControllerPort(EventMessageController* ctl, EnhancedTransmissionProtocolAddress const* sourceAddress);
void EnableEventMessageRestartController(EventMessageController* ctl, Bool enable, uint32 timeout);
Bool ReadyToPrintEventRestartMessage(EventMessageController* ctl);
void SendEventMessageControllerRestartMsg(EventMessageController* ctl);




//Function pointer functions
void MessageReceivedFromSocketEventMessageController(void* ctl,
		EnhancedTransmissionProtocolAddress const* sourceAddress,
		uint8 const data[], uint16 dataLength);

void TransportServiceStateChangeEventMessageController(void* ctl,
		SocketHandle socketHandle, uint16 udpPort); 



#define EventMessageControllerAlarmEnabled(ctl) ((ctl)->alarmController.enabled)
#define GetEventMessageControllerAlarmPrintPeriod(ctl) ((ctl)->alarmController.timing.printPeriodTicks * (ctl)->alarmController.timing.tickPeriod)
#define GetSocketHandle(ctl) ((ctl)->socketHandle) // NO_SOCKET if invalid
#define EventMessageControllerRestartEnabled(ctl) ((ctl)->restartController.enabled)
#define EventMessageControllerRestartConfigured(ctl) ((ctl)->restartController.configuredForUse)

#ifdef __cplusplus
}
#endif

#endif
