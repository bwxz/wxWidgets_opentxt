/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 */

/**
 * \file ImpairmentControlInterface.h
 * This file contains the declarations of the routines for the Impairment
 * control message set. These are messages for the configuration and management of the Impairment
 */

#ifndef IMPAIRMENT_CONTROL_INTERFACE_H
#define IMPAIRMENT_CONTROL_INTERFACE_H

#include <stdlib.h>
#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "ToPSyncControlDriverCommonMessages.h"
#include "SPIInterface.h"

/* Max data-link payload size minus the size of all non-impairment-data members in NewImpairmentDataMsg gives
 * the maximum number of bytes in the data-link payload that can be used for impairment data (doubles). */
#define MAX_IMPAIRMENT_MSG_SIZE_BYTES                     200
#define NUMBER_OF_IMPAIRMENTS_PER_API_MSG                 ((unsigned int)((MAX_IMPAIRMENT_MSG_SIZE_BYTES - 22u) / sizeof(double)))
#define SET_IMPAIRMENT_CONFIGURATION_MESSAGE_LENGTH       (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 2u)
#define SET_IMPAIRMENT_CONFIGURATION_RESP_MESSAGE_LENGTH  (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH)
#define REQUEST_NEW_IMPAIRMENT_DATA_MESSAGE_LENGTH        (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 6u)
#define NEW_IMPAIRMENT_DATA_MESSAGE_LENGTH                (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH + 9u + (NUMBER_OF_IMPAIRMENTS_PER_API_MSG * sizeof(double)))
#define NEW_IMPAIRMENT_DATA_RESP_MESSAGE_LENGTH           (TOPSYNC_CONTROL_MESSAGE_HEADER_LENGTH)


#ifdef __cplusplus
extern "C" {
#endif

/* Impairment Configuration Messages. */
typedef struct
{
	ToPSyncMsgHeader header;                         /* Offset: 0  */
	ImpairmentConfiguration impairmentConfiguration; /* Offset: 16  */ /*< NOTE: In the actual API message, only the enabled flag and master port index are transmitted */
} SetImpairmentConfigurationMsg;                     /* Length: 18  */

typedef ToPSyncMsgHeader	SetImpairmentConfigurationResponseMsg;
typedef ToPSyncMsgHeader	GetImpairmentConfigurationResponseMsg;

typedef struct
{
	ToPSyncMsgHeader header;     /* Offset: 0  */
	uint8	masterPtpPortIndex;  /* Offset: 16 */
	uint8	direction;           /* Offset: 17 */
	uint32	offset;              /* Offset: 18 */ /*< The number of delay measurements that have been used so far  */
} RequestNewImpairmentDataMsg;   /* Length: 22 */

typedef struct
{
	ToPSyncMsgHeader header;                         /* Offset: 0  */
	uint8	masterPtpPortIndex;                      /* Offset: 16 */
	uint8	direction;                               /* Offset: 17 */
	uint32	offset;                                  /* Offset: 18 */
	double  data[NUMBER_OF_IMPAIRMENTS_PER_API_MSG]; /* Offset: 22 */
} NewImpairmentDataMsg;

typedef ToPSyncMsgHeader NewImpairmentDataResponseMsg;

ToPSyncConfigResult DoSetImpairmentConfiguration(ImpairmentConfiguration const* impairmentConfiguration);
ToPSyncConfigResult DoImpairmentDataMessageArrived(uint8 impairmentController, uint8 direction, uint32 offset, const double data[]);
void WriteRequestNewImpairmentDataMsg(uint8 **data, const RequestNewImpairmentDataMsg *msg);
void ReactToSetImpairmentConfigurationMsg(const EnhancedTransmissionProtocolAddress*,
										  const uint8 *requestMessage, uint16 requestMessageLength,
                                                uint8 *responseBuffer, uint16 *responseBufferLength);
void ReactToImpairmentDataMsg(const EnhancedTransmissionProtocolAddress*,
		                      const uint8 *newImpairmentDataMessage, uint16 newImpairmentDataLength,
                                    uint8 *responseBuffer, uint16 *responseBufferLength);
Bool ReadNewImpairmentDataMsg(uint8 const **data, size_t newImpairmentDataLength, NewImpairmentDataMsg *msg);

#ifdef __cplusplus
}
#endif

#endif

