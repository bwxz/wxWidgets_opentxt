/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: SystemManagementMessageHandler.h $
 * $Revision: 3 $
 * $Date: 24/08/07 14:29 $
 */

/**
 * \file SystemManagementMessageHandler.h
 * This file contains function declerations for the system management message handlers.
 * These handle messages for system and device management, including system start-up/boot
 * functions.
 */

#ifndef SYSTEM_MANAGEMENT_MESSAGE_HANDLER_H
#define SYSTEM_MANAGEMENT_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "DelayMonitorControlInterface.h"
#include "BinaryLockMonitorControlInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToGetHardwareVersionMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSoftwareVersionMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncPartNumberMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSecondsSinceLastResetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
											  uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncLocationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetToPSyncSystemStateMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncSystemStateMsg(const uint8 *requestMessage, uint16 requestMessageLength,
										uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetInitialSystemConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetInitialSystemConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetToPSyncPtpSystemParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncPtpSystemParametersMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetToPSyncUploadConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncUploadConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
												uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetSecurityKeyMsg(const uint8 *requestMessage, uint16 requestMessageLength,
									uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMode2ConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMode2ConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetMode3ConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetMode3ConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetDrmStatisticsMsg(const uint8 *requestMessage, uint16 requestMessageLength,
		uint8 *responseBuffer, uint16 *responseBufferLength);



/******************************************************************************
 * New functions for memory mapped API (This is work in progress)
 * Functionality subject to change
 ******************************************************************************/

/* todo move this to new mmAPI interface types header file */
#define MMAPI_SOFTWARE_VERSION_LENGTH 4 //16 x uint8

/******************************************************************************
 * mmApiSystemManangemetParams Block Description
 * - Subblocks defined by mmApiDiagnosticSubBlock enum
 * - individual parameters defined by mmApiDiagnosticSubBlockParameters enum
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_SYSTEM_MANAGEMENT_PARAMS
typedef enum
{
	SYSTEM_MGMT_PARAMS_SUBBLOCK_APPLICATION    = 0,   			 		/* Application Parameters */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT           = 1,   			 		/* Boot Parameters */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_COMMON = 2,/* Initial System Configuration Parameters */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PORT0 = 3, /* Initial System Configuration Parameters for Port 0 */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PORT1 = 4, /* Initial System Configuration Parameters for Port 1 */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PTP = 5, 	/* Initial System Configuration Parameters for PTP */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_DELAY_MONITOR_CONFIG = 6,				/* System Configuration Parameters for PTP Delay Measurement and Error Counter */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_OUTPUT_PIN_CONFIG = 7,					/* System Configuration Parameters for Binary Lock and Alarm Output pins */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_CONTROL = 8,                       /* External voltage controlled oscillator control */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_INTERFACE = 9,					/* Control interface */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PLUG_AND_PLAY = 11                		/* Plug & Play Configuration */
	//SYSTEM_MGMT_PARAMS_SUBBLOCK_END
} mmApiSystemManagementSubBlock;


//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_PLUG_AND_PLAY
/*
	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SELECT_CFG, Select parameters to save to startup config , rw, 0
	  Bitmask to select which parameters are to be stored within the Plug & Play profile.
	  Note: Clearing a bit to 0 will add the selected parameters to the profile. Setting the bit to 1 will remove it from the profile. Valid configuration options:
	   Bit[0] = Pre-run system configuration (Initialising system state parameters)
	   Bit[1] = Reserved:  Post-run system configuration (Running state parameters)
	   Bit[2] = VLAN configuration network interface 0 (0/0)
	   Bit[3] = VLAN configuration network interface 1 (1/0)
	   Bit[4] = Network interface 0 (0/0) configured
	   Bit[5] = Network interface 1 (1/0) configured
	   Bit[6] = IPv4 configuration network interface 0 (0/0)
	   Bit[7] = IPv4 configuration network interface 1 (1/0)
	   Bit[8] = IPv6 configuration network interface 0 (0/0)
	   Bit[9] = IPv6 configuration network interface 1 (1/0)
	  Bit[10] = Control interface configuration
	  Bits[31:11] = Reserved
	  /
      Warning: Depending on the network configuration of ToPPsync prior to issuing this command ToPSync may fail to respond to subsequent UDP control commands after rebooting.
      In this event the user may use the SPI control interface to configure the device.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SAVE_CFG, Save running config to start up config, rw, 0
	  Bits[0:0] = Configuration Profile Destination
	     1 = Save running configuration to start up configuration

	     All other values reserved
	  /
      Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTORE_CFG, Restore Running Config, rw, 0
	  Bits[0:0] = write 1 to restore saved config to running config
	  /
      Note: This register write is valid in INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_STATUS, PnP Profile Status, ro, 0
	  Bits[31:0] = Operation status
	     0 = Profile disabled
	     1 = Profile active
	     /
	     All other values reserved

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_ERROR, PnP Profile Error, ro, 0
	  Bits[31:0] = Error code
	     0 = Profile checksum ok
	     1 = Profile checksum error
	     2 = Profile not initialised
	     /
	     All other values reserved

    + SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTART_PROTOCOL_ACTIVE, Activate the restart protocol, rw, 0x0
      Bits[31:1] = Reserved
      Bits[0:0]  = 0 - Restart protocol is not activated
       		       1 - Restart protocol is activated
      Note: This register write is valid only in INITIALISING_SYSTEM state over SPI. Setting this in any other state will not alter whether the protocol is activated or deactivated.
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

     + SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTART_PROTOCOL_STATE, Restart protocol current state, rO, 0x0
      Bits[31:2] = Reserved
      Bits[1:0]  = 0 - Restart protocol is waiting for response from management server
    			   1 - Restart protocol has received response from management server
    			   2 - Restart protocol has timed out waiting for management server
	  /
      Note: This register is valid only in INITIALISING_SYSTEM state over SPI.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_NETWORK_FIRMWARE_UPGRADE_ENABLE, Configure network firmware support, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0] = Configure network firmware upgrade support
	  0 = Disabled
	  1 = Enabled
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
      /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_1, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_2, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_3, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_4, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_5, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_6, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_7, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_8, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_9, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_10, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_11, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_12, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_13, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_14, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_15, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_16, Reserved, rw, 0
	  Bits[31:0] = Reserved
	  /
      Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_ERASE_SECTOR, Erase PnP sector, RW, 0
	  Bits[31:0] = Writing 0xACCEEDED to this register will erase lower sector
	  Note: This is only required if uploading an application version prior to R2.2
	  and PnP data has been stored.
	  WARNING this will erase stored PnP settings

 */

typedef enum
{
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SELECT_CFG = 0,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SAVE_CFG = 1,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTORE_CFG = 2,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_STATUS = 3,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_ERROR = 4,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTART_PROTOCOL_ACTIVE = 32,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESTART_PROTOCOL_STATE = 33,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_NETWORK_FIRMWARE_UPGRADE_ENABLE = 48,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SGMII_PCS_CONFIG_PHYS_PORT0 = 64,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_SGMII_PCS_CONFIG_PHYS_PORT1 = 65,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_1 = 66,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_2 = 67,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_3 = 68,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_4 = 69,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_5 = 70,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_6 = 71,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_7 = 72,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_8 = 73,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_9 = 74,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_10 = 75,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_11 = 76,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_12 = 77,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_13 = 78,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_14 = 79,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_15 = 80,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_RESERVED_16 = 81,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_ERASE_SECTOR = 128,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PNP_END
}mmApiSystemManagementSubBlockPnPParams;


//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_RESTART_PROTOCOL
/*
    + SYSTEM_MGMT_PARAMS_RESTART_PROTOCOL_ACTIVE, activate the restart protocol, rw, 0x0
    Bits[31:1] = Reserved
    Bits[0:0]  = 0 - restart protocol is not activated
    			 1 - restart protocol is activated
    Notes: Writing a value to this will only have an effect if done over SPI in the INITIALISING SYSTEM state.
    Setting this in any other state will not alter whether the protocol is activated or deactivated.

     + SYSTEM_MGMT_PARAMS_RESTART_PROTOCOL_STATE, restart protocol current state, rO, 0x0
    Bits[31:2] = Reserved
    Bits[1:0]  = 0 - restart protocol is waiting for response from management server
    			 1 - restart protocol has received response from management server
    			 2 - restart protocol has timed out waiting for management server

*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_RESTART_PROTOCOL_ACTIVE			= 0,
	SYSTEM_MGMT_PARAMS_RESTART_PROTOCOL_STATE			= 1
}mmApiSystemManagementParamsSubblockRestartProtocol;




//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_CONTROL
/*
	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_SELECT, Select PLL to control VCXO, rw, 6
	  Bits[31:4] = Reserved
	  Bits[3:0]  = Source
	      Valid bit (decimal) values:
	      000 (0) Clock PLL 1
	      001 (1) Clock PLL 2
	      010 (2) PTP PLL 1 (see notes)
	      011 (3) PTP PLL 2 (see notes)
	      100 (4) NODE PLL 1
	      101 (5) NODE PLL 1
	      110 (6) VCXO control is disabled
	   /
	   Notes: This is a one-shot setup of the device. To configure the minimum and maximum DAC levels use register /
	   %SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_DAC_PARAMS% and to configure the update frequency of the VCXO use /
	   register %SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_UPDATE_PERIOD_MSECS%.
	   /
	   Notes: If the PLL is to be driven by the node time then the register %NODE_TIME_CONFIG_PARAMS_SET_SELECTED_INPUT% /
	   must first be configured with the source that is to drive node time. The node time will not select any other source /
	   other than this one until the VCXO has finished calibrating. Once calibration has finished the node time source /
	   selection will operate as normal.

	 + SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_UPDATE_PERIOD_MSECS, Set the minumum VCXO update period in milliseconds, rw, 100
	   Bits[31:0] Unsigned 32-bit integer representing the minimum update period (meaning maximum update frequency) for the /
	              VCXO in milliseconds
	   /
	   Notes: When VCXO control has not been enabled using register %SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_SELECT% this /
	          register will read back zero. The default minimum update period when VCXO control is active is 100ms (10Hz). /
	          If the minimum update period is to be set, it should be set immediately after VCXO control is enabled.

	 + SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_DAC_PARAMS, Set DAC minimum and maximum levels, rw, 0xFFFF0000
	   Bits[31:16] An unsigned 16-bit integer expressing the maximum DAC level. DAC is 16 bits wide.
	   Bits[15:0]  An unsigned 16-bit integer expressing the minimum DAC level. DAC is 16 bits wide.
	   /
       By default the DAC value can range from 0 to 65,535, which will correspond to voltage outputs at DACOUT of
       DACNEG volts to DACPOS volts. Should the voltage range output by the DAC need to be restricted these registers
       can be used to accomplish this.
	   /
	   Notes: This register must be set before register %SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_SELECT% is written if
	   the DAC levels are to be applied.

	 + SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_HIU, Read the Hardware frequency Integer Unit (HIU) resulting from VCXO auto-calibration, ro, n/a
 	   Bits[31:0] HIU expressed as a single precision floating point number.
 	   /
 	   Notes: If the VCXO has not been calibrated or is not being used then the register returns 0.0

 */
typedef enum
{
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_SELECT = 0,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_UPDATE_PERIOD_MSECS = 1,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_DAC_PARAMS = 2,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_PLL_HIU = 3,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VCXO_END
}mmApiSystemManagementSubBlockVcxoParams;

//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_APPLICATION
/*
	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_HARDWARE_VERSION, Hardware Version, ro, 0
	  Bits[31:0] = Hardware Version e.g. 95020200

    + SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_0_3, Application Software Version, ro, 0
	  Returns 16 character Software Version
	  Bits[31:0] = First 4 characters (e.g. 'ts2A' if Software Version = 'ts2ApiDev_dc1')

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_4_7, Application Software version, ro, 0
	  Bits[31:0] = Characters 5 to 8 (e.g. 'piDev' using above example)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_8_11, Application Software version, ro, 0
	  Bits[31:0] = Characters 9 to 12 (e.g. 'v_dc' using above example)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_12_15, Application Software version, ro, 0
	  Bits[31:0] = Characters 13 to 16 (e.g. '1   ' using above example)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE, ToPSync System State, rw, 0
	  Bits[31:0] = ToPSync State (e.g. TOPSYNC_BOOT_STATE, TOPSYNC_RUNNING_STATE etc.)
	  Permitted values:
	  	0 - BOOT				  		Initial POR state
		1 - INITIALISING SYSTEM			System is being initialised
		2 - INITIALISING APPLICATION	Application is being initialised
		3 - RUNNING						Application is running
		4 - SOFTWARE CORRUPT			CRC check of the application image has failed
		5 - EXCEPTION					A fatal exception has been detected

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_TIME_SINCE_LAST_RESET, Time in seconds since last reset, ro, 0
	  Bits[31:0] = Elapsed time in seconds since the last reset of the ToPSync device

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_NETWORK_UPLOAD_FLAG, Network Upload Flag, ro, 0
	  Bits[31:1] = reserved
	  Bits[0] = Network Upload Flag
	  Permitted values:
	    0 - Indicates that SPI Uploaded Application is running
	    1 - Indicates that Network Uploaded Application is running

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_0_3, Module Serial Number ACS9860 parts only, ro, 0
	  Serial number comprise 12 ASCII encoded bytes [0,1,2,3,4,5,6,7,8,9,10,11], eg:'A114370001-08' where byte 0 = 'A'(0x41), byte 1 = '1'(0x31), byte 11 = '8'(0x38)
      Bits[31:24] = byte 0
      Bits[23:16] = byte 1
      Bits[15:8] = byte 2
      Bits[7:0] = byte 3

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_4_7, Module Serial Number ACS9860 parts only, ro, 0
      Bits[31:24] = byte 4
      Bits[23:16] = byte 5
      Bits[15:8] = byte 6
      Bits[7:0] = byte 7

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_8_11, Module Serial Number ACS9860 parts only, ro, 0
      Bits[31:24] = byte 8
      Bits[23:16] = byte 9
      Bits[15:8] = byte 10
      Bits[7:0] = byte 11

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_TEST_DATE_CODE, Module Test Date Code, ro, 0
	  Bits[31:0] = (Reserved for ACS9860 modules)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_PRODUCT_CODE, Module Product Code, ro, 0
	  Bits[31:0] = (Reserved for ACS9860 modules)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_REVISION, Module Revision, ro, 0
	  Bits[31:0] = (Reserved for ACS9860 modules)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_CHECKSUM_STORED, Stored boot checksum, ro, -
	  Bits[31:0] = Stored value of boot checksum

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_CHECKSUM_CALC, Calculated boot checksum, ro, -
	  Bits[31:0] = Calculated value of boot checksum

*/

typedef enum
{
	SYSTEM_MGMT_PARAMS_SUBBLOCK_HARDWARE_VERSION = 0,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_0_3 =   1,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_4_7 =   2,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_8_11 =  3,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SOFTWARE_VERSION_BYTES_12_15 = 4,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE = 5,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_TIME_SINCE_LAST_RESET = 6,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_NETWORK_UPLOAD_FLAG = 7,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_0_3 = 16,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_4_7 = 17,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_SERIAL_NUMBER_BYTES_8_11 = 18,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_TEST_DATE_CODE = 19,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_PRODUCT_CODE = 20,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_MODULE_REVISION = 21,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_CHECKSUM_STORED = 32,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_CHECKSUM_CALC   = 33,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_END
}mmApiSystemManagementSubBlockParams;



//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT
/*
    + SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_0_3, Factory Boot Software Version, ro, 0
	  Returns 16 character Software Version.
	  Bits[31:0] = First 4 characters (e.g. 'BR2.' if Software Version = 'BR2.1.1dc2  ')
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_4_7, Factory Boot Software version, ro, 0
	  Bits[31:0] = Characters 5 to 8 (e.g. '1.1d' using above example)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_8_11, Factory Boot Software version, ro, 0
	  Bits[31:0] = Characters 9 to 12 (e.g. 'c2  ' using above example)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_12_15, Factory Boot Software version, ro, 0
	  Bits[31:0] = Characters 13 to 16 (e.g. '    ' using above example)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

    + SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_0_3, Field Boot Software Version, ro, 0
	  Returns 16 character Software Version.
	  Bits[31:0] = First 4 characters (See Factory Boot Software version)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_4_7, Field Boot Software version, ro, 0
	  Bits[31:0] = Characters 5 to 8 (See Factory Boot Software version)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_8_11, Field Boot Software version, ro, 0
	  Bits[31:0] = Characters 9 to 12 (Factory Boot Software version)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_12_15, Field Boot Software version, ro, 0
	  Bits[31:0] = Characters 13 to 16 (Factory Boot Software version)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_TOPSYNC_PART_NUMBER, Flash programmed part number, ro, 0
	  Bits[31:0] = Generic ToPSync family device number (Deprecated)
	  Note: Valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE, Device start up mode, rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:8]   = Boot select. Valid values
	  0 = Factory boot (default)
	  1 = Field Boot
	  All others reserved
	  Bits[7:0]  = Boot mode. Valid values:
	  0 = Network boot (not yet supported)
	  1 = Plug & Play
	  2 = Product Boot (default)
	  All others reserved
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
      /
	  Warning: Writing to this parameter will cause the default startup configuration held in Flash memory to be updated.
	  All Flash memory devices have a limited lifetime and should be written to ONLY if the contents require updating.
	  /
	  Semtech does not recommend executing any unnecessary writes to this parameter.

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_DEBUG_PRINT, Debug printf enabled/disable, rw, 0
	  Bits[31:2] = Reserved
	  Bits[1:0]  = Boot debug printf enable.  Valid values:
	  0 Debug disabled (default),
	  1 Debug output enabled on UART0
	  2 Debug output enabled on UART1
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_RESET, Boot reset, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0]     = Reset device. 
	  Setting this bit to '1' will force an immediate software reset and reboot of the ToPSync device. This bit is self clearing.
	  /
	  Note: This register write is valid in BOOT state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT0_HIGH, Non volatile user programmed MAC address Port 0 (High), rw, 0
      Bits[31:24] = MAC address byte 0 (Most significant byte of 6-byte MAC address )
      Bits[23:16] = MAC address byte 1
      Bits[15:8] = MAC address byte 2
      Bits[7:0] = MAC address byte 3
	  e.g. MAC Address 00:16:C0:1F:B1:00 Byte 0 = 0x00, byte 1 = 0x16, byte 2 = 0xC0, byte 3 = 0x1F
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT0_LOW, Non volatile user programmed MAC address Port 0 (Low), rw, 0
      Bits[31:24] = MAC address byte 4
      Bits[23:16] = MAC address byte 5 (Least significant byte of 6-byte MAC address )
      Bit[15:0] = Reserved
	  e.g. MAC Address 00:16:C0:1F:B1:00 Byte 4 = 0xB1, byte 5 = 0x00
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_USE_DHCP, Port 0 DHCP enable / disable, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0]     = DHCP enabled. Valid values:
	  0 DHCP disabled
	  1 DHCP enabled
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_DHCP_LEASE_PERIOD,  Port 0 DHCP lease period, rw, 604800
	  Bits[31:0] = Lease period in seconds
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_IPADDRESS,  Port 0 IP address, rw, 0
	  Bits[31:0] = IP4 address 
	  e.g. the value 0xC0A87B84 represents the IP4 address 192.168.123.132
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_SUBNET,  Port 0 Subnet mask, rw, 0
	  Bits[31:0] = Subnet mask
	  e.g. the value 0xFFFFFFC0 represents the subnet 255.255.255.192
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_DEFAULT_GATEWAY,  Port 0 Default gateway, rw, 0
	  Bits[31:0] = Default gateway
	  e.g. the value 0xFFFFFF00 represents the default gateway 255.255.255.00
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SGMII_MODE_PORT0, Network port 0 SGMII configuration, rw, 0
	  Bits[31:2] = Reserved
	  Bit[1:0] = Network port 0 SGMII configuration. Valid values:
	  Bit[0] = Network port 0 SGMII MAC or PHY mode
      0 Network port 0 configured as MAC side of SGMII link
	  1 Network port 0 configured as PHY side of SGMII link
	  Bit[1] = Reserved
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT1_HIGH, Non volatile user programmed MAC address Port 1 (High), rw, 0
      Bits[31:24] = MAC address byte 0 (Most significant byte of 6-byte MAC address )
      Bits[23:16] = MAC address byte 1
      Bits[15:8] = MAC address byte 2
      Bits[7:0] = MAC address byte 3
	  e.g. MAC Address 00:16:C0:1F:B1:01 Byte 0 = 0x00, byte 1 = 0x16, byte 2 = 0xC0, byte 3 = 0x1F
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT1_LOW, Non volatile user programmed MAC address Port 1 (Low), rw, 0
      Bits[31:24] = MAC address byte 4
      Bits[23:16] = MAC address byte 5 (Least significant byte of 6-byte MAC address )
      Bit[15:0] = Reserved
	  e.g. MAC Address 00:16:C0:1F:B1:01 Byte 4 = 0xB1, byte 5 = 0x01
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_USE_DHCP, Port 1 DHCP enable / disable, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0]     = DHCP enabled. Valid values:
	  0 DHCP disabled
	  1 DHCP enabled
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_DHCP_LEASE_PERIOD,  Port 1 DHCP lease period, rw,604800
	  Bits[31:0] = Lease period in seconds
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_IPADDRESS,  Port 1 IP address, rw, 0
	  Bits[31:0] = IP4 address 
	  e.g. the value 0xC0A87B84 represents the IP4 address 192.168.123.132
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_SUBNET,  Port 1 Subnet mask, rw, 0
	  Bits[31:0] = Subnet mask
	  e.g. the value 0xFFFFFFC0 represents the subnet 255.255.255.192
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_DEFAULT_GATEWAY,  Port 1 Default gateway, rw, 0
	  Bits[31:0] = Default gateway
	  e.g. the value 0xFFFFFF00 represents the default gateway 255.255.255.00
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SGMII_MODE_PORT1, Network port 1 SGMII configuration, rw, 0
	  Bits[31:2] = Reserved
	  Bit[1:0] = Network port 1 SGMII configuration. Valid values:
	  Bit[0] = Network port 1 SGMII MAC or PHY mode
      0 Network port 1 configured as MAC side of SGMII link
	  1 Network port 1 configured as PHY side of SGMII link
	  Bit[1] = Reserved
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_PHYSICAL_PORT_ACTIVE_CONFIG, Select which port is active, rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:8] Port 1 enabled.
	  Bits[7:0] Port 0 enabled. Valid values:
      0 Port disabled
      1 Port enabled
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_CONFIG_PORT0, Port 0 VLAN enable/disable , rw, 0
	  Bits[31:1] = Reserved
	  Bit [0] = Vlan enabled. Valid values:
      1 VLAN enabled
	  0 VLAN disabled
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_CONFIG_PORT1, Port 1 VLAN enable/disable , rw, 0
	  Bits[31:1] = Reserved
	  Bit [0] = Vlan enabled. Valid values:
      1 VLAN enabled
	  0 VLAN disabled
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_TAG_PORT0, Port 0 VLAN tag , rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:13] = Priority Code Point(Point). This refers to the IEEE 802.1p
					priority. It sets the value that will be written to the
					VLAN header when a frame is transmitted on this interface.
	  Bits[12:12] = Drop Eligible Indicator(DEI). This indicates whether a
				    frame is eligible to be dropped in the presence of
				    congestion. It sets the value that will be written to the
				    VLAN header when a frame is transmitted on this interface.
	  Bits[11:0]  = VLAN identifier(VID). This specifies the value of the VID
				    that the interface belongs to. The interface will send and
				    receive frames with this VID set in the VLAN header. The
				    values 0x000 and 0xFFF are reserved.
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_TAG_PORT1, Port 1 VLAN tag , rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:13] = Priority Code Point(PCP). This refers to the IEEE 802.1p
					priority. It sets the value that will be written to the
					VLAN header when a frame is transmitted on this interface.
	  Bits[12:12] = Drop Eligible Indicator(DEI). This indicates whether a
				    frame is eligible to be dropped in the presence of
				    congestion. It sets the value that will be written to the
				    VLAN header when a frame is transmitted on this interface.
	  Bits[11:0]  = VLAN identifier(VID). This specifies the value of the VID
				    that the interface belongs to. The interface will send and
				    receive frames with this VID set in the VLAN header. The
				    values 0x000 and 0xFFF are reserved.
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_PRODUCT_TYPE, Product type , rw, 0xFFFFFFFF
	  Bits[31:0] = Product type (reserved)
	  /
	  Note: This register write is valid in BOOT or INITIALISING_SYSTEM state only. Register read is valid in all states (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).
	  /
	  Warning: Semtech does not recommend executing any unnecessary writes to this parameter. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE%)

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_CONTROL, Ethernet self test control, rw, 0
	  Bits[31:0] = Configure self test operation. Valid values:
	  0 Stop
	  1 Start
	  2 Busy
	  All others reserved
	  /
	  Note: This register is valid in BOOT state only. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_STATUS, Ethernet self test status, ro, 0
	  Bits[31:0] = Test state Valid values:
	  0 Idle
      1 Initialising link test
      2 Link test SGMII Port 0
      3 Link test SGMII Port 1
      4 Initialising Ethernet test
      5 Ethernet Tx/Rx test
      6 Halt link error (No valid link detected)
      7 Stopping
      All others reserved
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PORT0_PACKET_COUNT, Ethernet self test TX packet count, ro, 0
	  Bits[31:16] = Number of test packets received by ToPSync
	  Bits[15:0] = Number of test packets transmitted by ToPSync
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

    + SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PORT1_PACKET_COUNT, Ethernet self test RX packet count, ro, 0
	  Bits[31:16] = Number of test packets received by ToPSync
	  Bits[15:0] = Number of test packets transmitted by ToPSync
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_SERDES_STATUS, SERDES status register, ro, 0x00000000
	  Bits[31:7] = Reserved
	  Bit[6] = Serdes1 Rx clock detect, goes high when Rx PLL acquires lock
	  Bit[5] = Serdes1 Lock Detect output, goes high when Tx PLL acquires lock
	  Bit[4] = Serdes1 Squelch detector output, goes High when Rx input signal amplitude exceeds 150mV
	  Bit[3] = Reserved
	  Bit[2] = Serdes0 Rx clock detect, goes high when Rx PLL acquires lock
	  Bit[1] = Serdes0 Lock Detect output, goes high when Tx PLL acquires lock
	  Bit[0] = Serdes0 Squelch detector output, goes High when Rx input signal amplitude exceeds 150mV
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PCS0_STATUS, PCS0 status register, ro, 0x00000009
	  Bits[31:6] = Reserved
	  Bit[5] = Auto negotiation complete. Valid values:
	  0 = Auto negotiation not complete or not enabled
	  1 = Auto negotiation complete
	  Bits[4:3] = Reserved
	  Bit[2] = Link Status. Valid values:
	  0 = Link not valid
	  1 = Link valid
	  Bits[1:0] = Reserved
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

	- SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PCS1_STATUS, PCS1 status register, ro, 0x00000009
	  Bits[31:6] = Reserved
	  Bit[5] = Auto negotiation complete. Valid values:
	  0 = Auto negotiation not complete or not enabled
	  1 = Auto negotiation complete
	  Bits[4:3] = Reserved
	  Bit[2] = Link Status. Valid values:
	  0 = Link not valid
	  1 = Link valid
	  Bits[1:0] = Reserved
	  /
	  Note: This register is only valid in BOOT state. (See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%).

*/
typedef enum
{
	// USE C++ STYLE COMMENTS HERE SO THAT MMAPI DOC SCRIPT CAN IGNORE THESE COMMENTS
	// Hardware version, application software version and system state are
	// defined by mmApiSystemManagementSubBlockParams therefore omitted
	// from this section
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_0_3    = 6, /* Software Version - Read Only */
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_4_7    = 7,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_8_11   = 8,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FACTORY_BOOT_SOFTWARE_VERSION_BYTES_12_15  = 9,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_0_3      = 10,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_4_7      = 11,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_8_11     = 12,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_FIELD_BOOT_SOFTWARE_VERSION_BYTES_12_15    = 13,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_TOPSYNC_PART_NUMBER                        = 14,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_DEVICE_STARTUP_MODE                        = 15,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_DEBUG_PRINT                                = 16,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_BOOT_RESET                                 = 17,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT0_HIGH            = 32,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT0_LOW             = 33,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_USE_DHCP           = 34,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_DHCP_LEASE_PERIOD  = 35,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_IPADDRESS          = 36,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_SUBNET             = 37,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT0_DEFAULT_GATEWAY    = 38,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SGMII_MODE_PORT0                           = 39,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT1_HIGH            = 64,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_ETHERNET_MAC_ADDRESS_PORT1_LOW             = 65,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_USE_DHCP           = 66,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_DHCP_LEASE_PERIOD  = 67,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_IPADDRESS          = 68,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_SUBNET             = 69,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_IP_STARTUP_CONFIG_PORT1_DEFAULT_GATEWAY    = 70,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SGMII_MODE_PORT1                           = 71,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_PHYSICAL_PORT_ACTIVE_CONFIG                = 72,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_CONFIG_PORT0                          = 73,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_CONFIG_PORT1                          = 74,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_TAG_PORT0                             = 75,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_VLAN_TAG_PORT1                             = 76,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_PRODUCT_TYPE                               = 77,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_CONTROL                           = 128,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_STATUS                            = 129,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PORT0_PACKET_COUNT                = 130,
    SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PORT1_PACKET_COUNT                = 131,
    SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_SERDES_STATUS                     = 132,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PCS0_STATUS                       = 133,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_SELFTEST_PCS1_STATUS                       = 134,

	SYSTEM_MGMT_PARAMS_BOOT_END
}mmApiSystemManagementBootSubBlockParams;


//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_COMMON
/*
	+ SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_TYPE, control interface type, rw, 0
	  To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:1] = Reserved
	  Bit[0] = Control interface type. Valid values:
		  0	UDP
		  1 SPI

	+ SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_NUMBER, control network interface number, rw, 0
	  To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:1] = Reserved
	  Bits[0] = Specifies the network interface that can process ToPSync control packets and generate ToPTrace data. Valid values:
		  0 - network interface 0
		  1 - network interface 1

	+ SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_UDP_MANAGEMENT_PORT, UDP management port, rw, 2000
	  To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:16] = Reserved
	  Bits[15:0] = Specifies the UDP port used by the control interface.

    - SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_SECURITY_KEY, security key, rw, 0
      To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:0] = Security key

    - SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_LOCATION_IDENTIFIER, location identifier, rw, 0
      To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:0] = Location identifier

    - SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_MDIO_CONFIGURATION, MDIO configuration, rw, 0
      To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:1] = Reserved
	  Bit[0] = MDIO enabled. Valid values:
		  0 mdio disabled
		  1 mdio enabled

	+ SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_NETWORK_PROTOCOL, control network interface network protocol, rw, 0
	  To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:1] = Reserved
	  Bits[0] = Specifies the protocol of network interface that can process ToPSync control packets and generate ToPTrace data. Valid values:
		  0 - ipv4
		  1 - ipv6
*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_TYPE = 0,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_NUMBER = 1,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_UDP_MANAGEMENT_PORT = 2,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_SECURITY_KEY = 3,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_LOCATION_IDENTIFIER = 4,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_MDIO_CONFIGURATION = 5,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_CONTROL_INTERFACE_NETWORK_PROTOCOL = 8,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_END
}mmApiSystemManagementParamsSubblockInitialSystemConfiguration;

//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PORT0
//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PORT1
/*
    - SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_ETHERNET_CONFIGURATION, Ethernet configuration, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0]     = Ethernet enabled. Valid values:
		  0 Ethernet disabled
		  1 Ethernet enabled

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_CONFIGURATION, IP4 configuration, rw, 0
	  Bits[31:1] = Reserved
	  Bit[0]     = IP4 enabled. Valid values:
		  0 IP4 disabled
		  1 IP4 enabled

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DHCP_CONFIGURATION, IP4 DHCP configuration, rw, 1
	  Bits[31:1] = Reserved
	  Bit[0]     = DHCP enabled. Valid values:
		  0 DHCP disabled
		  1 DHCP enabled

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DHCP_LEASE_PERIOD, DHCP lease period, rw, 604800
	  Bits[31:0] = Lease period

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_ADDRESS, IP4 address, rw, 0
	  Bits[31:0] = IP4 address

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_SUBNET_MASK, Subnet mask, rw, 0
	  Bits[31:0] = subnet mask

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DEFAULT_GATEWAY_ADDRESS, Default gateway, rw, 0
	  Bits[31:0] = Default gateway

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_SGMII_CONFIGURATION, SGMII configuration, rw, 1
	  Bits[31:2] = Reserved
	  Bits[1:0]  = MII mode. Valid values:
	  	  00 Network port configured as MII
		  01 Network port configured as MAC side of SGMII link
		  10 Network port configured as PHY side of SGMII link
	  /
	  Note: MII can only be configured on one network interface

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_CONFIGURATION, Port configuration, rw, 0
	  Bits[31:1] = Reserved
      Bit[0] = Port enabled. Valid values:
		  0	Port disabled
		  1	Port enabled

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_VLAN_CONFIGURATION, Vlan configuration, rw, 0
	  Bits[31:0] = Reserved
	  Bit[0] = Vlan enabled. Valid values:
		  0 Vlan disabled
		  1 Vlan enabled

	- SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_VLAN_TAG, Vlan tag register, rw, 0
	  Bits[31:16] = Reserved
	  Bits[15:13] = Priority Code Point(PCP). This refers to the IEEE 802.1p
					priority. It sets the value that will be written to the
					VLAN header when a frame is transmitted on this interface.
	  Bits[12:12] = Drop Eligible Indicator(DEI). This indicates whether a
				    frame is eligible to be dropped in the presence of
				    congestion. It sets the value that will be written to the
				    VLAN header when a frame is transmitted on this interface.
	  Bits[11:0]  = VLAN identifier(VID). This specifies the value of the VID
				    that the interface belongs to. The interface will send and
				    receive frames with this VID set in the VLAN header. The
				    values 0x000 and 0xFFF are reserved.
*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_ETHERNET_CONFIGURATION		 = 0,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_CONFIGURATION			 = 1,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DHCP_CONFIGURATION		 = 2,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DHCP_LEASE_PERIOD		 = 3,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_ADDRESS 				 = 4,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_SUBNET_MASK 			 = 5,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_IP4_DEFAULT_GATEWAY_ADDRESS = 6,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_SGMII_CONFIGURATION		 = 7,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_CONFIGURATION				 = 8,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_VLAN_CONFIGURATION			 = 9,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_VLAN_TAG					 = 10,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PORT_END
}mmApiSystemManagementParamsSubblockInitialSystemConfigurationPort;

//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_INITIAL_SYSTEM_CONFIGURATION_PTP
/*
    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_UDP_EVENT_PORT, PTP UDP event port, rw, 319
      To set this parameter, it must be set when the system is in initialising system state.
      Bits[31:16] = Reserved
      Bit[15:0] = UDP event port

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_UDP_GENERAL_PORT, PTP UDP general port, rw, 320
	  To set this parameter, it must be set when the system is in initialising system state.
      Bits[31:16] = Reserved
      Bits[15:0] = UDP general port

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_MULTICAST_ADDRESS, PTP IP4 multicast address, rw, 0xE0000181
      To set this parameter, it must be set when the system is in initialising system state.
      Bits[31:0] = IP4 Multicast address

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_EVENT_TOS, IP4 event type-of-service, rw, 0xB8
      To set this parameter, it must be set when the system is in initialising system state.
      Bits[31:8] = Reserved
      Bits[7:0] = IP4 event type-of-service

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_GENERAL_TOS, PTP IP4 general type-of-service, rw, 0
      To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:8] = Reserved
	  Bits[7:0] = IP4 general type of service

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERTYPE, PTP Ethernet ethertype, rw, 0x88F7
      To set this parameter, it must be set when the system is in initialising system state.
	  Bits[31:16] = Reserved
	  Bits[15:0] = Ethertype for Ethernet PTP messages

    + SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERNET_MULTICAST_ADDRESS_1, PTP ethernet multicast address bytes 0-3, rw, 0x011B1900
      To set this parameter, it must be set when the system is in initialising system state.
	  Ethernet Address:
	  Bits[31:24] = Ethernet address byte 0
	  Bits[23:16] = Ethernet address byte 1
	  Bits[15:8]  = Ethernet address byte 2
	  Bits[7:0]   = Ethernet address byte 3

	+ SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERNET_MULTICAST_ADDRESS_2, PTP ethernet multicast address bytes 4=5, rw, 0
	  To set this parameter, it must be set when the system is in initialising system state.
	  Ethernet Address:
	  Bits[31:24] = Ethernet address byte 4
	  Bits[23:16] = Ethernet address byte 5
	  Bit[15:0]   = Reserved
*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_UDP_EVENT_PORT = 0,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_UDP_GENERAL_PORT = 1,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_MULTICAST_ADDRESS = 2,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_EVENT_TOS = 3,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_IP4_GENERAL_TOS = 4,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERTYPE = 5,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERNET_MULTICAST_ADDRESS_1 = 6,
	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_ETHERNET_MULTICAST_ADDRESS_2 = 7,

	SYSTEM_MGMT_PARAMS_INITIAL_SYSTEM_CONFIGURATION_PTP_END
}mmApiSystemManagementParamsSubblockInitialSystemConfigurationPtp;


//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_OUTPUT_PIN_CONFIG
/*
    + SYSTEM_MGMT_PARAMS_CONFIG_OUTPUT_PINS, config for binary lock and alarm pins, rw, 0x4
      Bits[31:3] = Reserved
      Bits[2:2]	=  0 - alarm active drive enable off
				   1 - alarm active drive enable on
      Bits[1:1]	=  0 - alarm polarity, pin is high when an enabled alarm is active and low when all enabled alarms are inactive,
				   1 - alarm polarity, pin is low when an enabled alarm is active and high when all enabled alarms are inactive
      Bits[0:0]	=  0 - binary lock pin is high when binary lock is high (ie no binary lock alarms active) and low when binary lock is low (a binary lock low alarm is active)
				   1 - binary lock pin is high when binary lock is low (ie a binary lock alarm is active) and low when binary lock is high (ie no binary lock alarms active)
*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_CONFIG_OUTPUT_PINS			= BINARY_LOCK_MONITOR_TOP_CONFIG_LOCK_OUTPUT_PIN
}mmApiSystemManagementParamsSubblockBinaryLockMonitorOutputPinConfig;

//PARAMETERSDEF:SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_INTERFACE
/*
	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_CONTROL, control register for control interface, rw, 0
	  Bits[31:2] = Reserved
	  Bits[1:0] = control register for debug over network interface
		0 - disable control network interface
		1 - enable control network interface
		2 - change control network interface. This option disables the existing configuration and setups the
		configuration from the control registers.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_PHYSICAL_INTERFACE, physical network interface for control configuration, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = physical network interface used for control configuration.
		0 - network interface 0
		1 - network interface 1

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_VIRTUAL_INTERFACE, virtual network interface for control configuration, rw, 0
	  Bits[31:3] = Reserved
	  Bits[2:0] = virtual network interface used for control configuration.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_MHOME_INDEX, multi home index for control network interface configuration, rw, 0
	  Bits[31:4] = Reserved
	  Bits[3:0] = multi home index used for control configuration.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_PROTOCOL, network protocol for control configuration, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network protocol used for control configuration.
		0 - udp over ipv4
		1 - udp over ipv6

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_UDP_PORT, udp port for  control interface configuration, rw, 2000
	  Bits[31:16] = Reserved
	  Bits[15:0] = UDP port used for control configuration.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_CONTROL, control interface status, rw, 0
	  Bits[31:2] = Reserved
	  Bits[1:0] = network control interface status
		0 - control network interface disabled
		1 - control network interface enabled

    + SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_PHYSICAL_INTERFACE, physical network interface for control status, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network interface used for control status.
		0 - physical network interface 0
		1 - physical network interface 1

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_VIRTUAL_INTERFACE, virtual network interface for control status, ro, 0
	  Bits[31:3] = Reserved
	  Bits[2:0] = virtual network interface used for control status.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_MHOME_INDEX, multi home index for control network interface status, ro, 0
	  Bits[31:4] = Reserved
	  Bits[3:0] = multi home index used for control status.

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_PROTOCOL, network protocol for control status, ro, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = network protocol used for control status.
		0 - udp over ipv4
		1 - udp over ipv6

	+ SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_UDP_PORT, udp port for  control interface status, ro, 2000
	  Bits[31:16] = Reserved
	  Bits[15:0] = UDP port used for control messages status.
*/
typedef enum
{
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_CONTROL = 0,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_PHYSICAL_INTERFACE = 10,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_VIRTUAL_INTERFACE = 11,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_MHOME_INDEX = 12,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_NETWORK_PROTOCOL = 13,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_UDP_PORT = 14,

	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_CONTROL = 19,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_PHYSICAL_INTERFACE = 20,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_VIRTUAL_INTERFACE = 21,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_MHOME_INDEX = 22,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_NETWORK_PROTOCOL	= 23,
	SYSTEM_MGMT_PARAMS_SUBBLOCK_CONTROL_STATUS_UDP_PORT			= 24,
}mmApiSystemManagementParamsSubblockControlInterface;



ToPSyncConfigResult mmApiGetSystemManagementConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetSystemManagementConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

ToPSyncConfigResult mmAPIProcessGetSystemMgmtApplicationParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessSetSystemMgmtApplicationParams(uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessGetSystemControlParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessSetSystemControlParams(uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessSetSystemMgmtPnPParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetSystemMgmtPnPParams(uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessGetSystemMgmtBootParams(uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessSetSystemMgmtBootParams(uint16 startAddress, uint16 endAddress, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
