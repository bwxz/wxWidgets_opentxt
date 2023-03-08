#ifndef UTC_OFFSET_CONTROLLER_H
#define UTC_OFFSET_CONTROLLER_H

#include "General.h"
#include "IEEE1588Time.h"
#include "TimeOfDay.h"

#define LEAP_SECONDS_SINCE_1JAN1972 35

#define NOT_EXPECTED -1


#ifdef __cplusplus
extern "C" {
#endif


typedef struct UTCOffsetControllerStruct
{
	IEEE1588Time	timeOfNextLeapSecondTAI;
	UTCOffset		utc;
	UTCOffset		output; // modified copy of utc
} UTCOffsetController;

void InitialiseUTCOffsetController(UTCOffsetController* controller);
void ResetUTCOffsetController(UTCOffsetController* controller);

void UTCOffsetControllerTick(UTCOffsetController* controller,
			IEEE1588Time const* currentTAITime);
// must be called at least each second while controller->utc.valid is TRUE

void UpdateUTCOffsetController(UTCOffsetController* controller,
			IEEE1588Time const* currentTAITime,
			UTCOffset const* update);

UTCOffset const* GetCurrentUTCOffset(UTCOffsetController const* controller, //controller is const to allow the  function to be called via a const ptr.  However the call MAY actually change the structure (because time has moved on)
			IEEE1588Time const* currentTAITime);

sint16 GetFutureUTCOffset(UTCOffsetController* controller,
			IEEE1588Time const* currentTAITime, uint16 secondsIntoFuture, Bool* second60);
UTCOffset const* GetConfiguredUTCOffset(UTCOffsetController const* controller,  //controller is const to allow the  function to be called via a const ptr.  However the call MAY actually change the structure (because time has moved on)
			IEEE1588Time const* currentTAITime);

Bool Second60(UTCOffsetController* controller, IEEE1588Time const* currentTAITime); // true if the current second is 23:59:60

sint32 GetTimeToNextLeapSecondSecs(UTCOffsetController const* controller, IEEE1588Time const* currentTAITime);
	// return time to next leap second in seconds (rounded up)
	// returns NOT_EXPECTED if none expected

//leap second may be coming but if it's not within the ptp limit time then return false
Bool UTCOffsetControllerLeapSecondOutsidePtpNotification(UTCOffsetController* controller,
			IEEE1588Time const* currentTAITime);

//Configuration functions
void UTCOffsetControllerSetOffset(UTCOffsetController* controller, sint16 newOffset, Bool valid);
Bool UTCOffsetControllerSetImpendingLeapSecond(UTCOffsetController* controller, Bool set,
				IEEE1588Time const* currentTAITime, uint16 daysToLeapSecond, Bool positive, Bool updateOnlyValidAfterMidday);
	// set == FALSE means leap set is NOT expected
	// if leap second will happen at the next midnight (UTC time) daysToLeapSecond == 0
	// if leap second will happen at tomorrow's midnight (UTC time) daysToLeapSecond == 1
	// daysToLeapSecond must not be greater than MAX_WARNING_DAYS

sint16 UTCOffsetControllerDaysToLeapSecond(UTCOffsetController* controller, IEEE1588Time const* currentTime);
	//returns NOT_EXPECTED if no leap expected.
	//a value of zero, means that the leap second is expected at midnight (UTC) tonight

void UTCOffsetControllerLeapSecondDetected(UTCOffsetController* controller, IEEE1588Time const* currentTime, Bool positive);

#define UTCOffsetControllerGetTimeOfImpendingLeapSecondTAI(ctl) ((ctl)->timeOfNextLeapSecondTAI)
#define UTCOffsetValid(ctl) ((ctl)->utc.valid)

#ifdef __cplusplus
}
#endif

#endif

