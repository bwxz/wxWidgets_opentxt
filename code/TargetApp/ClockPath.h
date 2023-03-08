#ifndef CLOCK_PATH_H
#define CLOCK_PATH_H

#include "TimeReferenceSelector.h"
#include "CurrentMaster.h"
#include "HoldoverController.h"
#include "BinaryLockMonitor.h"
#include "JumpSuppressor.h"
#include "PacketFilter-VariableBandwidth.h"
#include "HybridTimeController.h"
#include "TimeSmoother.h"
#include "AlarmMonitor.h"
#include "NodeTimeController.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	clockLockingPLL,
	ptpLockingPLL,
	numberOfClockPathPLLids
} ClockPathPLLid;


typedef struct ClockPathStruct
{
	ClockId						nodeTimeClockId;   //the time source that provides the node time
	PLLid						timeOutputPLL; //the time reference selector that provides time/phase aligned output
	                                           //(not always the same as nodeTimePLL)
	Bool						generateSmoothedFrequencyOutput;
//	Bool						forceHoldoverTime;
//	Bool						forceHoldoverFrequency;

	TimeReferenceSelector		timeReferenceSelector;
//	TimeSmoother				timeSmoother;
//	JumpSuppressor				jumpSuppressor;

	NodeTimeController			nodeTimeController;

	VariableBandwidthFilter		frequencyAverager;

	struct
	{
		Frequency				outputOffset[numberOfClockIds];
	} cache;

	AlarmClient					alarmTimeNotTAI;
	AlarmClient					alarmUTCOffsetUnknown;
	AlarmClient 				leapSecondWarningAlarm;
	uint32						leapSecondWarningInSecs;
} ClockPath;

void InitialiseClockPath(ClockPath* clockPath, ClockId nodeTimeClockId,
						struct AlarmMonitorStruct* alarmMonitor,
						ElapsedTime slowTickPeriod, ElapsedTime tickPeriod,
						uint32 leapSecondWarningInSecs);

void ResetClockPath(ClockPath* clockPath);

void ClockPathSlowTick(ClockPath* clockPath);

void ClockPathFastTick(ClockPath* clockPath);

#define GetPTPTimeStamperPllId() (secondaryPLL)
#define GetPTPTimeStamperClockId(cp) (networkTSA)
//#define GetTime(cp) GetTimeTRSel(&(cp)->timeReferenceSelector)

#define IsHoldoverValidBooleanCP(cp) ((cp)->timeReferenceSelector.selected ? IsHoldoverValidBoolean(&(cp)->timeReferenceSelector.selected->holdoverController) : FALSE)
#define HoldoverValidCP(cp) ((cp)->timeReferenceSelector.selected ? HoldoverValid(&(cp)->timeReferenceSelector.selected->holdoverController) : FALSE)
#define InvalidateRecentHoldoverDataCP(cp, time) InvalidateRecentHFCData(&(cp)->timeReferenceSelector.selected->holdoverController, time)

#define GetUTCOffsetCP(cp, currentTime1588) GetUTCOffsetTRSelector(GetNodeTimeTRSelCP(cp), currentTime1588) //returns NULL if invalid
#define GetUTCOffsetControllerCP(cp) GetUTCOffsetControllerTRSelector(GetNodeTimeTRSelCP(cp)) //returns NULL if invalid
#define UTCOffsetValidCP(cp) UTCOffsetValidTRSelector(GetNodeTimeTRSelCP(cp))
void GenerateSmoothedFrequencyOutputsCP(ClockPath* clockPath, Bool generateMeanFrequencyOutputs);

void ConfigurationChangedCP(ClockPath* clockPath, TimeReferenceSelector const* trs);

/* GetEpochCP need to return epoch associated with PTP timestamper */
#define GetEpochCP(cp, time) GetEpochTRSel(GetTimeReferenceSelectorCP(cp,GetPTPTimeStamperPllId()), time)

#define IsBoundaryClock(cp) (FALSE)
#define GetTimeReferenceSelectorCP(cp,pll) (&(cp)->timeReferenceSelector)
#define NodeTimePllCP(cp) ((cp)->nodeTimeClockId)
#define TimeOutputPllCP(cp) ((cp)->timeOutputPLL)
#define GetNodeTimeTRSelCP(cp) GetTimeReferenceSelectorCP(cp,0) //TimeReferenceSelector that provides the node time
#define FrequencySmootherEnabledCP(cp) ((cp)->generateSmoothedFrequencyOutput)
#define TimeIsTaiCP(cp) TimeIsTaiTRSel(GetNodeTimeTRSelCP(cp))
#define TimeIsUtcCP(cp) TimeIsUtcTRSel(GetNodeTimeTRSelCP(cp))
//#define SuppressingJumpCP(cp) SuppressingJump(&(cp)->jumpSuppressor)
#define SecondaryPllActiveCP(cp) (EnabledHTC(&(cp)->hybridTimeController) || TimeSmootherEnabled(&(cp)->timeSmoother))

Signal StablePhaseLagCP(ClockPath const* clockPath);
Bool LockAcceptableToBeMasterClockPath(ClockPath const* clockPath);
float GetLockValueClockPath(ClockPath const* clockPath);

#define GetHoldoverFrequencyCP(cp) GetHoldoverFrequency(&(cp)->timeReferenceSelector.selected->holdoverController)

void FrequencyOffsetChangedCP(ClockPath* clockPath, Frequency frequencyIncrease);
void TimeReferenceSelectorSelectionHasChangedCP(ClockPath* clockPath); // a time reference selector has changed its selected source

typedef enum
{
	phaseErrorGradientCP,
	setMaintainBinLockPinInSourceSwitchCP,
	setFrequencyOutputsSourceCP,
	getHoldoverValidCP,
	setHybridTimeControllerEnabledCP,
	setPhaseBuildOutEnabledCP,
	setPhasePullInPeriodCP,
	setPhasePullInMaximumPhaseDiffCP,
	setMaximumPhaseChangeRateSecondPerSecondCP,

	setLeapSecondWarningInSecsCP=10
} ClockPathGenericParameter;


Bool SetGenericParameterCP(ClockPath* clockPath, ClockPathGenericParameter id, float value);
float GetGenericParameterCP(ClockPath const* clockPath, ClockPathGenericParameter id);

void PrintClockPath(ClockPath const* clockPath, char** ptrptr, long *bufferSize, Bool title);

#ifdef __cplusplus
}
#endif

#endif
