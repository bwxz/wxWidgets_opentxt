#ifndef EVENT_MESSAGE_TRANSMIT_QUEUE_H
#define EVENT_MESSAGE_TRANSMIT_QUEUE_H

#include "General.h"
#include "IEEE1588Time.h"
#include "QueueTemplate.h"
#include "IEEE1588.h"
#include "PtpPort.h"
#include "VisibleMaster.h"

#include "MqxInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	Bool 							interruptRequired;  // the processor must be interrupted when the packet has been transmitted
	uint8							networkTimestamper; // the network ts that will trigger the interrupt
	NetworkProtocolSubInterface*	networkSubInterface;
	PCB_PTR 						pcbPtr;				//null if already sent for transmission
	EthernetAddress					ethernetAddress;  // must be valid
	uint16							etherType;

} TransmitRecord;


typedef struct
{
	PtpPort*						ptr;
	Bool							unicast;
	TransmissionProtocolAddress		address;
} InformPtpPortRecord;

typedef struct
{
	VisibleMaster* 					ptr;
} InformVisibleMasterRecord;

typedef struct
{
	NetworkProtocolSubInterface* ptr;
	IEEE1588Domain					domain;
	uint8							destinationPortIdBytes[V2_PORT_ID_SIZE];
} InformNPIRecord; //network protocol interface

typedef struct
{
	//needed when TransmitRecord.interruptRequired is true
	MessageType 					messageType;
	IEEE1588SequenceNumber 			sequenceNumber;

	union
	{
		InformPtpPortRecord				ptpPort;		//if messageType == syncMsg, pathDelayRequestMsg
		InformVisibleMasterRecord		visibleMaster;	//if messageType == delayRequestMsg;
		InformNPIRecord					networkProtocolInterface; // if mesageType == pathDelayResponseMsg
	} u;
} InformRecord;


typedef struct
{
	TransmitRecord		transmit;
	InformRecord 		inform;
} EventMessageTransmitRecord;


QueueTemplateDeclaration(EventMessageTransmitRecord);

typedef struct
{
	EventMessageTransmitRecordQueue queue;
	uint16							transmitNotificationTicksToTimeOut; // non zero means we are waiting for an interrupt
	uint16							ticksUntilInterruptMesssageAllowed;  // avoid a non-interrupt message causing an interrupt
} EventMessageTransmitQueue;

void InitialiseEventMessageTransmitQueue(EventMessageTransmitQueue* emtq, uint16 size);
void ResetEventMessageTransmitQueue(EventMessageTransmitQueue* emtq);
void TickEventMessageTransmitQueue(EventMessageTransmitQueue* emtq);
void EventPacketTransmitted(EventMessageTransmitQueue* emtq, IEEE1588Timestamp const* transmitTimestamp);

/* PRE: Interrupts have been disabled before calling */
#define MessageTransmitQueueIsEmpty(emtq) QueueIsEmpty(&(emtq)->queue)

/* PRE: Interrupts have been disabled before calling?????? */
#define MessageTransmitQueueIsFull(emtq) QueueIsFull(&(emtq)->queue)
#define MessageTransmitQueueIncrementFullCount(emtq) QueueIncrementFullCount(&(emtq)->queue)

#define HeadOfMessageTransmitQueue(emtq) HeadOfQueue(&(emtq)->queue)

/* PRE: Interrupts have been disabled before calling */
#define RemoveHeadOfMessageTransmitQueue(emtq) RemoveHeadOfQueue(&(emtq)->queue)

#define TailOfMessageTransmitQueue(emtq) TailOfQueue(&(emtq)->queue)

/* PRE: Interrupts have been disabled before calling */
#define AddToTailOfMessageTransmitQueue(emtq) AddToTailOfQueue(&(emtq)->queue)

/* PRE: Interrupts have been disabled before calling */
#define MessageTransmitQueueReadyToTransmit(emtq)(!MessageTransmitQueueIsEmpty(emtq) && HeadOfMessageTransmitQueue(emtq)->transmit.pcbPtr != NULL)

/* PRE: Interrupts have been disabled before calling */
#define MessageTransmitQueueWaitingForInterrupt(emtq) (!MessageTransmitQueueIsEmpty(emtq) && HeadOfMessageTransmitQueue(emtq)->transmit.pcbPtr == NULL)

void TransmitFromHeadOfEventMessageQueue(EventMessageTransmitQueue* emtq);	//transmits message at head of queue - MessageTransmitQueueIsEmpty() must be false

#ifdef __cplusplus
}
#endif

#endif
