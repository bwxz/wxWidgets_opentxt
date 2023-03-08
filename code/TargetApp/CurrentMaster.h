#ifndef CURRENT_MASTER_H
#define CURRENT_MASTER_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "CurrentMasterDirection.h"
#include "MessageStore.h"
#include "TimeReferenceSource.h"
#include "TimeReferenceSelector.h"
#include "EpochController.h"
#include "AlarmClient.h"
#include "currentMasterPhaseLagProcessing.h"
#include "HybridTimeController.h"
#include "DelayMonitor.h"

#define BC_STAGE_CLOCK_ERROR_RESOLUTION						(1.0e-09f/256)	//second, this is the phaseError per bit
#define BC_STAGE_CLOCK_ERROR_RANGE_SEC						1.0e-04f		//maximum 100 usec error
#define BC_STAGE_CLOCK_ERROR_RANGE_FIXED_POINT				(BC_STAGE_CLOCK_ERROR_RANGE_SEC/BC_STAGE_CLOCK_ERROR_RESOLUTION)
	

#ifdef __cplusplus
extern "C" {
#endif

#define DUMMY_PACKET_PERIOD ((ElapsedTime) 0.125)
#define UseMSDelay(cm) ((cm)->delaysToUse != s2m)
#define UseSMDelay(cm) ((cm)->delaysToUse != m2s)
#define UseBothDelays(cm) ((cm)->delaysToUse == both)


typedef struct
{
	ElapsedTime			previousRawPhaseLag;
	ElapsedTime			maximumRawPhaseLag;				//maximum in the sense of absolute value
} DynamicPllBandwidth;


typedef struct
{
	struct
	{
		uint32 numValid;                   /**< #Time stamps received that have made it into one of the timestamp stores */
		uint32 numInvalid;                 /**< #Time stamps rejected before use because they contain invalid information */
		uint32 numDroppedDueToTimeout;     /**< #Time stamps removed from the message store because they stayed there too long, i.e., we not matched to their pair */
		uint32 numDroppedDueToOverwrite;   /**< #Time stamps overwritten in the message store because they were the oldest and were overwritten so that more recent timestamps could be stored */
	} T1, T2, T3, T4;

	uint32 numM2SRxd;                      /**< #Full T1, T2 pairs received and used */
	uint32 numS2MRxd;                      /**< #Full T3, T4 pairs received and used */

	IEEE1588Time                    timestampSnapshot[4]; // T1, 2, 3, 4 at indicies 0, 1, 2, 3
} CurrentMasterTimeInfoStats;


typedef struct CurrentMasterStruct
{
	struct VisibleMasterStruct*		visibleMasterRecord; // NULL if invalid
	struct DelaySourceStruct*		delaySource;
	struct PtpPortStruct*			ptpPort;			 // CurrentMaster has 1-1 mapping to a PTP port
														 // This ptr is used mainly for eBoundary clock purposes
	TimeReferenceSource				timeReferenceSource;
	ClockId							clockId;	// ID of the network time stamper
	PortId							previousVMPortId;
	Bool							calibrationDoneAtLeastOnce;
	Bool							doCalBTwice;

	//added for dpa algorithm
	PacketAnalyserAlgorithm			packetAnalyserAlgorithm;
	CurrentMasterPostProcessing*	cmControl;	
	DynamicPllBandwidth				dynamicPllBandwidth;
	

	// transmitted sync message timestamp storage
	MessageStore					msTxTime;
	MessageStore					msRxTime;
	MessageStore					smTxTime;
	MessageStore					smRxTime; // for delay messages

	CurrentMasterDirection			masterToSlave;
	CurrentMasterDirection			slaveToMaster;
	Bool							approximateTimeUpdated;  //True if UpdateApproxTimeTRS() has been recently called
	AlarmClient						noCurrentMasterAlarm;

	// cache
	ElapsedTime						configuredPhaseLag;		//copy of configuration data
	float							locked; //updated on slow tick
	Direction						delaysToUse;  // copy of configuration data

	uint32							holdoffTickRemaining;  // when this is non zero will ignore incoming delay messages
														   // this is only used in timestamp processor modes 2&3

	CurrentMasterTimeInfoStats      stats;

	HybridTimeController			hybridTimeController;

} CurrentMaster;


// Public function
void InitialiseCurrentMaster(CurrentMaster* master,
		ClockId ptpInputClock, struct PtpPortStruct* port,
		struct AlarmMonitorStruct* alarmMonitor);

void ResetCurrentMaster(CurrentMaster* master);

void CurrentMasterSlowTick(CurrentMaster* master);

void MSDelayInformationReceivedCM(CurrentMaster* master,
			IEEE1588SequenceNumber messageSequenceNumber,
			IEEE1588Time const* transmitTime,  // null if not known
			sint32 transmitTimeCorrectionNs, // the value should be added to transmitTime
			IEEE1588Time const* receiveTime); // null if not known

void SMDelayInformationReceivedCM(CurrentMaster* master,
			IEEE1588SequenceNumber messageSequenceNumber,
			IEEE1588Time const* transmitTime,  // null if not known
			sint32 transmitTimeCorrectionNs, // the value should be added to transmitTime
			IEEE1588Time const* receiveTime); // null if not known

/* This function is used only for correcting stored T3 times with updates from external timestampers for Mode 2 operation */
Bool GetStoredT3Time(CurrentMaster* master,IEEE1588SequenceNumber messageSequenceNumber,
		IEEE1588Time* transmitTime);

Signal GetPhaseLagCM(CurrentMaster const* master);
#define IsMasterApproxTimeValidCM(cm) IsEpochControllerApproxTimeValid(&(cm)->epochController)
#define GetApproxTimeCM(cm) EpochControllerGetApproxTime(&(cm)->epochController)
Signal UnlockedPhaseLagCM(CurrentMaster const* master);

void PrintCurrentMaster(CurrentMaster const* master, char** ptrptr, long *bufferSize, Bool printTitle,
		Bool printPll, Bool printAlgorithm, Bool printModeStats);

void CurrentMasterCancelHoldoff(CurrentMaster* master);
void CurrentMasterEnterHoldoff(CurrentMaster* master);
void CurrentMasterDeselected(CurrentMaster* master);
void NewMasterSelectedAsCurrent(CurrentMaster* master, struct VisibleMasterStruct* visibleMaster,TimeSourceConfiguration const* configuration);
void CurrentMasterSelectHybridMode(CurrentMaster* master,TimeReferenceSource* clockSource);
void NewSourceSelectedAsCurrent(CurrentMaster* currentMaster, struct DelaySourceStruct* newSource);
void CurrentMasterPortConfigurationHasChanged(CurrentMaster* master, TimeSourceConfiguration const* configuration);
void CurrentMasterUpdatePeriodHasChanged(CurrentMaster* master);
#define ExpectedPhaseLagCM(cm) ExpectedPhaseLagTRS(&(cm)->timeReferenceSource)

#define GetTimeReferenceSourceCM(cm) (&((cm)->timeReferenceSource))
#define StateCM(cm) GetStateTRS(&((cm)->timeReferenceSource))
Bool CurrentMasterAligned(CurrentMaster const*  master);
#define GetSelectedMasterRecord(cm) ((cm)->visibleMasterRecord)

Bool CurrentMasterHasSelectedSource(CurrentMaster const*  master);
struct PtpPortStruct* CurrentMasterGetPort(CurrentMaster const*  master);

void ConstructDelayReport(DelayMonitor* dm, CurrentMaster* master); // only called from CurrentMasterDirection

void SetDelayReceivedNotificationFunctionCM(CurrentMaster* master, Direction direction, void (*function) (void* localData, ElapsedTime delay), void* delayReceivedFunctionFirstParameter);

void ResetMessageStores(CurrentMaster* master);
void SetPacketAnalyserAlgCM(CurrentMaster* master, PacketAnalyserAlgorithm alg);

//added for dpa algorithm
void UpdateRawPhaseLagCM(CurrentMaster * master);
void UpdatePhaseLagCM(CurrentMaster * master);
Signal GetPhaseLagCM_DPA(CurrentMaster const* master);
Signal RawPhaseLagCM_DPA(CurrentMaster const* master, Bool useMedianDelay);
Signal GetTwoPathPhaseLag(CurrentMaster const* master, Bool useMedianDelay);
Signal GetSinglePathPhaseLag(CurrentMaster const* master);

void InitialiseCurrentMasterPostProcessing(CurrentMaster * master);
void ResetCurrentMasterPostProcessing(CurrentMaster * master);
void CurrentMasterPostProcessingSlowTick(CurrentMaster * master);
void AlignPtpPhaseToReference(CurrentMaster * master, IEEE1588Time timeDiff);

#define PacketAnalyserAlgorithmCM(cm) GetAlgPllController((cm)->pllController)

Signal PhaseLagNoiseCompensation(CurrentMaster const* master, Signal phaseLag);
Signal GetPhaseLagForLockDetector(CurrentMaster const* master);

LogMessagePeriod CurrentMasterGetMessageRate(CurrentMaster const* master, Direction const dir, LogMessagePeriod const defaultPeriod);
void PrintCurrentMasterMinMaxDelaysAndReset(
		CurrentMaster *master,
		char** ptrptr,
		long *bufferSize,
		Bool printTitle);

#ifdef __cplusplus
}
#endif

#endif

