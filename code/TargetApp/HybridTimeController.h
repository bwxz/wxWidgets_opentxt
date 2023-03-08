#ifndef HYBRID_TIME_CONTROLLER_H
#define HYBRID_TIME_CONTROLLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "TimeReferenceSource.h"

#define MAX_TICKS_COUNT_IN_HYBRID						(15*60*SLOW_TICKS_PER_SECOND)
#define INITIAL_PERIOD_IN_HYBRID_WITH_HIHG_BANSWIDTH	(5*60*SLOW_TICKS_PER_SECOND)

struct HybridTimeControllerStruct;


typedef struct HybridTimeControllerStruct
{
	TimeReferenceSource const*				clockInputSource;

	//operation
	Bool									enabled;
	Bool									pllMode;		// TRUE if operation is as a PLL, FALSE if is uses the minimum delays
	Bool									pllModeChanged;	// True if the pllMode is changed by API
	Bool									inputsValid;	// for comparison on next tick
	Bool									clockInputIsPerfect;	//True = input clock's frequency is perfect
	Bool									useConfiguredBandwidth;	//True = use configured PLL b/w, otherwise use internal default one	

	Bool									inputClockIsCoherentCongruentMode;	//This parameter is used for congruent Hybrid only, where topSync will track to input clock frequency when PTP fails out

	uint									ticksInHybrid;		//Ticks counter in Hybrid mode
} HybridTimeController;


void InitialiseHybridTimeController(HybridTimeController* htc,
	uint32 samplesToValid, uint32 maxHistoryLengthSecs, uint32 defaultHistoryLengthSecs, uint32 maxTimeGranularitySecs);
void ResetHybridTimeController(HybridTimeController* htc);

void AssignClockLockingSourceToHybridTimeController(HybridTimeController* htc, TimeReferenceSource const* clockSource);

#define EnabledHTC(htc) ((htc)->enabled)
#define HTCInputsValid(htc) ((htc)->inputsValid)

Bool HTCSyntonisedModeDelayValid(HybridTimeController* htc);
Signal HTCSyntonisedModePhaseLag(HybridTimeController* htc);

void HTCCheckFrequencyOffsetMeasurement(HybridTimeController* htc, TimeReferenceSource* ptpTRS);

typedef enum
{
	enableHTC,
	setModeHTC,
	resetHTC,
	setClockInputIsPerfectHTC,
	setUseConfiguredBandwidthHTC,

	storedDelayDurationMsHTC = 10,
	storedDelayDurationSmHTC,
	storedDelayDurationHTC			//both
} HTCParameter;

Bool SetHybridTimeControllerParameter(HybridTimeController* htc, HTCParameter parameterNumber, float value);
Bool GetHybridTimeControllerParameter(HybridTimeController* htc, HTCParameter parameterNumber, float* value);
void PrintHybridTimeController(HybridTimeController const* htc, char** ptrptr, long *bufferSize, Bool printTitle);

#ifdef __cplusplus
}
#endif

#endif

