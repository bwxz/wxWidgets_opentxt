/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.

Name        $Workfile: $
Version     $Revision: #1 $
Date        $Date: 2015/10/27 $
*/

#ifndef API_MSG_HANDLER_MAP_H
#define API_MSG_HANDLER_MAP_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "mmAPIRegisterMap.h"


void mmAPIWriteMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void mmAPIReadMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void mmApiGetParameterAddresss(uint32 address, uint8 *mainBlock, uint16 *subBlock, uint16 *offset);


ToPSyncConfigResult GetPnPConfigurationProfile(void);
ToPSyncConfigResult SetPnPConfigurationProfile(void);
ToPSyncConfigResult WritePnPConfigProfileToFlash(void);

#endif
