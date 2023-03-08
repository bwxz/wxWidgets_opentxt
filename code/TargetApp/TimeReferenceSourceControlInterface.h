/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: TimeReferenceSourceControlInterface.h $
 * $Revision: 6 $
 * $Date: 3/03/09 12:08 $
 */

/**
 * \file TimeReferenceSourceControlInterface.h
 * This file contains the declrations of the handler routines for the Time Reference Source
 * control message set. These are messages for the configuration and management of the Time
 * Reference Source.
 */

#ifndef TIME_REFERENCE_SOURCE_CONTROL_INTERFACE_H
#define TIME_REFERENCE_SOURCE_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "TimeReferenceSource.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
sourceType is either viaPacketNetwork or viaWire

If source type == viaPacketNetwork, id identifies a PTP port
If soruce type == viaWire, id identifies a 1PPS input

*/

TimeReferenceSource *GetTimeReferenceSource(TimeTransport sourceType, uint8 id);
ToPSyncConfigResult DoGetTimeReferenceSource(TimeTransport sourceType, uint8 id, TimeReferenceSourceDetails *timeReferenceSourceDetails);

ToPSyncConfigResult DoSetTimeReferenceSourceConfiguration(TimeTransport sourceType, uint8 id, ReferenceClockConfiguration const* timeReferenceSourceConfiguration);
ToPSyncConfigResult DoGetTimeReferenceSourceConfiguration(TimeTransport sourceType, uint8 id, ReferenceClockConfiguration *timeReferenceSourceConfiguration);

ToPSyncConfigResult DoSetTimeReferenceSourcePLLBandwidth(TimeTransport sourceType, uint8 id, PLLid pll, Bool locked, Frequency bandwidth);
ToPSyncConfigResult DoGetTimeReferenceSourcePLLBandwidth(TimeTransport sourceType, uint8 id, PLLid pll, Bool locked, Frequency* bandwidth);
ToPSyncConfigResult DoSetFilterBandwidths(TimeTransport sourceType, uint8 id, Frequency lockedMasterToSlaveFilterBandwidth,
											  Frequency lockedSlaveToMasterFilterBandwidth,
											  Frequency unlockedMasterToSlaveFilterBandwidth,
											  Frequency unlockedSlaveToMasterFilterBandwidth);
ToPSyncConfigResult DoGetFilterBandwidths(TimeTransport sourceType, uint8 id, Frequency *lockedMasterToSlaveFilterBandwidth,
											  Frequency *lockedSlaveToMasterFilterBandwidth,
											  Frequency *unlockedMasterToSlaveFilterBandwidth,
											  Frequency *unlockedSlaveToMasterFilterBandwidth);

ToPSyncConfigResult DoSetInitialFrequencyMeasurementParameters(TimeTransport sourceType, uint8 id, uint16 initialFrequencyMeasurementDuration,
												uint16 minimumFrequencyMeasurementSamples);
ToPSyncConfigResult DoGetInitialFrequencyMeasurementParameters(TimeTransport sourceType, uint8 id, uint16 *initialFrequencyMeasurementDuration,
												uint16 *minimumFrequencyMeasurementSamples);
ToPSyncConfigResult DoSetMaxPhaseErrorBeforePhaseRealignment(TimeTransport sourceType, uint8 id, ElapsedTime maximumPhaseError);
ToPSyncConfigResult DoGetMaxPhaseErrorBeforePhaseRealignment(TimeTransport sourceType, uint8 id, ElapsedTime *maximumPhaseError);
ToPSyncConfigResult DoSetProportionalAndIntegralGains(TimeTransport sourceType, uint8 id, float unlockedProportionalGain, float lockedProportionalGain,
													  float unlockedIntegralGain, float lockedIntegralGain);
ToPSyncConfigResult DoGetProportionalAndIntegralGains(TimeTransport sourceType, uint8 id, float *unlockedProportionalGain, float *lockedProportionalGain,
													  float *unlockedIntegralGain, float *lockedIntegralGain);
ToPSyncConfigResult DoSetNoiseAnalyserBandwidths(TimeTransport sourceType, uint8 id, Frequency noiseAnalyserOpenBandwidth, Frequency noiseAnalyserClosedBandwidth);
ToPSyncConfigResult DoGetNoiseAnalyserBandwidths(TimeTransport sourceType, uint8 id, Frequency *noiseAnalyserOpenBandwidth, Frequency *noiseAnalyserClosedBandwidth);
ToPSyncConfigResult DoSetNoiseAnalyserNumberOfFilters(TimeTransport sourceType, uint8 id, uint8 numberOfFilters);
ToPSyncConfigResult DoGetNoiseAnalyserNumberOfFilters(TimeTransport sourceType, uint8 id, uint8 *numberOfFilters);
ToPSyncConfigResult DoSetNoiseAnalyserAlarmThreshold(TimeTransport sourceType, uint8 id, Direction direction, Bool onThreshold, Signal threshold);
ToPSyncConfigResult DoGetNoiseAnalyserAlarmThreshold(TimeTransport sourceType, uint8 id, Direction direction, Bool onThreshold, Signal* threshold);
ToPSyncConfigResult DoSetConfiguredPhaseLag(TimeTransport sourceType, uint8 id, float configuredPhaseLag);
ToPSyncConfigResult DoGetConfiguredPhaseLag(TimeTransport sourceType, uint8 id, float *configuredPhaseLag);
ToPSyncConfigResult DoSetBinLockPhaseErrorInputFilterBandwidth(TimeTransport sourceType, uint8 id, Bool locked, float bandwidth);
ToPSyncConfigResult DoSetTimeCorrectionDampingFactor(TimeTransport sourceType, uint8 id, float dampingFactor);
ToPSyncConfigResult DoGetTimeCorrectionDampingFactor(TimeTransport sourceType, uint8 id, float* dampingFactor);
//not used ToPSyncConfigResult DoGetBinLockPhaseErrorInputFilterBandwidth(TimeTransport sourceType, uint8 id, Bool locked, float* bandwidth);
ToPSyncConfigResult DoGetBinaryLockMonitorFilterChainLength(TimeTransport sourceType, uint8 id, uint8* chainLength);
ToPSyncConfigResult DoGetTimeReferenceSourceUTCOffset(TimeTransport sourceType, uint8 id, sint16 *output);
ToPSyncConfigResult DoSetMaximumFrequencyOffset(TimeTransport sourceType, uint8 id, float maximumFrequencyOffset);
ToPSyncConfigResult DoGetMaximumFrequencyOffset(TimeTransport sourceType, uint8 id, float *maximumFrequencyOffset);

ToPSyncConfigResult DoSetTimeReferenceSourceParameter(uint8 id1, uint8 id2, uint16 parameter, float value);
ToPSyncConfigResult DoGetTimeReferenceSourceParameter(uint8 id1, uint8 id2, uint16 parameter, float *value);

ToPSyncConfigResult DoGetTimeReferenceSourceState(TimeTransport sourceType,uint32 sourceIndex,uint32* state);
ToPSyncConfigResult DoGetTimeReferenceSourcePhaseError(TimeTransport sourceType,uint32 sourceIndex,float* error);
ToPSyncConfigResult DoGetTimeReferenceSourceMeasuredNoise(TimeTransport sourceType,uint32 sourceIndex,float* noise);

typedef enum
{
	TRSOURCE_STATUS_PARAMS_STATE				= 0,
	TRSOURCE_STATUS_PARAMS_PHASE_LAG_ERROR		= 1,
	TRSOURCE_STATUS_PARAMS_MEASURED_NOISE		= 2,
	TRSOURCE_STATUS_PARAMS_HOLDOVER_VALIDITY	= 3,
	TRSOURCE_STATUS_PARAMS_LOCK_VALUE			= 4,
	TRSOURCE_STATUS_PARAMS_LOCKED_STATE			= 5,
	TRSOURCE_STATUS_PARAMS_PHASE_ERROR_GRADIENT	= 6,
	TRSOURCE_STATUS_PARAMS_SOURCE_TYPE			= 7,
	TRSOURCE_STATUS_PARAMS_PHASE_ACCURACY		= 8,

    TRSOURCE_STATUS_PARAMS_TIME_SEC_MSB  		= 16,
    TRSOURCE_STATUS_PARAMS_TIME_SEC    			= 17,
    TRSOURCE_STATUS_PARAMS_TIME_NSEC   			= 18,
    TRSOURCE_STATUS_PARAMS_TIME_IS_TAI 			= 19,

    TRSOURCE_STATUS_PARAMS_CLOCK_CLASS 			= 32
}timeReferenceSourceStatusParams;

typedef enum
{
	TRSOURCE_CONFIG_PARAMS_NODE_ID_1				= 0,
	TRSOURCE_CONFIG_PARAMS_NODE_ID_2				= 1,
	TRSOURCE_CONFIG_PARAMS_CLOCK_CLASS				= 2,
	TRSOURCE_CONFIG_PARAMS_TIME_SOURCE				= 3,
	TRSOURCE_CONFIG_PARAMS_CLOCK_ACCURACY			= 4,
	TRSOURCE_CONFIG_PARAMS_OFFSET_LOG_VARIANCE		= 5,
	TRSOURCE_CONFIG_PARAMS_TIME_VALID				= 6,
	TRSOURCE_CONFIG_PARAMS_PRIORITY1				= 7,
	TRSOURCE_CONFIG_PARAMS_PRIORITY2				= 8,
	TRSOURCE_CONFIG_PARAMS_STEPS_REMOVED			= 9
}timeReferenceSourceRefClockParams;

typedef enum
{
	TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH						= 0,
	TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH							= 1,
	TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION					= 2,
	TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES 				= 3,

	TRSOURCE_CONFIG_PARAMS_CONFIGURED_PHASE_LAG 						= 4,
	TRSOURCE_CONFIG_PARAMS_CONFIGURED_MAX_PHASE_ERROR_FOR_JUMP			= 5,

	TRSOURCE_CONFIG_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER					= 9,
	
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_FAST_CALIBRATION					= 10,
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_FREQUENCY_ONLY					= 11,
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_NOISE_COMPENSATION				= 12,
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_RTD_COMPENSATION					= 13,
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_DIRECTION_SELECTION				= 14,
	TRSOURCE_CONFIG_PARAMS_PTP_TRAFFIC_COMPRESS_COEFFICIENT				= 15,
	TRSOURCE_CONFIG_PARAMS_PTP_TRAFFIC_COMPRESS_PROTECT_TRRESH_HI		= 16,
	TRSOURCE_CONFIG_PARAMS_PTP_MAXIMUM_SLIDING_WINDOW_SIZE_SECONDS		= 17,

	TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_STATE						= 20,
	TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_SEARCH_NUMBER_OF_SAMPLES	= 21,
	TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_SEARCH_MEDIAN_POINT			= 22,

	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_SPARSE_DELAY_FILTERING			= 25,
	TRSOURCE_CONFIG_PARAMS_PTP_MINIMUM_SPARSE_DELAY_JUMP_SECONDS		= 26,
	TRSOURCE_CONFIG_PARAMS_PTP_SPARSE_DELAY_RATE_PER_100SECONDS			= 27,

	TRSOURCE_CONFIG_PARAMS_PTP_CAN_BE_BACKUP_SOURCE						= 28,

	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_ADAPTIVE_PLL_BANDWIDTH			= 30,
	TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_ADAPTIVE_SLIDING_WINDOW_LENGTH	= 31,
	TRSOURCE_CONFIG_PARAMS_PTP_TIME_SINCE_LAST_ALIGN_WITH_MASTER_JUMP	= 32,

	TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1		= 35,
	TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2		= 36,

	TRSOURCE_CONFIG_PARAMS_LOCK_SENSITIVITY_MULTIPLE					= 40,

	TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH_DEBUG					= 64,
	TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH_DEBUG					= 65,
	TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_PROPORTIONAL_GAIN_DEBUG			= 66,
	TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_PROPORTIONAL_GAIN_DEBUG			= 67,
	TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_INTEGRAL_GAIN_DEBUG				= 68,
	TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_INTEGRAL_GAIN_DEBUG				= 69,
	TRSOURCE_CONFIG_PARAMS_APPLY_SETTINGS_DEBUG							= 70,

}timeReferenceSourceConfigParams;

typedef enum
{
	TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALUE	= 0,
	TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALID	= 1,
	TRSOURCE_LEAP_SECOND_PARAMS_DAYS			= 4,
	TRSOURCE_LEAP_SECOND_PARAMS_POSITIVE		= 5
}timeReferenceSourceUtcOffsetParams;

ToPSyncConfigResult mmAPIProcessGetTimeReferenceSourceStatusParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessSetTimeReferenceSourceRefClockParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetTimeReferenceSourceRefClockParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessSetTimeReferenceSourceConfigParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetTimeReferenceSourceConfigParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessSetTimeReferenceSourceUtcOffsetParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetTimeReferenceSourceUtcOffsetParams(TimeTransport sourceType,uint32 sourceIndex,uint16 startAddress, uint16 endAddress, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif
