/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: PtpPortsMessageHandler.h $
 * $Revision: 19 $
 * $Date: 21/05/09 16:13 $
 */

/**
 * \file PtpPortsMessageHandler.h
 * This file contains the declarations of the handler routines for the PTP ports control 
 * message set. The PTP ports control messages allow for the configuration and management
 * of the PTP ports.
 */

#ifndef PTP_PORTS_MESSAGE_HANDLER_H
#define PTP_PORTS_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/* General */
void ReactToConfigurePtpPortMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToDeconfigurePtpPortMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                        uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpPortConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                             uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpPortEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpPortStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpPortStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpNodeIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpNodeIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDefaultPtpNodeIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
									     uint8 *responseBuffer, uint16 *responseBufferLength);


/* Slave */
void ReactToSetRequestedAnnounceMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetRequestedAnnounceMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetRequestedSyncMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetRequestedSyncMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetRequestedDelayRequestMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetRequestedDelayRequestMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMessagePeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetFilterBandwidthsMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetFilterBandwidthsMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetAcceptableMasterTableRequiredMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAcceptableMasterTableRequiredMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToAddAcceptableMasterMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToDeleteAcceptableMasterMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAcceptableMasterTableEntryMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetAcceptablePartnerTableRequiredMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAcceptablePartnerTableRequiredMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToAddAcceptablePartnerMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToDeleteAcceptablePartnerMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAcceptablePartnerTableEntryMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetDelayToUseMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDelayToUseMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetV1PadMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetV1PadMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetNumberOfMissingAnnounceMessagesToDeclareMasterFailedMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
									     							   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetNumberOfMissingAnnounceMessagesToDeclareMasterFailedMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
									     							   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToEnablePtpPortMasterOperationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToEnablePtpPortSlaveOperationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);


void ReactToGetEnablePtpPortMasterOperationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetEnablePtpPortSlaveOperationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                   uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif

