/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: LocalOscillatorMessageHandler.h $
 * $Revision: 3 $
 * $Date: 19/09/07 9:36 $
 */

/**
 * \file LocalOscillatorMessageHandler.h
 * This file contains function declarations for configuring the local oscillator
 * parameters.
 */

#ifndef LOCAL_OSCILLATOR_MESSAGE_HANDLER_H
#define LOCAL_OSCILLATOR_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToSetLocalOscillatorTypeMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLocalOscillatorTypeMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetLocalOscillatorStratumLevelMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLocalOscillatorStratumLevelMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetLocalOscillatorPhaseNoisePairsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLocalOscillatorPhaseNoisePairsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                       uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif

