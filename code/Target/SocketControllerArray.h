#ifndef SOCKET_CONTROLLER_ARRAY_H
#define SOCKET_CONTROLLER_ARRAY_H

#include "SocketRecord.h"
#include "General.h"

typedef struct
{
	uint16 maxRecords;
	uint16 activeRecords;

	SocketRecord* store;	//[maxRecords]
} SocketArray;


void InitialiseSocketArray(SocketArray* array, uint16 records);
void ResetSocketArray(SocketArray* array);
SocketRecord* AddSocketRecordToArray(SocketArray* array,
			SocketHandle handle, uint16 udpPort, const NetworkInterfaceId *networkInterfaceId,
			uint32 mHomeIndex, uint8 protocol,
			Bool messagesTimestamped, TransmissionProtocolAddress *multicastGroup0,
			TransmissionProtocolAddress *multicastGroup1,
			void (*clientDataRxFunctionPtr) (void* clientData,
				EnhancedTransmissionProtocolAddress const* sourceAddress,
				uint8 const data[], uint16 dataLength),
			void (*socketStateChangeFunctionPtr) (void* clientData,
				SocketHandle socketHandle, uint16 udpPort),
			void* clientData, uint8 tos);


void SocketArraySetPortOperational(SocketArray* array,
								   const NetworkInterfaceId *networkInterfaceId,
								   uint32 mHomeIndex,
								   TransmissionProtocolAddress *tpa);
_Inline SocketRecord* FindSocketRecordByHandle(SocketArray* array, SocketHandle handle); // return NULL if not found
SocketRecord* FindSocketRecordByPort(SocketArray* array, int16 udpPort,
									 const NetworkInterfaceId *networkInterfaceId,
									 uint32 mHomeIndex,
									 TransmissionProtocol protocol); // return NULL if not found
void EraseEmptyRecordsFromArray(SocketArray* array);

#endif
