/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: GuiMessageHandler.h $
 * $Revision: 6 $
 * $Date: 26/11/07 18:28 $
 */

/**
 * \file GuiMessageHandler.h
 * This file contains declarations for the GUI message handler functions.
 * This is a temporary file for backwards compatibility. All the GUI messages
 * are not part of the ToPSync API and will therefore be obsoleted.
 */

#ifndef GUI_MESSAGE_HANDLER_H
#define GUI_MESSAGE_HANDLER_H

#define VISIBLE_MASTERS_MASK_BITS 32
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToDiscoveryMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLockValueMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPhaseErrorMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                uint8 *responseBuffer, uint16 *responseBufferLength);
                                                
void ReactToGetCurrentMasterIpAddressMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);                        

void ReactToGetNumberOfVisibleMastersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPortStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetCurrentMasterToSlaveFlightTimeMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSlaveToCurrentMasterFlightTimeMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetClockQualityMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetCurrentMasterToSlaveNoiseMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSlaveToCurrentMasterNoiseMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetCurrentMasterClockIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                             uint8 *responseBuffer, uint16 *responseBufferLength);
                                           
void ReactToSetDesiredPhaseLagMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDesiredPhaseLagMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetConnectivityMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetConnectivityMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                     uint8 *responseBuffer, uint16 *responseBufferLength);
    
#ifdef __cplusplus
}
#endif

#endif