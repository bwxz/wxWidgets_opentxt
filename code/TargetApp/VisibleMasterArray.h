#ifndef VISIBLE_MASTER_ARRAY_H
#define VISIBLE_MASTER_ARRAY_H

#include "VisibleMaster.h"
#include "SampleDivider.h"



#ifdef __cplusplus
extern "C" {
#endif

typedef struct VisibleMasterArrayStruct
{
	VisibleMaster* store;
	VisibleMaster* end;
	VisibleMaster* next;  // used by VisibleMasterArrayFastTick

	SampleDivider sampleDivider;
	uint16 		  changeCounter;
} VisibleMasterArray;


void InitialiseVisibleMasterArray(VisibleMasterArray* array, uint16 elements,uint8 localId,
								struct AlarmMonitorStruct* alarmMonitor,
								ElapsedTime visibleMasterSlowTickPeriod,
								ElapsedTime arrayTickPeriod);

void ResetVisibleMasterArray(VisibleMasterArray* array);

VisibleMaster*  FindVisibleMasterUsingPortId(VisibleMasterArray const* array, PortId const* source);
VisibleMaster*  FindVisibleMasterUsingSourceProtocolAddress(VisibleMasterArray const* array,
						TransmissionProtocolAddress const* source);
VisibleMaster*  FindVisibleMasterUsingIndex(VisibleMasterArray const* array, uint16 index);

VisibleMaster* FindUnusedVisibleMasterRecord(VisibleMasterArray const* array);

VisibleMaster* FindBestMaster(VisibleMasterArray const* array, VMState minimumAcceptableState);
VisibleMaster* FindWorstMaster(VisibleMasterArray const* array);
void FindBestMasters(VisibleMasterArray const* array, VMState minimumAcceptableState, VisibleMaster* output[], uint16 outputArraySize);

VisibleMaster* FindNextVisibleMaster(VisibleMasterArray const* array,VisibleMaster* prev);
	// NULL prev means find first

void VisibleMasterArrayFastTick(VisibleMasterArray* array);

void DeleteAllVisibleMasters(VisibleMasterArray const* array);
void VisibleMasterArrayPortConfigurationHasChanged(VisibleMasterArray const* array);
uint32 FindVisibleMasterMask(VisibleMasterArray const* array);

VisibleMaster* VisibleMasterArrayAddNewMaster(VisibleMasterArray *array,
					PortId const* portId,
					AnnounceMessage const* message,
					AcceptablePartnerRecord const* acceptableMasterRecord);

void InsertInVMPointerArray(VisibleMaster* array[], uint16 elements,
							VisibleMaster** insertionPoint, VisibleMaster* pointerToBeInserted);

VisibleMaster** FindInVMPointerArray(VisibleMaster* array[], uint16 elements,
							VisibleMaster* quarry);

VisibleMaster** FindEmptyPositionInVMPointerArray(VisibleMaster* array[], uint16 elements);

#define GetVisibleMasterArrayChangeCounter(v) ((v)->changeCounter)

#ifdef __cplusplus
}
#endif

#endif
