#ifndef IEEE1588MESSAGES_H
#define IEEE1588MESSAGES_H


#include "IEEE1588.h"
#include "IEEE1588Time.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
  * \name IEEE15888 Message Constants.
  *	The constants used to define the IEEE1588 message structures.
  */
#define V1_SYNC_MESSAGE_LENGTH 124

#define V2_MESSAGE_HEADER_LENGTH 34
#define V2_MESSAGE_TYPE_OFFSET 0
#define V2_VERSION_OFFSET 1 //LS nibble only
#define V2_MESSAGE_LENGTH_OFFSET 2
#define V2_SOURCE_PORT_OFFSET 20
#define V2_SOURCE_PORT_NUMBER_OFFSET (V2_SOURCE_PORT_OFFSET + 8)
#define V2_TIME_OFFSET V2_MESSAGE_HEADER_LENGTH
#define V2_TIMESTAMP_OFFSET (V2_TIME_OFFSET + 2)
#define V2_TIME_LENGTH 10
#define V2_FULL_SECONDS_LENGTH 6
#define V2_NANOSECONDS_LENGTH 4
#define V2_DOMAIN_OFFSET 4
#define V2_FLAG_OFFSET 6
#define V2_FLAG_SIZE 2
#define V2_PORT_ID_SIZE 10
#define V2_PORT_ID_OFFSET 20
#define V2_PORT_ID_PORT_NUMBER_OFFSET 28
#define V2_CORRECTION_FIELD_OFFSET 8
#define V2_CORRECTION_FIELD_SIZE 8
#define V2_CORRECTION_FIELD_SUB_NS_FIELD_SIZE 2
#define V2_SEQUENCE_NUMBER_OFFSET 30
#define V2_LOG_MESSAGE_PERIOD_OFFSET 33
#define V2_SEQUENCE_NUMBER_SIZE 2
#define V2_TIMING_MESSAGE_LENGTH 44
#define V2_DELAY_REQUEST_LENGTH V2_TIMING_MESSAGE_LENGTH
#define V2_DELAY_RESPONSE_LENGTH 54
#define V2_ANNOUNCE_MESSAGE_LENGTH 64
#define V2_LONG_TIMING_MESSAGE_LENGTH 54 // delay response, all path delay messages
#define V2_DELAY_RESPONSE_DEST_PORT_ID_OFFSET 44
#define V2_UDP6_WHITE_SPACE 2 //2 bytes at end of UDP packet when carried over IPv6, to allow checksum to be corrected
#define LEAST_SIGNIFICANT_SECONDS_BYTE_OFFSET_INSIDE_1588TIME (2 + sizeof(uint32) - 1) // epoch holds 2 bytes
#define NANOSECOND_OFFSET_INSIDE_1588TIME 6
#define V2_DREQ_MESSAGE_LENGTH V1_SYNC_MESSAGE_LENGTH + 10

#define V2_SIGNALLING_HEADER_LENGTH (V2_MESSAGE_HEADER_LENGTH+V2_PORT_ID_SIZE)

/* Internally used value to signal that the correction field is bigger than ToPSync can handle
 * It is NOT the same as the out of range value in the IEEE1588 spec
 */
#define CORRECTION_FIELD_OUT_OF_RANGE	((sint32)0x7FFFFFFF)

//flag masks
#define V2_UNICAST_MASK 0x04

// UDP transport specific masks
#define TRANSPORT_SPECIFIC_MASK 0xF0
#define V2_UDP_padForV1HardwareCompatibilityUDP_MASK 0x10


typedef enum {event, general, numberOfMessageClasses} MessageClass;


typedef struct
{
	Bool	alternateMaster:1;	//only set on Announce, Sync and Follow-up messages
	Bool	twoStep:1;
	Bool	sentToUnicastAddress:1; // sent to a unicast address
	uint8	:2;
	uint8	profileSpecific:2;
	uint8	:1;

	Bool	leapSecond61:1;
	Bool	leapSecond59:1;
	Bool	utcOffsetValid:1;
	Bool	tai:1;  // The time is TAI epoch
	Bool	timeTraceable:1; // to a known reference
	Bool	frequencyTraceable:1; // to a known reference
} MessageFlags;  // pattern matches transmitted flag format

typedef struct
{
	PortId					source;
	IEEE1588SequenceNumber	sequenceNumber;
	sint32					timestampCorrection;  // in ns
	sint8					logMessagePeriod;
	MessageFlags			flags;

} MessageHeader;


typedef struct
{
	MessageHeader			header;

	UTCOffset				utcOffset;
	ReferenceClock			grandmaster;
} AnnounceMessage;

typedef struct
{
	MessageHeader			header;
	IEEE1588Time			originTime;
} TimingMessage;

typedef struct
{
	MessageHeader			header;
	IEEE1588Time			originTime;
	PortId					destination;
} DelayRequestMessage;

typedef struct
{
	MessageHeader			header;
	IEEE1588Time			time;
	PortId					requestingPort;

} LongTimingMessage; //DelayResponse or Path Delay 


#define ReadMessageClass(messageText) (((messageText)[V2_MESSAGE_TYPE_OFFSET] & 0x08) == 0 ? event : general)
Bool MustBeFromAKnownMaster(MessageType messageType);
Bool MayBeFromAKnownMaster(MessageType messageType);
#define V2MessageWasSentToUnicastAddress(data) ((data)[V2_FLAG_OFFSET] & 0x04)
#define V2MessageWasSentToMulticastAddress(data) (V2MessageWasSentToUnicastAddress(data) ? FALSE:TRUE)

char const* MessageText(MessageType messageType);

extern const MessageType messageTxByteToMessageTypeTable[]; //value is messageType.  Index is MessageType value of 1588 message
#define ReadMessageTypeFromTransmittedByte(transmittedByte) messageTxByteToMessageTypeTable[(transmittedByte) & 0xF]
#define ReadMessageType(message) ReadMessageTypeFromTransmittedByte(message[V2_MESSAGE_TYPE_OFFSET])

extern const uint8 messageTypeToTxByteTable[]; // value is transitted message type byte (MessageType value of 1588 message). Index is messageType
#define GetMessageTypeTransmitByte(messageType) messageTypeToTxByteTable[messageType]


#define ReadSequenceNumber(message) ((IEEE1588SequenceNumber)((((uint16)(message)[V2_SEQUENCE_NUMBER_OFFSET]) << 8) + message[V2_SEQUENCE_NUMBER_OFFSET+1]))
#define ReadPtpMessageLength(message) ((uint16)((((uint16)(message)[V2_MESSAGE_LENGTH_OFFSET]) << 8) + (message)[V2_MESSAGE_LENGTH_OFFSET+1]))


#ifdef __cplusplus
}
#endif

#endif

