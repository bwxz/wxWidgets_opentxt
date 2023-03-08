/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: NetworkMasterTableControlInterface.h $
 * $Revision: 2 $
 * $Date: 12/12/08 10:12 $
 */



#ifndef NETWORK_MASTER_TABLE_CONTROL_INTERFACE_H
#define NETWORK_MASTER_TABLE_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "NetworkMasterTable.h"

#ifdef __cplusplus
extern "C" {
#endif

//SUBBLOCKSDEF:MMAPI_NETWORK_MASTER_TABLE
typedef enum
{
	NMT_SUBBLOCK_ENTRY_1    			= 0,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_2    			= 1,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_3    			= 2,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_4    			= 3,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_5    			= 4,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_6    			= 5,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_7    			= 6,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_8    			= 7,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_9    			= 8,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_10    			= 9,   		/* NMT entry */
	NMT_SUBBLOCK_ENTRY_32    			= 31,   		/* NMT entry */
	NMT_SUBBLOCK_CONFIG					= 1023,   	/* General Parameters */
	NMT_SUBBLOCK_END
} mmApiNmtSubBlock;

//PARAMETERSDEF:NMT_SUBBLOCK_CONFIG
/*
	+ NMT_RESET, reset network master table, wo, 0
	Bits[31:0] = reserved
				Notes: This will clear all the data in the network master table.

	+ NMT_DOMAIN_BITFIELD1, domain bit field for domains 1..31, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here. eg if this value = 0x7 then this means the user wants to accept entries with domains equal to
				0, 1 or 2.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD2, domain bit field for domains 32..63, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD3, domain bit field for domains 64..95, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD4, domain bit field for domains 96..127, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD5, domain bit field for domains 128..159, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD6, domain bit field for domains 160..191, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD7, domain bit field for domains 192..223, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_DOMAIN_BITFIELD8, domain bit field for domains 224..255, rw, 0
	Bits[31:0] = Domain bitfield
				Notes: if the user wants to filter the NMT based on domain then he can set the domain bitfield
				array here.
				If all the bits in the domain bitfield are zero then filtering on domain is not used.

	+ NMT_CHG_COUNTER, nmt change counter, ro, 0
	Bits[31:0] = integer
				Notes: Every time a new master comes online or a master is replaced then this counter
				is incremented. It should be checked periodically and if changed then the user can read
				this new master's details

	+ NMT_MASTER_BITFIELD1, nmt master bitfield 1, ro, 0
	Bits[31:0] = bit field mask
				Notes: a bit is set for each master entry in the array. ie if this value equals 0x7 then it
				means there is a master entry in the first three locations. So NMT_SUBBLOCK_ENTRY_1, NMT_SUBBLOCK_ENTRY_2
				and NMT_SUBBLOCK_ENTRY_3 can be read.
				At present only 32 masters are supported so only this first word is used

	- NMT_MASTER_BITFIELD2, nmt master bitfield 2, ro, 0
	Bits[31:0] = bit field mask
				Notes: a bit is set for each master entry in the array. ie if this value equals 7 then it
				means there is a master entry in the locations 33,34,35.
				Only used if there are more than 32 masters

	- NMT_MASTER_BITFIELD3, nmt master bitfield 3, ro, 0
	Bits[31:0] = bit field mask
				Notes: a bit is set for each master entry in the array. ie if this value equals 7 then it
				means there is a master entry in the locations 65,66,67
				Only used if there are more than 64 masters

	- NMT_MASTER_BITFIELD4, nmt master bitfield 4, ro, 0
	Bits[31:0] = bit field mask
				Notes: a bit is set for each master entry in the array. ie if this value equals 7 then it
				means there is a master entry in the locations 97,98,99
				Only used if there are more than 96 masters


*/
typedef enum
{
	NMT_RESET = 0,
	NMT_DOMAIN_BITFIELD1 = 1,
	NMT_DOMAIN_BITFIELD2 = 2,
	NMT_DOMAIN_BITFIELD3 = 3,
	NMT_DOMAIN_BITFIELD4 = 4,
	NMT_DOMAIN_BITFIELD5 = 5,
	NMT_DOMAIN_BITFIELD6 = 6,
	NMT_DOMAIN_BITFIELD7 = 7,
	NMT_DOMAIN_BITFIELD8 = 8,
	NMT_CHG_COUNTER = 16,
	NMT_MASTER_BITFIELD1 = 17,
	NMT_MASTER_BITFIELD2 = 18,
	NMT_MASTER_BITFIELD3 = 19,
	NMT_MASTER_BITFIELD4 = 20,
	NMT_CONFIG_END
}mmNMTSubBlockConfigParams;



//PARAMETERSDEF:NMT_SUBBLOCK_ENTRY_1
//PARAMETERSDEF:NMT_SUBBLOCK_ENTRY_2
//PARAMETERSDEF:NMT_SUBBLOCK_ENTRY_32
/*
 	+ NMT_ENTRY_ACTIVE, master record is active, ro, 0
	Bits[31:1] = reserved
	Bits[1:0] = active
				0 = record has not been used
				1 = record has a master's details
				Note how the register addresses change for entries 1,2 up to the 32nd entry

	+ NMT_ENTRY_DESTINATION_MAC1, receiving physical MAC, ro, 0
	Bits[31:1] = reserved
	Bits[0:0] =  destination mac
				0 or 1
				Notes:The physical MAC interface that received the message

	- NMT_ENTRY_DESTINATION_MAC2, receiving physical MAC, ro, 0
	Bits[31:0] = reserved

	+ NMT_ENTRY_TPA_PROTOCOL, Transmission protocol, ro, 0
	Bits[31:2] = reserved
	Bits[1:0] = protocol
				0 = udp4,
				1 = ethernet,
				2 = udp6
				Notes: 	The master's transmission protocol.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_TPA_ADDRESS_LENGTH, Transmission protocol address length, ro, 0
	Bits[31:5] = reserved
	Bits[4:0] = length
				4 = udp4,
				6 = ethernet,
				16 = udp6
				Notes: 	The length of the master's protocol address in bytes.
				For udp4 addresses the length is usually 4 bytes.
				For ethernet addresses the length is usually 6 bytes.
				For udp6 addresses the length is usually 16 bytes.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_TPA_ADDRESS1, Transmission protocol address bytes 0..3, ro, 0
	Bits[31:0] = The first 4 bytes of the address.
				Notes: 	The master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, the MSB in the word will be 10, the LSB in the word will be 9.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x0, the LSB in the word will be 0x11.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 1, the LSB in the word will be 4.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_TPA_ADDRESS2, Transmission protocol address bytes 4..7, ro, 0
	Bits[31:0] = The second set of 4 bytes of the address.
				Notes: 	The second set of 4 bytes in the master's protocol address
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, the MSB in the word will be 0x00, the next byte is 0x01.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 5, the LSB in the word will be 8.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_TPA_ADDRESS3, Transmission protocol address bytes 8..11, ro, 0
	Bits[31:0] = The third set of 4 bytes of the address.
				Notes: 	The third set of 4 bytes in the master's protocol address.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 9, the LSB in the word will be 12.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_TPA_ADDRESS4, Transmission protocol address bytes 12..15, ro, 0
	Bits[31:0] = The fourth set of 4 bytes of the address.
				Notes: 	The fourth set of 4 bytes in the master's protocol address in big endian.
				Each byte in this uint32 will be a value in the address. eg
				In the udp4 address 10.0.0.9, this word is not used.
				In the ethernet address 00:16:c0:11:00:01, this word is not used.
				In the udp6 address 1.2.3.4.5.6.7.8.9.10.11.12.13.14.15.16, the MSB in the word will be 13, the LSB in the word will be 16.
				It is recommended to get all of these six transmission protocol words in one go.


	+ NMT_ENTRY_PORTID_NODEID1, The master's portid node id bytes 0..3, ro, 0x0
	Bits[31:0] = The first set of 4 bytes of the node id
				Notes: 	The first set of 4 bytes in the master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0x00, the LSB in the word will be 0xff.
				It is recommended to get all of these three port id words in one go.


	+ NMT_ENTRY_PORTID_NODEID2, The master's portid node id bytes 4..7, ro, 0x0
	Bits[31:0] = The second set of 4 bytes of the node id
				Notes: 	The second set of 4 bytes in the master's node id
				Each byte in this uint32 will be a value in the address. eg
				In the node id 00:16:c0:ff:fe:11:00:01, the MSB in the word will be 0xfe, the LSB in the word will be 0x01.
				It is recommended to get all of these three port id words in one go.


	+ NMT_ENTRY_PORTID_PTPNUM, The master's portid ptp port number, ro, 0xFFFF
	Bits[31:16] = reserved
	Bits[15:0] = ptp number (starting from 0)
				Notes: 	Ptp port number of the master. This value starts from zero.
				A value of 0xFFFF acts as a wildcard.
				It is recommended to get all of these three port id words in one go.

	+ NMT_ENTRY_IEEE1588TIME_SECS, IEEE1588 receive time in secs bits 31 to 0, ro, 0
	Bits[31:0] = seconds bits 31 to 0
				Notes: 	This is the IEEE1588 time that the announce msg was received.
				It is recommended to get all of these four IEEE1588 words in one go.

	+ NMT_ENTRY_IEEE1588TIME_NSECS, IEEE1588 receive time in nsecs, ro, 0
	Bits[31:0] = nano seconds
				Notes: 	This is the IEEE1588 time that the announce msg was received.
				It is recommended to get all of these four IEEE1588 words in one go.

	+ NMT_ENTRY_IEEE1588TIME_SECS_MSB, IEEE1588 receive time secs bits 47 to 32, ro, 0
	Bits[31:16] = reserved
	Bits[15:0]  = seconds bits 47 to 32
				Notes: 	This is the IEEE1588 time that the announce msg was received.
				It is recommended to get all of these four IEEE1588 words in one go.

	+ NMT_ENTRY_IEEE1588TIME_NEGATIVE, IEEE1588 receive time negative, ro, 0
	Bits[31:1] = reserved
	Bits[0:0] = negative
				0 = positive time
				1 = negative time
				Notes: 	This is the IEEE1588 time that the announce msg was received.
				It is recommended to get all of these four IEEE1588 words in one go.

	+ NMT_ENTRY_DOMAIN, master's domain, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = domain
				Notes: 	This is ptp domain of the master from 0 to 255

	+ NMT_ENTRY_VERSION, master's ptp verson, ro, 0
	Bits[31:8] = reserved
	Bits[7:0] = version
				Notes: 	This is ptp version of the master

	+ NMT_ENTRY_ANNOUNCE_DATA1, announce msg data bytes 0..3, ro, 0
	Bits[31:0] = announce msg data
				Notes: This is the first 4 bytes of the received announce msg taken from offset
				47 of the msg. In total there are 17 bytes that are taken.
				It is recommended to get all these announce msg data in one go

	+ NMT_ENTRY_ANNOUNCE_DATA2, announce msg data bytes 4..7, ro, 0
	Bits[31:0] = announce msg data
				Notes: This is the second 4 bytes of the received announce msg taken from offset
				47 of the msg. In total there are 17 bytes that are taken.
				It is recommended to get all these announce msg data in one go

	+ NMT_ENTRY_ANNOUNCE_DATA3, announce msg data bytes 8..11, ro, 0
	Bits[31:0] = announce msg data
				Notes: This is the third 4 bytes of the received announce msg taken from offset
				47 of the msg. In total there are 17 bytes that are taken.
				It is recommended to get all these announce msg data in one go

	+ NMT_ENTRY_ANNOUNCE_DATA4, announce msg data bytes 12..15, ro, 0
	Bits[31:0] = announce msg data
				Notes: This is the fourth 4 bytes of the received announce msg taken from offset
				47 of the msg. In total there are 17 bytes that are taken.
				It is recommended to get all these announce msg data in one go

	+ NMT_ENTRY_ANNOUNCE_DATA5, announce msg data byte 16, ro, 0
	Bits[31:24] = announce msg data
				Notes: This is the last byte of the received announce msg taken from offset
				47 of the msg. In total there are 17 bytes that are taken.
				It is recommended to get all these announce msg data in one go
	Bits[23:0] = reserved


*/
typedef enum
{
	NMT_ENTRY_ACTIVE				= 0,
	NMT_ENTRY_DESTINATION_MAC1		= 1,
	NMT_ENTRY_DESTINATION_MAC2		= 2,
	NMT_ENTRY_TPA_PROTOCOL			= 3,
	NMT_ENTRY_TPA_ADDRESS_LENGTH	= 4,
	NMT_ENTRY_TPA_ADDRESS1			= 5,
	NMT_ENTRY_TPA_ADDRESS2			= 6,
	NMT_ENTRY_TPA_ADDRESS3			= 7,
	NMT_ENTRY_TPA_ADDRESS4			= 8,
	NMT_ENTRY_PORTID_NODEID1		= 9,
	NMT_ENTRY_PORTID_NODEID2		= 10,
	NMT_ENTRY_PORTID_PTPNUM 		= 11,
	NMT_ENTRY_IEEE1588TIME_SECS_MSB	= 12,
	NMT_ENTRY_IEEE1588TIME_SECS		= 13,
	NMT_ENTRY_IEEE1588TIME_NSECS	= 14,
	NMT_ENTRY_IEEE1588TIME_NEGATIVE	= 15,
	NMT_ENTRY_DOMAIN				= 16,
	NMT_ENTRY_VERSION				= 17,
	NMT_ENTRY_ANNOUNCE_DATA1		= 18,
	NMT_ENTRY_ANNOUNCE_DATA2		= 19,
	NMT_ENTRY_ANNOUNCE_DATA3		= 20,
	NMT_ENTRY_ANNOUNCE_DATA4		= 21,
	NMT_ENTRY_ANNOUNCE_DATA5		= 22,
	NMT_ENTRY_END
}mmNMTSubBlockEntryParams;

ToPSyncConfigResult DoGetNMTChangeCounter(uint32 * const counter);
ToPSyncConfigResult DoGetNMTMastersBitField(MastersArray * const  arrayBitfield);
NetworkMasterRecord *DoGetNMTEntry(uint16 index);
ToPSyncConfigResult DoReset();
ToPSyncConfigResult DoGetDomainArray(DomainArray *bitfield);
ToPSyncConfigResult DoSetDomainArray(DomainArray *bitfield);

ToPSyncConfigResult mmApiSetNMTConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetNMTConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
#ifdef __cplusplus
}
#endif

#endif

