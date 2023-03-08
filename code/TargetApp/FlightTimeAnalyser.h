#ifndef FLIGHT_TIME_ANALYSER_H
#define FLIGHT_TIME_ANALYSER_H

#include "General.h"
#include "PacketAcceptor-Density.h"
#include "PacketFilter.h"
#include "NoiseAnalyser.h"
#include "PacketFilter-FastRise.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {oneShotFTA, continuousFTA} ModeFTA;

typedef struct
{
	DensityPacketAcceptor	acceptor;

	ModeFTA					mode;
	Filter					unlockedDelayFilter;

	struct  
	// struct is used instead of union because the initialise functions 
	// allocate memory
	{
		FastRiseFilter			delayEstimator; // used during oneShotFTA
		VariableBandwidthFilter	running; // used during continuousFTA
		RateOfChangeMonitor		rateOfChange;   //of running filter
	} filter;

	NoiseAnalyser			noiseAnalyser;

	ElapsedTime				mostRecentPacketDelay;
	ElapsedTime				maxMostRecentPacketDelay;
	ElapsedTime				minMostRecentPacketDelay;
	float					mostRecentAcceptance;
	uint32					numberOfBigDelays; // delays received with delay > FTA_MAX_ACCEPTABLE_DELAY

} FlightTimeAnalyser;

void InitialiseFTA(FlightTimeAnalyser* fta,uint8 filterChainLength,
					Frequency unlockedBandwidth, Frequency lockedBandwidth,
					AlarmSource alarmSource, AlarmSourceIdentity alarmSourceIdentity,
					struct AlarmMonitorStruct* alarmMonitor);

void ResetFTA(FlightTimeAnalyser* fta);

void SetFilterBandwidthsFTA(FlightTimeAnalyser* fta, 
					Frequency unlockedBandwidth, Frequency lockedBandwidth);

void SetFilterChainLengthFTA(FlightTimeAnalyser* fta,uint8 filterChainLength);

#define SetNoiseAlarmThresholdsFTA(fta, on, off) NoiseAnalyserSetAlarmThresholds(&(fta)->noiseAnalyser, on, off)


void DelayReceivedFTA(FlightTimeAnalyser* fta, ElapsedTime delay, Bool active);
	// active is true if the data is to be used

void SlowTickFTA(FlightTimeAnalyser* fta, float lock);

void PhaseShiftFTA(FlightTimeAnalyser* fta, ElapsedTime shift);

void SetSamplePeriodFTA(FlightTimeAnalyser* fta, ElapsedTime samplePeriod); 
void SetTickPeriodFTA(FlightTimeAnalyser* fta, ElapsedTime tickPeriod);

#define StartDelayMeasurement(fta) StartEstimation(&(fta)->meanDelay)

//Information functions
#define DataValidFTA(fta) ((fta)->mode == continuousFTA)
ElapsedTime FilteredDelay(FlightTimeAnalyser const* fta);
ElapsedTime UnlockedDelay(FlightTimeAnalyser const* fta);

#ifndef _ARC
float DelayChangingSwiftlyFTA(FlightTimeAnalyser const* fta); //used in sim
#endif

#define GetMostRecentPacketDelay(fta) ((fta)->mostRecentPacketDelay)

#define NoiseFTA(fta)								ValueNA(&(fta)->noiseAnalyser)
#define NoiseValueValidFTA(fta)						ValidNA(&(fta)->noiseAnalyser)
#define GetNoiseAnalyser(fta)						(&(fta)->noiseAnalyser)
#define NoiseChangingSwiftlyFTA(fta)				NoiseValueChangingSwiftlyNA(&(fta)->noiseAnalyser)


#define SetNumberOfAcceptorListsFTA(fta, v)			SetNumberOfAcceptorListsDPA(&(fta)->acceptor,(v))
#define SetAcceptorCentileFTA(fta, v)				SetAcceptorCentileDPA(&(fta)->acceptor,(v))

#define SetLockValueForListLengthFTA(fta, max, v)	SetLockValueForListLength(&(fta)->acceptor, max, v)
#define SetHighNoiseThresholdFTA(fta, v)			SetHighNoiseThresholdDPA(&(fta)->acceptor, v)
#define SetMaximumNumberOfRecordsFTA(fta, locked, v)	SetMaximumNumberOfRecordsDPA(&(fta)->acceptor, locked, v)

#ifdef __cplusplus
}
#endif

#endif
