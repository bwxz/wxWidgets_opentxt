/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: SystemFunctions.h $
Version     $Revision: 32 $
Date        $Date: 2/03/09 14:57 $
*/

#ifndef SYSTEM_FUNCTIONS_H
#define SYSTEM_FUNCTIONS_H

#include "General.h"
#ifdef _ARC
#include "DebugPrintController.h"
#else
#include <stdio.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

//Functions provided by infra-structure
void lcdprintf(int line,char const text[],...);


void* AllocateMemory(uint bytes);

int MemoryEqual(void const* left, void const* right, uint size); // returns non zero on difference
char const* TimeText(void);  // only available if PRINT_DEBUG defined in SystemFunctions.c


int DummyPrintf(char const*,...);

void SystemFail(int lineNumber, char const fileName[]);

#ifndef _ARC
	Bool NodeIsLinear(void);
#endif


#ifdef __cplusplus
}
#endif


void PrintBytes(char const title[], uint8 const data[], uint16 length);		//Prints the bytes as a table of hex digits - 8 bytes to a row

#ifdef _ARC
	#define PRINT dbgprintfdefault
#else
	#define PRINT printf
#endif


#endif

