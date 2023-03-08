#ifndef HYBRID_TIME_CONTROLLER_CONTROL_INTERFACE_H
#define HYBRID_TIME_CONTROLLER_CONTROL_INTERFACE_H

#include "HybridTimeController.h"
#include "General.h"


#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetHybridTimeControllerParameter(uint8 controllerNumber, HTCParameter parameterNumber, float value);
ToPSyncConfigResult DoGetHybridTimeControllerParameter(uint8 controllerNumber, HTCParameter parameterNumber, float* value);

#ifdef __cplusplus
}
#endif

#endif
