#ifndef PACKET_RECORD_STORE_H
#define PACKET_RECORD_STORE_H

#include "General.h"
#include "PacketRecordList.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PacketRecordStore 
{
	uint16 size;
	struct PacketRecord *array; // points to an array of size
	struct PacketRecord* nextRecord;
	struct PacketRecord* oldestRecord;
	uint16 recordsIssued;  
};

void InitialisePRS(struct PacketRecordStore* store, uint16 storeSize);
void ResetPRS(struct PacketRecordStore* store);

struct PacketRecord* RequestNewPacketRecordPRS(struct PacketRecordStore* store);
void ReturnOldestPacketRecordPRS(struct PacketRecordStore* store);
void ReturnOldestPacketRecordsPRS(struct PacketRecordStore* store, uint16 numberOfRecords);

#define RecordsIssuedPRS(store) ((store)->recordsIssued)
#define MaxRecordsPRS(store) ((store)->size)

#ifdef __cplusplus
}
#endif


#endif

