/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: SystemExceptionsControlInterface.h $
 * $Revision: 1 $
 * $Date: 4/11/08 12:16 $
 */

/**
 * \file SystemExceptionsControlInterface.h
 * This file contains the declarations of the handler routines for the SystemExceptions control 
 * ControlInterface. The SystemExceptions control messages allow for the configuration and management
 * of the SystemExceptions.
 */

#ifndef SYSTEM_EXCEPTIONS_CONTROL_INTERFACE_H
#define SYSTEM_EXCEPTIONS_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoGetToPSyncSystemExceptions(uint8 *numberOfExceptions, ToPSyncSystemExceptionReport toPSyncSystemExceptionReport);
ToPSyncConfigResult DoSetToPSyncSystemExceptionsConfigurations(Bool reportExceptionsUnsolicited);




#ifdef __cplusplus
}
#endif

#endif

