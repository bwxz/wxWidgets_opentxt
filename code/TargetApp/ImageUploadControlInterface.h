/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */

/**
 * \file ImageUploadControlInterface.h
 * This file contains the declarations of the routines for the Image Upload
 * control message set.
 */

#ifndef IMAGE_UPLOAD_CONTROL_INTERFACE_H
#define IMAGE_UPLOAD_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult mmApiSetImageUploadParams(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetImageUploadParams(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);

//SUBBLOCKSDEF:MMAPI_IMAGE_UPLOAD_PARAMS
typedef enum
{
	IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_STATUS  		= 0,   /* Upload Status */
	IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_CONFIG  		= 1,   /* Upload Configuration */
	IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_DATA  		= 2,   /* Upload Data */

	IMAGE_UPLOAD_PARAMS_SUBBLOCK_END
} mmApiImageUploadSubBlock;

//PARAMETERSDEF:IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_STATUS
/*
	+ IMAGE_UPLOAD_STATUS_PARAMS_STATE, State of image upload process, ro, 0
	Bits[31:3] reserved
	Bits[2:0]  State.  Valid values:
			0		Idle.   There is no command in progress
			1 		Active. A command is in progress
			2		Error.  The command has failed.  See error code for details

	+ IMAGE_UPLOAD_STATUS_PARAMS_ERROR, Image upload error code, ro, 0
	Bits[31:8] reserved
	Bits[7:0]  Error code.  Valid values:
			0		None.  No error
			1 		Timeout.   	  Command timed out
			2 		CRC Failure.  Verify/program command failed on CRC check
			3		Incompatible. Image upload is incompatible with this device.
			4       Disabled. Image upload is disabled in this device.

*/

typedef enum
{
	IMAGE_UPLOAD_STATUS_PARAMS_STATE   = 0,
	IMAGE_UPLOAD_STATUS_PARAMS_ERROR   = 1,

	IMAGE_UPLOAD_STATUS_PARAMS_SUBBLOCK_END
}mmApiImageUploadSubBlockImageUploadStatusParams;

//PARAMETERSDEF:IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_CONFIG
/*
	+ IMAGE_UPLOAD_CONFIG_PARAMS_SIZE, Size of image upload, rw, 0
	Bits[31:0] Image size in bytes

	+ IMAGE_UPLOAD_CONFIG_PARAMS_CRC, Image upload CRC, rw, 0
	Bits[31:0] CRC value

	+ IMAGE_UPLOAD_CONFIG_PARAMS_PROTOCOL, Protocol used for upload, rw, 0
	Bits[31:8] reserved
	Bits[7:0]  Protocol
		0	MMAPI: Image is loaded via MMAPI registers over SPI or network
		1	TFTP over IPv4 via network interface

    + IMAGE_UPLOAD_CONFIG_PARAMS_SECURITY_KEY1, Security key for upload first word, rw, 0
	Bits[31:0] Key bits 63:32

	+ IMAGE_UPLOAD_CONFIG_PARAMS_SECURITY_KEY2, Security key for upload second word, rw, 0
	Bits[31:0] Key bits 31:0

	+ IMAGE_UPLOAD_CONFIG_PARAMS_TPA1, Transmission protocol address bytes 0..3, rw, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_TPA2, Transmission protocol address bytes 4..7, rw, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_TPA3, Transmission protocol address bytes 8..11, rw, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:ff:fe:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_TPA4, Transmission protocol address bytes 12..15, rw, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:ff:fe:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_PORT, Transmission protocol port number, rw, 0
	Bits[31:16] = reserved
	Bits[15:0]  = Port number
				Notes: The port number can have different meaning for different upload protocols
				e.g. upd port number or ethertype

	+ IMAGE_UPLOAD_CONFIG_PARAMS_BLOCK_SIZE, Data upload block size, rw, 39
	Bits[31:0] Block size in 32bit words.  Range 1-1024
	Notes: This register only applies to image upload via MMAPI. Other protocols define their own block size.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_ENABLE, Enable image upload operation, rw, 0
	Bits[31:1] = reserved
	Bit[0]     = enable
	The image upload operation can only be enabled/disabled in Initialising System State.  See register %SYSTEM_MGMT_PARAMS_SUBBLOCK_SYSTEMSTATE%

	+ IMAGE_UPLOAD_CONFIG_PARAMS_ACTION, Image upload action, rw, 0
	Bits[31:8] reserved
	Bits[7:0] Initiates an action of the upload process:
		0 - Start. For network protocols this will start the image upload
		           For MMAPI protocol the bytes will be transferred via API
		1 - Verify image using supplied CRC value
		2 - Decrypt image data using specified security protocol
		3 - Program image to flash
	The state register should be checked to see if the action has completed.

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME0, Image upload filename, rw, 0
	  Bits[31:0] = First 4 characters (e.g. 'uplo' if Software Version = 'upload_data.bin')
	  Note: Characters are taken from word in Network byte order
	        Filename must include null termination character

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME1, Image upload filename, rw, 0
	  Bits[31:0] = Characters 5 to 8 (e.g. 'ad_d' if Software Version = 'upload_data.bin')

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME2, Image upload filename, rw, 0
	  Bits[31:0] = Characters 9 to 12

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME3, Image upload filename, rw, 0
	  Bits[31:0] = Characters 13 to 16

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME4, Image upload filename, rw, 0
	  Bits[31:0] = Characters 17 to 20

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME5, Image upload filename, rw, 0
	  Bits[31:0] = Characters 21 to 24

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME6, Image upload filename, rw, 0
	  Bits[31:0] = Characters 25 to 28

	+ IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME7, Image upload filename, rw, 0
	  Bits[31:0] = Characters 29 to 32

*/

typedef enum
{
	IMAGE_UPLOAD_CONFIG_PARAMS_SIZE   		 = 0,
	IMAGE_UPLOAD_CONFIG_PARAMS_CRC    		 = 1,
	IMAGE_UPLOAD_CONFIG_PARAMS_PROTOCOL    	 = 2,
	IMAGE_UPLOAD_CONFIG_PARAMS_SECURITY_KEY1 = 3,
	IMAGE_UPLOAD_CONFIG_PARAMS_SECURITY_KEY2 = 4,
	IMAGE_UPLOAD_CONFIG_PARAMS_TPA1			 = 5,
	IMAGE_UPLOAD_CONFIG_PARAMS_TPA2			 = 6,
	IMAGE_UPLOAD_CONFIG_PARAMS_TPA3			 = 7,
	IMAGE_UPLOAD_CONFIG_PARAMS_TPA4			 = 8,
	IMAGE_UPLOAD_CONFIG_PARAMS_PORT			 = 9,
	IMAGE_UPLOAD_CONFIG_PARAMS_BLOCK_SIZE	 = 10,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILL_CHAR	 = 11,

	IMAGE_UPLOAD_CONFIG_PARAMS_ENABLE		 = 16,

	IMAGE_UPLOAD_CONFIG_PARAMS_ACTION		 = 32,

	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME0	 = 64,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME1	 = 65,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME2	 = 66,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME3	 = 67,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME4	 = 68,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME5	 = 69,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME6	 = 70,
	IMAGE_UPLOAD_CONFIG_PARAMS_FILENAME7	 = 71,

	IMAGE_UPLOAD_CONFIG_PARAMS_SUBBLOCK_END
}mmApiImageUploadSubBlockImageUploadConfigParams;

//PARAMETERSDEF:IMAGE_UPLOAD_PARAMS_SUBBLOCK_IMAGE_UPLOAD_DATA
/*
	+ IMAGE_UPLOAD_DATA_PARAMS_BLOCK_NUMBER, Data upload block number, rw, 0
	Bits[31:0] Block number (index starts at zero)
	Notes: The block number must be set before any data registers are written
		   Writes to this register will have no effect unless image upload state is Active
		   and the upload protocol is MMAPI

	+ IMAGE_UPLOAD_DATA_PARAMS_FIRST_DATA_WORD, Data upload first data word, rw, -
	Bits[31:0] Data word
	Notes: The consecutive registers following this one contain the rest of the data block
		   Writes to this register will have no effect unless image upload state is Active
		   and the upload protocol is MMAPI.  Not the words from the image must be in
		   Network Byte order (Big Endian)
*/

typedef enum
{
	IMAGE_UPLOAD_DATA_PARAMS_BLOCK_NUMBER 		= 0,
	IMAGE_UPLOAD_DATA_PARAMS_FIRST_DATA_WORD 	= 1,

	IMAGE_UPLOAD_DATA_PARAMS_SUBBLOCK_END
}mmApiImageUploadSubBlockImageUploadData;

#ifdef __cplusplus
}
#endif

#endif

