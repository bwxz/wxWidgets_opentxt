#ifndef SETS_CONTROL_INTERFACE_H
#define SETS_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C"
{
#endif

Bool DoSETSRead(uint8 address, uint8* value);
Bool DoSETSWrite(uint8 address, uint8 value);
Bool DoGetSETSAutomaticConfigurationEnabled(Bool *enabled);
Bool DoSetSETSAutomaticConfigurationEnabled(Bool enabled);

#ifdef __cplusplus
}
#endif


#endif