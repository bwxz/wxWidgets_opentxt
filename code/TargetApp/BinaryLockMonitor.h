#ifndef BINARY_LOCK_MONITOR_H
#define BINARY_LOCK_MONITOR_H

#include "ToPSyncTypes.h"
#include "HysteresisController.h"
#include "PacketFilter-VariableBandwidth.h"
#include "FilterFIR.h"
#include "AlarmClient.h"
#include "AlarmMonitor.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TimeReferenceSourceStruct;

typedef struct
{
	AlarmMonitor*	alarmMonitor;				//pointer to the grand alarmMonitor structure
	Bool			pinHighWhenLockLow;			//When TRUE, the output pin is HIGH when it's out of lock and LOW when in-lock				
} BinaryLockMonitorTop;

typedef enum 
{
	phaseBLC, 
	gradientBLC, 
	fuzzyLockBLC, 
	numberOfBLCs
} BinaryLockComponent;

typedef enum
{
	/* NOTE NOTE NOTE NOTE NOTE NOTE
	******************************************************************************
	BinaryLockMonitorParameters must not be moved to include files that are visible to the public.
	******************************************************************************
	NOTE NOTE NOTE NOTE NOTE NOTE  */

	blmMonitorMode = 0,
	blmFuzzyLockAcceptable,		/* note these currently apply to the mainPLL */
	blmFuzzyLockUnacceptable,   /* monitor only  (used in hybrid mode)       */

	blmParameterRange = 100

} BinaryLockMonitorParameter;

typedef enum
{
	monitorPTPInputBLM,
	monitorClockInputBLM,
	monitorBothInputsBLM,
	numberOfMonitorModesBLM
} monitorModeBLM;

typedef struct
{
	//Configuration
	Bool					force; // true if lock forced true or false
	Bool					forcedState;  // state of lock if forced
	Bool					maintainLockDuringSourceSwitch;	//Set by API, only applicable to nodeTime

	//Operation
	Bool					phaseValueValid;

	Bool					inSourceSwitching;		//NodeTime is in the process to do phasePullIn to newly selected source

	//Components
	struct TimeReferenceSourceStruct* 	timeReferenceSource;

	HysteresisController	phase;
	HysteresisController	gradient;
	HysteresisController	fuzzyLock;

	VariableBandwidthFilter	phaseFilter;
	FilterFIR				phaseFilterFIR;

	AlarmClient				binaryLockOffAlarm;
	AlarmClient				binaryLockLossOfLockAlarm; //used in setting alarm pin

} BinaryLockMonitor;

void InitialiseBinaryLockMonitorTop(BinaryLockMonitorTop* blmt, struct AlarmMonitorStruct* alarmMonitor);
void ResetBinaryLockMonitorTop(BinaryLockMonitorTop* blmt);
void InitialiseBinaryLockMonitor(BinaryLockMonitor* blm,
		struct TimeReferenceSourceStruct* timeReferenceSource,
		LockedStateThresholds const* thresholds,
		Frequency unlockedBandwidth, 
		Frequency lockedBandwidth,
		ElapsedTime samplePeriod,
		struct AlarmMonitorStruct* alarmMonitor,
		AlarmSourceIdentity identity);

void ResetBinaryLockMonitor(BinaryLockMonitor* blm);

void SetTimeReferenceSourceBLM(BinaryLockMonitor* blm, struct TimeReferenceSourceStruct* trs);
void SlowTickBLM(BinaryLockMonitor* blm,float lock);
Bool IsLockedBLM(BinaryLockMonitor const* blm);
Bool IsLockedBLMTop(BinaryLockMonitorTop const* blmt);			//this function return TURE if any of the source's out of binaryLock (raised an outOfLock alarm)
LockedStateThresholds GetThresholdsBLM(BinaryLockMonitor const* blm);
void SetThresholdsBLM(BinaryLockMonitor* blm, LockedStateThresholds const* newValues);
Bool SetParameterBLM(BinaryLockMonitor* blm, BinaryLockMonitorParameter parameter, float value);
float GetParameterBLM(BinaryLockMonitor* blm, BinaryLockMonitorParameter parameter);

#define ForceLockBLM(blm, l) {(blm)->force = TRUE; (blm)->forcedState = (l);}
#define ClearForceLockBLM(blm) {(blm)->force = FALSE;}
#define LockForced(blm) ((blm)->force)
#define LockForcedState(blm) ((blm)->forcedState)
#define SetMaintainLockWhenChangingInput(blm,set) ((blm)->maintainLockWhenChangingInput = (set))
#define GetMaintainLockWhenChangingInput(blm) ((blm)->maintainLockWhenChangingInput)

#define SetPhaseFilterBandwidthBLM(blm, narrow, bandwidth) SetBandwidthVariableBandwidthFilter(&(blm)->phaseFilter, narrow, bandwidth)
#define GetPhaseFilterBandwidthBLM(blm, narrow) GetBandwidthVariableBandwidthFilter(&(blm)->phaseFilter, narrow)
#define SetPhaseFilterLengthBLM(blm, cl) SetChainLengthVariableBandwidthFilter(&(blm)->phaseFilter, (cl))
#define GetPhaseLagBLM(blm) VariableBandwidthFilterValue(&(blm)->phaseFilter)
#define PhaseLagIsValidBLM(blm) DataValidVariableBandwidthFilter(&(blm)->phaseFilter)
#define GetPhaseErrorGradientBLM(blm) GradientFIRFilter(&(blm)->phaseFilterFIR)
#define GetSelectorBLM(blm) ((blm)->timeReferenceSelector)

#ifdef __cplusplus
}
#endif

#endif
