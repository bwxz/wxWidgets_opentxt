#ifndef DELAY_LIST_H
#define DELAY_LIST_H

#include "PacketRecordList.h"
#include "PacketRecordStore.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef PacketRecordValue DelayListValue;
typedef struct 
{
	struct PacketRecordStore store;

	uint16					maxNumberOfLists; //fixed
	uint16					numberOfLists;    //configurable
	struct PacketRecordList *subList; // pointer to an array of numberOfLists elements

} DelayList;


void InitialiseDelayList(DelayList* delayList, uint16 maxNumberOfLists, uint16 numberOfLists,
		uint16 maximumNumberOfRecordsWhenLocked,DelayListValue minimimumMeasurableDelayDifference);

void EmptyDelayList(DelayList* delayList);


uint16 AddValueToDelayList(DelayList* delayList, DelayListValue value);  
	// adds value - and deletes oldest value if too many records stored
	// returns the number of the list to which the record was added

void PhaseShiftDelayList(DelayList* delayList, DelayListValue shift);  // +ve shift increases delay

void SetDelayListLength(DelayList* delayList, uint16 newLength);  // sets list to no longer than newLength


#define DelayListRecords(list) (RecordsIssuedPRS(&(list)->store))
#define DelayListIsEmpty(list) (RecordsIssuedPRS(&(list)->store) == 0)
#define DelayListMaximumValue(list) ((list)->head->value)
#define DelayListMinimumValue(list) ((list)->tail->value)
#define GetDelaySubListNumber(delayList,sublistPtr) ((sublistPtr)-(delayList)->subList)
#define GetDelaySubList(delayList,n) (&(delayList)->subList[n])
#define NumberOfPRLists(list) ((list)->numberOfLists)
Bool SetNumberOfPRLists(DelayList* delayList, uint16 lists);
#define MaxNumberOfPRLists(list) ((list)->maxNumberOfLists)

#ifdef __cplusplus
}
#endif

#endif

