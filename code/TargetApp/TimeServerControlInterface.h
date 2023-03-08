#ifndef TIME_SERVER_CONTROL_INTERFACE_H
#define TIME_SERVER_CONTROL_INTERFACE_H

#include "TimeServerControl.h"

ToPSyncConfigResult DoSetToPSyncGlobalParameter(uint8 id1, uint8 id2, ToPSyncParameter parameter, float value);
ToPSyncConfigResult DoGetToPSyncGlobalParameter(uint8 id1, uint8 id2, ToPSyncParameter parameter, float* value);


#endif

