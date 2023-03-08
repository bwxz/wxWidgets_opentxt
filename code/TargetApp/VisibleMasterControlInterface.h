/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: VisibleMasterControlInterface.h $
 * $Revision: 2 $
 * $Date: 12/12/08 10:12 $
 */

/**
 * \file VisibleMasterControlInterface.h
 * This file contains the declrations of the handler routines for the VisibleMaster
 * control message set. These are messages for the configuration and management of the
 * VisibleMaster
 */

#ifndef VISIBLE_MASTER_CONTROL_INTERFACE_H
#define VISIBLE_MASTER_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

//SUBBLOCKSDEF:MMAPI_VMT1_PARAMS
//SUBBLOCKSDEF:MMAPI_VMT2_PARAMS
typedef enum
{
	VMT_SUBBLOCK_ENTRY_1    			= 0,   /* VMT entry 1 */
	VMT_SUBBLOCK_ENTRY_2    			= 1,   /* VMT entry 2 */
	VMT_SUBBLOCK_ENTRY_3    			= 2,   /* VMT entry 3 */
	VMT_SUBBLOCK_ENTRY_4    			= 3,   /* VMT entry 4 */
	VMT_SUBBLOCK_ENTRY_5    			= 4,   /* VMT entry 5 */
	VMT_SUBBLOCK_ENTRY_6    			= 5,   /* VMT entry 6 */
	VMT_SUBBLOCK_ENTRY_7    			= 6,   /* VMT entry 7 */
	VMT_SUBBLOCK_ENTRY_8    			= 7,   /* VMT entry 8 */
	VMT_SUBBLOCK_ENTRY_9    			= 8,   /* VMT entry 9 */
	VMT_SUBBLOCK_ENTRY_10    			= 9,   /* VMT entry 10 */
	VMT_SUBBLOCK_CONFIG					= 1023,   /* General Parameters */
	VMT_SUBBLOCK_END
} mmApiVmtSubBlock;

//PARAMETERSDEF:VMT_SUBBLOCK_CONFIG
/*
	+ VMT_CONFIG_MASK, Visible masters' mask, ro, 0
	Bits[31:0] = bit mask
				Notes: Retrieves the bit mask of the visible masters, where each bit represents which visible master is there.
				Eg if the mask = 0x3 this means the first two bits are set and so there are visible masters in the first two
				locations.

	+ VMT_CONFIG_GRANTS_ISSUED_CHG_COUNTER, grants issued change counter, ro, 0
	Bits[31:0] = integer
				Notes: This should be periodically called to keep a track of whether new grants have  been issued.
				eg if the value is different than the last time then this difference is the number of grants issued


*/
typedef enum
{
	VMT_CONFIG_MASK						= 0,
	VMT_CONFIG_GRANTS_ISSUED_CHG_COUNTER = 1,
	VMT_CONFIG_END
}mmVMTSubBlockConfigParams;



//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_1
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_2
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_3
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_4
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_5
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_6
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_7
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_8
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_9
//PARAMETERSDEF:VMT_SUBBLOCK_ENTRY_10
/*
	+ VMT_ENTRY_TPA_PROTOCOL, Transmission protocol, ro, 0
	Bits[31:2] = reserved
	Bits[1:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The visible master's transmission protocol.
				It is recommended to get all of these six transmission protocol words in one go.
				Note how register addresses change for entries 1,2 through to 10


	+ VMT_ENTRY_TPA_ADDRESS_LENGTH, Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the visible master's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				It is recommended to get all of these six transmission protocol words in one go.


	+ VMT_ENTRY_TPA_ADDRESS_1, Transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	The master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to get all of these six transmission protocol words in one go.


	+ VMT_ENTRY_TPA_ADDRESS_2, Transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	The second set of 4 bytes in the master's protocol address
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to get all of these six transmission protocol words in one go.


	+ VMT_ENTRY_TPA_ADDRESS_3, Transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to get all of these six transmission protocol words in one go.


	+ VMT_ENTRY_TPA_ADDRESS_4, Transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the master's protocol address in big endian.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to get all of these six transmission protocol words in one go.


	+ VMT_ENTRY_PORTID_NODEID_1, The master's portid node id bytes 0..3, ro, 0x0
	Bits[31:0] = The first set of 4 bytes of the node id
				Notes: 	The first set of 4 bytes in the master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				It is recommended to get all of these three port id words in one go.


	+ VMT_ENTRY_PORTID_NODEID_2, The master's portid node id bytes 4..7, ro, 0x0
	Bits[31:0] = The second set of 4 bytes of the node id
				Notes: 	The second set of 4 bytes in the master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				It is recommended to get all of these three port id words in one go.


	+ VMT_ENTRY_PORTID_PTPNUM, The master's portid ptp port number, ro, 0xFFFF
	Bits[31:16] = reserved
	Bits[15:0] = ptp number (starting from 1)
				Notes: 	Ptp port number of the visible master.
				A value of 0xFFFF acts as a wildcard.
				It is recommended to get all of these three port id words in one go.


	+ VMT_ENTRY_PTPPORT_NUM, The local ptp port number, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = ptp number (starting from 1)

	+ VMT_ENTRY_TRANSMITTED_PRIORITY1, Priority 1 of visible master, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = p1 value (from 0 to 255)

	+ VMT_ENTRY_TRANSMITTED_PRIORITY2, Priority 2 of visible master, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = p2 value (from 0 to 255)

	+ VMT_ENTRY_GM_NODEID_1, The grand master's node id bytes 0..3, ro, 0x0
	Bits[31:0] = The first set of 4 bytes of the node id
				Notes: 	The first set of 4 bytes in the grand master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				It is recommended to get all of these two node id words in one go.


	+ VMT_ENTRY_GM_NODEID_2, The grand master's node id bytes 4..7, ro, 0x0
	Bits[31:0] = The second set of 4 bytes of the node id
				Notes:	The second set of 4 bytes in the grand master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				It is recommended to get all of these two node id words in one go.


	+ VMT_ENTRY_GM_STEPS_REMOVED, steps removed from grand master, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = steps removed value (from 0 to 255)
				Notes: 	Number of steps removed this visible master has from the grand master.


	+ VMT_ENTRY_GM_CLOCK_CLASS, The grand master's clock class, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = clock class (from 0 to 255)
				force = 0,
				primaryReference = 6,
				secondaryReference = 7,
				defaultLocked = 13,
				holdoverClockClass = 14,
				bestClockStratumThatCanBeSlave = 128,
				reducedHoldoverClockClass = 193,
				stratum3 = 248,
				stratum4 = 254,
				highestStratumThatCanBeMaster = 254,
				defaultStratum = 255.

	+ VMT_ENTRY_GM_SOURCE, The grand master's clock source type, ro, 0
	Bits[31:4] = reserved
	Bits[3:0] = source
				atom = 0,
				gps = 1,
				radio = 2,
				ptp = 3,
				ntp = ptp = 3,
				handSet = 4,
				other = 5,
				internalOscillator = 6,  (No time reference at all - may be years out)


	+ VMT_ENTRY_GM_ACCURACY, The grand master's accuracy, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = accuracy (from 0 to 255)
				NS25  = 0x20,
				NS100 = 0x21,
				NS250 = 0x22,
				US1   = 0x23,
				US2_5 = 0x24,
				US10  = 0x25,
				US25  = 0x26,
				US100 = 0x27,
				US250 = 0x28,
				MS1   = 0x29,
				MS2_5 = 0x2A,
				MS10  = 0x2B,
				MS25  = 0x2C,
				MS100 = 0x2D,
				MS250 = 0x2E,
				S1    = 0x2F,
				S10   = 0x30,
				GT10S = 0x31,
				ACC_UNKNOWN = 0xFE  (The time accuracy is unknown)
				Notes: 	Reference clock accuracy of the grand master. Values represent:



	+ VMT_ENTRY_GM_LOG_VARIANCE, The grand master's log variance, ro, 0
	Bits[31:16] = reserved
	Bits[15:0] = log variance (from 0)
				Notes: 	Reference clock log variance of the grand master. Value is a uint16 as defined in 1588 v2 7.6.3.3


	+ VMT_ENTRY_GM_TIME_VALID, The grand master's time valid value, ro, 0
	Bits[31:1] = reserved
	Bits[0:0] = time valid
				0 = not TAI time,
				1 =  TAI time

	+ VMT_ENTRY_GM_PRIORITY1, The grand master's priority 1, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = p1 value (from 0 to 255)

	+ VMT_ENTRY_GM_PRIORITY2, The grand master's priority 2, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = p2 value (from 0 to 255)

	+ VMT_ENTRY_GM_TIME_TRANSPORT, The grand master's time transport, ro, 0
	Bits[31:3] = reserved
	Bits[2:0] = time transport value (from 0)
				noTimeTransport = 0,
				generatedLocally = 1,
				viaPacketNetwork = 2,
				viaWire = 3,
				hybridSource = 4.



	+ VMT_ENTRY_MSGCOUNT_UNI_ANNOUNCE, count of unicast announce messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the unicast announce messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_MULTI_ANNOUNCE, count of multicast announce messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the multicast announce messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_UNI_SYNC, count of unicast sync messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes:	Count of the unicast sync messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_MULTI_SYNC, count of multicast sync messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the multicast sync messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_UNI_DELAYRESP, count of unicast delay resp messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the unicast delay resp messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_MULTI_DELAYRESP, count of multicast delay resp messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the multicast delay resp messages received from the visible  master
				It is recommended to get all the *count of values* in one call.



	+ VMT_ENTRY_MSGCOUNT_UNI_DELAYREQ, count of unicast delay req messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the unicast delay req messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_MULTI_DELAYREQ, count of multicast delay req messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the multicast delay req messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_UNI_FOLLOWUP, count of follow up messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the unicast follow up messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_MSGCOUNT_MULTI_FOLLOWUP, count of follow up messages received , ro, 0
	Bits[31:0] = count (from 0)
				Notes: 	Count of the multicast follow up messages received from the visible  master
				It is recommended to get all the *count of values* in one call.


	+ VMT_ENTRY_RESET_STATISTICS, reset statistics , wo, 0
	Bits[31:1] = reserved
	Bits[0:0] = any value.
				Notes: 	This call will reset all the msg count statistics to zero


	+ VMT_ENTRY_GRANTED_ANNOUNCE_LOG, granted announce log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Granted announce messages log period. This may differ from the value requested by the PTP port.
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_GRANTED_SYNC_LOG, granted sync log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Granted sync messages log period. This may differ from the value requested by the PTP port.
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_GRANTED_DELAYREQ_LOG, granted delay req log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Granted delay req messages log period. This may differ from the value requested by the PTP port.
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_ACTUAL_ANNOUNCE_LOG, actual announce log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Actual announce messages log period. This may differ from the granted value.
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_ACTUAL_SYNC_LOG, actual sync log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Actual sync messages log period. This may differ from the granted value
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.



	+ VMT_ENTRY_ACTUAL_DELAYREQ_LOG, actual delay req log period , ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = log period - log base 2 as an sint8
				Notes: 	Actual delay req messages log period. This may differ from the granted value
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.



	+ VMT_ENTRY_REMAINING_ANNOUNCE_GRANT, announce grant remaining , ro, 0
	Bits[31:0] = time in s
				Notes: 	Amount of time in seconds remaining for the announce grant
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_REMAINING_SYNC_GRANT, sync grant remaining , ro, 0
	Bits[31:0] = time in s
				Notes: 	Amount of time in seconds remaining for the sync grant
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.


	+ VMT_ENTRY_REMAINING_DELAYREQ_GRANT, delay req grant remaining , ro, 0
	Bits[31:0] = time in s
				Notes: 	Amount of time in seconds remaining for the delay req grant
				It is recommended to get the *granted xxx log period*, *actual xxx log period* and *xxx remaining* values in one call.

	+ VMT_ENTRY_ESTIMATED_TIME_LAG_VALID, is the time lag valid , ro, 0
	Bits[31:1] = reserved
	Bits[0:0] = time lag valid
				0 = time lag invalid,
				1 = time lag valid

	+ VMT_ENTRY_ESTIMATED_TIME_LAG, the time lag, ro, 0
	Bits[31:0] = time lag as a float

	+ VMT_ENTRY_ESTIMATED_NOISE_VALID, estimated noise valid, ro, 0
	Bits[31:1] = reserved
	Bits[0:0] = valid
				0 = invalid,
				1 = valid

	+ VMT_ENTRY_ESTIMATED_NOISE_MASTERSLAVE, estimated noise in master to slave direction, ro, 0
	Bits[31:0] = noise as a float

	+ VMT_ENTRY_ESTIMATED_NOISE_SLAVEMASTER, estimated noise in slave to master direction, ro, 0
	Bits[31:0] = noise as a float

	+ VMT_ENTRY_ESTIMATED_PKT_DELAY_MASTERSLAVE, estimated packet delay in master to slave direction, ro, 0
	Bits[31:0] = delay as a float

	+ VMT_ENTRY_ESTIMATED_PKT_DELAY_SLAVEMASTER, estimated packet delay in slave to master direction, ro, 0
	Bits[31:0] = delay as a float

	+ VMT_ENTRY_VISIBLE_MASTER_STATE, visible master state, ro, 0
	Bits[31:3] = reserved
	Bits[2..0] = state
				0 invalidVM,
				1 validatingVM,
				2 tooFewTimingMessagesVM,
				3 notOfInterestVM,
				4 requestingContractVM,
				5 validVM


	+ VMT_ENTRY_WAIT_TO_RESTORE_TIME_REMAINING, wait to restore time remaining, ro, 0
	Bits[31:0] = time in seconds
				Note: wait to restore is a feature where a potential master is prevented from becoming the selected
				master for a configured time

	+ VMT_ENTRY_MASTER_LOCKOUT_ENABLE, master lock out, rw, 0
	Bits[31:1] = reserved
	Bits[0:0] = enable
				0 = disable
				1 = enable
				Note: if lock out is enabled then this master will not be considered as a potential master in the BMCA algorithm


*/
typedef enum
{
	VMT_ENTRY_TPA_PROTOCOL			= 0,
	VMT_ENTRY_TPA_ADDRESS_LENGTH	= 1,
	VMT_ENTRY_TPA_ADDRESS_1			= 2,
	VMT_ENTRY_TPA_ADDRESS_2			= 3,
	VMT_ENTRY_TPA_ADDRESS_3			= 4,
	VMT_ENTRY_TPA_ADDRESS_4			= 5,
	VMT_ENTRY_PORTID_NODEID_1		= 6,
	VMT_ENTRY_PORTID_NODEID_2		 = 7,
	VMT_ENTRY_PORTID_PTPNUM 		= 8,
	VMT_ENTRY_PTPPORT_NUM			= 9,
	VMT_ENTRY_TRANSMITTED_PRIORITY1	= 10,
	VMT_ENTRY_TRANSMITTED_PRIORITY2	= 11,
	VMT_ENTRY_GM_NODEID_1			= 20,
	VMT_ENTRY_GM_NODEID_2			= 21,
	VMT_ENTRY_GM_STEPS_REMOVED		= 22,
	VMT_ENTRY_GM_CLOCK_CLASS		= 23,
	VMT_ENTRY_GM_SOURCE				= 24,
	VMT_ENTRY_GM_ACCURACY			= 25,
	VMT_ENTRY_GM_LOG_VARIANCE		= 26,
	VMT_ENTRY_GM_TIME_VALID			= 27,
	VMT_ENTRY_GM_PRIORITY1			= 28,
	VMT_ENTRY_GM_PRIORITY2			= 29,
	VMT_ENTRY_GM_TIME_TRANSPORT		= 30,
	VMT_ENTRY_MSGCOUNT_UNI_ANNOUNCE	= 40,
	VMT_ENTRY_MSGCOUNT_MULTI_ANNOUNCE= 41,
	VMT_ENTRY_MSGCOUNT_UNI_SYNC		= 42,
	VMT_ENTRY_MSGCOUNT_MULTI_SYNC	= 43,
	VMT_ENTRY_MSGCOUNT_UNI_DELAYRESP= 44,
	VMT_ENTRY_MSGCOUNT_MULTI_DELAYRESP	= 45,
	VMT_ENTRY_MSGCOUNT_UNI_DELAYREQ		= 46,
	VMT_ENTRY_MSGCOUNT_MULTI_DELAYREQ	= 47,
	VMT_ENTRY_MSGCOUNT_UNI_FOLLOWUP		= 48,
	VMT_ENTRY_MSGCOUNT_MULTI_FOLLOWUP	= 49,
	VMT_ENTRY_RESET_STATISTICS = 60,
	VMT_ENTRY_GRANTED_ANNOUNCE_LOG	= 70,
	VMT_ENTRY_GRANTED_SYNC_LOG		= 71,
	VMT_ENTRY_GRANTED_DELAYREQ_LOG	= 72,
	VMT_ENTRY_ACTUAL_ANNOUNCE_LOG	= 73,
	VMT_ENTRY_ACTUAL_SYNC_LOG		= 74,
	VMT_ENTRY_ACTUAL_DELAYREQ_LOG	= 75,
	VMT_ENTRY_REMAINING_ANNOUNCE_GRANT = 76,
	VMT_ENTRY_REMAINING_SYNC_GRANT 	= 77,
	VMT_ENTRY_REMAINING_DELAYREQ_GRANT = 78,
	VMT_ENTRY_ESTIMATED_TIME_LAG_VALID = 100,
	VMT_ENTRY_ESTIMATED_TIME_LAG = 101,
	VMT_ENTRY_ESTIMATED_NOISE_VALID = 102,
	VMT_ENTRY_ESTIMATED_NOISE_MASTERSLAVE = 103,
	VMT_ENTRY_ESTIMATED_NOISE_SLAVEMASTER = 104,
	VMT_ENTRY_ESTIMATED_PKT_DELAY_MASTERSLAVE = 105,
	VMT_ENTRY_ESTIMATED_PKT_DELAY_SLAVEMASTER = 106,
	VMT_ENTRY_VISIBLE_MASTER_STATE = 110,
	VMT_ENTRY_WAIT_TO_RESTORE_TIME_REMAINING = 111,
	VMT_ENTRY_MASTER_LOCKOUT_ENABLE = 112,
	VMT_ENTRY_END
}mmVMTSubBlockEntryParams;


ToPSyncConfigResult DoGetVisibleMasters(uint8 ptpPort, uint32 *visibleMastersMask);
ToPSyncConfigResult DoGetMessageGrantStatus(uint8 ptpPort, uint8 visibleMasterId, MessageGrantStatus *messageGrantStatus);
ToPSyncConfigResult DoGetVisibleMaster(uint8 ptpPort, uint8 visibleMasterId, VisibleMasterStatus  *visibleMaster);
ToPSyncConfigResult DoGetVisibleMasterStatistics(uint8 ptpPort, uint8 visibleMasterId, VisibleMasterStatistics *visibleMasterStatistics);
ToPSyncConfigResult DoResetVisibleMasterStatistics(uint8 ptpPort, uint8 visibleMasterId);
ToPSyncConfigResult DoGetVisibleMasterDelayStatistics(uint8 ptpPort, uint8 visibleMasterId, VisibleMasterDelayStatistics *visibleMasterDelayStatistics);

ToPSyncConfigResult DoGetVisibleMasterParameter(uint8 ptpPort, uint8 id, uint16 param, float *value);
ToPSyncConfigResult GetVisibleMasterWaitToRestoreTimeRemaining(uint8 ptpPort, uint8 visibleMasterId, ElapsedTime *timeRemaining);

ToPSyncConfigResult DoSetVisibleMasterLockout(uint8 ptpPort, uint8 visibleMasterId, Bool enable);
ToPSyncConfigResult DoGetVisibleMasterLockout(uint8 ptpPort, uint8 visibleMasterId, Bool *enable);


ToPSyncConfigResult mmApiSetVMTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetVMTConfig(uint8 ptpPort, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
#ifdef __cplusplus
}
#endif

#endif

