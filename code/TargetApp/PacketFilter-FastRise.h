#ifndef FAST_RISE_FILTER_H
#define FAST_RISE_FILTER_H

#include "General.h"
#include "PacketFilter-VariableBandwidth.h"


#ifdef __cplusplus
extern "C" {
#endif



typedef struct
{
	VariableBandwidthFilter  filter;
	Bool risen;
} FastRiseFilter;


void InitialiseFastRiseFilter(FastRiseFilter* frf, 
					Frequency openBandwidth, Frequency closedBandwidth, 
					uint8 numberOfFilters, float filterRiseTimesBeforeValid, 
					ElapsedTime samplePeriod);
void ResetFastRiseFilter(FastRiseFilter* frf);
void FastRiseFilterWeightedInput(FastRiseFilter* frf, Signal input, float weight);
#define FastRiseFilterInput(frf, input) FastRiseFilterWeightedInput(frf,input,1.0f)
#define SetSamplePeriodFastRiseFilter(frf, samplePeriod) SetVariableBandwidthFilterSamplePeriod(&(frf)->filter, samplePeriod)

#define SetBandwidthFastRiseFilter(frf, narrow, bandwidth) SetBandwidthVariableBandwidthFilter(&(frf)->filter, narrow, bandwidth)
#define SetChainLengthFastRiseFilter(frf, numberOfFilters) SetChainLengthVariableBandwidthFilter(&(frf)->filter, numberOfFilters);
#define FastRiseFilterSetValue(frf,value) VariableBandwidthFilterSetValue(&(frf)->filter,value)
#define FastRiseFilterSetValid(frf, valid) VariableBandwidthFilterSetValid(&(frf)->filter, valid)

#define FastRiseFilterValue(frf) VariableBandwidthFilterValue(&(frf)->filter)

#define PhaseShiftFastRiseFilter(frf, shift) \
	PhaseShiftVariableBandwidthFilter(&(frf)->filter,shift)
#define DataValidFastRiseFilter(frf) DataValidVariableBandwidthFilter(&(frf)->filter)
#define SetRiseTimesToValidFastRiseFilter(frf, riseTimes)  SetRiseTimesToValidVariableBandwidthFilter(&(frf)->filter, riseTimes)

#ifdef __cplusplus
}
#endif

#endif
