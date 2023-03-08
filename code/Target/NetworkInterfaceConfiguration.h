/*
 * � Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */
#ifndef NETWORKINTERFACECONFIGURATION_H_
#define NETWORKINTERFACECONFIGURATION_H_

#include "InitialSystemConfigurationCommon.h"	/* NUMBER_OF_PHYSICAL_PORTS */
#include "ToPSyncInterfaceTypes.h"				/* NUMBER_OF_VIRTUAL_PORTS */
#include "IP.h"									/* IP6_ADDRESS_LENGTH */

#define VIRTUAL_PORT00_CONFIGURED PHYSICAL_PORT_CONFIGURATION_PORT0
#define VIRTUAL_PORT01_CONFIGURED 0
#define VIRTUAL_PORT02_CONFIGURED 0
#define VIRTUAL_PORT03_CONFIGURED 0
#define VIRTUAL_PORT04_CONFIGURED 0
#define VIRTUAL_PORT05_CONFIGURED 0

#define VIRTUAL_PORT10_CONFIGURED PHYSICAL_PORT_CONFIGURATION_PORT1
#define VIRTUAL_PORT11_CONFIGURED 0
#define VIRTUAL_PORT12_CONFIGURED 0
#define VIRTUAL_PORT13_CONFIGURED 0
#define VIRTUAL_PORT14_CONFIGURED 0
#define VIRTUAL_PORT15_CONFIGURED 0

#define VLAN_ID_PORT00	VLAN_ID_PORT0	/* VLAN_ID_PORT0 is defined in SystemConfiguration.h */
#define VLAN_ID_PORT01	0
#define VLAN_ID_PORT02	0
#define VLAN_ID_PORT03	0
#define VLAN_ID_PORT04  0
#define VLAN_ID_PORT05	0

#define VLAN_ID_PORT10	VLAN_ID_PORT1	/* VLAN_ID_PORT1 is defined in SystemConfiguration.h */
#define VLAN_ID_PORT11	0
#define VLAN_ID_PORT12	0
#define VLAN_ID_PORT13	0
#define VLAN_ID_PORT14	0
#define VLAN_ID_PORT15	0

#define VLAN_IS_CONFIGURED_PORT00 ((VLAN_ID_PORT00 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT01 ((VLAN_ID_PORT01 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT02 ((VLAN_ID_PORT02 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT03 ((VLAN_ID_PORT03 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT04 ((VLAN_ID_PORT04 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT05 ((VLAN_ID_PORT05 != 0) ? VLAN_ENABLED : 0)

#define VLAN_IS_CONFIGURED_PORT10 ((VLAN_ID_PORT10 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT11 ((VLAN_ID_PORT11 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT12 ((VLAN_ID_PORT12 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT13 ((VLAN_ID_PORT13 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT14 ((VLAN_ID_PORT14 != 0) ? VLAN_ENABLED : 0)
#define VLAN_IS_CONFIGURED_PORT15 ((VLAN_ID_PORT15 != 0) ? VLAN_ENABLED : 0)

/* IPv4 Port 0 */

#define IP4_ADDR_PORT001			0
#define IP4_SUBNET_MASK_PORT001		0
#define IP4_ADDR_PORT002			0
#define IP4_SUBNET_MASK_PORT002		0
#define IP4_ADDR_PORT003			0
#define IP4_SUBNET_MASK_PORT003		0
#define IP4_ADDR_PORT004			0
#define IP4_SUBNET_MASK_PORT004		0
#define IP4_ADDR_PORT005			0
#define IP4_SUBNET_MASK_PORT005		0

#define IP4_IS_CONFIGURED_PORT01	0
#define IP4_USE_DHCP_PORT01			0
#define IP4_ADDR_PORT010			0
#define IP4_SUBNET_MASK_PORT010		0
#define IP4_ADDR_PORT011			0
#define IP4_SUBNET_MASK_PORT011		0
#define IP4_ADDR_PORT012			0
#define IP4_SUBNET_MASK_PORT012		0
#define IP4_ADDR_PORT013			0
#define IP4_SUBNET_MASK_PORT013		0
#define IP4_ADDR_PORT014			0
#define IP4_SUBNET_MASK_PORT014		0
#define IP4_ADDR_PORT015			0
#define IP4_SUBNET_MASK_PORT015		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT01 0

#define IP4_IS_CONFIGURED_PORT02	0
#define IP4_USE_DHCP_PORT02			0
#define IP4_ADDR_PORT020			0
#define IP4_SUBNET_MASK_PORT020		0
#define IP4_ADDR_PORT021			0
#define IP4_SUBNET_MASK_PORT021		0
#define IP4_ADDR_PORT022			0
#define IP4_SUBNET_MASK_PORT022		0
#define IP4_ADDR_PORT023			0
#define IP4_SUBNET_MASK_PORT023		0
#define IP4_ADDR_PORT024			0
#define IP4_SUBNET_MASK_PORT024		0
#define IP4_ADDR_PORT025			0
#define IP4_SUBNET_MASK_PORT025		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT02 0

#define IP4_IS_CONFIGURED_PORT03	0
#define IP4_USE_DHCP_PORT03			0
#define IP4_ADDR_PORT030			0
#define IP4_SUBNET_MASK_PORT030		0
#define IP4_ADDR_PORT031			0
#define IP4_SUBNET_MASK_PORT031		0
#define IP4_ADDR_PORT032			0
#define IP4_SUBNET_MASK_PORT032		0
#define IP4_ADDR_PORT033			0
#define IP4_SUBNET_MASK_PORT033		0
#define IP4_ADDR_PORT034			0
#define IP4_SUBNET_MASK_PORT034		0
#define IP4_ADDR_PORT035			0
#define IP4_SUBNET_MASK_PORT035		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT03 0

#define IP4_IS_CONFIGURED_PORT04	0
#define IP4_USE_DHCP_PORT04			0
#define IP4_ADDR_PORT040			0
#define IP4_SUBNET_MASK_PORT040		0
#define IP4_ADDR_PORT041			0
#define IP4_SUBNET_MASK_PORT041		0
#define IP4_ADDR_PORT042			0
#define IP4_SUBNET_MASK_PORT042		0
#define IP4_ADDR_PORT043			0
#define IP4_SUBNET_MASK_PORT043		0
#define IP4_ADDR_PORT044			0
#define IP4_SUBNET_MASK_PORT044		0
#define IP4_ADDR_PORT045			0
#define IP4_SUBNET_MASK_PORT045		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT04 0

#define IP4_IS_CONFIGURED_PORT05	0
#define IP4_USE_DHCP_PORT05			0
#define IP4_ADDR_PORT050			0
#define IP4_SUBNET_MASK_PORT050		0
#define IP4_ADDR_PORT051			0
#define IP4_SUBNET_MASK_PORT051		0
#define IP4_ADDR_PORT052			0
#define IP4_SUBNET_MASK_PORT052		0
#define IP4_ADDR_PORT053			0
#define IP4_SUBNET_MASK_PORT053		0
#define IP4_ADDR_PORT054			0
#define IP4_SUBNET_MASK_PORT054		0
#define IP4_ADDR_PORT055			0
#define IP4_SUBNET_MASK_PORT055		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT05 0

/* IPv4 Port 1 */

#define IP4_ADDR_PORT101			0
#define IP4_SUBNET_MASK_PORT101		0
#define IP4_ADDR_PORT102			0
#define IP4_SUBNET_MASK_PORT102		0
#define IP4_ADDR_PORT103			0
#define IP4_SUBNET_MASK_PORT103		0
#define IP4_ADDR_PORT104			0
#define IP4_SUBNET_MASK_PORT104		0
#define IP4_ADDR_PORT105			0
#define IP4_SUBNET_MASK_PORT105		0

#define IP4_IS_CONFIGURED_PORT11	0
#define IP4_USE_DHCP_PORT11			0
#define IP4_ADDR_PORT110			0
#define IP4_SUBNET_MASK_PORT110		0
#define IP4_ADDR_PORT111			0
#define IP4_SUBNET_MASK_PORT111		0
#define IP4_ADDR_PORT112			0
#define IP4_SUBNET_MASK_PORT112		0
#define IP4_ADDR_PORT113			0
#define IP4_SUBNET_MASK_PORT113		0
#define IP4_ADDR_PORT114			0
#define IP4_SUBNET_MASK_PORT114		0
#define IP4_ADDR_PORT115			0
#define IP4_SUBNET_MASK_PORT115		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT11 0

#define IP4_IS_CONFIGURED_PORT12	0
#define IP4_USE_DHCP_PORT12			0
#define IP4_ADDR_PORT120			0
#define IP4_SUBNET_MASK_PORT120		0
#define IP4_ADDR_PORT121			0
#define IP4_SUBNET_MASK_PORT121		0
#define IP4_ADDR_PORT122			0
#define IP4_SUBNET_MASK_PORT122		0
#define IP4_ADDR_PORT123			0
#define IP4_SUBNET_MASK_PORT123		0
#define IP4_ADDR_PORT124			0
#define IP4_SUBNET_MASK_PORT124		0
#define IP4_ADDR_PORT125			0
#define IP4_SUBNET_MASK_PORT125		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT12 0

#define IP4_IS_CONFIGURED_PORT13	0
#define IP4_USE_DHCP_PORT13			0
#define IP4_ADDR_PORT130			0
#define IP4_SUBNET_MASK_PORT130		0
#define IP4_ADDR_PORT131			0
#define IP4_SUBNET_MASK_PORT131		0
#define IP4_ADDR_PORT132			0
#define IP4_SUBNET_MASK_PORT132		0
#define IP4_ADDR_PORT133			0
#define IP4_SUBNET_MASK_PORT133		0
#define IP4_ADDR_PORT134			0
#define IP4_SUBNET_MASK_PORT134		0
#define IP4_ADDR_PORT135			0
#define IP4_SUBNET_MASK_PORT135		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT13 0

#define IP4_IS_CONFIGURED_PORT14	0
#define IP4_USE_DHCP_PORT14			0
#define IP4_ADDR_PORT140			0
#define IP4_SUBNET_MASK_PORT140		0
#define IP4_ADDR_PORT141			0
#define IP4_SUBNET_MASK_PORT141		0
#define IP4_ADDR_PORT142			0
#define IP4_SUBNET_MASK_PORT142		0
#define IP4_ADDR_PORT143			0
#define IP4_SUBNET_MASK_PORT143		0
#define IP4_ADDR_PORT144			0
#define IP4_SUBNET_MASK_PORT144		0
#define IP4_ADDR_PORT145			0
#define IP4_SUBNET_MASK_PORT145		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT14 0

#define IP4_IS_CONFIGURED_PORT15	0
#define IP4_USE_DHCP_PORT15			0
#define IP4_ADDR_PORT150			0
#define IP4_SUBNET_MASK_PORT150		0
#define IP4_ADDR_PORT151			0
#define IP4_SUBNET_MASK_PORT151		0
#define IP4_ADDR_PORT152			0
#define IP4_SUBNET_MASK_PORT152		0
#define IP4_ADDR_PORT153			0
#define IP4_SUBNET_MASK_PORT153		0
#define IP4_ADDR_PORT154			0
#define IP4_SUBNET_MASK_PORT154		0
#define IP4_ADDR_PORT155			0
#define IP4_SUBNET_MASK_PORT155		0
#define IP4_DEFAULT_GATEWAY_ADDR_PORT15 0

/* IPv6 Port 0 */

#define IP6_ADDR_PORT001			{ 0 }
#define IP6_PREFIX_LENGTH_PORT001	0
#define IP6_ADDR_PORT002			{ 0 }
#define IP6_PREFIX_LENGTH_PORT002	0
#define IP6_ADDR_PORT003			{ 0 }
#define IP6_PREFIX_LENGTH_PORT003	0
#define IP6_ADDR_PORT004			{ 0 }
#define IP6_PREFIX_LENGTH_PORT004	0
#define IP6_ADDR_PORT005			{ 0 }
#define IP6_PREFIX_LENGTH_PORT005	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT00  { 0 }

#define IP6_CONFIGURED_PORT01		0
#define IP6_ADDR_ALLOCATION_PORT01 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT010			{ 0 }
#define IP6_PREFIX_LENGTH_PORT010	0
#define IP6_ADDR_PORT011			{ 0 }
#define IP6_PREFIX_LENGTH_PORT011	0
#define IP6_ADDR_PORT012			{ 0 }
#define IP6_PREFIX_LENGTH_PORT012	0
#define IP6_ADDR_PORT013			{ 0 }
#define IP6_PREFIX_LENGTH_PORT013	0
#define IP6_ADDR_PORT014			{ 0 }
#define IP6_PREFIX_LENGTH_PORT014	0
#define IP6_ADDR_PORT015			{ 0 }
#define IP6_PREFIX_LENGTH_PORT015	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT01 	{ 0 }

#define IP6_CONFIGURED_PORT02		0
#define IP6_ADDR_ALLOCATION_PORT02  IP6_ADDR_AUTO
#define IP6_ADDR_PORT020			{ 0 }
#define IP6_PREFIX_LENGTH_PORT020	0
#define IP6_ADDR_PORT021			{ 0 }
#define IP6_PREFIX_LENGTH_PORT021	0
#define IP6_ADDR_PORT022			{ 0 }
#define IP6_PREFIX_LENGTH_PORT022	0
#define IP6_ADDR_PORT023			{ 0 }
#define IP6_PREFIX_LENGTH_PORT023	0
#define IP6_ADDR_PORT024			{ 0 }
#define IP6_PREFIX_LENGTH_PORT024	0
#define IP6_ADDR_PORT025			{ 0 }
#define IP6_PREFIX_LENGTH_PORT025	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT02  { 0 }

#define IP6_CONFIGURED_PORT03		0
#define IP6_ADDR_ALLOCATION_PORT03 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT030			{ 0 }
#define IP6_PREFIX_LENGTH_PORT030	0
#define IP6_ADDR_PORT031			{ 0 }
#define IP6_PREFIX_LENGTH_PORT031	0
#define IP6_ADDR_PORT032			{ 0 }
#define IP6_PREFIX_LENGTH_PORT032	0
#define IP6_ADDR_PORT033			{ 0 }
#define IP6_PREFIX_LENGTH_PORT033	0
#define IP6_ADDR_PORT034			{ 0 }
#define IP6_PREFIX_LENGTH_PORT034	0
#define IP6_ADDR_PORT035			{ 0 }
#define IP6_PREFIX_LENGTH_PORT035	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT03  { 0 }

#define IP6_CONFIGURED_PORT04		0
#define IP6_ADDR_ALLOCATION_PORT04 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT040			{ 0 }
#define IP6_PREFIX_LENGTH_PORT040	0
#define IP6_ADDR_PORT041			{ 0 }
#define IP6_PREFIX_LENGTH_PORT041	0
#define IP6_ADDR_PORT042			{ 0 }
#define IP6_PREFIX_LENGTH_PORT042	0
#define IP6_ADDR_PORT043			{ 0 }
#define IP6_PREFIX_LENGTH_PORT043	0
#define IP6_ADDR_PORT044			{ 0 }
#define IP6_PREFIX_LENGTH_PORT044	0
#define IP6_ADDR_PORT045			{ 0 }
#define IP6_PREFIX_LENGTH_PORT045	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT04  { 0 }

#define IP6_CONFIGURED_PORT05		0
#define IP6_ADDR_ALLOCATION_PORT05 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT050			{ 0 }
#define IP6_PREFIX_LENGTH_PORT050	0
#define IP6_ADDR_PORT051			{ 0 }
#define IP6_PREFIX_LENGTH_PORT051	0
#define IP6_ADDR_PORT052			{ 0 }
#define IP6_PREFIX_LENGTH_PORT052	0
#define IP6_ADDR_PORT053			{ 0 }
#define IP6_PREFIX_LENGTH_PORT053	0
#define IP6_ADDR_PORT054			{ 0 }
#define IP6_PREFIX_LENGTH_PORT054	0
#define IP6_ADDR_PORT055			{ 0 }
#define IP6_PREFIX_LENGTH_PORT055	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT05  { 0 }

/* IPv6 Port 1 */

#define IP6_ADDR_PORT101			{ 0 }
#define IP6_PREFIX_LENGTH_PORT101	0
#define IP6_ADDR_PORT102			{ 0 }
#define IP6_PREFIX_LENGTH_PORT102	0
#define IP6_ADDR_PORT103			{ 0 }
#define IP6_PREFIX_LENGTH_PORT103	0
#define IP6_ADDR_PORT104			{ 0 }
#define IP6_PREFIX_LENGTH_PORT104	0
#define IP6_ADDR_PORT105			{ 0 }
#define IP6_PREFIX_LENGTH_PORT105	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT10  { 0 }

#define IP6_CONFIGURED_PORT11		0
#define IP6_ADDR_ALLOCATION_PORT11 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT110			{ 0 }
#define IP6_PREFIX_LENGTH_PORT110	0
#define IP6_ADDR_PORT111			{ 0 }
#define IP6_PREFIX_LENGTH_PORT111	0
#define IP6_ADDR_PORT112			{ 0 }
#define IP6_PREFIX_LENGTH_PORT112	0
#define IP6_ADDR_PORT113			{ 0 }
#define IP6_PREFIX_LENGTH_PORT113	0
#define IP6_ADDR_PORT114			{ 0 }
#define IP6_PREFIX_LENGTH_PORT114	0
#define IP6_ADDR_PORT115			{ 0 }
#define IP6_PREFIX_LENGTH_PORT115	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT11 	{ 0 }

#define IP6_CONFIGURED_PORT12		0
#define IP6_ADDR_ALLOCATION_PORT12  IP6_ADDR_AUTO
#define IP6_ADDR_PORT120			{ 0 }
#define IP6_PREFIX_LENGTH_PORT120	0
#define IP6_ADDR_PORT121			{ 0 }
#define IP6_PREFIX_LENGTH_PORT121	0
#define IP6_ADDR_PORT122			{ 0 }
#define IP6_PREFIX_LENGTH_PORT122	0
#define IP6_ADDR_PORT123			{ 0 }
#define IP6_PREFIX_LENGTH_PORT123	0
#define IP6_ADDR_PORT124			{ 0 }
#define IP6_PREFIX_LENGTH_PORT124	0
#define IP6_ADDR_PORT125			{ 0 }
#define IP6_PREFIX_LENGTH_PORT125	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT12  { 0 }

#define IP6_CONFIGURED_PORT13		0
#define IP6_ADDR_ALLOCATION_PORT13 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT130			{ 0 }
#define IP6_PREFIX_LENGTH_PORT130	0
#define IP6_ADDR_PORT131			{ 0 }
#define IP6_PREFIX_LENGTH_PORT131	0
#define IP6_ADDR_PORT132			{ 0 }
#define IP6_PREFIX_LENGTH_PORT132	0
#define IP6_ADDR_PORT133			{ 0 }
#define IP6_PREFIX_LENGTH_PORT133	0
#define IP6_ADDR_PORT134			{ 0 }
#define IP6_PREFIX_LENGTH_PORT134	0
#define IP6_ADDR_PORT135			{ 0 }
#define IP6_PREFIX_LENGTH_PORT135	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT13  { 0 }

#define IP6_CONFIGURED_PORT14		0
#define IP6_ADDR_ALLOCATION_PORT14 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT140			{ 0 }
#define IP6_PREFIX_LENGTH_PORT140	0
#define IP6_ADDR_PORT141			{ 0 }
#define IP6_PREFIX_LENGTH_PORT141	0
#define IP6_ADDR_PORT142			{ 0 }
#define IP6_PREFIX_LENGTH_PORT142	0
#define IP6_ADDR_PORT143			{ 0 }
#define IP6_PREFIX_LENGTH_PORT143	0
#define IP6_ADDR_PORT144			{ 0 }
#define IP6_PREFIX_LENGTH_PORT144	0
#define IP6_ADDR_PORT145			{ 0 }
#define IP6_PREFIX_LENGTH_PORT145	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT14  { 0 }

#define IP6_CONFIGURED_PORT15		0
#define IP6_ADDR_ALLOCATION_PORT15 	IP6_ADDR_AUTO
#define IP6_ADDR_PORT150			{ 0 }
#define IP6_PREFIX_LENGTH_PORT150	0
#define IP6_ADDR_PORT151			{ 0 }
#define IP6_PREFIX_LENGTH_PORT151	0
#define IP6_ADDR_PORT152			{ 0 }
#define IP6_PREFIX_LENGTH_PORT152	0
#define IP6_ADDR_PORT153			{ 0 }
#define IP6_PREFIX_LENGTH_PORT153	0
#define IP6_ADDR_PORT154			{ 0 }
#define IP6_PREFIX_LENGTH_PORT154	0
#define IP6_ADDR_PORT155			{ 0 }
#define IP6_PREFIX_LENGTH_PORT155	0
#define IP6_DEFAULT_GATEWAY_ADDR_PORT15  { 0 }

typedef struct
{
	uint8  ptpIpv6MulticastAddressArray[IP6_ADDRESS_LENGTH]; /* PTP IPv6 Multicast address */
} Ipv6SystemConfiguration;

typedef struct
{
	uint32 isConfigured;								/* Vlan configured on virtual port */
	uint32 vlanId;										/* Vlan id */
} VlanPacketInterfaceConfiguration;

typedef struct
{
	uint32 	ipAddress;					/**< IP address configured manually or obtained by DHCP */
	uint32 	subnetMask;					/**< Subnet mask configured manually or obtained by DHCP */
} Ipv4AddrConfiguration;

typedef struct
{
	uint32  configured;					/**< Flag indicating whether the IP packet interface is configured. */
	uint32 	useDHCP;					/**< DHCP used to get IP addressing if non-zero */
	uint32  dhcpLeasePeriodRequested;	/**< DHCP lease period if DHCP used */
	Ipv4AddrConfiguration ipv4AddressConfiguration[NUMBER_OF_IP_ADDRESSES_PER_INTERFACE];
	uint32  defaultGateway;				/**< Default gateway configured manually or obtained by DHCP */
} Ipv4PacketInterfaceConfiguration;

typedef struct
{
	uint8  ipv6AddressArray[IP6_ADDRESS_LENGTH];		/* IP address configured manually or obtained by DHCP */
	uint32 prefixLen;									/* Subnet mask configured manually or obtained by DHCP */
} Ipv6AddrConfiguration;

typedef struct
{
	uint32 isConfigured;								/* Flag indicating whether the IPv6 packet interface is configured. */
	uint32 addressMechanism;							/* mechanism used to allocate IPv6 address */
	Ipv6AddrConfiguration ipv6AddressConfiguration[NUMBER_OF_IP_ADDRESSES_PER_INTERFACE];
	uint8  defaultIpv6GatewayArray[IP6_ADDRESS_LENGTH];	/* Default gateway */
} Ipv6PacketInterfaceConfiguration;

typedef struct
{
	Bool isConfigured;										/* Flag indicating whether a network interface is configured */
	VlanPacketInterfaceConfiguration vlanConfiguration;
	Ipv4PacketInterfaceConfiguration ipConfiguration;
	Ipv6PacketInterfaceConfiguration ipv6Configuration;
} InitialNetworkInterfaceConfiguration;

#define isVlanEnabled(physicalPortNumber, virtualPortNumber) \
	(initialNetworkInterfaceConfiguration[(physicalPortNumber)][(virtualPortNumber)].vlanConfiguration.isConfigured)

extern Ipv6SystemConfiguration ipv6SystemConfiguration;
extern InitialNetworkInterfaceConfiguration initialNetworkInterfaceConfiguration[NUMBER_OF_PHYSICAL_PORTS][NUMBER_OF_VIRTUAL_PORTS];

#endif /* NETWORKINTERFACECONFIGURATION_H_ */
