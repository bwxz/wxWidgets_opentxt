/*
 * � Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: MDIOMessageHandler.h $Revision: 9 $
 * $Date: 9/10/08 17:06 $
 */

/**
 * \file MDIOMessageHandler.h
 * This file contains the declrations of the handler routines for the MDIO
 * control message set. These are messages for the configuration and management of the MDIO
 */

#ifndef MDIO_MESSAGE_HANDLER_H
#define MDIO_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


void ReactToSetMDIODataMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMDIODataMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
							uint8 *responseBuffer, uint16 *responseBufferLength);


#ifdef __cplusplus
}
#endif

#endif

