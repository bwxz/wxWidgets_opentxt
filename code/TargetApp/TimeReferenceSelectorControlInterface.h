/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: TimeReferenceSelectorControlInterface.h $
 * $Revision: 4 $
 * $Date: 8/04/09 15:42 $
 */

/**
 * \file TimeReferenceSelectorControlInterface.h
 * This file contains the declrations of the handler routines for the Time Reference Selector 
 * control message set. These are messages for the configuration and management of the Time 
 * Reference Selector.
 */

#ifndef TIME_REFERENCE_SELECTOR_CONTROL_INTERFACE_H
#define TIME_REFERENCE_SELECTOR_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "HoldoverControllerControlInterface.h"
#include "BinaryLockMonitorControlInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DoGetToPSyncTime(topSyncTime) DoGetToPSyncNodeTime(0,topSyncTime)

ToPSyncConfigResult DoGetSelectedTimeReferenceSource(TimeTransport* sourceType, uint8* id); /* paramters described in Time Reference Source section of this file */
ToPSyncConfigResult DoGetTimeReferenceSelectorStatistics(TimeReferenceSelectorStatistics *statistics);
ToPSyncConfigResult DoSetFrequencyControllerParameters(FrequencyControllerParameters const* frequencyControllerParameters);
ToPSyncConfigResult DoGetFrequencyControllerParameters(FrequencyControllerParameters *frequencyControllerParameters);
ToPSyncConfigResult DoSetLDThresholdMultiple(float multiple, Bool rising, Bool falling);
ToPSyncConfigResult DoGetLDThresholdMultiple(float* multiple, Bool rising, Bool falling);
ToPSyncConfigResult DoGetNodeUTCOffset(sint16 *offset);

ToPSyncConfigResult DoGetSelectedSourceBitMask(uint32 nodeTimeIndex,uint32* bitMask);

ToPSyncConfigResult DoSetInputEnableMask(uint32 nodeTimeIndex,uint32 enableMask);
ToPSyncConfigResult DoGetInputEnableMask(uint32 nodeTimeIndex,uint32* enableMask);

ToPSyncConfigResult DoGetToPSyncNodeTime(uint32 nodeTimeIndex, ToPSyncTime* topSyncTime);

#ifdef _SIMULATOR
ToPSyncConfigResult DoSetPacketAnalyserAlgorithm(PacketAnalyserAlgorithm paAlg);
#endif

/******************************************************************************
 * New functions for memory mapped API
 * Functionality subject to change
 ******************************************************************************/

/******************************************************************************
 * MMAPI_NODE_TIME_PARAMS Block Description
 * - Subblocks defined by mmApiNodeTimeSubBlock enum
 * - individual parameters defined by mmApiClockOutputsSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_NODE_TIME1_PARAMS
//SUBBLOCKSDEF:MMAPI_NODE_TIME2_PARAMS
typedef enum
{
	NODE_TIME_PARAMS_SUBBLOCK_STATUS     			= 0,   /* Node Time Status (RO) */
	NODE_TIME_PARAMS_SUBBLOCK_CONFIG     			= 1,   /* Node Time Config (RW) */
	NODE_TIME_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG	= 2,   /* Node Time Holdover Controller Config (RW) */
	NODE_TIME_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG 	= 3,   /* Node Time BinaryLockMonitor config */

	NODE_TIME_PARAMS_SUBBLOCK_END
} mmApiNodeTimeSubBlock;

//PARAMETERSDEF:NODE_TIME_PARAMS_SUBBLOCK_STATUS
/*
	+ NODE_TIME_STATUS_PARAMS_SELECTED_SOURCE, Source selected by node time as a bitmask, ro, 0
	  Bits[31:4] = Reserved
	  Bits[3:0] =
		  Permitted values:
		  1000 PTP PLL2 selected
		  0100 PTP PLL1 selected
		  0010 Clock PLL2 selected
		  0001 Clock PLL1 selected
		  0000 Local oscillator selected (no external source selected)

	+ NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC, Node time seconds bits 31 to 0, ro, -
	  Bits[31:0] = node time seconds bits 31 to 0 of 48 bit seconds field
	  Note: This parameter is consistent with the other node time registers if read in the same api message

	+ NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_NSEC, Node time nanoseconds, ro, -
	  Bits[31:0] = node time nanoseconds
	  Note: This parameter is consistent with the other node time registers if read in the same api message

	+ NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC_MSB, Node time secs bits 47 to 32, ro, -
	  Bits[31:16] = reserved
	  Bits[15:0]  = node time seconds bits 47 to 32 of 48 bit seconds field
	  Note: This parameter is consistent with the other node time registers if read in the same api message

	+ NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_IS_TAI, Node time TAI flag, ro, -
	  Bits[31:1] = reserved
	  Bits[0]    = 1 is TAI flag is TRUE, 0 if FALSE
	  Note: This parameter is consistent with the other node time registers if read in the same api message

*/

typedef enum
{
	NODE_TIME_STATUS_PARAMS_SELECTED_SOURCE		 	= 0,
    NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC_MSB  	= 1,
    NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC    	= 2,
    NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_NSEC   	= 3,
    NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_IS_TAI 	= 4

}mmApiNodeTimeSubBlockStatusParams;

//PARAMETERSDEF:NODE_TIME_PARAMS_SUBBLOCK_CONFIG
/*
    + NODE_TIME_CONFIG_PARAMS_INPUT_ENABLE, Enable inputs for selection by node time, rw, 1111B or 0000B
	  Bits[31:4] Reserved
	  Bits[3]    = 1 - enable PTP PLL2 input for selection, 0 - disable PTP PLL2 input
	  Bits[2]    = 1 - enable PTP PLL1 input for selection, 0 - disable PTP PLL1 input
	  Bits[1]    = 1 - enable Clock PLL2 input for selection, 0 - disable Clock PLL2 input
	  Bits[0]    = 1 - enable Clock PLL1 input for selection, 0 - disable Clock PLL1 input
	  Note: the default value for nodeTime 1 is 1111B and for nodeTime 2 is 0000B.

    + NODE_TIME_CONFIG_PARAMS_REVERTIVE, Enable NON-revertive Operation, rw, 0
	  Bits[31:1] Reserved
	  Bits[0]    = 1 - NON-revertive operation enabled, 0 - Revertive operation enable

    + NODE_TIME_CONFIG_PARAMS_ENABLE_PHASE_BUILD_OUT, Enable Phase Build Out, rw, 1
	  Bits[31:1] Reserved
	  Bits[0]    = 1 - Phase build out enabled, 0 - disabled

	+ NODE_TIME_CONFIG_PARAMS_PHASE_PULL_IN_PERIOD, The period to complete phasePullIn, rw, 900
	  Bits[31:0] float in unit of second

	+ NODE_TIME_CONFIG_PARAMS_PHASE_PULL_IN_MAXIMUM_PHASE_DIFF, The maximum phase difference for phasePullIn otherwise do a phase jump, rw, 1.0e-3
	  Bits[31:0] float in unit of second

	+ NODE_TIME_CONFIG_PARAMS_MAXIMUM_PHASE_CHANGE_RATE_SEC_PER_SEC, The maximum allowed phase change rate during phasePullIn, rw, 50e-9
	  Bits[31:0] float in unit of second per second

	+ NODE_TIME_CONFIG_PARAMS_REVERTIVE_SAME_TRANSPORT, Enable NON-revertive Operation On Same Transport, rw, 0
	  Bits[31:1] Reserved
	  Bits[0]    = 1 - NON-revertive operation enabled, 0 - Revertive operation enabled
	  Note this controls the revertive operation on the Node Time inputs.  There is a separate configuration
	  for revertive operation within a PTP port

	+ NODE_TIME_CONFIG_PARAMS_BMCA_MASK, Configures the BMCA steps to be performed, rw, 0xBF
	  Bits[31:8] Reserved
	  Bits[7:0] = mask
				0x01	GM Priority1
				0x02	GM Identity
				0x04	GM Clock Class
				0x08	GM Accuracy
				0x10	GM offsetScaledLogVariance
				0x20	GM Priority2
				0x40	Steps Removed
				0x80	GM Identity values
				Notes: 	Configures which steps in the best master clock algorithm are performed.
				The default value is 0xBF, ie all steps enabled except for Steps Removed

	+ NODE_TIME_CONFIG_PARAMS_HIGHEST_MASTER_CLOCK_CLASS, Highest clock class that can be a master, rw, 0xFE
	  Bits[31:8] Reserved
	  Bits[7:0] = Clock class
				Notes: 	If a master has a higher (therefore worse) clock class than this value then it cannot be selected
				as a master.

	+ NODE_TIME_CONFIG_PARAMS_SET_SELECTED_INPUT, Set Node Time Input manually, rw, 0xFF
	  Bits[31:8] = Reserved
	  Bits[7:0] =
		  Permitted values:
				(0)   Clock PLL 1
				(1)   Clock PLL 2
				(2)   PTP PLL 1
				(3)   PTP PLL 2
				(255) Node Time input selection is automatic (default)
	 Notes: Manually selected input must be enabled (see register %NODE_TIME_CONFIG_PARAMS_INPUT_ENABLE%)

    + NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_SEC_MSB, Node time secs bits 47 to 32, rw, -
	  Bits[31:16] = reserved
	  Bits[15:0]  = node time seconds bits 47 to 32 of 48 bit seconds field
	  Note: When read this shows the last setting to configure the node time
	        To read the current node time see register %NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC_MSB%
	        The time is not set until the register %NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_TAI% is written

    + NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_SEC, Node time secs bits 31 to 0, rw, -
	  Bits[31:0] = node time seconds bits 31 to 0 of 48 bit seconds field
	  Note: When read this shows the last setting to configure the node time
	        To read the current node time see register %NODE_TIME_STATUS_PARAMS_GET_NODE_TIME_SEC%
	        The time is not set until the register %NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_TAI% is written

    + NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_TAI, Node Time TAI and update the node time with the configured time, RW, -
      Bits[31:1] = Reserved
      Bits[0]    = Node Time is TAI
      When written to this register updates the node time with the configured values
      WARNING: THIS WILL HAVE UNSTABLE SIDE EFFECTS IF THE SYSTEM IS CURRENTLY LOCKED TO A TIME INPUT

    + NODE_TIME_CONFIG_PARAMS_UTC_OFFSET_VALUE, Node Time UTC Offset value, rw, -
	  Bits[31:0]  UTC Offset value as a signed integer. Valid range covers bits 15:0 only
	  Notes: This is the configured value for the Node Time when running without an input source
	  When the node time has a valid input the UTC Offset is inherited from the input

	+ NODE_TIME_CONFIG_PARAMS_UTC_OFFSET_VALID, Node Time UTC Offset valid, rw, -
	  Bits[31:1] Reserved
 	  Bits[0]    1 UTC Offset value is valid, 0 UTC Offset value is invalid
	  Notes: This is the configured value for the Node Time when running without an input source
	  When the node time has a valid input the UTC Offset is inherited from the input

	- NODE_TIME_CONFIG_PARAMS_ENABLE_FAST_UPDATE, Node Time Fast Tracking Enabled, rw, 0
	  Bits[31:1] Reserved
 	  Bits[0]    0 node time frequency tracks input sources at normal rate
 	  	  	  	 1 node time frequency tracks input sources at faster rate

*/

typedef enum
{
    NODE_TIME_CONFIG_PARAMS_INPUT_ENABLE	   			= 0,
    NODE_TIME_CONFIG_PARAMS_REVERTIVE	    			= 1,
    NODE_TIME_CONFIG_PARAMS_ENABLE_PHASE_BUILD_OUT	    = 2,
    NODE_TIME_CONFIG_PARAMS_PHASE_PULL_IN_PERIOD		= 3,
    NODE_TIME_CONFIG_PARAMS_PHASE_PULL_IN_MAXIMUM_PHASE_DIFF		= 4,
    NODE_TIME_CONFIG_PARAMS_MAXIMUM_PHASE_CHANGE_RATE_SEC_PER_SEC	= 5,
    NODE_TIME_CONFIG_PARAMS_REVERTIVE_SAME_TRANSPORT    = 6,
    NODE_TIME_CONFIG_PARAMS_BMCA_MASK    				= 7,
    NODE_TIME_CONFIG_PARAMS_HIGHEST_MASTER_CLOCK_CLASS	= 8,
    NODE_TIME_CONFIG_PARAMS_SET_SELECTED_INPUT  		= 9,

    NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_SEC_MSB  		= 16,
    NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_SEC    		= 17,
    NODE_TIME_CONFIG_PARAMS_SET_NODE_TIME_TAI   		= 18,

    NODE_TIME_CONFIG_PARAMS_UTC_OFFSET_VALUE			= 19,
	NODE_TIME_CONFIG_PARAMS_UTC_OFFSET_VALID        	= 20,

	NODE_TIME_CONFIG_PARAMS_ENABLE_FAST_UPDATE			= 32

}mmApiNodeTimeSubBlockConfigParams;


//PARAMETERSDEF:NODE_TIME_PARAMS_SUBBLOCK_HOLDOVER_CONTROLLER_CONFIG
/*
	+ NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_DURATION, Holdover duration, rw, 3600
	Bits[31:0]  Duration value as a unsigned integer.

	+ NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_RESET, Holdover reset, wo, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= any value.

	+ NODE_TIME_HOLDOVER_PARAMS_FORCE_HOLDOVER, Force holdover, rw, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= 1 - ForceHoldover enabled, 0 - disabled

	+ NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_CLASS, clock class on entering holdover, rw, 14
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value on entering holdover

	+ NODE_TIME_HOLDOVER_PARAMS_REDUCED_HOLDOVER_CLASS, clock class after holdover duration, rw, 193
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock class from Clock Class from IEEE1588 Clock stratum values
				Notes: This is the holdover clock class value after the holdover duration has expired

*/
typedef enum
{
	NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_DURATION		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_DURATION,
	NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_RESET		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_RESET,
	NODE_TIME_HOLDOVER_PARAMS_FORCE_HOLDOVER		= HOLDOVER_CONTROLLER_PARAMS_FORCE_HOLDOVER,
	NODE_TIME_HOLDOVER_PARAMS_HOLDOVER_CLASS		= HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_CLOCK_CLASS,
	NODE_TIME_HOLDOVER_PARAMS_REDUCED_HOLDOVER_CLASS = HOLDOVER_CONTROLLER_PARAMS_REDUCED_HOLDOVER_CLOCK_CLASS,
	NODE_TIME_HOLDOVER_PARAMS_END
}mmApiNodeTimeSubBlockHoldoverParams;

//PARAMETERSDEF:NODE_TIME_PARAMS_SUBBLOCK_BINARY_LOCK_MONITOR_CONFIG
/*
	+ NODE_TIME_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE, Binary error acceptable, rw, 1.0e-6
	Bits[31:0]  value as a float value.

	+ NODE_TIME_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE, Binary error unacceptable, rw, 5.0e-6
	Bits[31:0] 	value as a float value.

	+ NODE_TIME_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE, Binary error gradient acceptable, rw, 1.0e-9
	Bits[31:0]  value as a float value.

	+ NODE_TIME_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE, Binary error gradient unaccpetable, rw, 2.5e-9
	Bits[31:0] 	value as a unsigned integer.

	+ NODE_TIME_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE, Binary fuzzy lock acceptable, rw, 0.5
	Bits[31:0]  value as a float value.

	+ NODE_TIME_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE, Binary fuzzy lock unacceptable, rw, 0.25
	Bits[31:0] 	value as a float value.

	+ NODE_TIME_PARAMS_BLM_FORCE_LOCK, Binary force lock, rw, 0
	Bits[31:2]  reserved.
	Bits[1:0]	2 = Forced to UnLocked State, 1 = Forced to Locked State, 0 = Not Forced 

	+ NODE_TIME_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH, Binary maintain lock during source switch, rw, 0
	Bits[31:1]  reserved.
	Bits[0]		1 = Maintain Lock, 0 = Not Maintain Lock

*/


typedef enum
{
	NODE_TIME_PARAMS_BLM_ERR_SECONDS_ACCEPTABLE					= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_ACCEPTABLE,
	NODE_TIME_PARAMS_BLM_ERR_SECONDS_UNACCEPTABLE 				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_UNACCEPTABLE,
	NODE_TIME_PARAMS_BLM_ERR_GRADIENT_ACCEPTABLE				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_ACCEPTABLE,
	NODE_TIME_PARAMS_BLM_ERR_GRADIENT_UNACCEPTABLE				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_UNACCEPTABLE,
	NODE_TIME_PARAMS_BLM_FUZZY_LOCK_ACCEPTABLE					= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_ACCEPTABLE,
	NODE_TIME_PARAMS_BLM_FUZZY_LOCK_UNACCEPTABLE  				= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_UNACCEPTABLE,

	NODE_TIME_PARAMS_BLM_FORCE_LOCK								= BINARY_LOCK_MONITOR_CONFIG_PARAMS_FORCE_LOCK,
	NODE_TIME_PARAMS_BLM_MAINTAIN_LOCK_DURING_SOURCE_SWITCH 	= BINARY_LOCK_MONITOR_CONFIG_PARAMS_MAINTAIN_LOCK_DURING_SOURCE_SWITCH
}mmApiNodeTimeSubBlockBinaryLockMonitorParams;


ToPSyncConfigResult mmApiSetNodeTimeConfig(uint32 NodeTimeIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetNodeTimeConfig(uint32 NodeTimeIndex,uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
