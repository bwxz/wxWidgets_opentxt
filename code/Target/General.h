/*
Copyright ?2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.

Name        $Workfile: General.h $
Version     $Revision: 29 $
Date        $Date: 23/06/09 11:56 $
*/

#ifndef SMTC_GENERAL_H
#define SMTC_GENERAL_H

#ifndef LINUX

#include <limits.h>

#ifdef _MSC_VER
#pragma warning ( disable : 4514 4512 4710 4355)
#endif

#if defined(_WIN32) && !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#ifdef _ARC
	#define SEMTECH_TARGET
#endif


typedef unsigned char uchar;
typedef unsigned int uint;


#define INT16BIT short
#if USHRT_MAX != 0xFFFF
#error int16 data type has the wrong size __FILE__
#else
#ifndef UINT16_MAX
#define UINT16_MAX USHRT_MAX
#endif
#endif

#define INT32BIT long
#if ULONG_MAX != 0xFFFFFFFF
#error int32 data type has the wrong size __FILE__
#else
#ifndef UINT32_MAX
#define UINT32_MAX ULONG_MAX
#endif
#endif

typedef INT32BIT int32;
typedef unsigned INT32BIT uint32;
typedef int32 sint32;

typedef INT16BIT int16;
typedef unsigned INT16BIT uint16;
typedef int16 sint16;

typedef unsigned char uint8;
typedef signed char sint8;
#define SINT8_MAX SCHAR_MAX

#else

#ifdef __KERNEL__
#  include <linux/types.h>
#else
#  include <stdint.h>
#endif

typedef unsigned char uchar;
typedef unsigned int uint;

typedef int32_t int32;
typedef uint32_t uint32;
typedef int32 sint32;

typedef int16_t int16;
typedef uint16_t uint16;
typedef int16 sint16;

typedef uint8_t uint8;
typedef int8_t  sint8;

#endif


/* Copied from stdio.h */
#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

// Bool replacement
typedef uint8 Bool;

#ifndef TRUE
	#define TRUE ((Bool) 1)
#endif

#ifndef FALSE
	#define FALSE ((Bool) 0)
#endif

#ifndef NUMBER_OF_BOOL_VALUES
	#define NUMBER_OF_BOOL_VALUES 2
#endif

#define SECONDS_PER_EPOCH 4294967296.0
#define NANO_SECONDS_PER_SECOND 1000000000UL
#define NANO_SECONDS_PER_HALF_SECOND (NANO_SECONDS_PER_SECOND/2)

#define MILLI_SECONDS_PER_SECOND 1000

#define memzero(ptr) memset(ptr,0,sizeof(*(ptr)))
#define ArrayZero(ptr,elements) memset(ptr,0,sizeof(*(ptr)) * (elements))

typedef enum { no = 0, unknown = 1, yes = 2} ThreeState;

#ifdef __cplusplus

namespace Semtech
{
	template <class T> T const Absolute(T const &a)
	{
		if (a >= 0)
			return a;
		else
			return -a;
	}

	template <class T> Bool RangeCheck(T const &a, T const &min, T const &max)
	{
		if (a < min) return false;
		if (a > max) return false;
		return true;
	}

	//lint -e{1929} (Note -- function 'Semtech::Max(const <1>&, const <1>&)' returning a reference
	template <class T> T const& Max(T const &a, T const &b)
	{
		if (a >= b) return a;
		else return b;
	}

	//lint -e{1929} (Note -- function 'Semtech::Max(const <1>&, const <1>&)' returning a reference
	template <class T> T const& Min(T const &a, T const &b)
	{
		if (a <= b) return a;
		else return b;
	}
}
#else
// C only
#define ABS(a)	 ((a) >= 0 ? (a) : -(a))


#endif
#endif
