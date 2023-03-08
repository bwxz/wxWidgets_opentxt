#ifndef PACKET_FILTER_H
#define PACKET_FILTER_H

#include "ToPSyncTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
NOTE - For the filter to work, the cut off frequency (fc) must satisfy

  fc < 1/(2*Pi*Ts), where Ts is the sample period

  If this is not true, the filter's output will equal its input
*/

#define PACKET_FILTER_RISE_TIME_0_99 0.76f  // as a proportion of 1/cutoff
#define PACKET_FILTER_RISE_TIME_10_90 0.35f  // as a proportion of 1/cutoff

#define MAX_INPUT_MULTIPLICATION_RATIO 0.55f // to avoid instablity
typedef double FilterStore;
typedef struct
{
	uint8			configuredNumberOfFilters;
	ElapsedTime		samplePeriod;
	Frequency		cutOff;	// 3dB
	FilterStore*	store;
	FilterStore*	output; // address of element from which output is taken
	FilterStore*	last; // address of last element
	float			inputMultiplicationRatio;  // will never exceed MAX_INPUT_MULTIPLICATION_RATIO
} Filter;


void InitialiseFilter(Filter* filter, Frequency bandwidth, uint8 numberOfFilters, ElapsedTime newSamplePeriod);
void ResetFilter(Filter* filter);
void SetFilterParameters(Filter* filter, Frequency bandwidth, uint8 numberOfFilters, ElapsedTime newSamplePeriod);

#define GetFilterSamplePeriod(filter) ((filter)->samplePeriod)
#define FilterValue(filter) ((Signal)(*(filter)->output))
#define GetFilterChainLength(filter) ((filter)->output - (filter)->store)
void FilterSetValue(Filter* filter,Signal value);
void PhaseShiftFilter(Filter* filter,Signal shift);

void SetFilterSamplePeriod(Filter* filter, ElapsedTime newSamplePeriod);
void SetFilterChainLength(Filter* filter, uint8 numberOfFilters);
void SetFilterBandwidth(Filter* filter, Frequency bandwidth);

void FilterInput(Filter* filter, Signal input);
void WeightedFilterInput(Filter* filter, Signal input, float weight);


//Functions for directly changing inputMultiplicationRatio
// When these functions are used cutOff and samplePeriod are invalid
void InitialiseFilterUsingDivisionRatio(Filter* filter, uint8 numberOfFilters, float divisionRatio);

/* IIR filter output is (input - prevOutput) * M + prevOutput * ( 1 - M)

If M > 1 filter becomes unstable; if M > 0.5 the filter isn't much use
M = 2 Pi * filterCutOffFrequency * filterUpdatePeriod

0.55 < 2 Pi * filterCutOffFrequency * filterUpdatePeriod
filterUpdatePeriod < 1/(4 Pi * filterCutOffFrequency)
If the filterUpdatePeriod becomes too big we need to change filterCutOffFrequency and chain length
*/
#define PACKET_FILTER_MAX_USEABLE_UPDATE_PERIOD(cutoff) (MAX_INPUT_MULTIPLICATION_RATIO /(2 * PI * (cutoff))

//Private function
float CalculateInputMultiplicationRatio(Frequency cutOff,ElapsedTime samplePeriod);

#ifdef __cplusplus
}
#endif

#endif

