#ifndef MQX_PACKET_CONTROL_BLOCK_ALLOCATOR_H
#define MQX_PACKET_CONTROL_BLOCK_ALLOCATOR_H

#include "General.h"
#include "MqxInterface.h"


#ifdef  __cplusplus
extern "C" {
#endif

typedef uint32 TemplateVersion;
typedef struct
{
	TemplateVersion version;	//used to identify the version of data held in a PCB
	PCB	pcb;					// pcb must be immediately followed by dummy
	PCB_FRAGMENT dummy;			// space to hold next element of array
} PCBAllocatorElement;

// pcb->PRIVATE == 0, indicates that the pcb is free.

typedef struct
{
 	PCBAllocatorElement*	store; //FREE member of PCB points to NULL to indicate unused
	PCBAllocatorElement*	storeEnd; // last element

	PCBAllocatorElement* 	next;
	uint32	noPCBCount;			// count of missed PCB allocations
} PCBAllocator;

void InitialisePacketControlBlockAllocator(
	PCBAllocator* allocatorPtr, uint16 messageBytes, uint16 messages);

PCBAllocatorElement* RequestPCBFromAllocator(PCBAllocator* allocatorPtr); // return it by calling element->pcb.FREE(&element->pcb)
uint16 PCBsAvailable(PCBAllocator const* allocatorPtr);

#ifdef  __cplusplus
}
#endif


#endif

