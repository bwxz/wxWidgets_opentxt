#ifndef FREQUENCY_OFFSET_ESTIMATOR_H
#define FREQUENCY_OFFSET_ESTIMATOR_H

#include "General.h"
#include "LeastSquaresCalculator.h"
#include "IEEE1588Time.h"
#include "PacketFilter-FastRise.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NEW_CALIBRATION_ALGORITHM

#define DELAY_SAMPLE_BUFFER_SIZE		9

typedef struct
{
	//Configuration
	Bool			ignoreInitialSamples;			//when true, the samples during initialIgnorePeriod will be ignored
	Bool			skipNoiseEstimate;				//when true, noise estimation will be skipped
	
	
	ElapsedTime		initialFrequencyMeasurementTime;	// configured value
	ElapsedTime		frequencyMeasurementTime;			// can be increased for a noisy delay path

	uint16			initialSampleIgnoreTime;			// In seconds, the period to ignore the initial samples
	uint16			minFrequencyMeasurementPackets;

	//noise estimator, adpative measurement time and sample median filter	
	ElapsedTime		samples[DELAY_SAMPLE_BUFFER_SIZE];
	ElapsedTime		preDiffNoise;				//pre-noise estimate before frequency estimate is carried out, to decide the time needed for frequency estimate
	ElapsedTime		minimumDiffNoise;

	ElapsedTime		lastSample;				//the last sample, actually used for frequency estimation
	ElapsedTime		actualDiffNoise;		//the noise estimated using the actual sample used for frequency estimation

	uint			nextSampleIndex;
	uint			numberSamplesInBuffer;
	uint			consecutiveSamplesSkipped;

	Bool			ignoreInitialSamplesStarted;
	Bool			noiseEstimateStarted;
	Bool			firstNoiseEstimateObtained;
	Bool			noiseEstimateCompleted;
	Bool			frequencyEstimateStarted;
	Bool			frequencyEstimateCompleted;
	Bool			noiseEstimateValid;				//Indicate whether the noise estimate accompanying frequency estimate is valid or not

	IEEE1588Time	startTime;
	IEEE1588Time	lastUpdate;

	//Components
	LeastSquaresCalculator leastSquares;

	//The following are used for new algorithm
	IEEE1588Time	startingTime;
	IEEE1588Time	endingTime;

	ElapsedTime		frequencyOffset;
	ElapsedTime		initialPhase;
	ElapsedTime		noiseLevel;

	ElapsedTime		measurementTimePerUnit;
	ElapsedTime		frequencyOffsetUnit[3];
	ElapsedTime		initialPhaseUnit[3];
	ElapsedTime		actualDiffNoiseUnit[3];

	uint			currentUnitIndex;
	uint			measurementTimeMultiple;

	IEEE1588Time	startTimeUnit[3];
	
	//Components
	LeastSquaresCalculator leastSquareUnit;

} FrequencyOffsetEstimator;

void InitialiseFrequencyOffsetEstimator(FrequencyOffsetEstimator* estimator,
			ElapsedTime frequencyMeasurementTime, uint16 minFrequencyMeasurementPackets);

void ResetFrequencyOffsetEstimator(FrequencyOffsetEstimator* estimator);

void ConfigureFrequencyOffsetEstimator(FrequencyOffsetEstimator* estimator,
					ElapsedTime frequencyMeasurementTime, uint16 minFrequencyMeasurementPackets);

void InputFOE(FrequencyOffsetEstimator* estimator, IEEE1588Time const* sendTime, ElapsedTime delay);
//returns true when the estimate is complete

#ifndef NEW_CALIBRATION_ALGORITHM
#define GetFrequencyOffset(estimator) ((Frequency) GradientLSC(&(estimator)->leastSquares))
#else
#define GetFrequencyOffset(estimator) ((estimator)->frequencyOffset)
ElapsedTime GetCurrentPhaseOffsetNew(FrequencyOffsetEstimator const* estimator, IEEE1588Time const* endTime);
#endif

ElapsedTime GetCurrentPhaseOffset(FrequencyOffsetEstimator const* estimator);

//ElapsedTime GetMeasurementDuration(FrequencyOffsetEstimator const* estimator);
#define IsComplete(estimator) ((estimator)->frequencyEstimateCompleted)
void SetIgnoreInitialSampleTime(FrequencyOffsetEstimator* estimator, uint period);
void SetToSkipNoiseEstimation(FrequencyOffsetEstimator* estimator);

#ifdef __cplusplus
}
#endif

#endif
