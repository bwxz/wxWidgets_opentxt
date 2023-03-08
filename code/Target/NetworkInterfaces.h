#ifndef NETWORK_INTERFACES_H
#define NETWORK_INTERFACES_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "NetworkInterfaceConfiguration.h"
#include "ApplicationInfrastructureInterface.h"

#include "MqxInterface.h"
#ifdef _ARC
#include <trmacro.h>
#else
#define TM_MAX_IPS_PER_IF 2
#endif
#include "Ethernet.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{
	Bool configured;
	EthernetHandle enetHandle;
} EthernetInterfaceConfiguration;

#define DEFAULT_HOP_COUNT 1

/*
 * The maximum number of statically configured IP addresses per interface.
 * IPv6 will also have automatically allocated addresses. The first link-local
 * address will be at MAX_IPS_PER_IF.
 */
#define MAX_IPS_PER_IF TM_MAX_IPS_PER_IF

#define NUMBER_OF_IP_PROTOCOLS 2	/* IPv4 and IPv6 */

#define IP4_PROTO_INDEX	0
#define IP6_PROTO_INDEX	1

/* IPv4 address mechanism flags */

#define IP4_ADDR_STATIC	(0x1 << 0)
#define IP4_ADDR_DHCP	(0x1 << 1)

/* IPv6 address mechanism flags are defined in NetworkInterfacesIpv6 */

#define IpMHomeIndexBit(mHomeIndex)	(0x1 << (mHomeIndex))
#define MHOME_INDEX_MASK 0xFFFF
#define MHOME_IP_SECONDARY_ADDRESS_MASK 0xFE	/* IP addresses in the range 1-7 */

/*
 * NetworkInterfaceIpConfiguration is being used by both IPv4 and IPv6 but the addressMechanism field
 * has a different set of valid values. It may be that in the future this will be split into separate
 * structures.
 */
typedef struct
{
	uint32 configured;				// Each bit indicates whether the corresponding multihome index has been configured
	uint32 addressMechanism;		// indicates address mechanism that has been configured on the interface
} NetworkInterfaceIpConfiguration;

#define VLAN_TAG_MASK 0xFFFF		/* Vlan tag mask is for all 16 bits of vlan tag */
#define VLAN_ID_MASK 0xFFF			/* Vlan id mask is for the 12 bit vlan id */

typedef struct
{
	ttUserInterface interfaceHandle;										// Treck network stack handle
	NetworkInterfaceIpConfiguration ipConfiguration[NUMBER_OF_IP_PROTOCOLS];
} NetworkInterfaceConfiguration;

Bool CompareNetworkInterfaceId(const NetworkInterfaceId *id1, const NetworkInterfaceId *id2);
Bool IsIpConfiguredWithMHomeIndexBitMask(const NetworkInterfaceId *networkInterfaceId,
										 TransmissionProtocol protocol,
										 uint32 mHomeIndexBitMask);
Bool IsIpConfigured(const NetworkInterfaceId *networkInterfaceId, TransmissionProtocol protocol,
					uint32 mHomeIndex);
Bool IsIpConfiguredOnAnyMHomeIndex(const NetworkInterfaceId *networkInterfaceId,
								  TransmissionProtocol protocol);

#define IsEthernetConfigured(portNumber) controlDataPtr->ethernetConfiguration[(portNumber)].configured

#define BUFFERS_PER_FRAME	1

typedef enum
{
	getDOSProtectionActiveTime,
	getDOSProtectionActiveIncidents
} NetworkParameter;

/**
  *	Extended Ethernet statistics that are not included in the public EthernetInterfaceStatistics structure.
  */
typedef struct
{
	uint32 receivedAlign;         	/* Frame Alignment error    */
	uint32 receivedFcs;           	/* CRC error                */
	uint32 receivedRunt;          	/* Runt packet received     */
	uint32 receivedGiant;         	/* Giant packet received    */
	uint32 receivedLatecoll;      	/* Late collision           */
	uint32 receivedOverrun;       	/* DMA overrun              */
	uint32 transmittedSqe;       	/* Heartbeat lost           */
	uint32 transmittedDeferred;     /* Transmission deferred    */
	uint32 transmittedLatecoll;     /* Late collision           */
	uint32 transmittedExcesscoll;   /* Excessive collisions     */
	uint32 transmittedCarrier;      /* Carrier sense lost       */
	uint32 transmittedUnderrun;		/* DMA underrun             */
} EthernetInterfaceStatisticsExt;

Bool InitialiseEthernetInterface(const NetworkInterfaceId *networkInterfaceId, uint32 vlanConfiguration, uint16 vlanTag);

Bool InitialiseIpPacketInterface(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, Ipv4PacketInterfaceConfiguration const * ipConfiguration, uint32 vlanConfiguration, uint16 vlanTag);

int DeleteIpDefaultGateway(const NetworkInterfaceId *networkInterfaceId, uint8 protocol);

void ResetIpPacketInterface(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, TransmissionProtocol protocol);

void IPAddressAllocated(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, TransmissionProtocolAddress *address);

void IP4AddressAllocated(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, uint32 ipAddress);

void IPAddressLost(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, TransmissionProtocol protocol);

Bool GetIpPacketInterfaceStatistics(uint8 portNumber, IpPacketInterfaceStatistics *ipPacketInterfaceStatistics);

Bool GetEthernetInterfaceStatistics(uint8 portNumber, EthernetInterfaceStatistics *ethernetInterfaceStatistics,
									EthernetInterfaceStatisticsExt *ethernetInterfaceStatisticsExt);

Bool ReceiveFromEthernetEthertype(const NetworkInterfaceId *networkInterfaceId, uint16 ethertype, Bool enable);
Bool ReceiveEthernetMulticastMessages(const NetworkInterfaceId *networkInterfaceId, uint16 ethertype, uint8 const multicastAddress[], Bool enable);

void EnableEthernetRx(uint8 interface, uint8 enable);

void TickNetworkInterfaces(uint8 portNumber);
uint32 GetDoSProtectionActiveIncidents(uint8 portNumber);
uint32 GetDoSProtectionActiveTime(uint8 portNumber);
ToPSyncConfigResult GetNetworkParameter(NetworkParameter parameter, float* value);

Bool GetPortVlanTag(const NetworkInterfaceId *networkInterfaceId, uint16 *vlanTag);
Bool ChangePortVlanTag(const NetworkInterfaceId *networkInterfaceId, uint16 vlanTag);
Bool IsPortVlanEnabled(const NetworkInterfaceId *networkInterfaceId);
uint8 GetEthernetPayloadOffset(Bool dot1qVlanEnabled);
uint8 GetEthernetPayloadOffsetFromPort(const NetworkInterfaceId *networkInterfaceId);
void SendEthernetFrame(EthernetHandle enetHandle, PCB_PTR  pcb,  uint16  ethertype, uchar *destAddress, const NetworkInterfaceId *networkInterfaceId);

#ifdef  __cplusplus
}
#endif


#endif
