#ifndef RATE_OF_CHANGE_MONITOR_H
#define RATE_OF_CHANGE_MONITOR_H

#include "ToPSyncTypes.h"
#include "History.h"
#include "SampleDivider.h"
#include "ExponentialDecay.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {relativeRoc, absoluteRoc} RocMode;

typedef struct
{
	//configuration
	RocMode mode;
	Signal minSignificantValue;  //values below this are ignored

	// operation
	History history;
	Signal  mostRecent;
	ExponentialDecay output;

} RateOfChangeMonitor;


void InitialiseRateOfChangeMonitor(
	RateOfChangeMonitor* roc,
	RocMode mode,
	uint16 maxHistoryPeriodSecs, //max history to hold (excluding comparison time)
	uint16 historyPeriodSecs, //history to hold (excluding comparison time)
	uint16 comparisonPeriodSecs, //rate of change is calculated over this time
	uint16 decayTimeConstantSecs,
	Signal minSignificantValue, //values below this are ignored
	ElapsedTime tickPeriod);

void ResetRateOfChangeMonitor(RateOfChangeMonitor* roc);

void RateOfChangeMonitorTick(RateOfChangeMonitor* roc, Signal input, Bool inputValid);
void RateOfChangeMonitorSetValue(RateOfChangeMonitor* roc, Signal value);
void PhaseShiftRateOfChangeMonitor(RateOfChangeMonitor* roc, Signal shift);
void RateOfChangeMonitorSetMaxAbsoluteValue(RateOfChangeMonitor* roc, Signal maxValue);

void RateOfChangeMonitorSetTimeParameters(
	RateOfChangeMonitor* roc, 
	uint16 historyPeriodSecs, //history to hold (excluding comparison time)
	uint16 comparisonPeriodSecs, //rate of change is calculated over this time
	uint16 decayTimeConstantSecs);


#define OutputValidRoCM(roc) StoreIsFullHST(&(roc)->history)
#define OutputRoCM(roc) ((float) ValueED(&(roc)->output))

#ifdef __cplusplus
}
#endif

#endif

