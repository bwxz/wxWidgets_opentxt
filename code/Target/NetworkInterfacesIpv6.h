#ifndef NETWORKINTERFACEIPV6_H_
#define NETWORKINTERFACEIPV6_H_

#include "General.h"
#include "NetworkInterfaceConfiguration.h"
#include "ApplicationInfrastructureInterface.h"		/* NetworkInterfaceId */

#define IP6_ADDR_STATIC	 (0x1 << 0)
#define IP6_ADDR_DHCP	 (0x1 << 1)
#define IP6_ADDR_AUTO	 (0x1 << 2)

/*
 * Stateless auto-address configuration
 */
#define IP6_ADDR_AUTO_MHOME_START TM_MAX_IPS_PER_IF
#define IP6_ADDR_MAX_AUTO_IPS_PER_IF TM_6_MAX_AUTOCONF_IPS_PER_IF

Bool InitialiseIpv6PacketInterface(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, Ipv6PacketInterfaceConfiguration const* ipv6Configuration);
int Ipv6AddDefaultGateway(const NetworkInterfaceId *networkInterfaceId);
int Ipv6DeleteDefaultGateway(const NetworkInterfaceId *networkInterfaceId);

#endif /* NETWORKINTERFACEIPV6_H_ */
