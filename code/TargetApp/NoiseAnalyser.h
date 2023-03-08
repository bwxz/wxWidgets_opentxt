#ifndef NOISE_ANALYSER_H
#define NOISE_ANALYSER_H

#include "PacketFilter-FastRise.h"
#include "RateOfChangeMonitor.h"
#include "ExponentialDecay.h"
#include "HysteresisController.h"
#include "AlarmClient.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NA_NUMBER_OF_PREVIOUS_INPUTS_HELD 2 // NoiseAnalyser.c assumes the value is 2
typedef struct 
{
	FastRiseFilter			absoluteDifferenceFilter;
	FastRiseFilter			absoluteDifferenceFilterFullAcceptance;
	Signal					previousInput[NA_NUMBER_OF_PREVIOUS_INPUTS_HELD];
	float					previousAcceptance[NA_NUMBER_OF_PREVIOUS_INPUTS_HELD];
	RateOfChangeMonitor		rateOfChange;

	struct
	{
		HysteresisController	hysteresisController;
		AlarmClient				alarmClient;
	} alarmController;

	ExponentialDecay		output;

	//cache
	float					noiseChangingSwiftly;

}NoiseAnalyser;

void InitialiseNoiseAnalyser(NoiseAnalyser* analyser, 
	Frequency unlockedBandwidth, Frequency lockedBandwidth,
	Signal measurementGranularity, uint8 maxFilterChainLength,
	AlarmSource alarmSource, AlarmSourceIdentity alarmSourceIdentity, 
	struct AlarmMonitorStruct* alarmMonitor,
	Signal alarmOnThreshold, Signal alarmOffThreshold,
	ElapsedTime samplePeriod, ElapsedTime tickPeriod);

void ResetNoiseAnalyser(NoiseAnalyser* analyser);

void InputNA(NoiseAnalyser* analyser, float acceptance, Signal input);
void TickNA(NoiseAnalyser* analyser);
#define ValueNA(analyser) ValueED(&(analyser)->output)

void SetBandwidthNA(NoiseAnalyser* analyser, uint16 noiseDecayTimeConstant, Frequency unlockedBandwidth, Frequency lockedBandwidth);
#define SetChainLengthNA(analyser, filterChainLength) SetChainLengthFastRiseFilter(&(analyser)->absoluteDifferenceFilter,filterChainLength);

void SetSamplePeriodNA(NoiseAnalyser*,ElapsedTime newSamplePeriod);
void PhaseShiftNoiseAnalyser(NoiseAnalyser* analyser, Signal shift);
Bool ValidNA(NoiseAnalyser const* analyser);
#define NoiseValueChangingSwiftlyNA(analyser) ((analyser)->noiseChangingSwiftly)
void NoiseAnalyserSetAlarmThresholds(NoiseAnalyser* analyser, Signal on, Signal off);


#ifdef __cplusplus
}
#endif

#endif

