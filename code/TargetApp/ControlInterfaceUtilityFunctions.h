#ifndef CONTROL_INTERFACE_UTILITY_FUNCTIONS_H
#define CONTROL_INTERFACE_UTILITY_FUNCTIONS_H

#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif


TimeSourceConfiguration* GetTimeSourceConfiguration(TimeTransport sourceType, uint8 id,PLLid pll);
void TimeSourceConfigurationUpdated(TimeTransport  sourceType, uint8 id,PLLid pll);

#ifdef __cplusplus
}
#endif


#endif






