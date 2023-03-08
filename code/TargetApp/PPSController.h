#ifndef PPS_CONTROLLER_H
#define PPS_CONTROLLER_H

#include "General.h"
#include "SystemConfiguration.h"
#include "ToPSyncTypes.h"
#include "ClockPath.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*do we make sure that if the period is 1s then this system is not used ?
*/
typedef struct 
{
	// Configuration
	Bool enabled;
	ClockId outputSource;
	uint8 hardwareControllerId;
	uint8 outputPeriod;
	
	//Operation
	uint16 tickCount; // operation disabled when == SLOW_TICKS_PER_SECOND * outputPeriodInSeconds
	Bool outputPinEnabled;
} PPSController;


/*  */
void InitialisePPS(PPSController* pps, ClockPath* clockPath,
		Bool enabled, uint8 outputPeriod, // in secs 
		uint8 hardwareControllerId,
		ClockId outputSource);
void ResetPPS(PPSController* pps);
void SlowTickPPS(PPSController* pps);
void SetOutputPeriodPPS(PPSController* pps, uint8 outputPeriod);
#define GetOutputPeriodPPS(pps) ((pps)->outputPeriod)

void SetOutputSourcePPS(PPSController* pps, ClockId outputSource);
#define GetOutputSourcePPS(pps) ((pps)->outputSource)

#define EnabledPPS(pps) ((pps)->enabled)
#define OutputPinEnabledPPS(pps) ((pps)->outputPinEnabled)
void EnablePPS(PPSController* pps, Bool enable);


#ifdef __cplusplus
}
#endif

#endif
