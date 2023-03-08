#ifndef SOCKET_CONTROLLER_PORT_ARRAY_H
#define SOCKET_CONTROLLER_PORT_ARRAY_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "InitialSystemConfiguration.h"		// NUMBER_OF_PHYSICAL_PORTS
#include "NetworkInterfaces.h"				// NUMBER_OF_IP_PROTOCOLS

typedef struct
{
	TransmissionProtocolAddress ipAddress;	//0 == invalid
	Bool		changed;
} SocketPortRecord; 

typedef struct
{
	SocketPortRecord store[NUMBER_OF_PHYSICAL_PORTS][NUMBER_OF_VIRTUAL_PORTS] \
						  [NUMBER_OF_IP_ADDRESSES_PER_INTERFACE] \
						  [NUMBER_OF_IP_PROTOCOLS];  //[records]
	uint16 			records;
	Bool			changed; //one or more records has changed		   
} SocketPortArray;

#define NUMBER_OF_SOCKET_PORT_RECORDS \
	(NUMBER_OF_PHYSICAL_PORTS * NUMBER_OF_VIRTUAL_PORTS * \
	 NUMBER_OF_IP_ADDRESSES_PER_INTERFACE * NUMBER_OF_IP_PROTOCOLS)

// PortArray functions
// only used by SocketController
void InitialiseSocketPortArray(SocketPortArray* array);
void ResetSocketPortArray(SocketPortArray* array);
void SocketPortStateHasChanged(SocketPortArray* array,
	const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex,
	TransmissionProtocol protocol, TransmissionProtocolAddress *address);

Bool SocketPortFindMHomeIndexFromAddress(SocketPortArray* array,
	const NetworkInterfaceId *networkInterfaceId,
	TransmissionProtocolAddress *ipAddress, uint32 *mHomeIndex);

TransmissionProtocolAddress *SocketPortGetAddress(SocketPortArray* array,
	const NetworkInterfaceId *networkInterfaceId,
	uint32 mHomeIndex,
	TransmissionProtocol protocol);

#define PortIsOperational(array, networkInterfaceId, mHomeIndex, protocol) \
	(IsValidTPA(SocketPortGetAddress((array),(networkInterfaceId), \
							   (mHomeIndex),(protocol))))
#define PortArrayHasChanged(array) ((array)->changed)
#define PortArraySize(array) ((array)->records)

#define PortRecordHasChanged(array,id) ((array)->store[id].changed)
#endif
