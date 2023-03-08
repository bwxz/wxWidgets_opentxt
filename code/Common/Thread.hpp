/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: Thread.hpp $
Version     $Revision: 5 $
Date		$Date: 11/03/08 16:08 $

*/

#ifndef THEAD_H
#define THEAD_H
#include "General.h"
#include "Windows.h"

class Thread
{
private:
	const uint	stackSize;

#ifdef _MSC_VER
	HANDLE msThread;
#endif
#ifdef __BCPLUSPLUS__
        int thread_id;
#endif

	void (*runFunction) () ;
	void (*initialiseFunction) () ;

	static void StartFunction(void*,...);	// first parameter is class pointer
public:
	Thread(void (*aRunFunction) (), uint myStackSize = 16384);
	Thread(void (*aInitialiseFunction) (), void (*aRunFunction) (), uint myStackSize = 16384);
	bool Run(); // returns true on success

};

#endif

