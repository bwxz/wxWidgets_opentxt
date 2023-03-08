#ifndef PACKET_FILTER_VARIABLE_BANDWIDTH_H
#define PACKET_FILTER_VARIABLE_BANDWIDTH_H

#include "ToPSyncTypes.h"
#include "General.h"
#include "PacketFilter.h"
#include "GeometricInterpolator.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FILTER_RISE_TIMES_TO_GOOD_VALUE 1.0f


typedef struct
{
	Filter  fixedFilter;
	GeometricInterpolator bandwidth;
	Frequency   wideBandwidth;
	Frequency   narrowBandwidth;

	// data valid variables
	float sumOfWeightValuesThreshold; 
	float sumOfWeightValues; 
	float filterRiseTimesBeforeValid;
	Bool useNarrowBandwidthWhenCalculatingDataValid; //normally false

	//state
	float narrowness;
} VariableBandwidthFilter;

void InitialiseVariableBandwidthFilter(VariableBandwidthFilter* vbf, 
		Frequency wideBandwidth, Frequency narrowBandwidth, 
		uint8 numberOfFilters, float filterRiseTimesBeforeValid,
		Bool useNarrowBandwidthWhenCalculatingDataValid,
		ElapsedTime samplePeriod);

void ResetVariableBandwidthFilter(VariableBandwidthFilter* vbf);

void SetBandwidthVariableBandwidthFilter(VariableBandwidthFilter* vbf, Bool narrow, Frequency bandwidth);
#define GetBandwidthVariableBandwidthFilter(vbf, narrow) ((narrow) ? (vbf)->narrowBandwidth : (vbf)->wideBandwidth)
void SetChainLengthVariableBandwidthFilter(VariableBandwidthFilter* vbf, uint8 numberOfFilters);

#define VariableBandwidthFilterInput(vbf, input) VariableBandwidthWeightedFilterInput(vbf, input, 1.0f)
#define DataValidVariableBandwidthFilter(vbf) ((Bool) ((vbf)->sumOfWeightValues >= (vbf)->sumOfWeightValuesThreshold))

void VariableBandwidthWeightedFilterInput(VariableBandwidthFilter* vbf, Signal input, float weight);
void VariableBandwidthFilterSetNarrowness(VariableBandwidthFilter* vbf, float filterNarrowness);

#define GetVariableBandwidthFilterSamplePeriod(vbf) GetFilterSamplePeriod(&(vbf)->fixedFilter)
#define VariableBandwidthFilterValue(vbf) FilterValue(&(vbf)->fixedFilter)

#define VariableBandwidthFilterSetValue(vbf, value) FilterSetValue(&(vbf)->fixedFilter,value)

#define VariableBandwidthFilterSetValid(vbf, valid) ((vbf)->sumOfWeightValues = (valid) ? (vbf)->sumOfWeightValuesThreshold : 0)

#define PhaseShiftVariableBandwidthFilter(vbf, shift) PhaseShiftFilter(&(vbf)->fixedFilter,shift)


void SetVariableBandwidthFilterSamplePeriod(VariableBandwidthFilter* vbf, ElapsedTime newSamplePeriod);
void SetRiseTimesToValidVariableBandwidthFilter(VariableBandwidthFilter* vbf, float filterRiseTimesBeforeValid);


#ifdef __cplusplus
}
#endif

#endif

