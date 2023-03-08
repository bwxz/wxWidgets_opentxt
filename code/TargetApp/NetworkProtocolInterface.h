#ifndef NETWORK_PROTOCOL_INTERFACE_H
#define NETWORK_PROTOCOL_INTERFACE_H

#include "TwoLevelAddress.h"
#include "IEEE1588Time.h"
#include "IEEE1588Messages.h"
#include "Socket.h"

#include "MqxInterface.h"

#include "ApplicationInfrastructureInterface.h"
#include "ToPSyncInterfaceTypes.h"		// NUMBER_OF_IPV4_ADDRESSES_PER_INTERFAC


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Each interface can have multiple addresses and each address can be bound to a
 * PTP port. The subinterface stores fields associated with each of these addresses.
 */
typedef struct NetworkProtocolSubInterfaceStruct
{
	Bool									configured;
	Bool									enabled;
	struct NetworkProtocolInterfaceStruct*	networkInterface;
	uint32									mHomeIndex;
	struct PtpPortStruct**					ptpPortArray;
	struct PtpPortStruct**					endPtpPortArray; // one past end of array
	Bool									serviceLayerConfigured;
	Bool									serviceLayerIsOperational;
	Bool									pathDelayResponseEnabled;
	Bool									pathDelayRequestEnabled;
	SocketHandle							socketHandle[numberOfMessageClasses];  //udp only
	uint32									pathDelayRequestMessageCount;
											//NO_SOCKET indicates transport is unavailable
} NetworkProtocolSubInterface;

typedef struct NetworkProtocolInterfaceStruct
{
	//set at initialisation
	struct PhysicalPortStruct*		physicalPort;
	NetworkInterfaceId			    networkInterfaceId;
	TransmissionProtocol			transmissionProtocol;

	NetworkProtocolSubInterface 	networkProtocolSubInterfaceArray[NUMBER_OF_IP_ADDRESSES_PER_INTERFACE];

	TwoLevelAddress					multicastAddress;
	TwoLevelAddress					pathDelayAddress;
	ClockId							pathDelayClockId;	// ClockId for Path Delay *Responses* -
														// Path Delay Requests have id of sending PTP port

	//Configured
	uint16							clientProtocolIdentifier[numberOfMessageClasses];
									// in UDP this is port number
									// in Ethernet this is Ethertype

	Bool							configured;
	Bool							udpChecksumForAllPtpMsgsEnabled;	// udp only
} NetworkProtocolInterface;

// Enumerations identifying parameters.  A subset of the enumerations is also used in NetworkProtocolInterfaceParameterHost, and must use the same values
typedef enum
{
	setResponseToPathDelayRequests = 0,
	udpChecksumForAllPtpMsgs
} NetworkProtocolInterfaceParameter;

void InitialiseNetworkProtocolInterface(NetworkProtocolInterface* protoIf,
				uint maxPtpPorts,
				ClockId pathDelayClockId);

Bool FindNetworkProtocolInterfaceIndex(NetworkInterfaceId *networkInterfaceId,
								  TransmissionProtocol protocol,
								  uint32 *npiIndex);

NetworkProtocolInterface *FindNetworkProtocolInterface(NetworkInterfaceId *networkInterfaceId,
													   TransmissionProtocol transmissionProtocol);

Bool FindNetworkProtocolMhomeIndexFromAddress(NetworkProtocolInterface* protoIf,
											  uint8 const *addressPtr,
											  uint32 *mHomeIndex);

Bool GetNextNetworkProtocolInterfaceIndex(uint32 *npiIndex);

void ConfigureNetworkProtocolInterface(NetworkProtocolInterface* protoIf,
				NetworkInterfaceId*	networkInterfaceId,
				TransmissionProtocol transmissionProtocol,
				uint16 eventClientProtocolIdentifier,
				uint16 generalClientProtocolIdentifier,
				TransmissionProtocolAddress const* myMulticastGroup,
				TransmissionProtocolAddress const* pathDelayMulticastAddress);

void DeconfigureNetworkProtocolSubInterface(NetworkProtocolSubInterface* protoIf);

NetworkProtocolSubInterface *FindOrConfigureNPSI(
		NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex,
		TransmissionProtocol transmissionProtocol);

Bool RegisterPtpPortNPSI(NetworkProtocolSubInterface* protoSubIf, struct PtpPortStruct* port);
// returns TRUE on success

void DeregisterPtpPortNPSI(NetworkProtocolSubInterface* protoSubIf, struct PtpPortStruct* port);

void MessageReceivedNPI(NetworkProtocolInterface* protoIf,
						 TwoLevelAddress * sourceAddress,
						 uint8 const data[], uint16 length,
						 IEEE1588Time const* receiveTime,
						 uint32 changeCount, uint8 isMulticast,
						 uint32 mHomeIndex);

void TransmitGeneralMessageNPSI(NetworkProtocolSubInterface* protoSubIf,
		TwoLevelAddress * destinationAddress, uint8 ipTTL, //(destinationAddress may be NULL)
		uint8 message[], uint16 length);

void TransmitGeneralMessageNPSI_PCB(NetworkProtocolSubInterface* protoSubIf,
		TwoLevelAddress * destinationAddress, //(must not be NULL)
		PCB_PTR pcb);

void PathDelayResponseMessageTransmitedFromNPSI(NetworkProtocolSubInterface* protoIf,
					IEEE1588Timestamp const* transmitTimestamp, IEEE1588SequenceNumber sequenceNumber, IEEE1588Domain domain, uint8 const destinationPortIdBytes[]);

void EnableNPI(NetworkProtocolInterface* protoIf, Bool enable);
void EnableNPSI(NetworkProtocolSubInterface* protoSubIf, Bool enable);

#define NPSIServiceLayerConfigured(protoSubIf) ((protoSubIf)->serviceLayerConfigured)
#define NPSIFailed(protoSubIf) ((protoSubIf)->serviceLayerIsOperational = FALSE)
#define NPSIRecovered(protoSubIf) ((protoSubIf)->serviceLayerIsOperational = TRUE)
#define NPSIServiceLayerOperational(protoSubIf) ((protoSubIf)->serviceLayerIsOperational)
#define NPSIIsOperational(protoSubIf) (NPSIServiceLayerOperational(protoSubIf) && (protoSubIf)->enabled)
#define NPIProtocol(protoIf) ((protoIf)->transmissionProtocol)

uint16 NPIGetProtocolOverheadBytes(NetworkProtocolInterface const* protoIf);

uint16 NumberOfRegisteredPtpPortsNPSI(NetworkProtocolSubInterface const* protoIf);

void EthernetServiceStateChangeNPSI(NetworkProtocolSubInterface* protoIf, Bool start); //FALSE means failed

uint8 GetMicroFilterId(MessageType messageType,TransmissionProtocol protocol, uint8 portIndex);
void BuildPacketFilterNetProtocolIf(NetworkProtocolInterface const* protoIf,uint8 microFilterId,
		Bool transmit,uint32* payloadSearchTerms,uint32 numberOfPayloadSearchTerms,ClockId clockId, Bool hwUDPChecksumEnabled);
void DisablePacketFilterNetProtocolIf(NetworkProtocolInterface const* protoIf,Bool transmit,uint8 microFilterId);

//Function pointer functions
void MessageReceivedFromSocketNPSI(void* protoSubIf,
		EnhancedTransmissionProtocolAddress const* sourceAddress,
		uint8 const data[], uint16 dataLength);

void UDPServiceStateChangeNPSI(void* protoSubIf,
		SocketHandle socketHandle, uint16 udpPort);

Bool ConfigurePathDelayRequestNetProtocolSubIf(NetworkProtocolSubInterface* protoSubIf,ClockId clockId);
void DeconfigurePathDelayRequestNetProtocolSubIf(NetworkProtocolSubInterface* protoIf);

Bool ConfigurePathDelayResponseNetProtocolSubIf(NetworkProtocolSubInterface* protoSubIf,ClockId clockId);
void DeconfigurePathDelayResponseNetProtocolSubIf(NetworkProtocolSubInterface* protoSubIf);

#ifdef __cplusplus
}
#endif

#endif

