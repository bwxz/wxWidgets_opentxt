#ifndef TIME_SMOOTHER_CONTROL_INTERFACE_H
#define TIME_SMOOTHER_CONTROL_INTERFACE_H

#include "TimeSmoother.h"
#include "General.h"


#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetTimeSmootherParameter(uint8 controllerNumber, TimeSmootherParameter parameterNumber, float value);
ToPSyncConfigResult DoGetTimeSmootherParameter(uint8 controllerNumber, TimeSmootherParameter parameterNumber, float* value);

#ifdef __cplusplus
}
#endif

#endif
