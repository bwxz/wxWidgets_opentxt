#ifndef CURRENT_MASTER_PHASE_LAG_PROCESSING_H
#define CURRENT_MASTER_PHASE_LAG_PROCESSING_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "CurrentMasterDirection.h"
#include "MessageStore.h"
#include "TimeReferenceSource.h"
#include "TimeReferenceSelector.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INI_TICKS_TEMP_HOLD_OVER_DISABLED				(30*60*SLOW_TICKS_PER_SECOND)		//1800 secs

#define ROUND_TRIP_BUFFER_SIZE					30
#define MINIMUM_ROUND_TRIP_SAMPLE_INTERVAL		(3600*SLOW_TICKS_PER_SECOND)				//one hour per minimum sample
#define MINIMUM_ROUND_TRIP_BUFFER_SIZE			24											//correspond to 24 hours
#define TIME_TO_USE_SECOND_GLOBAL_MINIMUM		6											//6 hours after started

#define SINGLE_PATH_DELAY_SAMPLE_PERIOD_IN_SEC	10
#define SINGLE_PATH_DELAY_BUFFER_LENGTH_IN_SEC	60
#define SINGLE_PATH_DELAY_BUFFER_SIZE			(SINGLE_PATH_DELAY_BUFFER_LENGTH_IN_SEC/SINGLE_PATH_DELAY_SAMPLE_PERIOD_IN_SEC)			

#define NEAR_TERM_FLOOR_ARRAY_SIZE				3				

#define NEAR_TERM_FLOOR_SAMPLE_PERIOD_IN_SEC	(1*60)			//1 minutes
#define NEAR_TREM_FLOOR_TICKS_NUMBER			(NEAR_TERM_FLOOR_SAMPLE_PERIOD_IN_SEC*SLOW_TICKS_PER_SECOND)

#define HISTORY_RTD_BUFFER_SIZE					5				//in unit of 1 minute per sample

//Parameter relating phaseLag freshness processing
#define MIN_PHASE_LAG_FADING_START_AGE			(0*SLOW_TICKS_PER_SECOND)
#define MIN_PHASE_LAG_FADING_START_AGE_TCXO		(2*SLOW_TICKS_PER_SECOND)
#define MIN_PHASE_LAG_ATTENUATION_COEF			0.20f
#define MAX_PHASE_LAG_ATTENUATION_COEF			0.30f

#define PHASE_LAG_FADING_COEF				0.985f
#define PHASE_LAG_FADING_COEF_SLOW			0.99f
#define PHASE_LAG_FADING_COEF_FAST			0.96f
#define PHASE_LAG_FADING_COEF_SINGLE		0.98f

//#define	BEBUG_IDEAL_CLOCK_ERROR_ESTIMATION
typedef struct
{
	Bool					accuracyEstimateValid;
	ElapsedTime				ptpPhaseAccuracy;

} PtpPhaseAccuracyEstimate;

typedef struct
{
	uint					ticksSinceLastProtectiveHoldoverEnforced;
	uint					ticksInContinuousProtectiveHoldover;
	uint					ticksRemainingNoProtectiveHoldover;
} ProtectiveHoldoverControl;

typedef struct
{
	MedianDelayState		medianDelayState;				//medianDelayAdaptive = adaptive, medianDelayOnly=UseItSolely, medianDelayOff=notUseIt
		
	Bool					useMedianDelay;
	Bool					compenMedianIsInitialised;
	Bool					smoothedMedianRTDIsInitialised;
	uint					ticksSinceMedianSelected;
	uint					ticksSinceMininumSelected;
	uint					RTDJumped;

	ElapsedTime				compenMedian;
	ElapsedTime				smoothedMedianRTD;
		
} MedianDelayControl;

typedef struct
{
	ElapsedTime				referenceNoise;										//for either m2s or s2m
	ElapsedTime				referenceDelay;	
} PathFloors;


typedef struct
{
	Bool					pathSelectionEnabled;

	Direction				directionToUse;			//0=both, 1=M2S, 2=S2M
	Direction				lastSingleDirection;

	uint					tickDirectionToUseNotChanged;
	ElapsedTime				averageFilterRTD;
	Bool					averageFilterRTDInitialised;

	PathFloors				pathFloors;

} PathSelectionControl;

typedef struct
{
	Bool					RTDCompensationEnabled;
	Bool					pathDelayInitialised;
	Bool					clockErrorEstimateInitialised;
	
	int						bufferRTDIdx;
	int						bufferMinimumRTDIdx;
	
	int						tickCountMinimumRTD;						//one hour timer for minimumRND buffering
	int						ageOnPhaseLag;								//age applied on phaseLag
	
	ElapsedTime				bufferRTD[ROUND_TRIP_BUFFER_SIZE];
	ElapsedTime				bufferMinimumRTD[MINIMUM_ROUND_TRIP_BUFFER_SIZE];
	ElapsedTime				recentMinimumRTD;
	ElapsedTime				globalMinimumRTD;
	ElapsedTime				compenRTD;

	ElapsedTime				latestRTD;
	ElapsedTime				latestRawRTD;	

	ElapsedTime				msPathDelay;						//an estimation of "pure" path delay
	ElapsedTime				smPathDelay;

	ElapsedTime				msNoiseFloor;						
	ElapsedTime				smNoiseFloor;

	ElapsedTime				clockErrorEstimated;	
	ElapsedTime				rtdHistory[HISTORY_RTD_BUFFER_SIZE];
	ElapsedTime				maxRtdInRecentHistory;

	int						rtdHistoryIndex;
	int						rtdUpdateTickCounter;

	int						numberOfValidSamples;
	int						numberOfValidMinimumSamples;
	int						quietNetworkDurationTickCount;		//consecutive quiet network (both dir) period count
	int						bothDirectionPathIncreasedTickCount;

	uint					RTDIncreasedUpdated;				//timer to avoid repeatedly increase RTD
	
} RTDCompensation;

typedef struct
{
	Bool					noiseCompenEnabled;
	ElapsedTime				compenDev;
	ElapsedTime				remainLevelScaledPhaseLag;
	uint					phaseScalingFactor;
} NoiseCompensation;


typedef struct 
{	
	Bool							disablePhaseCompensationAlgorithm;
	uint							algorithmMutingPeriodAfterConfiguredPhaseLagChanged;

	NoiseCompensation				noiseCompen;
	RTDCompensation					RTDCompen;
	PathSelectionControl			pathSelectionController;
	MedianDelayControl				medianDelayController;
	ProtectiveHoldoverControl		protectiveHoldoverController;

	//phase output accuracy estimate
	PtpPhaseAccuracyEstimate		ptpPhaseAccuracyEstimator;

	//final phaseLag and the corresponding low path filter coef
	Bool							phaseLagFilterOff;
	ElapsedTime						phaseLag;						//final phaseLag
	ElapsedTime						phaseLagSinglePath;				//single path based phaseLag
	ElapsedTime						rawPhaseLag;
	ElapsedTime						rawMedianPhaseLag;

	ElapsedTime						rawAverageFilterPhaseLag;
	ElapsedTime						phaseLagSinglePathAverageFilter;	

	float							filterCoef;

	float							fadingCoef;					//fading coef used in phaseLag freshness calculation
	float							fadingCoef_single;			//fading coef used in phaseLag freshness calculation
	float							noFadingBelowThisThresh;	//

	uint							fadingStartAge;

} CurrentMasterPostProcessing;			//currentMaster level packetAnalyser related post processing(at the moment, only relevant to DPA alg)

void ReRouteDelayJumpPhaseLagPostProcess(CurrentMasterPostProcessing *ppp, ElapsedTime shift);

#ifdef __cplusplus
}
#endif

#endif

