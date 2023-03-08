/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: AlarmMessageHandler.h $Revision: 9 $
 * $Date: 6/11/08 17:02 $
 */

/**
 * \file AlarmMessageHandler.h
 * This file contains the declarations of the handler routines for the Alarm
 * control message set. These are messages for the configuration and management of the Alarm
 */

#ifndef ALARM_MESSAGE_HANDLER_H
#define ALARM_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


void ReactToSetAlarmSourceEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);


void ReactToGetAlarmSourceEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);


void ReactToSetAlarmSourceClientIdEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);


void ReactToGetAlarmSourceClientIdEnabledMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAlarmSetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAlarmSetArrayMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetAnyAlarmsSetMsg(const uint8 *requestMessage, uint16 requestMessageLength,
							uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif

