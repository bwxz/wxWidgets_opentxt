#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#include "General.h"
#include "TopSyncTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


Bool SetPLLBandwidth(PhaseLockLoopConfiguration* config, Bool locked, Frequency bandwidth);
#define SetPLLFilterChainLength(config, cl) ((config)->filter.chainLength = (cl))

#ifdef __cplusplus
}
#endif


#endif

