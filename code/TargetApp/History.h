#ifndef HISTORY_H
#define HISTORY_H

#include "General.h"
#include "TopSyncTypes.h"
#include "SampleDivider.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef double HistoryValue;

typedef struct 
{
	Frequency value;
	float acceptance;
} HistoryElement;

typedef struct
{
	Frequency value;
	ElapsedTime acceptedSeconds; // seconds of history * mean acceptance
} HistoryMean; 


typedef struct
{
	//configuration
	uint32 maxHistoryLengthSecs;
	ElapsedTime historyLengthSecs;
	ElapsedTime ignoredSecs;

	//input
	struct 
	{
		HistoryValue value;				// sum of the product of each input and its acceptance
		float acceptance;				// sum of each acceptance
		uint32 samples;					// number of samples
		Bool  sufficientSamplesStored;	// TRUE when sufficient samples have been stored
	} input;


	//store
	HistoryElement* store;
	HistoryElement* endPtr;
	HistoryElement* nextElement;

	//Operation
	Bool storeFull; // nextElement has rolled over since last compression
	uint8 currentDivision;

	SampleDivider	sampleDivider;

	struct 
	{
		HistoryMean output;
		Bool valid; // the holdover data has not been updated since this struct was updated	
	} cache;

}History;


void InitialiseHST(History* hst, 
		uint16 storedElements, 
		uint32 maxHistoryLengthSecs, uint32 historyLengthSecs, ElapsedTime samplePeriod);

void ResetHST(History* hst);

#define IgnoreTimeHST(hst, a) ((hst)->ignoredSecs = (a))
#define GetIgnorePeriodHST(hst)((hst)->ignoredSecs)

void InputHST(History* hst, HistoryValue input, float validity);
void PhaseShiftHST(History* hst, HistoryValue shift);
Bool SetAveragingPeriodHST(History* hst, uint32 newPeriodSecs); //returns FALSE if period is too long
HistoryMean ValueHST(History const* hst);  // may update output structure


void InvalidateRecentDataHST(History* hst, ElapsedTime invalidateTime);


#define GetElementDurationHST(hst) GetOutputPeriodSD(&(hst)->sampleDivider)
#define GetAveragingPeriodHST(hst) ((hst)->historyLengthSecs)
#define StoreIsFullHST(hst) ((hst)->storeFull)
uint32 StoredSecondsHST(History* hst);

#ifdef __cplusplus
}
#endif


#endif

