/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: TimeReferenceSourceMessageHandler.h $
 * $Revision: 11 $
 * $Date: 13/02/09 11:37 $
 */

/**
 * \file TimeReferenceSourceMessageHandler.h
 * This file contains the declarations of the handler routines for the Time Reference Source 
 * control message set. These are messages for the configuration and management of the time 
 * reference sources.
 */

#ifndef TIME_REFERENCE_SOURCE_MESSAGE_HANDLER_H
#define TIME_REFERENCE_SOURCE_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetTimeReferenceSourceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                            uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetTimeReferenceSourceConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTimeReferenceSourceConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                         uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetInitialFrequencyMeasurementParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		          uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetInitialFrequencyMeasurementParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 	 	  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMaxPhaseErrorBeforePhaseRealignmentMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 	 	uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMaxPhaseErrorBeforePhaseRealignmentMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 	 	uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetProportionalAndIntegralGainsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetProportionalAndIntegralGainsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetNoiseAnalyserBandwidthsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetNoiseAnalyserBandwidthsMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetNoiseAnalyserNumberOfFiltersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetNoiseAnalyserNumberOfFiltersMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               		 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetConfiguredPhaseLagMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetConfiguredPhaseLagMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTimeReferenceSourceUTCOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetNoiseAnalyserAlarmThresholdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
										               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetNoiseAnalyserAlarmThresholdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
										               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetTimeReferenceSourcePLLBandwidth(const uint8 *requestMessage, uint16 requestMessageLength, 
										               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTimeReferenceSourcePLLBandwidth(const uint8 *requestMessage, uint16 requestMessageLength, 
										               uint8 *responseBuffer, uint16 *responseBufferLength);


#ifdef __cplusplus
}
#endif

#endif


