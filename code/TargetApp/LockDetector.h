#ifndef LOCK_DETECTOR_H
#define LOCK_DETECTOR_H

#include "General.h"
#include "PacketFilter-FastRise.h"
#include "SystemConfiguration.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	// all relative values are relative to noise and update rate.
	// The base update rate is 64Hz (BASE_UPDATE_RATE)
	struct
	{
		Signal 	increaseLimit;			// phase error above which phase will not increase 
		Signal 	reductionMinPoint;		// phase error at which lock is reduced
		Signal	reductionZeroPoint; 	// phase error at which lock is zero
	} phase;
	
	struct
	{
		float	maximum;		// lock threshold is made easier if lock is below this value
		float	factor;			// amount by which threshold is made easier	
	} easyLock;
	
	struct
	{
		Frequency 	bandwidth;
		Frequency 	openBandwidth;
		uint8		chainLength;
		Frequency 	isSignificant;

		struct
		{
			Frequency	isSmall;
		} absolute;

		struct
		{
			Frequency	isBig;
		} relative; // to noise and update rate

		float riseTimesToValid;
	} gradient;
	
	struct
	{
		// all values assume 64 Hz update rate and are relative to noise
		Signal	acceptable;		// integrated PE at which lock is reduced
		Signal	unacceptable;		// integrated PE at which lock is zero
		Signal	maxValue;			// integrated PE cannot exceed noise * limit
		float	timeConstant;		//allows integrated phase to decay to zero
	} integratedPhase;

	struct
	{
		ElapsedTime acceptable;
		ElapsedTime unacceptable;
		float minLock; //lock will not fall below this value due to time between zeros
		
	} timeBetweenZeros;

	struct
	{
		float min;
		float max;

	} lockLimit;

	float increaseRate;	//per tick
	ElapsedTime lockFallTime;
	float floor;		//min value to which lock may fall
	
} LockDetectorThresholds;


typedef struct 
{
	// Configuration
	ElapsedTime	tickPeriod; 
	ElapsedTime phaseDetectorGranularity;
	float		scaleFactor; // relative to BASE_UPDATE_RATE

	struct
	{
		//if not specified, commanded parameters have default value of 1.0f
		Bool	isSpecified;			//TRUE if user specified a value different from the default value of 1.0f

		//the actual multiple used can be adaptive if isSpecified == FALSE		
		
		float	rising;
		float	falling;
	} thresholdSensitivityMultiple;  // set to allow sensitivity to be changed
	
	LockDetectorThresholds	configured; // relative to default update rate and noise
	LockDetectorThresholds  threshold; // actual Thresholds
	
	//Operation
	Bool		inputValid;
	Signal		integratedPhaseError;
	float		locked;
	float		peakLocked; // max value that lock has reached
	Signal		phaseLag;
	Signal		phaseAtPreviousTick;
	Signal		noise;
	uint32		ticksSinceLastZeroCrossing;
	Bool		crossedZero;  //set by Tick function
	Bool		firstTick;
	Bool		inHoldover;
	Bool		movedUpwardAtLastOpportunity; 
	Bool		movedDownwardAtLastOpportunity;
	Bool		isFalling; //a state variable
	Bool		gradientFilterActive;
	float		doNotReduceLockBelowThisValue; //previous input requested that lock not be reduced below this value;
	float		maxReductionPerTick;

	//Components
	FastRiseFilter gradientFilter;

	//mode 
	PacketAnalyserAlgorithm		mode;			//currently there are two working modes, 0, or 1, which differs slightly
	float		scaleFactorOnInputPhaseLag;

} LockDetector;

/* Call LDInitialise(...) on startup.  The syncPacketPeriod is in seconds */
void LDInitialise(LockDetector* detector, ElapsedTime tickPeriod);

/* call LDReset when master has been lost */
void LDReset(LockDetector* detector);

void LDResetPhase(LockDetector* detector);  // clears phase and gradient filters - leaves lock value

void LDSetPhaseInformationUpdatePeriod(LockDetector* detector, ElapsedTime phaseInformationUpdatePeriod);
// phaseInformationUpdatePeriod is the mean period between new time error measurements being received

void LDSetPhaseFilterBandwidth(LockDetector* detector, Frequency phaseFilterBandwidth);
	//phaseFilterBandwidth is the bandwidth by which the phase lag given to LD has been filtered

#define LDSetPhaseDetectorGranularity(ld, set) ((ld)->phaseDetectorGranularity = (set))

void LDInput(LockDetector* detector, Signal phaseLag, Signal noise, Bool inputValid, float doNotReduceLockBelowThisValue);  
	// called by node to inform detector of current phase
	// both inputs are in units of seconds
void LockDetectorTick(LockDetector* detector);


/* Returns the degree of lock */
#define LDValue(detector) ((detector)->locked)
#define LDPeakValue(detector) ((detector)->peakLocked)
#define IsLocked(detector) ((detector)->booleanLocked)
#define LDGradient(detector) ((detector)->gradientFilterActive ? FastRiseFilterValue(&(detector)->gradientFilter) : 0.0)

#define LDFalling(detector) ((detector)->isFalling)

/* Holdover functions */
#define EnterHoldoverLD(detector) ((detector)->inHoldover = TRUE)
void LeaveHoldoverLD(LockDetector* detector);
#define SetLDMode(detector, m) ((detector)->mode = (m))
void SetLDScaleFactorOnInputPhaseLag(LockDetector* detector, float scaleFactor);


// Enumerations identifying thresholds
typedef enum
{
	/* NOTE NOTE NOTE NOTE NOTE NOTE 
	******************************************************************************
	LDThreshold must not be moved to include files that are visible to the public. 
	******************************************************************************
	NOTE NOTE NOTE NOTE NOTE NOTE  */




	phaseIncreaseLimit = 0,
	phaseReductionMinPoint,
	phaseReductionZeroPoint,

	easyLockMaximum = 10,
	easyLockFactor,

	gradientBandwidth = 20,
	gradientOpenBandwidth,
	gradientChainLength,
	gradientIsSignificant,
	gradientAbsoluteIsSmall,
	UNUSED_gradientRelativeIsSmall,
	gradientRelativeIsBig,
	gradientRiseTimesToValid,
	
	integratedPhaseAcceptable = 30,
	integratedPhaseUnacceptable,
	integratedPhaseMaxValue,
	integratedPhaseTimeConstant,

	timeBetweenZerosAcceptable = 40,
	timeBetweenZerosUnacceptable,
	timeBetweenZerosMinLock,

	lockLimitMin = 50,
	lockLimitMax,

	lockIncreaseRate = 60,
	setDoNotReduceLockBelowValue,
	setLockFallTime,
	setRisingMultiple,
	setFallingMultiple,

	getFuzzyLockValue = 70,

	lockDetectorParameterRange = 100

} LDThreshold;

Bool SetLDThreshold(LockDetector* detector, LDThreshold name, float value);
	//returns TRUE on success

float GetLDThreshold(LockDetector const* detector, LDThreshold name);
	//returns < 0 on failure

void SetLDThresholdMultiple(LockDetector* detector, float multiple, Bool rising, Bool falling);

	//sets all thresholds

#define GetLDThresholdMultipleRising(detector) ((detector)->thresholdSensitivityMultiple.rising)
#define GetLDThresholdMultipleFalling(detector) ((detector)->thresholdSensitivityMultiple.falling)

LDThreshold GetLDThresholdEnum(int input); //maps old value to new value

void PrintLD(LockDetector const* detector, char** ptrptr, long *bufferSize, Bool title);


#ifdef __cplusplus
}
#endif

#endif
