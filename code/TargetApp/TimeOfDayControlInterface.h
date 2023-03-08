/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */

#ifndef TIMEOFDAYCONTROLINTERFACE_H_
#define TIMEOFDAYCONTROLINTERFACE_H_

#include "General.h"

#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * MMAPI_TOD_PARAMS Block Description
 * - Subblocks defined by mmApiTODSubBlock enum
 * - individual parameters defined by mmApiTODSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_TOD0_PARAMS
//SUBBLOCKSDEF:MMAPI_TOD1_PARAMS
typedef enum
{
	TOD_PARAMS_SUBBLOCK_CONFIG = 0, 				/* TOD configuration parameters */
	TOD_PARAMS_SUBBLOCK_INPUT_STATUS = 1, 			/* TOD input status */
	TOD_PARAMS_SUBBLOCK_NMEA_SENTENCE_CONFIG = 2,	/* NMEA sentence configuration */
	TOD_PARAMS_SUBBLOCK_END
} mmApiTODSubBlock;



//PARAMETERSDEF:TOD_PARAMS_SUBBLOCK_CONFIG
/*
	+ TOD_PARAMS_CONFIG_RECEIVE_ENABLE, enable/disable uart to receive TOD messages, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0] = Enable uart to receive TOD
	  Valid values:
		0: Disabled
		1: Enabled

	+ TOD_PARAMS_CONFIG_TRANSMIT_ENABLE, enable/disable uart to transmit TOD messages, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0] = Enable uart to transmit TOD
	  Valid values:
	    0: Disabled
	    1: Enabled

	+ TOD_PARAMS_CONFIG_BAUD_RATE, Baud Rate for uart, rw, 4800
	  Bits[31:0] = Baud Rate e.g. 1200, 2400, 4800, 9600, 19200

	+ TOD_PARAMS_CONFIG_RECEIVE_TOD_CODE, TOD code for receive, rw, 1
	  Bits[31:1] = reserved
	  Bits[0]  = TOD_CODE
	  Valid values:
		1 - NMEA

	+ TOD_PARAMS_CONFIG_TRANSMIT_TOD_CODE, TOD code for transmit, rw, 1
	  Bits[31:1] = reserved
	  Bits[0]  = TOD_CODE
	  Valid values:
		1 - NMEA

	+ TOD_PARAMS_CONFIG_RECEIVE_CLOCK_LOCKER_INDEX, clock PLL index for receive, rw, 0
	  Bits[31:2] = reserved
	  Bits[1:0]  = Clock PLL index
	  Valid values:
		  1 - Clock PLL 1
		  2 - Clock PLL 2

	+ TOD_PARAMS_CONFIG_TRANSMIT_CLOCK_PATH_INDEX, Node Time index for transmit, rw, 0
	  Bits[31:2] = reserved
	  Bits[1:0]  = Node Time index
	  Valid values:
		  1 - Node Time 1
		  2 - Node Time 2
*/

typedef enum
{
	TOD_PARAMS_CONFIG_RECEIVE_ENABLE			 = 0,
	TOD_PARAMS_CONFIG_TRANSMIT_ENABLE			 = 1,
    TOD_PARAMS_CONFIG_BAUD_RATE					 = 2,
    TOD_PARAMS_CONFIG_RECEIVE_TOD_CODE			 = 3,
    TOD_PARAMS_CONFIG_TRANSMIT_TOD_CODE			 = 4,
    TOD_PARAMS_CONFIG_RECEIVE_CLOCK_LOCKER_INDEX = 5,
    TOD_PARAMS_CONFIG_TRANSMIT_CLOCK_PATH_INDEX	 = 6,
	TOD_PARAMS_CONFIG_SUBBLOCK_END
}mmApiTODSubBlockParamsConfig;

//PARAMETERSDEF:TOD_PARAMS_SUBBLOCK_INPUT_STATUS
/*
	+ TOD_PARAMS_INPUT_STATUS_NUMBER_MSGS_RECEIVED,  number of TOD messages received, ro, 0
	  Bits[31:0] = Number of TOD messages received

	+ TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_SECONDS_MSB, time in last sentence received MS seconds (epoch bits), ro, 0
	  Bits[31:16] = Reserved
	  Bits[15:0] = Last sentence received (seconds bits 47 to 32)
				  This contains the epoch of the seconds taken from the time in the last message received.

	+ TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_SECONDS, time in last sentence received (seconds), ro, 0
	  Bits[31:0] = Last sentence received (seconds bits 31 to 0)
				  These are the lower 32 bits of the seconds taken from the time in the last message received.

	+ TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_NANOSECONDS, time in last sentence received (nanoseconds), ro, 0
	  Bits[31:0] = Last sentence received (nanoseconds)

	- TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_CONFIGURATION, time in last sentence received is TAI, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = Is TAI. Valid values are:
		  0 Is not TAI
		  1 Is TAI

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_1, last sentence received word 1, ro, 0
	  Bits[31:0] = Last sentence received word 1

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_2, last sentence received word 2, ro, 0
	  Bits[31:0] = Last sentence received word 2

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_3, last sentence received word 3, ro, 0
	  Bits[31:0] = Last sentence received word 3

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_4, last sentence received word 4, ro, 0
	  Bits[31:0] = Last sentence received word 4

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_5, last sentence received word 5, ro, 0
	  Bits[31:0] = Last sentence received word 5

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_6, last sentence received word 6, ro, 0
	  Bits[31:0] = Last sentence received word 6

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_7, last sentence received  word 7, ro, 0
	  Bits[31:0] = Last sentence received word 7

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_8, last sentence received word 8, ro, 0
	  Bits[31:0] = Last sentence received word 8

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_9, last sentence received  word 9, ro, 0
	  Bits[31:0] = Last sentence received word 9

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_10, last sentence received word 10, ro, 0
	  Bits[31:0] = Last sentence received word 10

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_11, last sentence received word 11, ro, 0
	  Bits[31:0] = Last sentence received word 11

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_12, last sentence received word 12, ro, 0
	  Bits[31:0] = Last sentence received word 12

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_13, last sentence received word 13, ro, 0
	  Bits[31:0] = Last sentence received word 13

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_14, last sentence received word 14, ro, 0
	  Bits[31:0] = Last sentence received word 14

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_15, last sentence received word 15, ro, 0
	  Bits[31:0] = Last sentence received word 15

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_16, last sentence received word 16, ro, 0
	  Bits[31:0] = Last sentence received word 16

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_17, last sentence received word 17, ro, 0
	  Bits[31:0] = Last sentence received word 17

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_18, last sentence received word 18, ro, 0
	  Bits[31:0] = Last sentence received word 18

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_19, last sentence received word 19, ro, 0
	  Bits[31:0] = Last sentence received word 19

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_20, last sentence received word 20, ro, 0
	  Bits[31:0] = Last sentence received word 20

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_21, last sentence received word 21, ro, 0
	  Bits[31:0] = Last sentence received word 21

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_22, last sentence received word 22, ro, 0
	  Bits[31:0] = Last sentence received word 22

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_23, last sentence received word 23, ro, 0
	  Bits[31:0] = Last sentence received word 23

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_24, last sentence received word 24, ro, 0
	  Bits[31:0] = Last sentence received word 24

	+ TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_25, last sentence received word 25, ro, 0
	  Bits[31:0] = Last sentence received word 25

*/
typedef enum
{
	TOD_PARAMS_INPUT_STATUS_NUMBER_MSGS_RECEIVED	 				  = 0,
	TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_SECONDS_MSB   = 1,
	TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_SECONDS 	  = 2,
	TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_NANOSECONDS   = 3,
	TOD_PARAMS_INPUT_STATUS_TIME_LAST_SENTENCE_RECEIVED_CONFIGURATION = 4,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_1 				  = 16,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_2 				  = 17,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_3 				  = 18,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_4 				  = 19,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_5                  = 20,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_6                  = 21,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_7 				  = 22,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_8 				  = 23,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_9 				  = 24,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_10 				  = 25,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_11 				  = 26,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_12 				  = 27,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_13 				  = 28,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_14 				  = 29,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_15 				  = 30,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_16 				  = 31,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_17 				  = 32,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_18 				  = 33,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_19 				  = 34,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_20 				  = 35,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_21 				  = 36,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_22 				  = 37,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_23 				  = 38,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_24 				  = 39,
	TOD_PARAMS_INPUT_STATUS_LAST_SENTENCE_RECEIVED_25 				  = 40,
}mmApiTODSubBlockParamsInputStatus;

//PARAMETERSDEF:TOD_PARAMS_SUBBLOCK_NMEA_SENTENCE_CONFIG
/*
	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_ACTIVE_SENTENCE, NMEA active sentence configuration, rw, 0x1
	  Bits[31:0] = NMEA active sentence configuration bit fields. The following are valid bit fields values:
		0x01 - NMEA RMC sentence
		0x02 - NMEA GGA sentence
		0x04 - NMEA ZDA sentence
		0x08 - SemTech time sentence
		0x10 - Semtech frequency sentence
		0x20 - Semtech time short sentence (IRIG)
		0x40 - Semtech time information sentence
		0x80 - Semtech time status sentence

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_TIME_FORMAT, SMTC proprietary message time format configuration, rw, 0x0
	  Bits[31:0] = SMTC proprietary message time format configuration. The following are valid values:
		  0x00 - TAI
		  0x01 - UTC
		  0x02 - GPS

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_TIME_ALIGNMENT, SMTC proprietary message time alignment, rw, 0x0
	  Bits[31:0] = SMTC proprietary message time alignment
		  0x00 - Time is aligned to the preceding PPnS edge
		  0x01 - Time is aligned to the next PPnS edge

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_1, SMTC proprietary message data byte 1, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 1

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_2, SMTC proprietary message data byte 2, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 2

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_3, SMTC proprietary message data byte 3, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 3

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_4, SMTC proprietary message data byte 4, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 4

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_5, SMTC proprietary message data byte 5, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 5

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_6, SMTC proprietary message data byte 6, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 6

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_7, SMTC proprietary message data byte 7, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 7

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_8, SMTC proprietary message data byte 8, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 8

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_9, SMTC proprietary message data byte 9, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 9

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_10, SMTC proprietary message data byte 10, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 10

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_11, SMTC proprietary message data byte 11, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 11

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_12, SMTC proprietary message data byte 12, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 12

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_13, SMTC proprietary message data byte 13, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 13

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_14, SMTC proprietary message data byte 14, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 14

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_15, SMTC proprietary message data byte 15, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 15

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_16, SMTC proprietary message data byte 16, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 16

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_17, SMTC proprietary message data byte 17, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 17

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_18, SMTC proprietary message data byte 18, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 18

    + TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_19, SMTC proprietary message data byte 19, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 19

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_20, SMTC proprietary message data byte 20, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 20

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_21, SMTC proprietary message data byte 21, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 21

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_22, SMTC proprietary message data byte 22, rw, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 22

	+ TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_23, SMTC proprietary message data byte 23, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0] = SMTC proprietary message data byte 23. This is read-only and is used for a checksum.

*/
typedef enum
{
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_ACTIVE_SENTENCE							= 0,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_TIME_FORMAT	= 1,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_TIME_ALIGNMENT	= 2,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_1 		= 16,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_2			= 17,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_3 		= 18,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_4 		= 19,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_5 		= 20,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_6 		= 21,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_7 		= 22,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_8 		= 23,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_9 		= 24,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_10 		= 25,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_11 		= 26,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_12 		= 27,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_13 		= 28,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_14 		= 29,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_15 		= 30,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_16 		= 31,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_17 		= 32,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_18 		= 33,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_19 		= 34,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_20 		= 35,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_21 		= 36,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_22 		= 37,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SMTC_PROPRIETARY_MESSAGE_DATA_23 		= 38,
	TOD_PARAMS_NMEA_SENTENCE_CONFIG_SUBBLOCK_END
}mmApiTODSubBlockParamsNMEASentenceConfig;

ToPSyncConfigResult mmApiSetTODConfig(uint8 uartPortNumber, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetTODConfig(uint8 uartPortNumber, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif /* TIMEOFDAYCONTROLINTERFACE_H_ */
