#ifndef FILTER_FIR_H
#define FILTER_FIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "General.h"
#include "ToPSyncTypes.h"


typedef struct
{
	// Configuration
	ElapsedTime		arrayElementPeriod;
	uint16			ticksPerArrayElementPeriodMinus1;


	//Operation
	Signal*			store;		// holds the array
	Signal*			end;		// one past last element
	Signal*			mostRecent; // most recent element written to
	Signal*			next;		// next element and oldest element
	Bool			full;		//when every element in the array has been written to
	uint16			tickCount;	// until next element increment
	uint16			inputCount;	// number of inputs held in inputStore
	Signal			inputStore; //sum of all inputs since last tick

	struct
	{
		struct 
		{
			Bool valid;
			Signal value;
		} mean;

		struct
		{
			Bool valid;
			Signal value;
		} gradient;
	} cache;

} FilterFIR;

void InitialiseFIRFilter(FilterFIR* filter, ElapsedTime filterDuration, ElapsedTime arrayElementPeriod, ElapsedTime tickPeriod);
	// filterDuration is the time over which the filter averages
	// arrayElementPeriod is the period between array increments (how often the output changes
	// tickPeriod is the period between ticks
	// arrayElementPeriod should be a multiple of tickPeriod

void ResetFIRFilter(FilterFIR* filter);

void InputFIRFilter(FilterFIR* filter, Signal value);
void TickFIRFilter(FilterFIR* filter);	// called each arrayElementPeriod
Signal GradientFIRFilter(FilterFIR const* filter);
void SetUpdatePeriodFIR(FilterFIR* filter, ElapsedTime updatePeriod);

#ifdef __cplusplus
}
#endif


#endif