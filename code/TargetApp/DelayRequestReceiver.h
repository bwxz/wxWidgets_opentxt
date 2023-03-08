/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this
 * file is owned by Semtech Corporation (Semtech). This is an
 * unpublished work.  The content of this file must be used only for
 * the purpose for which it was supplied by Semtech or its
 * distributors. The content  of this file must not be copied or
 * disclosed unless authorised in writing by Semtech.
 */
#ifndef DELAY_REQUEST_RECEIVER_H
#define DELAY_REQUEST_RECEIVER_H

#include "General.h"
#include "MessageReceiveQueue.h"

#include "IEEE1588Time.h"

#include "MqxInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint32 noTemplate;
	uint32 unicastNotEnabled;
	uint32 multicastNotEnabled;
	uint32 notMaster;
	uint32 ethernetNotEnabled;
	uint32 UDP4NotEnabled;
	uint32 UDP6NotEnabled;
	uint32 unknownEthertype;
	uint32 grantRequestError;
} DelayRequestReceiverStatistics;

typedef struct
{
	MessageReceiveQueue								receiveQueue;

	struct PtpPortStruct const*						ptpPort;
	uint8											ptpPortNumber; // assumed to be less than 255
	ClockId											clockId;
	struct NetworkProtocolSubInterfaceStruct*		networkProtocolSubInterface;
	struct PassiveMessageRateGrantorStruct*			delayResponseMessageController;  // cannot be NULL if networkProtocolInterface is not NULL
	uint8											domain;
	uint32											delayRequestReceptionEnabled;
	Bool											multicastEnabled;
	Bool											unicastEnabled;
	LogMessagePeriod								multicastDelayResponseLogPeriod;
	TransmissionProtocol							receivedProtocol;
	Bool											isMaster;
	DelayRequestReceiverStatistics					statistics;
	Bool											alwaysRespondToUnicastDelays;
} DelayRequestReceiver;

void InitialiseDelayRequestReceiver(DelayRequestReceiver* drmr, uint16 queueSize);
void DelayRequestReceiverAssignPtpPort(DelayRequestReceiver* drmr, struct PtpPortStruct const* ptpPort);
void ResetDelayRequestReceiverByClockId(DelayRequestReceiver* drmr, uint8 clockId);
void EnableDelayRequestStackBypassOperation(struct PtpPortStruct const* ptpPort);

#define AssignDelayRequestReceiverToClockPath(drmr,clockPath) AssignMessageReceiveQueueToClockPath(&(drmr)->receiveQueue,clockPath)

void DelayRequestMessageReceived(PCB_PTR pcbPtr, uint32 receiveTimeNanoseconds,
		unsigned char* payloadStart, uint8 portNumber, uint32 virtualPortNumber);

void DelayRequestMessageReceiverSlowTick(DelayRequestReceiver* drmr); // called when DataMutex is held

void ReactToReceivedDelayRequestMessages(DelayRequestReceiver* drmr, uint16 maxNumber);

#ifdef __cplusplus
}
#endif


#endif

