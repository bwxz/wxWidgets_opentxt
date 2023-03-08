#ifndef HYSTERESIS_CONTROLLER_H
#define HYSTERESIS_CONTROLLER_H

#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	float loGoingThreshold; // input below this sets "value" to false
	float hiGoingThreshold; // input above this sets "value" to true
	Bool  value;
	Bool  initialValue;
} HysteresisController;

void InitialiseHysteresisController(HysteresisController* hyc,
				float loGoingThreshold, float hiGoingThreshold, Bool initialValue);
#define ResetHyC(hyc) {(hyc)->value = (hyc)->initialValue;}

void InputHyC(HysteresisController* hyc,float input);
#define IsSetHyC(hyc) ((hyc)->value)

#define SetHiThresholdHyC(hyc, val) {(hyc)->hiGoingThreshold = val;}
#define SetLoThresholdHyC(hyc, val) {(hyc)->loGoingThreshold = val;}

#define GetHiThresholdHyC(hyc) ((hyc)->hiGoingThreshold)
#define GetLoThresholdHyC(hyc) ((hyc)->loGoingThreshold)


#ifdef __cplusplus
}
#endif

#endif


