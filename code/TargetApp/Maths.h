/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: Maths.h $
Version     $Revision: 19 $
Date		$Date: 3/04/09 10:08 $

*/

#ifndef SMTC_MATHS_H
#define SMTC_MATHS_H

#include "General.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#ifdef __cplusplus
extern "C" {
#endif

double RealRandom(void);
   // returns a random number between 0 and 1

#define Pi() 3.14159265358979323846

    
unsigned  InitialiseRealRandom(unsigned seed
#ifdef __cplusplus
= 0
#endif
	);
 // returns seed used


//returns non zero if a carry or borrow is necessary
// add is non zero if an add is needed, otherwise the function subtracts

unsigned long GreatestCommonDenominator(unsigned long x,unsigned long y);

sint16 IntegerLog2(double input);
double IntegerAntiLog2(sint16 input); 

uint32 NormaliseValue(uint32 value);  // returns value with all but MS bit reset

#define MAX3(a,b,c) MAX(MAX((a),(b)),(c))
#define RANGECHECK(a,min,max) ((a) >= (min) && (a) <= (max) ? 1 : 0)
#ifdef __cplusplus
}
#endif

#endif
