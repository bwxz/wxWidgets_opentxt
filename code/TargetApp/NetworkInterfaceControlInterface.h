/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */
#ifndef NETWORKINTERFACECONTROLINTERFACE_H_
#define NETWORKINTERFACECONTROLINTERFACE_H_

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "NetworkInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * MMAPI_NETWORK_INTERFACE_PARAMS Block Description
 * - Subblocks defined by mmApiTODSubBlock enum
 * - individual parameters defined by mmApiTODSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE0_PARAMS
typedef enum
{
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_CONFIG = 0,				/* Network Interface Parameters for network interface */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ETHERNET_CONFIG = 1,		/* Network Interface Parameters for Ethernet */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ETHERNET_STATISTICS = 2,	/* Network Interface Parameters for Ethernet Statistics */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_VLAN_CONFIG = 3,			/* Network Interface Parameters for VLAN */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_MDIO_CONFIG = 4,			/* Network Interface Parameters for MDIO */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_PCS_CONFIG = 5,			/* Network Interface Parameters for PCS */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_CONFIG = 6, 			/* Network Interface Parameters for IP4 */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_STATISTICS = 7,		/* Network Interface Parameters for IP4 Statistics */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_STATUS = 8,			/* Network Interface Parameters for IP4 status */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG = 16,	/* Network Interface Parameters for ARP entry configuration */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ARP_TABLE = 17,			/* Network Interface Parameters for ARP table */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP6_CONFIG = 32,			/* Network Interface Parameters for IP6 address configuration */
	NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP6_STATUS = 33,			/* Network Interface Parameters for IP6 address status */
	NETWOK_INTERFACE0_PARAMS_SUBBLOCK_END
} mmApiNetworkInterfaces0SubBlock;

/*this is put in a separate block as it doesn't have mdio available to use*/
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE1_PARAMS
typedef enum
{
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_CONFIG = 				0,	/* Network Interface Parameters for network interface */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ETHERNET_CONFIG = 		1,	/* Network Interface Parameters for Ethernet */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ETHERNET_STATISTICS = 	2,	/* Network Interface Parameters for Ethernet Statistics */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_VLAN_CONFIG = 			3,	/* Network Interface Parameters for VLAN */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_PCS_CONFIG = 			5,	/* Network Interface Parameters for PCS */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_CONFIG = 			6,	/* Network Interface Parameters for IP4 */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_STATISTICS = 		7,	/* Network Interface Parameters for IP4 Statistics */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_STATUS = 8,			/* Network Interface Parameters for IP4 status */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG = 		16,	/* Network Interface Parameters for ARP entry configuration */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ARP_TABLE = 				17,	/* Network Interface Parameters for ARP table */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP6_CONFIG = 32,			/* Network Interface Parameters for IP6 address configuration */
	NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP6_STATUS = 33,			/* Network Interface Parameters for IP6 address status */
	NETWOK_INTERFACE1_PARAMS_SUBBLOCK_END
} mmApiNetworkInterfaces1SubBlock;

//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE01_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE02_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE03_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE04_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE05_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE11_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE12_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE13_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE14_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_INTERFACE15_PARAMS
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_CONFIG = 0,				/* Network Interface Parameters for network interface */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_VLAN_CONFIG = 3,			/* Network Interface Parameters for VLAN */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_CONFIG = 6, 			/* Network Interface Parameters for IP4 */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_STATISTICS = 7,		/* Network Interface Parameters for IP4 Statistics */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_STATUS = 8,			/* Network Interface Parameters for IP4 status */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG = 16,	/* Network Interface Parameters for ARP entry configuration */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_ARP_TABLE = 17,			/* Network Interface Parameters for ARP table */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP6_CONFIG = 32,			/* Network Interface Parameters for IP6 address configuration */
	NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP6_STATUS = 33,			/* Network Interface Parameters for IP6 address status */
	NETWOK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_END
} mmApiNetworkInterfacesVirtualSubBlock;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_CONFIG_CONTROL, network interface control register, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network interface enabled. Valid values:
		  0 network interface disabled
		  1 network interface enabled
	  A virtual port with a virtual port number greater than 0 can only be
	  configured if the vlan id has been set. Only 6 virtual interfaces can
	  be configured on a ToPSync. Virtual ports cannot be deconfigured using
	  the mmapi.

	+ NETWORK_INTERFACE_PARAMS_CONFIG_DOS_PROTECTION_ACTIVE_TIME, network interface DOS protection active time, ro, 0
	  Bits[31:0] = time that DOS protection has been active on the network interface in clock ticks. Reading this register will cause
				   it to be reset to 0.

	+ NETWORK_INTERFACE_PARAMS_CONFIG_DOS_PROTECTION_ACTIVE_INCIDENTS, network interface DOS protection active incidents, ro, 0
	  Bits[31:0] = number of active incidents that have been detected on the network interface

*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_CONFIG_DOS_PROTECTION_ACTIVE_TIME = 1,
	NETWORK_INTERFACE_PARAMS_CONFIG_DOS_PROTECTION_ACTIVE_INCIDENTS = 2,
	NETWORK_INTERFACE_PARAMS_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockConfig;

/*
 * A separate subblock is created for the virtual interfaces because it only supports
 * a subset of the parameters.
 */
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_CONFIG
/*
	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_CONFIG_CONTROL, network interface control register, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network interface enabled. Valid values:
		  0 network interface disabled
		  1 network interface enabled
	  A virtual port with a virtual port number greater than 0 can only be
	  configured if the vlan id has been set. Only 6 virtual interfaces can
	  be configured on a ToPSync. Virtual ports cannot be deconfigured using
	  the mmapi.
*/
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceVirtualParamsSubBlockConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ETHERNET_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ETHERNET_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_ADDRESS_1, ethernet address bytes 0-3, ro, 1
	  Ethernet Address comprise of 6 bytes [0,1,2,3,4,5].
	  Bits[31:24] = Ethernet address byte 0
	  Bits[23:16] = Ethernet address byte 1
	  Bits[15:8]  = Ethernet address byte 2
	  Bits[7:0]   = Ethernet address byte 3

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_ADDRESS_2, ethernet address bytes 4-5, ro, 1
	  Bits[31:24] = Ethernet address byte 4
	  Bits[23:16] = Ethernet address byte 5
	  Bit[15:0]   = Reserved

	- NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_DEFAULT_ADDRESS_1, default ethernet address bytes 0-3, ro, 1
	  Ethernet Address comprise of 6 bytes [0,1,2,3,4,5].
	  Bits[31:24] = Ethernet address byte 0
	  Bits[23:16] = Ethernet address byte 1
	  Bits[15:8]  = Ethernet address byte 2
	  Bits[7:0]   = Ethernet address byte 3

    - NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_DEFAULT_ADDRESS_2, default ethernet address bytes 4-5, ro, 1
	  Bits[31:24] = Ethernet address byte 4
	  Bits[23:16] = Ethernet address byte 5
	  Bit[15:0]   = Reserved
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_ADDRESS_1 = 0,
	NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_ADDRESS_2 = 1,
	NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_DEFAULT_ADDRESS_1 = 2,
	NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_DEFAULT_ADDRESS_2 = 3,
	NETWORK_INTERFACE_PARAMS_ETHERNET_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockEthernetConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ETHERNET_STATISTICS
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ETHERNET_STATISTICS
/*
	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_PACKETS, received Ethernet packets, ro, 0
	  Bits[31:0] = Number of received Ethernet packets

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_MISSED_PACKETS, received Ethernet missed packets, ro, 0
	  Bits[31:0] = Number of missed received Ethernet packets

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_DISCARDED_PACKETS, received Ethernet discarded packets, ro, 0
	  Bits[31:0] = Number of discarded received Ethernet packets

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_ERRORED_PACKETS, received Ethernet packets with errors, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with errors

    + NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_CRC_ERRORS, received Ethernet packets with crc errors, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with CRC errors

    + NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_PACKETS, transmitted Ethernet packets, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_MISSED_PACKETS, transmitted Ethernet missed packets, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets that were missed

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_DISCARDED_PACKETS, transmitted Ethernet discarded packets, ro, 0
	  Bits[31:0] = Number of discarded transmitted Ethernet packets

	+ NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_ERRORED_PACKET, transmitted Ethernet packets with errors, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets with errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_ALIGNMENT_ERROR, received Ethernet packet alignment error, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with alignment errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_FCS_ERROR, received Ethernet packets with FCS errors, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with FCS errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_RUNT_ERROR, received runt Ethernet packets, ro, 0
	  Bits[31:0] = Number of runt received Ethernet packets

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_GIANT_ERROR, received giant Ethernet packets, ro, 0
	  Bits[31:0] = Number of giant received Ethernet packets

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_LATE_COLLISION_ERROR, received Ethernet packets with late collision errors, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with late collision errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_OVERRUN_ERROR, received Ethernet packets with overrun errors, ro, 0
	  Bits[31:0] = Number of received Ethernet packets with overrun errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_SQE_ERROR, transmitted Ethernet packets with SQE errors, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets with SQE errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_DEFERRED_ERROR, transmitted Ethernet packets with deferred errors, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets with deferred errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_LATE_COLLISION_ERROR, transmitted Ethernet packets with late collision errors, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets with late collision errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_EXCESS_COLLISION_ERROR, transmitted Ethernet packets with excessive collision errors, ro, 0
	  Bits[31:0] = Number of transmitted Ethernet packets with collision errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_CARRIER_ERROR, transmitted Ethernet packets with carrier error, ro, 0
	  Bits[31:0] = Number of transmitted packets with carrier errors

	- NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_UNDERRUN_ERROR, transmitted Ethernet packets with underrun errors, ro, 0
	  Bits[31:0] = Number of transmitted packets with underrun errors

*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_PACKETS = 0,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_MISSED_PACKETS = 1,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_DISCARDED_PACKETS = 2,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_ERRORED_PACKETS = 3,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_CRC_ERRORS = 4,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_PACKETS = 5,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_MISSED_PACKETS = 6,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_DISCARDED_PACKETS = 7,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_ERRORED_PACKET = 8,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_ALIGNMENT_ERROR = 9,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_FCS_ERROR = 10,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_RUNT_ERROR = 11,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_GIANT_ERROR = 12,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_LATE_COLLISION_ERROR = 13,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_RX_OVERRUN_ERROR = 14,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_SQE_ERROR = 15,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_DEFERRED_ERROR = 16,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_LATE_COLLISION_ERROR = 17,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_EXCESS_COLLISION_ERROR = 18,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_CARRIER_ERROR = 19,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_TX_UNDERRUN_ERROR = 20,
	NETWORK_INTERFACE_PARAMS_ETHERNET_STATISTICS_SUBBLOCK_END

} mmApiNetworkInterfaceParamsSubBlockEthernetStatistics;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_VLAN_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_VLAN_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_VLAN_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_CONTROL, VLAN control register, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = VLAN enabled. Valid values:
		  0 disable vlan on this interface
		  1 enable vlan on this interface
		  The VLAN configuration can be setup at any time but it is only applied
		  when the interface is configured. An interface cannot be deconfigured
		  so vlans cannot be disabled on an interface once they have been enabled.

	+ NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_TAG, VLAN tag register, rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:13] = Priority Code Point(PCP). This refers to the IEEE 802.1p
					priority. It sets the value that will be written to the
					VLAN header when a frame is transmitted on this interface.
	  Bits[12:12] = Drop Eligible Indicator(DEI). This indicates whether a
				    frame is eligible to be dropped in the presence of
				    congestion. It sets the value that will be written to the
				    VLAN header when a frame is transmitted on this interface.
	  Bits[11:0]  = VLAN identifier(VID). This specifies the value of the VID
				    that the interface belongs to. The interface will send and
				    receive frames with this VID set in the VLAN header. The
				    values 0x000 and 0xFFF are reserved.
	  The vlan configuration is applied when the interface is configured. Once
	  an interface has been configured to use a vlan, a write to this register
	  will change the vlan tag only if the interface has not been configured
	  to be used by any other subsystems. For example, the vlan tag cannot be
	  changed if the interface is configured with an IP address.

	+ NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_STATUS_CONTROL, VLAN status control register, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = VLAN enabled. Valid values:
		  0 vlan on this interface is disabled
		  1 vlan on this interface is enabled

	+ NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_STATUS_TAG, VLAN status tag register, ro, 0
	  Bits[31:16] = Reserved
	  Bits[15:13] = Priority Code Point(PCP). This refers to the IEEE 802.1p
					priority. It sets the value that will be written to the
					VLAN header when a frame is transmitted on this interface.
	  Bits[12:12] = Drop Eligible Indicator(DEI). This indicates whether a
				    frame is eligible to be dropped in the presence of
				    congestion. It sets the value that will be written to the
				    VLAN header when a frame is transmitted on this interface.
	  Bits[11:0]  = VLAN identifier(VID). This specifies the value of the VID
				    that the interface belongs to. The interface will send and
				    receive frames with this VID set in the VLAN header. The
				    values 0x000 and 0xFFF are reserved.
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_TAG = 1,
	NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_STATUS_CONTROL = 16,
	NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_STATUS_TAG = 17,
	NETWORK_INTERFACE_PARAMS_VLAN_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockVlanConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_MDIO_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_CONTROL, MDIO control, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = MDIO available. Valid values:
		  0 MDIO not available
		  1 MDIO available

	- NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_ADDRESS, MDIO address, rw, -
	  Bits[31:5] = Reserved
	  Bits[4:0] = MDIO address

	- NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_REGISTER, MDIO register, rw, -
	  Bits[31:5] = Reserved
	  Bits[4:0] = MDIO register

	- NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_DATA, MDIO data, rw, -
	  Bits[31:16] = Reserved
	  Bits[15:0] = MDIO data
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_ADDRESS = 1,
	NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_REGISTER = 2,
	NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_DATA = 3,
	NETWORK_INTERFACE_PARAMS_MDIO_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockMdioConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_PCS_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_PCS_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SGMII_CONTROL, SGMII configuration, ro, 0
	  Bits[31:2] = Reserved
	  Bits[1] = SGMII mode. Valid values:
		  0 SGMII is in PHY mode
		  1 SGMII is in MAC mode
	  Bit[0] = MII mode. Valid values:
	  	  0 MII mode
	  	  1 SGMII mode

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_CONTROL, PCS control register, rw, 0x00001140
	  Bits[31:16] = Reserved
	  Bit [15] = PCS Reset. Valid Values:
		  0 Normal operation
		  1 Generate a synchronous reset pulse to reset SGMII core (Self-Clearing)
      Bit [14] = Loopback. Valid Values:
		  0 Normal operation
		  1 Serial loopback is implemented in SGMII Core
	  Bit [13] = Reserved
	  Bit [12] = Auto Negotiation Enable. Valid Values:
		  0 Auto Negotiation disabled
		  1 Auto Negotiation enabled (default reset value)
      Bits[11:10] = Reserved
	  Bit [9] = Restart Auto Negotiation. Valid Values:
		  0 Normal operation
		  1 Restart an Auto Negotiation sequence. (Self-Clearing)
	  Bits[8:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_STATUS, PCS status register, ro, 0
	  Bits[31:0] = As defined in IEEE 802.3-2012 Clause 22.2.4.2

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_DEV_ABILITY, PCS device ability register, ro, 0
		These are all Read only bits, used by the SGMII PHY to advertise various capabilities
	  Bits[31:16] = Reserved
	  Bit [15] = Copper Link Status. Valid Values:
		  0 Copper interface link is down
		  1 Copper interface link is up
      Bit [14] = Acknowledgement bit used during autonegotiation.
		  Setting of the bit in the device ability advertisement register is not relevant to the
		  operation of the autonegotiation function. The bit is typically set in the received partner
		  ability register upon successful completion of autonegotiation.
	  Bit [13] = Reserved
	  Bit [12] = Copper Duplex Status. Valid Values:
		  0 Copper Interface resolved to Half-Duplex
		  1 Copper Interface resolved to Full-Duplex
      Bits[11:10] = Copper Speed. Valid Values:
		  00 Copper Interface Speed is 10Mbps
		  01 Copper Interface Speed is 100Mbps
		  10 Copper Interface Speed is Gigabit
		  11 Reserved
	  Bits[9:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_PARTNER_ABILITY, PCS partner ability register, ro, 0
		  These are all Read only bits, used by the SGMII PHY to advertise various capabilities
	  Bits[31:16] = Reserved
	  Bit [15] = Copper Link Status. Valid Values:
		  0 Copper interface link is down
		  1 Copper interface link is up
      Bit [14] = Acknowledgement bit used during autonegotiation.
		  Setting of the bit in the device ability advertisement register is not relevant to the
		  operation of the autonegotiation function. The bit is typically set in the received partner
		  ability register upon successful completion of autonegotiation.
	  Bit [13] = Reserved
	  Bit [12] = Copper Duplex Status. Valid Values:
		  0 Copper Interface resolved to Half-Duplex
		  1 Copper Interface resolved to Full-Duplex
      Bits[11:10] = Copper Speed. Valid Values:
		  00 Copper Interface Speed is 10Mbps
		  01 Copper Interface Speed is 100Mbps
		  10 Copper Interface Speed is Gigabit
		  11 Reserved
	  Bits[9:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_IF_MODE, PCS interface mode register, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SERDES_CONTROL, SERDES control register, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SERDES_STATUS, SERDES status register, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SGMII_LOCK_VALUE, SGMII lock value, ro, 0
	  Bits[31:0] = SGMII Reference Clock Frequency – indicates the relative frequency offset between
		  the local SGMII reference clock and the ToPSync REFCLK input.
		  The value indicates the offset in steps of 0.3 ppm, with a value of 0x00320000 indicating perfect alignment.
		  For reliable operation the value should be between 0x0031FEA2 and 0x0032015E.
		  An out of range value could indicate a missing local SGMII reference clock.

*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SGMII_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_CONTROL = 1,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_STATUS = 2,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_DEV_ABILITY = 3,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_PARTNER_ABILITY = 4,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_IF_MODE = 5,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SERDES_CONTROL = 6,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SERDES_STATUS = 7,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SGMII_LOCK_VALUE = 8,
	NETWORK_INTERFACE_PARAMS_PCS_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubblockPcsConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL, IP4 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
		  3 If ip4 is configured on the network interface, unconfigure the ip4 default gateway using the ip4 address in
		    the ip4 default gateway configuration register.
		  4 If ip4 is configured on the network interface and a default gateway is not configured, configure a default
		    gateway to be the ip4 address in the ip4 default gateway configuration register.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_CONTROL, IP4 dhcp configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 dhcp enabled. Valid values:
		  0 IP4 dhcp disabled
		  1 IP4 dhcp enabled
	  A write to this register sets the DHCP control configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. This register cannot be changed when
	  there are multiple IP4 addresses configured on this interface. IP4 addresses with a multi-home index greater than
	  zero must be unconfigured before the DHCP configuration can be changed. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  Enabling DHCP will clear the IP4 address and subnet configuration registers.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_LEASE_PERIOD_REQUESTED, dhcp requested lease period, rw, 604800
	  Bits[31:0] = IP4 dhcp requested lease period
	  A write to this register sets the requested DHCP lease period configuration register and it will not be applied until
	  the network interface is configured by writing to the IP4 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS, IP4 address, rw, 0
	  Bits[31:0]  = IP4 address to be configured.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK, IP4 subnet mask, rw, 0
	  Bits[31:0] = IP4 subnet mask.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DEFAULT_GATEWAY, IP4 default gateway, rw, 0
	  Bits[31:0] = IP4 default gateway
	  A write to this register sets the IP4 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP4 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_01, IP4 address multi-home index 1 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 1 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_01, IP4 address multi-home index 1, rw, 0
	  Bits[31:0]  = IP4 address to be configured multi-home index 1.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_01, IP4 subnet mask multi-home index 1, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 1.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_02, IPv4 address multi-home index 2 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 2 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_02, IP4 address multi-home index 2, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 2.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_02, IP4 subnet mask multi-home index 2, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 2.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_03, IPv4 address multi-home index 3 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = ip4 address multi-home index 3 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_03, IP4 address multi-home index 3, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 3.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_03, IP4 subnet mask multi-home index 3, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 3.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_04, IPv4 address multi-home index 4 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_04, IP4 address multi-home index 4, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 4.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_04, IP4 subnet mask multi-home index 4, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 4.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_05, IPv4 address multi-home index 5 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 5 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_05, IP4 address multi-home index 5, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 5.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_05, IP4 subnet mask multi-home index 5, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 5.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_CONTROL = 1,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_LEASE_PERIOD_REQUESTED = 2,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS	= 3,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK = 4,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DEFAULT_GATEWAY = 5,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_01	= 16,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_01	= 17,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_01 = 18,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_02 = 32,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_02	= 33,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_02 = 34,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_03 = 48,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_03 = 49,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_03 = 50,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_04 = 64,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_04	= 65,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_04 = 66,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_05 = 80,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_05	= 81,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_05 = 82,
	NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockIp4Config;

/*
 * The IPv4 virtual interfaces > 0 are the same as virtual interface 0 but only support a single static IPv4 address.
 * Hence the parameters are the same as virtual interface 0 except many of them are reserved.
 */
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_CONFIG
/*
	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL, IP4 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
		  3 If ip4 is configured on the network interface, unconfigure the ip4 default gateway using the ip4 address in
		    the ip4 default gateway configuration register.
		  4 If ip4 is configured on the network interface and a default gateway is not configured, configure a default
		    gateway to be the ip4 address in the ip4 default gateway configuration register.
	  A ToPSync should not be configured with more than 6 IP addresses.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DHCP_CONTROL, IP4 dhcp configuration control, rw, 1
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 dhcp enabled. Valid values:
		  0 IP4 dhcp disabled
		  1 IP4 dhcp enabled
	  A write to this register sets the DHCP control configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. This register cannot be changed when
	  there are multiple IP4 addresses configured on this interface. IP4 addresses with a multi-home index greater than
	  zero must be unconfigured before the DHCP configuration can be changed. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  Enabling DHCP will clear the IP4 address and subnet configuration registers.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DHCP_LEASE_PERIOD_REQUESTED, dhcp requested lease period, rw, 604800
	  Bits[31:0] = IP4 dhcp requested lease period
	  A write to this register sets the requested DHCP lease period configuration register and it will not be applied until
	  the network interface is configured by writing to the IP4 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS, IP4 address, rw, 0
	  Bits[31:0]  = IP4 address to be configured.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK, IP4 subnet mask, rw, 0
	  Bits[31:0] = IP4 subnet mask.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DEFAULT_GATEWAY, IP4 default gateway, rw, 0
	  Bits[31:0] = IP4 default gateway
	  A write to this register sets the IP4 default gateway configuration register and it will not be applied until the
	  network interface is configured by writing to the IP4 configuration control register. A read will read this register
	  and it may not be the same as the configuration currently setup on the network interface. The current configuration
	  on the network interface can be read using the appropriate status register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_01, IP4 address multi-home index 1 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 1 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_01, IP4 address multi-home index 1, rw, 0
	  Bits[31:0]  = IP4 address to be configured multi-home index 1.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_01, IP4 subnet mask multi-home index 1, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 1.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_02, IPv4 address multi-home index 2 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 2 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_02, IP4 address multi-home index 2, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 2.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_02, IP4 subnet mask multi-home index 2, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 2.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_03, IPv4 address multi-home index 3 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = ip4 address multi-home index 3 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_03, IP4 address multi-home index 3, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 3.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_03, IP4 subnet mask multi-home index 3, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 3.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_04, IPv4 address multi-home index 4 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 4 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_04, IP4 address multi-home index 4, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 4.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_04, IP4 subnet mask multi-home index 4, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 4.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_05, IPv4 address multi-home index 5 configuration control, rw, 1
	  Bits[31:3] = Reserved
	  Bit[2:0] = IP4 address multi-home index 5 configuration control.
	  A write to this register initiates one of the operations described below. A read will return whether ip4 has
	  been configured or unconfigured. It does not indicate whether the operation was successful and the appropriate
	  status register should be read to determine this. Valid values:
		  0 unconfigure the ip4 configuration on the network interface. This will not change the ip4 configuration
		    registers.
		  1 configure the network interface with the parameters that have been setup by the ip4 configuration registers.
		    The configuration registers should have been setup with a valid configuration, for example an ip4 address
			and a valid subnet mask. This operation is only permitted when the network interface does not already have an
			active ip4 configuration.
		  2 change ip4 address. This is an unconfigure operation followed by a configure operation in a single API call.
	  A ToPSync should not be configured with more than 6 IP addresses.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_05, IP4 address multi-home index 5, rw, 0
	  Bits[31:0]  = IP4 address multi-home index 5.
	  A write to this register sets the IP4 address configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 address configuration register can only be set when DHCP is disabled in the DHCP control register.

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_05, IP4 subnet mask multi-home index 5, rw, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 5.
	  A write to this register sets the IP4 subnet mask configuration register and it will not be applied until the network
	  interface is configured by writing to the IP4 configuration control register. A read will read this register and it
	  may not be the same as the configuration currently setup on the network interface. The current configuration on the
	  network interface can be read using the appropriate status register.
	  The IP4 subnet mask register can only be set when DHCP is disabled in the DHCP control register

*/
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DHCP_CONTROL = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DHCP_LEASE_PERIOD_REQUESTED = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DHCP_LEASE_PERIOD_REQUESTED,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_DEFAULT_GATEWAY = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_DEFAULT_GATEWAY,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_01	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_01	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_01 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_02 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_02	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_02 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_03 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_03 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_03 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_04 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_04	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_04 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_CONTROL_05 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_CONTROL_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_ADDRESS_05	= NETWORK_INTERFACE_PARAMS_IP4_CONFIG_ADDRESS_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBNET_MASK_05 = NETWORK_INTERFACE_PARAMS_IP4_CONFIG_SUBNET_MASK_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceVirtualParamsSubBlockIp4Config;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_STATISTICS
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_STATISTICS
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_STATISTICS
/*
	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_PACKETS, received ip4 packets, ro, 0
	  Bits[31:0] = Number of received ip4 packets

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_OCTETS, received ip4 octets, ro, 0
	  Bits[31:0] = Number of received ip4 octets

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_HDR_ERRORS, received ip4 packets with header errors, ro, 0
	  Bits[31:0] = Number of received ip4 packets with header errors

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_NO_ROUTES, received ip4 packets with no routes, ro, 0
	  Bits[31:0] = Number of received ip4 packets with no routes

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_ADDR_ERRORS, received ip4 packets with address errors, ro, 0
	  Bits[31:0] = Number of received ip4 packets with address errors

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_UNKNOWN_PROTOS, received ip4 packets with unknown protocols, ro, 0
	  Bits[31:0] = Number of received ip4 packets with unknown protocols

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_TRUNCATED_PACKETS, received truncated ip4 packets, ro, 0
	  Bits[31:0] = Number of received truncated ip4 packets

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_FORWARDED_DATAGRAMS, received ip4 forwarded datagrams, ro, 0
	  Bits[31:0] = Number of received ip4 forwarded datagrams

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_REQUIRED, received ip4 packets that require reassembly, ro, 0
	  Bits[31:0] = Number of received ip4 packets that required reassembly

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_OK, received ip4 packets that were reasssembled, ro, 0
	  Bits[31:0] = Number of received ip4 packets that were reassembled successfully

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_FAILED, received ip4 packets that failed to be reassembled, ro, 0
	  Bits[31:0] = Number of received ip4 packets that failed to be reassembled successfully

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_DISCARDED, received ip4 packets that were discared, ro, 0
	  Bits[31:0] = Number of received ip4 packets that were discarded

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_DELIVERED, received ip4 packets that were delivered to the upper layers, ro, 0
	  Bits[31:0] = Number of received ip4 packets that were delivered to the upper layers

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_PACKETS, transmitted ip4 requests, ro, 0
	  Bits[31:0] = Number of transmitted ip4 requests

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_NO_ROUTES, transmitted ip4 requests with no route, ro, 0
	  Bits[31:0] = Number of transmitted ip4 packets with no route

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FORW_DATAGRAMS, transmitted ip4 forwarded datagrams, ro, 0
	  Bits[31:0] = Number of transmitted ip4 forwarded datagrams

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_DISCARDED, transmitted ip4 packets that were discarded, ro, 0
	  Bits[31:0] = Number of transmitted ip4 discarded packets that were discarded

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_REQUIRED, transmitted ip4 requests that require fragmentation, ro, 0
	  Bits[31:0] = Number of transmitted ip4 requests that required fragmentation

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_OK, transmitted ip4 requests that were successfully fragmented, ro, 0
	  Bits[31:0] = Number of transmitted ip4 requests that were successfully	fragmented

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_FAIL, transmitted ip4 request that failed to be fragmented, ro, 0
	  Bits[31:0] = Number of transmitted ip4 requests that failed to be fragmented

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_CREATES, transmitted ip4 requests that were fragmented, ro, 0
	  Bits[31:0] = Number of transmitted ip4 requests that caused a fragmented packet to be created

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_TRANSMITTED, transmitted ip4 packets that were successfully sent, ro, 0
	  Bits[31:0] = Number of transmitted ip4 packets that were successfully sent

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_OCTETS, transmitted ip4 octets, ro, 0
	  Bits[31:0] = Number of transmitted ip4 octets

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_MCAST_PACKETS, received ip4 multicast packets, ro, 0
	  Bits[31:0] = Number of received ip4 multicast packets

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_MCAST_OCTETS, received ip4 multicast octets, ro, 0
	  Bits[31:0] = Number of received ip4 multicast octets

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_MCAST_PACKETS, transmitted ip4 multicast packets, ro, 0
	  Bits[31:0] = Number of transmitted ip4 multicast packets

	- NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_MCAST_OCTETS, transmitted ip4 multicast octets, ro, 0
	  Bits[31:0] = Number of transmitted ip4 multicast octets

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_BCAST_PACKETS, received ip4 broadcast packets, ro, 0
	  Bits[31:0] = Number of received ip4 broadcast packets

	+ NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_BCAST_PACKETS, transmitted ip4 broadcast packets, ro, 0
	  Bits[31:0] = Number of transmitted ip4 broadcast packets
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_PACKETS				= 0,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_OCTETS				= 1,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_HDR_ERRORS			= 2,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_NO_ROUTES			= 3,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_ADDR_ERRORS			= 4,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_UNKNOWN_PROTOS		= 5,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_TRUNCATED_PACKETS	= 6,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_FORWARDED_DATAGRAMS	= 7,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_REQUIRED		= 8,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_OK 			= 9,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_REASM_FAILED			= 10,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_DISCARDED			= 11,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_DELIVERED			= 12,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_PACKETS				= 13,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_NO_ROUTES			= 14,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FORW_DATAGRAMS		= 15,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_DISCARDED			= 16,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_REQUIRED		= 17,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_OK				= 18,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_FAIL 			= 19,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_FRAG_CREATES			= 20,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_TRANSMITTED			= 21,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_OCTETS				= 22,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_MCAST_PACKETS		= 23,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_MCAST_OCTETS 		= 24,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_MCAST_PACKETS		= 25,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_MCAST_OCTETS			= 26,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_RX_BCAST_PACKETS 		= 27,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_TX_BCAST_PACKETS		= 28,
	NETWORK_INTERFACE_PARAMS_IP4_STATISTICS_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockIp4Statistics;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_IP4_STATUS
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_IP4_STATUS
/*
	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL, IP4 address configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = ip4 enabled. Valid values:
		  0 ip4 disabled
		  1 ip4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_CONTROL, IP4 DHCP configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 DHCP enabled. Valid values:
		  0 IP4 DHCP disabled
		  1 IP4 DHCP enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_LEASE_PERIOD, DHCP requested lease period, ro, 0
	  Bits[31:0] = IP4 DHCP lease period

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS, IP4 address, ro, 0
	  Bits[31:0]  = IP4 address

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK, IP4 subnet mask, ro, 0
	  Bits[31:0] = IP4 subnet mask

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_DEFAULT_GATEWAY, IP4 default gateway, ro, 0
	  Bits[31:0] = IP4 default gateway

	 + NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_01, IP4 address multi-home index 1 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 1 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_01, IP4 address multi-home index 1, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 1

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_01, IP4 subnet mask multi-home index 1, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 1

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_02, IP4 address multi-home index 2 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 2 enabled. Valid values:
		  0 ip4 disabled
		  1 ip4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_02, IP4 address multi-home index 2, ro, 0
	  Bits[31:0]  = IP4 address

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_02, IP4 subnet mask multi-home index 2, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 2

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_03, ip4 address multi-home index 3 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 3 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_03, IP4 address multi-home index 3, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 3

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_03, IP4 subnet mask multi-home index 3, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 3

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_04, IP4 address multi-home index 4 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 4 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_04, IP4 address multi-home index 4, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 4

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_04, IP4 subnet mask multi-home index 4, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 4

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_05, IP4 address multi-home index 5 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 5 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_05, IP4 address multi-home index 5, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 5

	+ NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_05, IP4 subnet mask multi-home index 5, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 5
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_CONTROL = 1,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_LEASE_PERIOD = 2,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS	= 3,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK = 4,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_DEFAULT_GATEWAY = 5,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_01 = 16,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_01	= 17,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_01 = 18,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_02 = 32,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_02	= 33,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_02 = 34,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_03 = 48,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_03	= 49,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_03 = 50,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_04 = 64,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_04	= 65,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_04 = 66,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_05 = 80,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_05	= 81,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_05 = 82,
	NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockIp4Status;

/*
 * The IPv4 virtual interfaces > 0 are the same as virtual interface 0 but only support a single static IPv4 address.
 * Hence the parameters are the same as virtual interface 0 except many of them are reserved.
 */
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_IP4_STATUS
/*
	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL, IP4 address configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = ip4 enabled. Valid values:
		  0 ip4 disabled
		  1 ip4 enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DHCP_CONTROL, IP4 DHCP configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 DHCP enabled. Valid values:
		  0 IP4 DHCP disabled
		  1 IP4 DHCP enabled

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DHCP_LEASE_PERIOD, DHCP requested lease period, ro, 0
	  Bits[31:0] = IP4 DHCP lease period

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS, IP4 address, ro, 0
	  Bits[31:0]  = IP4 address

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK, IP4 subnet mask, ro, 0
	  Bits[31:0] = IP4 subnet mask

	+ NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DEFAULT_GATEWAY, IP4 default gateway, ro, 0
	  Bits[31:0] = IP4 default gateway

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_01, IP4 address multi-home index 1 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 1 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_01, IP4 address multi-home index 1, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 1

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_01, IP4 subnet mask multi-home index 1, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 1

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_02, IP4 address multi-home index 2 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 2 enabled. Valid values:
		  0 ip4 disabled
		  1 ip4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_02, IP4 address multi-home index 2, ro, 0
	  Bits[31:0]  = IP4 address

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_02, IP4 subnet mask multi-home index 2, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 2

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_03, ip4 address multi-home index 3 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 3 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_03, IP4 address multi-home index 3, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 3

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_03, IP4 subnet mask multi-home index 3, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 3

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_04, IP4 address multi-home index 4 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 4 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_04, IP4 address multi-home index 4, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 4

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_04, IP4 subnet mask multi-home index 4, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 4

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_05, IP4 address multi-home index 5 configuration status, ro, 0
	  Bits[31:1] = Reserved
	  Bit[0] = IP4 address multi-home index 5 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_05, IP4 address multi-home index 5, ro, 0
	  Bits[31:0]  = IP4 address multi-home index 5

	- NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_05, IP4 subnet mask multi-home index 5, ro, 0
	  Bits[31:0] = IP4 subnet mask multi-home index 5
*/
typedef enum
{
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DHCP_CONTROL = NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_CONTROL,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DHCP_LEASE_PERIOD = NETWORK_INTERFACE_PARAMS_IP4_STATUS_DHCP_LEASE_PERIOD,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS	= NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_DEFAULT_GATEWAY = NETWORK_INTERFACE_PARAMS_IP4_STATUS_DEFAULT_GATEWAY,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_01 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_01 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_01 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_01,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_02 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_02 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_02 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_02,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_03 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_03	= NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_03 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_03,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_04 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_04 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_04 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_04,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_CONTROL_05 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_CONTROL_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_ADDRESS_05	= NETWORK_INTERFACE_PARAMS_IP4_STATUS_ADDRESS_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBNET_MASK_05 = NETWORK_INTERFACE_PARAMS_IP4_STATUS_SUBNET_MASK_05,
	NETWORK_INTERFACE_VIRTUAL_PARAMS_IP4_STATUS_SUBBLOCK_END
} mmApiNetworkInterfaceVirtualParamsSubBlockIp4Status;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_ARP_ENTRY_CONFIG
/*
	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_CONTROL, network interface arp entry control register, rw, 0
	  Bits[31:2] = Reserve
	  Bits[2:0] = Writing to this register will cause an add, delete or get operation to be performed. Each
	  of these operations require that the appropriate ARP entry registers have been setup and the operation
	  may also setup any appropriate ARP entry registers. A read will always return 0. Valid values:
		1 - Add an ARP entry for the IP and Ethernet address set in the ARP entry registers
		2 - Delete the ARP entry associated with the IP address set in the ARP entry registers
		3 - Delete the ARP entry associated with the Ethernet address set in the ARP entry registers
		4 - Get the ARP entry Ethernet address associated with the IP address set in ARP entry registers
		5 - Get the ARP entry IP address associated with the Ethernet address set in the ARP entry registers

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ADDRESS_FAMILY, address family, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = Address family. Valid values:
		1 - IPv4

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_LENGTH, IP address length, rw, 4
	  Bits[31:8] = Reserved
	  Bits[7:0] = Length of IP address

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_1, IP address bytes 0..3, rw, 0
	  Bits[31:0] = The first 4 bytes of the IP address.
		For an IP4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_2, IP address bytes 4..7, rw, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_3, IP address bytes 8..11, rw, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_4, IP address bytes 12..15, rw, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_LENGTH, Ethernet address length, ro, 6
	  Bits[31:8] = Reserved
	  Bits[7:0] = Length of physical address

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_1, Ethernet address bytes 0..3, rw, 0
	  Bits[31:24] = MAC address byte 0 (Most significant byte of 6-byte MAC address )
      Bits[23:16] = MAC address byte 1
      Bits[15:8] = MAC address byte 2
      Bits[7:0] = MAC address byte 3
		e.g. MAC Address 00:16:C0:1F:B1:01 Byte 0 = 0x00, byte 1 = 0x16, byte 2 = 0xC0, byte 3 = 0x1F

	+ NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_2, Ethernet address bytes 4..7, rw, 0
	  Bits[31:24] = MAC address byte 4
      Bits[23:16] = MAC address byte 5 (Least significant byte of 6-byte MAC address )
      Bit[15:0] = Reserved
		e.g. MAC Address 00:16:C0:1F:B1:01 Byte 4 = 0xB1, byte 5 = 0x01
*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ADDRESS_FAMILY = 1,
 	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_LENGTH = 2,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_1 = 3,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_2 = 4,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_3 = 5,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_IP_ADDRESS_4 = 6,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_LENGTH = 7,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_1 = 8,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_ETHERNET_ADDRESS_2 = 9,
	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_CONFIG_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockArpEntryConfig;

//PARAMETERSDEF:NETWORK_INTERFACE0_PARAMS_SUBBLOCK_ARP_TABLE
//PARAMETERSDEF:NETWORK_INTERFACE1_PARAMS_SUBBLOCK_ARP_TABLE
//PARAMETERSDEF:NETWORK_INTERFACE_VIRTUAL_PARAMS_SUBBLOCK_ARP_TABLE
/*
	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_CONTROL, network interface arp table control register, rw, 0
	  Bits[31:8] = Reserve
	  Bits[7:0] = Writing to this register will cause the arp table entries for this interface to be read
	  and will be accessible via the appropriate arp table registers. A read will always return 0. Valid values:
		1 - Read the ARP table entries

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ADDRESS_FAMILY, address family of entries to be read from ARP table, rw, 1
	  Bits[31:8] = Reserved
	  Bits[7:0] = Address family. Valid values:
		1 - IPv4

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_NUMBER_OF_ENTRIES, number of entries read from the ARP table, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = Number of entries read from the ARP table

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_ADDRESS_FAMILY, ARP entry #n# address family, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = address family. Valid values:
		1 - IPv4

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_IP_ADDRESS_LENGTH, ARP entry #n# IP address length, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = Length of IP address

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_IP_ADDRESS_1, ARP entry #n# IP address bytes 0..3, ro, 0
	  Bits[31:0] = The first 4 bytes of the IP address.
		For an IP4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_IP_ADDRESS_2, ARP entry #n# IP address bytes 4..7, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_IP_ADDRESS_3, ARP entry #n# IP address bytes 8..11, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_IP_ADDRESS_4, ARP entry #n# IP address bytes 12..15, ro, 0
	  Bits[31:0] = Reserved

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_ETHERNET_ADDRESS_LENGTH, ARP entry #n# Ethernet address length, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = Length of physical address

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_ETHERNET_ADDRESS_1, ARP entry #n# Ethernet address bytes 0..3, ro, 0
	  Bits[31:24] = MAC address byte 0 (Most significant byte of 6-byte MAC address )
      Bits[23:16] = MAC address byte 1
      Bits[15:8] = MAC address byte 2
      Bits[7:0] = MAC address byte 3
		e.g. MAC Address 00:16:C0:1F:B1:01 Byte 0 = 0x00, byte 1 = 0x16, byte 2 = 0xC0, byte 3 = 0x1F
		A read of this register, will return the physical address that was set in the ARP IP address registers.
		A write to this register will not take effect until the appropriate control bit is written.

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_ETHERNET_ADDRESS_2, ARP entry #n# Ethernet address bytes 4..7, ro, 0
	  Bits[31:24] = MAC address byte 4
      Bits[23:16] = MAC address byte 5 (Least significant byte of 6-byte MAC address )
      Bit[15:0] = Reserved
		e.g. MAC Address 00:16:C0:1F:B1:01 Byte 4 = 0xB1, byte 5 = 0x01

	+ NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_TIME_TO_LIVE, ARP entry #n# ARP entry time-to-live, ro, 0
	  Bits[31:0] = time to live for ARP entry

	- NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_STATE, ARP entry #n# ARP entry state, ro, 0
	  Bits[31:0] = ARP entry state. Valid values:
	    0 - IPv4 entry

	- NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_#n#_REF_CNT, ARP entry #n# ARP entry reference count, ro, 0
	  Bits[31:0] = ARP entry reference count

*/
typedef enum
{
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_CONTROL = 0,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ADDRESS_FAMILY = 1,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_NUMBER_OF_ENTRIES = 2,
	// Gap
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_ADDRESS_FAMILY = 16,
 	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_IP_ADDRESS_LENGTH = 17,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_IP_ADDRESS_1 = 18,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_IP_ADDRESS_2 = 19,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_IP_ADDRESS_3 = 20,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_IP_ADDRESS_4 = 21,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_ETHERNET_ADDRESS_LENGTH = 22,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_ETHERNET_ADDRESS_1 = 23,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_ETHERNET_ADDRESS_2 = 24,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_TIME_TO_LIVE = 25,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_STATE = 26,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_1_REF_CNT = 27,
	// Gap
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_ADDRESS_FAMILY = 32,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_IP_ADDRESS_LENGTH = 33,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_IP_ADDRESS_1 = 34,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_IP_ADDRESS_2 = 35,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_IP_ADDRESS_3 = 36,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_IP_ADDRESS_4 = 37,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_ETHERNET_ADDRESS_LENGTH = 38,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_ETHERNET_ADDRESS_1 = 39,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_ETHERNET_ADDRESS_2 = 40,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_TIME_TO_LIVE = 41,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_STATE = 42,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_2_REF_CNT = 43,
	// Gap
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_ADDRESS_FAMILY = 48,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_IP_ADDRESS_LENGTH = 49,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_IP_ADDRESS_1 = 50,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_IP_ADDRESS_2 = 51,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_IP_ADDRESS_3 = 52,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_IP_ADDRESS_4 = 53,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_ETHERNET_ADDRESS_LENGTH = 54,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_ETHERNET_ADDRESS_1 = 55,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_ETHERNET_ADDRESS_2 = 56,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_TIME_TO_LIVE = 57,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_STATE = 58,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_3_REF_CNT = 59,
	// Gap
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_ADDRESS_FAMILY = 64,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_IP_ADDRESS_LENGTH = 65,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_IP_ADDRESS_1 = 66,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_IP_ADDRESS_2 = 67,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_IP_ADDRESS_3 = 68,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_IP_ADDRESS_4 = 69,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_ETHERNET_ADDRESS_LENGTH = 70,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_ETHERNET_ADDRESS_1 = 71,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_ETHERNET_ADDRESS_2 = 72,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_TIME_TO_LIVE = 73,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_STATE = 74,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_4_REF_CNT = 75,
	// Gap
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_ADDRESS_FAMILY = 80,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_IP_ADDRESS_LENGTH = 81,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_IP_ADDRESS_1 = 82,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_IP_ADDRESS_2 = 83,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_IP_ADDRESS_3 = 84,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_IP_ADDRESS_4 = 85,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_ETHERNET_ADDRESS_LENGTH = 86,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_ETHERNET_ADDRESS_1 = 87,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_ETHERNET_ADDRESS_2 = 88,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_TIME_TO_LIVE = 89,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_STATE = 90,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_5_REF_CNT = 91,
	//etc until ARP_TABLE_ENTRY_254
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_ADDRESS_FAMILY = 4064,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_IP_ADDRESS_LENGTH = 4065,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_IP_ADDRESS_1 = 4066,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_IP_ADDRESS_2 = 4067,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_IP_ADDRESS_3 = 4068,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_IP_ADDRESS_4 = 4069,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_ETHERNET_ADDRESS_LENGTH = 4070,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_ETHERNET_ADDRESS_1 = 4080,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_ETHERNET_ADDRESS_2 = 4081,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_TIME_TO_LIVE = 4082,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_STATE = 4083,
	NETWORK_INTERFACE_PARAMS_ARP_TABLE_ENTRY_254_REF_CNT = 4084,

	NETWORK_INTERFACE_PARAMS_ARP_ENTRY_SUBBLOCK_END
} mmApiNetworkInterfaceParamsSubBlockArpEntry;

typedef enum {
	IP_CONTROL_UNCONFIGURE = 0,
	IP_CONTROL_CONFIGURE = 1,
	IP_CONTROL_CHANGE = 2,
	IP_CONTROL_UNCONFIGURE_DEFAULT_GATEWAY = 3,
	IP_CONTROL_CONFIGURE_DEFAULT_GATEWAY = 4
} ipControlOperation;

ToPSyncConfigResult IpPacketInterfaceSetup(uint8 physicalPortNumber,
										   uint32 virtualPortNumber,
										   uint32 mHomeIndex,
										   ipControlOperation operation,
										   uint8 protocol);
ToPSyncConfigResult mmApiSetNetworkInterfaceConfig(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetNetworkInterfaceConfig(uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsConfigSet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsConfigGet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsVlanConfigSet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsVlanConfigGet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp4ConfigSet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessNetworkInterfaceParamsIp4ConfigGet(
	uint8 physicalPortNumber, uint32 virtualPortNumber, uint16 startAddress,
	uint16 endAddress, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif /* NETWORKINTERFACECONTROLINTERFACE_H_ */
