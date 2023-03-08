/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: ClockOutputsMessageHandler.h $
 * $Revision: 5 $
 * $Date: 13/02/09 11:36 $
 */

/**
 * \file ClockOutputsMessageHandler.h
 * This file contains declarations for the Clock outputs message handler
 * routines.
 */


#ifndef CLOCK_OUTPUTS_MESSAGE_HANDLER_H
#define CLOCK_OUTPUTS_MESSAGE_HANDLER_H

#include "General.h"

/* Below includes are for mmAPI */
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToSetOutputClockFrequencyMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOutputClockFrequencyMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
											 uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetOutputClockFrequencyEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
													uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOutputClockFrequencyEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
													uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetOnePPSOutputClockEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOnePPSOutputClockEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetOnePPSOutputClockPulseWidthMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOnePPSOutputClockPulseWidthMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPPSOutputPeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPPSOutputPeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetTODOutputConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTODOutputConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);
                                           
void ReactToSetPhaseAlignedOutputClockFreqMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPhaseAlignedOutputClockFreqMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPPSOutputSourceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPPSOutputSourceMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                              uint8 *responseBuffer, uint16 *responseBufferLength);




/******************************************************************************
 * New functions for memory mapped API (This is work in progress)
 * Functionality subject to change
 ******************************************************************************/

/******************************************************************************
 * MMAPI_CLOCK_OUTPUTS_PARAMS Block Description
 * - Subblocks defined by mmApiClockOutputsSubBlock enum
 * - individual parameters defined by mmApiClockOutputsSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_CLOCK_OUTPUTS_PARAMS
typedef enum
{
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY     = 0,   /* Frequency Parameters */
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS           = 1,   /* PPS Parameters */
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED = 2,   /* Phase Aligned Parameters */
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX           = 4,   /* Multiplexor Parameters */
	//CLOCK_OUTPUTS_PARAMS_SUBBLOCK_END
} mmApiClockOutputsSubBlock;


//PARAMETERSDEF:CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY
/*
	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS#n#, DDS Clock #n#, rw, 0
	  Bits[31:0] = Frequency in Hz
	  Notes: This frequency must be chosen so that it conforms to the range of permitted configurable frequencies (see /
	  ToPSync data sheet). Values less than 1000Hz, except 1Hz, or greater than 62.5 MHz are invalid and will be rejected with an /
	  out-of-range error.

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_ENABLE_DDS, Enable/Disable DDS Clocks, rw, 0
	  Bits[31:4] = Reserved
	  Bit[3] = DDS Clock 3 Enable (0=disable, 1 = enable)
	  Bit[2] = DDS Clock 2 Enable (0=disable, 1 = enable)
	  Bit[1] = DDS Clock 1 Enable (0=disable, 1 = enable)
	  Bit[0] = DDS Clock 0 Enable (0=disable, 1 = enable)

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS0, Select source for DDS (Frequency) output 0, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS1, Select source for DDS (Frequency) output 1, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS2, Select source for DDS (Frequency) output 2, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS3, Select source for DDS (Frequency) output 3, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

*/

typedef enum
{
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS0 = 0,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS1 = 1,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS2 = 2,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS3 = 3,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_ENABLE_DDS     = 32,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS0 = 64,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS1 = 65,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS2 = 66,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_SOURCE_SELECT_DDS3 = 67,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_END
}mmApiClockOutputsSubBlockParams;

//PARAMETERSDEF:CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS
/*
	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_ENABLE, PPS Enable/Disable, rw, 3
	  Bits[31:2] = Reserved
	  Bit[1] = Enable PPS 1 (0=disable, 1 = enable)
	  Bit[0] = Enable PPS 0 (0=disable, 1 = enable)
	  Note: Disabling PPSn output also disables the corresponding phase clock, overriding
	  registers %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK0_SOURCE% and
	  %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK1_SOURCE%

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS0_PERIOD, PPS0 Output Period, rw, 1
	  Bits[31:8] = Reserved
	  Bits[7:0] = Output periods in seconds

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS1_PERIOD, PPS1 Output Period, rw, 1
	  Bits[31:8] = Reserved
	  Bits[7:0] = Output periods in seconds

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_CLOCK1_PLL_PULSE_WIDTH, Clock PLL1 PPS Pulse Width, rw, 0
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the Clock PLL1 (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_CLOCK2_PLL_PULSE_WIDTH, Clock PLL2 PPS Pulse Width, rw, 0xF4240
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the Clock PLL2 (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_PTP1_PLL_PULSE_WIDTH, PTP PLL1 PPS Pulse Width, rw, 0xF4240
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the PTP PLL1 (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_PTP2_PLL_PULSE_WIDTH, PTP PLL2 PPS Pulse Width, rw, 0xF4240
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the PTP1 PLL (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_NODE1_PLL_PULSE_WIDTH, NODE PLL1 PPS Pulse Width, rw, 0xF4240
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the NODE PLL1 (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_NODE2_PLL_PULSE_WIDTH, NODE PLL2 PPS Pulse Width, rw, 0xF4240
	  Bits[31:8] = Width of 1PPS pulse ‘high’ period in nanoseconds generated by the NODE PLL2 (max 400ms).
	  The default value 0xF4240 specifies a 1ms high period.
	  Note : Bits 0 to 2 will be set to zero. This is because of the 8ns resolution of
	  the internal clock. These bits are ignored on writes
	  The actual PPS output that this pulse width affects is determined by the PPS0/1 and PhaseClk0/1 source select api


*/

typedef enum
{
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_ENABLE = 0,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS0_PERIOD = 32,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS1_PERIOD = 33,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_CLOCK1_PLL_PULSE_WIDTH = 64,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_CLOCK2_PLL_PULSE_WIDTH = 65,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_PTP1_PLL_PULSE_WIDTH   = 66,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_PTP2_PLL_PULSE_WIDTH   = 67,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_NODE1_PLL_PULSE_WIDTH  = 68,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_NODE2_PLL_PULSE_WIDTH  = 69,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PPS_END

}mmApiClockOutputsSubBlockPPSParams;

//PARAMETERSDEF:CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED
/*
	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_CLOCK_PLL1_FREQ, Freq divisor for ClockPLL1 phase aligned output, rw, 0x18
		Bits[31]    Sets the phase aligned freq to 10MHz (special case not available using divisor below)
                    If this bit is set all other bits in the register will be forced to 0
		Bits[30:26] Not used - read as zero
		Bits[26:0]  Divisor used to compute the output clock frequency. Default value is 0x18 (5 Mhz)
	                Output frequency is configured according to the following equation:
	                    Output frequency = 125e06 /(divider + 1).
	                Example: To output a 5 Mhz clock, the divider must be set to 24, so that: 125e06 /(24 + 1) = 5 Mhz

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_CLOCK_PLL2_FREQ, Freq divisor for Clock PLL2 phase aligned output, rw, 0x18
		Bits[31:0]  Same as "Freq divisor for ClockPLL1 phase aligned output"

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_PTP_PLL1_FREQ, Freq divisor for PTP PLL 1 phase aligned output, rw, 0x18
		Bits[31:0]  Same as "Freq divisor for ClockPLL1 phase aligned output"

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_PTP_PLL2_FREQ, Freq divisor for PTP PLL 2 phase aligned output, rw, 0x18
		Bits[31:0]  Same as "Freq divisor for ClockPLL1 phase aligned output"

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_NODE_PLL1_FREQ, Freq divisor for Node PLL 1 phase aligned output, rw, 0x18
		Bits[31:0]  Same as "Freq divisor for ClockPLL1 phase aligned output"

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_NODE_PLL2_FREQ, Freq divisor for Node PLL 2 phase aligned output, rw, 0x18
		Bits[31:0]  Same as "Freq divisor for ClockPLL1 phase aligned output"

*/

typedef enum
{
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_CLOCK_PLL1_FREQ = 0,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_CLOCK_PLL2_FREQ = 1,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_PTP_PLL1_FREQ   = 2,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_PTP_PLL2_FREQ   = 3,
    CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_NODE_PLL1_FREQ  = 4,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_NODE_PLL2_FREQ  = 5,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_PHASE_ALIGNED_END
}mmApiClockOutputsSubBlockPhaseAlignedParams;

//PARAMETERSDEF:CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX
/*
	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK0_SOURCE, PPS0 and PhaseClk0 source select, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 1

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK1_SOURCE, PPS1 and PhaseClk1 source select, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK2_SOURCE, PhaseClk2 source select, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK3_SOURCE, PhaseClk3 source select, rw, 4
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
		  Valid bit (decimal) values:
			  000 (0) Clock PLL 1
			  001 (1) Clock PLL 2
			  010 (2) PTP PLL 1
			  011 (3) PTP PLL 2
			  100 (4) NODE PLL 1
			  101 (5) NODE PLL 2

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS#n#_SOURCE, PTP block output #n# source select, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Output Source
		  Valid bit (decimal) values:
			  000 (0) ToPSync output driven by DDS Freq#n# (see %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_FREQUENCY_DDS#n#%)
			  001 (1) ToPSync output driven by PhaseClk0 (see %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK0_SOURCE%)
			  010 (2) ToPSync output driven by PhaseClk1 (see %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK1_SOURCE%)
			  011 (3) ToPSync output driven by PhaseClk2 (see %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK2_SOURCE%)
			  100 (4) ToPSync output driven by PhaseClk3 (see %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK3_SOURCE%)

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK0_SOURCE, Package pin OpClk0 source select, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Output Source
		  Valid bit (decimal) values:
			  000 (0) Package pin OpClk0 driven by SETS output 1
			  001 (1) Package pin OpClk0 driven by TopSync output 0 (see /
			          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS0_SOURCE%)

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK1_SOURCE, Package pin OpClk1 source select, rw, 1
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Output Source
		  Valid bit (decimal) values:
			  000 (0) Package pin OpClk0 driven by SETS output 2
			  001 (1) Package pin OpClk0 driven by TopSync output 1 (see /
			          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS1_SOURCE%)

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK2_SOURCE, Package pin OpClk2 source select, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Output Source
		  Valid bit (decimal) values:
			  000 (0) Package pin OpClk0 driven by SETS output 4
			  001 (1) Package pin OpClk0 driven by TopSync output 2 (see /
			          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS2_SOURCE%)

	+ CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK3_SOURCE, Package pin OpClk3 source select, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Output Source
		  Valid bit (decimal) values:
			  000 (0) Package pin OpClk0 driven by SETS output 5
			  001 (1) Package pin OpClk0 driven by PTP block output 3 (see /
			          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS3_SOURCE%)
*/

typedef enum
{
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK0_SOURCE = 0,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK1_SOURCE = 1,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK2_SOURCE = 2,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK3_SOURCE = 3,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS0_SOURCE = 32,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS1_SOURCE = 33,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS2_SOURCE = 34,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS3_SOURCE = 35,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK0_SOURCE = 64,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK1_SOURCE = 65,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK2_SOURCE = 66,
	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_OUTPUTCLK3_SOURCE = 67,

	CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_END
}mmApiClockOutputsSubBlockMuxParams;
ToPSyncConfigResult mmApiSetDDSOutputConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetDDSOutputConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

ToPSyncConfigResult mmAPIProcessGetDDSOutputParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessSetDDSOutputParams(uint16 startAddress, uint16 endAddress, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
