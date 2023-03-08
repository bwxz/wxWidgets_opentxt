/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: AlarmControlInterface.h $Revision: 9 $
 * $Date: 6/11/08 17:02 $
 */

/**
 * \file AlarmControlInterface.h
 * This file contains the declarations of the routines for the Alarm
 * control message set. These are messages for the configuration and management of the Alarm
 */

#ifndef ALARM_CONTROL_INTERFACE_H
#define ALARM_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "AlarmMonitor.h"

#ifdef __cplusplus
extern "C" {
#endif


//SUBBLOCKSDEF:MMAPI_ALARMS_PARAMS
typedef enum
{
	ALARM_SUBBLOCK_IN_HOLDOVER    									= 0,   			/* Alarm In Holdover */
	ALARM_SUBBLOCK_NO_CURRENT_MASTER								= 1,   			/* Alarm No Current Master */
	ALARM_SUBBLOCK_NO_CLOCK_INPUT									= 2,   			/* Alarm No Clock Input */
	ALARM_SUBBLOCK_NO_TIME_OF_DAY_INPUT								= 3,   			/* Alarm No Time Of Day Input */
	ALARM_SUBBLOCK_TOPSYNC_TIME_NOT_TAI								= 4,   			/* Alarm Time Not TAI */
	ALARM_SUBBLOCK_PTPPORT_NOT_OPERATIONAL							= 5,   			/* Alarm PTP Port Not Operational */
	ALARM_SUBBLOCK_VISIBLE_MASTER_REFUSED_SYNC_GRANT_REQUEST		= 6,   			/* Alarm Visible Master Refused Sync Grant request  */
	ALARM_SUBBLOCK_VISIBLE_MASTER_IGNORED_SYNC_GRANT_REQUEST		= 7,   			/* Alarm Visible Master Ignored Sync Grant Request */
	ALARM_SUBBLOCK_VISIBLE_MASTER_REFUSED_DELAY_RESPONSE_GRANT_REQUEST= 8,   		/* Alarm Visible Master Refused Delay Response Grant request */
	ALARM_SUBBLOCK_VISIBLE_MASTER_IGNORED_DELAY_RESPONSE_GRANT_REQUEST	= 9,   		/* Alarm Visible Master Ignored Delay Response Grant request */
	ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_SYNC_MESSAGES				= 10,   		/* Alarm Visible Master Too Few Sync Messages */
	ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_FOLLOW_UP_MESSAGES		= 11,   		/* Alarm Visible Master Too Few Follow Up messages*/
	ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_DELAY_RESPONSE_MESSAGES	= 12,   		/* Alarm Visible Master Too Few delay Response messages */
	ALARM_SUBBLOCK_ACCEPTABLE_MASTER_REFUSED_ANNOUNCE_GRANT_REQUEST	= 13,   		/* Alarm Acc Master Refused Announce Grant Request*/
	ALARM_SUBBLOCK_ACCEPTABLE_MASTER_IGNORED_ANNOUNCE_GRANT_REQUEST	= 14,   		/* Alarm Acc Master Ignored Announce Grant Request */
	ALARM_SUBBLOCK_ACCEPTABLE_MASTER_TOO_FEW_ANNOUNCE_MESSAGE		= 15,   		/* Alarm Acc Master Too Few Announce Messages */
	ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_SYNCS_WITHOUT_FOLLOW_UP	= 16,   		/* Alarm Current Master Too Many Syncs Without Follow Up */
	ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_FOLLOW_UPS_WITHOUT_SYNCS	= 17,   		/* Alarm Current Master Too Many Follow Ups without Sync */
	ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_MISSING_DELAY_RESPONSE_MESSAGES	= 18, 	/* Alarm Current Master Too Many Missing Delay Response Messages*/
	ALARM_SUBBLOCK_M2S_PACKET_DELAY_VARIATION						= 19,   		/* Alarm M2S Packet Delay Variation */
	ALARM_SUBBLOCK_S2M_PACKET_DELAY_VARIATION						= 20,   		/* Alarm S2M Packet Delay Variation */
	ALARM_SUBBLOCK_UTC_OFFSET_UNKNOWN								= 21,   		/* Alarm UTC Offset Unknown */
	ALARM_SUBBLOCK_TDM_INTERRUPT									= 22,   		/* Alarm TDM Interrupt */
	ALARM_SUBBLOCK_PATH_DELAY_INVALID								= 23,   		/* Alarm Path Delay Invalid */
	ALARM_SUBBLOCK_PATH_DELAY_TOO_FEW_RESPONSES						= 24,   		/* Alarm Path Delay Too Few Responses */
	ALARM_SUBBLOCK_PATH_DELAY_TOO_MANY_UNEXPECTED_RESPONSES			= 25,			/* Alarm Path Delay Too Many Unexpected Responses */
	ALARM_SUBBLOCK_PATH_DELAY_TOO_FEW_FOLLOW_UPS					= 26,			/* Alarm Path Delay Too Few Follow Ups */
	ALARM_SUBBLOCK_PATH_DELAY_TOO_MANY_UNEXPECTED_FOLLOW_UPS		= 27,			/* Alarm Path Delay Too Many Unexpected Follow Ups */
	ALARM_SUBBLOCK_LEAP_SECOND_WARNING								= 28,			/* Alarm Leap Second Warning */
	ALARM_SUBBLOCK_M2S_PACKET_DELAY_JUMP							= 29,			/* Alarm M2S Packet Delay Jump */
	ALARM_SUBBLOCK_S2M_PACKET_DELAY_JUMP							= 30,   		/* Alarm S2M Packet Delay Jump */
	ALARM_SUBBLOCK_LOCK_DETECT										= 31,			/* Alarm Lock Detect (used in setting lock pin)*/
	ALARM_SUBBLOCK_LOSS_OF_LOCK										= 32,			/* Alarm Loss of lock (can be used in setting alarm pin)*/
	ALARM_SUBBLOCK_ECC_ERROR										= 33,			/* Alarm ECC Error */
	ALARM_USER_DATA_READY											= 34,			/* Alarm User Data Ready */
	ALARM_TOO_FEW_SMTLVS											= 35,			/* Alarm too few SM TLVs have been received*/
	ALARM_NEW_SMTLV													= 36,			/* Alarm new changed SM TLV data has been received */
	ALARM_SUBBLOCK_CONFIG											= 1023,			/* Alarm system configuration */
	ALARM_SUBBLOCK_END
} mmApiAlarmSubBlock;



//PARAMETERSDEF:ALARM_SUBBLOCK_CONFIG
/*
	+ ANY_ALARM_SET, any alarms have been set, ro, 0
	Bits[31:1] = reserved
	Bits[0:0]	0 = no masked alarms have been set
				1 = at least one masked alarm has been set
				In normal mode this will be active if any of the enabled clients have activated their alarm
				In sticky mode this will be active if any of the enabled clients have activated their alarm and will remain active until the
				user has cleared the appropriate bit in alarm request bitfield.
				In change detect mode this will be active if any of the enabled clients have activated or deactivated their alarm and will remain active until the
				user has cleared the appropriate bit in alarm request bitfield.
				Notes: Currently there can be up to 64 clients that can set each alarm source. Clients can be enabled for each alarm.
				If at least one client has raised an alarm and this client is enabled in for that alarm (ie the bit representing it in
				client mask x is '1') then this parameter will have a value of 1.

	+ ALARM_ACTIVE_ALARMS1, active alarms bitfield showing which alarms are active, ro, 0
	Bits[31:0]	bitfield
				Each bit represents an alarm, ie if bit 1 is 1 then the alarm inHoldover is active on a client etc

	+ ALARM_ACTIVE_ALARMS2, active alarms bitfield showing which alarms are active, ro, 0
	Bits[31:1]	reserved
	Bits[1:0]   Each bit represents an alarm, ie if the first bit is 1 then the alarm value 32 (binary lock low used in alarm pin)
				is active. If the second bit is 1 then the alarm value 33 Alarm ECC Error is active

	+ ALARM_MODE, the alarm system mode of operation, rw, 0
	Bits[31:2] = reserved
	Bits[1:0]	0 = level mode
				1 = sticky mode
				2 = change detect mode
				Level mode is when one of the enabled clients sets an alarm to active
				Sticky mode is when one of the enabled clients sets an alarm active after being inactive. Check alarm request bitfield to see which client
				activated the alarm. These bits will remain as '1' until cleared by the user.
				Change detect mode is the same as Transitory mode except alarms can be triggered from going from active to inactive.


*/
typedef enum
{
	ANY_ALARM_SET = 0,
	ALARM_ACTIVE_ALARMS1 = 1,
	ALARM_ACTIVE_ALARMS2 = 2,
	ALARM_MODE = 16,
	ALARM_CONFIG_END
}mmAlarmSubBlockConfigParams;


//PARAMETERSDEF:ALARM_SUBBLOCK_IN_HOLDOVER
//PARAMETERSDEF:ALARM_SUBBLOCK_NO_CURRENT_MASTER
//PARAMETERSDEF:ALARM_SUBBLOCK_NO_CLOCK_INPUT
//PARAMETERSDEF:ALARM_SUBBLOCK_NO_TIME_OF_DAY_INPUT
//PARAMETERSDEF:ALARM_SUBBLOCK_TOPSYNC_TIME_NOT_TAI
//PARAMETERSDEF:ALARM_SUBBLOCK_PTPPORT_NOT_OPERATIONAL
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_REFUSED_SYNC_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_IGNORED_SYNC_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_REFUSED_DELAY_RESPONSE_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_IGNORED_DELAY_RESPONSE_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_SYNC_MESSAGES
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_FOLLOW_UP_MESSAGES
//PARAMETERSDEF:ALARM_SUBBLOCK_VISIBLE_MASTER_TOO_FEW_DELAY_RESPONSE_MESSAGES
//PARAMETERSDEF:ALARM_SUBBLOCK_ACCEPTABLE_MASTER_REFUSED_ANNOUNCE_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_ACCEPTABLE_MASTER_IGNORED_ANNOUNCE_GRANT_REQUEST
//PARAMETERSDEF:ALARM_SUBBLOCK_ACCEPTABLE_MASTER_TOO_FEW_ANNOUNCE_MESSAGE
//PARAMETERSDEF:ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_SYNCS_WITHOUT_FOLLOW_UP
//PARAMETERSDEF:ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_FOLLOW_UPS_WITHOUT_SYNCS
//PARAMETERSDEF:ALARM_SUBBLOCK_CURRENT_MASTER_TOO_MANY_MISSING_DELAY_RESPONSE_MESSAGES
//PARAMETERSDEF:ALARM_SUBBLOCK_M2S_PACKET_DELAY_VARIATION
//PARAMETERSDEF:ALARM_SUBBLOCK_S2M_PACKET_DELAY_VARIATION
//PARAMETERSDEF:ALARM_SUBBLOCK_UTC_OFFSET_UNKNOWN
//PARAMETERSDEF:ALARM_SUBBLOCK_TDM_INTERRUPT
//PARAMETERSDEF:ALARM_SUBBLOCK_PATH_DELAY_INVALID
//PARAMETERSDEF:ALARM_SUBBLOCK_PATH_DELAY_TOO_FEW_RESPONSES
//PARAMETERSDEF:ALARM_SUBBLOCK_PATH_DELAY_TOO_MANY_UNEXPECTED_RESPONSES
//PARAMETERSDEF:ALARM_SUBBLOCK_PATH_DELAY_TOO_FEW_FOLLOW_UPS
//PARAMETERSDEF:ALARM_SUBBLOCK_PATH_DELAY_TOO_MANY_UNEXPECTED_FOLLOW_UPS
//PARAMETERSDEF:ALARM_SUBBLOCK_LEAP_SECOND_WARNING
//PARAMETERSDEF:ALARM_SUBBLOCK_M2S_PACKET_DELAY_JUMP
//PARAMETERSDEF:ALARM_SUBBLOCK_S2M_PACKET_DELAY_JUMP
//PARAMETERSDEF:ALARM_SUBBLOCK_LOCK_DETECT
//PARAMETERSDEF:ALARM_SUBBLOCK_LOSS_OF_LOCK
//PARAMETERSDEF:ALARM_SUBBLOCK_ECC_ERROR
//PARAMETERSDEF:ALARM_USER_DATA_READY
//PARAMETERSDEF:ALARM_TOO_FEW_SMTLVS
//PARAMETERSDEF:ALARM_NEW_SMTLV

/*
	+ ALARM_CLIENT_ENABLE1, enable bits for client ids 1 to 32, rw, 0
	Bits[31:0] = 32 bit mask
				Notes: Each bit represents a client id, eg a value of 0x3 means that client 1 and 2 are enabled. Currently there can be
				up to 64 clients for an alarm. This number may increase.
				Note each of these sub blocks represents one alarm.
				Note how the memory map addresses change for each alarm up to the last alarm.
				If say an alarm has been raised by a client and that client id is masked in then a call to retrieve the parameter
				'any alarms have been set' will have a value of 1.

	+ ALARM_CLIENT_ENABLE2, enable bits for client ids 33 to 64, rw, 0
	Bits[31:0] = 32 bit mask
				Notes: Each bit represents a client id.  eg a value of 0x3 means that client 33 and 34 are enabled

	+ ALARM_STATUS1, alarm status bitfield for client id 1 to 32, r0, 0
	Bits[31:0] = 32 bit bitfield
				Notes: Each bit represents a client id, eg a value of 0x2 means that client 2 has raised the alarm

	+ ALARM_STATUS2, alarm status bitfield for client id 33 to 64, r0, 0
	Bits[31:0] = 32 bit bitfield
				Notes: Each bit represents a client id, eg a value of 0x2 means that client 34 has raised the alarm

	+ ALARM_REQUEST1, request bitfield for client id 1 to 32, rw, 0
	Bits[31:0] = 32 bit bitfield
				Each bit represents an enabled client id that has raised an alarm.
				In sticky or edge detect mode, after reading this, setting the required bit to 1 will clear the bit and allow another existing alarm to be propagated
				and used in activating an alarm.

	+ ALARM_REQUEST2, request bitfield for client id 33 to 64, rw, 0
	Bits[31:0] = 32 bit bitfield
				Each bit represents an enabled client id that has raised an alarm.
				In sticky or edge detect mode, after reading this, setting the required bit to 1 will clear the bit and allow another existing alarm to be propagated
				and used in activating an alarm.

*/
typedef enum
{
	ALARM_CLIENT_ENABLE1 = 0,
	ALARM_CLIENT_ENABLE2 = 1,

	ALARM_STATUS1 = 8,
	ALARM_STATUS2 = 9,

	ALARM_REQUEST1 = 16,
	ALARM_REQUEST2 = 17,

	ALARM_ENTRY_END
}mmAlarmSubBlockEntryParams;



ToPSyncConfigResult DoSetAlarmSourceEnabled(AlarmSource alarmSource, Bool enable);
ToPSyncConfigResult DoGetAlarmSourceEnabled(AlarmSource alarmSource, Bool *enable);
ToPSyncConfigResult DoSetAlarmSourceClientIdEnabled(AlarmSource alarmSource, AlarmSourceIdentity clientId, Bool enable);
ToPSyncConfigResult DoGetAlarmSourceClientIdEnabled(AlarmSource alarmSource, AlarmSourceIdentity clientId, Bool *enable);
ToPSyncConfigResult DoSetAlarmSourceClients(AlarmSource alarmSource, AlarmStateArray *clients);
ToPSyncConfigResult DoGetAlarmSourceClients(AlarmSource alarmSource, AlarmStateArray *clients);

ToPSyncConfigResult DoGetAlarmSet(AlarmSource alarmSource, Bool masked, uint32 *set);
ToPSyncConfigResult DoGetAlarmSetArray(AlarmSource alarmSource, Bool masked, AlarmStateArray *arrayOfSets);
ToPSyncConfigResult DoGetAnyAlarmsSet(Bool *set);
ToPSyncConfigResult DoGetActiveAlarms(AlarmSourceArray *alarmBitField);

ToPSyncConfigResult DoGetAlarmRequestArray(AlarmSource alarmSource, AlarmStateArray *arrayOfRequests);
ToPSyncConfigResult DoSetAlarmRequestArray(AlarmSource alarmSource, AlarmStateArray *arrayOfRequests);

ToPSyncConfigResult DoSetAlarmPolarity(AlarmPolarity data);
ToPSyncConfigResult DoGetAlarmPolarity(AlarmPolarity *data);
ToPSyncConfigResult DoSetAlarmDriveControl(AlarmActiveDriveControl data);
ToPSyncConfigResult DoGetAlarmDriveControl(AlarmActiveDriveControl *data);



ToPSyncConfigResult mmApiSetAlarmConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetAlarmConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);



#ifdef __cplusplus
}
#endif

#endif

