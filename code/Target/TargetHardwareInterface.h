#ifndef TARGET_HARDWARE_INTERFACE_H
#define TARGET_HARDWARE_INTERFACE_H

#include <mqx.h>
#include "ApplicationInfrastructureInterface.h"


void SetupIOPorts(void);  // This is called by  InitialiseDevice() but can be called earlier
void InitialiseDevice(void);
void InitialiseInterrupts(void);
void SetTaskPriority(unsigned int newPriority);
Bool SETSPresent(void);
Bool ECCPresent(void);

//Switched control values
Bool UseCompiledIPAddressValues(void);
Bool UseOddIPAddress(void);  // only use with ReadUseCompiledIPAddressValues()

uint32 ConvertTimeToTicks(float time);  // time is in seconds - if time is less than 1 tick, 1 is returned



#endif

