#ifndef MESSAGE_RECEIVE_QUEUE_H
#define MESSAGE_RECEIVE_QUEUE_H

#include "General.h"
#include "IEEE1588Time.h"
#include "QueueTemplate.h"
#include "MqxInterface.h"


typedef struct
{
	PCB_PTR pcbPtr;
	uint8 const* ptpMessage;
	IEEE1588Time rxTime;
	uint32 changeCount;   /* tracks when messages in the queue are lagging changes (e.g. phase jumps) */
	TransmissionProtocol protocol;
	NetworkInterfaceId networkInterfaceId; /* the network interface on which the message arrived */
	uint8 isMulticast;		/* set to 1 if multicast */
} MessageReceiveRecord;

QueueTemplateDeclaration(MessageReceiveRecord);


typedef struct
{
	MessageReceiveRecordQueue	queue;
	IEEE1588Time 				time;

} MessageReceiveQueue;

void MessageReceiveQueueUpdateTime(MessageReceiveQueue* mrq,IEEE1588Time* timeNow); // call when dataMutex is not held

void InitialiseMessageReceiveQueue(MessageReceiveQueue* mrq, uint16 size);
void ResetMessageReceiveQueue(MessageReceiveQueue* queue);


#define MessageReceiveQueueIsEmpty(mrq) QueueIsEmpty(&(mrq)->queue)
#define MessageReceiveQueueIsFull(mrq) QueueIsFull(&(mrq)->queue)

#define HeadOfMessageReceiveQueue(mrq) HeadOfQueue(&(mrq)->queue)
#define RemoveHeadOfMessageReceiveQueue(mrq) RemoveHeadOfQueue(&(mrq)->queue)
// MessageReceiveQueueIsEmpty must be false before RemoveHeadOfMessageReceiveQueue is called

#define TailOfMessageReceiveQueue(mrq) TailOfQueue(&(mrq)->queue)
#define AddToTailOfMessageReceiveQueue(mrq) AddToTailOfQueue(&(mrq)->queue)
// MessageReceiveQueueIsFull must be false before AddReceivedMessageToQueue is called

#define GetQTime(mrq) ((mrq)->time)

#endif
