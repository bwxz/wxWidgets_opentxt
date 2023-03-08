#ifndef TIME_REFERENCE_SELECTOR_H
#define TIME_REFERENCE_SELECTOR_H

#include "ToPSyncTypes.h"
#include "TimeReferenceSource.h"
#include "LockDetector.h"
#include "BinaryLockMonitor.h"
#include "EpochController.h"
#include "FrequencyController.h"
#include "HoldoverController.h"
#include "HardwareFrequencyController.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*TRSelSourceChangedCallbackFPtr)(uint32 trIndex);

typedef struct TimeReferenceSelectorStruct
{
	//Configuration
	struct ClockPathStruct*		clockPath;
	ClockId						clockId;

	ElapsedTime					slowTickPeriod;
	Bool						nonRevertiveSourceSelection;   // only search for the best source when the current external source has failed
	Bool						nonRevertiveSourceSelectionOnSameTransport; //only search for the best PTP source when the current PTP source has failed
	Bool						requireTAI;  // an external source must be TAI
	Bool						requireUTC;  // an external source must know correct UTC offset
	Bool						requirePRS; // an external frequency input must be traceable to a primary source
	Bool						allowNetworkTimeSourceToBeThisNodesReference;
	Bool						acceptApproxTimeFromPacketSource;
	
	//Source array
	uint32						inputSourceEnable;	// bit field indicating which input sources are available
	Bool						inputsHaveChanged;	// flag indicating input sources have changed

	// Operation
	TimeReferenceSource*		selected;			// NULL if none selected
	ClockId						manuallySelectedInput;	// Force tr selector to select a particular input
													// even if it doesn't qualify as valid

	Bool						tai;				// node time is TAI

	Bool						newSourceJustSelected;		//will be used for phase buildout calculation	

	BMCABitMask					bmcaBitMask; //note that Identity and Identity values are not relevant to the trs
	uint8						highestStratumThatCanBeMaster;

	UTCOffsetController			utcOffsetController;  // use for free running operation ONLY

	TRSelSourceChangedCallbackFPtr sourceChangedListener;
	struct
	{
		ToPSyncTime time;
		ToPSyncTimescale scale;
	} mmAPIShadows;

} TimeReferenceSelector;

/**
 * \fn TRSelectorSetNodeTimeInputMux
 * Enables or disables input sources to the time reference selector
 * Bit mask used where if bit (input source) is set then input is enabled and
 * if clear input source is disabled
 *
 * \return
 * 		TRUE:  Enable / Disable succeeded
 * 		FALSE: The enable / disable failed
 * 	           (caused by out of range bits in the mask being set)
 */
Bool TRSelectorSetNodeTimeInputMux(TimeReferenceSelector* trs,uint32 muxInputEnable);

/**
 * \fn TRSelectorSetPhaseBuildOutEnable
 * Enables or disables phase build out
 * When enabled switching from current source will maintain existing phase output
 * even if new source differs in phase.
 *
 * \return
 * 		TRUE:  Enable / Disable succeeded
 * 		FALSE: The enable / disable failed
 */

void InitialiseTimeReferenceSelector(TimeReferenceSelector* trs,
	struct ClockPathStruct*	clockPath, ClockId id,
	Frequency maxFrequencyOffset,
	struct AlarmMonitorStruct* alarmMonitor,
	ElapsedTime slowTickPeriod, ElapsedTime fastTickPeriod);

void ResetTimeReferenceSelector(TimeReferenceSelector* trs);
void TRSelectorSlowTick(TimeReferenceSelector* trSel);

#define GetIdTRSelector(trs) ((trs)->id)
float GetLockValueTRSelector(TimeReferenceSelector const* trs);
#define GetCurrentlySelectedSource(trs) ((trs)->selected)
#define SetAlgTRSel(trs, a) ((trs)->packetAnalyserAlgorithm = (a))

IEEE1588Time GetTimeTRSel(TimeReferenceSelector const* trs);

ReferenceClock const* GetReferenceClockTRSel(TimeReferenceSelector const* trs);	//never returns NULL

ReferenceClock const* GetBestNonNetworkReferenceClockTRSelector(TimeReferenceSelector const* trs);	//may return NULL
TimeReferenceSource* FindBestSourceTRSelector(TimeReferenceSelector const* trs,
						Bool includeNetwork, Bool includeHoldoverController);

//These functions should only be called from TimeReferenceSource
void SourceSamplePeriodHasChangedTRSelector(TimeReferenceSelector* trs, TimeReferenceSource const* changedSource);
void PhaseAlignTRSel(TimeReferenceSelector* trs, IEEE1588Time const* shift, Bool exact, Bool forceJump); // only called by hybrid time controller


void ConfigurationChangedTRSelector(TimeReferenceSelector* trs, TimeReferenceSource* source);

#define RequireUtcTRSel(trs) ((trs)->requireUTC)
#define RequireTaiTRSel(trs) ((Bool) ((trs)->requireTAI || RequireUtcTRSel(trs)))
#define RequirePrsTRSel(trs) ((trs)->requirePRS)


void SelectorSourceActionCompleteTRSelector(
		TimeReferenceSelector* trs, TimeReferenceSource* source, ActionTRS action,
		double result1, double result2);

#define TimeIsTaiTRSel(trs) ((trs)->tai)
#define FrequencyIsTraceableToPrsTRSel(trs) ((GetCurrentlySelectedSource(trs) && IsPrimaryReferenceSourceTRS(GetCurrentlySelectedSource(trs))) ? TRUE : FALSE)

Bool LockedToSourceTRSel(TimeReferenceSelector const* trs);
Bool LockAcceptableToBeMasterTRSel(TimeReferenceSelector const* trs);
Bool LockAcceptableToBeInHybridModeTRSel(TimeReferenceSelector const* trs);
Bool SelectedSourceIsExternalAndValid(TimeReferenceSelector const* trs);

Bool FrequencyIsPrsTRSel(TimeReferenceSelector const* trs);
// True if frequency is traceable to a primary time reference - otherwise FALSE

float SelectedInputIsGood(TimeReferenceSelector const* trs); // returns 0 to 1
void RequestPhaseJumpTRSelector(TimeReferenceSelector* trs, TimeReferenceSource const* source, IEEE1588Time const* shift, Bool exact);

void PrintTRSelector(TimeReferenceSelector const* trs, char** ptrptr, long*, Bool title);

#define TRSelectorPhaseLag(trs) (GetCurrentlySelectedSource(trs) ? GetCurrentlySelectedSource(trs)->performance.updatable.phaseLag:(Signal)0.0)
float GradientErrorIsLargeTRSelector(TimeReferenceSelector const* trs);

#define ExternalSourceTRSelector(trs,source) ((source)!=NULL && (source->timeSourceType) != localTRS)
#define LockedToWireSourceTRSelector(trs) ((trs)->selected && IsRunningTRS(GetCurrentlySelectedSource(trs)) && TimeTransportTRS(GetCurrentlySelectedSource(trs)) == viaWire)
#define NonRevertiveSourceSelectionTRSelector(trs) ((trs)->nonRevertiveSourceSelection)
#define NonRevertiveSourceSelectionOnSameTransportTRSelector(trs) (NonRevertiveSourceSelectionTRSelector(trs) || (trs)->nonRevertiveSourceSelectionOnSameTransport)
UTCOffset const* GetUTCOffsetTRSelector(TimeReferenceSelector const* trs, IEEE1588Time const* currentTime); //returns NULL if invalid
Bool UTCOffsetValidTRSelector(TimeReferenceSelector const* trs);
struct UTCOffsetControllerStruct* GetUTCOffsetControllerTRSelector(TimeReferenceSelector const* trs);  //returns NULL if invalid
#define FrequencyOffsetTRSel(trs) FCValue(&(trs)->frequencyController)
#define GetEpochTRSel(trs, time) EpochControllerGetEpoch(&trs->epochController, time)
#define PllName(trs) ("Main")
#define UseMainPLLFrequencyOffsetTRSel(trs) (GetCurrentlySelectedSource(trs) ? GetUseMainPLLFrequencyOffset(GetCurrentlySelectedSource(trs)) : FALSE)

ClockId TRSelectorGetManuallySelectedInput(uint32 trSelIndex);
ClockId TRSelectorGetCurrentlySelectedPll(uint32 trSelIndex);
TRSelSourceChangedCallbackFPtr TRSelectorSetSourceChangeListener(uint32 trSelIndex, TRSelSourceChangedCallbackFPtr newListener);

void TRSelectorInputHasChanged(TimeReferenceSelector* trs,ClockId clockId);
void TRSelectorLocalOscillatorConfigHasChanged(TimeReferenceSelector* trs);

void SetNonRevertiveSourceSelection(TimeReferenceSelector* trs, Bool set);
void SetNonRevertiveSourceSelectionOnSameTransport(TimeReferenceSelector* trs, Bool set);

// Enumerations identifying thresholds.  A subset of the enumerations is also used in TRSelThresholdHost, and must be the same values
typedef enum
{
	/* NOTE NOTE NOTE NOTE NOTE NOTE
	******************************************************************************
	TRSelThreshold must not be moved to include files that are visible to the public.
	******************************************************************************
	NOTE NOTE NOTE NOTE NOTE NOTE  */

	phaseIsSmallAbsolute = 0,
	phaseIsSmall,
	phaseIsBig,
	phaseGranularityMultiple,

	gradientIsSmallAbsolute = 10,
	gradientIsSmall,
	gradientIsBig,

	lockUnsuitableForHoldover = 30,
	lockSuitableForHoldover,

	lockUnsuitableForStepSuppressRising = 40,  //"rising" and "falling" refer to the direction in which fuzzy lock is moving (see LockDetector)
	lockSuitableForStepSuppressRising,
	lockUnsuitableForStepSuppressFalling,
	lockSuitableForStepSuppressFalling,
	lockMinValueToBeMaster,

	phaseJumpPersistLimit = 50,

	smoothingPLLRiseTime = 60,

	phaseErrorGradientDELETED = 70,

	nonRevertive = 80,
	nonRevertiveSameTransport,
	setRequireTAI,
	setRequireUTC,
	setMaintainBinLockPinInSourceSwitchDELETED,
	setAllowNetworkTimeSourceToBeThisNodesReference,
	setAcceptApproxTimeFromPacketSource,
	setRequireFrequencyTraceableToPrimaryRefSource,
	setFrequencyOutputsUseSmoothedTimeDELETED,

	setPacketAnalyserAlgorithm = 100,
	setEnableFrequencyOnly,
	
	setEnableNoiseCompensation,
	setEnableTrafficCompression,
	setEnableDirectionSelection,
	setTrafficCompressCoefficient,
	setTrafficCompressProtectThreshHi,
	setFrequencyOnlyClampThreshHi,

	setMaximumSlidingWindowSizeInSec,

	getHoldoverValidDELETED = 110,

	setPhaseBuildOutPropertyNodeTime1 = 120,
	setPhaseBuildOutPropertyNodeTime2 = 121,

	setMedianDelayState = 200,
	setMedianDelaySearchNumberOfSample,
	setMedianDelaySearchMedianPoint,

	setLockDetectorParameterMin = 300, 	// range 300 - 399
	setLockDetectorParameterMax = setLockDetectorParameterMin + lockDetectorParameterRange -1,

	// range 400 - 499
	setBinaryLockMonitorParameterMin = setLockDetectorParameterMin + lockDetectorParameterRange,
	setBinaryLockMonitorParameterMax = setBinaryLockMonitorParameterMin + blmParameterRange - 1,

	// range 500 - 599
	setEnableAdaptivePLLBandwidth = 500,

	setEnableSparseDelayFilter = 510,
	setMinimumSparseDelayJumpInSecond,
	setSparseDelayRatePer100Seconds,

} TRSelThreshold;

Bool SetThresholdTRSel(TimeReferenceSelector* trs, TRSelThreshold id, float value);
float GetThresholdTRSel(TimeReferenceSelector* trs, TRSelThreshold id);

#define AllowNetworkTimeSourceToBeThisNodesReferenceTRS(trs) ((trs)->allowNetworkTimeSourceToBeThisNodesReference)
#define AcceptApproxTimeFromPacketSource(trs) ((trs)->acceptApproxTimeFromPacketSource)


#ifdef __cplusplus
}
#endif

#endif

