#ifndef NODE_TIME_CONTROLLER_H
#define NODE_TIME_CONTROLLER_H

#include "ToPSyncTypes.h"
#include "TimeReferenceSource.h"
#include "TimeReferenceSelector.h"
#include "LockDetector.h"
#include "BinaryLockMonitor.h"
#include "EpochController.h"
#include "FrequencyController.h"
#include "HardwareFrequencyController.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE			96
#define REMAIN_ERROR_SAMPLE_AVERAGE_PERIOD				(15*60*SLOW_TICKS_PER_SECOND)
#define QUIET_SAMPLE_AVERAGE_PERIOD						(15*60*SLOW_TICKS_PER_SECOND)
#define SUB_QUIET_SAMPLE_AVERAGE_PERIOD					(120*60*SLOW_TICKS_PER_SECOND)
#define PERFECT_CLOCK_MAX_SEARCH_SAMPLES				REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE
#define PERFECT_CLOCK_MAX_SKIPPED_UPDATE				(REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE*2)
#define NON_PERFECT_CLOCK_MAX_SEARCH_SAMPLES			(REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE/4)
#define NON_PERFECT_CLOCK_MAX_SKIPPED_UPDATE			(REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE/2)
#define QUIET_PERIOD_ERROR_VALID_TICKS					(REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE*REMAIN_ERROR_SAMPLE_AVERAGE_PERIOD)
#define REMAIN_ERROR_COMPARISON_THRESH					(REMAIN_ERROR_SAMPLE_AVERAGE_PERIOD*0.995)

#define MAXIMUM_TICKS_AFTER_INITIALISATION				(100*60*SLOW_TICKS_PER_SECOND)
#define MINIMUM_TICKS_AFTER_CAL_B_AS_NO_COMPEN_PERIOD	(60*SLOW_TICKS_PER_SECOND)

#define MAX_NOISE_RE_CALCULATE_INIT_PTP_VS_CLOCK_DIFF	3.5e-08f
#define PTP_PENDING_PHASE_LAG_NOISE_LEVEL_LOW			1.0e-7f
#define PTP_PENDING_PHASE_LAG_NOISE_LEVEL_HIG			1.0e-6f			
#define PTP_PENDING_PHASE_LAG_RANGE_LOW_NOISE			5.0e-7f
#define PTP_PENDING_PHASE_LAG_RANGE_HIG_NOISE			1.0e-7f
#define PTP_PENDING_PHASE_LAG_APPLY_PERIOD				(5*60*SLOW_TICKS_PER_SECOND)

#define COHERENT_HYBRID_QUIET_NOISE_LEVEL				2.0e-8f
#define COHERENT_HYBRID_SUB_QUIET_NOISE_LEVEL			3.5e-8f
#define COHERENT_HYBRID_USE_PHASE_LAG_NOISE_LEVEL_0		2.0e-8f
#define COHERENT_HYBRID_USE_PHASE_LAG_NOISE_LEVEL_1		7.0e-8f
#define COHERENT_HYBRID_USE_PHASE_LAG_NOISE_LEVEL_2		1.0e-6f
#define COHERENT_HYBRID_USE_PHASE_LAG_WEIGHT_0			1.0f
#define COHERENT_HYBRID_USE_PHASE_LAG_WEIGHT_1			10.0f
#define COHERENT_HYBRID_USE_PHASE_LAG_WEIGHT_2			100.0f
#define MAX_PHASE_CHANGE_PER_PERIOD						5.0e-9f
#define MAX_PHASE_CHANGE_PER_MAXIMUM_SKIPPED_PERIOD		2.5e-8f
#define COHERENT_HYBRID_NUMBER_QUIET_PERIOD				2				

#define QUIET_NETWORK_NOISE_LEVEL						1.5e-08f
#define TICKS_IN_QUIET_NETWORK_FOR_INITIAL_ERROR_UPDATE	(60*60*SLOW_TICKS_PER_SECOND)
#define MINIMUM_INITIAL_ERROR_UPDATE_INTERVAL			(60*60*SLOW_TICKS_PER_SECOND)
#define MAXIMUM_INITIAL_ERROR_UPDATE_PHASE_LAG			1.5e-07f

#define ADJUSTMENT_PERIOD_FOR_INITIAL_ERROR				(10*60*SLOW_TICKS_PER_SECOND)

#define PHASE_OFFSET_FILTER_COEF						0.96f

typedef enum
{
	noPhaseBuildOut = 0,
	fullPhaseBuildOut,
	smoothPhasePullIn
} PhaseBuildOutType;

typedef struct
{
	Bool						phaseBuildOutEnable;
	PhaseBuildOutType			phaseBuildOutType;

	uint						phasePullInPeriod;
	uint						actualPhasePullInPeriod;
	uint						phasePullInCountDown;
	
	IEEE1588Time				phaseBuildOut;
	ElapsedTime					targetPhasePullIn;	
	ElapsedTime					phasePullInMaxPhaseDiff;
	ElapsedTime					maximumPhaseChangeRateSecondPerSecond;

	TimeReferenceSource*		PBOSource;						//This is the source on top of which to do PBO, i.e., the new source
	TimeReferenceSource*		PBOAgainstedSource;				//THis is the source PBO to build against with, i.e., the old source

	//specific for phase build on clock following the failure of ptp under congruent hybrid
	Bool						clockFrequencyTrackingWithErrorCorrection;
	Frequency					clockFrequencyError;

}PhaseBuildOutControl;

typedef struct
{
	ElapsedTime					aveRemainingPtpVsClockError[REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE];
	float						weight[REMAIN_PTP_VS_CLOCK_ERROR_BUFFER_SIZE];
	ElapsedTime					accumulatedQuietRemainingError;
	ElapsedTime					accumulatedSubQuietRemainingError;
	ElapsedTime					quietPeriodRemainingError;
	ElapsedTime					initialPtpVsClockError;
	ElapsedTime					initialPtpVsClockErrorExcludingPendingPhaseLag;
	ElapsedTime					averagedInitPtpVsClockError;
	ElapsedTime					ptpPendingPhaseLag;
	ElapsedTime					averagedRemainingError;
	ElapsedTime					averagingWeights;
	ElapsedTime					remainingPtpVsClockError;
	ElapsedTime					lastRemainingError;
	ElapsedTime					newRemainingError;

	ElapsedTime					phaseOffset;

	TimeReferenceSource*		hybridPtpTRS;
	TimeReferenceSource*		hybridClockTRS;

	uint						ticksSinceInitialiseCoherentHybrid;
	uint						nextSampleIndex;
	uint						numberOfValidSamples;
	uint						averagingPeriodTickCounter;	
	uint						numberOfSkippedUpdate;
	uint						quietPeriodTickCounter;
	uint						subQuietTickCounter;
	
	uint						ticksSinceLastQuietPeriodErrorUpdate;
	uint						ptpPendingPhaseLagTickToFullApply;

	uint						consecutiveQuietPeriods;
	
	Bool						coherentHyridOn;
	Bool						initialPtpVsClockErrorComputed;	
	Bool						useAvergedInitPtpVsClockError;
} CoherentHybridProcess;


typedef struct 
{
	ClockId						nodeTimeClockId;

	Bool						sourceHasSwitched;
	Bool						fastTrackingEnabled;	// if TRUE then node time frequency tracks input sources at faster rate

	TimeReferenceSelector*		timeReferenceSelector;
	TimeReferenceSource*		nodeTimeTrackingTRS;				//This is the timeReferenceSource which nodeTime is currently tracking, if not in holdover state

	PhaseBuildOutControl		PBOControl;
	CoherentHybridProcess		coherentHybridProcess;

	// Components
	HoldoverController			holdoverController;
	BinaryLockMonitor			binaryLockMonitor;

	AlarmClient					alarmClient;

} NodeTimeController;


void InitialiseNodeTimeController(NodeTimeController* ntc, ClockId clockId, TimeReferenceSelector* trs, 
		struct AlarmMonitorStruct* alarmMonitor, ElapsedTime slowTickPeriod);
void SlowTickNodeTimeController(NodeTimeController* ntc);

void FastTickNodeTimeController(NodeTimeController* ntc);

/**
 * \fn NodeTimeSetPhaseBuildOutEnable
 * Enables or disables phase build out
 * When enabled switching from current source will maintain existing phase output
 * even if new source differs in phase.
 *
 * \return
 * 		TRUE:  Enable / Disable succeeded
 * 		FALSE: The enable / disable failed
 */
Bool NodeTimeSetPhaseBuildOutEnable(NodeTimeController* ntc, Bool enable);

void PrintNodeSummary952x(NodeTimeController* ntc, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintNodeDetails952x(NodeTimeController* ntc, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintNodeDebug952x(NodeTimeController* ntc, uint8 index, char** ptrptr, long *bufferSize, Bool title);


#ifdef __cplusplus
}
#endif

#endif
