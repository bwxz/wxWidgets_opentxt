/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: DeviceSetsMuxMessageHandler.h $
 * $Revision: 2 $
 * $Date: 8/09/08 9:39 $
 */

/**
 * \file DeviceSetsMuxMessageHandler.h
 * This file contains declarations for the DeviceSetsMux message handler
 * routines. These include the TDM, PTP and OpClk muxes
 */

#ifndef DEVICE_SETS_MUX_MESSAGE_HANDLER_H
#define DEVICE_SETS_MUX_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


void ReactToSetMUXInputMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);
void ReactToGetMUXInputMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);


#ifdef __cplusplus
}
#endif

#endif