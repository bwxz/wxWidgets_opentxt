#ifndef INITIAL_SYSTEM_CONFIGURATION_H
#define INITIAL_SYSTEM_CONFIGURATION_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "TransmissionProtocol.h"
#include "InitialSystemConfigurationCommon.h"
#include "IP.h"
#include "NetworkInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAC_OCTETS_IN_EthernetMacAddress_WORD (MAC_ADDRESS_LENGTH/2)

extern InitialSystemConfiguration initialSystemConfiguration;

//utilities to convert between internal representation of MAC address and usual six-byte representation.
void SetConfiguredMacAddress(uint8 portNumber, const EthernetAddress macAddress);
void GetConfiguredMacAddress(uint8 portNumber, EthernetAddress macAddress);
void GetControlInterface(ExternalInterface* controlInterface);
uint32 GetSecurityKey(void);

//get the default MAC address
void GetDefaultMacAddress(uint8 portNumber, EthernetAddress macAddress);

#define IsProductBootPart() (initialSystemConfiguration.magicNumber   == MAGIC_NUMBER && \
							 initialSystemConfiguration.initialisedBy == BOOT_PRODUCT_INIT)

#define IsApplicationFeatureEnabled(x) (initialSystemConfiguration.applicationFeatureEnable & (x) ? TRUE : FALSE)

Bool GetInitialSystemConfigurationIsMii(uint8 portNumber);
Bool GetInitialSystemConfigurationSgmiiMode(uint8 portNumber, uint32 *sgmiiMode);
void SetInitialSystemConfigurationSgmiiMode(uint8 portNumber, uint32 sgmiiMode);
Bool GetInitialSystemConfigurationPhysicalPortActive(uint8 portNumber, Bool *portActive);
Bool GetInitialSystemConfigurationActivePhysicalPort(uint8 *activePhysicalPort);

uint32 GetSlavePtpPortLimitByPartNumber(void);
uint32 GetMasterPtpPortLimitByPartNumber(void);

#ifdef __cplusplus
}
#endif


#endif
