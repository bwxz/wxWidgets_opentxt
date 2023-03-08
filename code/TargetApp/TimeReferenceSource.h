/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this
 * file is owned by Semtech Corporation (Semtech). This is an
 * unpublished work.  The content of this file must be used only for
 * the purpose for which it was supplied by Semtech or its
 * distributors. The content  of this file must not be copied or
 * disclosed unless authorised in writing by Semtech.
 */
#ifndef TIME_REFERENCE_SOURCE_H
#define TIME_REFERENCE_SOURCE_H

#include "ToPSyncTypes.h"
#include "IEEE1588Time.h"
#include "HighRangeFilter.h"

#include "LockDetector.h"
#include "BinaryLockMonitor.h"
#include "EpochController.h"
#include "FrequencyController.h"
#include "HoldoverController.h"
#include "AlarmClient.h"


#ifdef __cplusplus
extern "C" {
#endif

#define MODE2_EXTERNAL_TIME_STAMPER_CLOCK_ID	firstNodeTimeClockId			//Note must be either nodeTime1 or nodeTime2

#define SOURCE_NAME_SIZE 16
#define HYBRID_NO_POST_PROCESSING_PERIOD		(600*SLOW_TICKS_PER_SECOND)
#define MAX_TICK_COUNT_AFTER_CAL_B				(60*60*SLOW_TICKS_PER_SECOND)
#define HOLD_OVER_DURATION_START_WIDE_BANDWIDTH	(1*60*60*SLOW_TICKS_PER_SECOND)	//start bandwidth widening if holdover longer than this
#define	HOLD_OVER_DURATION_CAN_BE_IGNORED		(30*60*SLOW_TICKS_PER_SECOND)
#define HYBRID_CLOCK_FREQUENY_ERROR_FILTER_COEF	0.999f
#define HYBRID_FREQUENY_OFFSET_FILTER_COEF		0.99f

//Define the parameters for the source (from holdover) to become stable
//The parameters are different for clock or ptp types of sources
#define CLOCK_HOLDOVER_PERIOD_0						(10*60*SLOW_TICKS_PER_SECOND)
#define CLOCK_SOURCE_TO_BE_STABLE_PERIOD_0			(30*SLOW_TICKS_PER_SECOND)
#define MAX_PHASE_CLOCK_SOURCE_TO_BE_STABLE			(1.0e-07f)
#define MIN_TICKS_CLOCK_SOURCE_TO_BE_STABLE			(30*SLOW_TICKS_PER_SECOND)
#define MIN_TICKS_CLOCK_PHASE_ERROR_BEEN_SMALL		(60*SLOW_TICKS_PER_SECOND)

#define PTP_HOLDOVER_PERIOD_0						(10*60*SLOW_TICKS_PER_SECOND)
#define PTP_HOLDOVER_PERIOD_1						(30*60*SLOW_TICKS_PER_SECOND)
#define PTP_HOLDOVER_PERIOD_2						(60*60*SLOW_TICKS_PER_SECOND)
#define PTP_SOURCE_TO_BE_STABLE_PERIOD_0			(2*60*SLOW_TICKS_PER_SECOND)
#define PTP_SOURCE_TO_BE_STABLE_PERIOD_1			(5*60*SLOW_TICKS_PER_SECOND)
#define PTP_SOURCE_TO_BE_STABLE_PERIOD_2			(10*60*SLOW_TICKS_PER_SECOND)
#define MAX_PHASE_PTP_SOURCE_TO_BE_STABLE			(5.0e-07f)
#define MIN_TICKS_PTP_SOURCE_TO_BE_STABLE			(2*60*SLOW_TICKS_PER_SECOND)
#define MIN_TICKS_PTP_PHASE_ERROR_BEEN_SMALL		(5*SLOW_TICKS_PER_SECOND)

#define COMMANDED_PLL_BW_INDICATING_TCXO			2.5e-03f

#define AVERAGE_FREQUENCY_HISTORY_SIZE				4
#define AVERAGE_FREQUENCY_PERIOD					(10*SLOW_TICKS_PER_SECOND)

#define QUIET_NETWORK_POST_CAL_SETTLE_PERIOD		(3*60*SLOW_TICKS_PER_SECOND)

#define TICKS_DO_PHASE_ALIGN_FOR_PTP_MASTER_JUMP	4

typedef enum
{
	sourceIsNotAligned = 0,						//The source is neither time nor frequency aligned
	sourceIsFrequencyAligned,					//The source is frequency aligned
	sourceIsPhaseAligned						//The source is phase (therefore also frequency) aligned
} PhaseBuildOutProperty;

typedef struct
{
	struct
	{
		Signal		isSmallAbsolute;
		Signal		isSmall;
		Signal		isBig;
		float		granularityMultiple;
	} phase;

	struct
	{
		Frequency	isSmallAbsolute;
		Frequency	isSmall;
		Frequency	isBig;
	} gradient;

	struct
	{
		struct
		{
			float unsuitable;
			float suitable;
		} holdover;

		struct
		{
			struct
			{
				float isUnlocked;
				float isLocked;
			} rising;

			struct
			{
				float isUnlocked;
				float isLocked;
			} falling;

		} stepSuppress;

		float minValueToBeMaster;
	} lock;

	uint8	phaseJumpPersist;
	float	delayedSuppressionDecreaseTime;  // in multiples of PLL bandwidth

} TRSelThresholds;

typedef enum
{
	// Request for the source to do something
	measureFrequencyOffsetTRS,	// result1 is offset deltaF/F (positive indicates that the reference is faster than this node
								// result2 is offset in seconds (positive indicates that the master time is ahead of this node)
	calibrateOscillatorTRS,
	measurePhaseOffsetTRS,		// result1 is offset in seconds (positive indicates that the master time is ahead of this node)
								// result2 is measured frequency offset
	runTRS,						// normal operation
	inputHasChangedTRS,			// the configuration or state of one or more other sources has changed
	numberOfActionsTRS
} ActionTRS;

typedef enum
{
	voidTRSrc,					/**< Empty */
	invalidTRSrc,				/**< No time is available */
	measuringFrequencyTRSrc,	/**< The source has been selected and is currently aligning */
	calibratingOscillatorTRSrc, /**< The source is calibrating it's oscillator (Perforce: //topdocs/TS2/VCXO_Control/VCXO_SDS.docx) */
	measuringPhaseTRSrc,		/**< The source has been selected and is currently aligning */
	holdoverTRSrc,				/**< The source was on runningTRSrc, then lost clock or PTP connection */
	runningTRSrc				/**< The source is providing time information to the selector. */
} TimeRSState;


typedef enum
{
	clockTRS,
	packetTRS,
	hybridTRS
} TRSType;


TimeReferenceSourceState ConvertInternalTRSStateToExternal(TimeRSState internal);

typedef enum {primary, secondary, numberOfTRSDirections} TRSDirection;


typedef enum
{
	wholePeriodsOnly,	// only whole clock periods
	accurateUpdateType,	// the approximate update is accurate
	otherUpdateType,
	applySecondsFloor,  // approximate time is of last integer second
	numberOfApproxUpdateTypes
} ApproxUpdateType;

typedef enum
{
	medianDelayDisabled = 0,		
	medianDelayOnly,
	medianDelayAdaptive
} MedianDelayState;

typedef struct
{
	//The Hybrid parameters valid only for the PTP source
	Bool			hybridEnabled;
	Bool			pllMode;					//In coherent or congruent hybrid mode, TRUE = congruent mode, FASLE = coherent mode
	Bool			clockInputIsPerfect;		//Valid only for coherent mode, TRUE = the input clock frequency is perfect, FALSE = not perfect
	Bool			inputClockIsCoherentCongruentMode; //This parameter is used for congruent Hybrid only, where topSync will track to input clock frequency when PTP fails out
	Frequency		inputClockFrequencyError;	//an estimate of input clock's own frequency error
	Frequency		frequencyOffsetFromInputClock;	//the frequency to be added to the PTP source, which is the summation of osc error + clock's own error
	struct TimeReferenceSourceStruct const*  inputClockSource;	//pointer to the input clock TRS

	//The Hybrid parameters valid only for the input Clock source
	Bool			isInputToHybrid;			//TRUE = the source (clock) is now used as a clock input for hybrid operation
	Bool			alignmentJumpNeeded;

	IEEE1588Time	jumpValue;
} HybridCrossSourceControl;

typedef void (*PhaseShiftFPtr)(void* localDataPtr, IEEE1588Time const* phaseShift, Bool hardwareHasMoved);
typedef void (*CalibrationStageResetFPtr)(void* localDataPtr); /* Called when a calibration stage has finished. E.g. end of firs FOE stage requires reset for buffers/filters etc so second FOE stage can start */

typedef struct TimeReferenceSourceStruct
{
	// Values controlled internally
	TimeRSState					state;
	Bool						enableFastCalibration;					//valid only for PTP source
	Bool						measurementComplete;
	Bool						sourceIsStable;
	HighRangeFilter				actualLag;
	uint8						phaseJumpIndicationCount[numberOfApproxUpdateTypes]; // number of consecutive time updates that should have caused a phase jump
	uint						postCalBSettleTickPoint_0;				//settling period after calibration when starting from a noisy rather than quiet network
	uint						postCalBSettleTickPoint_1;				//settling period after calibatoion 
	uint						ticksAfterCalB;					//used only for PTP source
	uint						ticksSinceRunningTRSrc;			//number of ticks after entering runningTRSrc state, used for all source types
	uint						ticksRemainingSourceToBeStable;	//This is a count down timer. When it becomes zero, the source will be declared as stable anyway
	uint						ticksSourceIsNotStable;			//counter, where source status has been delcared as Not Stable
	uint						ticksPhaseErrorBeenSmall;		//consecutive ticks phase error is staying small

	// Source data
	struct
	{
		struct
		{
			Signal					unlockedPhaseLag;
			Signal					phaseLag;
			Signal					stagePhaseLag;			//This is phaseLag without adding the grandClockError from previous BC
			Signal					phaseAccuracy;			//An estimate of the output phase accuracy for this TRS

			struct
			{
				Signal				mean;
				Signal				max;
				Bool				delayJumped;		//small delayJump happened, used for dynamic PLL b/w control
				Bool				overMicroSecondDelayJumped;		//delayJump over micro-second happened
				Bool				valid;
			} noise;

			float					requestTemporaryHoldover;
		} updatable; // by source

		struct
		{
			Bool				phaseInformationValid;
			Bool				updated;  // set when new data written
		} internal; //must not be updated by source
	} performance;

	struct
	{
		Frequency				pllBandwidth;
		Frequency				pllBandwidthRTDBased;
		Frequency				oldPllBandwidthCommanded;

		ElapsedTime				previousRTD;
		int						tickTimer;
		uint					tickInContinuousBandwidthIncrease;
		Bool					RTDJumpHappened;
		Bool					isInInitialHighBwPeriod;
	} dynamicPllBandwidth;

	// Values controlled (indirectly) by source
	//*****************************************

	struct
	{
		ReferenceClock const*	clock;			// the quality of the source
		ReferenceClock			previousValue;	// the previous value of GetReferenceClockTRS() - allows changes to be detected
	} reference;

	/*
	When the source takes unidirectional time (e.g. 1PPS pulses)
	samplePeriod[primary] is the time between successive samples,
	samplePeriod[secondary] is zero

	When the source takes bidirectional time (e.g. m2s and s2m 1588 packets)
	samplePeriod[primary] is the time between successive samples in one direction,
	samplePeriod[secondary] is the time between successive samples in the other

	*/
	ElapsedTime					samplePeriod[numberOfTRSDirections]; // total sample period

	Signal						requestedPhaseLag; 	//required by source - this is not the same as the configuredPhaseLag

	//Configuration
	//*****************************************
	char						name[SOURCE_NAME_SIZE];
	ClockId						clockId;
	TimeSourceConfiguration *	configuration;
	TRSType						timeSourceType;
	uint16						configurationChangeCounter;	//incremented whenever *configuration changes
	ElapsedTime					phaseDetectorGranularity;
	void*						localData;  // format of localData is known only by the client
	HybridCrossSourceControl	hybridCrossSourceControl;			// Hybrid operation related parameters

	struct UTCOffsetControllerStruct const* utcOffsetController; // may be NULL
	struct UTCOffsetControllerStruct        cachedUtcOffsetController;

	//PhaseShift callback function pointer - may be NULL
	PhaseShiftFPtr phaseShift;
	// Calibration stage reset function pointer - may NOT be NULL
	CalibrationStageResetFPtr calibrationReset;


	/* Update client information to compensate for a move forward of phaseShift seconds
	 * phaseShift is the value of the movement of the selector
	 * */

	TRSelThresholds				configured;	// configured thresholds, set by default and externally
	ElapsedTime					slowTickPeriod;

	Bool						requireTAI;  // an external source must be TAI
	Bool						requireUTC;  // an external source must know correct UTC offset
	Bool						requirePRS; // an external frequency input must be traceable to a primary source

	Bool						allowNetworkTimeSourceToBeThisNodesReference;
	Bool						acceptApproxTimeFromPacketSource;

	Bool						enableFrequencyOnly;

	Bool						enableNoiseCompensation;
	Bool						enableTrafficCompression;
	Bool						enableDirectionSelection;

	float						trafficCompressCoefficient;
	float						trafficCompressProtectThreshHi;

	uint32						maximumSlidingWindowSizeInSec;

//	float						oscillatorPhaseDrift;						//0-1 value indicating likely oscillator drift

	MedianDelayState			medianDelayState;								//medianDelayActive = adaptive, medianDelayOnly=UseItSolely, medianDelayOff=notUseIt
	Bool						enableAdaptivePLLBandwidth;
	Bool						enableAdaptiveSlidingWindowLength;
	
	Bool						ptpCanBeBackupSource;						//valid for PTP source only, which means it may run as backup for GPS
	Bool						ptpIsRunningAsBackupSource;					//valid for PTP source and only when it's running as backup for GPS

	Bool						enableSparseDelayFilter;
	uint32						sparseDelayRate;
	uint32						timerAfterSkipSample;

	uint32						ticksSinceLastAlignWithPtpMasterJump;		//this counter increase by one per slow ticks, when less than 4, do phaseJump

	ElapsedTime					minSparseDelayJump;

	PhaseBuildOutProperty		pboPropertyForNodeTime1;					//property assoicated to nodeTime1
	PhaseBuildOutProperty		pboPropertyForNodeTime2;					//property assoicated to nodeTime2

	// Operation
	Bool						tai;				// node time is TAI
	TRSelThresholds				threshold;			// thresholds in use, updated dynamically

	Frequency					outputFrequency;

	//parameter for frequency jump detection, used mainly to detect sudden clock frequency change during hybrid mode
	Frequency					averagedFrequencyLatest;
	Frequency					averagedFrequencyHistory[AVERAGE_FREQUENCY_HISTORY_SIZE];

	Frequency					frequencyJumpValue;

	Bool						frequencyJumpHappened;
	uint						numberValidAverageFrequency;
	uint						averagedFrequencyIndex;
	uint						ticksCountAverageFrequency;
	uint						countDownAfterFrequencyJump;

	// Components
	HoldoverController			holdoverController;

	LockDetector				lockDetector;
	FrequencyController			frequencyController;
	BinaryLockMonitor			binaryLockMonitor;

	Frequency                   frequencyMovementDueToCalA; // Need to record this when auto-calibrating a VCXO
	Bool                        approxTimeUpdated;
} TimeReferenceSource;


void InitialiseTimeReferenceSource(TimeReferenceSource* source,
	void* localData,
	char const name[],
	TRSType type,
	ClockId clockId,
	TimeSourceConfiguration const* configuration,  //may be NULL
	Signal	phaseDetectorGranularity,
	PhaseShiftFPtr phaseShift,
	CalibrationStageResetFPtr calibrationReset, // NOT null
	ElapsedTime primarySamplePeriod,
	ElapsedTime secondarySamplePeriod,
	Frequency maxFrequencyOffset,
	struct AlarmMonitorStruct* alarmMonitor,
	AlarmSourceIdentity identity,
	ElapsedTime slowTickPeriod,
	ElapsedTime fastTickPeriod);

void ResetTimeReferenceSource(TimeReferenceSource* source);
void SlowTickTRS(TimeReferenceSource* source);
void SlowTickTRS_Clock(TimeReferenceSource* source);
void FastTickTRS_Clock(TimeReferenceSource* source);
void SetSamplePeriodTRS(TimeReferenceSource* source, ElapsedTime primarySamplePeriod, ElapsedTime secondarySamplePeriod);

void ConfigurationChangedTRS(TimeReferenceSource* source, TimeSourceConfiguration const* newConfiguration);
	// pointer may have changed, or data at end of pointer may have changed
	//The function can be called when source is NULL, but will have no effect

void ReferenceTimeSignalsAvailable(TimeReferenceSource* source, Bool available);
// Client can see a time signal
// utcOffsetController may be NULL, indicating offset is not provided

void SetReferenceClockTRS(TimeReferenceSource* source, ReferenceClock* referenceClock);
	//either referenceClock OR sourceHoldingReference OR both are NULL
ReferenceClock const* GetReferenceClockTRS(TimeReferenceSource const* source);  // always returns a valid pointer

void ConfigurePhaseMonitorTRS(TimeReferenceSource* source, Frequency bandwidth, Bool locked);

void SetUTCOffsetControllerTRS(TimeReferenceSource* source, struct UTCOffsetControllerStruct const* controller);
struct UTCOffsetControllerStruct* GetUTCOffsetControllerTRS(TimeReferenceSource const* source);

float GradientErrorIsLargeTRS(TimeReferenceSource const* source);
Bool PllLockAcceptableToBeMaster(TimeReferenceSource const* source);
uint8 GetClockClassTRS(TimeReferenceSource const* source);
Bool TRSourceUseLocalIDForExternalGMID(TimeReferenceSource const* source);  // for external transmission from node

#define GetSelectorTRS(s) ((s)->selector)
//#define IsSelectedTRS(s) (GetCurrentlySelectedSource((s)->selector) == (s) ? TRUE : FALSE)
#define TimeIsTaiTRS(s) (s->tai)		// aligned to TAI
Bool FrequencyIsPRS(TimeReferenceSource const* source);	// traceable to a primary reference source
Bool FrequencyIsOKForPRS(TimeReferenceSource const* source); //as above without check for PRS

#define UTCOffsetValidTRS(s)  (GetUTCOffsetControllerTRS(s) ? UTCOffsetValid((s)->utcOffsetController) : FALSE)
IEEE1588Time GetTimeTRS(TimeReferenceSource* source);
#define MaximumPhaseErrorTRS(s) ((s)->configuration ? (s)->configuration->maximumPhaseError : PLL_MAX_OFFSET)
#define MaxNoiseTRS(s) ((s)->performance.updatable.noise.max)
#define GetRequestedLockValueTRS(s) ((s)->performance.updatable.requestedLockValue)
#define SetSourceForFrequencyOffset(s, freqOffsetSource) ((s)->hybridCrossSourceControl.inputClockSource = (freqOffsetSource))
#define GetEpochTRS(trs, time) (GetEpoch((trs)->clockId, time))

#define	FrequencyOffsetTRS(trs) ((trs)->outputFrequency)

void ActionCompleteTRS(TimeReferenceSource* source, ActionTRS action,
						double frequencyChange, double timeJumpForward);
/* called by client when a requested action is complete.  May be called immediately.
If the client does not do the action the result should be zero.  Otherwise the meaning of
result is listed with the type definition of ActionTRS.
*/

Bool UpdateApproxTimeTRS(TimeReferenceSource* source, IEEE1588Time const* approxTime,
	IEEE1588Time const* inputClockPeriod, ApproxUpdateType updateType);

Bool UpdateApproxTimeNoJumpTRS(TimeReferenceSource* source, IEEE1588Time const* approxTime, 
							   Bool* lagPersisting, IEEE1588Time* jumpSize);

Bool SetThresholdTRS(TimeReferenceSource* source, uint16 id, float value);
float GetThresholdTRS(TimeReferenceSource* source, uint16 idsource);

//Bool UpdateApproxTimeTRS(TimeReferenceSource* source, Bool phaseJumpNecessary,
//		ApproxUpdateType updateType, uint8 phaseJumpPersistCount);

// called at least each slow tick when time information is being received
// returns TRUE if the phase may be used
//input clockPeriod may be NULL, indicating source does not have an input clock

void UpdatedTimeInformationTRS(TimeReferenceSource* source, Bool phaseInformationValid);
// called each time source->performance is updated

#define HoldoverForced(s) ((s)->holdoverController.forceHoldover)
#define MarkPhaseInformationInvalid(s) ((s)->performance.internal.phaseInformationValid = FALSE)
#define PhaseInformationIsValid(s) ((s)->performance.internal.phaseInformationValid) //source is operational but cannot provide time at the moment
#define GetStateTRS(s) ((s)->state)
#define GetLockValueTRS(trs) (LDValue(&(trs)->lockDetector))
#define ExistsTRS(source) (GetStateTRS(source) > voidTRSrc)
#define IsValidTRS(source) (GetStateTRS(source) > invalidTRSrc)
#define IsRunningTRS(source) (GetStateTRS(source) >= runningTRSrc)
#define IsPllInput(source) ((source)->pllController!=NULL)
#define ConfiguredPhaseLagTRS(s) (0)			//dummy as the correction has been moved inside the phaseLag calculation algorithm
#define PhaseLagTRS(s) ((s)->performance.updatable.phaseLag - ConfiguredPhaseLagTRS(s))
#define UnlockedPhaseLagTRS(s) ((s)->performance.updatable.unlockedPhaseLag - ConfiguredPhaseLagTRS(s))
Signal StablePhaseLagTRS(TimeReferenceSource const* source); //returns stable phase lag if selected
IEEE1588Time const* ExpectedPhaseLagTRS(TimeReferenceSource const* source);
#define ActualPhaseLagTRS(s) HighRangeFilterValue(&(s)->actualLag) //returns pointer
#define ActualPhaseLagIsValidTRS(s) HighRangeFilterOutputValid(&(s)->actualLag)
#define SetActualLagFilterToZeroTRS(s) ZeroHighRangeFilter(&(s)->actualLag)
void PhaseShiftTRS(TimeReferenceSource* source, IEEE1588Time const* shift, Bool nodeShifted, Bool exact); //nodeShifted is TRUE if the node time has moved by shift
#define IsPrimaryReferenceSourceTRS(trs) (GetReferenceClockTRS(trs)->quality.stratum <= primaryReference)
#define TimeTransportTRS(trs) (GetReferenceClockTRS(trs)->timeTransport)
#define GetSourceTypeTRS(s) ((s)->timeSourceType)
#define ReferenceClockIsExternalTRS(trs) ReferenceClockIsExternal(GetReferenceClockTRS(trs))
#define MeasurementCompleteTRS(trs) ((trs)->measurementComplete)
#define SetMeasurementCompleteTRS(trs) ((trs)->measurementComplete=TRUE)
#define GetConfigurationChangeCounterTRS(trs) ((trs)->configurationChangeCounter)

#define RequireUtcTRS(trs) ((trs)->requireUTC)
#define RequireTaiTRS(trs) ((trs)->requireTAI || (trs)->requireUTC)
#define RequirePrsTRS(trs) ((trs)->requirePRS)

void SelectedTRS(TimeReferenceSource* source); //call when source is newly selected
void UnselectedTRS(TimeReferenceSource* source); //call when source is newly deselected
void SetStateTRS(TimeReferenceSource* source, TimeRSState newState);
void SourceSetReCalibration(TimeReferenceSource* source);
Bool FindMode2ActiveStatus(void);

char const* SourceStateText(TimeRSState state);  //only available if DEBUG_PRINT is defined
#define SourceName(s) ((s)->name)
#define SourcePllName(s) (GetSelectorTRS(s) ? PllName(GetSelectorTRS(s)) : "")
#define ResetTickCounterAfterCalB(trs) ((trs)->ticksAfterCalB = 0)
#define SetSourceStableStatus(trs, state) ((trs)->sourceIsStable = state)
#define SourceIsStable(trs) ((trs)->sourceIsStable)
#define SetTicksRemainingSourceToBeStable(trs, value) ((trs)->ticksRemainingSourceToBeStable = value)
#define ResetTicksSourceIsNotStable(trs) ((trs)->ticksSourceIsNotStable = 0)

typedef enum
{
	// common (neither direction) parameters are 000 - 49
	// the base values for the directional parameters are 50-199
	// ms parameters are 200 - 399
	// sm parameters are 400 - 599
	// common (both directions) parameters are 600 - 799

	binLockPhaseErrorInputFilterBandwidthUnlocked,
	binLockPhaseErrorInputFilterBandwidthLocked,
	setEnablePhaseBuildOut,
	setUnselectedPhaseLagFilterBandwidthOpen,
	setUnselectedPhaseLagFilterBandwidthClosed,
	setMaximumFrequencyOffset,
	getCurrentFrequencyOffset,	// 'read only' parameter

	minDirectionalParameter = 50, // values above this relate to one or both directions.  Below this they are commond
	setAcceptorUnlockedLength = minDirectionalParameter,
	setAcceptorLockedLength,
	setAcceptorLists,
	setAcceptorCentile,
	setlockValueForMinListLength,
	setlockValueForMaxListLength,
	setHighNoiseValue,

	timeSourceMSMin = 200,

	timeSourceSMMin = 400,

	timeSourceBothDirMin = 600,
	timeSourceBothDirMax = 799


}TimeSourceParameter;


void PrintTRS(TimeReferenceSource const* source, char** ptrptr, long *bufferSize, char const titlePrefix[], Bool printTitle);

char const* ActionTRS2String(ActionTRS action);

#ifdef __cplusplus
}
#endif


#endif

