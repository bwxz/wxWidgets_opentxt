/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: FirmwareIpConfig.h $
 * $Revision: 1 $
 * $Date: 23/07/07 10:04 $
 */

/**
 * \file FirmwareIpConfig.h
 * This files declares the interface for modifying the IP packet interface 
 * configuration before performing a firmware upload to a ToPSync device.
 * For plug-n-play parts, the IP configuration is embedded withing the actual
 * application image that is stored into Flash. If the IP configuration needs 
 * to be modified, so that a Plug-n-Play part uses different IP addresses as 
 * it starts up (or alternatively use DHCP) then the firmware image needs to 
 * be updated with the necessary IP configuration information before performing 
 * a firmware upgrade. The functions declared in this file allow you to do that 
 * by supplying the actual configuration together with a pointer to a buffer 
 * where the firmware image is stored.
 */

#ifndef FIRMWARE_IP_CONFIG_H
#define FIRMWARE_IP_CONFIG_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Indicates the start of the IP address configuration structure
 * for port 0, within the firmware buffer.
 */
#define PORT_0_IP_CONFIGURATION_BASE_OFFSET 0x7FFD4


/**
 * Indicates the start of the IP address configuration structure
 * for port 1, within the firmware buffer.
 */
#define PORT_1_IP_CONFIGURATION_BASE_OFFSET 0x7FFE8


/**
 * The IP address configuration structure
 */
typedef struct
{
    uint32 	useDHCP;					/**< DHCP used to get IP addressing if non-zero */  
	uint32  dhcpLeasePeriodRequested;	/**< DHCP lease period if DHCP used */ 
	uint32 	ipAddress;					/**< IP address configured manually or obtained by DHCP */ 
	uint32 	subnetMask;					/**< Subnet mask configured manually or obtained by DHCP */
	uint32  defaultGateway;				/**< Default gateway configured manually or obtained by DHCP */
} IpInterfaceConfiguration;


/**
 * Modifies the firmware image buffer to set the IP configuration for the given port.
 * \param firmwareBuffer            Buffer that holds the firmware image. Must be (1024*512) bytes long.
 * \param interfaceNumber           Identifies the interface that needs to be configured.
 * \param IpInterfaceConfiguration  The IP configuration for the specified port.
 * \param port0IpConfigBaseOffset	The address where port 0 ip configuration data is stored
 * \param port1IpConfigBaseOffset	The address where port 1 ip configuration data is stored
 */ 
void SetFirmwareIpConfiguration(uint8* firmwareBuffer, const uint8 interfaceNumber, const IpInterfaceConfiguration* ipConfiguration, uint32 port0IpConfigBaseOffset, uint32 port1IpConfigBaseOffset);

/**
 * Returns the IP configuration as currently configured in the firmware image.
 * \param firmwareBuffer            Buffer that holds the firmware image. Must be (1024*512) bytes long.
 * \param interfaceNumber           Identifies the interface for which to retrieve the configuration, one of 0 or 1.
 * \param IpInterfaceConfiguration  The IP configuration for the specified port.
 * \param port0IpConfigBaseOffset	The address where port 0 ip configuration data is stored
 * \param port1IpConfigBaseOffset	The address where port 1 ip configuration data is stored
 */
void GetFirmwareIpConfiguration(const uint8* firmwareBuffer, const uint8 interfaceNumber, IpInterfaceConfiguration* ipConfiguration, uint32 port0IpConfigBaseOffset, uint32 port1IpConfigBaseOffset);


#ifdef __cplusplus
}
#endif

#endif

