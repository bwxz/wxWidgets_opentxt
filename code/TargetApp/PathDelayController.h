#ifndef PATH_DELAY_STORE_H
#define PATH_DELAY_STORE_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "QueueTemplate.h"
#include "MessageStore.h"
#include "AlarmClient.h"
#include "ExecutionMonitor.h"
#include "AlarmMonitor.h"
#include "IEEE1588Messages.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	sint32					roundTripDelayNs;
	uint16					ticksToLive;
} PathDelay;

QueueTemplateDeclaration(PathDelay);

typedef enum
{
	pDelayResponseRx,
	pDelayResponseUnexpected,
	pDelayFollowUpRx,
	pDelayFollowUpUnexpected,
	numberOfpDelayExecutionTypes
} PDelayExecutionMonitorType;

typedef struct
{
	//Configuration
	uint16					ticksToLive;	// the length of an element's life
	uint16					minValidElements;	//for a valid output
	Bool					enabled;	// send path delay requests

	//Operation
	PortId					remotePort; // the port to which the object is measuring the delay
	PathDelayQueue			delayStore;	// holds the most recent delays, the measured delay value is half the minimum in this store
	MessageStore			requestTxTimeStore;
	MessageStore			requestRxTimeStore;
	MessageStore			responseRxTimeStore;
	ExecutionMonitor		messageReceptionMonitor[numberOfpDelayExecutionTypes]; // finds whether enough messages are being received
	AlarmClient				informationInvalidAlarm;

	struct
	{
		Bool					valid;
		sint32					value;
	} cache;

} PathDelayController;

void InitialisePathDelayController(PathDelayController* pdc, uint8 alarmId, AlarmMonitor* alarmMonitor, uint16 maxElements, uint16 minValidElements, uint16 ticksToLive);
void ResetPathDelayController(PathDelayController* pds);
void PathDelayControllerSlowTick(PathDelayController* pds);
void PathDelayControllerPhaseJump(PathDelayController* pdc);
void PathDelayRequestTransmitted(PathDelayController* pdc, IEEE1588SequenceNumber sequenceNumber, IEEE1588Time const* transmitTime);
void PathDelayResponseMessageReceived(PathDelayController* pdc, MessageType messageType, LongTimingMessage const* message, IEEE1588Time const* receiveTime);
	// PathDelayResponseMessageReceived is called when a pathDelayResponseMsg OR pathDelayFollowUpMsg
	// isTwoStep is ignored when isFollowUp == TRUE
	// msgTime is the value of the time carried in the message
	// correction is the value of the correction field of the message


#define PathDelayControllerEnabled(pdc) ((pdc)->enabled)
void EnablePathDelayController(PathDelayController* pdc, Bool enable);

#define PathDelayControllerDataValid(pdc) (PathDelayControllerEnabled(pdc) && (pdc)->cache.valid)
#define PathDelayControllerDataInvalid(pdc) (PathDelayControllerEnabled(pdc) && !(pdc)->cache.valid)
#define PathDelayControllerValue(pdc) ((pdc)->cache.value)

#ifdef __cplusplus
}
#endif


#endif
