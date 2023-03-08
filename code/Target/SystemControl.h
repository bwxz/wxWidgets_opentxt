#ifndef SYSTEM_CONTROL_H
#define SYSTEM_CONTROL_H

#include "ToPSyncInterfaceTypes.h"
#include "InitialSystemConfigurationCommon.h"
#include "ApplicationInfrastructureInterface.h"
#include "NetworkInterfaces.h"
#include "NetworkProtocolInterface.h"
#include "PhysicalPort.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Flag that indicates a system reset. */
extern Bool resetSystemFlag;
extern uint8 activePhysicalPort; // initialised by StartupSystem read by GetPhysicalPort()

extern uint8 networkControlInterfaceProtocol;	/* Control task protocol can be either ipv4 of ipv6 */


#ifdef _ARC
	extern ToPSyncSystemState systemStateGlobal;
	#define GetSystemState()  (systemStateGlobal)
#else
	ToPSyncSystemState GetSystemState(void);
#endif

void StartupSystem(void);
void SetSystemState(ToPSyncSystemState newSystemState);
#define GetPhysicalPort() (activePhysicalPort)
void ResetIpInterface(const NetworkInterfaceId *networkInterfaceId,
					  uint32 mHomeIndex, TransmissionProtocol protocol);

void GetPtpMulticastAddress(TransmissionProtocol transmissionProtocol,
				  	  	    TransmissionProtocolAddress *multicastGroup,
				  	  	    TransmissionProtocolAddress *pathDelayMulticastAddress);

void GetPtpClientProtocolNumber(TransmissionProtocol transmissionProtocol,
								uint16 *eventClientProtocolNumber,
								uint16 *generalClientProtocolNumber);

/* Configured Node ID access functions. */
void InitialiseConfiguredNodeId(void);
void SetConfiguredNodeId(const NodeId nodeId);
NodeId GetConfiguredNodeId(void);

uint32 GetRandomSeed(void);

void ConvertEthernetMacAddressToByteArray(EthernetMacAddress const* input, uint8 output[]);
void ConvertEthernetAddressToEthernetMacAddress(EthernetAddress ethernetAddress, EthernetMacAddress *ethernetMacAddress);

void ConvertInitialIPPacketInterfaceConfiguration(
		Ipv4PacketInterfaceConfiguration* out,
		InitialIpPacketInterfaceConfiguration const* in);
void SetToPSyncPartNumber(void);
Bool IsToPSyncGenerationTS1(void);
Bool MacAddressIsOkToChangeState(uint8 newState);


void SetManagementServerAddress(const uint8 *data, uint8 dataLen);

ToPSyncPartNumber GetToPSyncPartNumber(void);

#ifdef __cplusplus
}
#endif

#endif

