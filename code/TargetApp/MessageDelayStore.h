#ifndef MESSAGE_DELAY_STORE_H
#define MESSAGE_DELAY_STORE_H

#include "IEEE1588Time.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
	IEEE1588Time			txTime;
	IEEE1588Time			rxTime;
	sint32					correction;
	uint16					ticksToLive; // 0 == invalid
} StoredDelay;


typedef struct
{
	StoredDelay* store;
	StoredDelay* end;  // should not change
	StoredDelay* nextWrite; 
	StoredDelay* nextRead; 

    uint8   ticksToLive;
} MessageDelayStore;

void InitialiseMessageDelayStore(MessageDelayStore* ptr, uint16 maxMessagesStored, uint8 ticksToLive);
// ticksToLive is the number of times MessageDelayStoreTick can be called before a message is deleted
void ResetMessageDelayStore(MessageDelayStore* ptr);
void MessageDelayStoreTick(MessageDelayStore* ptr);

void StoreMessageDelay(MessageDelayStore* ptr,  
		IEEE1588Time const* txTime, IEEE1588Time const* rxTime, sint32 correction);

Bool RemoveMessageDelayFromStore(MessageDelayStore* ptr,  
		IEEE1588Time* txTime, IEEE1588Time* rxTime, sint32* correction);
// gets next message, returns FALSE if store is empty.

#define MessageDelayStoreContainsData(ptr) ((ptr)->nextWrite != (ptr)->nextRead)


#ifdef __cplusplus
}
#endif


#endif

