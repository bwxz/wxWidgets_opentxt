/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: ClockInputsMessageHandler.h $
 * $Revision: 6 $
 * $Date: 12/01/09 17:42 $
 */

/**
 * \file ClockInputsMessageHandler.h
 * This file contains declarations for the Clock inputs message handler
 * routines.
 */


#ifndef CLOCK_INPUTS_MESSAGE_HANDLER_H
#define CLOCK_INPUTS_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


void ReactToSetTODInputConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTODInputConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetTODInputStatusMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetUTCOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetUTCOffsetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetImpendingLeapSecondMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDaysToLeapSecondMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDaysToLeapSecondNodeMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDaysToLeapSecondSourceMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpInputClockFrequencyMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpInputClockFrequencyMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpInputClockEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpInputClockEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPtpInputClockSelectedMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetPtpInputClockSelectedMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPPSInputTimeMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetPPSInputTimeOfDayMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                    uint8 *responseBuffer, uint16 *responseBufferLength);



/******************************************************************************
 * New functions for memory mapped API (This is work in progress)
 * Functionality subject to change
 ******************************************************************************/
//SUBBLOCKSDEF:MMAPI_CLOCK_INPUTS_PARAMS
typedef enum
{
	CLOCK_INPUTS_SUBBLOCK_PARAMS = 0, /* Clock input configuration */
	CLOCK_INPUTS_SUBBLOCK_END
} mmApiClockInputsSubBlock;


//PARAMETERSDEF:CLOCK_INPUTS_SUBBLOCK_PARAMS
/*
    + CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX_CONFIG, Mux between SETS and package pins for input clocks, rw, 0x0
      Bits[0:0]  = '0' means package pin IPCLK0 is the selected frequency source
                   '1' means SETS output 01 is the selected frequency source
      Bits[1:1]  = '0' means package pin IPCLK1 is the selected frequency source
                   '1' means SETS output 02 is the selected frequency source
      Bits[2:2]  = '0' means package pin IPCLK2 is the selected frequency source
                   '1' means SETS output 04 is the selected frequency source
      Bits[3:3]  = '0' means package pin IPCLK3 is the selected frequency source
                   '1' means SETS output 05 is the selected frequency source

  	+ CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX#n#_FREQ_HZ, Frequency in Hertz from MUX #n#, rw, 0x0
	  Bits[31:0] = Frequency in Hertz of clock input. If the clock is enabled & selected on any clock PLL this
	               setting is applied immediately. The mux block for the input clock specifies whether the input
	               comes from a package pin or is routed internal within the ToPSync package from one of the SETS
	               outputs. The mux options must be set separately in register %CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX_CONFIG%.

 	+ CLOCK_INPUTS_SUBBLOCK_PARAMS_SRC#n#_FREQ_HZ, Frequency in Hertz of reference source #n#, rw, IPCLK 0|1 = 0x1; 0x0 otherwise.
	  Bits[31:0] = Frequency in Hertz of clock input.
	  /
	  Note: If the clock is enabled & selected on any clock PLL this setting is applied immediately. These inputs /
	        can only come from the corresponding package pins.

*/
typedef enum
{
	CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX_CONFIG = 0,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX0_FREQ_HZ = 1,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX1_FREQ_HZ = 2,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX2_FREQ_HZ = 3,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_MUX3_FREQ_HZ = 4,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_SRC4_FREQ_HZ = 5,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_SRC5_FREQ_HZ = 6,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_SRC6_FREQ_HZ = 7,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_SRC7_FREQ_HZ = 8,
	CLOCK_INPUTS_SUBBLOCK_PARAMS_END
} mmClockInputsSubBlockParams;



ToPSyncConfigResult mmApiSetGetClockInputsConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data, Bool isSetOperation);

#ifdef __cplusplus
}
#endif


#endif
