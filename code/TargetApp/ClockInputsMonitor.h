#ifndef CLOCK_INPUTS_MONITOR_H
#define CLOCK_INPUTS_MONITOR_H

#include "SystemConfiguration.h"
#include "General.h"

#ifdef TARGET_TS2D
	#define NUMBER_OF_PTP_INPUT_CLOCKS 8
#else
	#define NUMBER_OF_PTP_INPUT_CLOCKS 16
#endif
#define TICKS_TO_RECOGNIZE_CLOCK 5
#define SLOW_TICKS_TO_WAIT (uint)(((1 / (SLOW_TICK_PERIOD_SECS)) + 1))

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	Bool enabled;
	uint32 frequencyInHertz;
	uint8 ticks;
	uint8 priority;
}clockInputMonitorEntry;

typedef struct
{
	clockInputMonitorEntry clockInputMonitorTable[NUMBER_OF_PTP_INPUT_CLOCKS];
	uint8 slowTicksSinceLastOperation;
}ClockInputsMonitor;

clockInputMonitorEntry* GetClockInputEntry(ClockInputsMonitor* clockInputMonitor, uint8 input);
void InitialiseClockInputMonitor(ClockInputsMonitor* clockInputMonitor);
void ClockInputsMonitorSlowTick(ClockInputsMonitor* clockInputMonitor);

void SetClockInputMonitorFrequency(ClockInputsMonitor* clockInputMonitor, uint8 input, uint32 frequencyInHertz);
void ResetClockInputsMonitor(ClockInputsMonitor* clockInputMonitor);
Bool IsInputEnabledClockInputsMonitor(ClockInputsMonitor* clockInputMonitor, uint8 input);
void EnableInputClockInputsMonitor(ClockInputsMonitor* clockInputMonitor, uint8 input, Bool enable);
uint32 GetInputFrequencyClockInputsMonitor(ClockInputsMonitor* clockInputMonitor, uint8 input);

#ifdef __cplusplus
}
#endif


#endif
