#ifndef TOPSYNC_CLOCK_OUTPUTS_CONTROL_INTERFACE_H
#define TOPSYNC_CLOCK_OUTPUTS_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_ACS1790
#define NAB_OFFSET 1001
#define NAB_NORMAL_CALC 0xFFFFFFFF
#endif



ToPSyncConfigResult DoSetClockOutputsParameter(uint8 outputClockSelect, uint16 parameter, float opClkSource);
ToPSyncConfigResult DoGetClockOutputsParameter(uint8 outputClockSelect, uint16 parameter, float *opClkSource);

#ifdef __cplusplus
}
#endif

#endif

