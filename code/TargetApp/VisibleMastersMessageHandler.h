/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: VisibleMastersMessageHandler.h $
 * $Revision: 3 $
 * $Date: 12/12/08 10:12 $
 */

/**
 * \file VisibleMastersMessageHandler.h
 * This file contains the declarations of te handler routines for the Visible Masters control 
 * message set. The Visible Masters control messages allow for the monitoring of visible 
 * network masters.
 */

#ifndef VISIBLE_MASTERS_MESSAGE_HANDLER_H
#define VISIBLE_MASTERS_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetMessageGrantStatusMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetVisibleMastersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetVisibleMasterMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetVisibleMasterStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                        	    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToResetVisibleMasterStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
												  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetVisibleMasterDelayStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											      	 uint8 *responseBuffer, uint16 *responseBufferLength);


#ifdef __cplusplus
}
#endif

#endif
