/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: CurrentMasterControlInterface.h $
 * $Revision: 1 $
 * $Date: 4/11/08 12:16 $
 */

/**
 * \file CurrentMasterControlInterface.h
 * This file contains the declrations of the handler routines for the CurrentMaster 
 * control message set. These are messages for the configuration and management of the 
 * CurrentMaster
 */

#ifndef CURRENT_MASTER_CONTROL_INTERFACE_H
#define CURRENT_MASTER_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "ToPSyncControlDriverMessages.h"
#include "TimeReferenceSourceControlInterface.h"
#include "HoldoverControllerControlInterface.h"
#include "BinaryLockMonitorControlInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoGetCurrentMaster(Bool *currentMasterExists, CurrentMasterDetails *currentMaster);


/******************************************************************************
 * MMAPI_PTP_PLL#n#_PARAMS Block Description
 * - Subblocks defined by mmApiCurrentMasterSubBlock enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_PTP_PLL1_PARAMS
//SUBBLOCKSDEF:MMAPI_PTP_PLL2_PARAMS
typedef enum
{
	PTP_PLL_PARAMS_SUBBLOCK_SOURCE_STATUS  		= 0,   /* Source status */
	PTP_PLL_PARAMS_SUBBLOCK_SOURCE_CONFIG  		= 1,   /* Source configuration */
	PTP_PLL_PARAMS_SUBBLOCK_SOURCE_REFCLOCK 	= 2,   /* Source reference clock */
	PTP_PLL_PARAMS_SUBBLOCK_UTC_OFFSET 			= 3,   /* UTC Offset */
	PTP_PLL_PARAMS_SUBBLOCK_INPUT_STATUS  		= 8,   /* Source Input */
	PTP_PLL_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG 	= 10,	/* Holdover Controller */
	PTP_PLL_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG	= 11,   /* Binary Lock Monitor */
	PTP_PLL_PARAMS_SUBBLOCK_FREQ_OFFSET			= 12,   /* Frequency offset */

	PTP_PLL_PARAMS_SUBBLOCK_END
} mmApiCurrentMasterSubBlock;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_SOURCE_STATUS
/*
	+ PTP_PLL_STATUS_PARAMS_SOURCE_STATE, Source state, ro, 0
	Bits[31:3] reserved
	Bits[2:0]  Source state.  Valid values:
			0		void. Empty
			1 		invalid. No time is available.
			2 		valid. Time is available but the source has not been selected.
			3		measuring. The source has been selected and is measuring freq or phase offset.
			4		holdover. The source has lost lock and is currently in holdover.
			5		running. The source is providing time information.

	+ PTP_PLL_STATUS_PARAMS_PHASE_LAG_ERROR, Source phase lag error, ro, -
	Bits[31:0]	Phase lag error expressed as a single precision floating point number

	+ PTP_PLL_STATUS_PARAMS_MEASURED_NOISE, Source measured noise, ro, -
	Bits[31:0]	Measured noise expressed as a single precision floating point number
				This is the mean of noise in both directions

	+ PTP_PLL_STATUS_PARAMS_HOLDOVER_VALIDITY, Source holdover validity, ro, -
	Bits[31:0]	Holdover validity expressed as a single precision floating point number

	+ PTP_PLL_STATUS_PARAMS_LOCK_VALUE, Source lock value, ro, -
	Bits[31:0]	Lock value expressed as a single precision floating point number
				Range 0.0 to 1.0

	+ PTP_PLL_STATUS_PARAMS_LOCKED_STATE, Source locked state, ro, 0
	Bits[31:1]	Reserved
	Bits[0]		0 - not locked, 1 - locked

	+ PTP_PLL_STATUS_PARAMS_PHASE_ERROR_GRADIENT, Phase error gradient, ro, -
	Bits[31:0]	Phase error gradient expressed as a single precision floating point number
	This equals the frequency error of the PTP PLL with respect to its time source.

	+ PTP_PLL_STATUS_PARAMS_SOURCE_TYPE, Source type, ro, -
	Bits[31:2] Reserved
	Bits[1:0]  0 = Clock, 1 = Normal PTP, 2 = Hybrid PTP.

	+ PTP_PLL_STATUS_PARAMS_PHASE_ACCURACY, Phase output's accuracy (error range), ro, 0
	Bits[31:0]	Phase output's accuracy is expressed as a single precision floating point number. Valid for Ptp source only.
	Note: This gives an estimate of the possible accuracy range of the phase output. Accuracy should always be a positive value. Value "0" means the accuracy estimate is not valid.

	+ PTP_PLL_STATUS_PARAMS_TIME_SEC, PTP PLL time seconds bits 31 to 0, ro, -
	Bits[31:0] = PTP PLL time seconds bits 31 to 0 of 48 bit seconds field
	Note: This parameter is consistent with the other PTP PLL time registers if read in the same api message

	+ PTP_PLL_STATUS_PARAMS_TIME_NSEC, PTP PLL time nanoseconds, ro, -
	Bits[31:0] = PTP PLL time nanoseconds
	Note: This parameter is consistent with the other PTP PLL time registers if read in the same api message

	+ PTP_PLL_STATUS_PARAMS_TIME_SEC_MSB, PTP PLL time secs bits 47 to 32, ro, -
	Bits[31:16] = reserved
	Bits[15:0]  = PTP PLL time seconds bits 47 to 32 of 48 bit seconds field
	Note: This parameter is consistent with the other PTP PLL time registers if read in the same api message

	+ PTP_PLL_STATUS_PARAMS_TIME_IS_TAI, PTP PLL time TAI flag, ro, -
	Bits[31:1] = reserved
	Bits[0]    = 1 is TAI flag is TRUE, 0 if FALSE
	Note: This parameter is consistent with the other PTP PLL time registers if read in the same api message

	+ PTP_PLL_STATUS_PARAMS_CLOCK_CLASS, Current value of input source Clock Class, ro, -
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock class values
	Note that this may not be the same as %PTP_PLL_CONFIG_PARAMS_CLOCK_CLASS% if the source is in holdover.
*/

typedef enum
{
	PTP_PLL_STATUS_PARAMS_SOURCE_STATE       = TRSOURCE_STATUS_PARAMS_STATE,
	PTP_PLL_STATUS_PARAMS_PHASE_LAG_ERROR    = TRSOURCE_STATUS_PARAMS_PHASE_LAG_ERROR,
	PTP_PLL_STATUS_PARAMS_MEASURED_NOISE	    = TRSOURCE_STATUS_PARAMS_MEASURED_NOISE,
	PTP_PLL_STATUS_PARAMS_HOLDOVER_VALIDITY 	= TRSOURCE_STATUS_PARAMS_HOLDOVER_VALIDITY,
	PTP_PLL_STATUS_PARAMS_LOCK_VALUE 		= TRSOURCE_STATUS_PARAMS_LOCK_VALUE,
	PTP_PLL_STATUS_PARAMS_LOCKED_STATE		= TRSOURCE_STATUS_PARAMS_LOCKED_STATE,
	PTP_PLL_STATUS_PARAMS_PHASE_ERROR_GRADIENT	= TRSOURCE_STATUS_PARAMS_PHASE_ERROR_GRADIENT,
	PTP_PLL_STATUS_PARAMS_SOURCE_TYPE			= TRSOURCE_STATUS_PARAMS_SOURCE_TYPE,
	PTP_PLL_STATUS_PARAMS_PHASE_ACCURACY		= TRSOURCE_STATUS_PARAMS_PHASE_ACCURACY,

	PTP_PLL_STATUS_PARAMS_TIME_SEC_MSB  		= TRSOURCE_STATUS_PARAMS_TIME_SEC_MSB,
	PTP_PLL_STATUS_PARAMS_TIME_SEC    			= TRSOURCE_STATUS_PARAMS_TIME_SEC,
	PTP_PLL_STATUS_PARAMS_TIME_NSEC   			= TRSOURCE_STATUS_PARAMS_TIME_NSEC,
	PTP_PLL_STATUS_PARAMS_TIME_IS_TAI 			= TRSOURCE_STATUS_PARAMS_TIME_IS_TAI,

	PTP_PLL_STATUS_PARAMS_CLOCK_CLASS 			= TRSOURCE_STATUS_PARAMS_CLOCK_CLASS

}mmApiCurrentMasterSubBlockSourceStatusParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_SOURCE_CONFIG
/*
	+ PTP_PLL_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH, PTP PLL Unlocked Bandwidth, rw, 10.0e-3
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	+ PTP_PLL_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH, PTP PLL Locked Bandwidth, rw, 1.0e-3
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	+ PTP_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION, Frequency Measurement Duration, rw, 30
	Bits[31:16] Reserved
	Bits[15:0]  Duration of the initial frequency measurement period in seconds

	+ PTP_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES, Frequency Measurement Minimum Packets, rw, 50
	Bits[31:16] Reserved
	Bits[15:0]  The minimum number of packets to be used in the initial frequency measurement period.

	+ PTP_PLL_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER, Minimum lock value to be master, rw, 0.1
	Bits[31:0] Lock value expressed as a single precision floating point number
	The minimum lock value for an input source used as a time reference on a PTP port for the port to enter master state

	+ PTP_PLL_CONFIG_PARAMS_CONFIGURED_PHASE_LAG, Configured phase lag, rw, 0.0
	Bits[31:0] Configured phase lag in seconds expressed as a single precision floating point number

	+ PTP_PLL_CONFIG_PARAMS_CONFIGURED_MAX_PHASE_ERROR_FOR_JUMP, Configured maximum phase error for phase jump, rw, 15e-6
	Bits[31:0] Configured maximum phase error in seconds expressed as a single precision floating point number.
	Notes: This parameter specifies the maximum phase error before the PTP slave does a phase jump to align with the master.

	+ PTP_PLL_PARAMS_ENABLE_FAST_CALIBRATION, Enable fast calibration, rw, 0
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable
	Notes: When enabled, TopSync will do fast calibration to align with the master in a very short period. This parameter should only be enabled when the network load is low and PTP packet rate is normal or high (32 pps or higher).

	- PTP_PLL_PARAMS_ENABLE_FREQUENCY_ONLY, Enable frequency only operation, rw, 0
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	- PTP_PLL_PARAMS_ENABLE_NOISE_COMPENSATION, Enable noise compensation, rw, 1
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	- PTP_PLL_PARAMS_ENABLE_RTD_COMPENSATION, Enable RTD compensation, rw, 1
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	- PTP_PLL_PARAMS_ENABLE_DIRECTION_SELECTION, Enable direction selection, rw, 1
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable
	
	- PTP_PLL_PARAMS_TRAFFIC_COMPRESS_COEFFICIENT, Traffic compress coefficient, rw, 4.0
	Bits[31:0] float value,
	Notes: The valid input range is 0.0 - 7.0

	- PTP_PLL_PARAMS_TRAFFIC_COMPRESS_PROTECT_TRRESH_HI, Traffic compress protect thresh, rw, 2.5e-7
	Bits[31:0] float value,
	Notes: The valid input range is 1.0e-7 - 5.0e-7

	- PTP_PLL_PARAMS_MAXIMUM_SLIDING_WINDOW_SIZE_SECONDS, Sliding filter window size (seconds), rw, 60
	Bits[31:0] Integer value, 
	Notes: The maximum allowed value is 60 seconds, minimum value is 5 seconds.
	
	- PTP_PLL_PARAMS_MEDIAN_DELAY_STATE, Median delay filter state, rw, 2
	Bits[31:2] Reserved
	Bits[1:0]		0 = Disabled, 1 = MedianDelayOnly, 2 = Adaptive

	- PTP_PLL_PARAMS_MEDIAN_DELAY_SEARCH_NUMBER_OF_SAMPLES, Median delay filter search size, rw, 240
	Bits[31:0] Integer value
	Notes: The valid range is 80 - 240

	- PTP_PLL_PARAMS_MEDIAN_DELAY_SEARCH_MEDIAN_POINT, Median delay filter median point position, rw, 0.065
	Bits[31:0] Float value
	Notes: The valid range is 0 - 0.75.

	- PTP_PLL_PARAMS_ENABLE_SPARSE_DELAY_FILTERING, Enable sparse delay filter, rw, 1
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	- PTP_PLL_PARAMS_SPARSE_DELAY_JUMP_SECONDS, Sparse delay filter delay jump gap, rw, 4.0e-6
	Bits[31:0] Float value
	Notes: The value must be bigger than 1.0e-6.

	- PTP_PLL_PARAMS_SPARSE_DELAY_RATE_PER_100SECONDS, Sparse delay sample happening rate, rw, 4
	Bits[31:0] Integer value
	Notes: The valid range is 1 - 10.

	+ PTP_PLL_PARAMS_CAN_BE_BACKUP_SOURCE, PTP can be backup source to clock input such as GPS, rw, 0
	Bits[31:1] Reserved
	Bits[0]		1 = Can be, 0 = Can not be.

	- PTP_PLL_PARAMS_ENABLE_ADAPTIVE_PLL_BANDWIDTH, Enable adpative PLL bandwidth, rw, 1
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	- PTP_PLL_PARAMS_ENABLE_ADAPTIVE_SLIDING_WINDOW_LENGTH, Enable adaptive sliding window length, rw, 0
	Bits[31:1] Reserved
	Bits[0]		1 = Enable, 0 = Disable

	+ PTP_PLL_PARAMS_TIME_SINCE_LAST_ALIGN_WITH_MASTER_JUMP, Time since last jump to align with the master, rw, -
	Bits[31:0] Unsigned integer in unit of second
	Notes: Write to reset this register to indicate there is master jump. This register will increase one per second to record the time since last alignment with the master.

	+ PTP_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1, Phase buildout property for node time 1, rw, 2
	Bits[31:2] Reserved
	Bits[1:0]	0 = Is not aligned, 1 = Is frequency aligned, 2 = Is phase aligned
	Notes: The default value is different for PTP source and Clock source.

	+ PTP_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2, Phase buildout property for node time 2, rw, 2
	Bits[31:2] Reserved
	Bits[1:0]	0 = Is not aligned, 1 = Is frequency aligned, 2 = Is phase aligned
	Notes: The default value is different for PTP source and Clock source.

	+ PTP_PLL_PARAMS_LOCK_SENSITIVITY_MULTIPLE, Lock detector's sensitivity multiple factor, rw, 1
	Bits[31:0] Positive float value
*/

typedef enum
{
	PTP_PLL_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH	= TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH,
	PTP_PLL_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH	= TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH,

	PTP_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION		= TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION,
	PTP_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES 	= TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES,

	PTP_PLL_CONFIG_PARAMS_CONFIGURED_PHASE_LAG 		= TRSOURCE_CONFIG_PARAMS_CONFIGURED_PHASE_LAG,
	PTP_PLL_CONFIG_PARAMS_CONFIGURED_MAX_PHASE_ERROR_FOR_JUMP 		= TRSOURCE_CONFIG_PARAMS_CONFIGURED_MAX_PHASE_ERROR_FOR_JUMP,

	PTP_PLL_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER		= TRSOURCE_CONFIG_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER,

	PTP_PLL_PARAMS_ENABLE_FAST_CALIBRATION						= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_FAST_CALIBRATION,
	PTP_PLL_PARAMS_ENABLE_FREQUENCY_ONLY						= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_FREQUENCY_ONLY,
	PTP_PLL_PARAMS_ENABLE_NOISE_COMPENSATION					= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_NOISE_COMPENSATION,
	PTP_PLL_PARAMS_ENABLE_RTD_COMPENSATION					= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_RTD_COMPENSATION,
	PTP_PLL_PARAMS_ENABLE_DIRECTION_SELECTION				= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_DIRECTION_SELECTION,
	
	PTP_PLL_PARAMS_MAXIMUM_SLIDING_WINDOW_SIZE_SECONDS		= TRSOURCE_CONFIG_PARAMS_PTP_MAXIMUM_SLIDING_WINDOW_SIZE_SECONDS,
	PTP_PLL_PARAMS_TRAFFIC_COMPRESS_COEFFICIENT				= TRSOURCE_CONFIG_PARAMS_PTP_TRAFFIC_COMPRESS_COEFFICIENT,
	PTP_PLL_PARAMS_TRAFFIC_COMPRESS_PROTECT_TRRESH_HI		= TRSOURCE_CONFIG_PARAMS_PTP_TRAFFIC_COMPRESS_PROTECT_TRRESH_HI,
	PTP_PLL_PARAMS_MEDIAN_DELAY_STATE						= TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_STATE,
	PTP_PLL_PARAMS_MEDIAN_DELAY_SEARCH_NUMBER_OF_SAMPLES		= TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_SEARCH_NUMBER_OF_SAMPLES,
	PTP_PLL_PARAMS_MEDIAN_DELAY_SEARCH_MEDIAN_POINT			= TRSOURCE_CONFIG_PARAMS_PTP_MEDIAN_DELAY_SEARCH_MEDIAN_POINT,

	PTP_PLL_PARAMS_ENABLE_SPARSE_DELAY_FILTERING				= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_SPARSE_DELAY_FILTERING,
	PTP_PLL_PARAMS_SPARSE_DELAY_JUMP_SECONDS					= TRSOURCE_CONFIG_PARAMS_PTP_MINIMUM_SPARSE_DELAY_JUMP_SECONDS,
	PTP_PLL_PARAMS_SPARSE_DELAY_RATE_PER_100SECONDS			= TRSOURCE_CONFIG_PARAMS_PTP_SPARSE_DELAY_RATE_PER_100SECONDS,

	PTP_PLL_PARAMS_CAN_BE_BACKUP_SOURCE						= TRSOURCE_CONFIG_PARAMS_PTP_CAN_BE_BACKUP_SOURCE,
	PTP_PLL_PARAMS_ENABLE_ADAPTIVE_PLL_BANDWIDTH				= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_ADAPTIVE_PLL_BANDWIDTH,
	PTP_PLL_PARAMS_ENABLE_ADAPTIVE_SLIDING_WINDOW_LENGTH		= TRSOURCE_CONFIG_PARAMS_PTP_ENABLE_ADAPTIVE_SLIDING_WINDOW_LENGTH,

	PTP_PLL_PARAMS_TIME_SINCE_LAST_ALIGN_WITH_MASTER_JUMP		= TRSOURCE_CONFIG_PARAMS_PTP_TIME_SINCE_LAST_ALIGN_WITH_MASTER_JUMP,

	PTP_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1		= TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1,
	PTP_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2		= TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2,

	PTP_PLL_PARAMS_LOCK_SENSITIVITY_MULTIPLE					= TRSOURCE_CONFIG_PARAMS_LOCK_SENSITIVITY_MULTIPLE,

}mmApiCurrentMasterSubBlockSourceConfigParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_SOURCE_REFCLOCK
/*
	+ PTP_PLL_CONFIG_PARAMS_NODE_ID_1, Node ID bytes 0-3, ro, 0
	Bits[31:24] Node ID byte 0
	Bits[23:16] Node ID byte 1
	Bits[15:8]  Node ID byte 2
	Bits[7:0]   Node ID byte 3

	+ PTP_PLL_CONFIG_PARAMS_NODE_ID_2, Node ID bytes 4-7, ro, 0
	Bits[31:24] Node ID byte 4
	Bits[23:16] Node ID byte 5
	Bits[15:8]  Node ID byte 6
	Bits[7:0]   Node ID byte 7

	+ PTP_PLL_CONFIG_PARAMS_CLOCK_CLASS, Clock Class, ro, 0
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock class values

	+ PTP_PLL_CONFIG_PARAMS_TIME_SOURCE, Time Source, ro, 0
	Bits[31:4] Reserved
	Bits[3:0]  Time source. Allowed values
			000	Atomic clock
			001 GPS
			010 Terrestrial (radio)
			011 PTP
			100 NTP
			101 Hand set
			110 Other source
			111 internalOscillator. No time reference at all
		   1000	smpte time source F0 (arb)
		   1001 smpte time source F1

	+ PTP_PLL_CONFIG_PARAMS_CLOCK_ACCURACY, Clock Accuracy, ro, 0
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock Accuracy. Allowed values:
		0x20 NS25  The time is accurate to within 25 ns
		0x21 NS100 The time is accurate to within 100 ns
		0x22 NS250 The time is accurate to within 250 ns
		0x23 US1   The time is accurate to within 1 us
		0x24 US2_5 The time is accurate to within 2.5 us
		0x25 US10  The time is accurate to within 10 us
		0x26 US25  The time is accurate to within 25 us
		0x27 US100 The time is accurate to within 100 us
		0x28 US250 The time is accurate to within 250 us
		0x29 MS1   The time is accurate to within 1 ms
		0x2A MS2_5 The time is accurate to within 2.5 ms
		0x2B MS10  The time is accurate to within 10 ms
		0x2C MS25  The time is accurate to within 25 ms
		0x2D MS100 The time is accurate to within 100 ms
		0x2E MS250 The time is accurate to within 250 ms
		0x2F S1    The time is accurate to within 1 s
		0x30 S10   The time is accurate to within 10 s
        0x31 GT10S The time is accurate to >10 s
		0xFE ACC_UNKNOWN The time accuracy is unknown

	+ PTP_PLL_CONFIG_PARAMS_OFFSET_LOG_VARIANCE, Offset scaled log variance, ro, 0
	Bits[31:16] Reserved
	Bits[15:0]  IEEE1588 Offset scaled log variance defined in 1588 v2 7.6.3.3

	+ PTP_PLL_CONFIG_PARAMS_TIME_VALID, Time valid, ro, 0
	Bits[31:1] Reserved
	Bits[0]    1 - The time is a valid TAI time, 0 otherwise

	+ PTP_PLL_CONFIG_PARAMS_PRIORITY1, Priority 1 value, ro, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ PTP_PLL_CONFIG_PARAMS_PRIORITY2, Priority 2 value, ro, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ PTP_PLL_CONFIG_PARAMS_STEPS_REMOVED, Steps removed value, ro, 0
	Bits[31:16] Reserved
	Bits[15:0]  Steps removed value
*/

typedef enum
{
	PTP_PLL_CONFIG_PARAMS_NODE_ID_1	   			= TRSOURCE_CONFIG_PARAMS_NODE_ID_1,
	PTP_PLL_CONFIG_PARAMS_NODE_ID_2	   			= TRSOURCE_CONFIG_PARAMS_NODE_ID_2,
	PTP_PLL_CONFIG_PARAMS_CLOCK_CLASS	   		= TRSOURCE_CONFIG_PARAMS_CLOCK_CLASS,
	PTP_PLL_CONFIG_PARAMS_TIME_SOURCE	   		= TRSOURCE_CONFIG_PARAMS_TIME_SOURCE,
	PTP_PLL_CONFIG_PARAMS_CLOCK_ACCURACY   		= TRSOURCE_CONFIG_PARAMS_CLOCK_ACCURACY,
	PTP_PLL_CONFIG_PARAMS_OFFSET_LOG_VARIANCE	= TRSOURCE_CONFIG_PARAMS_OFFSET_LOG_VARIANCE,
	PTP_PLL_CONFIG_PARAMS_TIME_VALID			= TRSOURCE_CONFIG_PARAMS_TIME_VALID,
	PTP_PLL_CONFIG_PARAMS_PRIORITY1	   			= TRSOURCE_CONFIG_PARAMS_PRIORITY1,
	PTP_PLL_CONFIG_PARAMS_PRIORITY2	   			= TRSOURCE_CONFIG_PARAMS_PRIORITY2,
	PTP_PLL_CONFIG_PARAMS_STEPS_REMOVED			= TRSOURCE_CONFIG_PARAMS_STEPS_REMOVED
}mmApiCurrentMasterSubBlockSourceRefClockParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_INPUT_STATUS
/*
	+ PTP_PLL_INPUT_PARAMS_INPUT_SOURCE_EXISTS, Input Source Exists, ro, 0
	Bits[31:1] reserved
	Bits[0] Input source exists:
	        1 - PTP PLL has input from an external source.
	        0 - PTP PLL has no current input

	+ PTP_PLL_INPUT_PARAMS_VISIBLE_MASTER_INDEX, Visible Master Index, ro, 0xffffffff
	Bits[31:0] Index of current input source in visible master table
			   If PTP PLL has no current input the value is 0xffffffff

	+ PTP_PLL_INPUT_PARAMS_CURRENT_INPUT_STATE, Input State, ro, -
	Bits[31:2] reserved
	Bits[1:0]  Input state of PTP PLL. Valid values:
			00	Estimating frequency offset
			01	Estimating phase offset.
			10  Running.

	+ PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK, Clock input mux to select LO or clock PLL for freq input, rw, 0
	Bits[31:3] Reserved
	Bits[2:0] Valid values (Other values are reserved):
		0 - Local oscillator for frequency
		1 - Clock PLL1 used as frequency input
		2 - Clock PLL2 used as frequency input

	+ PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_COHERENT, Clock input is coherent, rw, 1
	Bits[31:1] Reserved
	Bits[0]  1 = Is coherent, 0 = Not coherent, or congruent

	- PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_PERFECT, Clock input is perfect, rw, 1
	Bits[31:1] Reserved
	Bits[0]  1 = Is perfect, 0 = Not perfect
	Note this parameter is only valid for coherent clock input, to specify whether the clock's frequency is almost perfect or not.

	+ PTP_PLL_INPUT_PARAMS_HYBRID_USE_CONFIGURED_BANDWIDTH, Use configured PLL bandwdith, rw, 0
	Bits[31:1] Reserved
	Bits[0]  1 = Use Configured bandwdith, 0 = Use internal default bandwidth
	Notes: this parameter may be set to TRUE for operation of Hybrid in Boundary Clock case. 

	
	- PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_COHERENT_IN_CONGRUENT_MODE, Coherent clock in congruent Hybrid mode, rw, 0
	Bits[31:1] Reserved
	Bits[0]  1 = Clock is coherent, 0 = Clock is non-coherent
	Notes: this parameter is only valid for congruent Hybrid mode. 
*/

typedef enum
{
	PTP_PLL_INPUT_PARAMS_INPUT_SOURCE_EXISTS			= 0,
	PTP_PLL_INPUT_PARAMS_VISIBLE_MASTER_INDEX			= 1,
	PTP_PLL_INPUT_PARAMS_CURRENT_INPUT_STATE			= 2,
	PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK					= 3,
	PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_COHERENT		= 4,
	PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_PERFECT		= 5,
	PTP_PLL_INPUT_PARAMS_HYBRID_USE_CONFIGURED_BANDWIDTH	= 6,

	PTP_PLL_INPUT_PARAMS_HYBRID_CLOCK_IS_COHERENT_IN_CONGRUENT_MODE = 10

}mmApiCurrentMasterSubBlockInputStatusParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_UTC_OFFSET
/*
	+ PTP_PLL_PARAMS_UTC_OFFSET_VALUE, UTC Offset Value, ro, 0
	Bits[31:0]  UTC Offset value as a signed integer. Valid range covers bits 15:0 only
	Note: if the PTP port does not have a source selected this value is invalid

	+ PTP_PLL_PARAMS_UTC_OFFSET_VALID, UTC Offset Value, ro, 0
	Bits[31:1] Reserved
	Bits[0]    1 UTC Offset value is valid, 0 UTC Offset value is invalid
	Note: if the PTP port does not have a source selected this value is invalid

	+ PTP_PLL_PARAMS_LEAP_SECOND_DAYS, Days to leap second, ro, 0
	Bits[31:0]  Number of days as a signed integer. Valid range covers bits 15:0 only
		If leap second will happen at the next midnight (UTC time) number of days = 0.
		If leap second will happen at tomorrow's midnight (UTC time) number of days = 1.
		Number of days must not be greater than MAX_WARNING_DAYS.
		Setting this value to <0 will clear any pending leap second
		It is advised to set this and the following register in one write operation.
		Note: if the PTP port does not have a source selected this value is invalid

	+ PTP_PLL_PARAMS_LEAP_SECOND_POSITIVE, Leap second is positive, ro, 0
	Bits[31:1] Reserved
	Bits[0]    1 leap second jump is positive, 0 leap second jump is negative
		It is advised to set this and the previous register in one write operation.
		Note: if the PTP port does not have a source selected this value is invalid

*/
typedef enum
{
	PTP_PLL_PARAMS_UTC_OFFSET_VALUE		= TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALUE,
	PTP_PLL_PARAMS_UTC_OFFSET_VALID		= TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALID,
	PTP_PLL_PARAMS_LEAP_SECOND_DAYS		= TRSOURCE_LEAP_SECOND_PARAMS_DAYS,
	PTP_PLL_PARAMS_LEAP_SECOND_POSITIVE 	= TRSOURCE_LEAP_SECOND_PARAMS_POSITIVE
}mmApiCurrentMasterSubBlockUtcOffsetParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG
/*
	+ PTP_PLL_PARAMS_HOLDOVER_DURATION, Holdover Duration, rw, 3600
	Bits[31:0]  Duration value as a unsigned integer.

	+ PTP_PLL_PARAMS_HOLDOVER_RESET, Reset, wo, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= any value.
				Notes: This resets the holdover data used to maintain effective holdover in the absence
				of an input source.  It does not force the PLL to exit the holdover state and should not
				be used when the PLL is in holdover

	+ PTP_PLL_PARAMS_FORCE_HOLDOVER, Disable/enable forceHoldover, rw, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= 1 - ForceHoldover enabled, 0 - disabled

	+ PTP_PLL_PARAMS_HOLDOVER_CLASS, clock class on entering holdover, rw, 14
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value on entering holdover

	+ PTP_PLL_PARAMS_REDUCED_HOLDOVER_CLASS, clock class after holdover duration, rw, 193
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value after the holdover duration has expired

	+ PTP_PLL_PARAMS_HOLDOVER_TRIGGERING_NOISE_LEVEL, packet noise level triggering holdover state, rw, 10.0e-6
	Bits[31:0] = positive float value
				Notes: The valid minimum value for this parameter is 1.0e-6

	+ PTP_PLL_PARAMS_HOLDOVER_GMID, Use local node ID for GM ID in holdover, rw, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= 0 Keep previous GM (external) ID in holdover (default)
	            = 1 Change transmitted GM ID in PTP messages to local node ID in holdover
*/
typedef enum
{
	PTP_PLL_PARAMS_HOLDOVER_DURATION		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_DURATION,
	PTP_PLL_PARAMS_HOLDOVER_RESET		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_RESET,
	PTP_PLL_PARAMS_FORCE_HOLDOVER		= HOLDOVER_CONTROLLER_PARAMS_FORCE_HOLDOVER,
	PTP_PLL_PARAMS_HOLDOVER_CLASS		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_CLOCK_CLASS,
	PTP_PLL_PARAMS_REDUCED_HOLDOVER_CLASS = HOLDOVER_CONTROLLER_PARAMS_REDUCED_HOLDOVER_CLOCK_CLASS,
	PTP_PLL_PARAMS_HOLDOVER_TRIGGERING_NOISE_LEVEL = HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_TRIGGERING_NOISE_LEVEL,
	PTP_PLL_PARAMS_HOLDOVER_GMID        = HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_GMID
}mmApiCurrentMasterSubBlockHoldoverParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG
/*
	+ PTP_PLL_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE, Binary error acceptable, rw, 1.0e-6
	Bits[31:0]  value as a float value.

	+ PTP_PLL_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE, Binary error unacceptable, rw, 5.0e-6
	Bits[31:0] 	value as a float value.

	+ PTP_PLL_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE, Binary error gradient acceptable, rw, 1.0e-9
	Bits[31:0]  value as a float value.

	+ PTP_PLL_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE, Binary error gradient unaccpetable, rw, 2.5e-9
	Bits[31:0] 	value as a float value.

	+ PTP_PLL_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE, Binary fuzzy lock acceptable, rw, 0.5
	Bits[31:0]  value as a float value.

	+ PTP_PLL_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE, Binary fuzzy lock unacceptable, rw, 0.25
	Bits[31:0] 	value as a float value.

	+ PTP_PLL_PARAMS_BLM_FORCE_LOCK, Binary force lock, rw, 0
	Bits[31:2]  reserved.
	Bits[1:0]	2 = Forced to UnLocked State, 1 = Forced to Locked State, 0 = Not Forced 

	+ PTP_PLL_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH, Binary maintain lock during source switch, rw, 0
	Bits[31:1]  reserved.
	Bits[0]		1 = Maintain Lock, 0 = Not Maintain Lock

	- PTP_PLL_PARAMS_BLM_FILTER_BANDWIDTH_UNLOCKED, Binary lock monitor filter bandwidth (Unlocked), rw, 1.0e-2
	Bits[31:0] 	value as a float value.

	- PTP_PLL_PARAMS_BLM_FILTER_BANDWIDTH_LOCKED, Binary lock monitor filter bandwidth (Locked), rw, 5.0e-4
	Bits[31:0] 	value as a float value.

*/

typedef enum
{
	PTP_PLL_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_ACCEPTABLE,
	PTP_PLL_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE 		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_UNACCEPTABLE,
	PTP_PLL_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_ACCEPTABLE,
	PTP_PLL_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_UNACCEPTABLE,
	PTP_PLL_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_ACCEPTABLE,
	PTP_PLL_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE  		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_UNACCEPTABLE,

	PTP_PLL_PARAMS_BLM_FORCE_LOCK					= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FORCE_LOCK,
	PTP_PLL_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH = BINARY_LOCK_MONITOR_CONFIG_PARAMS_MAINTAIN_LOCK_DURING_SOURCE_SWITCH,

	PTP_PLL_PARAMS_BLM_FILTER_BANDWIDTH_UNLOCKED    = BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_UNLOCKED,
	PTP_PLL_PARAMS_BLM_FILTER_BANDWIDTH_LOCKED 		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_LOCKED,

}mmApiCurrentMasterSubBlockBinaryLockMonitorParams;

//PARAMETERSDEF:PTP_PLL_PARAMS_SUBBLOCK_FREQ_OFFSET
/*
	+ PTP_PLL_FREQ_OFFSET_MAX_FREQ_OFFSET, Clock PLL max frequency offset, rw, 0
	Bits[31:0] Max frequency offset in Hz expressed as a single precision floating point number
	Value in Hz

	+ PTP_PLL_FREQ_OFFSET_CURRENT_FREQ_OFFSET, Clock PLL CURRENT frequency offset, rO, 0
	Bits[31:0] frequency offset in Hz expressed as a single precision floating point number
	Value in Hz
*/
typedef enum
{
	PTP_PLL_FREQ_OFFSET_MAX_FREQ_OFFSET	= 0,
	PTP_PLL_FREQ_OFFSET_CURRENT_FREQ_OFFSET = 1,
}mmApiCurrentMasterSubBlockFreqOffsetParams;


ToPSyncConfigResult mmApiSetCurrentMasterConfig(uint32 currentMasterIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetCurrentMasterConfig(uint32 currentMasterIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
