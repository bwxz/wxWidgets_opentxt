/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: ClockLockerControlInterface.h $
 * $Revision: 1 $
 * $Date: 20/06/07 15:35 $
 */

/**
 * \file ClockLockerControlInterface.h
 * This file contains declarations for the Clock Locker Control Interface
 * routines.
 */


#ifndef CLOCK_LOCKER_CONTROL_INTERFACE_H
#define CLOCK_LOCKER_CONTROL_INTERFACE_H

#include "General.h"
#include "TimeReferenceSourceControlInterface.h"
#include "HoldoverControllerControlInterface.h"
#include "BinaryLockMonitorControlInterface.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * MMAPI_CLOCK_LOCKER#n#_PLL_PARAMS Block Description
 * - Subblocks defined by mmApiNodeTimeSubBlock enum
 * - individual parameters defined by mmApiClockOutputsSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_CLOCK_PLL1_PARAMS
//SUBBLOCKSDEF:MMAPI_CLOCK_PLL2_PARAMS
typedef enum
{
	CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_STATUS  		= 0,   /* Source status params */
	CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_CONFIG  		= 1,   /* Source config params */
	CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_REFCLOCK 		= 2,   /* Source reference params */
	CLOCK_PLL_PARAMS_SUBBLOCK_UTC_OFFSET 			= 3,   /* UTC Offset */
	CLOCK_PLL_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG		= 4,   /* Holdover controller config */
	CLOCK_PLL_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG		= 5,   /* BinaryLockMonitor config */
	CLOCK_PLL_PARAMS_SUBBLOCK_FREQ_OFFSET			= 6,   /* Frequency offset */

	CLOCK_PLL_PARAMS_SUBBLOCK_INPUT_CONFIG 				= 32,	/* Input configuration */

	CLOCK_PLL_PARAMS_SUBBLOCK_END
} mmApiClockLockerSubBlock;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_STATUS
/*
	+ CLOCK_PLL_STATUS_PARAMS_SOURCE_STATE, Source state, ro, 0
	Bits[31:3] reserved
	Bits[2:0]  Source state.  Valid values:
			0		void. Empty
			1 		invalid. No time is available.
			2 		valid. Time is available but the source has not been selected.
			3		measuring. The source has been selected and is measuring freq or phase offset.
			4		holdover. The source has lost lock and is currently in holdover.
			5		running. The source is providing time information.

	+ CLOCK_PLL_STATUS_PARAMS_PHASE_LAG_ERROR, Source phase lag error, ro, -
	Bits[31:0]	Phase lag error expressed as a single precision floating point number

	+ CLOCK_PLL_STATUS_PARAMS_MEASURED_NOISE, Source measured noise, ro, -
	Bits[31:0]	Measured noise expressed as a single precision floating point number

	+ CLOCK_PLL_STATUS_PARAMS_HOLDOVER_VALIDITY, Source holdover validity, ro, -
	Bits[31:0]	Holdover validity expressed as a single precision floating point number

	+ CLOCK_PLL_STATUS_PARAMS_LOCK_VALUE, Source lock value, ro, -
	Bits[31:0]	Lock value expressed as a single precision floating point number
				Range 0.0 to 1.0

	+ CLOCK_PLL_STATUS_PARAMS_LOCKED_STATE, Source locked state, ro, 0
	Bits[31:1]	Reserved
	Bits[0]		0 - not locked, 1 - locked

	+ CLOCK_PLL_STATUS_PARAMS_PHASE_ERROR_GRADIENT, Phase error gradient, ro, -
	Bits[31:0]	Phase error gradient expressed as a single precision floating point number
	This equals the frequency error of the Clock PLL with respect to its time source.

	+ CLOCK_PLL_STATUS_PARAMS_SOURCE_TYPE, Source type, ro, -
	Bits[31:2] Reserved
	Bits[1:0]  0 = Clock, 1 = Normal PTP, 2 = Hybrid PTP.

	+ CLOCK_PLL_STATUS_PARAMS_TIME_SEC, Clock PLL time seconds bits 31 to 0, ro, -
	Bits[31:0] = Clock PLL time seconds bits 31 to 0 of 48 bit seconds field
	Note: This parameter is consistent with the other Clock PLL time registers if read in the same api message

	+ CLOCK_PLL_STATUS_PARAMS_TIME_NSEC, Clock PLL time nanoseconds, ro, -
	Bits[31:0] = Clock PLL time nanoseconds
	Note: This parameter is consistent with the other Clock PLL time registers if read in the same api message

	+ CLOCK_PLL_STATUS_PARAMS_TIME_SEC_MSB, Clock PLL time secs bits 47 to 32, ro, -
	Bits[31:16] = reserved
	Bits[15:0]  = Clock PLL time seconds bits 47 to 32 of 48 bit seconds field
	Note: This parameter is consistent with the other Clock PLL time registers if read in the same api message

	+ CLOCK_PLL_STATUS_PARAMS_TIME_IS_TAI, Clock PLL time TAI flag, ro, -
	Bits[31:1] = reserved
	Bits[0]    = 1 is TAI flag is TRUE, 0 if FALSE
	Note: This parameter is consistent with the other Clock PLL time registers if read in the same api message

	+ CLOCK_PLL_STATUS_PARAMS_CLOCK_CLASS, Current value of input source Clock Class, ro, -
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock class values
	Note that this may not be the same as %CLOCK_PLL_CONFIG_PARAMS_CLOCK_CLASS% if the source is in holdover.

*/

typedef enum
{
	CLOCK_PLL_STATUS_PARAMS_SOURCE_STATE       	= TRSOURCE_STATUS_PARAMS_STATE,
	CLOCK_PLL_STATUS_PARAMS_PHASE_LAG_ERROR    	= TRSOURCE_STATUS_PARAMS_PHASE_LAG_ERROR,
	CLOCK_PLL_STATUS_PARAMS_MEASURED_NOISE	    = TRSOURCE_STATUS_PARAMS_MEASURED_NOISE,
	CLOCK_PLL_STATUS_PARAMS_HOLDOVER_VALIDITY 	= TRSOURCE_STATUS_PARAMS_HOLDOVER_VALIDITY,
	CLOCK_PLL_STATUS_PARAMS_LOCK_VALUE 			= TRSOURCE_STATUS_PARAMS_LOCK_VALUE,
	CLOCK_PLL_STATUS_PARAMS_LOCKED_STATE		= TRSOURCE_STATUS_PARAMS_LOCKED_STATE,
	CLOCK_PLL_STATUS_PARAMS_PHASE_ERROR_GRADIENT = TRSOURCE_STATUS_PARAMS_PHASE_ERROR_GRADIENT,
	CLOCK_PLL_STATUS_PARAMS_SOURCE_TYPE			 = TRSOURCE_STATUS_PARAMS_SOURCE_TYPE,

	CLOCK_PLL_STATUS_PARAMS_TIME_SEC_MSB  			= TRSOURCE_STATUS_PARAMS_TIME_SEC_MSB,
	CLOCK_PLL_STATUS_PARAMS_TIME_SEC    			= TRSOURCE_STATUS_PARAMS_TIME_SEC,
	CLOCK_PLL_STATUS_PARAMS_TIME_NSEC   			= TRSOURCE_STATUS_PARAMS_TIME_NSEC,
	CLOCK_PLL_STATUS_PARAMS_TIME_IS_TAI 			= TRSOURCE_STATUS_PARAMS_TIME_IS_TAI,

	CLOCK_PLL_STATUS_PARAMS_CLOCK_CLASS 			= TRSOURCE_STATUS_PARAMS_CLOCK_CLASS
}mmApiClockLockerSubBlockSourceStatusParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_CONFIG
/*
	+ CLOCK_PLL_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH, Clock PLL Unlocked Bandwidth, rw, -
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	+ CLOCK_PLL_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH, Clock PLL Locked Bandwidth, rw, -
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	+ CLOCK_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION, Frequency Measurement Duration, rw, 10
	Bits[31:16] Reserved
	Bits[15:0]  Duration of the initial frequency measurement period in seconds

	+ CLOCK_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES, Frequency Measurement Minimum Samples, rw, 0
	Bits[31:16] Reserved
	Bits[15:0]  The minimum number of samples to be used in the initial frequency measurement period.

	+ CLOCK_PLL_CONFIG_PARAMS_CONFIGURED_PHASE_LAG, Configured phase lag, rw, 0.0
	Bits[31:0] Configured phase lag in seconds expressed as a single precision floating point number

	+ CLOCK_PLL_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER, Minimum lock value to be master, rw, 0.1
	Bits[31:0] Lock value expressed as a single precision floating point number
	The minimum lock value for an input source used as a time reference on a PTP port for the port to enter master state

	+ CLOCK_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1, Phase buildout property for node time 1, rw, 0
	Bits[31:2] Reserved
	Bits[1:0]	0 = Is not aligned, 1 = Is frequency aligned, 2 = Is phase aligned
	Note the default value is different for PTP source and Clock source.

	+ CLOCK_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2, Phase buildout property for node time 2, rw, 0
	Bits[31:2] Reserved
	Bits[1:0]	0 = Is not aligned, 1 = Is frequency aligned, 2 = Is phase aligned
	Note the default value is different for PTP source and Clock source.

	- CLOCK_PLL_PARAMS_UNLOCKED_PLL_BANDWIDTH_DEBUG, Clock PLL Unlocked Bandwidth, rw, -
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_LOCKED_PLL_BANDWIDTH_DEBUG, Clock PLL Locked Bandwidth, rw, -
	Bits[31:0] Bandwidth in Hz expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_UNLOCKED_PLL_PROPORTIONAL_GAIN_DEBUG, Clock PLL Unlocked Proportional Gain, rw, -
	Bits[31:0] Gain expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_LOCKED_PLL_PROPORTIONAL_GAIN_DEBUG, Clock PLL Locked Proportional Gain, rw, -
	Bits[31:0] Gain expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_UNLOCKED_PLL_INTEGRAL_GAIN_DEBUG, Clock PLL Unlocked Integral Gain, rw, -
	Bits[31:0] Gain expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_LOCKED_PLL_INTEGRAL_GAIN_DEBUG, Clock PLL Locked Integral Gain, rw, -
	Bits[31:0] Gain expressed as a single precision floating point number

	- CLOCK_PLL_PARAMS_APPLY_SETTINGS_DEBUG, Apply debug bandwidth and gain settings, rw, -
	Bits[31:0] Non zero value will apply the above bandwidth and gain settings


*/
typedef enum
{
	CLOCK_PLL_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH = TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH,
	CLOCK_PLL_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH	  = TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH,

	CLOCK_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION		= TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_DURATION,
	CLOCK_PLL_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES 	= TRSOURCE_CONFIG_PARAMS_FREQ_MEASUREMENT_MIN_SAMPLES,

	CLOCK_PLL_CONFIG_PARAMS_CONFIGURED_PHASE_LAG		= TRSOURCE_CONFIG_PARAMS_CONFIGURED_PHASE_LAG,

	CLOCK_PLL_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER		= TRSOURCE_CONFIG_PARAMS_LOCK_MIN_VALUE_TO_BE_MASTER,

	CLOCK_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1	= TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_1,
	CLOCK_PLL_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2	= TRSOURCE_CONFIG_PARAMS_PHASE_BUILD_OUT_PROPERTY_FOR_NODE_TIME_2,

	CLOCK_PLL_PARAMS_UNLOCKED_PLL_BANDWIDTH_DEBUG         = TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_BANDWIDTH_DEBUG,
	CLOCK_PLL_PARAMS_LOCKED_PLL_BANDWIDTH_DEBUG           = TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_BANDWIDTH_DEBUG,
	CLOCK_PLL_PARAMS_UNLOCKED_PLL_PROPORTIONAL_GAIN_DEBUG = TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_PROPORTIONAL_GAIN_DEBUG,
	CLOCK_PLL_PARAMS_LOCKED_PLL_PROPORTIONAL_GAIN_DEBUG   = TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_PROPORTIONAL_GAIN_DEBUG,
	CLOCK_PLL_PARAMS_UNLOCKED_PLL_INTEGRAL_GAIN_DEBUG     = TRSOURCE_CONFIG_PARAMS_UNLOCKED_PLL_INTEGRAL_GAIN_DEBUG,
	CLOCK_PLL_PARAMS_LOCKED_PLL_INTEGRAL_GAIN_DEBUG	      = TRSOURCE_CONFIG_PARAMS_LOCKED_PLL_INTEGRAL_GAIN_DEBUG,
	CLOCK_PLL_PARAMS_APPLY_SETTINGS_DEBUG                 = TRSOURCE_CONFIG_PARAMS_APPLY_SETTINGS_DEBUG,

}mmApiClockLockerSubBlockSourceConfigParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_SOURCE_REFCLOCK
/*
	+ CLOCK_PLL_CONFIG_PARAMS_NODE_ID_1, Node ID bytes 0-3, rw, 0
	Bits[31:24] Node ID byte 0
	Bits[23:16] Node ID byte 1
	Bits[15:8]  Node ID byte 2
	Bits[7:0]   Node ID byte 3

	+ CLOCK_PLL_CONFIG_PARAMS_NODE_ID_2, Node ID bytes 4-7, rw, 0
	Bits[31:24] Node ID byte 4
	Bits[23:16] Node ID byte 5
	Bits[15:8]  Node ID byte 6
	Bits[7:0]   Node ID byte 7

	+ CLOCK_PLL_CONFIG_PARAMS_CLOCK_CLASS, Clock Class, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock class values

	+ CLOCK_PLL_CONFIG_PARAMS_TIME_SOURCE, Time Source, rw, 0
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


	+ CLOCK_PLL_CONFIG_PARAMS_CLOCK_ACCURACY, Clock Accuracy, rw, 0
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

	+ CLOCK_PLL_CONFIG_PARAMS_OFFSET_LOG_VARIANCE, Offset scaled log variance, rw, 0
	Bits[31:16] Reserved
	Bits[15:0]  IEEE1588 Offset scaled log variance defined in 1588 v2 7.6.3.3

	+ CLOCK_PLL_CONFIG_PARAMS_TIME_VALID, Time valid, rw, 0
	Bits[31:1] Reserved
	Bits[0]    1 - The time is a valid TAI time, 0 otherwise

	+ CLOCK_PLL_CONFIG_PARAMS_PRIORITY1, Priority 1 value, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ CLOCK_PLL_CONFIG_PARAMS_PRIORITY2, Priority 2 value, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ CLOCK_PLL_CONFIG_PARAMS_STEPS_REMOVED, Steps removed value, rw, 0
	Bits[31:16] Reserved
	Bits[15:0]  Steps removed value
*/
typedef enum
{
	CLOCK_PLL_CONFIG_PARAMS_NODE_ID_1	   		= TRSOURCE_CONFIG_PARAMS_NODE_ID_1,
	CLOCK_PLL_CONFIG_PARAMS_NODE_ID_2	   		= TRSOURCE_CONFIG_PARAMS_NODE_ID_2,
	CLOCK_PLL_CONFIG_PARAMS_CLOCK_CLASS	   		= TRSOURCE_CONFIG_PARAMS_CLOCK_CLASS,
	CLOCK_PLL_CONFIG_PARAMS_TIME_SOURCE	   		= TRSOURCE_CONFIG_PARAMS_TIME_SOURCE,
	CLOCK_PLL_CONFIG_PARAMS_CLOCK_ACCURACY	   	= TRSOURCE_CONFIG_PARAMS_CLOCK_ACCURACY,
	CLOCK_PLL_CONFIG_PARAMS_OFFSET_LOG_VARIANCE	= TRSOURCE_CONFIG_PARAMS_OFFSET_LOG_VARIANCE,
	CLOCK_PLL_CONFIG_PARAMS_TIME_VALID	   		= TRSOURCE_CONFIG_PARAMS_TIME_VALID,
	CLOCK_PLL_CONFIG_PARAMS_PRIORITY1	   		= TRSOURCE_CONFIG_PARAMS_PRIORITY1,
	CLOCK_PLL_CONFIG_PARAMS_PRIORITY2	   		= TRSOURCE_CONFIG_PARAMS_PRIORITY2,
	CLOCK_PLL_CONFIG_PARAMS_STEPS_REMOVED  		= TRSOURCE_CONFIG_PARAMS_STEPS_REMOVED
}mmApiClockLockerSubBlockSourceRefClockParams;


//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_UTC_OFFSET
/*
	+ CLOCK_PLL_PARAMS_UTC_OFFSET_VALUE, UTC Offset Value, rw, 0
	Bits[31:0]  UTC Offset value as a signed integer. Valid range covers bits 15:0 only

	+ CLOCK_PLL_PARAMS_UTC_OFFSET_VALID, UTC Offset Value, rw, 0
	Bits[31:1] Reserved
	Bits[0]    1 UTC Offset value is valid, 0 UTC Offset value is invalid

	+ CLOCK_PLL_PARAMS_LEAP_SECOND_DAYS, Days to leap second, rw, 0
	Bits[31:0]  Number of days as a signed integer. Valid range covers bits 15:0 only
		If leap second will happen at the next midnight (UTC time) number of days = 0.
		If leap second will happen at tomorrow's midnight (UTC time) number of days = 1.
		Number of days must not be greater than MAX_WARNING_DAYS.
		Setting this value to <0 will clear any pending leap second and reset the
		"Leap second is positive" register (below) to zero.

	+ CLOCK_PLL_PARAMS_LEAP_SECOND_POSITIVE, Leap second is positive, rw, 0
	Bits[31:1] Reserved
	Bits[0]    1 leap second jump is positive, 0 leap second jump is negative
		Note this register can only be updated if  "Days to leap second" register (above) is >= 0

*/
typedef enum
{
	CLOCK_PLL_PARAMS_UTC_OFFSET_VALUE		= TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALUE,
	CLOCK_PLL_PARAMS_UTC_OFFSET_VALID		= TRSOURCE_UTCOFFSET_PARAMS_UTC_OFFSET_VALID,
	CLOCK_PLL_PARAMS_LEAP_SECOND_DAYS		= TRSOURCE_LEAP_SECOND_PARAMS_DAYS,
	CLOCK_PLL_PARAMS_LEAP_SECOND_POSITIVE	= TRSOURCE_LEAP_SECOND_PARAMS_POSITIVE
}mmApiClockLockerSubBlockUtcOffsetParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG
/*
	+ CLOCK_PLL_PARAMS_HOLDOVER_DURATION, Duration value, rw, 0
	Bits[31:0]  Duration value as a unsigned integer.

	+ CLOCK_PLL_PARAMS_HOLDOVER_RESET, Reset, w0, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= any value.
				Notes: This resets the holdover data used to maintain effective holdover in the absence
				of an input source.  It does not force the PLL to exit the holdover state and should not
				be used when the PLL is in holdover

	+ CLOCK_PLL_PARAMS_FORCE_HOLDOVER, Disable/enable forceHoldover, rw, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= 1 - ForceHoldover enabled, 0 - disabled

	+ CLOCK_PLL_PARAMS_HOLDOVER_CLASS, clock class on entering holdover, rw, 14
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value on entering holdover

	+ CLOCK_PLL_PARAMS_REDUCED_HOLDOVER_CLASS, clock class after holdover duration, rw, 193
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value after the holdover duration has expired

*/
typedef enum
{
	CLOCK_PLL_PARAMS_HOLDOVER_DURATION		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_DURATION,
	CLOCK_PLL_PARAMS_HOLDOVER_RESET			= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_RESET,
	CLOCK_PLL_PARAMS_FORCE_HOLDOVER			= HOLDOVER_CONTROLLER_PARAMS_FORCE_HOLDOVER,
	CLOCK_PLL_PARAMS_HOLDOVER_CLASS			= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_CLOCK_CLASS,
	CLOCK_PLL_PARAMS_REDUCED_HOLDOVER_CLASS	= HOLDOVER_CONTROLLER_PARAMS_REDUCED_HOLDOVER_CLOCK_CLASS
}mmApiClockLockerSubBlockHoldoverParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG
/*
	+ CLOCK_PLL_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE, Binary error acceptable, rw, 1.0e-6
	Bits[31:0]  value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE, Binary error unacceptable, rw, 5.0e-6
	Bits[31:0] 	value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE, Binary error gradient acceptable, rw, 1.0e-9
	Bits[31:0]  value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE, Binary error gradient unacceptable, rw, 2.5e-9
	Bits[31:0] 	value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE, Binary fuzzy lock acceptable, rw, 0.5
	Bits[31:0]  value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE, Binary fuzzy lock unacceptable, rw, 0.25
	Bits[31:0] 	value as a float value.

	+ CLOCK_PLL_PARAMS_BLM_FORCE_LOCK, Binary force lock, rw, 0
	Bits[31:2]  reserved.
	Bits[1:0]	2 = Forced to UnLocked State, 1 = Forced to Locked State, 0 = Not Forced 

	+ CLOCK_PLL_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH, Binary maintain lock during source switch, rw, 0
	Bits[31:1]  reserved.
	Bits[0]		1 = Maintain Lock, 0 = Not Maintain Lock

	- CLOCK_PLL_PARAMS_BLM_FILTER_BANDWIDTH_UNLOCKED, Binary lock monitor filter bandwidth (Unlocked), rw, 7.5e-2
	Bits[31:0] 	value as a float value.

	- CLOCK_PLL_PARAMS_BLM_FILTER_BANDWIDTH_LOCKED, Binary lock monitor filter bandwidth (Locked), rw, 7.5e-2
	Bits[31:0] 	value as a float value.

*/
typedef enum
{
	CLOCK_PLL_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_ACCEPTABLE,
	CLOCK_PLL_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE 			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_UNACCEPTABLE,
	CLOCK_PLL_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_ACCEPTABLE,
	CLOCK_PLL_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_UNACCEPTABLE,
	CLOCK_PLL_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_ACCEPTABLE,
	CLOCK_PLL_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE  			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_UNACCEPTABLE,

	CLOCK_PLL_PARAMS_BLM_FORCE_LOCK							= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FORCE_LOCK,
	CLOCK_PLL_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH = BINARY_LOCK_MONITOR_CONFIG_PARAMS_MAINTAIN_LOCK_DURING_SOURCE_SWITCH,

	CLOCK_PLL_PARAMS_BLM_FILTER_BANDWIDTH_UNLOCKED    		= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_UNLOCKED,
	CLOCK_PLL_PARAMS_BLM_FILTER_BANDWIDTH_LOCKED 			= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_LOCKED,

}mmApiClockLockerSubBlockBinaryLockMonitorParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_INPUT_CONFIG
/*
    + CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_SRC_ENABLE, Bitmask to enable clock inputs, rw, 0x1
      Bits[31:8]  = Reserved
      Bits[7:0]   = A bit mask where '1' indicates enabled, and '0' indicates disabled. Bits 0-3 are mux inputs 0-3 /
                    respectively and bits 4-7 are ipclk inputs 4-7 respectively.
         Notes: A source can only be enabled if it's frequency is non-zero.

    + CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_SRC_SELECT, Select an input clock, rw, 0x1
      Bits[31:0]  = Value selecting the input clock source. 0-3 selects mux inputs 0-3 respectively and 4-7 selects /
                    ipclk inputs 4-7 respectively.
					0 - MUX input 0 is selected
					1 - MUX input 1 is selected
					2 - MUX input 2 is selected
					3 - MUX input 3 is selected
					4 - IPCLK input 4 is selected
					5 - IPCLK input 5 is selected
					6 - IPCLK input 6 is selected
					7 - IPCLK input 7 is selected
         Notes: A source can only be selected if it's frequency is non-zero and it is enabled.

	+ CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SECONDS_BYTES_0_3, Used to set the seconds of the most recent clock edge, rw, 0
	  Bits[31:0]  = The least significant 4 bytes of the seconds count of the most recent clock edge with the least /
	                significant byte in bits[7:0]. The register contents do not take effect until register /
	                %CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SET% is written to and are ignored unless the /
	                selected input frequency is 1Hz.

	+ CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SECONDS_BYTES_4_5, Used to set the seconds of the most recent clock edge, rw, 0
	  Bits[31:16] = Must be set to zero
	  Bits[15:0]  = The most significant 2 bytes of the seconds count of the most recent clock edge with the most /
	                significant byte in bits[15:8]. The register contents do not take effect until register /
	                %CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SET% is written to and are ignored unless the /
	                selected input frequency is 1Hz.

	+ CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_NANOSECONDS, Used to set the nanoseconds of the most recent clock edge, rw, 0
	  Bits[31:0]  = Nanoseconds portion of the time of most the recent clock edge. The register contents do not take /
	                effect until register %CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SET% is written to and are /
	                ignored unless the selected input frequency is 1Hz.

	+ CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SET, Used to set the time of the most recent clock edge, rw, 0
	  The time scale used to interpret the time of the most recent edge. Writing to this register causes /
	  the contents of the seconds and nanoseconds registers to be read by ToPSync and applied as the time for the most /
	  recent clock edge, interpreted using the time scale (GPS or TAI) as written to this register. Ignored unless the /
	  selected input frequency is 1Hz.
	  Bits[31:0]  = 0x0 => UTC,
	                0x1 => TAI,
	                0x2 => GPS
	                0x3 => ARB

    + CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_VALID_THRESHOLD, TOD input message threshold, rw, 2
	  Bits[31:8] = reserved
	  Bits[7:0]  = Threshold
	  ToPSync must receive a sequence of 'Threshold' TOD messages before it accepts the input as valid.
	  A value of zero means that a single message is accepted as valid.

 */
typedef enum
{
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_SRC_ENABLE                        = 0,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_SRC_SELECT                        = 1,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SECONDS_BYTES_4_5 = 2,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SECONDS_BYTES_0_3 = 3,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_NANOSECONDS       = 4,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_SOURCE_TIME_SET               = 5,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_TOD_VALID_THRESHOLD               = 8,
	CLOCK_PLL_INPUT_CONFIG_SUBBLOCK_NUM_PARAMS
} mmApiClockLockerSubBlockConfigParams;

//PARAMETERSDEF:CLOCK_PLL_PARAMS_SUBBLOCK_FREQ_OFFSET
/*
	+ CLOCK_PLL_FREQ_OFFSET_MAX_FREQ_OFFSET, Clock PLL max frequency offset, rw, 0
	Bits[31:0] Max frequency offset in Hz expressed as a single precision floating point number
	Value in Hz

	+ CLOCK_PLL_FREQ_OFFSET_CURRENT_VALUE, Clock PLL current frequency offset, ro, 0
	Bits[31:0] 	= Current frequency offset in Hz expressed as a single precision floating point number
	This register is provided for oscillator calibration.

*/
typedef enum
{
	CLOCK_PLL_FREQ_OFFSET_MAX_FREQ_OFFSET	= 0,
	CLOCK_PLL_FREQ_OFFSET_CURRENT_VALUE 	= 1,
}mmApiClockLockerSubBlockFreqOffsetParams;

ToPSyncConfigResult mmApiSetClockLockerPllConfig(uint32 clockLockerIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetClockLockerPllConfig(uint32 clockLockerIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif
