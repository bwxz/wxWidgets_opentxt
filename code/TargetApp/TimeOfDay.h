#ifndef TOD_H
#define TOD_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SECS_PER_MIN 60
#define MINS_PER_HOUR 60

#ifdef _SIMULATOR
#define HOURS_PER_DAY 2  // to allow simulator to have shorter days
#else
#define HOURS_PER_DAY 24
#endif

#define MONTHS_PER_YEAR 12

#define SECS_PER_HOUR (MINS_PER_HOUR * SECS_PER_MIN)
#define SECS_PER_DAY (HOURS_PER_DAY * SECS_PER_HOUR)

#define GPS_TIMESCALE_LAG_FROM_TAI_SECS		19

#ifdef __cplusplus
}
#endif


#endif

