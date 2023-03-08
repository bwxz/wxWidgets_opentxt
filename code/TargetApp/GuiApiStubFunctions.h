/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: GuiApiStubFunctions.h $
 * $Revision: 4 $
 * $Date: 4/03/09 13:09 $
 */

/**
 * \file GuiApiStubFunctions.h
 * This file contains the stub functions for performing the requested control tasks.
 */

#ifndef GUI_STUB_FUNCTIONS_H
#define GUI_STUB_FUNCTIONS_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

/************************************************************************/
/* TIME REFERENCE SELECTOR                                              */
/************************************************************************/
ToPSyncConfigResult DoGetLockValue(float *lock);
ToPSyncConfigResult DoGetPhaseError(ElapsedTime* phaseError);
ToPSyncConfigResult DoGetSelectedTimeReference(ReferenceClock* timeReference);


/************************************************************************/
/* CURRENT MASTER                                                       */
/************************************************************************/
ToPSyncConfigResult DoGetCurrentMasterFlightTime(Direction direction, ElapsedTime* flightTime);
ToPSyncConfigResult DoGetCurrentMasterNoise(Direction direction, Signal* noise);
ToPSyncConfigResult DoGetCurrentMasterAddress(TransmissionProtocolAddress* currentMasterAddress);

/************************************************************************/
/* PTP PORTS                                                            */
/************************************************************************/
ToPSyncConfigResult DoDeleteAcceptableMasterTable(uint8 ptpPortNumber);

#endif