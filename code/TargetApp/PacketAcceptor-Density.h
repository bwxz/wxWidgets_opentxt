#ifndef PACKET_ACCEPTOR_DENSITY_H
#define PACKET_ACCEPTOR_DENSITY_H


#include "DelayList.h"
#include "PacketFilter.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef DelayListValue AcceptorValue;
typedef struct 
{
	DelayList	delayList;

	//Configured values
	ElapsedTime maximumTimeToValid; // in seconds
	Signal		highNoiseThreshold;
	struct PacketRecordList*	listToBeUsedInHighNoise; // during high noise, packets not put in this list have an acceptance of zero
	uint16		maxRecordsStored[NUMBER_OF_BOOL_VALUES];  //FALSE == unlocked, TRUE == locked

	float		lockValueForListLength[NUMBER_OF_BOOL_VALUES];  //lock value at which list length equals min (FALSE) and max (TRUE)
	float		maxInputNoise;

	ElapsedTime	maxUnlockedTimeStorage; 
		// max time that DPA will store data when unlocked - avoids oscillation

	// Calculated values
	uint16		minimumValidNumberOfRecords; // fewer reconds means output is invalid
	uint16		unlockedTargetSize;
	uint16		targetSize;
	uint16		packetsAddedToNonZeroList;
	Filter		meanAcceptance;

	struct 
	{
		float acceptance;
		float highNoiseAcceptance;
	} output;

}DensityPacketAcceptor;


void InitialiseDPA(DensityPacketAcceptor* acceptor, uint16 maxNumberOfLists, uint16 numberOfLists, 
				ElapsedTime maximumTimeToValid, ElapsedTime maxUnlockedTimeStorage,
				AcceptorValue valueGranularity, ElapsedTime samplePeriod);

void ResetDPA(DensityPacketAcceptor* acceptor);

void SetSamplePeriodDPA(DensityPacketAcceptor* acceptor, ElapsedTime samplePeriod);

void AddDPA(DensityPacketAcceptor* acceptor, AcceptorValue value, Signal noise);  // returns acceptance 0 to 1
void SlowTickDPA(DensityPacketAcceptor* acceptor, float locked, Signal noise);
#define PhaseShiftDPA(acc, shift) PhaseShiftDelayList(&(acc)->delayList,(shift))// +ve shift increases delay

#define DataValidDPA(acc) (DelayListRecords(&(acc)->delayList) >= (acc)->minimumValidNumberOfRecords)
#define GetMeanAcceptanceDPA(acc) ((float) FilterValue(&(acc)->meanAcceptance))

#define DPAIsEmpty(acceptor) DelayListIsEmpty(&(acceptor)->delayList)
#define MinimumValueDPA(acceptor) (DelayListMinimumValue(&(acceptor)->delayList))
#define GetAcceptance(acceptor) ((acceptor)->output.acceptance)
#define GetHighNoiseAcceptance(acceptor) ((acceptor)->output.highNoiseAcceptance)

#define SetLockValueForListLength(acceptor, max, v) ((acceptor)->lockValueForListLength[max] = (v))

#define SetHighNoiseThresholdDPA(acceptor, v) ((acceptor)->highNoiseThreshold = (v))

Bool SetMaximumNumberOfRecordsDPA(DensityPacketAcceptor* acceptor, Bool locked, uint16 max);
#define GetMaximumNumberOfRecordsDPA(acceptor, locked) ((acceptor)->maxRecordsStored[locked])


void SetAcceptorCentileDPA(DensityPacketAcceptor* acceptor, uint16 centile);
#define SetNumberOfAcceptorListsDPA(acceptor, lists) SetNumberOfPRLists(&(acceptor)->delayList, lists)

#ifdef __cplusplus
}
#endif

#endif

