#ifndef CLOCK_OUTPUTS_H
#define CLOCK_OUTPUTS_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C"
{
#endif


// Enumerations identifying parameters.
typedef enum
{
	setSelectOutputClockSource = 0,
	setPhaseAlignedOutputClockFrequency10MHz,
	setSelectPPSOutputClockSource,
	setSelectFrequencyOutputsSource
} ClockOutputsParameter;

ToPSyncConfigResult DoSetOutputClockFrequency(uint8 output, uint32 frequencyInHertz);
ToPSyncConfigResult DoGetOutputClockFrequency(uint8 output, uint32* frequencyInHertz);
ToPSyncConfigResult DoSetOutputClockFrequencyEnabled(uint8 output, Bool enable);
ToPSyncConfigResult DoGetOutputClockFrequencyEnabled(uint8 output, Bool* enabled);
ToPSyncConfigResult DoSetOnePPSOutputClockEnabled(uint8 output, Bool enabled);
ToPSyncConfigResult DoGetOnePPSOutputClockEnabled(uint8 output, Bool *enabled);
ToPSyncConfigResult DoSetOnePPSOutputClockPulseWidth(uint8 output, uint32 pulseWidth);
ToPSyncConfigResult DoGetOnePPSOutputClockPulseWidth(uint8 output, uint32 *pulseWidth);
ToPSyncConfigResult DoSetPPSOutputSource(uint8 output, ClockId source);
ToPSyncConfigResult DoGetPPSOutputSource(uint8 output, ClockId* source);
ToPSyncConfigResult DoSetPPSOutputPeriod(uint8 output, uint8 outputPeriod);
ToPSyncConfigResult DoGetPPSOutputPeriod(uint8 output, uint8 *outputPeriod);
ToPSyncConfigResult DoGetTODOutputConfiguration(uint8 onePPSOutput, uint8 uartOutput, 
      											Bool* enabled, TODTimeCode* timeCode, UartBaudRate *uartBaudRate);
ToPSyncConfigResult DoSetTODOutputConfiguration(uint8 onePPSOutput, uint8 uartOutput,
      							 				Bool enabled, TODTimeCode timeCode, UartBaudRate uartBaudRate);
ToPSyncConfigResult DoSetPhaseAlignedOutputClockFrequency(uint8 output, uint32 divisor);
ToPSyncConfigResult DoGetPhaseAlignedOutputClockFrequency(uint8 output, uint32 *divisor, uint32 *frequencyInHertz);
void DisableAllClockOutputs(void);
void SetOutputClockFrequencyDefaults(ToPSyncPartNumber partNumber);
ToPSyncConfigResult DoSetSelectOutputClockSource(uint8 outputClockSelect,  uint8 value);
ToPSyncConfigResult DoGetSelectOutputClockSource(uint8 outputClockSelect,  uint8* value);

ToPSyncConfigResult DoSetFrequencyOutputSource(uint8 output, ClockId source);
ToPSyncConfigResult DoGetFrequencyOutputSource(uint8 output, ClockId* source);

ToPSyncConfigResult DoSetPhaseAlignedOutputClockFrequency10MHz(uint8 output, Bool enable);
ToPSyncConfigResult DoGetPhaseAlignedOutputClockFrequency10MHz(uint8 output, Bool *enabled);

ToPSyncConfigResult DoSetPhaseAlignedOutputClockDivisor(uint8 output, uint32 divisor);
ToPSyncConfigResult DoGetPhaseAlignedOutputClockDivisor(uint8 output, uint32* divisor);

#ifdef __cplusplus
}
#endif


#endif
