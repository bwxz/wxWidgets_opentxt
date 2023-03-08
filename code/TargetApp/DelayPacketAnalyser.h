#ifndef DELAY_PACKET_ANALYSER_H
#define DELAY_PACKET_ANALYSER_H

#include "General.h"
#include "TopSyncInterfaceTypes.h"
#include "TimeReferenceSource.h"


#ifdef __cplusplus
extern "C" {
#endif

#define MIN_DPA_EXP_FILTER_COEFFICIENT			0.995f
#define	MAX_DPA_EXP_FILTER_COEFFICIENT			0.99975f
#define JUMP_DPA_EXP_FILTER_COEFFICIENT			0.99990f				//used when there is positive jump	
#define ABSOLUTE_MIN_EXP_FILTER_COEFFICIENT		0.7f

#define MIN_SLIDING_WINDOW_IN_TIME				MINIMUM_SLIDING_WINDOW_SIZE_IN_SEC
#define MAX_SLIDING_WINDOW_IN_TIME				MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC

#define MAX_BANDWIDTH_BASED_WINDOW_LENGTH		MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC
#define MIN_BANDWIDTH_BASED_WINDOW_LENGTH		(MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC/2)
#define BANDWIDTH_FOR_MAX_WINDOW_LENGTH			2.0e-03f
#define BANDWIDTH_FOR_MIN_WINDOW_LENGTH			4.0e-03f

#define MAXIMUM_NUMBER_OF_SEGMENTS				3

#define DEFAULT_LOG_UPDATE_PERIOD				(-5)
#define DEFAULT_NUMBER_OF_SAMPLES_PER_SECOND	32
#define DELAY_PACKET_ANALYSER_BUF_SIZE			490		//8*60+10. At 8 samples per second and for maximum of 60 seconds 
														
#define NOISE_SAMPLE_BUFFER_SIZE				1
#define ABSOLUTE_SAMPLE_DIFF_BUFFER_SIZE		8

#define	NOISE_FLOOR_DEV_DPA						1.0e-9f

#define	PERIOD_0_AFTER_CAL_B					(1*SLOW_TICKS_PER_SECOND)			//unit of slow tick, or 1 seconds
#define	PERIOD_1_AFTER_CAL_B					(240*SLOW_TICKS_PER_SECOND)		//unit of slow tick
#define	PERIOD_AFTER_CAL_B						(900*SLOW_TICKS_PER_SECOND)		//unit of slow tick
#define MAX_AGE_OF_PHASE								(MAX_SLIDING_WINDOW_IN_TIME*SLOW_TICKS_PER_SECOND)
#define NUMBER_TICKS_BEFORE_APPLYING_POST_PROCESSING	(300*SLOW_TICKS_PER_SECOND)		//5 minutes
#define NUMBER_TICKS_BEFORE_APPLYING_NOISE_COMPEN		(300*SLOW_TICKS_PER_SECOND)
#define NUMBER_TICKS_BEFORE_APPLYING_TRAFFIC_COMPRESS	(300*SLOW_TICKS_PER_SECOND)
#define NUMBER_TICKS_BEFORE_APPLYING_PATH_SELECT		(120*SLOW_TICKS_PER_SECOND)
#define NUMBER_TICKS_BEFORE_APPLYING_RTD_COMPEN			(60*SLOW_TICKS_PER_SECOND)
#define NUMBER_TICKS_BEFORE_ENABLE_POST_PROCESSING		(30*SLOW_TICKS_PER_SECOND)

#define RE_ROUTE_DELAY_JUMP_THRESH_0			25.0e-06f
#define RE_ROUTE_DELAY_JUMP_THRESH_1			50.0e-06f
#define RE_ROUTE_DELAY_JUMP_THRESH_2			80.0e-06f
#define RE_ROUTE_DELAY_JUMP_THRESH_3			120.0e-06f
#define HUGE_DELAY_JUMP_UP_FADING_OUT_PERIOD	(90*SLOW_TICKS_PER_SECOND)
#define HUGE_DELAY_JUMP_DN_FADING_OUT_PERIOD	HUGE_DELAY_JUMP_UP_FADING_OUT_PERIOD		//if both direction jump, negative jump detected early
#define USE_DN_JUMPED_MINIMUM_PERIOD			(5*SLOW_TICKS_PER_SECOND)
#define DELAY_JUMP_THRESH						6.0e-06f
#define DELAY_JUMP_FADING_OUT_PERIOD			(210*SLOW_TICKS_PER_SECOND)	
#define MICRO_SEC_DELAY_JUMP_THRESH				1.0e-06f
#define MICRO_SEC_DELAY_JUMP_FADING_OUT_PERIOD	(210*SLOW_TICKS_PER_SECOND)	
#define SMALL_DELAY_JUMP_THRESH					0.5e-06f
#define SMALL_DELAY_JUMP_FADING_OUT_PERIOD		(300*SLOW_TICKS_PER_SECOND)	
#define MEDIAN_DELAY_JUMP_THRESH				6.0e-06f
#define MEDIAN_DELAY_JUMP_FADING_OUT_PERIOD		(210*SLOW_TICKS_PER_SECOND)
#define NO_DELAY_JUMP							0
#define POSITIVE_DELAY_JUMP						1
#define NEGATIVE_DELAY_JUMP						-1
#define NOISE_LEVEL_FOR_MIN_WINDOW				2.5e-08f
#define NOISE_LEVEL_FOR_MAX_WINDOW				1.5e-07f
#define TRIGGERING_DELAY_JUMP					(2.5*DELAY_JUMP_THRESH)

#define NUMBER_SUB_MINIMUMS						16
#define DEFAULT_NUMBER_SIDE_POINTS				3
#define DEFAULT_CENTRAL_MEDIAN_POINT_INDEX		(NUMBER_SUB_MINIMUMS - DEFAULT_NUMBER_SIDE_POINTS - 1)
#define NUMBER_SUB_MINIMUMS_INCREASE_STEP		1

#define AVERAGE_FILTER_BUFFER_SIZE				10
#define SECONDS_AVERAGE_PERIOD					15
#define TICKS_AVERAGE_PERIOD					(SECONDS_AVERAGE_PERIOD*SLOW_TICKS_PER_SECOND)
#define NUMBER_MAX_SAMPLE_BUFFER_SIZE			10
#define NUMBER_MIN_SAMPLE_BUFFER_SIZE			5
#define LONG_TERM_AVERAGE_DELAY_HIG_FILTER_COEF	0.99
#define LONG_TERM_AVERAGE_DELAY_LOW_FILTER_COEF	0.9999

//#define PRINT_MIN_MAX_RECENT_SAMPLES

typedef struct
{
	Bool				enabled;
	uint				numberSkippedSamples;
	uint				remainingTicksBeforeClearNumberSkippedSamples;

	uint				timerAfterSkipSample;
	ElapsedTime			minSparseDelayJump;

} SparseDelayFilter;


typedef struct
{	
	ElapsedTime			noiseSamplePrevious;	
	ElapsedTime			noiseSampleLatest;
	ElapsedTime			sampleDiffBuffer[ABSOLUTE_SAMPLE_DIFF_BUFFER_SIZE];

	ElapsedTime			noiseDev;
	
	uint				sampleDiffBufPtr;
	uint				numSampleDiffInBuffer;

	Bool				noiseValueValid;
	Bool				reinitialiseNoiseValue;
	Bool				previousSampleValid;
	uint				countDownSkipNoiseUpdate;

	AlarmClient			heavyPdvAlarm;

}DPANoiseAnalyser;

typedef struct
{
	ElapsedTime			DPA_buffer[DELAY_PACKET_ANALYSER_BUF_SIZE];
	ElapsedTime			decimatedMinimumSample;

	ElapsedTime			minimum;
	ElapsedTime			median;
	
	//the previous minimum and median detail
	ElapsedTime			subMinimum[NUMBER_SUB_MINIMUMS];
	uint				positionOfCurrentSubMinimum[NUMBER_SUB_MINIMUMS];
	uint				numberValidSubMinimums;								//from the least to the most
	Bool				currentSubMinimumIsNew[NUMBER_SUB_MINIMUMS];
	Bool				disableSubMinimumSearch;
	
	uint				medianPointIndexInSubMinimums;
	uint				numberSideSubminimumsForAveraging;

	uint                nominalPacketRate;
	uint                actualPacketRate;

	//the parameter for actualPacketRate calculation	
	uint				numberPacketsReceivedCurrentMinute;

	uint				sampleCountForDecimation;
	uint				decimationFactor;
	
	uint				inPtr;

	uint				tickCountSinceLastSampleReceived;
	uint				tickCountSinceLastNewMinimumOutput;
	uint				numberOfNewMinimumSinceNewMinimumInOtherDirection;
	uint				numberOfValidSampleInBuffer;

	uint				maxSlidingWindowInSec;
	uint				slidingWindowInTime;
	uint				slidingWindowInSample;

	uint				positionOfCurrentMinimumInBuffer;
	uint				positionOfCurrentMedianInBuffer;
		
	uint				ageOfCurrentMinimum;
	uint				ageOfCurrentMedian;

	uint				ticksForNextMinimumAgeingUpdate;
	uint				ticksForNextMedianAgeingUpdate;

	Bool				currentMinimumIsNew;
	Bool				currentMedianIsNew;

	Bool				outputIsValid;
	Bool				outputMedianIsValid;

	Bool				newMinimumDelayFound;		//this parameter will be used to assist roundTripDelay calculation
	Bool				newMedianDelayFound;
	Bool				dropCurrentMinimum;

	SparseDelayFilter	sparseDelayFilter;

}DPAPacketFilter;

typedef struct
{
	ElapsedTime				periodAverage_buffer[AVERAGE_FILTER_BUFFER_SIZE];
	ElapsedTime				currentPeriodAverage;
	ElapsedTime				averagePacketDelay;
	ElapsedTime				currentMax[NUMBER_MAX_SAMPLE_BUFFER_SIZE];
	ElapsedTime				currentMin[NUMBER_MIN_SAMPLE_BUFFER_SIZE];

	ElapsedTime				outputAverageFilter;

	uint					averageIndex;
	uint					numberSamplesCurrentAverage;
	uint					ticksAveragePeriod;
	uint					numberAverages;

	Bool					outputValid;

	//debugging
	uint					outlinerDiscarded;

}AveragePacketFilter;

typedef struct
{
	DPAPacketFilter			packetFilter;
	ElapsedTime				mostRecentPacketDelay;

#ifdef PRINT_MIN_MAX_RECENT_SAMPLES
	ElapsedTime				minMostRecentPacketDelay;
	ElapsedTime				maxMostRecentPacketDelay;
#endif

	ElapsedTime				outputMin;
	ElapsedTime				outputMedian;

	double					filterCoeff;

	DPANoiseAnalyser		networkPdvAnalyser;
	DPANoiseAnalyser		noiseAnalyser;
	DPANoiseAnalyser		medianNoiseAnalyser;
	DPANoiseAnalyser		averageNoiseAnalyser;

	ElapsedTime				medianMinusMinimum;

	LogMessagePeriod		logUpdatePeriod;

	Bool					isFirstDelayValue;	
	Bool					isFirstMedianDelayValue;
	Bool					medianMinusMinimusInitialised;

	ElapsedTime				outputAt30Sec;
	ElapsedTime				outputAt60Sec;
	uint					ticks60Sec;
	uint					countDownAfterSmallDelayJump;		//these are used for noise based PLL control
	Bool					smallDelayJumpHappened;				//these are used for noise based PLL control
	Bool					skipSmallDelayJumpCheck;

	uint					countDownAfterHugeDelayJump;
	uint					countDownAfterMicroSecDelayJump;		//these are used for RTD delay compen
	int						microSecDelayJumpHappened;				//these are used for RTD delay compen, value -1, 0, 1

	uint					countDownAfterMedianDelayJump;
	uint					countDownAfterDelayJump;
	
	uint					ticksNoHugeDelayJumpCheck;				//when non-zero, don't huge delay jump check

	int						medianDelayJumpHappened;	//3-value variable. -1=jump down; 0=no jump, +1=jump up;
	int						hugeDelayJumpHappened;		//3-value variable. -1=jump down; 0=no jump, +1=jump up;
	int						delayJumpHappened;			//3-value variable. -1=jump down; 0=no jump, +1=jump up;
	ElapsedTime				delayJump;					//actual median delay jump value
	ElapsedTime				hugeDelayJump;				//actual huge delay jump value
	ElapsedTime				microSecDelayJump;				//actual micro delay jump value
	ElapsedTime				medianDelayJump;			//median delay filter output's delay jump

	AveragePacketFilter		averagePacketFilter;
	
	AlarmClient				packetDelayJumpAlarm;
	
}DelayPacketAnalyser;

void InitialiseDelayPacketAnalyser(DelayPacketAnalyser *dpa, AlarmSource alarmSource0, AlarmSourceIdentity alarmSourceIdentity0,
					AlarmSource alarmSource1, AlarmSourceIdentity alarmSourceIdentity1,struct AlarmMonitorStruct* alarmMonitor);
void ResetDelayPacketAnalyser(DelayPacketAnalyser *dpa);

void DelayReceivedDPA(DelayPacketAnalyser *dpa, ElapsedTime delay, Bool active, float lock, Bool initialAlignment, Bool doAverageFiltering, ElapsedTime delayOffset, DelayPacketAnalyser *dpa2, ElapsedTime *delayJumpUpBothDir);
void SlowTickDPAnalyser(DelayPacketAnalyser *dpa, TimeRSState state, float lock, LogMessagePeriod logUpdatePeriod, Frequency lockedPllBandwidth, Frequency lockedBandwidth, Frequency unlockedBandwidth, Signal noiseMax, Bool adaptiveWindowLength, Bool doAverageFiltering);
void SetFilterCoefficientDPA(DelayPacketAnalyser *dpa, float lock, Frequency lockedBandwidth, Frequency unlockedBandwidth);
void SetSlidingWindowSize(DelayPacketAnalyser *dpa, float lock, Signal noiseMax, Frequency lockedPllBandwidth, Bool adaptiveWindowLength);
void PhaseShiftDPAnalyser(DelayPacketAnalyser *dpa, ElapsedTime shift);

#define DataValidDPAnalyser(dpa) ((dpa)->packetFilter.outputIsValid)
#define DataValidMedianDPAnalyser(dpa) ((dpa)->packetFilter.outputMedianIsValid)
#define NoiseDPAnalyser(dpa)	((dpa)->noiseAnalyser.noiseDev)
#define	ValueDPANA(analyser) ((analyser)->noiseDev)
#define NoiseValidDPAnalyser(dpa)	((dpa)->noiseAnalyser.noiseValueValid)
#define ValueDPAnalyser(dpa) ((dpa)->outputMin)
#define CompensatedValueDPAnalyser	ValueDPAnalyser

#define AgeOfValueDPAnalyser(dpa) ((dpa)->packetFilter.ageOfCurrentMinimum)
#define GetMostRecentPacketDelayDPA(dpa) ((dpa)->mostRecentPacketDelay)
#define SetDpaNoiseDev(dpa, value) ((dpa)->noiseAnalyser.noiseDev = value)

#define SmallDelayJumpHappened(dpa) ((dpa)->smallDelayJumpHappened)
#define MicroSecDelayJumpHappened(dpa) ((dpa)->microSecDelayJumpHappened)
#define DelayJumpHappened(dpa) ((dpa)->delayJumpHappened)
#define HugeDelayJumpHappened(dpa) ((dpa)->hugeDelayJumpHappened)

#define SetFirstMedianDelayValueFlag(dpa, value) ((dpa)->isFirstMedianDelayValue = value)
#define MedianDelayJumpHappened(dpa) ((dpa)->MedianDelayJumpHappened)
#define MedianNoiseAnalyser(dpa) ((dpa)->medianNoiseAnalyser.noiseDev)

#define SetSlidingWindowSizeInSample(dpa, value) ((dpa)->packetFilter.slidingWindowInSample = value)

#ifdef __cplusplus
}
#endif


#endif
