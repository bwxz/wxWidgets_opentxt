/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */

/**
 * \file InitialSystemConfigurationCommon.h
 * Contains the definition of the initial system configuration structure and is shared between
 * product boot and the application.
 */
#ifndef INITIAL_SYSTEM_CONFIGURATION_COMMON_H
#define INITIAL_SYSTEM_CONFIGURATION_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAGIC_NUMBER 				0x12345A5A
#define NUMBER_OF_RESERVED_WORDS 	4


typedef struct
{
	uint32 mostSignificantWord;	  	//upper three bytes
	uint32 leastSignificantWord;	//lower three bytes

}EthernetMacAddress;

typedef struct
{
	uint32 isConfigured;
	uint32 useDHCP;
	uint32 dhcpLeasePeriodRequested;
	uint32 ipAddress;
	uint32 subnetMask;
	uint32 defaultGateway;
}InitialIpPacketInterfaceConfiguration;

typedef struct
{
	uint32 isConfigured;
}InitialEthernetPacketInterfaceConfiguration;

typedef enum
{
	HOST_JTAG_INIT,
	BOOT_PRODUCT_INIT,
	BOOT_PLUG_AND_PLAY_INIT,
	NETWORK_UPLOAD_INIT
}InitialisedBy;

/*
 * SGMII Configuration
 * These flags are used by the sgmiiConfiguration field in the
 * InitialSystemConfiguration. The first two bits represent the
 * MII/SGMII mode.
 * Note: MII can only be enabled on one network interface.
 */
#define SGMII_CONFIGURATION_MII_MODE_MASK	((uint32)0x00000003)
#define SGMII_CONFIGURATION_IS_MII			((uint32)0x00000000)
#define SGMII_CONFIGURATION_IS_MAC			((uint32)0x00000001)
#define SGMII_CONFIGURATION_IS_PHY			((uint32)0x00000002)
#define SGMII_CONFIGURATION_UNINITIALISED	((uint32)0x80000000)

/*
 * Active Physical Port Configuration
 * These are defined as bit-fields and may not be set.
 */
#define PHYSICAL_PORT_CONFIGURATION_PORT_ACTIVE		((uint32)0x00000001)
#define PHYSICAL_PORT_CONFIGURATION_UNINITIALISED	((uint32)0x80000000)

/*
 * Vlan Port Configuration
 * These are defined as bit-fields and may not be set.
 */
#define VLAN_ENABLED		((uint32)0x00000001)
#define VLAN_UNINITIALISED	((uint32)0x80000000)

#define NUMBER_OF_PHYSICAL_PORTS 2

/*
 * Application Features
 * These are to enable functionality that requires a certain version of Boot code
 * These are defined as bit-fields and may not be set.
 */
#define APP_FEATURE_NETWORK_UPLOAD_ENABLED	((uint32)0x00000001)

typedef struct InitialSystemConfiguration
{
	EthernetMacAddress macAddress[NUMBER_OF_PHYSICAL_PORTS];
	uint32 linkSpeedDuplexMode[NUMBER_OF_PHYSICAL_PORTS];
	InitialIpPacketInterfaceConfiguration ipPacketInterfaceConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	InitialEthernetPacketInterfaceConfiguration ethernetPacketInterfaceConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	uint32 udpEventPortNumber;
	uint32 udpGeneralPortNumber;
	uint32 udpManagementPortNumber;
	uint32 ptpIpMulticastAddress;
	uint32 ptpEthertype;
	EthernetMacAddress ptpEthernetMulticastAddress;
	uint32 controlInterfaceType;
	uint32 controlInterfaceId;
	uint32 uploadInterfaceType;
	uint32 uploadInterfaceId;
	uint32 tcpUploadPortNumber;
	uint32 securityKey;
	uint32 locationIdentifier;
	uint32 mdioAvailable;
	uint32 eventTos;
	uint32 generalTos;
	uint32 reserved[NUMBER_OF_RESERVED_WORDS];
	uint32 applicationFeatureEnable;
	uint32 productType;
	uint32 initialSystemState;
	uint32 magicNumber;
	uint32 factoryFeatureEnable;
	uint32 initialisedBy;
	uint32 sgmiiConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	uint32 physicalPortConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	uint32 vlanConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	uint32 vlanTag[NUMBER_OF_PHYSICAL_PORTS];
}InitialSystemConfiguration;

extern InitialSystemConfiguration initialSystemConfiguration;

#ifdef __cplusplus
}
#endif

#endif
