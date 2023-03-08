#ifndef SOCKET_CONTROLLER_H
#define SOCKET_CONTROLLER_H

#include "SocketRecord.h"
#include "SocketControllerArray.h"
#include "SocketControllerPortArray.h"
#include "General.h"
#include "ClockPath.h"
#include "Socket.h"

#include <mqx.h>
#include <mutex.h>


typedef struct
{
	SocketPortArray portArray; 	//[numberOfPhyPorts]

	SocketArray  	writable;  // can be updated by the program
	SocketArray  	active;    // used by socket function
	SocketHandle*	activeHandleArray;  //copied from active array
	Bool 			writableArrayChanged; // true if the writable array has been edited
	uint16			numberOfOpenSockets;

	MUTEX_STRUCT 	mutex;
	// writable and writableArrayChanged can only be used when mutex is owned

} SocketController;

void InitialiseSocketController(SocketController* controller, uint8 maxSockets, uint8 numberOfPhyPorts);
void ResetSocketController(SocketController* controller);

SocketHandle SocketControllerOpenSocket(SocketController* controller, uint16 udpPort, const NetworkInterfaceId *networkInterfaceId,
			uint32 mHomeIndex, uint8 protocol,
			Bool messagesTimestamped, TransmissionProtocolAddress *multicastGroup0,
			TransmissionProtocolAddress *multicastGroup1,  //Null == no multicast
			void (*clientDataRxFunctionPtr) (void* clientData,
				EnhancedTransmissionProtocolAddress const* sourceAddress,
				uint8 const data[], uint16 dataLength),	  //function called when data for client is received

			void (*socketStateChangeFunctionPtr) (void* clientData,
				SocketHandle socketHandle, uint16 udpPort),

			void* clientData,  // value of clientData parameter of clientDataRxFunctionPtr function
			uint8 tos
			);
// returns NO_SOCKET on error

void SocketControllerPhyPortStateHasChanged(SocketController* controller, const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex,
											TransmissionProtocol protocol, TransmissionProtocolAddress *address);  //address == 0 indicates address lost
void SocketControllerCloseSocket(SocketController* controller, uint16 udpPort,
								 const NetworkInterfaceId *networkInterfaceId,
								 uint32 mHomeIndex,
								 TransmissionProtocol protocol);
void ReceiveMessageFromSockets(SocketController* controller);  // receives a message from the sockets and calls handler function
void SocketControllerCheckForConfigurationUpdate(SocketController* controller); // synchronises SocketArray with RTCS state
Bool SocketControllerPortArrayHasChanged(SocketController* controller);

#endif

