/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: PhysicalPortControlInterface.h $
 * $Revision: 2 $
 * $Date: 26/01/09 17:40 $
 */

/**
 * \file PhysicalPortControlInterface.h
 * This file contains the declarations of the handler routines for the PhysicalPort control
 * ControlInterface. The PhysicalPort control messages allow for the configuration and management
 * of the Physical Ports.
 */

#ifndef PHYSICAL_PORT_CONTROL_INTERFACE_H
#define PHYSICAL_PORT_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetMasterLoadLimit(uint8 ptpPortNumber, MasterLoadLimit limitType, sint32 value);
ToPSyncConfigResult DoGetMasterLoadLimit(uint8 ptpPortNumber, MasterLoadLimit limitType, sint32 *value);

ToPSyncConfigResult DoSetPhysicalPortParameter(uint8 ptpPortNumber, uint16 param, float value);
ToPSyncConfigResult DoGetPhysicalPortParameter(uint8 ptpPortNumber, uint16 param, float *value);
ToPSyncConfigResult DoGetIssuedGrantDetailsMsg(uint8 ptpPortNumber, MessageType messageType, uint16 index, GrantStatus *grantStatus);
ToPSyncConfigResult DoGetIssuedGrantDetailsByPtpPortMsg(uint8 ptpPortNumber, MessageType messageType, uint16 index, GrantStatus *grantStatus);


#ifdef __cplusplus
}
#endif

#endif
