#ifndef SAMPLE_DIVIDER_H
#define SAMPLE_DIVIDER_H

#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
Used when the calling object receives more samples (data) than it needs.  
This object tells the calling object which samples to use (a n/m division)
*/
typedef struct
{
	Bool		enabled;
	ElapsedTime samplePeriod;    // period provided
	ElapsedTime outputPeriod;  // period required by client
	ElapsedTime timeSinceRollover; // rollover happens when timeSinceRollover > requiredPeriod
	uint		samplesSinceRollover;  // valid from time UseThisInputSD(..) returns to next call of 
	uint		storedVersionOfSamplesSinceRollover; // valid from time UseThisInputSD(..) returns true to next call of UseThisInputSD(..)
} SampleDivider;

void InitialiseSampleDivider(SampleDivider* sd, ElapsedTime outputPeriod, ElapsedTime samplePeriod);

void ResetSampleDivider(SampleDivider* sd);
void InputSD(SampleDivider* sd); 
Bool OutputNowSD(SampleDivider* sd);
// returns true if the sample should be used;
uint16 GetOutputsForThisTick(SampleDivider* sd);

void SetRequiredOutputPeriodSD(SampleDivider* sd, ElapsedTime outputPeriod);

#define GetOutputPeriodSD(sd) ((sd)->outputPeriod)
#define GetSamplePeriodSD(sd) ((sd)->samplePeriod)
// MeanSampleDivision: 0.5 is added to adjust the rounding.
#define MeanSampleDivision(sd) ((uint32) (GetOutputPeriodSD(sd) / GetSamplePeriodSD(sd) + 0.5)) 
#define EnableSD(sd,enable) {(sd)->enabled = (enable);}

#ifdef __cplusplus
}
#endif


#endif
