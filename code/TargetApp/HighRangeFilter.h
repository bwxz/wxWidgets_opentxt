#ifndef HIGH_RANGE_FILTER_H
#define HIGH_RANGE_FILTER_H

#include "ToPSyncTypes.h"
#include "IEEE1588Time.h"
#include "PacketFilter-Value.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
HighRangeFilter comprises two parts:
	Stable holds the bulk of the value.
	Filter holds the values of less than MAX_FILTER_VALUE

Some clients need an almost stable value from the object.
Because of this Stable is visible from outside the object.
*/


typedef struct
{
	PacketFilterValidByValue	filter;
	IEEE1588Time				stable;		//value = stable + filter
	Bool						holdsData;	// has received at least one input

	struct
	{
		Bool			upToDate;
		IEEE1588Time	output;
	} cache;
} HighRangeFilter;


void InitialiseHighRangeFilter(HighRangeFilter* hrf, Frequency openBandwidth, Frequency closedBandwidth,
					uint8 numberOfFilters, float filterRiseTimesBeforeValid,
					ElapsedTime samplePeriod);

void ResetHighRangeFilter(HighRangeFilter* hrf);
void HighRangeFilterInput(HighRangeFilter* hrf, ElapsedTime input);
//not used void HighRangeFilter1588Input(HighRangeFilter* hrf, IEEE1588Time const* input, Bool wholeSeconds);
void HighRangeFilterShift(HighRangeFilter* hrf, IEEE1588Time const* shift, Bool valueIsPrecise);	//shiftIsPrecise is FALSE if the shift is approximate

void HighRangeFilterSet(HighRangeFilter* hrf, IEEE1588Time const* input, Bool valueIsPrecise);
void ZeroHighRangeFilter(HighRangeFilter* hrf);
IEEE1588Time HighRangeFilterValue(HighRangeFilter const* hrf);
#define HighRangeFilterStableValue(hrf) (&(hrf)->stable)

#define HighRangeFilterOutputValid(hrf) DataValidPacketFilterValidByValue(&(hrf)->filter)
#define SetSamplePeriodHighRangeFilter(hrf, period) SetPacketFilterValidByValueSamplePeriod(&(hrf)->filter, period)
#define SetBandwidthHighRangeFilter(hrf, narrow, bandwidth) SetBandwidthPacketFilterValidByValue(&(hrf)->filter, narrow, bandwidth)
#define SetChainLengthHighRangeFilter(hrf, numberOfFilters) SetChainLengthPacketFilterValidByValue(&(hrf)->filter, numberOfFilters)


void AlignStableValueHRF(HighRangeFilter* hrf);
#ifdef __cplusplus
}
#endif

#endif

