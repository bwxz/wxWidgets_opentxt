#ifndef TIME_OF_DAY_SEQUENCE_MONITORING_H
#define TIME_OF_DAY_SEQUENCE_MONITORING_H

#include "General.h"
#include "TimeOfDay.h"
#include "IEEE1588Time.h"
#include "UTCOffsetController.h"
#include "AlarmClient.h"


typedef struct
{
	ToPSyncTimeOfDay	timeOfDay;
	IEEE1588Time		receiveTime;
	ToPSyncTimescale	timescale;
	sint16				timescaleLagFromTAI;
} TimeOfDayInput;

typedef struct
{
	//Configuration
	uint8					inputPeriod;
	uint8					inputValidThreshold;
	uint8					maxMissedInputs;
	Bool					allowUnexpectedLeapSeconds;

	//Operation
	Bool					fromDedicatedInput;	// from UART or API
	TimeOfDayInput			previousInput;
	UTCOffsetController		utcOffsetController;
	uint8					inputCount; // number of consistent messages received up to messageValidThreshold
	uint16					timeoutPeriodTicks;
	uint16					ticksToTimeout;
	AlarmClient				alarmClient;	//active when time of day not received

} TimeOfDayController;

void InitialiseTimeOfDayController(TimeOfDayController* todc, uint8 inputValidThreshold, uint8 maxMissedInputs, struct AlarmMonitorStruct* alarmMonitor,AlarmSourceIdentity alarmId);
void ResetTimeOfDayController(TimeOfDayController* todc);
void TimeOfDayControllerSlowTick(TimeOfDayController* todc, IEEE1588Time const* currentTime);
void SetTimeOfDayInputPeriod(TimeOfDayController* todc, uint8 period);
#define SetTimeOfDayInputValidThreshold(todc, thr) ((todc)->inputValidThreshold = (thr))
#define GetTimeOfDayInputValidThreshold(todc) ((todc)->inputValidThreshold)
void SetTimeOfDayMaxMissedInputs(TimeOfDayController* todc, uint8 maxMissedInputs);
#define GetTimeOfDayMaxMissedInputs(todc) ((todc)->maxMissedInputs)
#define GetUTCOffsetControllerTODC(todc) (&(todc)->utcOffsetController)

Bool TimeOfDayInputReceived(TimeOfDayController* todc, ToPSyncTimeOfDay const* input, ToPSyncTimescale timescale, IEEE1588Time const* receiveTime, Bool fromDedicatedInput); //fromDedicatedInput is TRUE if it is from a UART or API
	//returns TRUE if the input is valid;

#define TimeOfDayIsValid(todc) ((todc)->inputCount > (todc)->inputValidThreshold)
#define GetTimeOfDayValue(todc) (&(todc)->previousInput.timeOfDay)
#define SetAllowUnexpectedLeapSeconds(todc, allow) ((todc)->allowUnexpectedLeapSeconds = (allow))
#define GetAllowUnexpectedLeapSeconds(todc) ((todc)->allowUnexpectedLeapSeconds)
#define AllowUnexpectedLeapSeconds(todc) ((todc)->allowUnexpectedLeapSeconds)
#define GetTimescaleLagFromTAI(todc) ((todc)->previousInput.timescaleLagFromTAI)
#define GetTimescaleToDC(todc) ((todc)->previousInput.timescale)
#define ReceivingDedicatedTimeOfDayInput(todc) ((todc)->fromDedicatedInput)


#endif

