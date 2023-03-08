/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: ExternalInterfacesMessageHandler.h $
 * $Revision: 2 $
 * $Date: 29/06/07 18:32 $
 */

/**
 * \file ExternalInterfacesMessageHandler.h
 * This file contains declarations for the External Intefaces message handler
 * routines. These include the Ethernet interface, Ethernet Raw interface, IP
 * packet inteface and SPI interface handler functions.
 */

#ifndef EXTERNAL_INTERFACES_MESSAGE_HANDLER_H
#define EXTERNAL_INTERFACES_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetExternalInterfacesMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToResetNetworkInterfaceStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                     uint8 *responseBuffer, uint16 *responseBufferLength);
 
/* Ethernet Interface */
void ReactToSetEthernetMacAddressMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetMacAddressMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDefaultEthernetMacAddressMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMDIOLinkAvailabilityMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                             uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetEthernetLinkSpeedAndDuplexModeMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetLinkSpeedAndDuplexModeMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToRestartAutonegotiationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetEthernetInterfaceEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetLinkStatusMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMacAddressFilteringEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMacAddressFilteringEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPermittedMacAddressesMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPermittedMacAddressesMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetInterfaceStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

/* Ethernet Packet Interface */
void ReactToAddEthernetPacketInterfaceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToDeleteEthernetPacketInterfaceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetEthernetPacketInterfaceEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetPacketInterfaceStatusMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEthernetPacketInterfaceStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                          uint8 *responseBuffer, uint16 *responseBufferLength);

/* IP Packet Interface */
void ReactToAddIpPacketInterfaceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                          uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToDeleteIpPacketInterfaceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                             uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToChangeIpPacketInterfaceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                          uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetIpPacketInterfaceConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetIpPacketInterfaceEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetIpPacketInterfaceStatusMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetIpPacketInterfaceStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

/* SPI Bus Interface */
void ReactToGetSPIBusStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToResetSPIBusStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

/*I2C interface*/
void ReactToReadI2CMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToWriteI2CMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                           uint8 *responseBuffer, uint16 *responseBufferLength);


#ifdef __cplusplus
}
#endif

#endif
