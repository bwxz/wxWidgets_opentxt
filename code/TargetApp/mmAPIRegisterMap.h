/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.
*/

#ifndef API_MEMORY_MAP_H
#define API_MEMORY_MAP_H


/******************************************************************************
 * Revision number for mmAPI parameters
 *
 * MMAPI_PARAMETERS_MAP_MAJOR_REVISION:
 * The major revision increments whenever there is a significant change to the
 * memory map such as changing the addresses at which parameters or adding new
 * subblocks.
 *
 * MMAPI_PARAMETERS_MAP_MINOR_REVISION:
 * The minor revision increments whenever there is a minor change to the memory
 * map such as appending new parameters to end of an existing sub block or when
 * a parameter is deprecated or removed but its address is retained as 'reserved'
 * for future use.
 *
 ******************************************************************************/
#define MMAPI_PARAMETERS_MAP_MAJOR_REVISION 4
#define MMAPI_PARAMETERS_MAP_MINOR_REVISION 4


/******************************************************************************
 * Ascii test string 'smtc' returned by debug read register
 ******************************************************************************/
#define MMAPI_SMTC_TEST_PATTERN						0x736D7463


/******************************************************************************
 * Top level blocks for the memory mapped parameter API
 *
 * Notes:
 * These top level blocks are aligned to the ToPSync2 Release 2 architecture
 * diagram. Sub block and parameter definitions are defined in the #include
 * files associated with each specific function.
 *
 * This is work in progress & functionalities may be shuffled around at this
 * develops.
 *
 * Document Parser
 * ---------------
 * The following text delimiters exist within the #include files for use by the
 * document parser:
 *
 * //MAINBLOCKSDEF
 * //SUBBLOCKSDEF
 * //PARAMETERSDEF
 *
 * For information on the document parser see (todo: insert ref)
 *
 ******************************************************************************/
//MAINBLOCKSDEF
typedef enum
{
	MMAPI_DIAGNOSTIC_PARAMS 			= 0,  /* Debug Diagnostics Configuration */
	MMAPI_SYSTEM_MANAGEMENT_PARAMS		= 1,  /* System Management Configuration */
	MMAPI_CLOCK_INPUTS_PARAMS			= 2,  /* Clock Inputs Configuration */
	MMAPI_CLOCK_OUTPUTS_PARAMS			= 3,  /* Clock Outputs Configuration */
	MMAPI_NETWORK_INTERFACE0_PARAMS     = 4,  /* Network Interface 1 Configuration (physical port 0, virtual port 0) */
	MMAPI_NETWORK_INTERFACE1_PARAMS		= 5,  /* Network Interface 2 Configuration (physical port 1, virtual port 0) */
	//not used yet MMAPI_EXTERNAL_INTERFACES_PARAMS	= 6,  /* External Interfaces Configuration */
	MMAPI_TOD0_PARAMS					= 7,  /* Time Of Day Interface 1 Configuration */
	MMAPI_TOD1_PARAMS					= 8,  /* Time Of Day Interface 2 Configuration */
	MMAPI_LOCAL_OSCILLATOR_PARAMS		= 9,  /* Local Oscillator Configuration */
	MMAPI_PTP_PORT1_PARAMS				= 10,  /* PTP Slave Port 1 Configuration */
	MMAPI_PTP_PORT2_PARAMS				= 11,  /* PTP Slave Port 2 Configuration */
	MMAPI_PTP_PORT3_PARAMS				= 12, /* PTP Master Port 1 Configuration */
	MMAPI_PTP_PORT4_PARAMS				= 13, /* PTP Master Port 2 Configuration */
	//GAP FOR FUTURE 2 more slaves and 2 more masters
	MMAPI_AMT1_PARAMS					= 18,  /* Acceptable Master Table 1 Configuration */
	MMAPI_VMT1_PARAMS					= 19,  /* Visible Master Table 1 Configuration */
	MMAPI_PTP_PLL1_PARAMS				= 20,  /* PTP PLL 1 Configuration */
	MMAPI_AMT2_PARAMS					= 21,  /* Acceptable Master Table 2 Configuration */
	MMAPI_VMT2_PARAMS					= 22,  /* Visible Master Table 2 Configuration */
	MMAPI_PTP_PLL2_PARAMS				= 23,  /* PTP PLL 2 Configuration */
	//GAP FOR FUTURE 2 more slaves
	MMAPI_AST1_PARAMS					= 30,  /* Acceptable Slave Table 1 Configuration */
	MMAPI_AST2_PARAMS					= 31,  /* Acceptable Slave Table 2 Configuration */
	//GAP FOR FUTURE 2 more masters
	MMAPI_NETWORK_MASTER_TABLE			= 34, /* Network Master Table Configuration */
	MMAPI_CLOCK_PLL1_PARAMS				= 35, /* Clock PLL 1 Configuration */
	MMAPI_CLOCK_PLL2_PARAMS				= 36, /* Clock PLL 2 Configuration */
	// RESERVED GAP
	MMAPI_NODE_TIME1_PARAMS				= 39, /* Node Time 1 Configuration */
	MMAPI_NODE_TIME2_PARAMS				= 40, /* Node Time 2 Configuration */
	MMAPI_TDM_ESETS_PARAMS				= 41, /* TDM (eSETS) Configuration */
	MMAPI_ALARMS_PARAMS					= 42, /* Alarm Configuration */
	MMAPI_NETWORK_PARAMS				= 43, /* Network Configuration */
	MMAPI_NETWORK_INTERFACE01_PARAMS	= 50, /* Virtual interface Configuration (physical port 0, virtual port 1) */
	MMAPI_NETWORK_INTERFACE02_PARAMS	= 51, /* Virtual interface Configuration (physical port 0, virtual port 2) */
	MMAPI_NETWORK_INTERFACE03_PARAMS	= 52, /* Virtual interface Configuration (physical port 0, virtual port 3) */
	MMAPI_NETWORK_INTERFACE04_PARAMS	= 53, /* Virtual interface Configuration (physical port 0, virtual port 4) */
	MMAPI_NETWORK_INTERFACE05_PARAMS	= 54, /* Virtual interface Configuration (physical port 0, virtual port 5) */
	MMAPI_NETWORK_INTERFACE11_PARAMS	= 60, /* Virtual interface Configuration (physical port 1, virtual port 1) */
	MMAPI_NETWORK_INTERFACE12_PARAMS	= 61, /* Virtual interface Configuration (physical port 1, virtual port 2) */
	MMAPI_NETWORK_INTERFACE13_PARAMS	= 62, /* Virtual interface Configuration (physical port 1, virtual port 3) */
	MMAPI_NETWORK_INTERFACE14_PARAMS	= 63, /* Virtual interface Configuration (physical port 1, virtual port 4) */
	MMAPI_NETWORK_INTERFACE15_PARAMS	= 64, /* Virtual interface Configuration (physical port 1, virtual port 5) */
	MMAPI_IMAGE_UPLOAD_PARAMS			= 208,/* Image upload control */
	MMAPI_ACS1790_PARAMS                = 224,/* ACS 1790 Configuration */
	MMAPI_TOPLEVEL_END
} mmAPITopLevelBlocks;



#endif




