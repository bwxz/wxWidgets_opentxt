#ifndef IEEE1588TIME_H
#define IEEE1588TIME_H

#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
#include <fstream>
extern "C" {
#endif



typedef struct
{
	uint32 seconds;
	uint32 nanoseconds;  // nanoseconds limited to < 1e9 
} IEEE1588Timestamp;

typedef struct
{
	IEEE1588Timestamp count; 
	uint16   epoch;
	Bool	negative; // true means the entire structure is negative
} IEEE1588Time;

typedef struct
{
	Bool			valid;
	sint16			currentOffset;		// +ve means UTC is behind TAI	
	Bool			positiveExpected;
	Bool			negativeExpected;
} UTCOffset;


#define IEEE1588TimeIsNonZero(ptr) ((ptr)->count.nanoseconds != 0 || (ptr)->count.seconds != 0 || (ptr)->epoch != 0)
#define IEEE1588TimeIsZero(ptr) (!IEEE1588TimeIsNonZero(ptr))
#define IEEE1588TimeIsNotNegative(ptr) (!(ptr)->negative)
#define IEEE1588TimeIsNegative(ptr) ((ptr)->negative)
#define TimeIsGreaterThanZero(ptr) (IEEE1588TimeIsNotNegative(ptr) && IEEE1588TimeIsNonZero(ptr))

#define TimesAreEqual(l,r) \
	((l)->count.nanoseconds == (r)->count.nanoseconds && \
	(l)->count.seconds == (r)->count.seconds && \
	(l)->epoch == (r)->epoch && \
	(l)->negative == (r)->negative)


#ifdef __cplusplus
IEEE1588Timestamp CalculateIEEE1588Timestamp(double doubleTime);
//doubleTime must be positive
#endif

ElapsedTime Subtract1588TimeFP(IEEE1588Time const* left, IEEE1588Time const* right);
IEEE1588Time AddElapsedTimeToIEEE1588Time(IEEE1588Time const* input, ElapsedTime shift);
IEEE1588Time AddNsToIEEE1588Time(IEEE1588Time const* input, sint32 shift);
IEEE1588Time Add1588Time(IEEE1588Time const* left, IEEE1588Time const* right);
IEEE1588Time Subtract1588Time(IEEE1588Time const* left, IEEE1588Time const*  right);
IEEE1588Time AddSecondsTo1588Time(IEEE1588Time const* time, sint32 seconds);
IEEE1588Time AddNanosecondsTo1588Time(IEEE1588Time const* time, sint32 nanoseconds);
//note the below truncates the nanoseconds value rather than rounds it
IEEE1588Time ConvertElapsedTimeToIEEE1588Format(ElapsedTime input);
IEEE1588Time NegateIEEE1588Time(IEEE1588Time const* input);
// input must be less than an epoch
//not used IEEE1588Time GetNearestTime(IEEE1588Time const* timeNow, uint32 eventNanoseconds);
	// event must be later than timeNow


ElapsedTime ConvertIEEE1588FormatToElapsedTime(IEEE1588Time const* input);
IEEE1588Time RoundIEEE1588TimeToNearestSecond(IEEE1588Time const* input);
IEEE1588Time RoundIEEE1588TimeToNearestPeriod(IEEE1588Time const* input, IEEE1588Time const* period); //period < 1second

Bool UpdateTimeWithNanoseconds(IEEE1588Time* time, uint32 updateTimeNS);
	// sets time to match ns value (moving time seconds forward or backward by as necessary.  
	// If this causes time to be moved by more than 2ms the function returns FALSE.  

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
std::ostream& operator<<(std::ostream&s,IEEE1588Time const&);
#endif


#endif

