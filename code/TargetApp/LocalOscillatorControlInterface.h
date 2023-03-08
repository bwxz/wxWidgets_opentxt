/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: LocalOscillatorControlInterface.h $
 * $Revision: 1 $
 * $Date: 4/11/08 12:16 $
 */

/**
 * \file LocalOscillatorControlInterface.h
 * This file contains function declarations for configuring the local oscillator
 * parameters.
 */

#ifndef LOCAL_OSCILLATOR_CONTROL_INTERFACE_H
#define LOCAL_OSCILLATOR_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "TimeReferenceSourceControlInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetLocalOscillatorType(LocalOscillatorType localOscillatorType);
ToPSyncConfigResult DoGetLocalOscillatorType(LocalOscillatorType *localOscillatorType);
ToPSyncConfigResult DoSetLocalOscillatorStratumLevel(ClockStratum stratumLevel);
ToPSyncConfigResult DoGetLocalOscillatorStratumLevel(ClockStratum *stratumLevel);
ToPSyncConfigResult DoSetLocalOscillatorPhaseNoisePairs(uint16 noOfValues, const PhaseNoisePairs phaseNoisePairs);
ToPSyncConfigResult DoGetLocalOscillatorPhaseNoisePairs(uint16 *noOfValues, PhaseNoisePairs phaseNoisePairs);

ToPSyncConfigResult mmApiGetLocalOscillatorConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetLocalOscillatorConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

#define MAX_FREQ_OFFSET 0.0001

//SUBBLOCKSDEF:MMAPI_LOCAL_OSCILLATOR_PARAMS
typedef enum
{
	LOCAL_OSCILLATOR_PARAMS_SUBBLOCK_REFCLOCK = 0,	/* Local Oscillator Reference Clock*/
	LOCAL_OSCILLATOR_PARAMS_SUBBLOCK_CONFIG   = 1,	/* Local Oscillator Configuration */
}mmApiLocalOscillatorSubBlock;

//PARAMETERSDEF:LOCAL_OSCILLATOR_PARAMS_SUBBLOCK_REFCLOCK
/*
	+ LOCAL_OSCILLATOR_REFCLOCK_NODE_ID_1, Node ID bytes 0-3, rw, 0
	Bits[31:24] Node ID byte 0 (Most significant byte of the 8-byte node ID)
	Bits[23:16] Node ID byte 1
	Bits[15:8]  Node ID byte 2
	Bits[7:0]   Node ID byte 3

	+ LOCAL_OSCILLATOR_REFCLOCK_NODE_ID_2, Node ID bytes 4-7, rw, 0
	Bits[31:24] Node ID byte 4
	Bits[23:16] Node ID byte 5
	Bits[15:8]  Node ID byte 6
	Bits[7:0]   Node ID byte 7 (Least significant byte of the 8-byte node ID)

	+ LOCAL_OSCILLATOR_REFCLOCK_CLOCK_CLASS, Clock Class, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  IEEE1588 Clock class values

	+ LOCAL_OSCILLATOR_REFCLOCK_TIME_SOURCE, Time Source, rw, 0
	Bits[31:3] Reserved
	Bits[2:0]  Time source. Allowed values
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

	+ LOCAL_OSCILLATOR_REFCLOCK_CLOCK_ACCURACY, Clock Accuracy, rw, 0
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

	+ LOCAL_OSCILLATOR_REFCLOCK_OFFSET_LOG_VARIANCE, Offset scaled log variance, rw, 0
	Bits[31:16] Reserved
	Bits[15:0]  IEEE1588 Offset scaled log variance defined in 1588 v2 7.6.3.3

	+ LOCAL_OSCILLATOR_REFCLOCK_TIME_VALID, Time valid, rw, 0
	Bits[31:1] Reserved
	Bits[0]    1 - The time is a valid TAI time, 0 otherwise

	+ LOCAL_OSCILLATOR_REFCLOCK_PRIORITY1, Priority 1 value, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ LOCAL_OSCILLATOR_REFCLOCK_PRIORITY2, Priority 2 value, rw, 0
	Bits[31:8] Reserved
	Bits[7:0]  Priority 1 value

	+ LOCAL_OSCILLATOR_REFCLOCK_STEPS_REMOVED, Steps removed value, rw, 0
	Bits[31:16] Reserved
	Bits[15:0]  Steps removed value
*/
typedef enum
{
	LOCAL_OSCILLATOR_REFCLOCK_NODE_ID_1	   			= TRSOURCE_CONFIG_PARAMS_NODE_ID_1,
	LOCAL_OSCILLATOR_REFCLOCK_NODE_ID_2	   			= TRSOURCE_CONFIG_PARAMS_NODE_ID_2,
	LOCAL_OSCILLATOR_REFCLOCK_CLOCK_CLASS	   		= TRSOURCE_CONFIG_PARAMS_CLOCK_CLASS,
	LOCAL_OSCILLATOR_REFCLOCK_TIME_SOURCE	   		= TRSOURCE_CONFIG_PARAMS_TIME_SOURCE,
	LOCAL_OSCILLATOR_REFCLOCK_CLOCK_ACCURACY	   	= TRSOURCE_CONFIG_PARAMS_CLOCK_ACCURACY,
	LOCAL_OSCILLATOR_REFCLOCK_OFFSET_LOG_VARIANCE 	= TRSOURCE_CONFIG_PARAMS_OFFSET_LOG_VARIANCE,
	LOCAL_OSCILLATOR_REFCLOCK_TIME_VALID	   		= TRSOURCE_CONFIG_PARAMS_TIME_VALID,
	LOCAL_OSCILLATOR_REFCLOCK_PRIORITY1	   			= TRSOURCE_CONFIG_PARAMS_PRIORITY1,
	LOCAL_OSCILLATOR_REFCLOCK_PRIORITY2	   			= TRSOURCE_CONFIG_PARAMS_PRIORITY2,
	LOCAL_OSCILLATOR_REFCLOCK_STEPS_REMOVED			= TRSOURCE_CONFIG_PARAMS_STEPS_REMOVED
}mmApiLocalOscillatorSubBlockRefClockParams;

//PARAMETERSDEF:LOCAL_OSCILLATOR_PARAMS_SUBBLOCK_CONFIG
/*
	+ LOCAL_OSCILLATOR_CONFIG_FREQ_OFFSET, Local Oscillator frequency offset, rw, 0
	Bits[31:0] = Applied frequency offset in Hz expressed as a single precision floating point number.
	The maximum value for this is +-0.0001
	This register is provided for oscillator calibration.
*/
typedef enum
{
	LOCAL_OSCILLATOR_CONFIG_FREQ_OFFSET	   		= 0
}mmApiLocalOscillatorSubBlockConfigParams;

#ifdef __cplusplus
}
#endif

#endif

