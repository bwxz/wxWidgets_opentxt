#ifndef HARDWARE_FREQUENCY_CONTROLLER_H
#define HARDWARE_FREQUENCY_CONTROLLER_H

#include "ToPSyncTypes.h"
#include "SampleDivider.h"
#include "VariableFrequencyOscillator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*HFC_HardwareWriteCompletedFPtr)(ClockId, Frequency);

typedef struct
{
	ClockId                        clockId;                           //< Clock Id I'm associated with. Mostly useful for debug.
	Frequency                      hardwareAccumulatedFrequencyError; //< keep track of error so output freq can be dithered to achieve on-average accuracy
	Bool                           servicedRequestedOffset;
	Frequency                      requestedOffset;
	Frequency                      compensationOffset;
	Frequency                      appliedFrequencyOffset;	          //< value applied to hardware
	Frequency                      oscillatorOffset;	              //< offset set externally from oscillator measurement
	Frequency                      hardwareIntegerUnit;               //< amount that h/w freq offset changes because of a single bit value change
	Frequency                      originalHardwareIntegerUnit;

	sint32                         lastIntegerValueWritten;

	HFC_HardwareWriteCompletedFPtr writeDoneCallbackFPtr;             //< possibly tell someone each time we write to hardware

	ElapsedTime                    tickPeriod;                        //< period at which the tick function is called
	ElapsedTime                    updateMinimumPeriod;               //< the MINIMUM period at which the hardware should be updated. This will normally come from vfo.vfoGetUpdatePeriodFPtr, but may be forced slower by the user.
	SampleDivider                  doUpdateSD;                        //< sets frequency at which h/w can be updated w.r.t HFC tick period
	VFO                            vfo;                               //< Functions to get info on h/w and h/w writing strategy
} HardwareFrequencyController;

#define SetHardwareFrequencyControllerOscillatorOffset(hfc, f) ((hfc)->oscillatorOffset = (f))
#define GetHardwareFrequencyControllerOscillatorOffset(hfc)    ((hfc)->oscillatorOffset)

void InitialiseHardwareFrequencyController(HardwareFrequencyController* hfc, ClockId myClock, ElapsedTime tickPeriod, VFO const *vfo);
void ResetHardwareFrequencyController(HardwareFrequencyController* hfc);
void SetHardwareFrequencyControllerVFO(HardwareFrequencyController* hfc, VFO const *vfo);
void SetHardwareFrequencyControllerOffset(HardwareFrequencyController* hfc, Frequency frequency);
Frequency GetHardwareFrequencyControllerOffset(HardwareFrequencyController* hfc);
void SyncHardwareFrequencyController(HardwareFrequencyController* destination, HardwareFrequencyController* source);
Frequency SetHardwareIntegerUnit(HardwareFrequencyController *hfc, Frequency newHardwareIntegerUnit);
Frequency GetHardwareIntegerUnit(HardwareFrequencyController *hfc);
HFC_HardwareWriteCompletedFPtr RegisterHardwareFrequencyControllerCallback(HardwareFrequencyController *hfc, HFC_HardwareWriteCompletedFPtr cb);
void TickHardwareFrequencyController(HardwareFrequencyController* hfc);
void ForceTickHardwareFrequencyController(HardwareFrequencyController *hfc);
void SetHardwareFrequencyControllerCompensation(HardwareFrequencyController *hfc, Frequency frequency);
Bool ForceHardwareFrequencyControllerUpdateRateSeconds(HardwareFrequencyController* hfc, ElapsedTime periodInSeconds);
ElapsedTime GetHardwareFrequencyControllerUpdateRateSeconds(HardwareFrequencyController* hfc);

#ifdef __cplusplus
}
#endif

#endif

