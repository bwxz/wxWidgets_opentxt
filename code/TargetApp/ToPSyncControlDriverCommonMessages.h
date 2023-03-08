/*
Copyright ?2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: ToPSyncControlDriverCommonMessages.h $
Version     $Revision: 10 $
Date        $Date: 2/03/09 14:57 $
*/

/**
  * \file ToPSyncControlDriverCommonMessages.h
  *	Declarations for messages which are common to both the boot and ToPSync main application.
  */
#ifndef TOPSYNC_CONTROL_DRIVER_COMMON_MESSAGES_H
#define TOPSYNC_CONTROL_DRIVER_COMMON_MESSAGES_H

#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \def TOPSYNC_CONTROL_MESSAGE_SET_ID
 *	Following message set Ids are reserved:
 *	- 0x01 - 1588 PTP messages,
 *	- 0x02 - 1588 short messages,
 *	- 0xF0 - Semtech proprietary management messages
 *  - 0xE0 - Semtech proprietary mode 2 and mode 3 specific messages
 *  - 0xB0 - Semtech Proprietary memory mapped parameter messages
 */
#define TOPSYNC_CONTROL_MESSAGE_SET_ID						    0xF1
#define TOPSYNC_DELAY_REPLACEMENT_MESSAGE_SET_ID	            0xE0
#define TOPSYNC_MMAPI_MESSAGE_SET_ID							0xB0

#define TOPSYNC_CONTROL_MESSAGE_TYPE_NONE						0xFFFF


/* Message Lengths */
/** \defgroup TSControlMsgs ToPSync Control Message Lengths
 *  Macros defining the lengths of the ToPSync control messages
 */
/**\{ */
#define TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH				    15
#define SET_TOPSYNC_SYSTEM_STATE_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 2)
#define SET_TOPSYNC_SYSTEM_STATE_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 2)
#define GET_TOPSYNC_SYSTEM_STATE_MESSAGE_LENGTH					TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_TOPSYNC_SYSTEM_STATE_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 2)
#define GET_ETHERNET_MAC_ADDRESS_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 1)
#define GET_ETHERNET_MAC_ADDRESS_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 7)

#define GET_HARDWARE_VERSION_MESSAGE_LENGTH						TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_HARDWARE_VERSION_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + HARDWARE_VERSION_LENGTH)
#define GET_SOFTWARE_VERSION_MESSAGE_LENGTH						TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_SOFTWARE_VERSION_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + (SOFTWARE_VERSION_LENGTH+1))
#define GET_TOPSYNC_PART_NUMBER_MESSAGE_LENGTH					TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_TOPSYNC_PART_NUMBER_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 2)
#define UPGRADE_FIRMWARE_MESSAGE_LENGTH                         (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 16)
#define UPGRADE_FIRMWARE_RESP_MESSAGE_LENGTH                    TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH

#define UPGRADE_FIRMWARE_USING_FIFO_MESSAGE_LENGTH              (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 12)
#define UPGRADE_FIRMWARE_USING_FIFO_RESP_MESSAGE_LENGTH         TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define UPGRADE_FIRMWARE_USING_FIFO_VERIFY_MESSAGE_LENGTH       TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH

#define FIRMWARE_BURST_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 132)
#define FIRMWARE_BURST_RESP_MESSAGE_LENGTH						TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define FIRMWARE_CRC_MESSAGE_LENGTH								(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 4)
#define FIRMWARE_CRC_RESP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 4)
#define GET_SETS_SOFTWARE_VERSION_MESSAGE_LENGTH				TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_SETS_SOFTWARE_VERSION_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + (SOFTWARE_VERSION_LENGTH+1))
#define GET_APP_SOFTWARE_VERSION_MESSAGE_LENGTH					TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_APP_SOFTWARE_VERSION_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + (SOFTWARE_VERSION_LENGTH+1))
#define GET_SETS_HARDWARE_VERSION_MESSAGE_LENGTH				TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_SETS_HARDWARE_VERSION_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + HARDWARE_VERSION_LENGTH)

#define UPLOAD_FIRMWARE_APP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 24)
#define UPLOAD_FIRMWARE_APP_RESP_MESSAGE_LENGTH					TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define UPLOAD_FIRMWARE_BOOT_MESSAGE_LENGTH						UPLOAD_FIRMWARE_APP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_BOOT_RESP_MESSAGE_LENGTH				UPLOAD_FIRMWARE_APP_RESP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_APP_BURST_MESSAGE_LENGTH				FIRMWARE_BURST_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_APP_BURST_RESP_MESSAGE_LENGTH			FIRMWARE_BURST_RESP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_BOOT_BURST_MESSAGE_LENGTH				FIRMWARE_BURST_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_BOOT_BURST_RESP_MESSAGE_LENGTH			FIRMWARE_BURST_RESP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_APP_CRC_MESSAGE_LENGTH					FIRMWARE_CRC_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_APP_CRC_RESP_MESSAGE_LENGTH				FIRMWARE_CRC_RESP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_BOOT_CRC_MESSAGE_LENGTH					FIRMWARE_CRC_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_BOOT_CRC_RESP_MESSAGE_LENGTH			FIRMWARE_CRC_RESP_MESSAGE_LENGTH
#define UPLOAD_FIRMWARE_APP_USING_FIFO_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define UPLOAD_FIRMWARE_APP_USING_FIFO_RESP_MESSAGE_LENGTH		(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define UPLOAD_FIRMWARE_BOOT_USING_FIFO_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define UPLOAD_FIRMWARE_BOOT_USING_FIFO_RESP_MESSAGE_LENGTH		(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define SET_STARTUP_MODE_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define SET_STARTUP_MODE_RESP_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define GET_STARTUP_MODE_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)
#define GET_STARTUP_MODE_RESP_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 8)

//todo: check lengths
#define SET_IP_STARTUP_CONFIG_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 27)
#define SET_IP_STARTUP_CONFIG_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 27)
#define GET_IP_STARTUP_CONFIG_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 1)
#define GET_IP_STARTUP_CONFIG_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 27)

#define SET_SGMII_MODE_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)
#define SET_SGMII_MODE_RESP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)
#define GET_SGMII_MODE_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 1)
#define GET_SGMII_MODE_RESP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)

#define SET_PHYSICAL_PORT_ACTIVE_CONFIG_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)
#define SET_PHYSICAL_PORT_ACTIVE_CONFIG_RESP_MESSAGE_LENGTH		(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)
#define GET_PHYSICAL_PORT_ACTIVE_CONFIG_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 1)
#define GET_PHYSICAL_PORT_ACTIVE_CONFIG_RESP_MESSAGE_LENGTH		(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 5)

#define SET_DEBUG_PRINT_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 4)
#define SET_DEBUG_PRINT_RESP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 4)
#define GET_DEBUG_PRINT_MESSAGE_LENGTH							(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH)
#define GET_DEBUG_PRINT_RESP_MESSAGE_LENGTH						(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 4)
#define GET_FIELD_BOOT_VERSION_MESSAGE_LENGTH					TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH
#define GET_FIELD_BOOT_VERSION_RESP_MESSAGE_LENGTH				(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + (SOFTWARE_VERSION_LENGTH+1))


/*
 * Introduced for TS2 boot set/get mac address api to avoid confusion & conflicts with existing boot
 * get api and appication set api
 */
#define SET_ETHERNET_MAC_ADDRESS_MESSAGE_LENGTH					(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 7)
#define SET_ETHERNET_MAC_ADDRESS_RESP_MESSAGE_LENGTH			(TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 7)
/**\} */


typedef uint16 ToPSyncMsgSequenceNumber;
typedef uint16 ToPSyncMsgSet;
typedef uint8 ToPSyncMsgLength;  /* maximum size of a ToPSync message is 200 bytes */
typedef uint8 ToPSyncResultType;
typedef uint16 ToPSyncMsgType;

/* ToPSync Message Header */
typedef struct
{
	ToPSyncMsgSet messageSetId;
	ToPSyncMsgLength messageLength;
	ToPSyncMsgType messageType;
	ToPSyncMsgSequenceNumber sequenceNumber;
	ToPSyncMsgSequenceNumber originatingSequenceNumber;
	Bool endOfMessage;		     /* indicates whether the message is the last one. */
	ToPSyncConfigResult result;  /* only used in responses. */
	uint32 securityKey;
} ToPSyncMsgHeader;


/*******************************
 * Generic External Interfaces Get message.
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
} GenericExternalInterfacesGetMsg;


/******************************* 
 * Ethernet MAC Address message.
 *******************************/
typedef GenericExternalInterfacesGetMsg GetEthernetMacAddressMsg;
typedef struct 
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
	EthernetAddress macAddress;
} GetEthernetMacAddressResponseMsg;


/******************************* 
 * Hardware Version message
 *******************************/
typedef ToPSyncMsgHeader GetHardwareVersionMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 hardwareVersion;
}GetHardwareVersionResponseMsg;

/******************************* 
 * SETS Hardware Version message
 *******************************/
typedef ToPSyncMsgHeader GetSetsHardwareVersionMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 hardwareVersion;
}GetSetsHardwareVersionResponseMsg;

/******************************* 
 * Software Version message.
 *******************************/
typedef ToPSyncMsgHeader GetSoftwareVersionMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	char softwareVersion[SOFTWARE_VERSION_LENGTH+1];
}GetSoftwareVersionResponseMsg;

typedef GetSoftwareVersionMsg GetFieldBootVersionMsg;
typedef GetSoftwareVersionResponseMsg GetFieldBootVersionResponseMsg;

/******************************* 
 * Sets Software Version message.
 *******************************/
typedef ToPSyncMsgHeader GetSetsSoftwareVersionMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	char softwareVersion[SOFTWARE_VERSION_LENGTH+1];
}GetSetsSoftwareVersionResponseMsg;


/******************************* 
 * App Software Version message.
 *******************************/
typedef ToPSyncMsgHeader GetAppSoftwareVersionMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	char softwareVersion[SOFTWARE_VERSION_LENGTH+1];
}GetAppSoftwareVersionResponseMsg;


/*******************************
 * TopSync Part Number message
 *******************************/
typedef ToPSyncMsgHeader GetToPSyncPartNumberMsg;
typedef struct
{
	ToPSyncMsgHeader header;
	ToPSyncPartNumber partNumber;
} GetToPSyncPartNumberResponseMsg;


/*******************************
 * ToPSync System State message.
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	ToPSyncSystemState newSystemState;
} ToPSyncSystemStateMsg;

typedef ToPSyncSystemStateMsg SetToPSyncSystemStateMsg;
typedef ToPSyncSystemStateMsg SetToPSyncSystemStateResponseMsg;
typedef ToPSyncMsgHeader	  GetToPSyncSystemStateMsg;
typedef ToPSyncSystemStateMsg GetToPSyncSystemStateResponseMsg;


/*******************************
 * Upgrade Firmware message
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 encryptionKey[FIRMWARE_ENCRYPTION_KEY_NUMBER_OF_WORDS];
} UpgradeFirmwareMsg;
typedef ToPSyncMsgHeader UpgradeFirmwareResponseMsg;


/**************************************
 * Upgrade Firmware Using FIFO message
 *************************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 length;
	uint32 firmwareCrc;
} UpgradeFirmwareUsingFifoMsg;
typedef ToPSyncMsgHeader UpgradeFirmwareUsingFifoVerificationMsg;
typedef ToPSyncMsgHeader UpgradeFirmwareUsingFifoResponseMsg;

/*******************************
 * Firmware Burst message
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint16 burstNumber;
	uint16 burstSize;
	uint8 burstData[FIRMWARE_BURST_DATA_LENGTH];
} FirmwareBurstMsg;
typedef ToPSyncMsgHeader FirmwareBurstResponseMsg;


/*******************************
 * Firmware CRC message
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 crc;
} FirmwareCrcMsg;
typedef FirmwareCrcMsg FirmwareCrcResponseMsg;




/*******************************
 * Upload Firmware App/Boot message
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 location;
	uint32 length;
	uint32 encryptionKey[FIRMWARE_ENCRYPTION_KEY_NUMBER_OF_WORDS];
} UploadFirmwareAppMsg;
typedef UploadFirmwareAppMsg UploadFirmwareAppResponseMsg;

/*boot*/
typedef UploadFirmwareAppMsg UploadFirmwareBootMsg;
typedef UploadFirmwareAppMsg UploadFirmwareBootResponseMsg;






/*******************************
 * Upload Firmware App/Boot Burst message
 *******************************/
typedef FirmwareBurstMsg UploadFirmwareAppBurstMsg;
typedef FirmwareBurstMsg UploadFirmwareAppBurstResponseMsg;
typedef FirmwareBurstMsg UploadFirmwareBootBurstMsg;
typedef FirmwareBurstMsg UploadFirmwareBootBurstResponseMsg;



/*******************************
 * Upload Firmware App/BootCRC message
 *******************************/
typedef FirmwareCrcMsg UploadFirmwareAppCrcMsg;
typedef FirmwareCrcMsg UploadFirmwareAppCrcResponseMsg;
typedef FirmwareCrcMsg UploadFirmwareBootCrcMsg;
typedef FirmwareCrcMsg UploadFirmwareBootCrcResponseMsg;



/**************************************
 * Uload Firmware App/Boot Using FIFO message
 *************************************/
typedef UpgradeFirmwareUsingFifoMsg UploadFirmwareAppUsingFifoMsg;
typedef UpgradeFirmwareUsingFifoMsg UploadFirmwareAppUsingFifoResponseMsg;
typedef UpgradeFirmwareUsingFifoMsg UploadFirmwareBootUsingFifoMsg;
typedef UpgradeFirmwareUsingFifoMsg UploadFirmwareBootUsingFifoResponseMsg;




/*******************************
 * Set/Get Startup mode
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 bootSelect;
	uint8 mode;
} SetStartupModeMsg;
typedef SetStartupModeMsg SetStartupModeResponseMsg;


typedef struct
{
	ToPSyncMsgHeader header;
	uint8 bootSelect;
	uint8 mode;
}GetStartupModeMsg;
typedef SetStartupModeMsg GetStartupModeResponseMsg;




/*******************************
 * Set/Get IP Config Startup Config
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 port;
	IpBootConfiguration ipConfig;
} SetIpStartupConfigMsg;
typedef SetIpStartupConfigMsg SetIpStartupConfigResponseMsg;

typedef struct
{
	ToPSyncMsgHeader header;
	uint8 port;
} GetIpStartupConfigMsg;
typedef SetIpStartupConfigMsg GetIpStartupConfigResponseMsg;


/*******************************
 * Set/Get SGMII MAC PHY port mode
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
	uint32 sgmiiMode;
} SetSgmiiModeMsg;
typedef SetSgmiiModeMsg SetSgmiiModeResponseMsg;

typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
} GetSgmiiModeMsg;
typedef SetSgmiiModeMsg GetSgmiiModeResponseMsg;

/*******************************
 * Set/Get active physical port Config
 *******************************/
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
	PhysicalPortActiveConfig physicalPortActiveConfig;
} SetPhysicalPortActiveConfigMsg;
typedef SetPhysicalPortActiveConfigMsg SetPhysicalPortActiveConfigResponseMsg;

typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
} GetPhysicalPortActiveConfigMsg;
typedef SetPhysicalPortActiveConfigMsg GetPhysicalPortActiveConfigResponseMsg;


typedef struct
{
	ToPSyncMsgHeader header;
	uint8 portNumber;
	EthernetAddress macAddress;
} SetEthernetMacAddressMsg;
typedef SetEthernetMacAddressMsg SetEthernetMacAddressResponseMsg;

#if(0)
typedef struct
{
	ToPSyncMsgHeader header;
	uint8 port;
	EthernetAddress macAddress;
} GetMacAddressMsg;
typedef GetMacAddressMsg GetMacAddressResponseMsg;
#endif


/* Set / Get debug print message
*/
typedef struct
{
	ToPSyncMsgHeader header;
	uint32 data;
} SetDebugPrintMsg;

typedef struct
{
	ToPSyncMsgHeader header;
} GetDebugPrintMsg;

typedef SetDebugPrintMsg SetDebugPrintResponseMsg;
typedef SetDebugPrintMsg GetDebugPrintResponseMsg;






/*******************************
 * Header Access functions.
 *******************************/
void InitialiseTopSyncMessageHeader(ToPSyncMsgHeader* header,
                                    ToPSyncMsgSet messageSetId,
	                                ToPSyncMsgLength messageLength,
						            ToPSyncMsgType messageType,
			 			            ToPSyncMsgSequenceNumber sequenceNumber,
                                    ToPSyncMsgSequenceNumber originatingSequenceNumber,
                                    Bool endOfMessage,
                                    ToPSyncConfigResult result,
									uint32 securityKey);

void ReadToPSyncMessageHeader(uint8 const ** data, ToPSyncMsgHeader* header);

void WriteToPSyncMessageHeader(uint8** data, const ToPSyncMsgHeader* header);

uint16 GetToPSyncMessageSet(const uint8 data[]);

uint16 GetToPSyncMessageType(const uint8 data[]);

void SetToPSyncMessageSeqNo(const uint8 data[], ToPSyncMsgType messageOriginatingNumber);

uint16 GetToPSyncMessageSeqNo(const uint8 data[]);

void SetToPSyncMessageOriginatingSeqNo(const uint8 data[], ToPSyncMsgType messageOriginatingSequenceNumber);

#ifndef _ARC
uint16 GetToPSyncMessageOriginatingSeqNo(const uint8 data[]);
#endif

#ifndef SEMTECH_TARGET
ToPSyncConfigResult GetToPSyncMessageResult(const uint8 data[]);
void SetToPSyncMessageLength(const uint8 data[], ToPSyncMsgLength length);
#endif

ToPSyncMsgLength GetToPSyncMessageLength(const uint8 data[]);

void SetToPSyncMessageType(const uint8 data[], ToPSyncMsgType messageType);

void SetToPSyncMessageResult(const uint8 data[], ToPSyncConfigResult result);

void SetToPSyncMessageSecurityKey(const uint8 data[], uint32 securityKey);

uint32 GetToPSyncMessageSecurityKey(const uint8 data[]);

uint32 PeekInteger(const uint8 data[], uint8 start, uint8 bytes);


/*******************************
 * Generic Ethernet Get message.
 *******************************/
void ReadGenericExternalInterfacesGetMsg(uint8 const **data, GenericExternalInterfacesGetMsg *msg);
void WriteGenericExternalInterfacesGetMsg(uint8 **data, const GenericExternalInterfacesGetMsg *msg);


/******************************* 
 * Ethernet MAC Address message.
 *******************************/
void ReadGetEthernetMacAddressMsg(uint8 const **data, GetEthernetMacAddressMsg *msg);
void WriteGetEthernetMacAddressMsg(uint8 **data, const GetEthernetMacAddressMsg *msg);

void ReadGetEthernetMacAddressResponseMsg(uint8 const **data, GetEthernetMacAddressResponseMsg *msg);
void WriteGetEthernetMacAddressResponseMsg(uint8 **data, const GetEthernetMacAddressResponseMsg *msg);


/******************************* 
 * Hardware Version message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetHardwareVersionMsg(uint8 const **data, GetHardwareVersionMsg *msg);
void WriteGetHardwareVersionMsg(uint8 **data, const GetHardwareVersionMsg *msg);

void ReadGetHardwareVersionResponseMsg(uint8 const **data, GetHardwareVersionResponseMsg *msg);
#endif
void WriteGetHardwareVersionResponseMsg(uint8 **data, const GetHardwareVersionResponseMsg *msg);

/******************************* 
 * SETS Hardware Version message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetSetsHardwareVersionMsg(uint8 const **data, GetSetsHardwareVersionMsg *msg);
void WriteGetSetsHardwareVersionMsg(uint8 **data, const GetSetsHardwareVersionMsg *msg);

void ReadGetSetsHardwareVersionResponseMsg(uint8 const **data, GetSetsHardwareVersionResponseMsg *msg);
void WriteGetSetsHardwareVersionResponseMsg(uint8 **data, const GetSetsHardwareVersionResponseMsg *msg);
#endif

/******************************* 
 * Software Version message.
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetSoftwareVersionMsg(uint8 const **data, GetSoftwareVersionMsg *msg);
void WriteGetSoftwareVersionMsg(uint8 **data, const GetSoftwareVersionMsg *msg);

void ReadGetSoftwareVersionResponseMsg(uint8 const **data, GetSoftwareVersionResponseMsg *msg);
#endif
void WriteGetSoftwareVersionResponseMsg(uint8 **data, const GetSoftwareVersionResponseMsg *msg);


#ifndef SEMTECH_TARGET
#define ReadGetFieldBootVersionMsg ReadGetSoftwareVersionMsg
#define WriteGetFieldBootVersionMsg WriteGetSoftwareVersionMsg
#define ReadGetFieldBootVersionResponseMsg ReadGetSoftwareVersionResponseMsg
#define WriteGetFieldBootVersionResponseMsg WriteGetSoftwareVersionResponseMsg
#endif

/******************************* 
 * Sets Software Version message.
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetSetsSoftwareVersionMsg(uint8 const **data, GetSetsSoftwareVersionMsg *msg);
void WriteGetSetsSoftwareVersionMsg(uint8 **data, const GetSetsSoftwareVersionMsg *msg);

void ReadGetSetsSoftwareVersionResponseMsg(uint8 const **data, GetSetsSoftwareVersionResponseMsg *msg);
void WriteGetSetsSoftwareVersionResponseMsg(uint8 **data, const GetSetsSoftwareVersionResponseMsg *msg);
#endif

/******************************* 
 * App Software Version message.
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetAppSoftwareVersionMsg(uint8 const **data, GetAppSoftwareVersionMsg *msg);
void WriteGetAppSoftwareVersionMsg(uint8 **data, const GetAppSoftwareVersionMsg *msg);

void ReadGetAppSoftwareVersionResponseMsg(uint8 const **data, GetAppSoftwareVersionResponseMsg *msg);
void WriteGetAppSoftwareVersionResponseMsg(uint8 **data, const GetAppSoftwareVersionResponseMsg *msg);
#endif

/*******************************
 * TopSync Part Number message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadGetToPSyncPartNumberMsg(uint8 const **data, GetToPSyncPartNumberMsg *msg);
void WriteGetToPSyncPartNumberMsg(uint8 **data, const GetToPSyncPartNumberMsg *msg);

void ReadGetToPSyncPartNumberResponseMsg(uint8 const **data, GetToPSyncPartNumberResponseMsg *msg);
#endif
void WriteGetToPSyncPartNumberResponseMsg(uint8 **data, const GetToPSyncPartNumberResponseMsg *msg);

/*******************************
 * ToPSync System State message.
 *******************************/
void ReadToPSyncSystemStateMsg(uint8 const **data, ToPSyncSystemStateMsg *msg);
void WriteToPSyncSystemStateMsg(uint8 **data, const ToPSyncSystemStateMsg *msg);

void ReadSetToPSyncSystemStateMsg(uint8 const **data, SetToPSyncSystemStateMsg *msg);
void WriteSetToPSyncSystemStateMsg(uint8 **data, const SetToPSyncSystemStateMsg *msg);


void ReadSetToPSyncSystemStateResponseMsg(uint8 const **data, SetToPSyncSystemStateResponseMsg *msg);
void WriteSetToPSyncSystemStateResponseMsg(uint8 **data, const SetToPSyncSystemStateResponseMsg *msg);

void ReadGetToPSyncSystemStateMsg(uint8 const **data, GetToPSyncSystemStateMsg *msg);
void WriteGetToPSyncSystemStateMsg(uint8 **data, const GetToPSyncSystemStateMsg *msg);

#ifndef SEMTECH_TARGET
void ReadGetToPSyncSystemStateResponseMsg(uint8 const **data, GetToPSyncSystemStateResponseMsg *msg);
#endif
void WriteGetToPSyncSystemStateResponseMsg(uint8 **data, const GetToPSyncSystemStateResponseMsg *msg);


/**************************************
 * Upgrade Firmware Using FIFO message
 **************************************/
#ifndef SEMTECH_TARGET
void ReadUpgradeFirmwareUsingFifoMsg(uint8 const **data, UpgradeFirmwareUsingFifoMsg *msg);


#ifndef _ARC
void WriteUpgradeFirmwareUsingFifoMsg(uint8 **data, const UpgradeFirmwareUsingFifoMsg *msg);
#endif

void ReadUpgradeFirmwareUsingFifoVerificationMsg(uint8 const **data, UpgradeFirmwareUsingFifoVerificationMsg *msg);

#ifndef _ARC
void WriteUpgradeFirmwareUsingFifoVerificationMsg(uint8 **data, const UpgradeFirmwareUsingFifoVerificationMsg *msg);
#endif

void ReadUpgradeFirmwareUsingFifoResponseMsg(uint8 const **data, UpgradeFirmwareUsingFifoResponseMsg *msg);

#ifndef _ARC
void WriteUpgradeFirmwareUsingFifoResponseMsg(uint8 **data, const UpgradeFirmwareUsingFifoResponseMsg *msg);
#endif
#endif

/*******************************
 * Upgrade Firmware message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadUpgradeFirmwareMsg(uint8 const **data, UpgradeFirmwareMsg *msg);
void WriteUpgradeFirmwareMsg(uint8 **data, const UpgradeFirmwareMsg *msg);

void ReadUpgradeFirmwareResponseMsg(uint8 const **data, UpgradeFirmwareResponseMsg *msg);
void WriteUpgradeFirmwareResponseMsg(uint8 **data, const UpgradeFirmwareResponseMsg *msg);
#endif

/*******************************
 * Firmware Burst message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadFirmwareBurstMsg(uint8 const **data, FirmwareBurstMsg *msg);
void WriteFirmwareBurstMsg(uint8 **data, const FirmwareBurstMsg *msg);

void ReadFirmwareBurstResponseMsg(uint8 const **data, FirmwareBurstResponseMsg *msg);
void WriteFirmwareBurstResponseMsg(uint8 **data, const FirmwareBurstResponseMsg *msg);
#endif

/*******************************
 * Firmware CRC message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadFirmwareCrcMsg(uint8 const **data, FirmwareCrcMsg *msg);
void WriteFirmwareCrcMsg(uint8 **data, const FirmwareCrcMsg *msg);

void ReadFirmwareCrcResponseMsg(uint8 const **data, FirmwareCrcResponseMsg *msg);
void WriteFirmwareCrcResponseMsg(uint8 **data, const FirmwareCrcResponseMsg *msg);
#endif


/*******************************
 * Upload Firmware App/Boot message
 *******************************/
#ifndef SEMTECH_TARGET
void ReadUploadFirmwareAppMsg(uint8 const **data, UploadFirmwareAppMsg *msg);
void WriteUploadFirmwareAppMsg(uint8 **data, const UploadFirmwareAppMsg *msg);

#define ReadUploadFirmwareAppResponseMsg ReadUploadFirmwareAppMsg
#define WriteUploadFirmwareAppResponseMsg WriteUploadFirmwareAppMsg

/*boot*/
#define ReadUploadFirmwareBootMsg ReadUploadFirmwareAppMsg
#define WriteUploadFirmwareBootMsg WriteUploadFirmwareAppMsg
#define ReadUploadFirmwareBootResponseMsg ReadUploadFirmwareAppResponseMsg
#define WriteUploadFirmwareBootResponseMsg WriteUploadFirmwareAppResponseMsg
#endif

/*******************************
 * Upload Firmware App/Boot Burst message
 *******************************/
#ifndef SEMTECH_TARGET
#define ReadUploadFirmwareAppBurstMsg ReadFirmwareBurstMsg
#define WriteUploadFirmwareAppBurstMsg WriteFirmwareBurstMsg
#define ReadUploadFirmwareAppBurstResponseMsg ReadFirmwareBurstMsg
#define WriteUploadFirmwareAppBurstResponseMsg WriteFirmwareBurstMsg

#define ReadUploadFirmwareBootBurstMsg ReadFirmwareBurstMsg
#define WriteUploadFirmwareBootBurstMsg WriteFirmwareBurstMsg
#define ReadUploadFirmwareBootBurstResponseMsg ReadFirmwareBurstMsg
#define WriteUploadFirmwareBootBurstResponseMsg WriteFirmwareBurstMsg
#endif

/*******************************
 * Upload Firmware App/Boot CRC message
 *******************************/
#ifndef SEMTECH_TARGET
#define ReadUploadFirmwareAppCrcMsg ReadFirmwareCrcMsg
#define WriteUploadFirmwareAppCrcMsg WriteFirmwareCrcMsg
#define ReadUploadFirmwareAppCrcResponseMsg ReadFirmwareCrcResponseMsg
#define WriteUploadFirmwareAppCrcResponseMsg WriteFirmwareCrcResponseMsg

#define ReadUploadFirmwareBootCrcMsg ReadFirmwareCrcMsg
#define WriteUploadFirmwareBootCrcMsg WriteFirmwareCrcMsg
#define ReadUploadFirmwareBootCrcResponseMsg ReadFirmwareCrcResponseMsg
#define WriteUploadFirmwareBootCrcResponseMsg WriteFirmwareCrcResponseMsg
#endif

/**************************************
 * Upload Firmware App/Boot Using FIFO message
 **************************************/
#ifndef SEMTECH_TARGET
#define ReadUploadFirmwareAppUsingFifoMsg ReadUpgradeFirmwareUsingFifoMsg
#define WriteUploadFirmwareAppUsingFifoResponseMsg WriteUpgradeFirmwareUsingFifoMsg

#ifndef _ARC
#define WriteUploadFirmwareAppUsingFifoMsg WriteUpgradeFirmwareUsingFifoMsg
#define ReadUploadFirmwareAppUsingFifoResponseMsg ReadUpgradeFirmwareUsingFifoMsg
#endif


#define ReadUploadFirmwareBootUsingFifoMsg ReadUpgradeFirmwareUsingFifoMsg
#define WriteUploadFirmwareBootUsingFifoResponseMsg WriteUpgradeFirmwareUsingFifoMsg

#ifndef _ARC
#define WriteUploadFirmwareBootUsingFifoMsg WriteUpgradeFirmwareUsingFifoMsg
#define ReadUploadFirmwareBootUsingFifoResponseMsg ReadUpgradeFirmwareUsingFifoMsg
#endif
#endif


/**************************************
 * Set/Get Startup Mode Message
 **************************************/

/*Set message*/
#ifndef SEMTECH_TARGET
void ReadSetStartupModeMsg(uint8 const **data, SetStartupModeMsg *msg);
void WriteSetStartupModeMsg(uint8 **data, const SetStartupModeMsg *msg);
#define ReadSetStartupModeResponseMsg ReadSetStartupModeMsg
#define WriteSetStartupModeResponseMsg WriteSetStartupModeMsg


/*Get message*/
void ReadGetStartupModeMsg(uint8 const **data, GetStartupModeMsg *msg);
void WriteGetStartupModeMsg(uint8 **data, const GetStartupModeMsg *msg);
#define ReadGetStartupModeResponseMsg ReadSetStartupModeMsg
#define WriteGetStartupModeResponseMsg WriteSetStartupModeMsg
#endif


/*******************************
 * Set/Get IP Config Startup Config
 *******************************/

/*Set message*/
#ifndef SEMTECH_TARGET
void ReadSetIpStartupConfigMsg(uint8 const **data, SetIpStartupConfigMsg *msg);
void WriteSetIpStartupConfigMsg(uint8 **data, const SetIpStartupConfigMsg *msg);
#define ReadSetIpStartupConfigResponseMsg ReadSetIpStartupConfigMsg
#define WriteSetIpStartupConfigResponseMsg WriteSetIpStartupConfigMsg

/*get*/
void ReadGetIpStartupConfigMsg(uint8 const **data, GetIpStartupConfigMsg *msg);
void WriteGetIpStartupConfigMsg(uint8 **data, const GetIpStartupConfigMsg *msg);
#define ReadGetIpStartupConfigResponseMsg ReadSetIpStartupConfigMsg
#define WriteGetIpStartupConfigResponseMsg WriteSetIpStartupConfigMsg
#endif

/*******************************
 * Set/Get SGMII MAC/PHY port mode
 *******************************/

/*Set message*/
#ifndef SEMTECH_TARGET
void ReadSetSgmiiModeMsg(uint8 const **data, SetSgmiiModeMsg *msg);
void WriteSetSgmiiModeMsg(uint8 **data, const SetSgmiiModeMsg *msg);
#define ReadSetSgmiiModeResponseMsg ReadSetSgmiiModeMsg
#define WriteSetSgmiiModeResponseMsg WriteSetSgmiiModeMsg

/*get*/
void ReadGetSgmiiModeMsg(uint8 const **data, GetSgmiiModeMsg *msg);
void WriteGetSgmiiModeMsg(uint8 **data, const GetSgmiiModeMsg *msg);
#define ReadGetSgmiiModeResponseMsg ReadSetSgmiiModeMsg
#define WriteGetSgmiiModeResponseMsg WriteSetSgmiiModeMsg
#endif

/*******************************
 * Set/Get active physical port
 *******************************/

/*Set message*/
#ifndef SEMTECH_TARGET
void ReadSetPhysicalPortActiveConfigMsg(uint8 const **data, SetPhysicalPortActiveConfigMsg *msg);
void WriteSetPhysicalPortActiveConfigMsg(uint8 **data, const SetPhysicalPortActiveConfigMsg *msg);
#define ReadSetPhysicalPortActiveConfigResponseMsg ReadSetPhysicalPortActiveConfigMsg
#define WriteSetPhysicalPortActiveConfigResponseMsg WriteSetPhysicalPortActiveConfigMsg

/*get*/
void ReadGetPhysicalPortActiveConfigMsg(uint8 const **data, GetPhysicalPortActiveConfigMsg *msg);
void WriteGetPhysicalPortActiveConfigMsg(uint8 **data, const GetPhysicalPortActiveConfigMsg *msg);
#define ReadGetPhysicalPortActiveConfigResponseMsg ReadSetActivePhysicalPortConfigMsg
#define WriteGetPhysicalPortActiveConfigResponseMsg WriteSetActivePhysicalPortConfigMsg
#endif

/*******************************
 * Set/Get MAC address (NEW)
 *******************************/

/*Set message*/
void ReadSetEthernetMacAddressMsg(uint8 const **data, SetEthernetMacAddressMsg *msg);
void WriteSetEthernetMacAddressMsg(uint8 **data, const SetEthernetMacAddressMsg *msg);
#define ReadSetEthernetMacAddressResponseMsg ReadSetEthernetMacAddressMsg
#define WriteSetEthernetMacAddressResponseMsg WriteSetEthernetMacAddressMsg

/*get*/
#ifndef SEMTECH_TARGET
void ReadGetMacAddressMsg(uint8 const **data, GetEthernetMacAddressMsg *msg);
void WriteGetMacAddressMsg(uint8 **data, const GetEthernetMacAddressMsg *msg);
#define ReadGetMacAddressResponseMsg ReadGetMacAddressMsg
#define WriteGetMacAddressResponseMsg WriteSetMacAddressMsg
#endif

/*******************************
 * Set/Get debug print msg (NEW)
 *******************************/
#ifndef SEMTECH_TARGET
void WriteSetDebugPrintMsg(uint8 **data, const SetDebugPrintMsg *msg);
void ReadSetDebugPrintMsg(uint8 const **data, SetDebugPrintMsg *msg);
void ReadGetDebugPrintMsg (uint8 const **data, GetDebugPrintMsg *msg);

#define ReadSetDebugPrintResponseMsg ReadSetDebugPrintMsg
void WriteGetDebugPrintMsg (uint8 **data, const GetDebugPrintMsg *msg);
#define ReadGetDebugPrintResponseMsg ReadSetDebugPrintMsg

#define WriteSetDebugPrintResponseMsg WriteSetDebugPrintMsg
#define WriteGetDebugPrintResponseMsg WriteSetDebugPrintMsg
#endif

#ifdef __cplusplus
}
#endif

#endif

