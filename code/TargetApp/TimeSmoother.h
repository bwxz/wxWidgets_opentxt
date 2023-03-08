#ifndef TIME_SMOOTHER_H
#define TIME_SMOOTHER_H

#include "General.h"
#include "TimeReferenceSource.h"
#include "TimeReferenceSelector.h"
#include "PacketFilter-VariableBandwidth.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef struct TimeSmootherStruct 
{
	//configuration
	struct ClockPathStruct*					clockPath;
	ElapsedTime								slowTickPeriod;
	Bool									enabled;

	TimeSourceConfiguration					configuration;
	//operation
	TimeReferenceSource*					inputSource;
	TimeReferenceSource						outputSource;
	Bool									inputValid;

	VariableBandwidthFilter					inputFilter;

} TimeSmoother;

void InitialiseTimeSmoother(TimeSmoother* ts,
							struct ClockPathStruct* clockPath,
		                    TimeReferenceSource* inputSource,
							ClockId outputClockId,
							ElapsedTime slowTickPeriod);
void ResetTimeSmoother(TimeSmoother* ts);


void SlowTickTimeSmoother(TimeSmoother* ts);
void EnableTimeSmoother(TimeSmoother* ts, Bool enable);
#define TimeSmootherEnabled(ts) ((ts)->enabled)


typedef enum
{
	enableTS,
	resetTS,
	setUnlockedBandwidthTS,
	setLockedBandwidthTS

} TimeSmootherParameter;

Bool SetTimeSmootherParameter(TimeSmoother* ts, TimeSmootherParameter parameterNumber, float value);
Bool GetTimeSmootherParameter(TimeSmoother* ts, TimeSmootherParameter parameterNumber, float* value);
void TimeSmootherConfigurationUpdated(TimeSmoother* ts);


#ifdef __cplusplus
}
#endif

#endif
