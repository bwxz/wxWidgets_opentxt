#ifndef SOCKET_RECORD_H
#define SOCKET_RECORD_H

#include "Socket.h"
#include "General.h"
#include "TransmissionProtocol.h"
#include "NetworkInterfaces.h"

typedef struct
{
	SocketHandle	handle;	  // == NO_SOCKET when non operational
	Bool			valid;		// the record is valid
	NetworkInterfaceId networkInterfaceId;
	uint32			mHomeIndex;
	uint16			udpPort;
	uint8			protocol;
	TransmissionProtocolAddress	multicastGroup0;  // Null is none
	TransmissionProtocolAddress	multicastGroup1;  // Null is none
	Bool			messagesTimestamped;
	Bool			attached;	// attached to message receive process;
	Bool			deleteRequested;	// the owner has requested that the socket be deleted

	void (*clientDataRxFunctionPtr) (void* clientData,
		EnhancedTransmissionProtocolAddress const* sourceAddress,
		uint8 const data[], uint16 dataLength);	  //function called when data for client is received

	void (*socketStateChangeFunctionPtr) (void* clientData,
				SocketHandle socketHandle, uint16 udpPort);

	void* 			clientData;  // value of clientData parameter of clientDataRxFunctionPtr function
	uint8			tos;
} SocketRecord;



#endif
