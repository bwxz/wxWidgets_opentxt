#ifndef ROUTER_CONTROLLER_H
#define ROUTER_CONTROLLER_H

#include "General.h"
#include <trsocket.h>
#include <mqx.h>
#include <mutex.h>
#include "Socket.h"

#define RC_MAX_ROUTERS 1

typedef struct
{
	ttUserIpAddress address[RC_MAX_ROUTERS];
	int records; // number of valid records

} AddressRecord;

typedef struct
{
	AddressRecord current; // routers given to protocol stack
	AddressRecord future;  // routers yet to be given to protocol stack
	Bool different; // current and future are different

	MUTEX_STRUCT 	mutex;

} RouterController;

extern RouterController routerController;

void InitialiseRouterController(void);

void RoutersAllocated(ttUserIpAddress const address[], uint8 numberOfRouters);
	// calling this function removes all existing routers

void RouterControllerTick(void);
	// this function must not be called from DHCP task

#define RouterControllerChanged() (routerController.different)

#endif

