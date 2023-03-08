/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: DelayMonitorControlInterface.h $
 * $Revision: 6 $
 * $Date: 3/03/09 12:08 $
 */

/**
 * \file DelayMonitorControlInterface.h
 * This file contains the declarations of the handler routines for the Delay Monitor
 * control message set. These are messages for the configuration and management of the
 * BinaryLockMonitor.
 */

#ifndef DELAY_MONITOR_CONTROL_INTERFACE_H
#define DELAY_MONITOR_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "DelayMonitor.h"

#ifdef __cplusplus
extern "C" {
#endif

//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_DELAY_MONITOR_CONFIG
/*
    + DELAY_MONITOR_ENABLE_DELAY_PRINTING_PTP_PLL1, Enable printing out delay measurement result PTP PLL1, rw, 0
      Bits[31:1] = Reserved
      Bit[0] = 1 - enabled, 0 - not enabled

    + DELAY_MONITOR_GET_DELAY_PRINTING_STATE_PTP_PLL1, Get delay measurement state PTP PLL1, ro, -
      Bits[31:0] = 32-bit unsigned integer state value. Valid values:
	  0 = noSelectedSource.
	  1 = no1HzInputDetected.
	  2 = calibratingTo1HzInput.
	  3 = sourceDataNotValid.
	  4 = masterInvisible.
	  5 = masterInvalid.
	  6 = masterValidating.
	  7 = masterTooFewTimingMessages.
	  8 = masterNotOfInterest.
	  9 = masterRequestingContract.
	  10 = aligningTo1Hz.
	  11 = notPrinting.
	  12 = printingDelays. 
	  Other = reserved.

    + DELAY_MONITOR_ENABLE_PTP_ERROR_MEASURING_PTP_PLL1, Enable PTP phase error counter PTP PLL1, rw, 0
      Bits[31:1] = Reserved
      Bit[0] = 1 - enabled, 0 - not enabled

	+ DELAY_MONITOR_INPUT_REFERENCE_CLOCK_FOR_PTP_PLL1, Specify Reference Clock ID for PTP PLL1, rw, 2
	  Bits[31:2] = reserved
	  Bits[1:0] = 0 - Input Clock PLL1, 1 - Input Clock PLL2, 2 - No Reference Clock Specified
	  Notes: When no reference clock is specified, the device will automatically use the available clock (either Clock PLL1 or Clock PLL2) as reference. The reference clock must be 1pps clock.

	+ DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_PTP_PLL1, Get the phase difference of PTP PLL1 against Reference Clock, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (PTP PLL1 - Reference Clock). 

	+ DELAY_MONITOR_GET_PHASE_DIFF_PTP_PLL1_VS_PTP_PLL2, Get the phase difference of PTP PLL1 against PTP PLL2, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (PTP PLL1 - PTP PLL2). 

	+ DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_NODE_TIME1, Get the phase difference of NodeTime1 against Reference Clock, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (NodeTime1 - Reference Clock). 

	+ DELAY_MONITOR_GET_PHASE_DIFF_CLOCK_PLL1_VS_CLOCK_PLL2, Get the phase difference of Clock PLL2 against Clock PLL1, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (Clock PLL2 - Clock PLL1). 

    + DELAY_MONITOR_ENABLE_DELAY_PRINTING_PTP_PLL2, Enable printing out delay measurement result PTP PLL2, rw, 0
      Bits[31:1] = Reserved
      Bit[0] = 1 - enabled, 0 - not enabled

    + DELAY_MONITOR_GET_DELAY_PRINTING_STATE_PTP_PLL2, Get delay measurement state PTP PLL2, ro, -
      Bits[31:0] = 32-bit unsigned integer state value. Valid values:
	  0 = noSelectedSource.
	  1 = no1HzInputDetected.
	  2 = calibratingTo1HzInput.
	  3 = sourceDataNotValid.
	  4 = masterInvisible.
	  5 = masterInvalid.
	  6 = masterValidating.
	  7 = masterTooFewTimingMessages.
	  8 = masterNotOfInterest.
	  9 = masterRequestingContract.
	  10 = aligningTo1Hz.
	  11 = notPrinting.
	  12 = printingDelays. 
	  Other = reserved.

    + DELAY_MONITOR_ENABLE_PTP_ERROR_MEASURING_PTP_PLL2, Enable PTP phase error counter PTP PLL2, rw, 0
      Bits[31:1] = Reserved
      Bit[0] = 1 - enabled, 0 - not enabled

	+ DELAY_MONITOR_INPUT_REFERENCE_CLOCK_FOR_PTP_PLL2, Specify Reference Clock ID for PTP PLL2, rw, 2
	  Bits[31:2] = reserved
	  Bits[1:0] = 0 - Input Clock PLL1, 1 - Input Clock PLL2, 2 - No Reference Clock Specified
	  Notes: When no reference clock is specified, the device will automatically use the available clock (either Clock PLL1 or Clock PLL2) as reference. The reference clock must be 1pps clock.

	+ DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_PTP_PLL2, Get the phase difference of PTP PLL2 against Reference Clock, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (PTP PLL2 - Reference Clock).

	+ DELAY_MONITOR_GET_PHASE_DIFF_PTP_PLL2_VS_PTP_PLL1, Get the phase difference of PTP PLL2 against PTP PLL1, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (PTP PLL2 - PTP PLL1). 

	+ DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_NODE_TIME2, Get the phase difference of NodeTime2 against Reference Clock, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (NodeTime2 - Reference Clock). 

	+ DELAY_MONITOR_GET_PHASE_DIFF_CLOCK_PLL2_VS_CLOCK_PLL1, Get the phase difference of Clock PLL1 against Clock PLL2, ro, -
      Bits[31:0] = 32-bit float value
	  Notes: This returns the phase difference of (Clock PLL1 - Clock PLL2). 

*/
typedef enum
{
	DELAY_MONITOR_ENABLE_DELAY_PRINTING_PTP_PLL1					= 0,
	DELAY_MONITOR_GET_DELAY_PRINTING_STATE_PTP_PLL1 				= 1,
	DELAY_MONITOR_ENABLE_PTP_ERROR_MEASURING_PTP_PLL1				= 2,
	DELAY_MONITOR_INPUT_REFERENCE_CLOCK_FOR_PTP_PLL1				= 3,
	DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_PTP_PLL1		= 4,
	DELAY_MONITOR_GET_PHASE_DIFF_PTP_PLL1_VS_PTP_PLL2				= 5,
	DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_NODE_TIME1		= 6,
	DELAY_MONITOR_GET_PHASE_DIFF_CLOCK_PLL1_VS_CLOCK_PLL2			= 7,
	DELAY_MONITOR_ENABLE_DELAY_PRINTING_PTP_PLL2					= 16,
	DELAY_MONITOR_GET_DELAY_PRINTING_STATE_PTP_PLL2 				= 17,
	DELAY_MONITOR_ENABLE_PTP_ERROR_MEASURING_PTP_PLL2				= 18,
	DELAY_MONITOR_INPUT_REFERENCE_CLOCK_FOR_PTP_PLL2				= 19,
	DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_PTP_PLL2		= 20,
	DELAY_MONITOR_GET_PHASE_DIFF_PTP_PLL2_VS_PTP_PLL1				= 21,
	DELAY_MONITOR_GET_PHASE_DIFF_REFERENCE_CLOCK_VS_NODE_TIME2		= 22,
	DELAY_MONITOR_GET_PHASE_DIFF_CLOCK_PLL2_VS_CLOCK_PLL1			= 23

}mmApiDelayMonitorSubBlockEntryParams;

ToPSyncConfigResult mmAPIProcessSetDelayMonitorParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetDelayMonitorParams(uint16 startAddress, uint16 endAddress, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
