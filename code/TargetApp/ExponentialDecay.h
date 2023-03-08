#ifndef EXPONENTIAL_DECAY_H
#define EXPONENTIAL_DECAY_H

#include "ToPSyncTypes.h"

typedef struct
{
	Signal		output;
	Signal		limitValue;
	ElapsedTime	tickPeriod;
	uint32		timeConstant;
	Signal		multiplicationValue;
} ExponentialDecay;


void InitialiseExponentialDecay(ExponentialDecay* ed, 
				Signal limitValue, uint32 timeConstant, ElapsedTime tickPeriod);

void ResetExponentialDecay(ExponentialDecay* ed);

void ExponentialDecayInput(ExponentialDecay* ed, Signal input);
void SetTimeConstantED(ExponentialDecay* ed, uint32 timeConstant);
#define PhaseShiftED(ed, shift) ((ed)->output += (shift))

#define ValueED(ed) ((ed)->output)
#define SetValueED(ed, value) ((ed)->output = (value));

#endif

