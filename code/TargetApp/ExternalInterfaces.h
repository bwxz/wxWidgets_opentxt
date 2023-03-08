#ifndef EXTERNAL_INTERFACES_H
#define EXTERNAL_INTERFACES_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "NetworkInterfaces.h"


#ifdef __cplusplus
extern "C"
{
#endif

// Enumerations identifying parameters.
typedef enum
{
	setLockAddress = 0,
	ethernetStatReceivedAlign,
	ethernetStatReceivedFcs,
	ethernetStatReceivedRunt,
	ethernetStatReceivedGiant,
	ethernetStatReceivedLatecoll,
	ethernetStatReceivedOverrun,
	ethernetStatTransmittedSqe,
	ethernetStatTransmittedDeferred,
	ethernetStatTransmittedLatecoll,
	ethernetStatTransmittedExcesscoll,
	ethernetStatTransmittedCarrier,
	ethernetStatTransmittedUnderrun,
	pcsSgmiiConfiguration,
	pcsControl,
	pcsStatus,
	pcsDevAbility,
	pcsPartnerAbility,
	pcsIfMode,
	pcsSerdesControl,
	pcsSerdesStatus,
	pcsSerdeslockValue,
} ExternalInterfacesParameter;



ToPSyncConfigResult DoGetExternalInterfaces(uint8 *numberOfExternalInterfaces, ExternalInterface externalInterfaces[MAXIMUM_EXTERNAL_INTERFACES]);
ToPSyncConfigResult DoResetNetworkInterfaceStatistics(uint8 portNumber, ResetStatisticsMask mask);
/* Ethernet Interface */
ToPSyncConfigResult DoSetEthernetMacAddress(uint8 portNumber, const EthernetAddress macAddress);
ToPSyncConfigResult DoGetEthernetMacAddress(uint8 portNumber, EthernetAddress macAddress);
ToPSyncConfigResult DoGetDefaultEthernetMacAddress(uint8 portNumber, EthernetAddress macAddress);
ToPSyncConfigResult DoGetMDIOLinkAvailability(uint8 portNumber, Bool *mdioIsAvailable);
ToPSyncConfigResult DoSetEthernetLinkSpeedAndDuplexMode(uint8 portNumber, LinkSpeedDuplexMode linkSpeedDuplexMode);
ToPSyncConfigResult DoGetEthernetLinkSpeedAndDuplexMode(uint8 portNumber, LinkSpeedDuplexMode *linkSpeedDuplexMode);
ToPSyncConfigResult DoRestartAutonegotiation(uint8 portNumber);
ToPSyncConfigResult DoSetEthernetInterfaceEnabled(uint8 portNumber, Bool enabled);
ToPSyncConfigResult DoGetEthernetLinkStatus(uint8 portNumber, Bool *enabled, Bool *linkUpState, LinkSpeedDuplexMode *linkSpeedDuplexMode);
ToPSyncConfigResult DoSetMacAddressFilteringEnabled(uint8 portNumber, Bool enabled);
ToPSyncConfigResult DoGetMacAddressFilteringEnabled(uint8 portNumber, Bool *enabled);
ToPSyncConfigResult DoSetPermittedMacAddresses(uint8 portNumber, uint8 numberOfMacAddresses, EthernetAddress macAddresses[MAX_PERMITTED_MAC_ADDRESSES]);
ToPSyncConfigResult DoGetPermittedMacAddresses(uint8 portNumber, uint8 *numberOfMacAddresses, EthernetAddress macAddresses[MAX_PERMITTED_MAC_ADDRESSES]);
ToPSyncConfigResult DoGetEthernetInterfaceStatistics(uint8 portNumber, EthernetInterfaceStatistics *statistics);
/* Ethernet Packet Interface */
ToPSyncConfigResult DoAddEthernetPacketInterface(uint8 portNumber);
ToPSyncConfigResult DoDeleteEthernetPacketInterface(uint8 portNumber);
ToPSyncConfigResult DoSetEthernetPacketInterfaceEnabled(uint8 portNumber, Bool enabled);
ToPSyncConfigResult DoGetEthernetPacketInterfaceStatus(uint8 portNumber, Bool *enabled, Bool *linkUpStatus);
ToPSyncConfigResult DoGetEthernetPacketInterfaceStatistics(uint8 portNumber, EthernetPacketInterfaceStatistics *statistics);
/* IP Packet Interface */
ToPSyncConfigResult DoAddIpPacketInterface(uint8 portNumber, IpPacketInterfaceConfiguration *ipInterfaceConfiguration);
ToPSyncConfigResult DoDeleteIpPacketInterface(uint8 portNumber);
ToPSyncConfigResult DoChangeIpPacketInterface(uint8 portNumber, IpPacketInterfaceConfiguration *ipInterfaceConfiguration);
ToPSyncConfigResult DoGetIpPacketInterfaceConfiguration(uint8 portNumber, IpPacketInterfaceConfiguration *ipInterfaceConfiguration);
ToPSyncConfigResult DoSetIpPacketInterfaceEnabled(uint8 portNumber, Bool enabled);
ToPSyncConfigResult DoGetIpPacketInterfaceStatus(uint8 portNumber, Bool *enabled, Bool *linkUpStatus);
ToPSyncConfigResult DoGetIpPacketInterfaceStatistics(uint8 portNumber, IpPacketInterfaceStatistics *ipPacketInterfaceStatistics);
/* SPI Bus Interface */
ToPSyncConfigResult DoGetSPIBusStatistics(SpiInterfaceStatistics *statistics);
ToPSyncConfigResult DoResetSPIBusStatistics(void);

/*gen param*/
ToPSyncConfigResult DoSetExternalInterfacesParameter(uint8 id1, uint16 parameter, float value);
ToPSyncConfigResult DoGetExternalInterfacesParameter(uint8 id1, uint16 parameter, float *value);

#ifdef __cplusplus
}
#endif


#endif
