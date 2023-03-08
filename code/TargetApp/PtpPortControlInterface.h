/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: PtpPortControlInterface.h $
 * $Revision: 12 $
 * $Date: 28/05/09 19:28 $
 */

/**
 * \file PtpPortsControlInterface.h
 * This file contains the declarations of the handler routines for the PTP ports control 
 * ControlInterface. The PTP ports control messages allow for the configuration and management
 * of the PTP ports.
 */

#ifndef PTP_PORTS_CONTROL_INTERFACE_H
#define PTP_PORTS_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "PtpPort.h"
#include "AcceptablePartnerController.h"
#include "VisibleMaster.h"
#include "ToPSyncTypes.h"
#include "UserData.h"
#include "SMPTEData.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoConfigurePtpPort(const PtpPortConfiguration *ptpPort);
ToPSyncConfigResult DoDeconfigurePtpPort(uint8 ptpPortNumber);
ToPSyncConfigResult DoGetPtpPortConfiguration(uint8 ptpPortNumber, PtpPortConfiguration *ptpPort);
ToPSyncConfigResult DoSetPtpPortEnabled(uint8 ptpPortNumber, Bool enabled);
ToPSyncConfigResult DoSetPtpPortState(uint8 ptpPortNumber, PTPPortState ptpPortState);
ToPSyncConfigResult DoGetPtpPortState(uint8 ptpPortNumber, PTPPortState *ptpPortState);
ToPSyncConfigResult	DoPtpPortSetMessagePeriod(uint8 ptpPortNumber, MessageType messageType, Bool multicast, Bool required,  LogMessagePeriod logPeriod, uint32 grantDuration);
ToPSyncConfigResult	DoPtpPortGetMessagePeriod(uint8 ptpPortNumber, MessageType messageType, Bool multicast, Bool required,  LogMessagePeriod *logPeriod, uint32 *grantDuration);
ToPSyncConfigResult DoSetRequestedAnnounceMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod logPeriod, uint32 grantDuration);
ToPSyncConfigResult DoGetRequestedAnnounceMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod *logPeriod, uint32 *grantDuration);
ToPSyncConfigResult DoSetRequestedSyncMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod logPeriod, uint32 grantDuration);
ToPSyncConfigResult DoGetRequestedSyncMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod *logPeriod, uint32 *grantDuration);
ToPSyncConfigResult DoSetRequestedDelayRequestMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod logPeriod, uint32 grantDuration);
ToPSyncConfigResult DoGetRequestedDelayRequestMessagePeriod(uint8 ptpPortNumber, LogMessagePeriod *logPeriod, uint32 *grantDuration);
ToPSyncConfigResult DoSetAcceptablePartnerTableRequired(uint8 ptpPortNumber, Bool enabled, Bool forMaster);
ToPSyncConfigResult DoGetAcceptablePartnerTableRequired(uint8 ptpPortNumber, Bool *enabled, Bool forMaster);
ToPSyncConfigResult DoSetEnableAcceptableMasterRecord(uint8 ptpPortNumber, uint8 entry, Bool enable);
ToPSyncConfigResult DoSetEnableAcceptableSlaveRecord(uint8 ptpPortNumber, uint16 entry, Bool enable);

ToPSyncConfigResult DoAddAcceptablePartner(uint8 ptpPortNumber, TransmissionProtocolAddress const* address, PortId const* portId, uint8 priority1, uint8 priority2, Bool requestUnicastAnnounceFromMaster, Bool forMaster);
ToPSyncConfigResult DoDeleteAcceptablePartner(uint8 ptpPortNumber, TransmissionProtocolAddress const* address, PortId const* portId, Bool forMaster);
ToPSyncConfigResult DoGetAcceptablePartnerTableEntry(uint8 ptpPortNumber, uint8 entryNumber, uint8 *numberOfTableEntries, AcceptablePartnerTableEntry *acceptablePartnerTableEntry, Bool masterSlave);

ToPSyncConfigResult DoSetDelayToUse(uint8 ptpPortNumber, Bool masterToSlaveDelayUsed, Bool slaveToMasterDelayUsed);
ToPSyncConfigResult DoGetDelayToUse(uint8 ptpPortNumber, Bool *masterToSlaveDelayUsed, Bool *slaveToMasterDelayUsed);
ToPSyncConfigResult DoSetV1Pad(uint8 ptpPortNumber, Bool enable, Bool force);
ToPSyncConfigResult DoGetV1Pad(uint8 ptpPortNumber, Bool* enabled, Bool* active);
ToPSyncConfigResult DoSetPtpNodeId(const NodeId* id);
ToPSyncConfigResult DoGetPtpNodeId(NodeId* id);
ToPSyncConfigResult DoGetDefaultPtpNodeId(NodeId* id);
ToPSyncConfigResult DoSetPtpPortNumberOfMissingAnnounceMessagesToMasterLost(const uint8 ptpPortNumber, uint16 numberOfMissingAnnounceMessages);
ToPSyncConfigResult DoGetPtpPortNumberOfMissingAnnounceMessagesToMasterLost(const uint8 ptpPortNumber, uint16* numberOfMissingAnnounceMessages);

ToPSyncConfigResult DoSetEnablePTPPortMasterOperation(const uint8 ptpPortNumber, Bool enable);
ToPSyncConfigResult DoSetEnablePTPPortSlaveOperation(const uint8 ptpPortNumber, Bool enable);
ToPSyncConfigResult DoGetEnablePTPPortMasterOperation(const uint8 ptpPortNumber, Bool *enable);
ToPSyncConfigResult DoGetEnablePTPPortSlaveOperation(const uint8 ptpPortNumber, Bool *enable);
ToPSyncConfigResult DoSetPtpPortAddressingMode(uint8 ptpPortNumber, PtpPortTransmissionAddressing addressingMode);
ToPSyncConfigResult DoGetPtpPortAddressingMode(uint8 ptpPortNumber, PtpPortTransmissionAddressing* addressingMode);

ToPSyncConfigResult DoSetPtpPortParameter(uint8 ptpPortNumber, uint16 parameter, float value);
ToPSyncConfigResult DoGetPtpPortParameter(uint8 ptpPortNumber, uint16 parameter, float* value);

ToPSyncConfigResult DoSetBMCABitMask(uint8 ptpPortNumber, BMCABitMask mask);
ToPSyncConfigResult DoGetBMCABitMask(uint8 ptpPortNumber, BMCABitMask *mask);

ToPSyncConfigResult DoSetForcedMaster(uint8 ptpPortNumber, Bool enable, uint16 visMasterIndex);
ToPSyncConfigResult DoGetForcedMaster(uint8 ptpPortNumber, Bool *enable, uint16 *visMasterIndex);

void EnableForcedGrantOnSlave(PtpPort* port, AcceptablePartnerRecord const *acceptablePartnerRecord, VisibleMaster *visibleMaster);
ToPSyncConfigResult DoGetIsBetterMasterAvailable(uint8 ptpPortNumber, BetterMasterAvailable *available);

//maybe below should be in VM array
ToPSyncConfigResult DoSetMasterLockOut(uint8 ptpPortNumber, uint16 visMasterIndex, Bool enable);
ToPSyncConfigResult DoGetMasterLockOut(uint8 ptpPortNumber, uint16 visMasterIndex, Bool *enable);

ToPSyncConfigResult DoSetWaitToRestoreTime(uint8 ptpPortNumber, ElapsedTime time);
ToPSyncConfigResult DoGetWaitToRestoreTime(uint8 ptpPortNumber, ElapsedTime *time);
//maybe below should be in VM array
ToPSyncConfigResult DoGetMasterWaitToRestoreTime(uint8 ptpPortNumber, uint16 visMasterIndex, ElapsedTime *time);


/******************************************************************************
 * New functions for memory mapped API (This is work in progress)
 * Functionality subject to change
 ******************************************************************************/

typedef enum
{
	SMPTE_SYS_FRAME_NUMERATOR	= 0,
	SMPTE_SYS_FRAME_DENOMINATOR	= 1,
	SMPTE_MASTER_LOCKING_STATUS	= 2,
	SMPTE_TIME_ADDRESS_FLAGS	= 3,
	SMPTE_CURRENT_LOCAL_OFFSET	= 4,
	SMPTE_JUMP_SECONDS	= 5,
	SMPTE_TIME_OF_NEXT_JUMP0	= 6,
	SMPTE_TIME_OF_NEXT_JUMP1	= 7,
	SMPTE_TIME_OF_NEXT_JAM0	= 8,
	SMPTE_TIME_OF_NEXT_JAM1	= 9,
	SMPTE_TIME_OF_PREV_JAM0	= 10,
	SMPTE_TIME_OF_PREV_JAM1	= 11,
	SMPTE_PREV_JAM_LOCAL_OFFSET = 12,
	SMPTE_DAYLIGHT_SAVING	= 13,
	SMPTE_LEAP_SECOND_JUMP	= 14
}mmApiSmpteControlSubBlockData;


typedef enum
{
	SMPTE_SEND_ENABLE	= 16,
	SMPTE_SEND_PERIOD	= 17,
	SMPTE_SEND_DATA_NOW	= 18
}mmApiSmpteControlSubBlockSend;


typedef enum
{
	SMPTE_RECEIVE_TPA_ADDRESS_LENGTH	= 32,
	SMPTE_RECEIVE_TPA_ADDRESS1	= 33,
	SMPTE_RECEIVE_TPA_ADDRESS2	= 34,
	SMPTE_RECEIVE_TPA_ADDRESS3	= 35,
	SMPTE_RECEIVE_TPA_ADDRESS4	= 36,
	SMPTE_RECEIVE_PORTID_NODEID1	= 37,
	SMPTE_RECEIVE_PORTID_NODEID2	= 38,
	SMPTE_RECEIVE_PORTID_PTPNUM	= 39,
	SMPTE_RECEIVE_DATA_IS_NEW = 40,
	SMPTE_RECEIVE_TIMEOUT = 41
}mmApiSmpteControlSubBlockReceive;



/******************************************************************************
 * MMAPI_PTP_SLAVE_PORT_0_PARAMS Block Description
 * - Subblocks defined by mmApiPtpPortSubBlock enum
 * - individual parameters defined by mmApiPtpPortSubBlockParams enum
 ******************************************************************************/
//SUBBLOCKSDEF:MMAPI_PTP_PORT1_PARAMS
//SUBBLOCKSDEF:MMAPI_PTP_PORT2_PARAMS
typedef enum
{
	PTP_PORT_SLAVE_SUBBLOCK_GENERAL				= 0,   /* General Parameters */
	PTP_PORT_SLAVE_SUBBLOCK_PARAMS    			= 1,   /* Generic Parameters */
	PTP_PORT_SLAVE_SUBBLOCK_MODE_PARAMS         = 2,   /* Detailed setup for both PTP mode and Timestamp processor mode. */
	PTP_PORT_SLAVE_SUBBLOCK_STATS    			= 3,   /* Read only PTP slave statistics. */
	PTP_PORT_SLAVE_SUBBLOCK_SEND_USER_DATA 		= 4,					/* Subsystem to allow user defined data to be sent between devices*/
	PTP_PORT_SLAVE_SUBBLOCK_RECEIVE_USER_DATA	= 5,				/* Subsystem to allow user defined data to be received between devices*/
	PTP_PORT_SLAVE_SUBBLOCK_RECEIVE_SMPTE_DATA	= 6,			/* Subsystem to allow smpte data to be received between devices*/
	PTP_PORT_SLAVE_SUBBLOCKS_END
} mmApiPtpPortSlaveSubBlock;

//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_STATS
/*
 + PTP_PORT_SLAVE_STATS_LAST_T#n#_SECS_HI, Bits 47 through 32 of seconds portion of last T#n# time stamp seen, ro, 0
   Bits[31:16]  reserved
   Bits[15:0]   bits 47 to 32 of the 48-bit seconds field in the last IEEE T#n# time stamp received /
                (via normal PTP flow or mode 2 time stamp replacement methods)
                /
   Notes: This is just a snapshot of the last time stamp seen when this API call was serviced. If read in a block /
          it is not guaranteed that timestamps are paired. For example, if T1|3 and T2|4 timestamps are read, the two /
          may be from packets with different sequence id's... they are just the last seen.

 + PTP_PORT_SLAVE_STATS_LAST_T#n#_SECS_LO, Bits 31 through 0 of seconds portion of last T#n# time stamp seen, ro, 0
   Bits[31:0]   bits 31 to 0 of the 48-bit seconds field in the last IEEE T#n# time stamp received /
                (via normal PTP flow or mode 2 time stamp replacement methods)

 + PTP_PORT_SLAVE_STATS_LAST_T#n#_NANOS, Nanoseconds portion of last T#n# time stamp seen, ro, 0
   Bits[31:0]   bits 31 to 0 of the nanoseconds field in the last IEEE T#n# time stamp received /
                (via normal PTP flow or mode 2 time stamp replacement methods)

 + PTP_PORT_SLAVE_STATS_NUM_T#n#_VALID, Num T#n# valid, ro, 0
   Bits[31:0]   a rolling 32-bit counter indicating the number of valid T#n# time stamps received.

 + PTP_PORT_SLAVE_STATS_NUM_T#n#_INVALID, Num T#n# invalid, ro, 0
   Bits[31:0]   a rolling 32-bit counter indicating the number of invalid T#n# time stamps received. An invalid /
                time stamp is one that does not conform to the IEEE1588 specification or contains unintelligible data.

 + PTP_PORT_SLAVE_STATS_NUM_T#n#_DROPPED, Num T#n# valid but dropped, ro, 0
   Bits[31:0]   a rolling 32-bit counter indicating the number of valid T#n# time stamps received that were /
                not used because their pair time stamp was not seen (in time). For example, a T1 time stamp could /
                be received, but if the corresponding T2 was never delivered by the remote time stamping PHY then the /
                T1 would be dropped.

 + PTP_PORT_SLAVE_STATS_DRMS_RECEIVED, Num DRM messages received, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.
   /
   Note: Although this is grouped with port-specific statistics, this is not port specific and applies globally.

 + PTP_PORT_SLAVE_STATS_DRMS_DROPPED, Num DRM messages received but dropped, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.
   /
   Note: Although this is grouped with port-specific statistics, this is not port specific and applies globally.

 + PTP_PORT_SLAVE_STATS_DRMS_BAD_PTP_PORT, Num DRMS messages received but with invalid PTP port number, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.
   /
   Note: Although this is grouped with port-specific statistics, this is not port specific and applies globally.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_SRC_SEL, Num of source-select DRM messages received, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: that this only applies when ToPSync is operating in timestamp processor /
         mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_SRC_DESEL, Num of source-deselect DRM messages received, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: that this only applies when ToPSync is operating in timestamp processor /
         mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_T#n#_RECEIVED, Num of T#n# DRM messages received, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_T#n#_INVALID, Num of T#n# DRM messages received but deemed invalid, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_T#n#_INVALID_STAMP, Num of T#n# DRM messages received but deemed invalid due to a bad timestamp value, ro, 0
   Bits[31:0]   a rolling 32-bit counter. An invalid time stamp is one that does not conform to the IEEE1588 /
                specification or contains unintelligible data.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_T#n#_INVALID_MAJ, Num of T#n# DRM messages received but with an invalid major mode, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.

 + PTP_PORT_SLAVE_STATS_DRMS_NUM_T#n#_INVALID_MIN, Num of T#n# DRM messages received but with an invalid minor mode, ro, 0
   Bits[31:0]   a rolling 32-bit counter.
   /
   Note: This is DRM specific so will only apply in either PTP mode, using DRMs for remote timestamp delivery, or when /
         in timestamp processor mode. The ToPSync mode of operation can be read from register %PTP_PORT_SLAVE_MODE_SELECT%.
 */
typedef enum
{
	PTP_PORT_SLAVE_STATS_LAST_T1_SECS_HI             = 0,
	PTP_PORT_SLAVE_STATS_LAST_T1_SECS_LO             = 1,
	PTP_PORT_SLAVE_STATS_LAST_T1_NANOS               = 2,

	PTP_PORT_SLAVE_STATS_LAST_T2_SECS_HI             = 3,
	PTP_PORT_SLAVE_STATS_LAST_T2_SECS_LO             = 4,
	PTP_PORT_SLAVE_STATS_LAST_T2_NANOS               = 5,

	PTP_PORT_SLAVE_STATS_LAST_T3_SECS_HI             = 6,
	PTP_PORT_SLAVE_STATS_LAST_T3_SECS_LO             = 7,
	PTP_PORT_SLAVE_STATS_LAST_T3_NANOS               = 8,

	PTP_PORT_SLAVE_STATS_LAST_T4_SECS_HI             = 9,
	PTP_PORT_SLAVE_STATS_LAST_T4_SECS_LO             = 10,
	PTP_PORT_SLAVE_STATS_LAST_T4_NANOS               = 11,

	PTP_PORT_SLAVE_STATS_NUM_T1_VALID                = 12,
	PTP_PORT_SLAVE_STATS_NUM_T1_INVALID              = 13,
	PTP_PORT_SLAVE_STATS_NUM_T1_DROPPED              = 14,

	PTP_PORT_SLAVE_STATS_NUM_T2_VALID                = 15,
	PTP_PORT_SLAVE_STATS_NUM_T2_INVALID              = 16,
	PTP_PORT_SLAVE_STATS_NUM_T2_DROPPED              = 17,

	PTP_PORT_SLAVE_STATS_NUM_T3_VALID                = 18,
	PTP_PORT_SLAVE_STATS_NUM_T3_INVALID              = 19,
	PTP_PORT_SLAVE_STATS_NUM_T3_DROPPED              = 20,

	PTP_PORT_SLAVE_STATS_NUM_T4_VALID                = 21,
	PTP_PORT_SLAVE_STATS_NUM_T4_INVALID              = 22,
	PTP_PORT_SLAVE_STATS_NUM_T4_DROPPED              = 23,

	PTP_PORT_SLAVE_STATS_DRMS_RECEIVED               = 24,
	PTP_PORT_SLAVE_STATS_DRMS_DROPPED                = 25,
	PTP_PORT_SLAVE_STATS_DRMS_BAD_PTP_PORT           = 26,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_SRC_SEL            = 27,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_SRC_DESEL          = 28,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_T1_RECEIVED        = 29,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T1_INVALID         = 30,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T1_INVALID_STAMP   = 31,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T1_INVALID_MAJ     = 32,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T1_INVALID_MIN     = 33,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_T2_RECEIVED        = 34,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T2_INVALID         = 35,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T2_INVALID_STAMP   = 36,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T2_INVALID_MAJ     = 37,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T2_INVALID_MIN     = 38,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_T3_RECEIVED        = 39,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T3_INVALID         = 40,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T3_INVALID_STAMP   = 41,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T3_INVALID_MAJ     = 42,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T3_INVALID_MIN     = 43,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_T4_RECEIVED        = 44,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T4_INVALID         = 45,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T4_INVALID_STAMP   = 46,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T4_INVALID_MAJ     = 47,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_T4_INVALID_MIN     = 48,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_SYNC_RECEIVED      = 49,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_SYNC_INVALID       = 50,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_SYNC_INVALID_STAMP = 51,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_SYNC_INVALID_MAJ   = 52,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_SYNC_INVALID_MIN   = 53,

	PTP_PORT_SLAVE_STATS_DRMS_NUM_DLY_RECEIVED       = 54,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_DLY_INVALID        = 55,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_DLY_INVALID_STAMP  = 56,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_DLY_INVALID_MAJ    = 57,
	PTP_PORT_SLAVE_STATS_DRMS_NUM_DLY_INVALID_MIN    = 58,

	PTP_PORT_SLAVE_STATS_END
}mmApiPtpPortSlaveSubBlockInfoParams;


//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_MODE_PARAMS
/*
   + PTP_PORT_SLAVE_MODE_SELECT, Mode of port operation, rw, 0
     Bits[31:1] = Reserved.
     Bits[0:0]  = Mode of operation. See UG-TS2 01.
                 0 - PTP mode.
                 1 - Timestamp processor mode.
     /
     Notes: This register must only be changed when the PTP port is deconfigured (see register /
            %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.


   + PTP_PORT_SLAVE_MODE_2_T#n#_MAJOR_MODE, MODE 2: Major mode of T#n# timestamp-value delivery to the TopSync slave, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  major timestamping mode defines how PTP packet T#n# timestamp values are delivered to ToPSync.
                0 - Internal  -               Timestamping is done locally at the ToPSync PHY.
                1 - DRM       -               Timestamping is done remotely. Timestamps are delivered to ToPSync using /
                                              Delay Replacement Messages (DRMs). The transport mechanism is defined by /
                                              the minor mode.
                2 - Structured in-band -      Timestamping is done remotely. T#n# timestamps are delivered to ToPSync /
                                              by inserting the T#n# timestamp as a Semtech proprietary TLV in the PTP /
                                              message. The type of the TLV is defined by the minor mode.
                3 - Unstructured in-band -    Timestamping is done remotely. Timestamps are delivered to ToPSync by /
                                              inserting the T#n# timestamp at a specific location offset from the /
                                              start of the PTP payload, defined by the registers /
                                              %PTP_PORT_SLAVE_MODE_2_T#n#_TIME_EMBED_LOC_SECS_HI%, through /
                                              %PTP_PORT_SLAVE_MODE_2_T#n#_TIME_EMBED_LOC_NANOS%. The minor mode /
                                              defines the endianess and the timestamp format determines whether /
                                              the second-field offset register is used.
                4 - Reserved
                5 - Local transparent clock - Timestamping is done remotely. See UG_TS2 01 for further information.
                6-15 - Reserved
     /
     Notes: This register must only be changed when the PTP port is deconfigured (see register /
            %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     See also: The minor mode register (%PTP_PORT_SLAVE_MODE_2_T#n#_MINOR_MODE%) and timestamp-value format /
               (%PTP_PORT_SLAVE_MODE_2_T#n#_TIME_FORMAT%).


   + PTP_PORT_SLAVE_MODE_2_T#n#_MINOR_MODE, MODE 2: The minor mode for T#n# fills in the details of the major mode of timestamp delivery, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  the minor timestamping mode defines the format of T#n# timestamp values delivered to ToPSync. Register /
                value meanings depend on the major mode register %PTP_PORT_SLAVE_MODE_2_T#n#_MAJOR_MODE%.
                /
                If the major mode is "1 - DRM" then valid configuration is as follows.
                1 - DRMs delivered via Ethernet only. SPI DRMs will be ignored.
                2 - DRMs delivered via SPI. Ethernet DRMs will be ignored.
                3 - DRMS delivered via Ethernet or SPI.
                /
                If the major mode is "2 - Structure in-band" then valid configuration is as follows (see UG_TS2 01 /
                for further information).
                1 - Short TLV format is expected.
                2 - Long TLV format is expected.
                /
                If the major mode is "3 - Unstructured in-band" then valid configuration is as follows.
                1 - Timestamp is embedded as little endian data.
                2 - Timestamp is embedded as big endian data.
                /
                For other modes, this register is not used.
     /
     Notes: If the major mode (register %PTP_PORT_SLAVE_MODE_2_T#n#_MAJOR_MODE%) is set to internal, this register /
            is not used.
     Notes: This register must only be changed when the PTP port is deconfigured (see register /
            %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).


   + PTP_PORT_SLAVE_MODE_2_T#n#_TIME_FORMAT, MODE 2: Format of T#n# timestamps, rw, 1
     Bits[31:4] reserved
     Bits[3:0]  timestamp format. Defines whether timestamp will be nanoseconds only or full seconds and nanoseconds.
                0 - sub-second timestamps (32-bit nanosecond) are expected only.
                1 - full 10 octet timestamps as defined in IEEE 1588-2008 are expected (seconds and nanoseconds).
                2 - timestamp will contain a nanosecond timestamp with full 32bit value range (external timestamper has /
                free running 32bit timestamper sync'ed to seconds value of epoch)

     /
     Notes: If the major mode (register %PTP_PORT_SLAVE_MODE_2_T#n#_MAJOR_MODE%) is set to internal, this register /
            is not used.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).


   + PTP_PORT_SLAVE_MODE_2_T#n#_TIME_EMBED_LOC_NANOS, MODE 2: Offset of the T#n# 32-bit nanoseconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x10
     Bits [31:0] offset of the 32-bit nanosecond portion of the unstructured in-band timestamp value from the start of /
                 the PTP payload. The offset may go past the end of the PTP packet payload as long as the /
                 encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used and /
            %PTP_PORT_SLAVE_MODE_2_T#n#_TIME_FORMAT% is '1'.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).

   + PTP_PORT_SLAVE_MODE_2_T#n#_TIME_EMBED_LOC_SECS_HI, MODE 2: Offset of bits 47 to 32 of the T#n# 48-bit seconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x44
     Bits [31:0] offset of the most significant 16 bits of the second portion of the unstructured in-band timestamp /
                 value from the start of the PTP payload. The offset may go past the end of the PTP packet payload as /
                 long as the encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used and /
            %PTP_PORT_SLAVE_MODE_2_T#n#_TIME_FORMAT% is '1'.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).

   + PTP_PORT_SLAVE_MODE_2_T#n#_TIME_EMBED_LOC_SECS_LO, MODE 2: Offset of bits 31 to 0 of the T#n# 48-bit seconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x46
     Bits [31:0] offset of the lease significant 32 bits of the second portion of the unstructured in-band timestamp /
                 value from the start of the PTP payload. The offset may go past the end of the PTP packet payload as /
                 long as the encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).

   + PTP_PORT_SLAVE_MODE_2_T3_IS_TIMESTAMPED, MODE 2: Whether egress delay request packets are timestamped, rw, 1
     Bits[31:1] reserved
     Bits[0:0]  flag defines whether egress delay request packets are timestamped as they leave ToPSync or whether /
                a user defined pattern is written into the origin timestamp field instead.
                1 - the egress delay request PTP packet's origin timestamp field is filled with the packet egress time.
                0 - the egress delay request PTP packet's origin timestamp field is filled with a user defined /
                    pattern (see registers %PTP_PORT_SLAVE_MODE_2_T3_PATTERN_SECONDS_HI% through /
                    %PTP_PORT_SLAVE_MODE_2_T3_PATTERN_NANOSECONDS%) and is not timestamped.
     /
     Notes: If the major mode (register %PTP_PORT_SLAVE_MODE_2_T3_MAJOR_MODE%) is set to local timestamping this /
            register is not used.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).


   + PTP_PORT_SLAVE_MODE_2_T3_PATTERN_SECONDS_HI, MODE 2: Egress delay request timestamp-pattern seconds bits 47 to 32, rw, 0
     Bits[31:16] = reserved
     Bits[15:0]  = pattern that will be written into bits 47 to 32 of the seconds field of the egress delay request /
                   origin timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     Notes: This pattern is only used when egress delay request packets are NOT being timestamped.
     See also: Register %PTP_PORT_SLAVE_MODE_2_T3_IS_TIMESTAMPED% defining if T3 is timestamped.


   + PTP_PORT_SLAVE_MODE_2_T3_PATTERN_SECONDS_LO, MODE 2: Egress delay request timestamp-pattern seconds bits 31 to 0, rw, 0
     Bits[31:0] pattern that will be written into bits 31 to 0 of seconds field of the egress delay request origin /
                timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     Notes: This pattern is only used when egress delay request packets are NOT being timestamped.
     See also: Register %PTP_PORT_SLAVE_MODE_2_T3_IS_TIMESTAMPED% defining if T3 is timestamped.


   + PTP_PORT_SLAVE_MODE_2_T3_PATTERN_NANOSECONDS, MODE 2: Egress delay request timestamp-pattern nanoseconds, rw, 0
	 Bits[31:0] pattern that will be written into bits 31 to 0 of the nanoseconds field of the egress delay request /
	            origin timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if the port /
            is in PTP mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     Notes: This pattern is only used when egress delay request packets are NOT being timestamped.
     See also: Register %PTP_PORT_SLAVE_MODE_2_T3_IS_TIMESTAMPED% defining if T3 is timestamped.


   + PTP_PORT_SLAVE_MODE_3_DELIVERY_METHOD, MODE 3: Delivery method (Ethernet | SPI), rw, 0
     Bits[31:4] reserved
     Bits[3:0]  Bit mask specifiying acceptable modes of DRM delivery.
     0000 - Disables DRM delivery!
     0001 - Enables SPI delivery only
     0010 - Enables Ethernet delivery only
     0011 - Enables both SPI and Ethernet delivery.
     xxxx - All other values are invalid.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if TopSync /
            is in timestamp-processor mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     Notes: Applies only to timestamp processor mode.


   + PTP_PORT_SLAVE_MODE_3_TIME_FORMAT, MODE 3: Format of timestamps being delivered, rw, 0
     Bits[31:4] reserved
     Bits[3:0]
	 0 - 32-bit nanosecond timestamps expected.
     1 - full 48-bit seconds and 32-bit nanoseconds (IEEE1588) timestamps expected.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_SLAVE_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect if TopSync /
            is in timestamp-processor mode (see register %PTP_PORT_SLAVE_MODE_SELECT%).
     Notes: Applies only to timestamp processor mode.

 */
typedef enum
{
	PTP_PORT_SLAVE_MODE_SELECT                      = 0,

	PTP_PORT_SLAVE_MODE_2_T2_MAJOR_MODE             = 1,
	PTP_PORT_SLAVE_MODE_2_T2_MINOR_MODE             = 2,
	PTP_PORT_SLAVE_MODE_2_T2_TIME_FORMAT            = 3,
	PTP_PORT_SLAVE_MODE_2_T2_TIME_EMBED_LOC_SECS_HI = 4,
    PTP_PORT_SLAVE_MODE_2_T2_TIME_EMBED_LOC_SECS_LO = 5,
	PTP_PORT_SLAVE_MODE_2_T2_TIME_EMBED_LOC_NANOS   = 6,
	PTP_PORT_SLAVE_MODE_2_T3_IS_TIMESTAMPED         = 7,
	PTP_PORT_SLAVE_MODE_2_T3_PATTERN_SECONDS_HI     = 8,
	PTP_PORT_SLAVE_MODE_2_T3_PATTERN_SECONDS_LO     = 9,
	PTP_PORT_SLAVE_MODE_2_T3_PATTERN_NANOSECONDS    = 10,
	PTP_PORT_SLAVE_MODE_2_T3_MAJOR_MODE             = 11,
	PTP_PORT_SLAVE_MODE_2_T3_MINOR_MODE             = 12,
	PTP_PORT_SLAVE_MODE_2_T3_TIME_FORMAT            = 13,
	PTP_PORT_SLAVE_MODE_2_T3_TIME_EMBED_LOC_SECS_HI = 14,
	PTP_PORT_SLAVE_MODE_2_T3_TIME_EMBED_LOC_SECS_LO = 15,
	PTP_PORT_SLAVE_MODE_2_T3_TIME_EMBED_LOC_NANOS   = 16,

	PTP_PORT_SLAVE_MODE_3_DELIVERY_METHOD           = 17,
	PTP_PORT_SLAVE_MODE_3_TIME_FORMAT               = 18,

	PTP_PORT_SLAVE_MODE_END
}mmApiPtpPortSlaveSubBlockModeParams;


//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_GENERAL
/*
	+ PTP_PORT_SLAVE_GENERAL_CONNECTOR, physical port connector, rw, 0
	Bits[31:8]	reserved
	Bits[7:0] 	connector. The physical port that this ptp port is connected to, starting from 0.
			Notes: It is recommended that the first five words, connector, protocol, version, domain and configure are set at the same time.

	+ PTP_PORT_SLAVE_GENERAL_PROTOCOL, ptp port protocol, rw, 0
	Bits[31:2]	reserved
	Bits[1:0]	protocol. 	The protocol used in the ptp port.
			0 udp4,
			1 ethernet,
			2 udp6

	+ PTP_PORT_SLAVE_GENERAL_VERSION, ptp port version, ro, 2
	Bits[31:3]	reserved
	Bits[2:0]	version
			1 version1,
			2 version2

	+ PTP_PORT_SLAVE_GENERAL_CONFIGURE, configure ptp port, rw, 0
	Bits[31:1]	reserved
	Bits[0:0]	configure
			0 deconfigure,
			1 configure
			Notes: Resets the PTP port, then configures the ptp port with the settings 'physical port connector', 'ptp /
			port protocol', 'ptp port version' and 'domain' (registers %PTP_PORT_SLAVE_GENERAL_CONNECTOR% through /
			%PTP_PORT_SLAVE_GENERAL_DOMAIN%). The mode configurations will also be applied at this point (see registers /
			%PTP_PORT_SLAVE_MODE_SELECT% through %PTP_PORT_SLAVE_MODE_3_TIME_FORMAT%). Finally the network interface /
			is enabled and the PTP port enters the listening state.
			Notes: Deconfiguring a port will also disable the port.


	+ PTP_PORT_SLAVE_GENERAL_ENABLE, enable ptp port, rw, 0
	Bits[31:1]	reserved
	Bits[0:0]	enable
			0 disable,
			1 enable
			Enables the ptp port for use. If enabled it will allow the ptp port to begin moving through it's /
			states and PTP traffic to flow.
			Notes: A PTP port must be configured (%PTP_PORT_SLAVE_GENERAL_CONFIGURE%) before it can be enabled or /
			       disabled. Disabling a PTP port does not deconfigure it.

    + PTP_PORT_SLAVE_GENERAL_VIRTUAL_INTERFACE_NUMBER, virtual interface number, rw, 0
	Bits[31:3]  reserved
	Bits[2:0]   virtual interface number

	+ PTP_PORT_SLAVE_GENERAL_MHOME_INDEX, multi home index of address on interface, rw, 0
	Bits[31:4]  reserved
	Bits[3:0]  multi home index of address on interface

	+ PTP_PORT_SLAVE_GENERAL_DOMAIN, ptp port domain, rw, 0
	Bits[31:8]	reserved
	Bits[7:0]	domain (starting from 0)
			Notes: 	Set the domain number of the ptp port. This can be set at the same time as configuring the ptp port.
			It can also be set by itself when a ptp port has already been configured.
			It will only be able to communicate with other ptp ports on the same domain.


	- PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_MULTI_DES_PERIOD, desired multicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 6 to -4)
			Notes: 	The desired multicast log period of the announce message.
			The desired log period is the smallest (and hence fastest rate) that is desired.
			The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			This setting should only be used on a ptp port that actually provides these multicast messages.


	+ PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_REQ_PERIOD, required unicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 6 to -4)
			Notes: 	required unicast log period of the announce message.
			The desired log period is the smallest (and hence fastest rate) that is desired.
			The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	+ PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_REQ_DURATION, required unicast announce duration, rw, 250
	Bits[31:0]	duration
			Notes: 	Set duration of the required unicast grant duration of the announce message.


	+ PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_DES_PERIOD, desired unicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 6 to -4)
			Notes: Set desired unicast log period of the announce message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	- PTP_PORT_SLAVE_GENERAL_SYNC_MSG_MULTI_DES_PERIOD, desired multicast sync log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: 	Set desired multicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			This setting should only be used on a ptp port that actually provides these multicast messages.

	+ PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_REQ_PERIOD, required unicast sync log period, rw, -3
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: 	Set required unicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			It is recommended to set this and the next two parameters at the same time.


	+ PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_REQ_DURATION, required unicast sync duration, rw, 250
	Bits[31:0]	duration
			Notes: 	Set duration of the required unicast grant duration of the sync message.


	+ PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_DES_PERIOD, desired unicast sync log period, rw, -5
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: 	Set desired unicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.

	+ PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_MULTI_DES_PERIOD, desired multicast delay resp log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: 	Set desired multicast log period of the delay resp message. The desired log period is the smallest
			(and hence fastest rate) that is desired. The required log period is the largest (and hence slowest rate) that is
			satisfactory to the ptp port.
			This setting should only be used on a ptp port that actually provides these multicast messages.


	+ PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_REQ_PERIOD, required unicast delay resp log period, rw, -3
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: 	Set required unicast log period of the delay resp message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			It is recommended to set this and the next two parameters at the same time.


	+ PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_REQ_DURATION, required unicast delay resp duration, rw, 250
	Bits[31:0]	duration
			Notes :	Set duration of the required delay resp grant duration of the sync message.


	+ PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_DES_PERIOD, desired unicast delay resp log period, rw, -5
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 4 to -7)
			Notes: Set desired unicast log period of the delay resp message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.

	+ PTP_PORT_SLAVE_GENERAL_NODE_ID_1, The node id of the ptp port bytes 0 to 3, rw, 0x0
	Bits[31:0]	The first set of 4 bytes of the node id
			Notes: 	The first set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
			It is recommended to set all of these two node id words in one go.

	+ PTP_PORT_SLAVE_GENERAL_NODE_ID_2, The node id of the ptp port bytes 4 to 7, rw, 0x0
	Bits[31:0]	The second set of 4 bytes of the node id
			Notes: 	The second set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
			It is recommended to set all of these two node id words in one go.


	+ PTP_PORT_SLAVE_GENERAL_DEFAULT_NODE_ID_1, The default node id of the ptp port, ro, 0x0
	Bits[31:0]	The first set of 4 bytes of the node id
			Notes: The first set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
			It is recommended to get all of these two node id words in one go.


	+ PTP_PORT_SLAVE_GENERAL_DEFAULT_NODE_ID_2, The default id of the ptp port, ro, 0x0
	Bits[31:0]	The second set of 4 bytes of the node id
			Notes: 	The second set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
			It is recommended to get all of these two node id words in one go.


	+ PTP_PORT_SLAVE_GENERAL_PTP_STATE, The state of the ptp port, ro, 0x0
	Bits[31:4]	reserved
	Bits[3:0]	state of the ptp port
			0 = portFaulty,
			1 = portDisabled,
			2 = portListening,
			3 = portPreMaster,
			4 = portMaster,
			5 = portPassive,
			6 = portUncalibrated,
			7 = portSlave


	+ PTP_PORT_SLAVE_GENERAL_MS_DELAY_TO_USE, use master to slave delays, rw, 0x1
	Bits[31:1]	reserved
	Bits[0:0]	m2s delay
			0 = disable,
			1 = enable
			Notes: 	Configures the ptp port to use master to slave delays.
			It is recommended to set this and the next parameter at the same time.
			If this and the next parameter are enabled then delays in both directions will be used.


	+ PTP_PORT_SLAVE_GENERAL_SM_DELAY_TO_USE, use slave to master delays, rw, 0x1
	Bits[31:1]	reserved
	Bits[0:0]	m2s delay
				0 = disable,
				1 = enable
				Notes: 	Configures the ptp port to use slave to master delays.
				It is recommended to set this and the previous parameter at the same time.
				If this and the previous parameter are enabled then delays in both directions will be used.


	+ PTP_PORT_SLAVE_GENERAL_MISSING_ANNOUNCE, number of missing announce messages, rw, 0x5
	Bits[31:16]	reserved
	Bits[15:0] = number of missing announce
				Notes: Configures the number of missing announce messages after which the master is considered to be lost.


	+ PTP_PORT_SLAVE_GENERAL_BMCA_MASK, best master clock algorithm mask, rw, 0xBF
	Bits[31:8] = reserved
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


	+ PTP_PORT_SLAVE_GENERAL_FORCED_MASTER_ENABLE, enabled forced master operation, rw, 0x0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the forced master operation. If set then the next parameter gives the visible master index of the device
				to be the current master, thus overriding the usual selection method.
				It is recommended to set this and the next parameter at the same time.


	+ PTP_PORT_SLAVE_GENERAL_FORCED_MASTER_INDEX, visible master index of the forced master, rw, 0x0
	Bits[31:8] = reserved
	Bits[7:0] = index (from 0 to max number of visible masters)
				Notes: 	Sets visible master index of the device to be the current master, thus overriding the usual selection method.
				It is recommended to set this and the previous parameter at the same time.


	+ PTP_PORT_SLAVE_GENERAL_BETTER_MASTER_AVAILABLE, better master available flag, ro, 0x0
	Bits[31:1] = reserved
	Bits[0:0] = flag
				0 = true,
				1 = false
				Notes: 	This indicates if there is a better master available than the currently selected master.

	+ PTP_PORT_SLAVE_GENERAL_WAIT_TO_RESTORE, wait to restore time, rw, 0x0
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Set the time in seconds after which a visible master can be considered to be the current master.

	+ PTP_PORT_SLAVE_GENERAL_REVERTIVE_SAME_TRANSPORT, Enable Revertive Operation On Same Transport, rw, 0
	  Bits[31:1] Reserved
	  Bits[0]    = 1 - Revertive operation enabled, 0 - disabled
	  Note this controls the revertive operation on the PTP port.  There is a separate configuration
	  for revertive operation for Node Time inputs

*/

typedef enum
{
	PTP_PORT_SLAVE_GENERAL_CONNECTOR             = 0,
	PTP_PORT_SLAVE_GENERAL_PROTOCOL              = 1,
	PTP_PORT_SLAVE_GENERAL_VERSION               = 2,
	PTP_PORT_SLAVE_GENERAL_DOMAIN                = 3,
	PTP_PORT_SLAVE_GENERAL_CONFIGURE             = 4, /* Note: will use 4 prev params if configured */
	PTP_PORT_SLAVE_GENERAL_ENABLE                = 5, /* Enable / disable port */

	PTP_PORT_SLAVE_GENERAL_VIRTUAL_INTERFACE_NUMBER	= 7, /* Skipped 6 so that offset matches Master */
	PTP_PORT_SLAVE_GENERAL_MHOME_INDEX			  = 8,

	PTP_PORT_SLAVE_GENERAL_NODE_ID_1              = 16, /* Note: two consecutive params */
	PTP_PORT_SLAVE_GENERAL_NODE_ID_2		      = 17,

	PTP_PORT_SLAVE_GENERAL_DEFAULT_NODE_ID_1     = 18, /* Note: two consecutive params */
	PTP_PORT_SLAVE_GENERAL_DEFAULT_NODE_ID_2	 = 19,

	PTP_PORT_SLAVE_GENERAL_PTP_STATE             = 20,
	PTP_PORT_SLAVE_GENERAL_BMCA_MASK			 = 21,
	PTP_PORT_SLAVE_GENERAL_BETTER_MASTER_AVAILABLE	= 22,

	PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_MULTI_DES_PERIOD   	= 32,
	PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_REQ_PERIOD   	= 33, /*  Note: best to set next two consecutive params in one hit */
	PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_REQ_DURATION  	= 34,
	PTP_PORT_SLAVE_GENERAL_ANNOUNCE_MSG_UNI_DES_PERIOD   	= 35,

	PTP_PORT_SLAVE_GENERAL_SYNC_MSG_MULTI_DES_PERIOD	= 36,
	PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_REQ_PERIOD   	= 37, /* Note: best to set next two consecutive params in one hit */
	PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_REQ_DURATION  	= 38,
	PTP_PORT_SLAVE_GENERAL_SYNC_MSG_UNI_DES_PERIOD   	= 39,

	PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_MULTI_DES_PERIOD   = 40,
	PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_REQ_PERIOD   	= 41, /*  Note: best to set next two consecutive params in one hit */
	PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_REQ_DURATION  	= 42,
	PTP_PORT_SLAVE_GENERAL_DELAYRESP_MSG_UNI_DES_PERIOD   	= 43,


	PTP_PORT_SLAVE_GENERAL_MS_DELAY_TO_USE       = 80,
	PTP_PORT_SLAVE_GENERAL_SM_DELAY_TO_USE       = 81,

	PTP_PORT_SLAVE_GENERAL_MISSING_ANNOUNCE      = 82,

	PTP_PORT_SLAVE_GENERAL_FORCED_MASTER_ENABLE	= 83,  /*best to set/get next two params at the same time*/
	PTP_PORT_SLAVE_GENERAL_FORCED_MASTER_INDEX	= 84,
	PTP_PORT_SLAVE_GENERAL_WAIT_TO_RESTORE		= 85,
	PTP_PORT_SLAVE_GENERAL_REVERTIVE_SAME_TRANSPORT	= 86,

	PTP_PORT_SLAVE_GENERAL_END

}mmApiPtpPortSlaveSubBlockGeneralParams;
//note for above that you can't have multicast and required message periods, and you can't set multicast duration



/* todo: Check with Adrian how he intends to consolidate enums
 * since PtpPort.h already takes care of the following
 */
//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_PARAMS
/*
	+ PTP_PORT_SLAVE_PARAMS_ADDRESSING_MODE, addressing mode, rw, 0
	Bits[31:2] = reserved
	Bits[1:0] = addressing mode
				asAppropriate = 0,
				unicastOnly = 1,
				multicastOnly = 2
				Notes: 	Sets the addressing mode of the ptp port.


	+ PTP_PORT_SLAVE_PARAMS_USE_P_DELAY, enable path delay request messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				This enables sending of path delay request messages.

	+ PTP_PORT_SLAVE_PARAMS_ANNOUNCE_GRANT_REQUEST_THRESHOLD, announce grant request threshold, rw, 20
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the announce grant request threshold - this is the time remaining for a grant after which
				new grant requests will be made.


	+ PTP_PORT_SLAVE_PARAMS_SYNC_GRANT_REQUEST_THRESHOLD, sync grant request threshold, rw, 20
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the sync grant request threshold - this is the time remaining for a grant after which
				new grant requests will be made.


	+ PTP_PORT_SLAVE_PARAMS_DELAY_GRANT_REQUEST_THRESHOLD, delay grant request threshold, rw, 20
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the delay grant request threshold - this is the time remaining for a grant after which
				new grant requests will be made.


	+ PTP_PORT_SLAVE_PARAMS_ANNOUNCE_GRANT_REPEAT_PERIOD, announce grant repeat period, rw, 2
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the announce grant repeat period - when grant requests are made they will be repeated at this interval.


	+ PTP_PORT_SLAVE_PARAMS_SYNC_GRANT_REQUEST_REPEAT_PERIOD, sync grant repeat period, rw, 2
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the sync grant repeat period - when grant requests are made they will be repeated at this interval.


	+ PTP_PORT_SLAVE_PARAMS_DELAY_GRANT_REQUEST_REPEAT_PERIOD, delay grant repeat period, rw, 2
	Bits[31:16] = reserved
	Bits[15:0] = time in s
				Notes: 	Sets the delay grant repeat period - when grant requests are made they will be repeated at this interval.


	- PTP_PORT_SLAVE_PARAMS_BE_SLAVE_EVEN_WHEN_MASTER_TIME_NOT_USED, slave when master's time not used, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to be a slave even when the master's time is not used.
				Do the customers ever use this ?
				DoSetPtpPortParameter(0, setBeSlaveEvenWhenMastersTimeIsNotUsed, 1.0f); is called from systemcontrol
				and DoSetToPSyncGlobalParameter for enablePrinting.

	+ PTP_PORT_SLAVE_PARAMS_HOLDOFF_TIMER, holdoff timer, rw, 0
	Bits[31:0] = time in s, sint32
				Notes: 	Enables the holdoff timer which is the time from when the master is not visible until when the port will
				stop considering it as a use-able master. A non zero value will begin this operation.

	+ PTP_PORT_SLAVE_PARAMS_MS_ACCEPT_MULTICAST_TIMING_MESSAGES,  accept ms multicast timing messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to accept master to slave multicast timing messages.
				When there are no active unicast grants and this flag is true then it means the timing
				situation is good. Thus the state of the visible master can be set to valid - meaning it can be used as
				a master.


	+ PTP_PORT_SLAVE_PARAMS_MS_ENABLE_UNICAST_GRANT_REQUESTS,  enable ms unicast grant requests, rw, 1
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to  make master to slave unicast grant requests. This is on by default.
				If this is on and the addressing mode is not multicastOnly then this will enable grant requests to
				be made.



	+ PTP_PORT_SLAVE_PARAMS_SM_ACCEPT_MULTICAST_TIMING_MESSAGES,  accept sm multicast timing messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to accept slave to master multicast timing messages.
				When there are no active unicast grants and this flag is true then it means the timing
				situation is good. Thus the state of the visible master can be set to valid - meaning it can be used as
				a master.



	+ PTP_PORT_SLAVE_PARAMS_SM_ENABLE_UNICAST_GRANT_REQUESTS,  enable sm unicast grant requests, rw, 1
	Bits[31:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to  make slave to master unicast grant requests. This is on by default
				If this is on and the addressing mode is not multicastOnly then this will enable grant requests to
				be made.



	+ PTP_PORT_SLAVE_PARAMS_MASTER_PACKET_INTERFACE_SPEED,  master packet interface speed, rw, 0
	Bits[31:0] = speed in bits per second
				Notes: 	Sets the master packet interface speed in bits per second.

	+ PTP_PORT_SLAVE_PARAMS_P_DELAY_RESPONSE_ENABLE, enable path delay response messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: This can only be enabled when path delay requests have been disabled.

	+ PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_ENABLE,  enable enhanced boundary clock, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the enhanced boundary clock.


	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_USE_GCE,  enhanced boundary clock use gce, rw, 0
	Bits[31:3] = reserved
	Bits[2:0] = values from below
				bcGceNormal = 0
				bcSlave_UseZeroedGce = 1,
				bcMaster_SendGceOnly = 1,
				bcSlave_UseExternalGce = 2,
				bcMaster_SendSceOnly = bcSlave_UseExternalGce = 2,
				bcSlaveUseGceMax = bcSlave_UseExternalGce = 2,
				bcMaster_SendZeroedGceOnly = 3
				Notes: 	Defines how GrandClockError (GCE) should be used.

	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_EXTERNAL_GCE, enhanced boundary clock external gce, rw, 0
	Bits[31:0] = value


	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_INTERNAL_GCE, enhanced boundary clock internal gce, ro, 0
	Bits[31:0] = value
				Notes: The internal Grand Clock Error


	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_STAGE_ERROR,  enhanced boundary clock stage error, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = value
				Notes: Defines the internal SCE (StageClockError).


	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_RXRATE,  enhanced boundary clock rx rate, ro, 0
	Bits[31:0] = values from 0
				Notes: 	Defines the enhanced boundary clock message receiving rate.
				The number of message per second equals to (1/2**RxRate).
				This parameter is only applicable to boundary clock slave side.


	- PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_NUM_TLV_RECEIVED,  enhanced boundary clock tlv received, rw, 0
	Bits[31:0] = values from 0
				Notes: 	Defines the number of enhanced boundary clock TLV frames received since last reset.
				This parameter is mainly used for reading out the TLV frame number from the internal counter.
				'0' is the only allowed value to be written to this parameter, which effectively resets the counter.

	+ PTP_PORT_SLAVE_PARAMS_PRS_FREQ_TRACEABILITY_CLOCK_STRATUM_VALUE,  primary reference source clock stratum value, rw, 6
	Bits[31:8] = reserved
	Bits[7:0] = Clock stratum level
				Notes: This value will be used when comparing the clock class on setting the Freq Traceable flag in ptp messages.
				The default value is clock stratum level primaryReference (=6)

	+ PTP_PORT_SLAVE_PARAMS_NETWORK_TRAFFIC_PROFILE, network traffic load profile, rw, 0
	Bits[31:2] = reserved
	Bits[1:0] = values from below:
				normalLoadTraffic = 0,
				heavyLoadTraffic = 1,

	+ PTP_PORT_SLAVE_PARAMS_FREQ_TRACEABILITY_OVERRIDE_VALUE, override frequency traceable flag , rw, 0
	Bits[31:2] = reserved
	Bits[1:1] =  if '1' then use the override the frequency traceable flag in ptp messages with the value in bit0.
	Bits[0:0] =  if '1' then frequency traceable flag is 1
				 if '0' then frequency traceable flag is 0


	+ PTP_PORT_SLAVE_PARAMS_ANNOUNCE_RECEIPT_TIMEOUT, announce receipt timeout , rw, 3
	Bits[31:4] = reserved
	Bits[3:0] =  number of mean announce periods before timeout occurs (value between 2 and 10 for SMPTE)
				 eg the timeout will be value*mean announce time

*/
typedef enum
{
	PTP_PORT_SLAVE_PARAMS_ADDRESSING_MODE							= 0,
	PTP_PORT_SLAVE_PARAMS_USE_P_DELAY								= 1,
	PTP_PORT_SLAVE_PARAMS_MASTER_PACKET_INTERFACE_SPEED          	= 2,

	PTP_PORT_SLAVE_PARAMS_MS_ACCEPT_MULTICAST_TIMING_MESSAGES		= 3,
	PTP_PORT_SLAVE_PARAMS_MS_ENABLE_UNICAST_GRANT_REQUESTS          = 4,
	PTP_PORT_SLAVE_PARAMS_SM_ACCEPT_MULTICAST_TIMING_MESSAGES       = 5,
	PTP_PORT_SLAVE_PARAMS_SM_ENABLE_UNICAST_GRANT_REQUESTS          = 6,

	PTP_PORT_SLAVE_PARAMS_P_DELAY_RESPONSE_ENABLE					= 10,

	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_ENABLE					= 16,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_USE_GCE                   = 19,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_EXTERNAL_GCE              = 20,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_INTERNAL_GCE              = 21,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_STAGE_ERROR               = 22,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_RXRATE                    = 23,
	PTP_PORT_SLAVE_PARAMS_EBOUNDARY_CLOCK_NUM_TLV_RECEIVED          = 24,

	PTP_PORT_SLAVE_PARAMS_ANNOUNCE_GRANT_REQUEST_THRESHOLD			= 64,
	PTP_PORT_SLAVE_PARAMS_SYNC_GRANT_REQUEST_THRESHOLD				= 65,
	PTP_PORT_SLAVE_PARAMS_DELAY_GRANT_REQUEST_THRESHOLD				= 66,
	PTP_PORT_SLAVE_PARAMS_ANNOUNCE_GRANT_REPEAT_PERIOD				= 67,
	PTP_PORT_SLAVE_PARAMS_SYNC_GRANT_REQUEST_REPEAT_PERIOD			= 68,
	PTP_PORT_SLAVE_PARAMS_DELAY_GRANT_REQUEST_REPEAT_PERIOD			= 69,

	PTP_PORT_SLAVE_PARAMS_BE_SLAVE_EVEN_WHEN_MASTER_TIME_NOT_USED	= 70,
	PTP_PORT_SLAVE_PARAMS_HOLDOFF_TIMER								= 71,
	PTP_PORT_SLAVE_PARAMS_PRS_FREQ_TRACEABILITY_CLOCK_STRATUM_VALUE	= 72,

	PTP_PORT_SLAVE_PARAMS_NETWORK_TRAFFIC_PROFILE					= 73,
	PTP_PORT_SLAVE_PARAMS_FREQ_TRACEABILITY_OVERRIDE_VALUE			= 74,
	PTP_PORT_SLAVE_PARAMS_ANNOUNCE_RECEIPT_TIMEOUT					= 75,


	PTP_PORT_SLAVE_PARAMS_SUBBLOCK_END
}mmApiPtpPortSlaveSubBlockParams;



//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_SEND_USER_DATA
/*
    + PTP_PORT_SLAVE_SEND_USER_DATA_TIMEOUT, the length of time the data message is sent after which it times out, rw, 10
	  The message is sent at a rate of 4Hz until this timeout or an acknowledge is received.
	  Default and min value is 2s, max value is 10s
      Bits[31:8] = Reserved
      Bits[7:0] = time in secs

	+ PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH, Receivers Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until the network interface on the physical port is configured
				In these cases it will calculate the value depending on the ptp port configuration's protocol.


	+ PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS1, Receiver Transmission protocol address bytes 0..3, rw, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS2, Receiver Transmission protocol address bytes 4..7, rw, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS3, Receiver Transmission protocol address bytes 8..11, rw, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS4, Receiver Transmission protocol address bytes 12..15, rw, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_SEND_USER_DATA_ENABLE, enable this system, rw, 0
	Bits[31:1] = Reserved
	Bits[0:0] = '1' will enable the system. This will start the timing of the system but no messages will be sent until the
				  data is ready to be sent
				'0' disable the system.

	+ PTP_PORT_SLAVE_SEND_USER_DATA_SEND, send the data, rw, 0
	Note that this will send the data to the first configured ptp port on the same domain at the receiver end.
	Bits[31:1] = Reserved
	Bits[0:0] = '1' - if there is data to send then this will start sending the data in a signalling message at a rate of 4Hz.
				'0' - The system will automatically clear this bit when the data has been sent.

	+ PTP_PORT_SLAVE_SEND_USER_CONTROL_REGISTER, states whether sending was ok or failed, rw, 0
	Bits[31:2] = Reserved
	Bits[1:0] =  If first bit is 1 then it was sent ok
				 If second bit is 1 then the send failed


	+ PTP_PORT_SLAVE_SEND_USER_DATA_FAIL, sending the data failed, rw, 0
	Bits[31:1] = Reserved
	Bits[0:0] = '0' - not set
				'1' - sending the data failed

	+ PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA_LENGTH, length of data to send in words, rw, 0
	Bits[31:16] = Reserved
	Bits[15:0] = Length of data. Maximum size is 64 words
	This length is large enough to take gps ephemeris data

	+ PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA1, first 4 bytes of data to send, rw, 0
	Bits[31:0] = data
	The data words must all be set at the same time. Note that the data up to the last value
	data word is contiguous.

	+ PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA64, last possible 4 bytes of data to send, rw, 0
	Bits[31:0] = data
	The data words must all be set at the same time. Note that the data up to the last value
	data word is contiguous.
*/
typedef enum
{
	PTP_PORT_SLAVE_SEND_USER_DATA_TIMEOUT = SEND_USER_DATA_TIMEOUT,
	PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH = SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH,
	PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS1 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS1,
	PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS2 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS2,
	PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS3 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS3,
	PTP_PORT_SLAVE_SEND_USER_DATA_RECEIVER_TPA_ADDRESS4 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS4,
	PTP_PORT_SLAVE_SEND_USER_DATA_ENABLE = SEND_USER_DATA_ENABLE,
	PTP_PORT_SLAVE_SEND_USER_DATA_SEND = SEND_USER_DATA_SEND,
	PTP_PORT_SLAVE_SEND_USER_CONTROL_REGISTER = SEND_USER_DATA_SEND_CONTROL_REGISTER,
	PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA_LENGTH = SEND_USER_DATA_SEND_DATA_LENGTH,
	PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA1 = SEND_USER_DATA_SEND_DATA1,
	PTP_PORT_SLAVE_SEND_USER_DATA_SEND_DATA64 = SEND_USER_DATA_SEND_DATA64,
	PTP_PORT_SLAVE_SEND_USER_DATA_END
}mmApiPtpPortSlaveSubBlockSendUserData;


//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_RECEIVE_USER_DATA
/*
     + PTP_PORT_SLAVE_RECEIVE_USER_DATA_TIMEOUT, the length of time the acknowledge message is sent before it times out, rw, 10
	  The message is sent at a rate of 4Hz until this timeout.
	  Default and min value is 2s, maximum value is 10
      Bits[31:8] = Reserved
      Bits[7:0] = timeout

    + PTP_PORT_SLAVE_RECEIVE_USER_DATA_ENABLE, enable the receipt of user data, rw, 0
      Bits[31:1] = Reserved
      Bits[0:0] = '1' enable
				  '0' disable

    + PTP_PORT_SLAVE_RECEIVE_USER_DATA_READY, data is ready to read, rw, 0
      The users should clear this bit after reading the data
      Bits[31:1] = Reserved
      Bits[0:0] = '1' data has been received and can be read
				  '0' no data

    - PTP_PORT_SLAVE_RECEIVE_USER_DATA_FAIL, received data was corrupted, rw, 0
      The users should clear this bit after reading the data
      Bits[31:1] = Reserved
      Bits[0:0] = '1' data has been corrupted
				  '0' no data

	+ PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH, transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until the network interface on the physical port is configured
				In these cases it will calculate the value depending on the ptp port configuration's protocol.


	+ PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1, transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2, transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3, transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4, transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these four transmission protocol words in one go.


    + PTP_PORT_SLAVE_RECEIVE_USER_DATA_LENGTH, length of data received in words, ro, 0
      Bits[31:16] = Reserved
      Bits[15:0] = length of data
      This value can be up to 64 words


    + PTP_PORT_SLAVE_RECEIVE_USER_DATA_DATA1, first 4 bytes of data received, ro, 0
      Bits[31:0] = Four bytes of received data
	  These received data bytes up to the length must be read at the same time.
	  Note that the data up to the 64th word of data received is contiguous

    + PTP_PORT_SLAVE_RECEIVE_USER_DATA_DATA64, last possible 4 bytes of data received, ro, 0
      Bits[31:0] = Four bytes of received data
	  These received data bytes up to the length must be read at the same time.
	  Note that the data up to the 64th word of data received is contiguous
*/
typedef enum
{
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_TIMEOUT = RECEIVE_USER_DATA_TIMEOUT,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_ENABLE = RECEIVE_USER_DATA_ENABLE,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_READY = RECEIVE_USER_DATA_READY,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_FAIL = RECEIVE_USER_DATA_FAIL,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_LENGTH = RECEIVE_USER_DATA_LENGTH,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_DATA1 = RECEIVE_USER_DATA_DATA1,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_DATA64 = RECEIVE_USER_DATA_DATA64,
	PTP_PORT_SLAVE_RECEIVE_USER_DATA_END
}mmApiPtpPortSlaveSubBlockReceiveUserData;





//PARAMETERSDEF:PTP_PORT_SLAVE_SUBBLOCK_RECEIVE_SMPTE_DATA
/*
     + PTP_PORT_SLAVE_RECEIVE_SMPTE_SYS_FRAME_NUMERATOR, Default video frame rate of the slave system as a lowest term rational, ro, 0
	  The data type shall be composed of a pair of unsigned Int32 values coded in big-endian form where the first shall be the numerator
	  and the second shall be the denominator. The denominator shall be the smallest value that represents the frame rate denominator.
      Bits[31:0] = numerator

     + PTP_PORT_SLAVE_RECEIVE_SMPTE_SYS_FRAME_DENOMINATOR, Default video frame rate of the slave system as a lowest term rational, ro, 0
	  The data type shall be composed of a pair of unsigned Int32 values coded in big-endian form where the first shall be the numerator
	  and the second shall be the denominator. The denominator shall be the smallest value that represents the frame rate denominator.
      Bits[31:0] = denominator

     + PTP_PORT_SLAVE_RECEIVE_SMPTE_MASTER_LOCKING_STATUS, Complementary information to clockClass, ro, 0
	  This gives more information regarding the clock class.
      Bits[31:8] = reserved
      Bits[7:0] = 	0: Not in use
					1: Free Run
					2: Cold Locking. In response to a disturbance, the grandmaster is re-locking quickly. In this situation, a rapid phase
						adjustment with a time discontinuity can be expected.
					3: Warm Locking. In response to a disturbance, the grandmaster is re-locking slowly by means of a frequency adjustment,
						with no phase discontinuity. Time continuity is maintained.
					4: Locked (i.e., in normal operation and stable)

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_ADDRESS_FLAGS, Indicates the intended SMPTE ST 12-1 flags, ro, 0
      Bits[31:2] = reserved
      Bits[1:0] =	Bit 0: Drop frame
         	 	 	 	 0: Non-drop-frame
         	 	 	 	 1: Drop-frame
					Bit 1: Color Frame Identification
         	 	 	 	 0: Not in use

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_CURRENT_LOCAL_OFFSET, Offset in seconds of Local Time from grandmaster PTP time, ro, 0
      Bits[31:0] = offset in seconds


      + PTP_PORT_SLAVE_RECEIVE_SMPTE_JUMP_SECONDS, The size of the next discontinuity in seconds of Local Time, ro, 0
      Bits[31:0] = A value of zero indicates that no discontinuity is expected. A positive value indicates that the discontinuity will
      	  	  	  cause the currentLocalOffset to increase.

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JUMP0, the seconds portion of the grandmaster PTP time at the time that the next discontinuity of the currentLocalOffset, ro, 0
      The discontinuity occurs at the start of the second indicated
      Bits[31:0] = this is a 48 bit number where the top 32 bits are stored in this register

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JUMP1, the seconds portion of the grandmaster PTP time at the time that the next discontinuity of the currentLocalOffset, ro, 0
      The discontinuity occurs at the start of the second indicated
	 Bits[15:0] = reserved
	 Bits[31:16] = this is a 48 bit number where the bottom 16 bits are stored in this register


      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JAM0, The value of the seconds portion of the PTP time corresponding to the next scheduled occurrence of the Daily Jam, ro, 0
	  If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
      Bits[31:16] = this is a 48 bit number where the top 32 bits are stored in this register

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JAM1, The value of the seconds portion of the PTP time corresponding to the next scheduled occurrence of the Daily Jam, ro, 0
      If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
	 Bits[15:0] = reserved
	 Bits[31:16] = this is a 48 bit number where the bottom 16 bits are stored in this register


      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_PREV_JAM0, the seconds portion of the PTP time corresponding to the previous occurrence of the Daily Jam, ro, 0
	  If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
      Bits[31:0] = this is a 48 bit number where the top 32 bits are stored in this register

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_PREV_JAM1, the seconds portion of the PTP time corresponding to the previous occurrence of the Daily Jam, ro, 0
	 Bits[15:0] = reserved
	 Bits[31:16] = this is a 48 bit number where the bottom 16 bits are stored in this register



	 + PTP_PORT_SLAVE_RECEIVE_SMPTE_PREV_JAM_LOCAL_OFFSET, The value of currentLocalOffset at the time of the previous Daily Jam event, rw, 0
	 Bits[31:0] = offset
	 If a discontinuity of Local Time occurs at the jam time, this parameter reflects the offset after the discontinuity


      + PTP_PORT_SLAVE_RECEIVE_SMPTE_DAYLIGHT_SAVING, indicates the daylight saving, ro, 0
      Bits[31:3] = reserved
	  Bits[2:0] = 	Bit 0:  Current Daylight Saving
						0: Not in effect
						1: In effect
					Bit 1: Daylight Saving at next discontinuity
						0: Not in effect
						1: In effect
					Bit 2: Daylight Saving at previous Daily Jam event
						0: Not in effect
						1: In effect

      + PTP_PORT_SLAVE_RECEIVE_SMPTE_LEAP_SECOND_JUMP, The reason for the forthcoming discontinuity of currentLocalOffset indicated  by timeOfNextJump, ro, 0
      Bits[31:1] = reserved
	  Bits[0:0] = Bit 0:
              	  	  0: Other than a change in the number of leap seconds  (default)
              	  	  1: A change in number of leap seconds


 	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS_LENGTH, the sender transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until the network interface on the physical port is configured
				In these cases it will calculate the value depending on the ptp port configuration's protocol.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS1, the sender transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS2, the sender transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS3, the sender transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS4, the sender transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_NODEID1, the sender port id node id bytes 0..3, ro, 0x0
	Bits[31:0] = The first set of 4 bytes of the node id
	            /
				Notes: 	The first set of 4 bytes in the the sender port id  node id. /
				Each byte in this uint32 will be a value in the address. eg /
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				/
				It is recommended to set all of these three port id words in one go.


	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_NODEID2,  the sender port id node id bytes 4..7, ro, 0x0
	Bits[31:0] = The second set of 4 bytes of the node id
	/
				Notes: 	The second set of 4 bytes in the the sender port id  node id. /
				Each byte in this uint32 will be a value in the address. eg /
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				/
				It is recommended to set all of these three port id words in one go.

	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_PTPNUM,  the sender port id ptp port number, ro, 0x0
	Bits[31:16] = reserved
	Bits[15:0] = ptp number (starting from 1)
				Notes: 	Ptp port number of the the sender port id
				It is recommended to set all of these three port id words in one go.

	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_DATA_IS_NEW,  whether the data is new (and hence has not been read yet), ro, 0x0
	Bits[31:1] = reserved
	Bits[0:0] = if 0 then this data has been read
				if 1 then this is new data

	+ PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TIMEOUT,  Timeout before alarmTooFewSMTLVs gets raised, rw, 0x5
	Bits[31:3] = reserved
	Bits[2:0] = Timeout before alarmTooFewSMTLVs gets raised. value between 2s and 5s

*/
typedef enum
{
	PTP_PORT_SLAVE_RECEIVE_SMPTE_SYS_FRAME_NUMERATOR = SMPTE_SYS_FRAME_NUMERATOR,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_SYS_FRAME_DENOMINATOR = SMPTE_SYS_FRAME_DENOMINATOR,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_MASTER_LOCKING_STATUS = SMPTE_MASTER_LOCKING_STATUS,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_ADDRESS_FLAGS = SMPTE_TIME_ADDRESS_FLAGS,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_CURRENT_LOCAL_OFFSET = SMPTE_CURRENT_LOCAL_OFFSET,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_JUMP_SECONDS = SMPTE_JUMP_SECONDS,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JUMP0 = SMPTE_TIME_OF_NEXT_JUMP0,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JUMP1 = SMPTE_TIME_OF_NEXT_JUMP1,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JAM0 = SMPTE_TIME_OF_NEXT_JAM0,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_NEXT_JAM1 = SMPTE_TIME_OF_NEXT_JAM1,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_PREV_JAM0 = SMPTE_TIME_OF_PREV_JAM0,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_TIME_OF_PREV_JAM1 = SMPTE_TIME_OF_PREV_JAM1,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_PREV_JAM_LOCAL_OFFSET = SMPTE_PREV_JAM_LOCAL_OFFSET,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_DAYLIGHT_SAVING = SMPTE_DAYLIGHT_SAVING,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_LEAP_SECOND_JUMP = SMPTE_LEAP_SECOND_JUMP,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS_LENGTH = SMPTE_RECEIVE_TPA_ADDRESS_LENGTH,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS1 = SMPTE_RECEIVE_TPA_ADDRESS1,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS2 = SMPTE_RECEIVE_TPA_ADDRESS2,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS3 = SMPTE_RECEIVE_TPA_ADDRESS3,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TPA_ADDRESS4 = SMPTE_RECEIVE_TPA_ADDRESS4,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_NODEID1 = SMPTE_RECEIVE_PORTID_NODEID1,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_NODEID2 = SMPTE_RECEIVE_PORTID_NODEID2,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_PORTID_PTPNUM = SMPTE_RECEIVE_PORTID_PTPNUM,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_DATA_IS_NEW = SMPTE_RECEIVE_DATA_IS_NEW,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_RECEIVE_TIMEOUT = SMPTE_RECEIVE_TIMEOUT,
	PTP_PORT_SLAVE_RECEIVE_SMPTE_DATA_END
}mmApiPtpPortSlaveSubBlockReceiveSmpteData;



//master
//SUBBLOCKSDEF:MMAPI_PTP_PORT3_PARAMS
//SUBBLOCKSDEF:MMAPI_PTP_PORT4_PARAMS
typedef enum
{
	PTP_PORT_MASTER_SUBBLOCK_GENERAL			= 0,   /* General Parameters */
	PTP_PORT_MASTER_SUBBLOCK_PARAMS    			= 1,   /* Generic Parameters */
	PTP_PORT_MASTER_SUBBLOCK_GRANTS_CONFIG		= 2,   /* Grant configuration details */
	PTP_PORT_MASTER_SUBBLOCK_GRANTS_ANNOUNCE	= 3,   /* Details of all the announce grants, up to 1024 of these */
	PTP_PORT_MASTER_SUBBLOCK_GRANTS_SYNC		= 4,   /* Details of all the sync grants, up to 1024 of these */
	PTP_PORT_MASTER_SUBBLOCK_GRANTS_DELAYRESP	= 5,   /* Details of all the delay resp grants, up to 1024 of these */
	PTP_PORT_MASTER_SUBBLOCK_MODE_PARAMS        = 6,   /* Detailed setup of PTP mode */
	PTP_PORT_MASTER_SUBBLOCK_SEND_USER_DATA		= 7,					/* Subsystem to allow user defined data to be sent between devices, eg GPS data*/
	PTP_PORT_MASTER_SUBBLOCK_RECEIVE_USER_DATA	= 8,				/* Subsystem to allow user defined data to be received between devices, eg GPS data*/
	PTP_PORT_MASTER_SUBBLOCK_SEND_SMPTE_DATA	= 9,	/* Send smpte data between devices */
	PTP_PORT_MASTER_SUBBLOCKS_END
} mmApiPtpPortMasterSubBlock;

//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_MODE_PARAMS
/*
   - PTP_PORT_MASTER_MODE_2_T1_MAJOR_MODE, Major mode (general mode) of T1 delivery from remote PHY to ToPSync master, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  major timestamping mode defining how PTP packet T1 timestamp values are delivered to ToPSync.
                0 - Normal    - For sync packets this implies that the remote PHY is one step. Whether the egress sync /
                                is timestamped depends on the register %PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED%./
                                For delay request packets this implies that the packet is timestamped locally on /
                                ingress to TopSync.
                1 - Reserved
                2 - TLV       - Only applies to ingress delay request packets. The PHY has timestamped the ingress /
                                time and appended it to the delay request as a Semtech proprietary TLV.
                3 - Embedded  - Only applies to ingress delay request packets. The PHY has timestamped the ingress /
                                time and embedded the timestamp in the Ethernet packet.
                4 - Reserved
                5 - Correction field adjustment - For sync packets this may or may not mean that the packet is /
                                                  timestamped as it leaves TopSync. For delay request packets, it /
                                                  means that the ingress delay request packet is timestamped locally /
                                                  and the remote PHY has also adjusted the packet's CF as described in /
                                                  UG-TS2 01.
                6-15 - Reserved
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T4_MAJOR_MODE, Major mode (general mode) of T4 delivery from remote PHY to ToPSync master, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  major timestamping mode defining how PTP packet T4 timestamp values are delivered to ToPSync.
                0 - Normal    - For sync packets this implies that the remote PHY is one step. Whether the egress sync /
                                is timestamped depends on the register %PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED%./
                                For delay request packets this implies that the packet is timestamped locally on /
                                ingress to TopSync.
                1 - Reserved
                2 - TLV       - Only applies to ingress delay request packets. The PHY has timestamped the ingress /
                                time and appended it to the delay request as a Semtech proprietary TLV.
                3 - Embedded  - Only applies to ingress delay request packets. The PHY has timestamped the ingress /
                                time and embedded the timestamp in the Ethernet packet.
                4 - Reserved
                5 - Correction field adjustment - For sync packets this may or may not mean that the packet is /
                                                  timestamped as it leaves TopSync. For delay request packets, it /
                                                  means that the ingress delay request packet is timestamped locally /
                                                  and the remote PHY has also adjusted the packet's CF as described in /
                                                  UG-TS2 01.
                6-15 - Reserved
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   - PTP_PORT_MASTER_MODE_2_T1_MINOR_MODE, Detailed description of the general mode of timestamp delivery, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  minor timestamping mode defining the format of the timestamp information delivered back to ToPSync. /
                Register value meanings depend on register setting of %PTP_PORT_MASTER_MODE_2_T1_MAJOR_MODE%. /
                If the major mode (register %PTP_PORT_MASTER_MODE_2_T1_MAJOR_MODE%) is "0 - normal" then this /
                register is ignored. If the major mode is "1 - DRM" then valid configuration is as follows.
                1 - DRMs delivered via Ethernet only. SPI DRMs will be ignored.
                2 - DRMs delivered via SPI. Ethernet DRMs will be ignored.
                3 - DRMS delivered via Ethernet or SPI.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.


   + PTP_PORT_MASTER_MODE_2_T4_MINOR_MODE, Detailed description of the general mode of timestamp delivery, rw, 0
     Bits[31:4] reserved
     Bits[3:0]  minor timestamping mode defining the format of the timestamp information delivered back to ToPSync. /
                Register value meanings depend on register setting of %PTP_PORT_MASTER_MODE_2_T4_MAJOR_MODE%. /
                If the major mode (register %PTP_PORT_MASTER_MODE_2_T4_MAJOR_MODE%) is "0 - normal" then this /
                register is ignored.
                /
                If the major mode is "1 - DRM" then valid configuration is as follows.
                1 - DRMs delivered via Ethernet only. SPI DRMs will be ignored.
                2 - DRMs delivered via SPI. Ethernet DRMs will be ignored.
                3 - DRMS delivered via Ethernet or SPI.
                /
				If the major mode is "2- TLV" then valid configuration is as follows.
				1 - Short TLV format is expected.
				2 - Long TLV format is expected.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.


   - PTP_PORT_MASTER_MODE_2_T1_TIME_FORMAT, Format of t1 timestamps, rw, 1
     Bits[31:4] reserved
     Bits[3:0]  timestamp format. Defines whether timestamp will be nanoseconds only or full seconds and nanoseconds. /
                If the major mode (register %PTP_PORT_MASTER_MODE_2_T1_MAJOR_MODE%) is "0 - normal" then this /
                register is ignored.
                0 - 32-bit nanosecond timestamps expected.
                1 - full 48-bit seconds and 32-bit nanoseconds (IEEE1588) timestamps expected.
                2 - timestamp will contain a nanosecond timestamp with full 32bit value range (external timestamper has /
                free running 32bit timestamper sync'ed to seconds value of epoch)

     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T4_TIME_FORMAT, Format of t4 timestamps, rw, 1
     Bits[31:4] reserved
     Bits[3:0]  timestamp format. Defines whether timestamp will be nanoseconds only or full seconds and nanoseconds. /
                If the major mode (register %PTP_PORT_MASTER_MODE_2_T4_MAJOR_MODE%) is "0 - normal" then this /
                register is ignored.
                0 - 32-bit nanosecond timestamps expected.
                1 - full 48-bit seconds and 32-bit nanoseconds (IEEE1588) timestamps expected.
                2 - timestamp will contain a nanosecond timestamp with full 32bit value range (external timestamper has /
                free running 32bit timestamper sync'ed to seconds value of epoch)

     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED, Whether egress sync packets are timestamped, rw, 1
     Bits[31:1] reserved
     Bits[0:0]  flag defining whether sync PTP packets are timestamped as they leave ToPSync or whether a user defined pattern /
                is written into the origin timestamp field instead.
                1 - the sync PTP packet's origin timestamp field is filled with the packet egress time (default)
                0 - the sync PTP packet's origin timestamp field is filled with a user defined pattern (see registers /
                    %PTP_PORT_MASTER_MODE_2_T1_PATTERN_SECONDS_HI%-%PTP_PORT_MASTER_MODE_2_T1_PATTERN_NANOSECONDS%) /
                    and is not timestamped.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T1_PATTERN_SECONDS_HI,  Egress sync timestamp-pattern seconds bits 47 to 32, rw, 0
     Bits[31:16] = reserved
     Bits[31:0]  = pattern that will be written into seconds bits 47 to 32 of the egress sync origin timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.
     Notes: This pattern is only used when egress sync packets are NOT being timestamped.
     See also: Register %PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED%.

   + PTP_PORT_MASTER_MODE_2_T1_PATTERN_SECONDS_LO, Egress sync timestamp-pattern seconds bits 31 to 0, rw, 0
     Bits[31:0]  = pattern that will be written into seconds bits 31 to 0 of the egress sync origin timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.
     Notes: This pattern is only used when egress sync packets are NOT being timestamped.
     See also: Register %PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED%.

   + PTP_PORT_MASTER_MODE_2_T1_PATTERN_NANOSECONDS, Egress sync timestamp-pattern nanoseconds, rw, 0
     Bits[31:0]  = pattern that will be written into nanoseconds bits 31 to 0 of the egress sync origin timestamp.
     /
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.
     Notes: This pattern is only used when egress sync packets are NOT being timestamped.
     See also: register %PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED%.

   + PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_NANOS, MODE 2: Offset of the T4 32-bit nanoseconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x10
     Bits [31:0] offset of the 32-bit nanosecond portion of the unstructured in-band timestamp value from the start of /
                 the PTP payload. The offset may go past the end of the PTP packet payload as long as the /
                 encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used and /
            %PTP_PORT_MASTER_MODE_2_T4_TIME_FORMAT% is '1'.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_SECS_HI, MODE 2: Offset of bits 47 to 32 of the T4 48-bit seconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x44
     Bits [31:0] offset of the most significant 16 bits of the second portion of the unstructured in-band timestamp /
                 value from the start of the PTP payload. The offset may go past the end of the PTP packet payload as /
                 long as the encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used and /
            %PTP_PORT_MASTER_MODE_2_T4_TIME_FORMAT% is '1'.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.

   + PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_SECS_LO, MODE 2: Offset of bits 31 to 0 of the T4 48-bit seconds timestamp value from the start of the UDP or Ethernet payload, rw, 0x46
     Bits [31:0] offset of the lease significant 32 bits of the second portion of the unstructured in-band timestamp /
                 value from the start of the PTP payload. The offset may go past the end of the PTP packet payload as /
                 long as the encapsulating protocol payload is extended appropriately to contain the timestamp value.
     /
     Notes: Register is only relevant when unstructured in-band timstamp delivery is being used.
	 Notes: This register must only be changed when the PTP port is deconfigured (see register /
	        %PTP_PORT_MASTER_GENERAL_CONFIGURE%). When the port is re-enabled the setting will take effect.


 */
typedef enum
{
	PTP_PORT_MASTER_MODE_SELECT                     = 0,
	PTP_PORT_MASTER_MODE_2_T1_MAJOR_MODE            = 1,
	PTP_PORT_MASTER_MODE_2_T1_MINOR_MODE            = 2,
	PTP_PORT_MASTER_MODE_2_T1_TIME_FORMAT           = 3,
	PTP_PORT_MASTER_MODE_2_T1_IS_TIMESTAMPED        = 4,
	PTP_PORT_MASTER_MODE_2_T1_PATTERN_SECONDS_HI    = 5,
	PTP_PORT_MASTER_MODE_2_T1_PATTERN_SECONDS_LO    = 6,
	PTP_PORT_MASTER_MODE_2_T1_PATTERN_NANOSECONDS   = 7,
	PTP_PORT_MASTER_MODE_2_T4_MAJOR_MODE            = 8,
	PTP_PORT_MASTER_MODE_2_T4_MINOR_MODE            = 9,
	PTP_PORT_MASTER_MODE_2_T4_TIME_FORMAT           = 10,
	PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_SECS_HI = 11,
	PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_SECS_LO = 12,
	PTP_PORT_MASTER_MODE_2_T4_TIME_EMBED_LOC_NANOS   = 13,

	PTP_PORT_MASTER_MODE_END
} mmApiPtpPortMasterSubBlockModeParams;

//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_GENERAL
/*
	+ PTP_PORT_MASTER_GENERAL_CONNECTOR, physical port connector, rw, 0
	Bits[31:8]	reserved
	Bits[7:0] 	connector. The physical port that this ptp port is connected to, starting from 0.
			Notes: It is recommended that the first five words, connector, protocol, version, domain and configure are set at the same time.

	+ PTP_PORT_MASTER_GENERAL_PROTOCOL, ptp port protocol, rw, 0
	Bits[31:2]	reserved
	Bits[1:0]	protocol. 	The protocol used in the ptp port.
			0 udp4,
			1 ethernet,
			2 udp6

	+ PTP_PORT_MASTER_GENERAL_VERSION, ptp port version, ro, 2
	Bits[31:3]	reserved
	Bits[2:0]	version
			1 version1,
			2 version2

	+ PTP_PORT_MASTER_GENERAL_CONFIGURE, configure ptp port, rw, 0
	Bits[31:1]	reserved
	Bits[0:0]	configure
			0 deconfigure,
			1 configure
			Notes: Configures the ptp port with the settings physical port connector, ptp port protocol, ptp port version and domain.
			This will also bring the ptp port up to its initial values and start up the network interface


	+ PTP_PORT_MASTER_GENERAL_ENABLE, enable ptp port, rw, 0
	Bits[31:1]	reserved
	Bits[0:0]	enable
			0 disable,
			1 enable
			Notes: Enable the ptp port for use. If enabled it will allow the ptp port to begin moving through its states

	+ PTP_PORT_MASTER_GENERAL_TIMEBASE, Timebase used for port master operations, rw, 4
	Bits[31:3] = Reserved
	Bits[2:0] = Source
		Valid bit (decimal) values:
		010 (2) PTP PLL 1
		011 (3) PTP PLL 2
		100 (4) NODE PLL 1
		101 (5) NODE PLL 2

	+ PTP_PORT_MASTER_GENERAL_VIRTUAL_INTERFACE_NUMBER, virtual interface number, rw, 0
	Bits[31:3]  reserved
	Bits[2:0]   virtual interface number

	+ PTP_PORT_MASTER_GENERAL_MHOME_INDEX, multi home index of address on interface, rw, 0
	Bits[31:4] reserved
	Bits[3:0]  multi home index of address on interface

	+ PTP_PORT_MASTER_GENERAL_DOMAIN, ptp port domain, rw, 0
	Bits[31:8]	reserved
	Bits[7:0]	domain (starting from 0)
			Notes: 	Set the domain number of the ptp port. This can be set at the same time as configuring the ptp port.
			It can also be set by itself when a ptp port has already been configured.
			It will only be able to communicate with other ptp ports on the same domain.


	+ PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_MULTI_DES_PERIOD, desired multicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period log base 2 as an sint8 (value can go from 6 to -4)
			Notes: 	The desired multicast log period of the announce message.
			The desired log period is the smallest (and hence fastest rate) that is desired.
			The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	- PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_REQ_PERIOD, required unicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8 (value can go from 6 to -4)
			Notes: 	required unicast log period of the announce message.
			The desired log period is the smallest (and hence fastest rate) that is desired.
			The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	- PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_REQ_DURATION, required unicast announce duration, rw, 250
	Bits[31:0]	duration
			Notes: 	Set duration of the required unicast grant duration of the announce message.


	- PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_DES_PERIOD, desired unicast announce log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2  as an sint8 (value can go from 6 to -4)
			Notes: Set desired unicast log period of the announce message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	+ PTP_PORT_MASTER_GENERAL_SYNC_MSG_MULTI_DES_PERIOD, desired multicast sync log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2  as an sint8 (value can go from 4 to -7)
			Notes: 	Set desired multicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	- PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_REQ_PERIOD, required unicast sync log period, rw, -3
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2  as an sint8 (value can go from 4 to -7)
			Notes: 	Set required unicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			It is recommended to set this and the next two parameters at the same time.


	- PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_REQ_DURATION, required unicast sync duration, rw, 250
	Bits[31:0]	duration
			Notes: 	Set duration of the required unicast grant duration of the sync message.


	- PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_DES_PERIOD, desired unicast sync log period, rw, -5
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2  as an sint8 (value can go from 4 to -7)
			Notes: 	Set desired unicast log period of the sync message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.

	+ PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_MULTI_DES_PERIOD, desired multicast delay resp log period, rw, 1
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8  (value can go from 4 to -7)
			Notes: 	Set desired multicast log period of the delay resp message. The desired log period is the smallest
			(and hence fastest rate) that is desired. The required log period is the largest (and hence slowest rate) that is
			satisfactory to the ptp port.


	- PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_REQ_PERIOD, required unicast delay resp log period, rw, -3
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8  (value can go from 4 to -7)
			Notes: 	Set required unicast log period of the delay resp message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.
			It is recommended to set this and the next two parameters at the same time.


	- PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_REQ_DURATION, required unicast delay resp duration, rw, 250
	Bits[31:0]	duration
			Notes :	Set duration of the required delay resp grant duration of the sync message.


	- PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_DES_PERIOD, desired unicast delay resp log period, rw, -5
	Bits[31:8]	reserved
	Bits[7:0]	log period  - log base 2 as an sint8  (value can go from 4 to -7)
			Notes: Set desired unicast log period of the delay resp message. The desired log period is the smallest (and hence fastest rate)
			that is desired. The required log period is the largest (and hence slowest rate) that is satisfactory to the ptp port.


	+ PTP_PORT_MASTER_GENERAL_NODE_ID_1, The node id of the ptp port bytes 0 to 3, rw, 0x0
	Bits[31:0]	The first set of 4 bytes of the node id
			Notes: 	The first set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
			It is recommended to set all of these two node id words in one go.

	+ PTP_PORT_MASTER_GENERAL_NODE_ID_2, The node id of the ptp port bytes 4 to 7, rw, 0x0
	Bits[31:0]	The second set of 4 bytes of the node id
			Notes: 	The second set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
			It is recommended to set all of these two node id words in one go.


	+ PTP_PORT_MASTER_GENERAL_DEFAULT_NODE_ID_1, The default node id of the ptp port, ro, 0x0
	Bits[31:0]	The first set of 4 bytes of the node id
			Notes: The first set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
			It is recommended to get all of these two node id words in one go.


	+ PTP_PORT_MASTER_GENERAL_DEFAULT_NODE_ID_2, The default id of the ptp port, ro, 0x0
	Bits[31:0]	The second set of 4 bytes of the node id
			Notes: 	The second set of 4 bytes in the node id
			Each byte in this uint32 will be a value in the address. eg
			In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
			It is recommended to get all of these two node id words in one go.


	+ PTP_PORT_MASTER_GENERAL_PTP_STATE, The state of the ptp port, ro, 0x0
	Bits[31:4]	reserved
	Bits[3:0]	state of the ptp port
			0 = portFaulty,
			1 = portDisabled,
			2 = portListening,
			3 = portPreMaster,
			4 = portMaster,
			5 = portPassive,
			6 = portUncalibrated,
			7 = portSlave


	+ PTP_PORT_MASTER_GENERAL_BMCA_MASK, best master clock algorithm mask, rw, 0xBF
	Bits[31:8] = reserved
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

	+ PTP_PORT_MASTER_GENERAL_BETTER_MASTER_AVAILABLE, better master available flag, ro, 0x0
	Bits[31:1] = reserved
	Bits[0:0] = flag
				0 = true,
				1 = false
				Notes: 	This indicates if there is a better master available than the currently selected master.

	+ PTP_PORT_MASTER_GENERAL_MULTICAST_TX_ENABLE_ANNOUNCE, enable/disable sending multicast announce messages, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = enable sending multicast announce messages
				0 = disable sending multicast announce messages
				Notes: ToPSync will not sent multicast announce messages when the PTP port address mode is unicastOnly.

	+ PTP_PORT_MASTER_GENERAL_MULTICAST_TX_ENABLE_SYNC, enable/disable sending multicast sync messages, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = enable sending multicast sync messages
				0 = disable sending multicast sync messages
				Notes: ToPSync will not send multicast sync messages when the PTP port addressing mode is unicastOnly.

	+ PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_ANNOUNCE, accept announce unicast grant requests, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = accept announce unicast grant requests
				0 = drop announce unicast grant requests
				Notes: ToPSync will drop unicast grant requests when the PTP port address mode is multicastOnly.

	+ PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_SYNC, accept sync unicast grant requests, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = accept sync unicast grant requests
				0 = drop sync unicast grant requests
				Notes: ToPSync will drop unicast grant requests when the PTP port address mode is multicastOnly.

	+ PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_DELAY_RESPONSE, accept delay response unicast grant requests, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = accept delay response unicast grant requests
				0 = drop delay response unicast grant requests
				Notes: ToPSync will drop unicast grant requests when the PTP port address mode is multicastOnly.

*/
typedef enum
{
	PTP_PORT_MASTER_GENERAL_CONNECTOR             = 0,
	PTP_PORT_MASTER_GENERAL_PROTOCOL              = 1,
	PTP_PORT_MASTER_GENERAL_VERSION               = 2,
	PTP_PORT_MASTER_GENERAL_DOMAIN                = 3,
	PTP_PORT_MASTER_GENERAL_CONFIGURE             = 4, /* Note: will use 4 prev params if configured */
	PTP_PORT_MASTER_GENERAL_ENABLE                = 5, /* Enable / disable port */
	PTP_PORT_MASTER_GENERAL_TIMEBASE              = 6,
	PTP_PORT_MASTER_GENERAL_VIRTUAL_INTERFACE_NUMBER = 7,
	PTP_PORT_MASTER_GENERAL_MHOME_INDEX			  = 8,

	PTP_PORT_MASTER_GENERAL_NODE_ID_1            = 16, /* Note: two consecutive params */
	PTP_PORT_MASTER_GENERAL_NODE_ID_2	         = 17,

	PTP_PORT_MASTER_GENERAL_DEFAULT_NODE_ID_1    = 18, /* Note: two consecutive params */
	PTP_PORT_MASTER_GENERAL_DEFAULT_NODE_ID_2	 = 19,

	PTP_PORT_MASTER_GENERAL_PTP_STATE             = 20,
	PTP_PORT_MASTER_GENERAL_BMCA_MASK             	= 21,
	PTP_PORT_MASTER_GENERAL_BETTER_MASTER_AVAILABLE = 22,

	PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_MULTI_DES_PERIOD   = 32,
	PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_REQ_PERIOD   	= 33, /*  Note: best to set next two consecutive params in one hit */
	PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_REQ_DURATION  	= 34,
	PTP_PORT_MASTER_GENERAL_ANNOUNCE_MSG_UNI_DES_PERIOD   	= 35,

	PTP_PORT_MASTER_GENERAL_SYNC_MSG_MULTI_DES_PERIOD	= 36,
	PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_REQ_PERIOD   	= 37, /* Note: best to set next two consecutive params in one hit */
	PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_REQ_DURATION  	= 38,
	PTP_PORT_MASTER_GENERAL_SYNC_MSG_UNI_DES_PERIOD   	= 39,

	PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_MULTI_DES_PERIOD  = 40,
	PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_REQ_PERIOD   	= 41, /*  Note: best to set next two consecutive params in one hit */
	PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_REQ_DURATION  = 42,
	PTP_PORT_MASTER_GENERAL_DELAYRESP_MSG_UNI_DES_PERIOD   	= 43,

	PTP_PORT_MASTER_GENERAL_MULTICAST_TX_ENABLE_ANNOUNCE   				= 80,
	PTP_PORT_MASTER_GENERAL_MULTICAST_TX_ENABLE_SYNC					= 81,

	PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_ANNOUNCE 		= 85,
	PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_SYNC 			= 86,
	PTP_PORT_MASTER_GENERAL_UNICAST_GRANT_REQUEST_ACCEPT_DELAY_RESPONSE	= 87,


	PTP_PORT_MASTER_GENERAL_GENERAL_END

}mmApiPtpPortMasterSubBlockGeneralParams;


/* todo: Check with Adrian how he intends to consolidate enums
 * since PtpPort.h already takes care of the following
 */
//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_PARAMS
/*
	+ PTP_PORT_MASTER_PARAMS_TWOSTEP_OPERATION, two step operation, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable

	+ PTP_PORT_MASTER_PARAMS_ADDRESSING_MODE, addressing mode, rw, 0
	Bits[31:2] = reserved
	Bits[1:0] = addressing mode
				asAppropriate = 0,
				unicastOnly = 1,
				multicastOnly = 2
				Notes: 	Sets the addressing mode of the ptp port.


	+ PTP_PORT_MASTER_PARAMS_USE_P_DELAY, enable path delay messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				This enables sending of path delay request messages.


	+ PTP_PORT_MASTER_PARAMS_NUMBER_OF_ALTERNATE_MASTERS, number of alternate masters, rw, 0
	Sets the number of alternate masters. If greater than zero then the number of masters operational on this domain
	will be this value + 1.
	Bits[31:8] = reserved
	Bits[7:0] = number (from 0)

	- PTP_PORT_MASTER_PARAMS_CLOCKID, clock id, rw, 0
	Bits[31:3] = reserved
	Bits[2:0] = values taken from below
				clockTSA = 0,
				clockTSB = 1,
				networkTSA = 2,
				networkTSB = 3,
				networkTSC = 4,
				networkTSD = 5.
				Notes: 		Sets the clock id of the ptp port.
				Looks like this is superceded by PTP_PORT_MASTER_GENERAL_TIMEBASE so remnove.

	- PTP_PORT_MASTER_PARAMS_MS_ACCEPT_MULTICAST_TIMING_MESSAGES,  accept ms multicast timing messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to accept master to slave multicast timing messages.
				When there are no active unicast grants and this flag is true then it means the timing
				situation is good. Thus the state of the visible master can be set to valid - meaning it can be used as
				a master.
				This is for slave port only.



	- PTP_PORT_MASTER_PARAMS_MS_ENABLE_UNICAST_GRANT_REQUESTS,  enable ms unicast grant requests, rw, 1
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to  make master to slave unicast grant requests. This is on by default.
				If this is on and the addressing mode is not multicastOnly then this will enable grant requests to
				be made.
				This is for slave port only.


	- PTP_PORT_MASTER_PARAMS_SM_ACCEPT_MULTICAST_TIMING_MESSAGES,  accept sm multicast timing messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to accept slave to master multicast timing messages.
				When there are no active unicast grants and this flag is true then it means the timing
				situation is good. Thus the state of the visible master can be set to valid - meaning it can be used as
				a master.
				This is for slave port only.



	- PTP_PORT_MASTER_PARAMS_SM_ENABLE_UNICAST_GRANT_REQUESTS,  enable sm unicast grant requests, rw, 1
	Bits[31:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the port to  make slave to master unicast grant requests. This is on by default
				If this is on and the addressing mode is not multicastOnly then this will enable grant requests to
				be made.
				This is for slave port only.


	- PTP_PORT_MASTER_PARAMS_MASTER_PACKET_INTERFACE_SPEED,  master packet interface speed, rw, 0
	Bits[31:0] = speed in bits per second
				Notes: 	Sets the master packet interface speed in bits per second.
				This is only used on a slave ptp port hence it has been removed

	+ PTP_PORT_MASTER_PARAMS_RENEWAL_FLAG,  master renewal flag, rw, 1
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Sets the master renewal flag. If TRUE then this means the master is likely to renew new grant requests


	+ PTP_PORT_MASTER_PARAMS_REFUSAL_FLAG,  master refusal flag, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Sets the master refusal flag. If the master is unable to grant a requested rate then if this flag is set it will
				refuse the grant request rather than offer a lower rate.


	+ PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_TAI_UNKNOWN,  not become master if tai unknown, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	If this is set then the ptp port will only become a master if TAI is known


	+ PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_UTC_UNKNOWN,  not become master if utc unknown, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	If this is set then the ptp port will only become a master if UTC is known


	+ PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_SOURCE_IS_NOT_PRS,  not become master if not prs, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	If this is set then the ptp port will only become a master if the source is a primary reference source

	+ PTP_PORT_MASTER_PARAMS_P_DELAY_RESPONSE_ENABLE, enable path delay response messages, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: This can only be enabled when path delay requests have been disabled.

	+ PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_ENABLE,  enable enhanced boundary clock, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the enhanced boundary clock.


	- PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_TXRATE,  enhanced boundary clock tx rate, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = BcTxRate taken from below values.
				bcTxRateModMin = 0,
				bcTxRateMod1 = 0
				bcTxRateMod2 = 1
				bcTxRateMod4 = 2
				bcTxRateMod8 = 3
				bcTxRateMod16 = 4
				bcTxRateMod32 = 5
				bcTxRateMod64 = 6
				bcTxRateMod128 = 7
				Notes: 	Sets enhanced boundary clock transmission rate. The message transmission rate is
				PacketRequest Message Per Second/2**BcTxRate. This means the smaller the value of BcTxRate,
				the higher the message transmission rate. This parameter is only applicable to boundary clock master side.



	- PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_ENCRYPTION,  enhanced boundary clock encryption, rw, 0
	Bits[31:2] = reserved
	Bits[1:0] = values from below
				bcEncryptionAlg0 = 0
				bcEncryptionAlg1 = 1
				Notes: 	Sets enhanced boundary clock message encryption algorithm. The values are:

	+ PTP_PORT_MASTER_PARAMS_PRS_FREQ_TRACEABILITY_CLOCK_STRATUM_VALUE,  primary reference source clock stratum value, rw, 6
	Bits[31:8] = reserved
	Bits[7:0] = Clock stratum level
				Notes: This value will be used when comparing the clock class on setting the Freq Traceable flag in ptp messages.
				The default value is clock stratum level primaryReference (=6)

	+ PTP_PORT_MASTER_PARAMS_FREQ_TRACEABILITY_OVERRIDE_VALUE, override frequency traceable flag , rw, 0
	Bits[31:2] = reserved
	Bits[1:1] =  if '1' then use the override the frequency traceable flag in ptp messages with the value in bit0.
	Bits[0:0] =  if '1' then frequency traceable flag is 1
				 if '0' then frequency traceable flag is 0

	+ PTP_PORT_MASTER_PARAMS_ALWAYS_RESPOND_TO_UNICAST_DELAYS, always respond to unicast delay requests , rw, 0
	Bits[31:1] = reserved
	Bits[0:0] =  if '1' then unicast delay requests are always responded to with unicast delay response
				 if '0' then the behaviour is as per the ptp port unicast/multicast/asAppropriate setting
				 Notes: Normally a unicast delay response is responded to only if the ptp port is unicast and the grant mechanism is used.
				 A unicast delay request would also be responded to if the Forced Grant Mechanism in the AMT and AST has been configured.
				 This 'always respond to unicast delay request' setting is used for the case where the ptp master is multicast and no grants
				 have been set up and no Forced Grant mechanism has been used.
				 In this mode no checks are made as to the ability of the port to be provide the responses at the rate coming in so this
				 is to be sparingly.



*/
typedef enum
{
	PTP_PORT_MASTER_PARAMS_ADDRESSING_MODE                            = 0,
	PTP_PORT_MASTER_PARAMS_USE_P_DELAY                                = 1,
	PTP_PORT_MASTER_PARAMS_MASTER_PACKET_INTERFACE_SPEED              = 2,

	PTP_PORT_MASTER_PARAMS_MS_ACCEPT_MULTICAST_TIMING_MESSAGES        = 3, /* Generic param is write only! */
	PTP_PORT_MASTER_PARAMS_MS_ENABLE_UNICAST_GRANT_REQUESTS           = 4, /* Generic param is write only */
	PTP_PORT_MASTER_PARAMS_SM_ACCEPT_MULTICAST_TIMING_MESSAGES        = 5, /* Generic param is write only! */
	PTP_PORT_MASTER_PARAMS_SM_ENABLE_UNICAST_GRANT_REQUESTS           = 6, /* Generic param is write only */

	PTP_PORT_MASTER_PARAMS_P_DELAY_RESPONSE_ENABLE					  = 10,

	PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_ENABLE                     = 16,
	PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_TXRATE                     = 17,
	PTP_PORT_MASTER_PARAMS_EBOUNDARY_CLOCK_ENCRYPTION                 = 18,

	PTP_PORT_MASTER_PARAMS_TWOSTEP_OPERATION                          = 96,
	PTP_PORT_MASTER_PARAMS_NUMBER_OF_ALTERNATE_MASTERS                = 97,
	PTP_PORT_MASTER_PARAMS_CLOCKID                                    = 98,
	PTP_PORT_MASTER_PARAMS_RENEWAL_FLAG                               = 99,
	PTP_PORT_MASTER_PARAMS_REFUSAL_FLAG                               = 100,
	PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_TAI_UNKNOWN        = 101,
	PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_UTC_UNKNOWN        = 102,
	PTP_PORT_MASTER_PARAMS_DO_NOT_BECOME_MASTER_IF_SOURCE_IS_NOT_PRS  = 103,
	PTP_PORT_MASTER_PARAMS_PRS_FREQ_TRACEABILITY_CLOCK_STRATUM_VALUE  = 104,
	PTP_PORT_MASTER_PARAMS_FREQ_TRACEABILITY_OVERRIDE_VALUE			  = 105,
	PTP_PORT_MASTER_PARAMS_ALWAYS_RESPOND_TO_UNICAST_DELAYS			  = 106,

	PTP_PORT_MASTER_PARAMS_SUBBLOCK_END
}mmApiPtpPortMasterSubBlockParams;


//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_GRANTS_CONFIG
/*
+ PTP_PORT_MASTER_GRANTS_MAX_SLAVES, max number of slaves, rw, 1024
Bits[31:16]	reserved
Bits[15:0] 	max number.
				Notes: This is the number of slaves to produce grants for, eg with the default values there can be
				up to 10 1024 announce grants, 1024 sync grants and 1024 delay resp grants

+ PTP_PORT_MASTER_GRANTS_MAX_TOTAL_ANNOUNCE_RATE, max total announce rate, rw, 512
Bits[31:0] 	max rate.
				Notes: This is the maximum total announce rate. The summation of all the announce rates on this master cannot
				exceed this value.

+ PTP_PORT_MASTER_GRANTS_MAX_TOTAL_SYNC_RATE, max total sync rate, rw, 8192
Bits[31:0] 	max rate.
				Notes: This is the maximum total sync rate . The summation of all the sync rates on this master cannot
				exceed this value.

+ PTP_PORT_MASTER_GRANTS_MAX_TOTAL_DELAYRESP_RATE, max total delay resp rate, rw, 8192
Bits[31:0] 	max rate.
				Notes: This is the maximum total delay response rate. The summation of all the delay resp rates on this master cannot
				exceed this value.

+ PTP_PORT_MASTER_GRANTS_MIN_ANNOUNCE_LOG_PERIOD, min announce log period, rw, -4
Bits[31:8] 	reserved
Bits[7:0] 	Min log period base 2 as sint8
				Notes: This is the minimum announce log period for a grant.

+ PTP_PORT_MASTER_GRANTS_MIN_SYNC_LOG_PERIOD, min sync log period, rw, -7
Bits[31:8] 	reserved
Bits[7:0] 	Min log period base 2 as sint8
				Notes: This is the minimum sync log period for a grant.

+ PTP_PORT_MASTER_GRANTS_MIN_DELAYRESP_LOG_PERIOD, min delay response log period, rw, -7
Bits[31:8] 	reserved
Bits[7:0] 	Min log period base 2 as sint8
				Notes: This is the minimum delay response log period for a grant.

+ PTP_PORT_MASTER_GRANTS_MAX_ANNOUNCE_DURATION, max announce duration, rw, 300
Bits[31:0] 	max duration.
				Notes: This is the maximum duration of an announce grant.

+ PTP_PORT_MASTER_GRANTS_MAX_SYNC_DURATION, max sync duration, rw, 300
Bits[31:0] 	max duration.
				Notes: This is the maximum duration of a sync grant.

+ PTP_PORT_MASTER_GRANTS_MAX_DELAYRESP_DURATION, max delay response duration, rw, 300
Bits[31:0] 	max duration.
				Notes: This is the maximum duration of a delay response grant.

+ PTP_PORT_MASTER_GRANTS_ANNOUNCE_GRANTS_ISSUED, number of announce grants issued, ro, 0
Bits[31:0] 	number.
				Notes: This is the number of announce grants that are currently issued

+ PTP_PORT_MASTER_GRANTS_SYNC_GRANTS_ISSUED, number of sync grants issued, ro, 0
Bits[31:0] 	number.
				Notes: This is the number of sync grants that are currently issued

+ PTP_PORT_MASTER_GRANTS_DELAYRESP_GRANTS_ISSUED, number of delay resp grants issued, ro, 0
Bits[31:0] 	number.
				Notes: This is the number of delay response grants that are currently issued

+ PTP_PORT_MASTER_GRANTS_ANNOUNCE_CHG_COUNTER, announce grant change counter, ro, 0
Bits[31:0] 	number.
				Notes: This value increments every time an announce grant is renewed or created. This should be called
				periodically and if it has changed then the user can obtain new information on the grants issued.

+ PTP_PORT_MASTER_GRANTS_SYNC_CHG_COUNTER, sync grant change counter, ro, 0
Bits[31:0] 	number.
				Notes: This value increments every time a sync grant is renewed or created. This should be called
				periodically and if it has changed then the user can obtain new information on the grants issued.

+ PTP_PORT_MASTER_GRANTS_DELAYRESP_CHG_COUNTER, delay response grant change counter, ro, 0
Bits[31:0] 	number.
				Notes: This value increments every time a delay response grant is renewed or created. This should be called
				periodically and if it has changed then the user can obtain new information on the grants issued.

*/
typedef enum
{
	PTP_PORT_MASTER_GRANTS_MAX_SLAVES                      = 0,
	PTP_PORT_MASTER_GRANTS_MAX_TOTAL_ANNOUNCE_RATE         = 1,
	PTP_PORT_MASTER_GRANTS_MAX_TOTAL_SYNC_RATE		       = 2,
	PTP_PORT_MASTER_GRANTS_MAX_TOTAL_DELAYRESP_RATE        = 3,
	PTP_PORT_MASTER_GRANTS_MIN_ANNOUNCE_LOG_PERIOD		   = 4,
	PTP_PORT_MASTER_GRANTS_MIN_SYNC_LOG_PERIOD		       = 5,
	PTP_PORT_MASTER_GRANTS_MIN_DELAYRESP_LOG_PERIOD        = 6,
	PTP_PORT_MASTER_GRANTS_MAX_ANNOUNCE_DURATION		   = 7,
	PTP_PORT_MASTER_GRANTS_MAX_SYNC_DURATION			   = 8,
	PTP_PORT_MASTER_GRANTS_MAX_DELAYRESP_DURATION		   = 9,
	PTP_PORT_MASTER_GRANTS_ANNOUNCE_GRANTS_ISSUED		   = 10,
	PTP_PORT_MASTER_GRANTS_SYNC_GRANTS_ISSUED		   	   = 11,
	PTP_PORT_MASTER_GRANTS_DELAYRESP_GRANTS_ISSUED		   = 12,
	PTP_PORT_MASTER_GRANTS_ANNOUNCE_CHG_COUNTER		   	   = 13,
	PTP_PORT_MASTER_GRANTS_SYNC_CHG_COUNTER		   	       = 14,
	PTP_PORT_MASTER_GRANTS_DELAYRESP_CHG_COUNTER		   = 15,
	PTP_PORT_MASTER_GRANTS_CONFIG_SUBBLOCK_END
}mmApiPtpPortMasterSubBlockGrantsConfig;


//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_GRANTS_ANNOUNCE
/*
	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_PROTOCOL, grant #n# transmission protocol, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The grantee's transmission protocol.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_ADDRESS_LENGTH, grant #n# transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the slave's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024



	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_ADDRESS_1, grant #n# transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_ADDRESS_2, grant #n# transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_ADDRESS_3, grant #n# transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_TPA_ADDRESS_4, grant #n# transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024

	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_LOG_PERIOD, grant #n# announce log period, ro, 0
	Bits[31:8] = Reserved
	Bits[7:0] = log period base 2 as a signed int
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024

	+ PTP_PORT_MASTER_ANNOUNCE_GRANT#n#_DURATION, grant #n# announce duration, ro, 0
	Bits[31:0] = announce grant duration in secs
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024

*/
typedef enum
{
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_PROTOCOL			= 0,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_ADDRESS_LENGTH		= 1,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_ADDRESS_1			= 2,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_ADDRESS_2			= 3,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_ADDRESS_3			= 4,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_TPA_ADDRESS_4			= 5,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_LOG_PERIOD				= 6,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1_DURATION				= 7,

	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_PROTOCOL			= 10,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_ADDRESS_LENGTH		= 11,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_ADDRESS_1			= 12,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_ADDRESS_2			= 13,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_ADDRESS_3			= 14,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_TPA_ADDRESS_4			= 15,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_LOG_PERIOD				= 16,
	PTP_PORT_MASTER_ANNOUNCE_GRANT2_DURATION				= 17,

	//PTP_PORT_MASTER_ANNOUNCE_GRANT3_TPA_PROTOCOL			= 20,

	//etc until grant 1024
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_PROTOCOL			= 10230,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_ADDRESS_LENGTH	= 10231,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_ADDRESS_1		= 10232,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_ADDRESS_2		= 10233,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_ADDRESS_3		= 10234,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_TPA_ADDRESS_4		= 10235,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_LOG_PERIOD			= 10236,
	PTP_PORT_MASTER_ANNOUNCE_GRANT1024_DURATION				= 10237,

	PTP_PORT_MASTER_ANNOUNCE_GRANTS_SUBBLOCK_END			= 10238
}mmApiPtpPortMasterSubBlockAnnounceGrants;


//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_GRANTS_SYNC
/*
	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_PROTOCOL, grant #n# transmission protocol, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The grantee's transmission protocol.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_ADDRESS_LENGTH, grant #n# transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the slave's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024



	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_ADDRESS_1, grant #n# transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_ADDRESS_2, grant #n# transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_ADDRESS_3, grant #n# transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_SYNC_GRANT#n#_TPA_ADDRESS_4, grant #n# transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024

	+ PTP_PORT_MASTER_SYNC_GRANT#n#_LOG_PERIOD, grant #n# sync log period, ro, 0
	Bits[31:8] = Reserved
	Bits[7:0] = log period base 2 as a signed int
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_SYNC_GRANT#n#_DURATION, grant #n# sync duration, ro, 0
	Bits[31:0] = sync grant duration in secs
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024

*/
typedef enum
{
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_PROTOCOL			= 0,
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_ADDRESS_LENGTH		= 1,
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_ADDRESS_1			= 2,
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_ADDRESS_2			= 3,
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_ADDRESS_3			= 4,
	PTP_PORT_MASTER_SYNC_GRANT1_TPA_ADDRESS_4			= 5,
	PTP_PORT_MASTER_SYNC_GRANT1_LOG_PERIOD				= 6,
	PTP_PORT_MASTER_SYNC_GRANT1_DURATION				= 7,

	PTP_PORT_MASTER_SYNC_GRANT2_TPA_PROTOCOL			= 10,
	PTP_PORT_MASTER_SYNC_GRANT2_TPA_ADDRESS_LENGTH		= 11,
	PTP_PORT_MASTER_SYNC_GRANT2_TPA_ADDRESS_1			= 12,
	PTP_PORT_MASTER_SYNC_GRANT2_TPA_ADDRESS_2			= 13,
	PTP_PORT_MASTER_SYNC_GRANT2_TPA_ADDRESS_3			= 14,
	PTP_PORT_MASTER_SYNC_GRANT2_TPA_ADDRESS_4			= 15,
	PTP_PORT_MASTER_SYNC_GRANT2_LOG_PERIOD				= 16,
	PTP_PORT_MASTER_SYNC_GRANT2_DURATION				= 17,

	//PTP_PORT_MASTER_SYNC_GRANT3_TPA_PROTOCOL			= 20,

	//etc for all 1024 grants
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_PROTOCOL			= 10230,
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_ADDRESS_LENGTH	= 10231,
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_ADDRESS_1		= 10232,
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_ADDRESS_2		= 10233,
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_ADDRESS_3		= 10234,
	PTP_PORT_MASTER_SYNC_GRANT1024_TPA_ADDRESS_4		= 10235,
	PTP_PORT_MASTER_SYNC_GRANT1024_LOG_PERIOD			= 10236,
	PTP_PORT_MASTER_SYNC_GRANT1024_DURATION				= 10237,

	PTP_PORT_MASTER_SYNC_GRANTS_SUBBLOCK_END			= 10238
}mmApiPtpPortMasterSubBlockSyncGrants;


//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_GRANTS_DELAYRESP
/*
	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_PROTOCOL, grant #n# transmission protocol, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The grantee's transmission protocol.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_ADDRESS_LENGTH, grant #n# transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the slave's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024



	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_ADDRESS_1, grant #n# transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_ADDRESS_2, grant #n# transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_ADDRESS_3, grant #n# transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_TPA_ADDRESS_4, grant #n# transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the slave's address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to get all of these six transmission protocol words in one go.
				The sequence of parameter addresses is continued for grants 1 through to 1024

	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_LOG_PERIOD, grant #n# delay response log period, ro, 0
	Bits[31:8] = Reserved
	Bits[7:0] = log period base 2 as a signed int
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024


	+ PTP_PORT_MASTER_DELAYRESP_GRANT#n#_DURATION, grant #n# delay response duration, ro, 0
	Bits[31:0] = delay response grant duration in secs
				Notes: The sequence of parameter addresses is continued for grants 1 through to 1024

*/
typedef enum
{
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_PROTOCOL			= 0,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_ADDRESS_LENGTH		= 1,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_ADDRESS_1			= 2,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_ADDRESS_2			= 3,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_ADDRESS_3			= 4,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_TPA_ADDRESS_4			= 5,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_LOG_PERIOD				= 6,
	PTP_PORT_MASTER_DELAYRESP_GRANT1_DURATION				= 7,

	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_PROTOCOL			= 10,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_ADDRESS_LENGTH		= 11,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_ADDRESS_1			= 12,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_ADDRESS_2			= 13,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_ADDRESS_3			= 14,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_TPA_ADDRESS_4			= 15,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_LOG_PERIOD				= 16,
	PTP_PORT_MASTER_DELAYRESP_GRANT2_DURATION				= 17,

	//PTP_PORT_MASTER_DELAYRESP_GRANT3_TPA_PROTOCOL			= 20,

	//etc for all 1024 grants
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_PROTOCOL		= 10230,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_ADDRESS_LENGTH	= 10231,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_ADDRESS_1		= 10232,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_ADDRESS_2		= 10233,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_ADDRESS_3		= 10234,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_TPA_ADDRESS_4		= 10235,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_LOG_PERIOD			= 10236,
	PTP_PORT_MASTER_DELAYRESP_GRANT1024_DURATION			= 10237,

	PTP_PORT_MASTER_DELAYRESP_GRANTS_SUBBLOCK_END			= 10238
}mmApiPtpPortMasterSubBlockDelayRespGrants;





//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_SEND_USER_DATA
/*
      + PTP_PORT_MASTER_SEND_USER_DATA_TIMEOUT, the length of time the data message is sent before it times out, rw, 10
	  The message is sent at a rate of 4Hz until this timeout or an acknowledge is received.
	  Default value is 2s, max value is 10s
      Bits[31:8] = Reserved
      Bits[7:0] = Number of repeats

	+ PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH, Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until the network interface on the physical port is configured
				In these cases it will calculate the value depending on the ptp port configuration's protocol.


	+ PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS1, Transmission protocol address bytes 0..3, rw, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS2, Transmission protocol address bytes 4..7, rw, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS3, Transmission protocol address bytes 8..11, rw, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS4, Transmission protocol address bytes 12..15, rw, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these four transmission protocol words in one go.

	+ PTP_PORT_MASTER_SEND_USER_DATA_ENABLE, enable this system, rw, 0
	Bits[31:1] = Reserved
	Bits[0:0] = '1' will enable the system. This will start the timing of the system but no messages will be sent until the
				  data is ready to be sent
				'0' disable the system.

	+ PTP_PORT_MASTER_SEND_USER_DATA_SEND, send the data, rw, 0
	Note that this will send the data to the first configured ptp port on the same domain at the receiver end.
	Bits[31:1] = Reserved
	Bits[0:0] = '1' - if there is data to send then this will start sending the data in a signalling message at a rate of 4Hz.
				'0' - The system will automatically clear this bit when the data has been sent.

	+ PTP_PORT_MASTER_SEND_USER_CONTROL_REGISTER, states whether sending was ok or failed, rw, 0
	Bits[31:2] = Reserved
	Bits[1:0] =  If first bit is 1 then it was sent ok
				 If second bit is 1 then the send failed

	+ PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA_LENGTH, length of data to send in words, rw, 0
	Bits[31:16] = Reserved
	Bits[15:0] = Length of data. Maximum size is 64 words

	+ PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA1, first 4 bytes of data to send, rw, 0
	Bits[31:0] = data
	The data words must all be set at the same time. Note that the data up to the 64th word is contiguous.

	+ PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA64, last possible 4 bytes of data to send, rw, 0
	Bits[31:0] = data
	The data words must all be set at the same time. Note that the data up to the 64th word is contiguous.
*/
typedef enum
{
	PTP_PORT_MASTER_SEND_USER_DATA_TIMEOUT = SEND_USER_DATA_TIMEOUT,
	PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH = SEND_USER_DATA_RECEIVER_TPA_ADDRESS_LENGTH,
	PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS1 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS1,
	PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS2 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS2,
	PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS3 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS3,
	PTP_PORT_MASTER_SEND_USER_DATA_RECEIVER_TPA_ADDRESS4 = SEND_USER_DATA_RECEIVER_TPA_ADDRESS4,
	PTP_PORT_MASTER_SEND_USER_DATA_ENABLE = SEND_USER_DATA_ENABLE,
	PTP_PORT_MASTER_SEND_USER_DATA_SEND = SEND_USER_DATA_SEND,
	PTP_PORT_MASTER_SEND_USER_DATA_CONTROL_REGISTER = SEND_USER_DATA_SEND_CONTROL_REGISTER,
	PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA_LENGTH = SEND_USER_DATA_SEND_DATA_LENGTH,
	PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA1 = SEND_USER_DATA_SEND_DATA1,
	PTP_PORT_MASTER_SEND_USER_DATA_SEND_DATA64 = SEND_USER_DATA_SEND_DATA64,
	PTP_PORT_MASTER_SEND_USER_DATA_END
}mmApiPtpPortMasterSubBlockSendUserData;



//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_RECEIVE_USER_DATA
/*
    + PTP_PORT_MASTER_RECEIVE_USER_DATA_TIMEOUT, the length of time the acknowledge message is sent after which it times out, rw, 10
	  The acknowledge messages is sent at a rate of 4Hz until this timeout.
	  Default is 2, max value is 10s
      Bits[31:8] = Reserved
      Bits[7:0] = time in secs

    + PTP_PORT_MASTER_RECEIVE_USER_DATA_ENABLE, enable the receipt of user data, rw, 0
      Bits[31:1] = Reserved
      Bits[0:0] = '1' enable
				  '0' disable

	+ PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH, sender transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until the network interface on the physical port is configured
				In these cases it will calculate the value depending on the ptp port configuration's protocol.


	+ PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1, sender transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2, sender transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3, sender transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these four transmission protocol words in one go.


	+ PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4, sender transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these four transmission protocol words in one go.


    + PTP_PORT_MASTER_RECEIVE_USER_DATA_READY, data is ready to read, rw, 0
      The users should clear this bit after reading the data
      Bits[31:1] = Reserved
      Bits[0:0] = '1' data has been received and can be read
				  '0' no data

    - PTP_PORT_MASTER_RECEIVE_USER_DATA_FAIL, received data was corrupted, rw, 0
      The users should clear this bit after reading the data
      Bits[31:1] = Reserved
      Bits[0:0] = '1' data is corrupted
				  '0' no data



   + PTP_PORT_MASTER_RECEIVE_USER_DATA_LENGTH, length of data received in words, ro, 0
      Bits[31:16] = Reserved
      Bits[15:0] = length of data
      This value can be up to 64 words


    + PTP_PORT_MASTER_RECEIVE_USER_DATA_DATA1, first 4 bytes of data received, ro, 0
      Bits[31:0] = Four bytes of received data
	  These received data bytes up to the length must be read at the same time.
	  Note that the data up to the 64th word of data received is contiguous

    + PTP_PORT_MASTER_RECEIVE_USER_DATA_DATA64, last possible 4 bytes of data, ro, 0
      Bits[31:0] = Four bytes of received data
	  These received data bytes up to the length must be read at the same time.
	  Note that the data up to the 64th word of data received is contiguous

*/
typedef enum
{
	PTP_PORT_MASTER_RECEIVE_USER_DATA_TIMEOUT = RECEIVE_USER_DATA_TIMEOUT,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_ENABLE = RECEIVE_USER_DATA_ENABLE,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS_LENGTH,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS1,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS2,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS3,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4 = RECEIVE_USER_DATA_SENDER_TPA_ADDRESS4,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_READY = RECEIVE_USER_DATA_READY,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_FAIL = RECEIVE_USER_DATA_FAIL,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_LENGTH = RECEIVE_USER_DATA_LENGTH,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_DATA1 = RECEIVE_USER_DATA_DATA1,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_DATA64 = RECEIVE_USER_DATA_DATA64,
	PTP_PORT_MASTER_RECEIVE_USER_DATA_END
}mmApiPtpPortMasterSubBlockReceiveUserData;




//PARAMETERSDEF:PTP_PORT_MASTER_SUBBLOCK_SEND_SMPTE_DATA
/*
	+ PTP_PORT_MASTER_SEND_SMPTE_SYS_FRAME_NUMERATOR, Default video frame rate of the slave system as a lowest term rational, rw, 0
		 The data type shall be composed of a pair of unsigned Int32 values coded in big-endian form where the first shall be the numerator
		 and the second shall be the denominator. The denominator shall be the smallest value that represents the frame rate denominator.
		 Bits[31:0] = numerator

	+ PTP_PORT_MASTER_SEND_SMPTE_SYS_FRAME_DENOMINATOR, Default video frame rate of the slave system as a lowest term rational, rw, 0
		 The data type shall be composed of a pair of unsigned Int32 values coded in big-endian form where the first shall be the numerator
		 and the second shall be the denominator. The denominator shall be the smallest value that represents the frame rate denominator.
		 Bits[31:0] = denominator

	+ PTP_PORT_MASTER_SEND_SMPTE_MASTER_LOCKING_STATUS, Complementary information to clockClass, rw, 0
	 This gives more information regarding the clock class.
	 Bits[31:8] = reserved
	 Bits[7:0] = 	0: Not in use
					1: Free Run
					2: Cold Locking. In response to a disturbance, the grandmaster is re-locking quickly. In this situation, a rapid phase
						adjustment with a time discontinuity can be expected.
					3: Warm Locking. In response to a disturbance, the grandmaster is re-locking slowly by means of a frequency adjustment,
						with no phase discontinuity. Time continuity is maintained.
					4: Locked (i.e., in normal operation and stable)

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_ADDRESS_FLAGS, Indicates the intended SMPTE ST 12-1 flags, rw, 0
	 Bits[31:2] = reserved
	 Bits[1:0] =	Bit 0: Drop frame
						 0: Non-drop-frame
						 1: Drop-frame
					Bit 1: Color Frame Identification
						 0: Not in use

	 + PTP_PORT_MASTER_SEND_SMPTE_CURRENT_LOCAL_OFFSET, Offset in seconds of Local Time from grandmaster PTP time, rw, 0
	 Bits[31:0] = offset in seconds


	 + PTP_PORT_MASTER_SEND_SMPTE_JUMP_SECONDS, The size of the next discontinuity in seconds of Local Time, rw, 0
	 Bits[31:0] = A value of zero indicates that no discontinuity is expected. A positive value indicates that the discontinuity will
				  cause the currentLocalOffset to increase.

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JUMP0, the seconds portion of the grandmaster PTP time at the time that the next discontinuity of the currentLocalOffset, rw, 0
	 The discontinuity occurs at the start of the second indicated
	 Bits[31:0] = this is a 48 bit number where the top 32 bits are stored in this register

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JUMP1, the seconds portion of the grandmaster PTP time at the time that the next discontinuity of the currentLocalOffset, rw, 0
	 The discontinuity occurs at the start of the second indicated
	 Bits[31:16] = reserved
	 Bits[15:0] = this is a 48 bit number where the bottom 16 bits are stored in this register

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JAM0, The value of the seconds portion of the PTP time corresponding to the next scheduled occurrence of the Daily Jam, rw, 0
	 If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
	 Bits[31:16] = this is a 48 bit number where the top 32 bits are stored in this register

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JAM1, The value of the seconds portion of the PTP time corresponding to the next scheduled occurrence of the Daily Jam, rw, 0
	 If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
	 Bits[31:16] = reserved
	 Bits[15:0] = this is a 48 bit number where the bottom 16 bits are stored in this register


	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_PREV_JAM0, the seconds portion of the PTP time corresponding to the previous occurrence of the Daily Jam, rw, 0
	 If no Daily Jam is scheduled, the value of timeOfNextJam shall be zero
	 Bits[31:0] = this is a 48 bit number where the top 32 bits are stored in this register

	 + PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_PREV_JAM1, the seconds portion of the PTP time corresponding to the previous occurrence of the Daily Jam, rw, 0
	 Bits[31:16] = reserved
	 Bits[15:0] = this is a 48 bit number where the bottom 16 bits are stored in this register


	 + PTP_PORT_MASTER_SEND_SMPTE_PREV_JAM_LOCAL_OFFSET, The value of currentLocalOffset at the time of the previous Daily Jam event, rw, 0
	 Bits[31:0] = offset
	 If a discontinuity of Local Time occurs at the jam time, this parameter reflects the offset after the discontinuity


	 + PTP_PORT_MASTER_SEND_SMPTE_DAYLIGHT_SAVING, indicates the daylight saving, rw, 0
	 Bits[31:3] = reserved
	 Bits[2:0] = 	Bit 0:  Current Daylight Saving
						0: Not in effect
						1: In effect
					Bit 1: Daylight Saving at next discontinuity
						0: Not in effect
						1: In effect
					Bit 2: Daylight Saving at previous Daily Jam event
						0: Not in effect
						1: In effect

	 + PTP_PORT_MASTER_SEND_SMPTE_LEAP_SECOND_JUMP, The reason for the forthcoming discontinuity of currentLocalOffset indicated  by timeOfNextJump, rw, 0
	 Bits[31:1] = reserved
	 Bits[0:0] = Bit 0:
					  0: Other than a change in the number of leap seconds  (default)
					  1: A change in number of leap seconds

	 + PTP_PORT_MASTER_SEND_SMPTE_ENABLE, enable the smpte sending, rw, 0
	 Bits[31:1] = reserved
	 Bits[0:0] = Bit 0:
					  0: disable
					  1: enable

	 + PTP_PORT_MASTER_SEND_SMPTE_PERIOD, log period of the data sending rate, rw, 0
	 Bits[31:8] = reserved
	 Bits[7:0] = value from -2 (ie 4Hz) to 3 (1/8 Hz)

	 + PTP_PORT_MASTER_SEND_SMPTE_SEND_DATA_NOW, send data now, wo, 0
	 Bits[31:1] = reserved
	 Bits[0:0] = if 1 is written then the data will be sent immediately

*/
typedef enum
{
	PTP_PORT_MASTER_SEND_SMPTE_SYS_FRAME_NUMERATOR = SMPTE_SYS_FRAME_NUMERATOR,
	PTP_PORT_MASTER_SEND_SMPTE_SYS_FRAME_DENOMINATOR = SMPTE_SYS_FRAME_DENOMINATOR,
	PTP_PORT_MASTER_SEND_SMPTE_MASTER_LOCKING_STATUS = SMPTE_MASTER_LOCKING_STATUS,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_ADDRESS_FLAGS = SMPTE_TIME_ADDRESS_FLAGS,
	PTP_PORT_MASTER_SEND_SMPTE_CURRENT_LOCAL_OFFSET = SMPTE_CURRENT_LOCAL_OFFSET,
	PTP_PORT_MASTER_SEND_SMPTE_JUMP_SECONDS = SMPTE_JUMP_SECONDS,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JUMP0 = SMPTE_TIME_OF_NEXT_JUMP0,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JUMP1 = SMPTE_TIME_OF_NEXT_JUMP1,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JAM0 = SMPTE_TIME_OF_NEXT_JAM0,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_NEXT_JAM1 = SMPTE_TIME_OF_NEXT_JAM1,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_PREV_JAM0 = SMPTE_TIME_OF_PREV_JAM0,
	PTP_PORT_MASTER_SEND_SMPTE_TIME_OF_PREV_JAM1 = SMPTE_TIME_OF_PREV_JAM1,
	PTP_PORT_MASTER_SEND_SMPTE_PREV_JAM_LOCAL_OFFSET = SMPTE_PREV_JAM_LOCAL_OFFSET,
	PTP_PORT_MASTER_SEND_SMPTE_DAYLIGHT_SAVING = SMPTE_DAYLIGHT_SAVING,
	PTP_PORT_MASTER_SEND_SMPTE_LEAP_SECOND_JUMP = SMPTE_LEAP_SECOND_JUMP,
	PTP_PORT_MASTER_SEND_SMPTE_ENABLE = SMPTE_SEND_ENABLE,
	PTP_PORT_MASTER_SEND_SMPTE_PERIOD	= SMPTE_SEND_PERIOD,
	PTP_PORT_MASTER_SEND_SMPTE_SEND_DATA_NOW	= SMPTE_SEND_DATA_NOW,
	PTP_PORT_MASTER_SEND_SMPTE_DATA_END
}mmApiPtpPortMasterSubBlockSmpteData;



//SUBBLOCKSDEF:MMAPI_AMT1_PARAMS
//SUBBLOCKSDEF:MMAPI_AMT2_PARAMS
typedef enum
{
	AMT_SUBBLOCK_ENTRY_1    			= 0,   /* AMT entry 1  */
	AMT_SUBBLOCK_ENTRY_2    			= 1,   /* AMT entry 2  */
	AMT_SUBBLOCK_ENTRY_3    			= 2,   /* AMT entry 3  */
	AMT_SUBBLOCK_ENTRY_4    			= 3,   /* AMT entry 4  */
	AMT_SUBBLOCK_ENTRY_5    			= 4,   /* AMT entry 5  */
	AMT_SUBBLOCK_ENTRY_6    			= 5,   /* AMT entry 6  */
	AMT_SUBBLOCK_ENTRY_7    			= 6,   /* AMT entry 7  */
	AMT_SUBBLOCK_ENTRY_8    			= 7,   /* AMT entry 8  */
	AMT_SUBBLOCK_ENTRY_9    			= 8,   /* AMT entry 9  */
	AMT_SUBBLOCK_ENTRY_10    			= 9,   /* AMT entry 10 */
	AMT_SUBBLOCK_CONFIG					= 1023,   /* General Parameters */
	AMT_SUBBLOCK_END
} mmApiAmtSubBlock;

//PARAMETERSDEF:AMT_SUBBLOCK_CONFIG
/*
	+ AMT_CONFIG_ENABLE, Enable acceptable master table, rw, 0
	This flag will enable or disable the acceptable master table.
	Bits[31:0] = Enable (0= disable, 1 = enable)

	+ AMT_CONFIG_BITFIELD1, validity of entries 1..10, ro, 0
	Bits[31:10] = reserved
	Bits[9:0] = Bitfield
				Notes: if entry 1 is valid then bit 0 in this field is 1, if entry 10 is valid then
				bit 9 is 1 etc. Currently only 10 masters are supported

*/
typedef enum
{
	AMT_CONFIG_ENABLE					= 0,
	AMT_CONFIG_BITFIELD1				= 1,
	AMT_CONFIG_END
}mmAMTSubBlockConfigParams;




//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_1
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_2
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_3
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_4
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_5
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_6
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_7
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_8
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_9
//PARAMETERSDEF:AMT_SUBBLOCK_ENTRY_10
/*
	- AMT_ENTRY_TPA_PROTOCOL, Transmission protocol, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The acceptable master's transmission protocol.
				It is recommended to set all of these six transmission protocol words in one go.
				Note how the register addresses are set for entry 1,2 and up to the 10th acceptable master


	+ AMT_ENTRY_TPA_ADDRESS_LENGTH, Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the acceptable master's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until either %AMT_ENTRY_TPA_ADDRESS_1% has been set when the ptp port is configured or when
				the record has been enabled. In these cases it will calculate the value depending on
				the ptp port configuration's protocol.


	+ AMT_ENTRY_TPA_ADDRESS_1, Transmission protocol address bytes 0..3, rw, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these six transmission protocol words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFF then this means that the
				acceptable master entry is not in use.


	+ AMT_ENTRY_TPA_ADDRESS_2, Transmission protocol address bytes 4..7, rw, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AMT_ENTRY_TPA_ADDRESS_3, Transmission protocol address bytes 8..11, rw, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the acceptable master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AMT_ENTRY_TPA_ADDRESS_4, Transmission protocol address bytes 12..15, rw, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the acceptable master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AMT_ENTRY_PORTID_NODEID_1, The acceptable master's port id node id bytes 0..3, rw, 0xFFFFFFFF
	Bits[31:0] = The first set of 4 bytes of the node id
	            /
				Notes: 	The first set of 4 bytes in the acceptable master's node id. /
				Each byte in this uint32 will be a value in the address. eg /
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				/
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFF then this means that the
				acceptable master entry is not in use.
				If the address words are non-zero but the nodeid words are set to 0xFFFFFFFF then the address will be used but the /
				nodeid will be ignored.


	+ AMT_ENTRY_PORTID_NODEID_2,  The acceptable master's port id node id bytes 4..7, rw, 0xFFFFFFFF
	Bits[31:0] = The second set of 4 bytes of the node id
	/
				Notes: 	The second set of 4 bytes in the acceptable master's node id. /
				Each byte in this uint32 will be a value in the address. eg /
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				/
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFF then this means that the
				acceptable master entry is not in use.
				If the address words are non-zero but the nodeid words are set to 0xFFFFFFFF then the address will be used but the /
				nodeid will be ignored.

	+ AMT_ENTRY_PORTID_PTPNUM,  The acceptable master's port id ptp port number, rw, 0xFFFF
	Bits[31:16] = reserved
	Bits[15:0] = ptp number (starting from 1)
				Notes: 	Ptp port number of the acceptable master.
				If the PPTNUM has a value of 0xFFFF then it will act as a wild card.
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFF then this means that the
				acceptable master entry is not in use.


	+ AMT_ENTRY_PRIORITY1, Priority 1 of the acceptable master, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = Priority 1
				Notes: 	Priority 1 of the acceptable master. In comparing reference clocks lower values are deemed to be
				better sources than higher. Value can go from 0 to 255.
				This is now deprecated although will still work. Users should use the override facility later on in this
				entry.


	+ AMT_ENTRY_PRIORITY2, Priority 2 of the acceptable master, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = Priority 2
				Notes: 	Priority 2 of the acceptable master. In comparing reference clocks lower values are deemed to be
				better sources than higher. Value can go from 0 to 255.
				This is now deprecated although will still work. Users should use the override facility later on in this
				entry.


	+ AMT_ENTRY_UNICAST_REQUEST, Unicast master flag, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = unicast
				0 = multicast,
				1 = unicast
				Notes: 	Sets the acceptable master to be multicast or unicast
				If unicast then the node will make unicast grant requests to this current master when this AMT entry is enabled, /
				otherwise it will default to multicast.


	+ AMT_ENTRY_FORCED_GRANT, forced grant flag, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = forced grant
				0 = disable,
				1 = enable
				/
				Notes: Enables or disables the forced grant mechanism.
				The forced grant mode of operation allows unicast operation between a master and a slave without
				requiring the usual process of establishing a contract through the exchange of signalling messages.
				Setting this bit prevents the slave from requesting unicast announce, sync and delay response messages,
				instead assuming that these will be provided without any negotiation, and enables the generation of delay request messages at the rate
				programmed in this acceptable master table entry once the master starts sending announce messages
				This mechanism should be enabled when the acceptable master entry field 'enabled' is FALSE. When this master entry is enabled then
				the forced grant flag is checked and if it is TRUE then the forced grant mechanism is started. Note that this mechanism cannot
				be used at the same time as the mechanism used for register %AMT_ENTRY_USE_MSG_RATES%.


	+ AMT_ENTRY_DELAYREQ_PERIOD, forced grant delay request log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = delay request log period  - log base 2  as an sint8  (value can go from 4 to -7)
	            /
				Notes: 	Sets the forced grant delay request log period. This is the log period of the delay request message to be /
				sent from the slave to the acceptable master.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the forced grant flag is checked and if it is TRUE then the delay request messages are sent at this log period value.


	+ AMT_ENTRY_USE_MSG_RATES, use message rates flag, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = use message rates
				0 = disable,
				1 = enable
				/
				Notes: 	Enables the configuration of the various message rates to be used on a per master basis.
				Usually the rates are defined on a per ptp port basis - this mechanism allows the rates to be set on a per master basis.
				This mechanism should be enabled while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined after this should be used.
				Note that this mechanism cannot be used at the same time as the register %AMT_ENTRY_FORCED_GRANT% mechanism.

	+ AMT_ENTRY_DES_ANNOUNCE_PERIOD, desired announce log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = desired announce log period  - log base 2  as an sint8 (value can go from 6 to -4)
	/
				Notes: 	Configures the desired announce message log period in use with the 'use message rates' mechanism. The desired rate /
				is the best smallest possible log period (hence fastest rate) that is wanted, whereas the required rate is the highest log period /
				(hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used.


	+ AMT_ENTRY_DES_SYNC_PERIOD, desired sync log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = desired sync log period  - log base 2  as an sint8 (value can go from 4 to -7)
	/
				Notes: 	Configures the desired sync message log period in use with the 'use message rates' mechanism. The desired rate /
				is the best smallest possible log period (hence fastest rate) that is wanted, whereas the required rate is the highest log period /
				(hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used.



	+ AMT_ENTRY_DES_DELAYREQ_PERIOD, desired delay request log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = desired delay req log period   - log base 2  as an sint8 (value can go from 4 to -7)
	/
				Notes: 	Configures the desired delay request message log period in use with the 'use message rates' mechanism.
				The desired rate is the best smallest possible log period (hence fastest rate) that is wanted, whereas the /
				required rate is the highest log period (hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used.


	+ AMT_ENTRY_REQ_ANNOUNCE_PERIOD, required announce log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = required announce log period  - log base 2  as an sint8 (value can go from 6 to -4)
				Notes: 	Configures the required announce message log period in use with the 'use message rates' mechanism. The desired rate /
				is the best smallest possible log period (hence fastest rate) that is wanted, whereas the required rate is the highest log period /
				(hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used. /



	+ AMT_ENTRY_REQ_SYNC_PERIOD, required sync log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = required sync log period  - log base 2  as an sint8 (value can go from 4 to -7)
	/
				Notes: 	Configures the required sync message log period in use with the 'use message rates' mechanism. The desired rate /
				is the best smallest possible log period (hence fastest rate) that is wanted, whereas the required rate is the highest log period /
				(hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used.


	+ AMT_ENTRY_REQ_DELAYREQ_PERIOD, required delay request log period, rw, 0
	Bits[8:1] = reserved
	Bits[7:0] = required delay req log period  - log base 2  as an sint8 (value can go from 4 to -7)
	/
				Notes: 	Configures the required delay request message log period in use with the 'use message rates' mechanism. The desired rate /
				is the best smallest possible log period (hence fastest rate) that is wanted, whereas the required rate is the highest log period /
				(hence lowest rate) that can satisfactory to this slave.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the rates defined here should be used.



	+ AMT_ENTRY_GRANT_DURATION, grant duration, rw, 0
	Bits[31:0] = grant duration in seconds.
	/
				Notes: 	Configures the grant duration in use with the 'use message rates' mechanism.
				Usually this rate is configured on a per ptp port basis,this setting allows it to be set on a per master basis.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then /
				the use message rates flag is checked and if it is TRUE then the value defined here should be used.


	+ AMT_ENTRY_ENABLE, enable entry, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable record.
				0 = disable,
				1 = enable
				/
				Notes: 	Enables this acceptable master entry to be used.
				When this is enabled the master can now be used as an acceptable master. If disabled then this means that master cannot /
				be considered as an acceptable master. To configure any of the values described in this master entry then it is strongly /
				recommended to firstly disable the record, change the settings, then enable the record, otherwise it may result in /
				unexpected behaviour. If this entry is set up to be unicast then enabling this will start making unicast grant requests /
				to the master. The forced grant and msg rates features will not start activating until both this entry and the acceptable /
				master table are enabled.

	+ AMT_ENTRY_REQ_PRS, master must have a primary reference source, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = 0 - ignore this field
				1 - if a master is to be used as a source then it must have a primary reference source

	+ AMT_ENTRY_REQ_TAI, master must have a TAI time, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = 0 - ignore this field
				1 - if a master is to be used as a source then it must have a TAI time

	+ AMT_ENTRY_REQ_UTC, master must have a UTC time, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = 0 - ignore this field
				1 - if a master is to be used as a source then its utc time must be valid

	+ AMT_ENTRY_OVERRIDE_BITMASK, bit mask for what fields to override in BMCA, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  bitmask
				 Each bit represent a data item to override from the incoming Announce messages.
				 These items are taken from the Best Master Clock Algorithm and are in the same order
				 that they are used in the BMCA. If a bit is a '1' then the corresponding value is take from
				 the next 6 fields and will be stored in the Visible Master instead of the values from the Announce
				 message. Each bit represents an item in the BMCA and can have one of the following values:
				 0x01	GM Priority1
				 0x02	GM Identity (not used in this override facility)
				 0x04	GM Clock Class
				 0x08	GM Accuracy
				 0x10	GM offsetScaledLogVariance
				 0x20	GM Priority2
				 0x40	Steps Removed
				 0x80	GM Identity values (not used in this override facility)

	+ AMT_ENTRY_OVERRIDE_PRIORITY1, Priority1 override value, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  value from 0 to 255. If bit 1 in the bit mask is a '1' then this Priority1 value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

	+ AMT_ENTRY_OVERRIDE_CLOCK_CLASS, Clock class override value, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  value from 0 to 255. If bit 3 in the bit mask is a '1' then this Clock class value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

	+ AMT_ENTRY_OVERRIDE_ACCURACY, Accuracy override value, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  value from 0 to 255. If bit 4 in the bit mask is a '1' then this Accuracy value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

	+ AMT_ENTRY_OVERRIDE_LOG_VAR, Offset scaled log variance override value, rw, 0
	Bits[31:16] = reserved
	Bits[15:0] =  value from 0 to 0xFFFF. If bit 5 in the bit mask is a '1' then this log variance value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

	+ AMT_ENTRY_OVERRIDE_PRIORITY2, Priority2 override value, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  value from 0 to 255. If bit 6 in the bit mask is a '1' then this Priority value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

	+ AMT_ENTRY_OVERRIDE_STEPS_REMOVED, Steps removed override value, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] =  value from 0 to 255. If bit 7 in the bit mask is a '1' then this steps removed value will be
				 stored in the Visible Master and used in the BMCA instead of the one from the Announce message.

*/
typedef enum
{
	AMT_ENTRY_TPA_PROTOCOL			= 0,
	AMT_ENTRY_TPA_ADDRESS_LENGTH	= 1,
	AMT_ENTRY_TPA_ADDRESS_1			= 2,
	AMT_ENTRY_TPA_ADDRESS_2			= 3,
	AMT_ENTRY_TPA_ADDRESS_3			= 4,
	AMT_ENTRY_TPA_ADDRESS_4			= 5,
	AMT_ENTRY_PORTID_NODEID_1		= 6,
	AMT_ENTRY_PORTID_NODEID_2		= 7,
	AMT_ENTRY_PORTID_PTPNUM 		= 8,
	AMT_ENTRY_PRIORITY1				= 9,
	AMT_ENTRY_PRIORITY2				= 10,
	AMT_ENTRY_UNICAST_REQUEST		= 11,
	AMT_ENTRY_FORCED_GRANT			= 12,
	AMT_ENTRY_DELAYREQ_PERIOD		= 13,	/* used for forced grant*/
	AMT_ENTRY_USE_MSG_RATES			= 14,
	AMT_ENTRY_DES_ANNOUNCE_PERIOD	= 15,
	AMT_ENTRY_DES_SYNC_PERIOD		= 16,
	AMT_ENTRY_DES_DELAYREQ_PERIOD	= 17,
	AMT_ENTRY_REQ_ANNOUNCE_PERIOD	= 18,	/* required msg rates*/
	AMT_ENTRY_REQ_SYNC_PERIOD		= 19,	/* required msg rates*/
	AMT_ENTRY_REQ_DELAYREQ_PERIOD	= 20,	/* required msg rates*/
	AMT_ENTRY_GRANT_DURATION		= 21,	/* grant duration*/
	AMT_ENTRY_REQ_PRS				= 22,
	AMT_ENTRY_REQ_TAI				= 23,
	AMT_ENTRY_REQ_UTC				= 24,
	AMT_ENTRY_OVERRIDE_BITMASK		= 32,
	AMT_ENTRY_OVERRIDE_PRIORITY1	= 33,
	AMT_ENTRY_OVERRIDE_CLOCK_CLASS	= 34,
	AMT_ENTRY_OVERRIDE_ACCURACY		= 35,
	AMT_ENTRY_OVERRIDE_LOG_VAR		= 36,
	AMT_ENTRY_OVERRIDE_PRIORITY2	= 37,
	AMT_ENTRY_OVERRIDE_STEPS_REMOVED= 38,
	AMT_ENTRY_ENABLE				= 128,
	AMT_ENTRY_END
}mmAMTSubBlockEntryParams;


//SUBBLOCKSDEF:MMAPI_AST1_PARAMS
//SUBBLOCKSDEF:MMAPI_AST2_PARAMS
typedef enum
{
	AST_SUBBLOCK_ENTRY_1    			= 0,   /* AST entry */
	AST_SUBBLOCK_ENTRY_2    			= 1,   /* AST entry */
	AST_SUBBLOCK_ENTRY_3    			= 2,   /* AST entry */
	AST_SUBBLOCK_ENTRY_4    			= 3,   /* AST entry */
	AST_SUBBLOCK_ENTRY_5    			= 4,   /* AST entry */
	AST_SUBBLOCK_ENTRY_6    			= 5,   /* AST entry */
	AST_SUBBLOCK_ENTRY_7    			= 6,   /* AST entry */
	AST_SUBBLOCK_ENTRY_8    			= 7,   /* AST entry */
	AST_SUBBLOCK_ENTRY_9    			= 8,   /* AST entry */
	AST_SUBBLOCK_ENTRY_10    			= 9,   /* AST entry */
	AST_SUBBLOCK_ENTRY_1023    			= 1022,   /* AST entry */
	AST_SUBBLOCK_CONFIG					= 1023,   /* General Parameters */
	AST_SUBBLOCK_END
} mmApiAstSubBlock;

//PARAMETERSDEF:AST_SUBBLOCK_CONFIG
/*
	+ AST_CONFIG_ENABLE, enable the AST table, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable,
				1 = enable
				Notes: 	Enables the acceptable slave table

	+ AST_CONFIG_BITFIELD1, validity of entries 1..32, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 1 is valid then bit 0 in this field is 1, if entry 32 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD2, validity of entries 33..64, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 33 is valid then bit 0 in this field is 1, if entry 64 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD3, validity of entries 65..96, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 65 is valid then bit 0 in this field is 1, if entry 96 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD4, validity of entries 97..128, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 97 is valid then bit 0 in this field is 1, if entry 128 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD5, validity of entries 129..160, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 129 is valid then bit 0 in this field is 1, if entry 160 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD6, validity of entries 161..192, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 161 is valid then bit 0 in this field is 1, if entry 192 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD7, validity of entries 193..224, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 193 is valid then bit 0 in this field is 1, if entry 224 is valid then
				bit 31 is 1 etc

	+ AST_CONFIG_BITFIELD8, validity of entries 225..256, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 225 is valid then bit 0 in this field is 1, if entry 256 is valid then
				bit 31 is 1 etc. Note that these bitfields are continued for the full 1023 slaves that can be held in the
				AST.

	+ AST_CONFIG_BITFIELD32, validity of entries 993..1023, ro, 0
	Bits[31:0] = bitfield
				Notes: if entry 993 is valid then bit 0 in this field is 1, if entry 1023 is valid then
				bit 30 is 1 etc.


*/
typedef enum
{
	AST_CONFIG_ENABLE					= 0,
	AST_CONFIG_BITFIELD1				= 1,
	AST_CONFIG_BITFIELD2				= 2,
	AST_CONFIG_BITFIELD3				= 3,
	AST_CONFIG_BITFIELD4				= 4,
	AST_CONFIG_BITFIELD5				= 5,
	AST_CONFIG_BITFIELD6				= 6,
	AST_CONFIG_BITFIELD7				= 7,
	AST_CONFIG_BITFIELD8				= 8,
	AST_CONFIG_BITFIELD32				= 32,
	AST_CONFIG_END
}mmASTSubBlockConfigParams;

//PARAMETERSDEF:AST_SUBBLOCK_ENTRY_1
//PARAMETERSDEF:AST_SUBBLOCK_ENTRY_2
//PARAMETERSDEF:AST_SUBBLOCK_ENTRY_1023
/*
	- AST_ENTRY_TPA_PROTOCOL, Transmission protocol, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The acceptable slave's transmission protocol.
				It is recommended to set all of these six transmission protocol words in one go.
				Note how the register addresses are set for entry 1,2 and up to the 1023rd acceptable slave


	+ AST_ENTRY_TPA_ADDRESS_LENGTH, Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the acceptable slave's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				This length will be zero until either AST_ENTRY_TPA_ADDRESS_1 has been set when the ptp port is configured or when
				the record has been enabled. In these cases it will calculate the value depending on
				the ptp port configuration's protocol.



	+ AST_ENTRY_TPA_ADDRESS_1, Transmission protocol address bytes 0..3, rw, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to set all of these six transmission protocol words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFF then this means that the
				acceptable master entry is not in use.


	+ AST_ENTRY_TPA_ADDRESS_2, Transmission protocol address bytes 4..7, rw, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AST_ENTRY_TPA_ADDRESS_3, Transmission protocol address bytes 8..11, rw, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the acceptable slave's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:ff:fe:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AST_ENTRY_TPA_ADDRESS_4, Transmission protocol address bytes 12..15, rw, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the acceptable slave's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:ff:fe:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to set all of these six transmission protocol words in one go.


	+ AST_ENTRY_PORTID_NODEID_1, The acceptable slave's port id node id bytes 0..3, rw, 0xFFFFFFFF
	Bits[31:0] = The first set of 4 bytes of the node id
				Notes: 	The first set of 4 bytes in the acceptable slave's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFFFFFFFF then this means that the
				acceptable master entry is not in use.


	+ AST_ENTRY_PORTID_NODEID_2,  The acceptable slave's port id node id bytes 4..7, rw, 0xFFFFFFFF
	Bits[31:0] = The second set of 4 bytes of the node id
				Notes: 	The second set of 4 bytes in the acceptable slave's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFFFFFFFF then this means that the
				acceptable master entry is not in use.


	+ AST_ENTRY_PORTID_PTPNUM,  The acceptable slave's port id ptp port number, rw, 0xFFFF
	Bits[31:16] = reserved
	Bits[15:0] = ptp number (starting from 1)
				Notes: 	Ptp port number of the acceptable slave. This values starts from zero.
				A value of 0xFFFF acts as a wildcard.
				It is recommended to set all of these three port id words in one go.
				If all the address words are set to zero and all of the nodeid words are set to 0xFFFF then this means that the
				acceptable master entry is not in use.


	+ AST_ENTRY_PRIORITY1, Priority 1 of the acceptable slave, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = Priority 1
				Notes: 	Priority 1 of the acceptable slave. In comparing reference clocks lower values are deemed to be
				better sources than higher. Value can go from 0 to 255.


	+ AST_ENTRY_PRIORITY2, Priority 2 of the acceptable slave, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = Priority 2
				Notes: 	Priority 2 of the acceptable slave. In comparing reference clocks lower values are deemed to be
				better sources than higher. Value can go from 0 to 255.

	+ AST_ENTRY_FORCED_GRANT, forced grant flag, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = forced grant
				0 = disable,
				1 = enable
				Notes:Enables or disables the forced grant mechanism.
				The forced grant mode of operation allows unicast operation between a master and a slave without requiring the usual
				process of establishing a contract through the exchange of signalling messages.
				Setting this bit causes the master to send announce and sync messages to the specified slave and to respond to delay request
				messages received from that slave without any negotiation.
				This mechanism should be enabled when the acceptable slave entry field 'enabled' is FALSE. When this slave entry is enabled then
				the forced grant flag is checked and if it is TRUE then the forced grant mechanism is started.

	+ AST_ENTRY_ANNOUNCE_PERIOD, forced grant announce log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = announce log period  - log base 2  as an sint8 (value can go from 6 to -4)
				Notes: 	Sets the forced grant announce log period. This is the log period of the announce message to be
				sent from the master to the acceptable slave
				This value should be set while this acceptable slave entry is disabled. When this slave entry is enabled then
				the forced grant flag is checked and if it is TRUE then the announce messages are sent at this log period value.

	+ AST_ENTRY_SYNC_PERIOD, forced grant sync log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = sync log period  - log base 2  as an sint8 (value can go from 4 to -7)
				Notes: 	Sets the forced grant sync log period. This is the log period of the sync message to be
				sent from the master to the acceptable slave
				This value should be set while this acceptable slave entry is disabled. When this slave entry is enabled then
				the forced grant flag is checked and if it is TRUE then the sync messages are sent at this log period value.


	+ AST_ENTRY_DELAYRESP_PERIOD, forced grant delay response log period, rw, 0
	Bits[31:8] = reserved
	Bits[7:0] = delay response log period  - log base 2  as an sint8 (value can go from 4 to -7)
				Notes: 	Sets the forced grant delay response log period. This is the log period of the delay response message to be
				sent from the slave to the acceptable master.
				This value should be set while this acceptable master entry is disabled. When this master entry is enabled then
				the forced grant flag is checked and if it is TRUE then the delay response messages are sent at this log period value.

	+ AST_ENTRY_ENABLE, enable entry, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable record.
				0 = disable,
				1 = enable
				Notes: 	Enables this acceptable slave entry to be used.
				When this is enabled the slave can now be used as an acceptable slave. If disabled then this means that slave cannot
				be considered as an acceptable slave. To configure any of the values described in this slave entry then it is strongly
				recommended to firstly disable the record, change the settings, then enable the record, otherwise it may result in
				unexpected behaviour.

	+ AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_ANNOUNCE, enable unicast announces when forced grant is enabled, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = enable unicast announce messages when forced grant is enabled
				0 = disable unicast announce messages when forced grant is enabled
				Notes: ToPSync will not send unicast messages when the PTP port address mode is multicastOnly.

	+ AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_SYNC, enable unicast syncs when forced grant is enabled, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = enable unicast sync messages when forced grant is enabled
				0 = disable unicast sync messages when forced grant is enabled
				Notes: ToPSync will not send unicast messages when the PTP port address mode is multicastOnly.

	+ AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_DELAY_RESPONSE, enable unicast delay responses when forced grant is enabled, rw, 0x1
	Bits[31:1] = reserved
	Bits[0:0] = flag
				1 = enable unicast delay response messages when forced grant is enabled
				0 = disable unicast delay response messages when forced grant is enabled
				Notes: ToPSync will not send unicast messages when the PTP port address mode is multicastOnly.

*/
typedef enum
{
	AST_ENTRY_TPA_PROTOCOL			= 0,
	AST_ENTRY_TPA_ADDRESS_LENGTH	= 1,
	AST_ENTRY_TPA_ADDRESS_1			= 2,
	AST_ENTRY_TPA_ADDRESS_2			= 3,
	AST_ENTRY_TPA_ADDRESS_3			= 4,
	AST_ENTRY_TPA_ADDRESS_4			= 5,
	AST_ENTRY_PORTID_NODEID_1		= 6,
	AST_ENTRY_PORTID_NODEID_2		= 7,
	AST_ENTRY_PORTID_PTPNUM 		= 8,
	AST_ENTRY_PRIORITY1				= 9,
	AST_ENTRY_PRIORITY2				= 10,
	AST_ENTRY_FORCED_GRANT			= 11,
	AST_ENTRY_ANNOUNCE_PERIOD		= 12,
	AST_ENTRY_SYNC_PERIOD			= 13,
	AST_ENTRY_DELAYRESP_PERIOD		= 14,
	AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_ANNOUNCE 		= 32,
	AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_SYNC 			= 33,
	AST_ENTRY_FORCED_GRANT_UNICAST_TX_ENABLE_DELAY_RESPONSE = 34,
	AST_ENTRY_ENABLE				= 128,
	AST_ENTRY_END
}mmASTSubBlockEntryParams;


ToPSyncConfigResult mmApiSetPtpPortSlaveConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetPtpPortSlaveConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetPtpPortMasterConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetPtpPortMasterConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetAMTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetAMTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiSetASTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetASTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif
