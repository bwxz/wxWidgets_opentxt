#ifndef GENERIC_CONFIGURATION_H
#define GENERIC_CONFIGURATION_H

#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


ToPSyncConfigResult DoSetOrGetGenericParameter(Bool set, uint8 id1, uint8 id2, uint16 input, float* parameterValue);

#ifdef __cplusplus
}
#endif

#endif