#ifndef MIN_HISTORY_H
#define MIN_HISTORY_H

#include "General.h"
#include "SampleDivider.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	Signal	value;
	uint32	samples;
} MinHistoryElement;

typedef struct
{
	// initialisation
	uint16 storedElements;	// one smaller than array size (to ensure an unused element

	//configuration
	uint32 configuredStoredSecs;
	uint16 usedElements;	// number of elements used in calculation
	uint16 usedElementsSaved;  //used to recover the usedElements after initial period

	//input
	MinHistoryElement input; // min of all inputs received since a value was last added to store

	//store
	MinHistoryElement* store;
	MinHistoryElement* endArrayPtr;  // one past end of storage array
	MinHistoryElement* nextElement;
	Bool storeFull;

	SampleDivider	sampleDivider;

	struct
	{
		MinHistoryElement 	output;
		Bool				upToDate;
	} cache;
}MinHistory;


void InitialiseMinHST(MinHistory* hst, 
		uint16 storedElements, uint32 historyLengthSecs, ElapsedTime tickPeriod);

void ResetMinHST(MinHistory* hst);


void InputMinHST(MinHistory* hst, Signal input);
void TickMinHst(MinHistory* hst);
void SetAveragingPeriodMinHST(MinHistory* hst, uint32 newPeriodSecs);
Signal ValueMinHST(MinHistory const* history);  // may update cache
uint32 SamplesMinHST(MinHistory const* history);  // may update cache
uint16 ValidElementsMinHST(MinHistory const* history);
void PhaseShiftMinHST(MinHistory* hst, Signal shift);
void ShiftElementsOutMinHST(MinHistory* hst, sint16 shift);


#define GetAveragingPeriodMinHST(hst) ((hst)->configuredStoredSecs)

void PrintMinHST(MinHistory const* history, char** ptrptr, char const titlePrefix[], Bool printTitle);

#ifdef __cplusplus
}
#endif


#endif

