#ifndef CLOCK_PATH_CONTROL_INTERFACE_H
#define CLOCK_PATH_CONTROL_INTERFACE_H

#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NOT_USE
#ifdef _SIMULATOR
ToPSyncConfigResult DoSetSuppressPhaseJump(Bool phaseJumpSuppressionEnabled);
#endif
ToPSyncConfigResult DoGetSuppressPhaseJump(Bool *phaseJumpSuppressionEnabled);
#endif

ToPSyncConfigResult DoSetOutputClockFrequencySmootherBandwidth(Bool locked, Frequency  bandwidth);
ToPSyncConfigResult DoGetOutputClockFrequencySmootherBandwidth(Bool locked, Frequency* bandwidth);
ToPSyncConfigResult DoSetOutputClockFrequencySmootherEnable(Bool enabled);
ToPSyncConfigResult DoGetOutputClockFrequencySmootherEnable(Bool* enabled);


ToPSyncConfigResult DoSetClockPathParameter(uint8 id, uint16 param, float value);
ToPSyncConfigResult DoGetClockPathParameter(uint8 id, uint16 param, float *value);


#ifdef __cplusplus
}
#endif

#endif

