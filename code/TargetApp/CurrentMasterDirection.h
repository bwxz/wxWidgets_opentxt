#ifndef CURRENT_MASTER_DIRECTION_H
#define CURRENT_MASTER_DIRECTION_H

#include "FlightTimeAnalyser.h"
#include "FrequencyOffsetEstimator.h"
#include "ToPSyncInterfaceTypes.h"
#include "VisibleMasterDirection.h"
#include "MessageDelayStore.h"

#include "DelayPacketAnalyser.h"
#include "SystemConfiguration.h"

#ifdef __cplusplus
extern "C" {
#endif

	// CurrentMasterState is defined in TopSyncInterfaceTypes.h


typedef struct
{
	LogMessagePeriod				logUpdatePeriod;

	FlightTimeAnalyser				flightTimeAnalyser;

	//added for dpa algorithm
	DelayPacketAnalyser				delayPacketAnalyser;

	FrequencyOffsetEstimator		frequencyOffsetEstimator;

	struct CurrentMasterStruct*		master;

	DirectionConfiguration const*	configuration; 
	MessageDelayStore				delayMeasurementModeDelayStore; // only used in time measurement mode
} CurrentMasterDirection;


void InitialiseCurrentMasterDirection(CurrentMasterDirection* direction, 
					struct CurrentMasterStruct* master,
					ElapsedTime frequencyMeasurementTime, uint16 minFrequencyMeasurementPackets,
					AlarmSource alarmSource, AlarmSourceIdentity alarmSourceIdentity,
					AlarmSource alarmSource1, AlarmSourceIdentity alarmSourceIdentity1,
					struct AlarmMonitorStruct* alarmMonitor);

void ResetCurrentMasterDirection(CurrentMasterDirection* direction);
void CurrentMasterDirectionSlowTick(CurrentMasterDirection* direction,LogMessagePeriod logUpdatePeriod,Bool eboundaryClockEnabled); // each SLOW_TICK_PERIOD_SECS

#define ActiveCMD(dir) ((dir)->active == TRUE && ActiveVMD((dir)->visibleMasterDirection) && (dir)->configuration != NULL)

#define FlightTimeCMD(dir) GetMostRecentPacketDelay(&(dir)->flightTimeAnalyser)
#define NoiseValidCMD(dir) NoiseValueValidFTA(&(dir)->flightTimeAnalyser)
#define NoiseValueCMD(dir) NoiseFTA(&(dir)->flightTimeAnalyser)

//added for dpa algorithm
#define FlightTimeCMD_DPA(dir) GetMostRecentPacketDelayDPA(&(dir)->delayPacketAnalyser)
#define NoiseValidCMD_DPA(dir) NoiseValidDPAnalyser(&(dir)->delayPacketAnalyser)
#define NoiseValueCMD_DPA(dir) NoiseDPAnalyser(&(dir)->delayPacketAnalyser)

#define LogUpdatePeriodCMD(dir) ((dir)->logUpdatePeriod)
#define NoiseChangingSwiftlyCMD(dir) NoiseChangingSwiftlyFTA(&(dir)->flightTimeAnalyser)
#define UnlockedDelayCMD(dir) UnlockedDelay(&(dir)->flightTimeAnalyser)
void CMDirectionResetTimingPeriod(CurrentMasterDirection* direction);

void SetCurrentMasterDirectionParameters(CurrentMasterDirection* direction, FrequencyMeasurementConfiguration const* frequencyMeasurementConfiguration);
	// frequencyMeasurementConfiguration may be null, meaning those values are unchanged

void ResetCurrentMasterDirectionPhase(CurrentMasterDirection* direction);
void PhaseShiftCurrentMasterDirection(CurrentMasterDirection* direction, IEEE1588Time const* shift); // shift +ve means that the expected delay has increased
void FullDelayInformationReceivedCMD(CurrentMasterDirection* direction,
			IEEE1588Time const* transmitTime, Signal delay,
			IEEE1588Time const* receiveTime,
			IEEE1588Time const* masterTime, sint32 timeCorrectionNs);

#define MessageDelayStoreContainsDataCMD(dir) MessageDelayStoreContainsData(&(dir)->delayMeasurementModeDelayStore)

void CurrentMasterDirectionPortConfigurationHasChanged(
					CurrentMasterDirection* direction,
					DirectionConfiguration const* configuration,
					FrequencyMeasurementConfiguration const* frequencyMeasurementConfiguration);


void SetCurrentMasterDirectionLogUpdatePeriod(CurrentMasterDirection* direction, LogMessagePeriod logUpdatePeriod);
void SetDelayReceivedNotificationFunctionCMD(CurrentMasterDirection* direction, void (*function) (void* localData, ElapsedTime delay), void* delayReceivedFunctionFirstParameter);

void PrintCurrentMasterDirection(CurrentMasterDirection const* direction, char** ptrptr, long *bufferSize, char const title[]);// if title is NULL prints values
#ifdef __cplusplus
}
#endif


#endif


