#ifndef DELAYREPLACEMENTMESSAGES_H
#define DELAYREPLACEMENTMESSAGES_H

/*
 * DelayMessages.h
 *
 *  Created on: 10 Oct 2011
 *      Author: ahome
 */

#include "General.h"
#include "IEEE1588Time.h"
#include "ToPSyncControlDriverMessages.h"

typedef struct
{
	ToPSyncDelayMessageType	messageType;
	uint8					port; 	//port through which master messages sent/received - normally fixed
	PortId					id;		//ID of port on source sending messages
} DelayMessageHeader;

typedef struct
{
	DelayMessageHeader 	header;
	IEEE1588Time 					timestampA;
	IEEE1588Time 					timestampB;
	sint32 							timestampCorrection;
	IEEE1588SequenceNumber 			sequenceNumber;
} DelayTimingMessage;

typedef struct
{
	DelayMessageHeader 	header;
	LogMessagePeriod 				logT1T2MessagePeriod;
	LogMessagePeriod 				logT3T4MessagePeriod;
} DelayInformationMessage;

void ReadDelayMessageHeader(uint8 const* data,DelayMessageHeader* header);
uint8 ReadPtpPortIdFromDelayMessage(uint8 const* data);
void ReadSourcePortFromDelayMessage(uint8 const* data, PortId* sourcePortIdentity);
ToPSyncDelayMessageType ReadMessageTypeFromDelayMessage(uint8 const* data);
void ReadDelayTimingMessage(uint8 const* data,DelayTimingMessage* message);
void ReadDelayInformationMessage(uint8 const* data,DelayInformationMessage* message);


#endif /* DELAYREPLACEMENTMESSAGES_H */
