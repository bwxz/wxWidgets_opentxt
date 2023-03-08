#ifndef ETHERNET_INTERFACE_H
#define ETHERNET_INTERFACE_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ARC
	#include <mqx.h>
	#include <message.h>			// for mqx _pool_id
	#include <klog.h>
	#include <log.h>
	#include <fio.h>				// for sprintf
    #include <trsocket.h>			// get network byte order settings to be used
									// in preference to those defined in pcb.h
	#include <pcb.h>
	#include <enet.h>
#else

typedef struct pcb_fragment
{
	uint32		LENGTH;
	uint8*		FRAGMENT;
} PCB_FRAGMENT, * PCB_FRAGMENT_PTR;

typedef struct pcb
{
	void			(* FREE)(struct pcb *);
	void*			PRIVATE;
	PCB_FRAGMENT	FRAG[1];
} PCB, * PCB_PTR;

typedef uint32* ttUserInterface;

uint32 _mem_sum_ip(uint32 startingValue, int _mem_size, uint8 const data[]);


#endif

// values used by the PRIVATE member of PCB (Packet Control Block)
#define PRIVATE_FREE 0
#define PRIVATE_USED 1
#define PRIVATE_DO_NOT_FREE 2

#ifdef __cplusplus
}
#endif


#endif

