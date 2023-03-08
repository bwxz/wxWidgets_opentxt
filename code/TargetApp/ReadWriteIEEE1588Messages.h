#ifndef READ_WRITE_IEEE1588_MESSAGES_H
#define READ_WRITE_IEEE1588_MESSAGES_H

#ifdef __cplusplus
extern "C" {
using namespace Semtech;
#endif


#include "General.h"
#include "IEEE1588Messages.h"

//General
#define ReadMessageVersion(data) ((data)[1] & 0x0F)
IEEE1588Domain ReadMessageDomain(uint8 const data[]);
void ReadSourcePortFromMessage(uint8 const data[], PortId* sourcePort);
uint16 GetExpectedMessageLength(MessageType messageType);
uint32 FindDomainOfIEEE1588Message(uint8 const data[],uint16 length);
void ReadIEEE1588Timestamp(uint8 const ** data, IEEE1588Timestamp* timestamp);
void WriteIEEE1588Timestamp(uint8 ** data, IEEE1588Timestamp const* timestamp);
void ReadIEEE1588Time(uint8 const ** data, IEEE1588Time* time);
void WriteIEEE1588Time(uint8 ** data, IEEE1588Time const* time);
void WriteIEEE1588TimeZeroNs(uint8 ** data, IEEE1588Time const* time);

/* Reads the correction field of IEE1588 messages
 * NOTE truncates down to sint32 from sint64 and will return 0 if correction
 * is out of range of sint32
 * TODO Raise exception for "OutOfRange" condition
 */
sint32 ReadCorrectionField(uint8 const** data);
void WriteFullCorrectionField(uint8 **data, sint64 correction);
sint64 ReadFullCorrectionField(uint8 const** data);

void ReadAnnounceMessage(uint8 const ** data, AnnounceMessage* message); 
void ReadTimingMessage(uint8 const ** data, TimingMessage* message); 
void ReadLongTimingMessage(uint8 const ** data, LongTimingMessage* message);


OffsetScaledLogVariance ReadV1LogVariance(uint8 const ** data);
void WriteV1LogVariance(uint8 ** data, OffsetScaledLogVariance variance);
void ReadV1ClockId(uint8 const ** data, ClockAccuracy* clockAccuracy, TimeSource* timeSource);
void WriteV1ClockId(uint8 ** data, ClockAccuracy clockAccuracy);
IEEE1588Domain ReadV1MessageDomain(uint8 const data[]);
void WriteV1MessageDomain(uint8** data, IEEE1588Domain domain);

ClockStratum ReadV1ClockStratum(uint8 const** data);
void WriteV1ClockStratum(uint8** data, ClockStratum stratum);


void ReadIEEE1588MessageHeader(uint8 const ** data, MessageHeader* message);

void WriteIEEE1588MessageHeader(uint8 ** data, PortId const* sourcePort, 
				MessageFlags messageFlags, MessageType messageType, 
				LogMessagePeriod logMessagePeriod,
				IEEE1588Domain domain, IEEE1588SequenceNumber sequenceNumber,
				uint32 correction, 
				Bool unicast, Bool allowAlternateMasterFlagToBeSet, Bool allowTwoStepFlagToBeSet);

		

uint16 GetExpectedMessageLength(MessageType messageType);
void UpdateV2MessageLength(uint8 message[], uint16 messageLength);
uint16 ReadV2MessageLength(uint8 const message[]);


void WriteV2TimeSource(uint8** data, TimeSource timeSource);
#define ReadV1OrV2SequenceNumber(msg) \
	(((IEEE1588SequenceNumber) msg[V2_SEQUENCE_NUMBER_OFFSET]) << 8 |\
	 ((IEEE1588SequenceNumber) msg[V2_SEQUENCE_NUMBER_OFFSET+1]))

#define WriteV1OrV2SequenceNumber(msg, sn) \
	((msg)[V2_SEQUENCE_NUMBER_OFFSET] = (uint8)((sn) >> 8), (msg)[V2_SEQUENCE_NUMBER_OFFSET+1] = (uint8) (sn))
#define WriteV2LogMessagePeriod(msg, lmp)  ((msg)[V2_LOG_MESSAGE_PERIOD_OFFSET] = (uint8) (lmp))

sint64 PeakIEEE1588MessageHeaderCorrectionField(uint8 const *const data);
void PokeIEEE1588MessageHeaderCorrectionField(uint8 *data, sint64 cf);

#ifdef __cplusplus
}
#endif

#endif

