#ifndef EPOCH_CONTROLLER_H
#define EPOCH_CONTROLLER_H

#include "IEEE1588Time.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
	IEEE1588Time	approxTime;
	uint16			ticksRemaining; //SLOW_TICK_PERIOD
} EpochController;


void InitialiseEpochController(EpochController* epochController);
void ResetEpochController(EpochController* epochController);
void EpochControllerApplyOffset(EpochController* epochController, IEEE1588Time const* offset);

uint16 EpochControllerGetEpoch(EpochController* epochController, IEEE1588Timestamp const* now);

void EpochControllerSetTime(EpochController* epochController, IEEE1588Time const* time);
void EpochControllerSlowTick(EpochController* epochController);
#define EpochControllerGetApproxTime(epc) (&(epc)->approxTime) // returns a pointer
#define IsEpochControllerApproxTimeValid(epc) ((epc)->ticksRemaining > 0)

#ifdef __cplusplus
}
#endif


#endif

