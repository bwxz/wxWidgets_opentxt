#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "General.h"
#include "SystemFunctions.h"
#include "ApplicationInfrastructureInterface.h"
#include <memory.h>

/*To use QueueTemplate to create a queue to handle Elements
create Structure, put QueueTemplateDeclaration(Structure); in a .h file
put  QueueTemplateDefinition(Structure) in a .c file
define the function void DeleteStructure(Structure* ptr)

Use TailOfQueue(q) to find the element to write to
Use AddToTailOfQueue(q) to add the previous write item to the tail of the queue
Use HeadOfQueue(q) to read the head item of a queue and RemoveHeadOfQueue(q) to remove it

//Example  .h file
//================

#include "QueueTemplate.h"
typedef struct
{
	int a;
	int b;
} MyStructure;

QueueTemplateDeclaration(MyStructure);

//Example .c file
//===============

#include "MyFile.h"

QueueTemplateDefinition(MyStructure);

void DeleteMyStructure(MyStructure* element)
{
	//do what needs to be done
}

//Example .c file using the queue
//===============================
#include "MyFile.h"

MyStructureQueue queue;

void Initialise(void)
{
	const uint16 numberOfEntries = 10;

	InitialiseMyStructureQueue(&queue, numberOfEntries);
}


void Add(int a, int b)
{
    (MAY NEED TO ENTER CRITICAL REGION - EG Disable interrupts)
	if (!QueueIsFull(&queue))
	{
		MyStructure* ptr = TailOfQueue(&queue);

		ptr->a = a;
		ptr->b = b;

		AddToTailOfQueue(&queue);
	}
	(MAY NEED TO LEAVE CR)
}

void Remove(int* a, int* b)
{
	(MAY NEED TO ENTER CRITICAL REGION - EG Disable interrupts)
	if (!QueueIsEmpty(&queue))
	{
		MyStructure* ptr = HeadOfQueue(&queue);

		*a = ptr->a;
		*b = ptr->b;

		DeleteMyStructure(ptr);
		RemoveHeadOfQueue(&queue);
	}
	(MAY NEED TO LEAVE CR)
}

Note:  The preprocessor command '##' concatenates the two elements on either side of it.
*/
#define QueueTemplateDeclaration(Element) \
	QueueTemplateStructDeclaration(Element); \
	QueueTemplateInitialiseDeclaration(Element); \
	QueueTemplateResetDeclaration(Element); \
	QueueTemplateQueueLengthDeclaration(Element); \
	QueueTemplateDeleteDeclaration(Element)

#define QueueTemplateStructDeclaration(Element)																			\
typedef struct																										\
{																													\
	Element*						store;																			\
	Element*						last;																			\
	Element*						writePtr;																		\
	Element*						readPtr;																		\
	uint32							fullCount;																	    \
} Element ## Queue

#define QueueTemplateInitialiseDeclaration(Element) \
void Initialise ## Element ## Queue(Element ## Queue* queue, uint16 size)

#define QueueTemplateResetDeclaration(Element) \
void Reset ## Element ## Queue(Element ## Queue* queue)

#define QueueTemplateQueueLengthDeclaration(Element) \
uint16 Element ## QueueLength(Element ## Queue const* queue)

/*This function must be defined for each instantiation */
#define QueueTemplateDeleteDeclaration(Element) \
void Delete ## Element(Element* element)

#define QueueIsEmpty(q) ((q)->writePtr == (q)->readPtr)
#define QueueIsFull(q) ((((q)->writePtr + 1) == (q)->readPtr) || 													\
	((q)->writePtr == (q)->last && (q)->readPtr == (q)->store))
#define QueueIncrementFullCount(q) ((q)->fullCount++)

#ifndef _MSC_VER
	#define IncrementQueuePtr(q, ptr) ((ptr) < (q)->last ? (ptr)++ : (ptr) = (q)->store)
#else
	// This version is only included because the MS Visual C++ compiler generates a error "error C2106: '=' : left operand must be l-value" for the one line version
	// The multiline version does not need to be terminated by a semicolon.  If it is, an empty statement will result.
	#define IncrementQueuePtr(q, ptr)																				\
	{																												\
	if ((ptr) < (q)->last)																							\
		(ptr)++;																									\
	else																											\
		(ptr) = (q)->store;																							\
	}
#endif


#define HeadOfQueue(q) ((q)->readPtr)
// QueueIsEmpty(..) must be false before RemoveMessageFromMessageReceiveQueue is called
#define RemoveHeadOfQueue(q) IncrementQueuePtr((q), (q)->readPtr)

#define TailOfQueue(q) ((q)->writePtr)
// QueueIsFull must be false before AddToTailOfQueue is called
#define AddToTailOfQueue(q) IncrementQueuePtr((q), (q)->writePtr)



#define QueueTemplateDefinition(Element)	                                                                        \
		QueueTemplateInitDefinition(Element)                                                                        \
		QueueTemplateResetDefinition(Element)                                                                       \
		QueueTemplateLengthDefinition(Element)

#define QueueTemplateInitDefinition(Element)                                                                        \
void Initialise ## Element ## Queue(Element ## Queue* queue, uint16 queueSize)										\
{																													\
	uint32 bytes = (queueSize+1) * sizeof(Element);																	\
																													\
	memzero(queue);																									\
																													\
	queue->store = (Element*) AllocateMemory(bytes);																\
	queue->last = queue->store + queueSize;																			\
	queue->writePtr = queue->store;																					\
	queue->readPtr  = queue->store;																					\
																													\
	memset(queue->store, 0, bytes);																					\
																													\
	Reset ## Element ## Queue(queue);																				\
}

#define QueueTemplateResetDefinition(Element)                                                                        \
void Reset ## Element ## Queue(Element ## Queue* queue)																\
{																													\
	DisableInterrupts();																							\
	while(!QueueIsEmpty(queue))																						\
	{																												\
		Element* element = HeadOfQueue(queue);																		\
																													\
		Delete ## Element(element);																					\
																													\
		RemoveHeadOfQueue(queue);																					\
	}																												\
																													\
	queue->writePtr = queue->store;																					\
	queue->readPtr  = queue->store;																					\
	EnableInterrupts();																								\
}

#define QueueTemplateLengthDefinition(Element)                                                                      \
uint16 Element ## QueueLength(Element ## Queue const* queue)														\
{																													\
	uint16 result = 0;																								\
	Element const* head;																							\
	Element const* tail;																							\
																													\
	DisableInterrupts();																							\
	head = HeadOfQueue(queue);																						\
	tail = TailOfQueue(queue);																						\
	EnableInterrupts();																								\
																													\
	if (head >= tail)																								\
		result = (uint16) (head - tail);																			\
	else																											\
		result = (uint16) ((queue->last + 1 - tail) + (head - queue->store));										\
																													\
	return result;																									\
}

#endif

