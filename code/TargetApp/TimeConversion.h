#ifndef TIME_CONVERSION_H
#define TIME_CONVERSION_H


#include "IEEE1588Time.h"
#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "TimeOfDay.h"

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************
 WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
****************************************************************************
When not compiled on the ARC processor,
TimeConversion works only until 2108 (138 years after 1970) because
it uses 32 bit arithmetic.  The ARC compiler allows use of the long long int
data type, allowing the full range of times supported by IEEE1588Time to be
converted.
*/


ToPSyncTimeOfDay Convert1588FormatTimeToToD(IEEE1588Time const* input, Bool second60);
void ConvertToDTo1588Format(ToPSyncTimeOfDay const* timeOfDay, IEEE1588Time* result, Bool* second60);
	//second60 is true if the time is a +ve leap second (61st second of the minute)

sint64 SubtractTimeOfDay(ToPSyncTimeOfDay const* left, ToPSyncTimeOfDay const* right, Bool testForLeapSecond, Bool* definiteLeapSecond, Bool* possibleLeapSecond, Bool* positive);
	//returns seconds between left and right
	//possibleLeapSecond, definiteLeapSecond, and positive are outputs
	//positive is only true if the leap is known to be positive


Bool IsLeapYear(uint16 year);
uint16 LeapYearsSince1970(uint16 year); // excluding this year
uint16 FindMonthFromYearDay(uint day, Bool leapYear); // returns 0 to 11
uint16 YearDayOfStartOfCurrentMonth(uint month, Bool leapYear);
uint16 DaysInCurrentMonth(uint month, Bool leapYear);	// month value starts from zero
uint16 YearDayOfToday(uint16 day, uint16 month, uint16 year); // day, month and return values ALL start from zero
uint32 FirstDayOfYear(uint16 year); //returns days since 1970, of Jan 1 of year
uint16 FindYear(uint32 daysSince1970); //returns year in which the specified day occurs
ToPSyncTimeOfDay FindDate(uint32 daysSince1970); // zeroes hours, minutes and seconds
Bool ToPSyncTimeOfDayIsValid(ToPSyncTimeOfDay const* input, Bool leapSecondIsPossible);


#ifdef __cplusplus
}
#endif

#endif
