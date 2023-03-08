#ifndef PACKET_RECORD_LIST_H
#define PACKET_RECORD_LIST_H

#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef float PacketRecordValue;	// stored as float to save space
struct PacketRecord
{
	PacketRecordValue			value;
	struct PacketRecordList*	packetRecordList;	// if list != NULL record is in use
	struct PacketRecord*		next;
	struct PacketRecord*		prev;
};


struct PacketRecordList
{
	struct PacketRecord*		head;
	struct PacketRecord*		tail;
	uint16						elements;
	PacketRecordValue			minimimumMeasurableListRange;
}; 



void InitialisePacketRecord(struct PacketRecord* record); // must be called before a record is used
void InitialisePacketRecordList(struct PacketRecordList* list,PacketRecordValue minimimumMeasurableListRange); 
	// must be called before a list is used
void ResetPacketRecordList(struct PacketRecordList* list); // must be called before a list is used


void AddPacketToList(struct PacketRecordList* list, struct PacketRecord* packet);
struct PacketRecordList* RemovePacketFromList(struct PacketRecord* packet);
struct PacketRecord* RemovePacketFromListHead(struct PacketRecordList* list);
struct PacketRecord* RemovePacketFromListTail(struct PacketRecordList* list);
void PhaseShiftList(struct PacketRecordList* list, PacketRecordValue shift);

#define PLMax(list) ((list)->head->value)
#define PLMin(list) ((list)->tail->value)
#define PLMid(list) ((PLMax(list) + PLMin(list)) / 2)
#define PLEmpty(list) ((list)->tail == NULL ? TRUE : FALSE)
#define RemoveHighestValuePacket(list) RemovePacketFromListHead(list)
#define RemoveLowestValuePacket(list) RemovePacketFromListTail(list)
#define PLElements(list) ((list)->elements)
#define PLMaxRecord(list) ((list)->head)
#define PLMinRecord(list) ((list)->tail)
#define PLMaxRecords(list) MaxRecordsPRS(&(list)->store)


float PLDensity(struct PacketRecordList const* list);
PacketRecordValue PLRange(struct PacketRecordList const* list);

//debug only

#ifdef DEBUG
void TestPacketListConsistency(struct PacketRecordList* list);
void TestPacketListArrayConsistency(struct PacketRecordList* listArray, int lists);

#else
#define TestPacketListConsistency(a)
#define TestPacketListArrayConsistency(a,b)
#endif


#ifdef __cplusplus
}
#endif

#endif

