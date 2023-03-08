/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this
 * file is owned by Semtech Corporation (Semtech). This is an
 * unpublished work.  The content of this file must be used only for
 * the purpose for which it was supplied by Semtech or its
 * distributors. The content  of this file must not be copied or
 * disclosed unless authorised in writing by Semtech.
 */
#ifndef CLOCK_TIMESTAMP_CONTROL_H
#define CLOCK_TIMESTAMP_CONTROL_H

#include "IEEE1588Time.h"
#include "PacketFilter-VariableBandwidth.h"
#include "TimeReferenceSource.h"
#include "TimeReferenceSelector.h"
#include "TimeOfDay.h"
#include "ClockPath.h"
#include "ToPSyncTypes.h"
#include "ClockInputsMonitor.h"
#include "AlarmClient.h"
#include "TimeConversion.h"
#include "TimeOfDayController.h"


#include <time.h>

#define CLOCK_EDGES_TO_VALID 5

#define MAX_SAMPLES_PER_SECOND  64
#define MAX_SAMPLES_TO_AVERAGE 2

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ClockLockingControllerStruct
{
	//Configuration
	Bool						selectedInputEnabled;
	Bool						edgesAreSignificant;	// the edges of a signal occur at the top of second
	ClockPath*					clockPath;
	ReferenceClock				referenceClock;
	IEEE1588Time				inputPeriod;
	uint16						ticksToMissedClockEdge;
	uint8 						selectedInput;		// hardware
	uint8						clockTimeStamper;   // index of clock timestamper (not guaranteed to be same as clockId)
	TimeSourceConfiguration		configuration;
	float						assumedClockInputNoise;	//allows the lock detector to lock when the clock input has a significant input jitter


	// Controlled by object
	TimeReferenceSource			timeReferenceSource;
	Bool						clockInputValid;  //true when receiving clock edges and enabled
	Bool						phaseDiscontinuity; // phase jump may have occurred
	Bool						approxTimeUpdated;	//set by ClockLockingControllerSlowTick cleared when time updated
	uint8						edgesDetected;  // stops counting at CLOCK_EDGES_TO_VALID
	uint16						slowTicksSinceLastClockEdge;

	struct		/* This struct is used to average the phase lags when we have an input faster then 1PPS */
	{
		struct
		{
			Signal				sum;	//total of values stored
			uint16				count; //number of values stored
		} current;

		uint16					samplesToAverage;

	} phaseLagAverager;

	/* When the input is high frequency, it is divided to 32Hz.
	If the ClockLockingController aimed to reduce its phase error
	to zero, this would cause the device to move phase by up to
	1/64th of a second when locking.
	clockDivisionCompensationIsActive avoids this
	*/
	struct
	{
		Bool enabled;
		Bool active;
	} clockDivisionCompensation; 


	IEEE1588Time				previousEdge;
	IEEE1588Time				rawPhaseLag;
	IEEE1588Time				nextEdgeIdeal;	//ideal time for next edge to arrive (no phase error) - relative to node time
	IEEE1588Time				nextEdgeExpected; // one period after the previous edge - relative to node time
	IEEE1588Time				phaseBuildOutCompensation;  //subtracted from rawPhaseLag before it presented to the PLL

	// variables used to detect incorrect input frequencies
	struct
	{
		//Configuration
		Frequency				maxFrequencyOffset;  //w.r.t. local oscillator
		ElapsedTime				maxJitter;  //change since previous edge

		//Operation
		Signal					edgeDiffLimit;
	} debouncer;

	//objects
	ClockInputsMonitor			clockInputsMonitor;
	VariableBandwidthFilter		filter;
	Filter						unlockedFilter;
	FrequencyOffsetEstimator	frequencyOffsetEstimator;
	TimeOfDayController			timeOfDayController;
	AlarmClient					alarmClientClockInput;

	struct
	{
		ToPSyncTime time;
		ToPSyncTimescale scale;
	} mmAPIShadows;
}ClockLockingController;

void PrintClockLocker(ClockLockingController const* clockLocker, char** ptrptr, long *bufferSize, Bool title);

void ClockLockingControllerSlowTick(ClockLockingController* clControl);

void ClockLockingControllerFastTick(ClockLockingController* clControl);

void ClockEdgeDetected(ClockLockingController* clControl, const IEEE1588Timestamp* edgeTimestamp);

void InitialiseClockLockingController(
		ClockLockingController* clControl,
		NodeId const* nodeId,
		struct AlarmMonitorStruct* alarmMonitor,
		ClockPath* clockPath, ClockId clockId);

Bool EnableClockLockingControllerInput(ClockLockingController* clControl, uint8 input, Bool enable);

#define ClockLockingControllerEnabled(c) ((c)->selectedInputEnabled)

void AssignClockLockingControllerToClockPath(ClockLockingController* clControl,
				ClockPath* clockPath, PLLid pll);

void ResetClockLockingController(ClockLockingController* clControl);

void SendToDToClockLockingController(ClockLockingController* clControl, ToPSyncTimeOfDay const* timeOfDay, ToPSyncTimescale timescale, Bool fromDedicatedInput); // fromDedicatedInput is TRUE if it is from UART or API
#define ReceivingDedicatedTimeOfDayInputCLC(cl) ReceivingDedicatedTimeOfDayInput(&(cl)->timeOfDayController)

#define SetClockLockingControllerReferenceClock(clControl, referenceClockPtr) ((clControl)->referenceClock = *(referenceClockPtr))
#define GetClockLockingControllerReferenceClock(clControl) (&(clControl)->referenceClock)
#define SetClockLockingControllerQuality(clControl, clockQualityPtr) ((clControl)->referenceClock.quality = *(clockQualityPtr))
void SetClockLockingControllerPriority(ClockLockingController* clControl,Bool setPriorityOne, uint8 priority);
#define GetClockLockingControllerTimestamperId(cl) ((cl)->clockTimeStamper)
#define GetTimeReferenceSourceCLC(cl) ((cl)->timeReferenceSource)
#define InputEdgeTimeIsSignificantCLC(cl) ((cl)->edgesAreSignificant)
#define GetInputPeriodCLC(cl) (&(cl)->inputPeriod)
#define GetClockPathCLC(cl) ((cl)->clockPath)
#define ClockInputValid(cl) ((cl)->clockInputValid)

void SetClockLockingControllerMaxInputFrequencyOffset(ClockLockingController* clControl, Frequency maxOffset); //w.r.t. local Osc
#define GetClockLockingControllerMaxInputFrequencyOffset(clControl) ((clControl)->debouncer.maxFrequencyOffset) //w.r.t. local Osc

void SetClockLockingControllerMaxInputPhaseJitter(ClockLockingController* clControl, Signal maxJitter);
#define GetClockLockingControllerMaxInputPhaseJitter(clControl) ((clControl)->debouncer.maxJitter)

void ClockLockingControllerConfigurationUpdated(ClockLockingController* clControl);

void SetPTPInputClockFrequency(ClockLockingController* clControl, uint8 ptpClockInput, uint32 frequencyInHertz);
uint32 GetPTPInputClockFrequency(ClockLockingController* clControl, uint8 ptpClockInput);
#define IsPTPInputClockEnabled(clControl, ptpClockInput) IsInputEnabledClockInputsMonitor(&(clControl)->clockInputsMonitor, (ptpClockInput))
void SetPTPInputClockPriority(ClockLockingController* clControl, uint8 ptpClockInput, uint8 priority);
uint8 GetPTPInputClockPriority(ClockLockingController* clControl, uint8 ptpClockInput);
Bool ClockLockingControllerSelectPTPInputClock(ClockLockingController* clControl, uint8 ptpInputClock);
#define GetSelectedPTPInputClock(c) ((c)->selectedInput)
Bool UpdateApproxTimeCLC(ClockLockingController* clControl, IEEE1588Time const* approxTime, ApproxUpdateType updateType);
// returns TRUE if the phase may be used

typedef enum
{
	setEdgesAreSignificant,				//at least 1 input signal edge/sec occurs at top of second
	setAssumedInputNoiseValue,
	getRawPhaseLag = 10,
	increasePhaseBuildOutCompensation,
	setClearInputFilters = 13,							//input is still selected but clock edges are ignored
	timeOfDayInputValidThreshold = 200,
	timeOfDayEnableAutoLeapSecondDetection,
	setStepsRemovedForInputClock,
	timeOfDayMaxMissedInputs

} ClockLockingControllerParameter;

Bool ClockLockingControllerSetParameter(ClockLockingController* clControl, ClockLockingControllerParameter parameter, float value);
Bool ClockLockingControllerGetParameter(ClockLockingController* clControl, ClockLockingControllerParameter parameter, float* value);


#define PrintClockLockingController(clControl, ptrptr, printTitle) PrintTRS((clControl)->timeReferenceSource, ptrptr, "Clk", printTitle)
void PrintClockLockerSummary952x(ClockLockingController const* clockLocker, uint8 index, char** ptrptr,  long *bufferSize, Bool title);
void PrintClockLockerDetail952x(ClockLockingController const* clockLocker, uint8 index, char** ptrptr,  long *bufferSize, Bool title);


#ifdef __cplusplus
}
#endif


#endif

