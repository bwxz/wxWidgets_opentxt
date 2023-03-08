/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: DiagnosticsMessageHandler.h $
 * $Revision: 6 $
 * $Date: 3/10/07 14:46 $
 */

/**
 * \file DiagnosticsMessageHandler.h
 * This file contains declarations for the Diagnostics message handler functions.
 * These are messages for debug and diagnostics.
 */

#ifndef DIAGNOSTICS_MESSAGE_HANDLER_H
#define DIAGNOSTICS_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult mmApiGetDiagnosticConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetDiagnosticConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

ToPSyncConfigResult mmAPIProcessGetDiagnosticParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessSetDiagnosticParams(uint16 startAddress, uint16 endAddress, uint32 *data);

#ifdef _ARC
#ifdef TARGET_TS2D
//called from control message handler
void CreateECCInsertionError();
#endif
#endif

/******************************************************************************
 * mmApiDiagnosticParams Block Description
 * - Subblocks defined by mmApiDiagnosticSubBlock enum
 * - individual parameters defined by mmApiDiagnosticSubBlockParams enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_DIAGNOSTIC_PARAMS
typedef enum
{
	DIAGNOSTICS_REGISTER_MAP    = 0,   			 /* Register Map */
												 /* Reserved for Application Self-Test */
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER	= 2,			 /* System debug */
	DIAGNOSTICS_LCD				= 3,			 /* Lcd Display Settings */
	DIAGNOSTICS_I2C             = 4,             /* I2C Access for debug only */
	DIAGNOSTICS_DAC             = 5,             /* Direct DAC control for debug only */
	DIAGNOSTICS_ECC				= 6				 /* ECC Settings */
} mmApiDiagnosticsSubBlock;

//PARAMETERSDEF:DIAGNOSTICS_REGISTER_MAP
/*
	+ DIAGNOSTICS_TEST_REGISTER_1, Test Register 1, ro, 0x736D7473
	  Bits[31:24] = 0x73 's'
	  Bits[23:16] = 0x6D 'm'
	  bits[15:8]  = 0x74 't'
	  Bits[7:0]   = 0x73 'c'

	+ DIAGNOSTICS_TEST_REGISTER_2, Test register 2, rw, 0x00000000
	  Bits[31:0] = Determined by user (This register is a scratch pad provided as a debug
	               aid during initial board bring up. Accessing this register does not affect
	               normal ToPSync operation.

	+ DIAGNOSTICS_REGISTER_MAP_MAJOR_MINOR_REVISION, Register Map Revision number (Major/Minor Rev), ro, 0
	  Bits[31:16] = Major revision number
	  Bits[15:0] = Minor revision number

    - DIAGNOSTICS_REGISTER_MAP_REVISION_RESERVED_1,Register Map Revision (Reserved), ro, 0
	  Bits[31:0] = Reserved for memory map versioning

*/

typedef enum
{
	DIAGNOSTICS_TEST_REGISTER_1  = 0,
	DIAGNOSTICS_TEST_REGISTER_2  = 1,
	DIAGNOSTICS_REGISTER_MAP_MAJOR_MINOR_REVISION   = 2,
	DIAGNOSTICS_RESERVED_1             = 3,

	DIAGNOSTICS_PARAMS_SUBBLOCK_END
}mmApiDiagnosticSubBlockParams;

//PARAMETERSDEF:DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER
/*
	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_CONTROL, control register for debug controller, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network interface configured for debug. Valid values are:
		0 - disable debug controller on a network interface
		1 - enable debug controller on a network interface. This means that the debug controller will be listening for
		debug requests on the network interface.

	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_PHYSICAL_INTERFACE, network physical interface for debug controller, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network interface used for debug. This should only be set when the debug port is disabled.
	  Valid values are:
		0 - network interface 0
		1 - network interface 1

	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_PROTOCOL, network protocol for debug controller, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network protocol used for debug. This should only be set when the debug port is disabled.
	  Valid values are:
		0 - udp over ipv4
		1 - udp over ipv6

	- DIAGNOSTICS_SYSTEM_DEBUG_UART_INTERFACE, uart used for debug messages, rw, 1
	  Bits[31:2] = Reserved
	  Bits[1:0] = 	1 - 1st uart
					2 = 2nd uart

	- DIAGNOSTICS_SYSTEM_DEBUG_UART_ENABLE, enable uart debug messages, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = 	0 = disable
					1 = enable
					Note that these messages are set up to use Baud rate of 115200
					
	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_VIRTUAL_INTERFACE, network virtual interface for debug controller, rw, 0
	  Bits[31:3] = Reserved
	  Bits[2:0] = virtual network interface used for debug. This should only be set when the debug port is disabled.

	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_MHOME_INDEX, network multi home index for debug controller, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0] = multi home index used for debug. This should only be set when the debug port is disabled.

	+ DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_UDP_PORT, UDP port used for debug controller, rw, 323
	  Bits[32:16] = Reserved
	  Bits[15:0] = UDP Port used by debug controller. This should only be set when the debug port is disabled.
*/
typedef enum
{
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_CONTROL = 10,
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_PHYSICAL_INTERFACE	= 16,
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_PROTOCOL	= 17,
	DIAGNOSTICS_SYSTEM_DEBUG_UART_INTERFACE		= 18, 		/* Uart used for debug messages  */
	DIAGNOSTICS_SYSTEM_DEBUG_UART_ENABLE		= 19, 		/* Enable/Disable uart debug messages */
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_VIRTUAL_INTERFACE = 20,
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_MHOME_INDEX = 21,
	DIAGNOSTICS_SYSTEM_DEBUG_CONTROLLER_NETWORK_UDP_PORT = 22,
} mmApiDiagnosticsSystemDebugSubBlockParams;



//PARAMETERSDEF:DIAGNOSTICS_LCD
/*
	+ DIAGNOSTICS_LCD_DISPLAY_PERIOD, The length of time for which each screen is displayed on the LCD, rw, 1
	  Bits[31:0] = Time in secs as a float
					 Notes: The minimum period is 0.5s

	+ DIAGNOSTICS_LCD_BITMASK, The bit mask configures which of the LCD screens to display, rw, 0x1FF
	  Bits[31:9] = Reserved
	  Bits[8:0] =  Each represents which screen to display from the below values. It will not allow all the screens to /
				   be disabled.
					LCD_BIT_PTPSLAVE1 0x1
					LCD_BIT_PTPSLAVE2 0x2
					LCD_BIT_PTPMASTER1 0x4
					LCD_BIT_PTPMASTER2 0x8
					LCD_BIT_NODETIME1 0x10
					LCD_BIT_NODETIME2 0x20
					LCD_BIT_CLOCKPLL1 0x40
					LCD_BIT_CLOCKPLL2 0x80
					LCD_BIT_GENERAL 0x100
					LCD_BIT_USER_DATA 0x2000

	+ DIAGNOSTICS_LCD_FREEZE, This freezes the currently displayed LCD screen, rw, 0x0
	  Bits[31:1] = Reserved
	  Bits[0:0] =  0  - LCD will behave normally and each screen is displayed in turn
				   1  - only the current LCD screen will be displayed
	  /
      Note: If a LCD selection switch is fitted in hardware and Freeze is selected by it, then this software selection has no effect

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_0_3, Chars 0 to 3 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char
	  Notes: eg in the string 'hello' the character 'h' will reside in Bits[31:24]

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_4_7, Chars 4 to 7 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_8_11, Chars 8 to 11 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_12_15, Chars 12 to 15 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_16_19, Chars 16 to 19 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_20_23, Chars 20 to 23 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_24_27, Chars 24 to 27 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_28_31, Chars 28 to 31 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_32_35, Chars 32 to 35 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_36_39, Chars 36 to 39 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_40_43, Chars 40 to 43 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_44_47, Chars 44 to 47 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_48_51, Chars 48 to 51 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_52_55, 52 to 55 Chars to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_56_59, Chars 56 to 59 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

	+ DIAGNOSTICS_LCD_USER_DATA_CHARS_60_63, Chars 60 to 63 to be displayed on lcd display for user data, rw, 0
	  Bits[31:24] = 1st char
	  Bits[23:16] = 2nd char
	  Bits[15:8] =  3rd char
	  Bits[7:0] = 	4th char

*/
typedef enum
{
	DIAGNOSTICS_LCD_DISPLAY_PERIOD	= 0,
	DIAGNOSTICS_LCD_BITMASK			= 1,
	DIAGNOSTICS_LCD_FREEZE			= 2,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_0_3	= 32,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_4_7	= 33,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_8_11	= 34,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_12_15	= 35,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_16_19	= 36,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_20_23	= 37,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_24_27	= 38,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_28_31	= 39,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_32_35	= 40,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_36_39	= 41,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_40_43	= 42,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_44_47	= 43,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_48_51	= 44,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_52_55	= 45,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_56_59	= 46,
	DIAGNOSTICS_LCD_USER_DATA_CHARS_60_63	= 47
} mmApiDiagnosticsLcdSubBlockParams;


//PARAMETERSDEF:DIAGNOSTICS_I2C
/*
    + DIAGNOSTICS_I2C_LOCK_ENABLED, Are certain I2C addresses denied through this API?, rw, 0x1
      Bits[31:1] Reserved
      Bit[0]     '1' - The I2C address between %DIAGNOSTICS_I2C_LOCK_BEGIN_ADDRESS% and %DIAGNOSTICS_I2C_LOCK_END_ADDRESS% /
                       inclusive are locked and cannot be accessed via this API.
                 '0' - All I2C addresses are accessible through this API.

    + DIAGNOSTICS_I2C_LOCK_BEGIN_ADDRESS, Lowest I2C address denied access through this API, ro, 0x60
      Bits[31:7] Reserved
      Bits[6:0]  The lowest I2C address that cannot be accessed (is protected) through this API, if protection is /
                 enabled (%DIAGNOSTICS_I2C_LOCK_ENABLED%). The address does not include the read|write bit.
      /
      Note: The address does not include the read/write bit.

    + DIAGNOSTICS_I2C_LOCK_END_ADDRESS, Highest I2C address denied access through this API, ro, 0x63
      Bits[31:7] Reserved
      Bits[6:0]  The highest I2C address that cannot be accessed (is protected) through this API, if protection is /
                 enabled (%DIAGNOSTICS_I2C_LOCK_ENABLED%). The address does not include the read|write bit.
      /
      Note: The address does not include the read/write bit.

    + DIAGNOSTICS_I2C_ADDRESS, Address to which register (optional) and data (required) will be read or written from, rw, NA
	  Bits[31:7] Reserved
      Bits[6:0]  The I2C address to read or write from. The address must not include the read/write bit.
      /
      Note: The address must not include the read/write bit.
      Note: The I2C access only takes place when the register %DIAGNOSTICS_I2C_DATA% is read or written. This register /
            must be setup prior to this.

    + DIAGNOSTICS_I2C_REGISTER, Register to which data will be read or written, rw, NA
	  Bit[31]     '1' - Use the register address in the I2C access, '0' - register not used in access.
	  Bits[30:16] Reserved
	  Bits[15:0]  The register to be read from or written to.
	  /
      Note: The I2C access only takes place when the register %DIAGNOSTICS_I2C_DATA% is read or written. This register /
            must be setup prior to this.

    + DIAGNOSTICS_I2C_DATA, Data to write or that is read from the address & register values, rw, NA
	  Bits[31:8] Reserved
	  Bits[7:0]  If register is written the value is written to the device at the address specified in register /
	             %DIAGNOSTICS_I2C_ADDRESS% and register specified in %DIAGNOSTICS_I2C_REGISTER%.

	+ DIAGNOSTICS_I2C_LAST_ERROR, Last error to occur, ro, 0
	  Bits[31:0] Valid decimal values and meanings:
					0  - Success
					1  - OS failure
					2  - I2C Module Busy
					3  - A parameter was out of range or invalid
					4  - The slave address was invalid
					5  - A timeout occurred waiting for r/w to complete
					6  - Slave did not acknowledge it's address
					7  - Slave did not acknowledge a register r/w
					8  - Slave did not acknowledge a data write
					9  - Reserved
					10 - General error (generally indicated fatal condition)

 */
typedef enum
{
	DIAGNOSTICS_I2C_LOCK_ENABLED		= 0,
	DIAGNOSTICS_I2C_LOCK_BEGIN_ADDRESS	= 1,
	DIAGNOSTICS_I2C_LOCK_END_ADDRESS	= 2,
	DIAGNOSTICS_I2C_ADDRESS				= 3,
	DIAGNOSTICS_I2C_REGISTER			= 4,
	DIAGNOSTICS_I2C_DATA				= 5,
	DIAGNOSTICS_I2C_LAST_ERROR          = 6
} mmApiDiagnosticsI2CSubBlockParams;


//PARAMETERSDEF:DIAGNOSTICS_DAC
/*
	+ DIAGNOSTICS_DAC_ENABLED, Enable or disable the DAC output, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0]    = Bit value '1' turns DAC on, '0' turns DAC off.

	+ DIAGNOSTICS_DAC_OFFSET, Read/write the DAC control word offset, rw, 0
	  Bits[31:16] = Not used
	  Bits[15:0]  = Dac offset as signed 16-bit integer. This is the offset applied to the DAC central control value 1<<15.

 */
typedef enum
{
	DIAGNOSTICS_DAC_ENABLED = 0,
	DIAGNOSTICS_DAC_OFFSET = 1,
	DIAGNOSTICS_DAC_END
} mmApiDiagnosticsDACSubBlockParams;



//PARAMETERSDEF:DIAGNOSTICS_ECC
/*
	+ DIAGNOSTICS_ECC_ERROR_INSERTION_KEY, enable ecc insertion error, rw, 0x0
	  Bits[31:8] = Reserved
	  Bits[7:0]  = Writing 0x5A will enable insertion errors
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

	+ DIAGNOSTICS_ECC_GENERATE_INSERTION_ERROR, generate ecc insertion error, wo, 0x0
	  Bits[31:1] = Reserved
	  Bits[0:0]  = Bit value '1' generates an insertion error, '0' for normal operation
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

	+ DIAGNOSTICS_ECC_BITS_TO_BE_ERRORED, bitfield for SDRAM bits to be errored , rw, 0
	  Bits[31:0] = If 1st bit is 1 then SDRAM bit 0 is to be error, if 32nd then SDRAM bit 31 is to be errored
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

	+ DIAGNOSTICS_ECC_READ_DOUBLE_ERROR, read ecc double error, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0]  = Bit value '1' means there is an ecc double insertion error
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

	+ DIAGNOSTICS_ECC_READ_SINGLE_ERROR_COUNT, read ecc single error count, ro, 0
	  Bits[31:8] = Reserved
	  Bits[7:0]  = Count of single errors
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

	+ DIAGNOSTICS_ECC_CLEAR, clear ecc error, wo, 0
	  Bits[31:1] = Reserved
	  Bits[0:0]  = Bit value '1' clears an ecc error
	  These ECC items only apply to ACS9520 with ECC memory fitted and enabled

 */
typedef enum
{
	DIAGNOSTICS_ECC_ERROR_INSERTION_KEY = 0,
	DIAGNOSTICS_ECC_GENERATE_INSERTION_ERROR = 1,
	DIAGNOSTICS_ECC_BITS_TO_BE_ERRORED = 2,
	DIAGNOSTICS_ECC_READ_DOUBLE_ERROR = 3,
	DIAGNOSTICS_ECC_READ_SINGLE_ERROR_COUNT = 4,
	DIAGNOSTICS_ECC_CLEAR = 5,
	DIAGNOSTICS_ECC_END
} mmApiDiagnosticsECCSubBlockParams;


#ifdef __cplusplus
}
#endif

#endif
