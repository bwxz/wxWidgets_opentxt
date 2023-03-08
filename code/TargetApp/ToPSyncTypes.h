#ifndef TOP_SYNC_TYPES_H
#define TOP_SYNC_TYPES_H

#include "General.h"
#include "TopSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


// Ethernet defines
#define OUI_LENGTH 3
#define BOARD_ID_LENGTH (MAC_ADDRESS_LENGTH - OUI_LENGTH)
#define EUI_64_PAD_LENGTH 2


#define MILLISECONDS_IN_A_SECOND				1000


typedef struct
{
	Frequency	bandwidth[NUMBER_OF_BOOL_VALUES]; //1 = locked/closed, 0 = unlocked/open
	uint8		chainLength;
} FilterConfiguration;

typedef struct
{
	uint16 	lists;	// max of DPA_MAX_NUMBER_OF_LISTS
	uint16 	centile;
	uint16 	listLength[NUMBER_OF_BOOL_VALUES]; //1 = locked, 0 = unlocked
	float	lockValueForListLength[NUMBER_OF_BOOL_VALUES];  //lock value at which list length equals min (FALSE) and max (TRUE)
	Signal	highNoiseThreshold;
} AcceptorConfiguration;

typedef struct
{
	uint16 duration;
	uint16 minimumSamples;
} FrequencyMeasurementConfiguration;

typedef struct
{
	AcceptorConfiguration acceptor;
	FilterConfiguration phaseFilter;
	FilterConfiguration noiseFilter;

	struct
	{
		Signal on;
		Signal off;
	} noiseAlarmThreshold;

} DirectionConfiguration;

typedef struct
{
	float proportional[NUMBER_OF_BOOL_VALUES]; //1 = locked, 0 = unlocked
	float integral[NUMBER_OF_BOOL_VALUES]; //1 = locked, 0 = unlocked
} GainConfiguration;

typedef struct
{
	FilterConfiguration		filter;
	GainConfiguration		gain;
	Frequency				pllBandwidth[NUMBER_OF_BOOL_VALUES];	// pllBandwidth, filter and gain must be aligned by the function that writes
											// normally pllBandwidth is invalid if filter and gain are individually set

	Frequency				pllBandwidthCommanded[NUMBER_OF_BOOL_VALUES];	//store the required bandwidth specified by commands, valid for PTPPort only

} PhaseLockLoopConfiguration;

typedef struct
{
	FrequencyMeasurementConfiguration frequencyMeasurement;
	PhaseLockLoopConfiguration		pll; 

	//masterToSlave and slaveToMaster are not used if source is viaWire
	DirectionConfiguration			masterToSlave;
	DirectionConfiguration			slaveToMaster;

	FilterConfiguration				unselectedPhaseLagFilter; // bandwidth of source's actualLag filter

	Bool							enableFrequencySmoother;
	Bool							enableTimeSmoother;
	Bool							suppressPhaseJumps;

	Direction						delaysToUse;
	ElapsedTime						maximumPhaseError;
	ElapsedTime						configuredPhaseLag;  // the node should lag the source by this time
	ElapsedTime						previousConfiguredPhaseLag;  

//	FilterConfiguration				phaseMonitor;  //low update rate members are unused
} TimeSourceConfiguration;

typedef enum 
{
	//first elements equal PLLid

	frequencyOutput = numberOfPLLids, 
	// the frequency output of the node - the value of this is not significant 
	// but the rate of change is

	numberOfHardwareFrequencyControllers
} FrequencyControllerId;
	
/* FrequencyControllerId is used to identify the phaseAccumulator hardware- variable rate frequency generator
*/

typedef enum
{
	unstableFloor,
	stableFloor
} PacketAnalyserAlgorithm;


/* 64 bit integers are not part of standard "C". */
typedef unsigned long long int uint64;
typedef signed   long long int sint64;

//Input clocks
typedef enum {clockReal, clockDiv} DividerOutput; 
/*
clockReal is also called DivN
clockDiv is also called DivM
*/

typedef uint32 InterfaceBytePerSec; // interface rate in byte/sec e.g. 10Mbit/s == 1250000

#ifdef __cplusplus
}
#endif


#endif

