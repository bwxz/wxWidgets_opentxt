#ifndef FREQUENCY_CONTROLLER_H
#define FREQUENCY_CONTROLLER_H


#include "ToPSyncTypes.h"
#include "GeometricInterpolator.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef DOUBLE_TYPE FCGain;


typedef struct
{
	//Configuration
	Frequency				maxOffset; // configured limit
	ElapsedTime				samplePeriod;
	float					noisyLockThreshold;
	Signal					noisyEnvironmentLimit;

	//Operation
	struct 
	{
		float				locked;
		Signal				noise;
	} previous;

	double					integrator;
	double					mostRecentProportionalGain;

	Frequency				frequency;

	GeometricInterpolator	proportionalGainInterpolator;
	GeometricInterpolator	integralGainInterpolator;

} FrequencyController;

/* Call InitialiseFC(...) on startup.  The syncPacketPeriod is in seconds.
OscillatorQuality is a number between 1 (good) and 0 (bad) */
void InitialiseFC(FrequencyController* frequencyController, 
	Frequency maxOffset, 
	double unlockedProportionalGain, double lockedProportionalGain,
	double unlockedIntegralGain, double lockedIntegralGain,
	ElapsedTime samplePeriod);

void ResetFC(FrequencyController* frequencyController);

/* Call FCSetSamplePeriod(...) when the syncPacketPeriod needs to be changed from 
that set by FCReset(...).  The syncPacketPeriod is in seconds */
#define FCSetSamplePeriod(fc, period) ((fc)->samplePeriod = (period))

void SetFrequencyControllerGainValues(FrequencyController* frequencyController,
		double unlockedProportionalGain, double lockedProportionalGain,
		double unlockedIntegralGain, double lockedIntegralGain);

/* 
FCInput(...) is called every <samplePeriod> seconds.  FCValue(...) returns the offset 
of the required frequency from the nominal frequency of the local oscillator 
For example a return value of 0 indicates that the nominal frequency
should be used and a return value of +1e-6 indicates that a frequency of 1ppm above
nominal frequency should be used.  

phaseLag is the amount by which the node is behind the master, in seconds.  

locked is the degree to which the node is locked.  
0 indicates completely unlocked.  
1 indicates completely locked.  
*/

void FCInput(FrequencyController* frequencyController, Signal phaseLag, 
				float acceptInput, float locked, Signal noise);

void FCChangeOffset(FrequencyController* frequencyController, Frequency increase);
void FCSetOffset(FrequencyController* frequencyController, Frequency newFrequencyOffset);
void SlowTickFC(FrequencyController* frequencyController);

void PrintFC(FrequencyController const* frequencyController, char** ptrptr, long *bufferSize, Bool title);

#define FCZeroIntegrator(frequencyControllerPtr) ((frequencyControllerPtr)->integrator = 0)
#define FCValue(frequencyControllerPtr)		((frequencyControllerPtr)->frequency)
#define FCMeanValue(frequencyControllerPtr) ((Frequency)((frequencyControllerPtr)->integrator))
#define FCSetMaxOffset(fc, offset)			((fc)->maxOffset = (offset))
#define FCGetMaxOffset(fc)					((fc)->maxOffset)
#define FCSetNoisyEnvironmentLimit(fc,lt)	((fc)->noisyEnvironmentLimit = (lt))
#define FCGetNoisyEnvironmentLimit(fc)		((fc)->noisyEnvironmentLimit)
#define FCSetNoisyLockThreshold(fc,th)		((fc)->noisyLockThreshold = (th))
#define FCGetNoisyLockThreshold(fc)			((fc)->noisyLockThreshold)
#define FCGetSamplePeriod(fc)				((fc)->samplePeriod)
#define FCSetFrequency(fc, f)				((fc)->integrator = (f), (fc)->frequency = (f))

#ifdef __cplusplus
}
#endif

#endif
