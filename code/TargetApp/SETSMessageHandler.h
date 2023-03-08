/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: SETSMessageHandler.h $
 * $Revision: 3 $
 * $Date: 23/05/08 14:11 $
 */

/**
 * \file SETSMessageHandler.h
 * This file contains declarations for the SETS message handler
 * routines.
 */


#ifndef SETS_MESSAGE_HANDLER_H
#define SETS_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToSETSReadWriteMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetSETSAutomaticConfigurationEnabled(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSETSAutomaticConfigurationEnabled(const uint8 *requestMessage, uint16 requestMessageLength, 
                                           uint8 *responseBuffer, uint16 *responseBufferLength);



/******************************************************************************
 * MMAPI_TDM_PARAMS Block Description
 * - Subblocks defined by mmApiTDMSubBlock enum
 * - individual parameters defined by mmApiTDMSubBlockParams enum
 ******************************************************************************/
//SUBBLOCKSDEF:MMAPI_TDM_ESETS_PARAMS
typedef enum
{
	TDM_ESETS_SUBBLOCK_PARAMS_REGISTERS   = 0, /* TDM Register Interface */
	TDM_ESETS_SUBBLOCK_PARAMS_INPUT_MUXES = 1, /* MUXes for SETS inputs pins SETSI3, SETSI4 */
	TDM_ESETS_SUBBLOCK_END
} mmApiTDMSubBlock;

//PARAMETERSDEF:TDM_ESETS_SUBBLOCK_PARAMS_INPUT_MUXES
/*
	+ TDM_MUX_SETSI3, TDM (eSETS) input SETSI3 MUX, rw, 0x0
	  TDM (eSETS) input SETSI3 is taken from either IpClk0 or the output of one of the PTP block's PhaseOPCLk's
	  Bits[31:1] Reserved
	  Bits[0:0]
	      0 - SETSI3 is driven from package pin IpClk0
	      1 - SETSI3 is driven by the clock that is driving OpClk0 (see /
	          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS0_SOURCE% and %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK0_SOURCE%)

	+ TDM_MUX_SETSI4, TDM (eSETS) input SETSI4 MUX, rw, 0x0
	  TDM (eSETS) input SETSI4 is taken from either IpClk1 or the output of one of the PTP block's PhaseOPCLk's
	      0 - SETSI4 is driven from package pin IpClk1
	      1 - SETSI4 is driven by the clock that is driving OpClk1 (see /
	          %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_DDS1_SOURCE% and %CLOCK_OUTPUTS_PARAMS_SUBBLOCK_MUX_PHASECLK1_SOURCE%)

	- TDM_MUX_SETSI7, TDM (eSETS) input SETSI7 MUX, rw, 0x0
	  TDM (eSETS) input SETSI7 is taken from either IpClk2 or the output of one of the PTP block's PhaseOPCLk's
	      0 - SETSI7 is driven from package pin IpClk2
	      1 - SETSI7 is driven by the output of the first Div N divider
	  /
	  Warning: This is not exposed as we do not offer the facility for the divN divider to drive SETs

	- TDM_MUX_SETSI8, TDM (eSETS) input SETSI8 MUX, rw, 0x0
	  TDM (eSETS) input SETSI8 is taken from either IpClk3 or the output of one of the PTP block's PhaseOPCLk's
	      0 - SETSI8 is driven from package pin IpClk3
	      1 - SETSI8 is driven by the output of the second Div N divider
	  /
	  Warning: This is not exposed as we do not offer the facility for the divN divider to drive SETs
 */
typedef enum
{
	TDM_MUX_SETSI3 = 0,
	TDM_MUX_SETSI4 = 1,
	TDM_MUX_SETSI7 = 2,
	TDM_MUX_SETSI8 = 3,
	TDM_MUX_END
} mmApiTDMSubBlockParamsInputMuxes;


//PARAMETERSDEF:TDM_ESETS_SUBBLOCK_PARAMS_REGISTERS
/*
 	+ TDM_REGISTER_#n#, TDM (eSETS) Register #n:hex#, rw, 0x0
	  Bits[31:8] = Reserved
	  Bits[7:0]  = TDM (eSETS) Register.  Refer to ACS9522 datasheet

*/
typedef enum
{
	TDM_REGISTER_0  = 0,
	TDM_REGISTER_1  = 1,
	TDM_REGISTER_2  = 2,
	TDM_REGISTER_3  = 3,
	TDM_REGISTER_4  = 4,
	TDM_REGISTER_5  = 5,
	TDM_REGISTER_6  = 6,
	TDM_REGISTER_7  = 7,
	TDM_REGISTER_8  = 8,
	TDM_REGISTER_9  = 9,

	TDM_REGISTER_10 = 10,
	TDM_REGISTER_11 = 11,
	TDM_REGISTER_12 = 12,
	TDM_REGISTER_13 = 13,
	TDM_REGISTER_14 = 14,
	TDM_REGISTER_15 = 15,
	TDM_REGISTER_16 = 16,
	TDM_REGISTER_17 = 17,
	TDM_REGISTER_18 = 18,
	TDM_REGISTER_19 = 19,

	TDM_REGISTER_20 = 20,
	TDM_REGISTER_21 = 21,
	TDM_REGISTER_22 = 22,
	TDM_REGISTER_23 = 23,
	TDM_REGISTER_24 = 24,
	TDM_REGISTER_25 = 25,
	TDM_REGISTER_26 = 26,
	TDM_REGISTER_27 = 27,
	TDM_REGISTER_28 = 28,
	TDM_REGISTER_29 = 29,

	TDM_REGISTER_30 = 30,
	TDM_REGISTER_31 = 31,
	TDM_REGISTER_32 = 32,
	TDM_REGISTER_33 = 33,
	TDM_REGISTER_34 = 34,
	TDM_REGISTER_35 = 35,
	TDM_REGISTER_36 = 36,
	TDM_REGISTER_37 = 37,
	TDM_REGISTER_38 = 38,
	TDM_REGISTER_39 = 39,

	TDM_REGISTER_40 = 40,
	TDM_REGISTER_41 = 41,
	TDM_REGISTER_42 = 42,
	TDM_REGISTER_43 = 43,
	TDM_REGISTER_44 = 44,
	TDM_REGISTER_45 = 45,
	TDM_REGISTER_46 = 46,
	TDM_REGISTER_47 = 47,
	TDM_REGISTER_48 = 48,
	TDM_REGISTER_49 = 49,

	TDM_REGISTER_50 = 50,
	TDM_REGISTER_51 = 51,
	TDM_REGISTER_52 = 52,
	TDM_REGISTER_53 = 53,
	TDM_REGISTER_54 = 54,
	TDM_REGISTER_55 = 55,
	TDM_REGISTER_56 = 56,
	TDM_REGISTER_57 = 57,
	TDM_REGISTER_58 = 58,
	TDM_REGISTER_59 = 59,

	TDM_REGISTER_60 = 60,
	TDM_REGISTER_61 = 61,
	TDM_REGISTER_62 = 62,
	TDM_REGISTER_63 = 63,
	TDM_REGISTER_64 = 64,
	TDM_REGISTER_65 = 65,
	TDM_REGISTER_66 = 66,
	TDM_REGISTER_67 = 67,
	TDM_REGISTER_68 = 68,
	TDM_REGISTER_69 = 69,

	TDM_REGISTER_70 = 70,
	TDM_REGISTER_71 = 71,
	TDM_REGISTER_72 = 72,
	TDM_REGISTER_73 = 73,
	TDM_REGISTER_74 = 74,
	TDM_REGISTER_75 = 75,
	TDM_REGISTER_76 = 76,
	TDM_REGISTER_77 = 77,
	TDM_REGISTER_78 = 78,
	TDM_REGISTER_79 = 79,

	TDM_REGISTER_80 = 80,
	TDM_REGISTER_81 = 81,
	TDM_REGISTER_82 = 82,
	TDM_REGISTER_83 = 83,
	TDM_REGISTER_84 = 84,
	TDM_REGISTER_85 = 85,
	TDM_REGISTER_86 = 86,
	TDM_REGISTER_87 = 87,
	TDM_REGISTER_88 = 88,
	TDM_REGISTER_89 = 89,

	TDM_REGISTER_90 = 90,
	TDM_REGISTER_91 = 91,
	TDM_REGISTER_92 = 92,
	TDM_REGISTER_93 = 93,
	TDM_REGISTER_94 = 94,
	TDM_REGISTER_95 = 95,
	TDM_REGISTER_96 = 96,
	TDM_REGISTER_97 = 97,
	TDM_REGISTER_98 = 98,
	TDM_REGISTER_99 = 99,

	TDM_REGISTER_100 = 100,
	TDM_REGISTER_101 = 101,
	TDM_REGISTER_102 = 102,
	TDM_REGISTER_103 = 103,
	TDM_REGISTER_104 = 104,
	TDM_REGISTER_105 = 105,
	TDM_REGISTER_106 = 106,
	TDM_REGISTER_107 = 107,
	TDM_REGISTER_108 = 108,
	TDM_REGISTER_109 = 109,

	TDM_REGISTER_110 = 110,
	TDM_REGISTER_111 = 111,
	TDM_REGISTER_112 = 112,
	TDM_REGISTER_113 = 113,
	TDM_REGISTER_114 = 114,
	TDM_REGISTER_115 = 115,
	TDM_REGISTER_116 = 116,
	TDM_REGISTER_117 = 117,
	TDM_REGISTER_118 = 118,
	TDM_REGISTER_119 = 119,

	TDM_REGISTER_120 = 120,
	TDM_REGISTER_121 = 121,
	TDM_REGISTER_122 = 122,
	TDM_REGISTER_123 = 123,
	TDM_REGISTER_124 = 124,
	TDM_REGISTER_125 = 125,
	TDM_REGISTER_126 = 126,
	TDM_REGISTER_127 = 127,
	TDM_REGISTER_END
} mmApiTDMSubBlockParamsRegisters;


ToPSyncConfigResult mmApiSetTDMConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetTDMConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

//ToPSyncConfigResult mmAPIProcessGetTDMParams(uint16 startAddress, uint16 endAddress, uint32 *data);
//ToPSyncConfigResult mmAPIProcessSetTDMParams(uint16 startAddress, uint16 endAddress, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif
