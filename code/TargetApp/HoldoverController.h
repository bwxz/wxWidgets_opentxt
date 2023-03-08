#ifndef HOLDOVER_CONTROLLER_H
#define HOLDOVER_CONTROLLER_H

#include "ToPSyncTypes.h"
#include "History.h"
#include "UTCOffsetController.h"
#include "AlarmClient.h"

#define SHORT_PERIOD_IN_SECOND				120									//two minute
#define	HISTORY_FREQ_PER_SHORT_PERIOD		(SHORT_PERIOD_IN_SECOND*SLOW_TICKS_PER_SECOND)			
#define HISTORY_FREQ_PER_SHORT_BUFFER_SIZE	5									//Total of 10 minutes

#define LONG_PERIOD_IN_SECOND				600									//10 minute
#define	HISTORY_FREQ_PER_LONG_PERIOD		(LONG_PERIOD_IN_SECOND*SLOW_TICKS_PER_SECOND)			
#define HISTORY_FREQ_PER_LONG_BUFFER_SIZE	37			//one sample per 10 minutes, so total of 6 hours 10 minutes

#define EXTRA_PERIOD_IN_HOUR				2
#define EXTRA_PERIOD_IN_SECOND				(EXTRA_PERIOD_IN_HOUR*3600)
#define HISTORY_FREQ_PER_EXTRA_PERIOD		(EXTRA_PERIOD_IN_SECOND*SLOW_TICKS_PER_SECOND) 
#define HISTORY_FREQ_PER_EXTRA_BUFFER_SIZE	(74/EXTRA_PERIOD_IN_HOUR)			//a total of 74 hours

#define HOLDOVER_BACKWARD_NUMBER_OF_HISTORY_DATA			1
#define MINIMUM_HOLDOVER_TRIGGERING_NOISE_LEVEL				1.0e-6f
#define DEFAULT_HOLDOVER_TRIGGERING_NOISE_LEVEL				10.0e-6f

#define FIRST_ORDER_FITTING
//#define NEW_HLD_ALGORITHM

#ifdef __cplusplus
extern "C"
{
#endif

struct TimeReferenceSourceStruct;

typedef struct 
{
	// configuration
	Bool		forceHoldover;		//When this flag is set, the source will go into holdover unconditionally.
	
	ElapsedTime tickPeriod;
	uint32 holdOverDurationTicks;  // before clockQuality drops

	ReferenceClock heldoverSource;

	//Operation
	ElapsedTime historyFreqPerShortPeriod[HISTORY_FREQ_PER_SHORT_BUFFER_SIZE];
	ElapsedTime historyFreqPerLongPeriod[HISTORY_FREQ_PER_LONG_BUFFER_SIZE];
	ElapsedTime historyFreqPerExtraPeriod[HISTORY_FREQ_PER_EXTRA_BUFFER_SIZE];

	ElapsedTime freqShortPeriod;
	ElapsedTime freqLongPeriod;
	ElapsedTime freqExtraPeriod;

#ifdef FIRST_ORDER_FITTING
	ElapsedTime agingFreqHour_00_24;			//aging freq in the past (0 - 24) hours
//	ElapsedTime agingFreqHour_12_36;			//aging freq in the past (12 - 36) hours
	ElapsedTime agingFreqHour_00_48;			//aging freq in the past (00 - 48) hours

	ElapsedTime agingFreqHour_24_48;			//aging freq in the past (24 - 48) hours
	
	ElapsedTime agingFreqHour_48_72;			//aging freq in the past (48 - 72) hours

	ElapsedTime agingOffset_00_24;
	
	ElapsedTime futureAgingFreq_AT_00;		//aging frequency at 0 (the start of holdover)

#ifndef NEW_HLD_ALGORITHM
	ElapsedTime futureAgingFreq_00_06;		//predicted aging freq in the future (0-6) hours
	ElapsedTime futureAgingFreq_06_12;		//predicted aging freq in the future (6-12) hours 
	ElapsedTime futureAgingFreq_12_18;		//predicted aging freq in the future (12-18) hours and thereafter
	ElapsedTime futureAgingFreq_18_24;		//predicted aging freq in the future (18-24) hours and thereafter
#else
	ElapsedTime agingFreqAtHourPoint;							//0 order
	ElapsedTime freqChangePerSecFromAging;						//1st order
	ElapsedTime changePerHourForFreqChangePerSecFromAging;		//2nd order (00-12 hours)
	ElapsedTime changePerHourForFreqChangePerSecFromAging2;		//2nd order (12-24 hours)
	ElapsedTime	freqChangePerSecFromAgingHigherBound;
	ElapsedTime	freqChangePerSecFromAgingLowerBound;
#endif

	ElapsedTime holdoverFreqAtEndOfDateBack;

#else
	ElapsedTime a0;
	ElapsedTime a1;
	ElapsedTime a2;

	ElapsedTime timeAtStartOfHoldover;
#endif

	ElapsedTime outputFreq;
	
	ElapsedTime	safeguardHoldoverTriggeringNoiseLevel;

	uint32  ticksShortPeriod;		//one minute-period counter
	uint32  ticksLongPeriod;		//five minute-period counter
	uint32	ticksExtraPeriod;		//extra-period counter

	float	ageHistoryFreqLongPeriod[HISTORY_FREQ_PER_LONG_BUFFER_SIZE];
	float	ageHistoryFreqExtraPeriod[HISTORY_FREQ_PER_EXTRA_BUFFER_SIZE];

	uint8	indexToNextFreqInShortBuffer;
	uint8	indexToNextFreqInLongBuffer;
	uint8	indexToNextFreqInExtraBuffer;

	uint8	numberFreqSamplesInShortBuffer;		//one minute averaged buffer
	uint8	numberFreqSamplesInLongBuffer;		//five minutes averaged buffer
	uint8	numberFreqSamplesInExtraBuffer;		//extra period averaged bufer

	AlarmClient inHoldoverAlarm;

	//Control
	Bool	agingEstimateIsValid;
	Bool	inHoldover;							//in holdover when PTP or clock input is lost
	Bool	inProtectiveHoldover;					//in holdover due to high noisy network connection, invalid for clock source

	uint32  ticksInHoldover;  // when ticksInHoldover reaches holdOverDurationTicks becomes localOscillator
	uint32	ticksInLastHoldover;		//this records the last holdover ticks

	ClockStratum clockClassOnEnteringHoldover;
	ClockStratum clockClassReducedAfterHoldoverPeriod;

	Bool 	changeGMIDInHoldover; // when TRUE the transmitted GMID should be set to the local ID
								  // when holdver is active
} HoldoverController;

#define HFC_MIN_HOLDOVER_VALID 0.7f

void InitialiseHFC(
	HoldoverController* hld,
	uint32 maxAveragingPeriodSecs,  
	uint32 defaultAveragingPeriodSecs,
	ElapsedTime minTimeToValid,
	ElapsedTime maxTimeToValid,
	ElapsedTime holdoverDuration, // before clock quality becomes localOscillator
	struct AlarmMonitorStruct* alarmMonitor,
	AlarmSourceIdentity identity,
	ElapsedTime samplePeriod,
	ElapsedTime tickPeriod
);

void ResetHFC(HoldoverController* hld);
void ResetHFCHistory(HoldoverController* hld);
void TickHFC(HoldoverController* hld);

void LeaveHoldoverHFC(HoldoverController* hld);
void EnterHoldoverHFC(HoldoverController* hld, Bool protectiveHoldover);
void UpdateClockReferenceHFC(HoldoverController* hld, ReferenceClock const* source);
void NewReferenceUsedByNodeHFC(HoldoverController* hld, struct TimeReferenceSourceStruct const* nodeCurrentTimeReferenceSource);
void HoldoverControllerTRSelectorChanged(HoldoverController* hld,PLLid newPllId);
void RemoveLatestHoldoverData(HoldoverController* hld, uint numberOfLongSamplesToRemove);

void SetHoldoverDuration(HoldoverController* hld, ElapsedTime duration);
void ShiftHoldoverFrequency(HoldoverController* hld, Frequency shift);
ElapsedTime GetHoldoverDuration(const HoldoverController* hld);

#define GetHoldoverPll(hld) ((hld)->holdoverPll)

void InputHFC(HoldoverController* hld, Frequency input);

Frequency GetHoldoverFrequency(HoldoverController const* hld);
float HoldoverValid(HoldoverController const* hld); 
#define IsHoldoverValidBoolean(hld) (HoldoverValid(hld) >= HFC_MIN_HOLDOVER_VALID)
// suffient data stored - including from previous references

void PrintHoldoverController(HoldoverController const* hld, char** ptrptr, Bool printTitle);

void InvalidateRecentHFCData(HoldoverController *hld, ElapsedTime invalidateTime);

void SetLocalReferenceClockHFC(HoldoverController* hld, ReferenceClock const* localOscillator);
#define GetTimeReferenceSourceHFC(hld) ((hld)->timeReferenceSource[hld->holdoverPll])
#define GetLocalReferenceClockHFC(hld) (&(hld)->localOscillator)
void SetReductionInClockStratum(HoldoverController* hld, ClockStratum reduction);

#ifdef __cplusplus
}
#endif


#endif

