#ifndef MESSAGE_STORE_H
#define MESSAGE_STORE_H

#include "IEEE1588Time.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
	IEEE1588SequenceNumber	sequenceNumber;

	IEEE1588Time			time;
	sint32					correction; // correction to time (in ns)
	/* correct time = time + correction */

	uint16					ticksToLive; // 0 == invalid
} StoredMessage;


struct MsgStoreStruct;
typedef struct MsgStoreStruct MessageStore;

struct MsgStoreStruct
{
	StoredMessage*			store;
	StoredMessage*			end;  // should not change
	StoredMessage*			nextWrite;

	uint16					tickLifetime;  // time for which the message is stored
	uint32					numDeadMsgs;
	uint32					numOverwrittenMsgs;
	void (*fptrMmsgDeletedCB)(MessageStore* ptr, IEEE1588SequenceNumber sno, IEEE1588Time const* time, sint32 correction, Bool isTout, void *cookie);
	void *cookie;
};



void InitialiseMessageStore(MessageStore* ptr, uint16 maxMessagesStored, uint16 tickLifetime);
/* Call for extra message store debugging */
void InitialiseMessageStoreWithCallbacks(
		MessageStore* ptr,
		uint16 maxMessagesStored,
		uint16 tickLifetime,
		void (*fptrMmsgDeletedCB)(MessageStore*, IEEE1588SequenceNumber, IEEE1588Time const*, sint32, Bool, void *cookie),
		void *cookie );
// ticksToLive is the number of times CleanMessageStore can be called before a message is deleted
void ResetMessageStore(MessageStore* ptr);
void MessageStoreTick(MessageStore* ptr);  //return number of messages discared

void StoreMessage(MessageStore* ptr, IEEE1588SequenceNumber sequenceNumber,
		IEEE1588Time const* time, sint32 correction);
Bool RemoveMessageFromStore(MessageStore* ptr, IEEE1588SequenceNumber sequenceNumber,
		IEEE1588Time* time, sint32* correction);


//returns true if message was in store and writes time to localTime
// function may be called with correction == NULL, if the caller isn't interested

Bool MessageIsHeldInStore(MessageStore* ptr, IEEE1588SequenceNumber sequenceNumber);

#ifdef __cplusplus
}
#endif


#endif

