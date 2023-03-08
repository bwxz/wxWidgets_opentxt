/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: SystemExceptionsMessageHandler.h $
 * $Revision: 1 $
 * $Date: 20/06/07 15:36 $
 */

/**
 * \file SystemExceptionsMessageHandler.h
 * This file contains the declarations of the handler functions for the System
 * Exception control messages.
 */

#ifndef SYSTEM_EXCEPTIONS_MESSAGE_HANDLER_H
#define SYSTEM_EXCEPTIONS_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetToPSyncSystemExceptionsMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetToPSyncSystemExceptionsConfigurationsMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                              uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif
