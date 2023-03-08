/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: TimeReferenceSelectorMessageHandler.h $
 * $Revision: 11 $
 * $Date: 24/03/09 9:53 $
 */

/**
 * \file TimeReferenceSelectorMessageHandler.h
 * This file contains the declrations of the handler routines for the Time Reference Selector 
 * control message set. These are messages for the configuration and management of the Time 
 * Reference Selector.
 */

#ifndef TIME_REFERENCE_SELECTOR_MESSAGE_HANDLER_H
#define TIME_REFERENCE_SELECTOR_MESSAGE_HANDLER_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetSelectedTimeReferenceSourceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTimeReferenceSelectorStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                        uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMaximumFrequencyOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMaximumFrequencyOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetLockedStateThresholdsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLockedStateThresholdsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetForceLockedUnlockedStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetForceLockedUnlockedStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLockedStateMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetFrequencyControllerParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetFrequencyControllerParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncTimeMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetToPSyncParameterMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncParameterMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetLockDetectorThresholdMultipleMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetLockDetectorThresholdMultipleMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetNodeUTCOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetReductionInClockStratum(const uint8 *requestMessage, uint16 requestMessageLength, 
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetReductionInClockStratum(const uint8 *requestMessage, uint16 requestMessageLength, 
												uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif
