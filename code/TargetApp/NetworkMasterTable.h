#ifndef NETWORK_MASTER_TABLE_H
#define NETWORK_MASTER_TABLE_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "IEEE1588.h"
#include "PhysicalPort.h"
#include "IEEE1588Time.h"


#ifdef __cplusplus
extern "C" {
#endif


/*
The Network Master Table is a list of all Announce messages sensed by ToPSync during its activity.
The aim of this block is to offer a probe over the network and show all the masters that have been detected.
The table is used by the host application to provide candidates for entry into the AMT that will be filtered by Domain.
The list is always enabled.
The table is ideally 32 entries long with a minimum 16 required
The NMT shall have the ability to be Pre-filtered using a domain number (bit field).
Bit field shall be 256 bits. Default is all domains enabled.

If it is from an already recorded master it will update the receive time in it.
If it is from an unknown master and there is space then it will add this master’s details in the first spare slot in the array
If it is from an unknown master and the array is full then it will replace the oldest entry in the array.

*/


#define REMAINING_ANNOUNCE_MSG_DATA 17   //last 17 bytes from offset 47 of announce msg
#define ANNOUNCE_MSG_OFFSET 47   //from offset 47 of announce msg

/*
destinationMac		The physical MAC interface that received the message.
tpa Address 		Either the udp or ethernet Source Address
portId				The Source's PortIdentity
Domain				Domain number
PTP Version			Version
RX Time				The time at which the announce message was received
Announce bytestream	The Announce message from offset 47 (17 bytes)
*/
typedef struct
{
	NetworkInterfaceId			destinationMac;
	TransmissionProtocolAddress tpaAddress;
	PortId						portId;
	IEEE1588Time 				receiveTime;
	IEEE1588Domain 				domain;
	IEEE1588Version 			ptpVersion;
	uint8						remainingAnnounceData[REMAINING_ANNOUNCE_MSG_DATA];
	Bool						active; //whether the record is in use
} NetworkMasterRecord;



typedef struct
{
	NetworkMasterRecord* 	array;
	NetworkMasterRecord* 	end;
	uint32					changeCounter;
	DomainArray 			bitfield; // can filter incoming messages by domain
} NetworkMasterTable;

/*this creates the records in the table*/
void InitialiseNetworkMasterTable(NetworkMasterTable* nmt,
		uint16 maxRecords);

/*clears all the records in the table*/
void ResetNetworkMasterTable(NetworkMasterTable* nmt);

/*
This function will process the announce messages received, and:
If it is from an already recorded master it will update the receive time in it.
If it is from an unknown master and there is space then it will add this master’s details in the first spare slot in the array
If it is from an unknown master and the array is full then it will replace the oldest entry in the array.
 */
ToPSyncConfigResult NewAnnounceMessageReceivedNetworkMasterTable(NetworkMasterTable* nmt, NetworkInterfaceId *destinationMac,
		TransmissionProtocolAddress const *tpaAddress, PortId	const *portId, IEEE1588Time const *receiveTime,
		IEEE1588Domain domain, IEEE1588Version 	ptpVersion, uint8 const  data[], uint16 length);

/*
 * This function returns the number of records in the table. If the bit field has each array element equal to
 * zero then the number of active records are returned.
 * If the domain bitfield is used then it returns the number of active entries with domain numbers that are set
 * in the bitfield. eg if the domain bit field has bitfield.domainMask[0] = 7 then it returns the number of
 * entries with domains equal to 0,1 or 2.
 */
uint16 GetNumberOfRecordsNetworkMasterTable(NetworkMasterTable* nmt, DomainArray bitfield);


void GetMastersBitfieldNetworkMasterTable(NetworkMasterTable* nmt, MastersArray *arrayBitfield);
void SetDomainFilterNetworkMasterTable(NetworkMasterTable* nmt, DomainArray bitfield);
void GetDomainFilterNetworkMasterTable(NetworkMasterTable* nmt, DomainArray bitfield);


/*
 * This function retrieves the network master record from the table by index. If the bit field has each array element equal to
 * zero then it will go through the active entries and retrieve the one at location of index
 * If the domain bitfield is used then it will go through the active entries with domain numbers that are set
 * in the bitfield and retrieve the one at location of index.
 * eg if the domain bit field has bitfield.domainMask[0] = 7 then it goes through the active entries with
 * domains equal to 0,1 or 2 and retrieves the one at location of index.
 */

Bool GetEntryAtIndexByDomainNetworkMasterTable(NetworkMasterTable* nmt, uint16 index, DomainArray bitfield, NetworkMasterRecord *returnRecord);

NetworkMasterRecord *GetEntryAtIndexNetworkMasterTable(NetworkMasterTable* nmt, uint16 index);

/*
 * This function retrieves the network master record in the table matching the mac, tpa and port id
 *
 */
Bool FindRecordNetworkMasterTable(NetworkMasterTable* nmt, NetworkInterfaceId *mac,
		TransmissionProtocolAddress const *tpaAddress, PortId	const *portId, NetworkMasterRecord *returnRecord);



#ifdef __cplusplus
}
#endif


#endif

