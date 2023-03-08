/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: IEEE1588InterfaceTypes.h $
Version     $Revision: 17 $
Date        $Date: 13/11/08 18:04 $
*/

/**
  * \file IEEE1588InterfaceTypes.h
  *	Public IEEE1588 types.
  */
#ifndef IEEE1588_INTERFACE_TYPES_H
#define IEEE1588_INTERFACE_TYPES_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  *	IEEE1588 Clock stratum values
  */
typedef enum
{
	force = 0,								/**< Force */
	primaryReference = 6,					/**< Primary reference */			
	secondaryReference = 7,					/**< Secondary reference */
	defaultLocked = 13,						/**< Locked value */
	holdoverClockClass = 14,				/**< Holdover value */
	bestClockStratumThatCanBeSlave = 128,	/**< Best slave */
	smpte150 = 150,
	smpte158 = 158,
	reducedHoldoverClockClass = 193,		/**< Holdover reduction after period */
	smpte220 = 220,
	smpte228 = 228,
	stratum3 = 248,							/**< Stratum 3 */
	stratum4 = 254,							/**< Stratum 4 */
	highestStratumThatCanBeMaster = 254,	/**< Highest value that can be master*/
	defaultStratum = 255					/**< Default stratum */
} ClockStratum; // low values are better

/**
  *	Time sources.  These must be allocated so that good clocks have low numbers. Must start at zero.
  */
typedef enum
{
	atom,		/**< Atomic clock */
	gps,		/**< GPS */
	radio,		/**< Terrestrial */
	ptp,		/**< PTP */
	ntp,		/**< NTP */
	handSet,	/**< Hand set */	
	other,		/**< Other source */
	internalOscillator, /**< No time reference at all - may be years out */
	smpteArbF0,	/**< the time value is undefined and is not related to real time and is ARB */
	smpteF1,	/**< referenced to a local time source. Subsequent time accuracy depends on the synchronisation signal */
	numberOfTimeSourceEnumerations
} TimeSource;

typedef uint16 OffsetScaledLogVariance; /**< defined in 1588 v2 7.6.3.3 */
typedef sint8 LogMessagePeriod;			/**< The log base 2 of the message period */
typedef uint8 IEEE1588Version;			/**< The 1588 PTP version */
typedef uint8 IEEE1588Domain;			/**< The 1588 PTP domain */
typedef uint16 IEEE1588SequenceNumber;	/**< The sequence number */

#define UNDEFINED_LOG_PERIOD ((LogMessagePeriod) SINT8_MAX)
#define MAX_LOG_PERIOD       ((LogMessagePeriod) SINT8_MAX-1) /**< The max log message period */
#define INFINITE_PERIOD UNDEFINED_LOG_PERIOD  

/**
  *	The IEEE 1588 clock quality.
  */
typedef enum 
{
	NS25  = 0x20, /**< The time is accurate to within 25 ns */ 
	NS100 = 0x21, /**< The time is accurate to within 100 ns */ 
	NS250 = 0x22, /**< The time is accurate to within 250 ns */ 
	US1   = 0x23, /**< The time is accurate to within 1 us */ 
	US2_5 = 0x24, /**< The time is accurate to within 2.5 us */ 
	US10  = 0x25, /**< The time is accurate to within 10 us */ 
	US25  = 0x26, /**< The time is accurate to within 25 us */
	US100 = 0x27, /**< The time is accurate to within 100 us */
	US250 = 0x28, /**< The time is accurate to within 250 us */
	MS1   = 0x29, /**< The time is accurate to within 1 ms */
	MS2_5 = 0x2A, /**< The time is accurate to within 2.5 ms */
	MS10  = 0x2B, /**< The time is accurate to within 10 ms */
	MS25  = 0x2C, /**< The time is accurate to within 25 ms */
	MS100 = 0x2D, /**< The time is accurate to within 100 ms */
	MS250 = 0x2E, /**< The time is accurate to within 250 ms */
	S1    = 0x2F, /**< The time is accurate to within 1 s */
	S10   = 0x30, /**< The time is accurate to within 10 s */
	GT10S = 0x31, /**< The time is accurate to >10 s   */
	ACC_UNKNOWN = 0xFE /**< The time accuracy is unknown */
} ClockAccuracy;

/**
  *	The IEEE 1588 clock quality.
  */
typedef struct
{
	ClockStratum		stratum;			/**< The clock stratum or class */
	TimeSource			source;				/**< The time source */
	ClockAccuracy		accuracy;			/**< The accuracy */
	OffsetScaledLogVariance	logVariance;	/**< The log base 2 variance */
	Bool				timeValid;			/**< The time is a valid TAI time */
} ClockQuality;

#define EUI64LENGTH 8  /**< Length of IEEE EUI-64 individual assigned number */

/**
  *	Node Id.
  */
typedef struct
{
	uint8	data[EUI64LENGTH]; /**< IEEE EUI-64 individual assigned number */
} NodeId;

/**
  *	Port Id
  */
typedef struct
{
	NodeId node;	/**< Node Id */ 
	uint16 port;	/**< the port number */
} PortId;

/**
  *	Reference clock configuration.
  */
typedef struct
{
	NodeId					id;				/**< Node Id */ 
	ClockQuality 			quality;		/**< The clock quality */ 
	uint8					priority1;		/**< Priority 1 value */
	uint8					priority2;		/**< Priority 2 value */
} ReferenceClockConfiguration;

/*
 * Management message action field
 */
typedef enum
{
	get, set, response, command, acknowledge, reserved
}ManagementActionField;

#ifdef __cplusplus
}
#endif

#endif

