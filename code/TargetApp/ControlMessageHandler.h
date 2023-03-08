/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: ControlMessageHandler.h $
 * $Revision: 7 $
 * $Date: 9/10/07 18:25 $
 */

/**
 * \file ControlMessageHandler.h
 * Contains the function and type declarations for processing of control messages. 
 */

#ifndef CONTROL_MESSAGE_HANDLER_H
#define CONTROL_MESSAGE_HANDLER_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8 ValidityTableEntry;
typedef void (*ExtendedProcessControlMessageFPtr)(const EnhancedTransmissionProtocolAddress*,
		                                          const uint8 *requestMessage, uint16 requestMessageLength,
                                                  uint8 *responseBuffer, uint16 *responseBufferLength);
typedef void (*ProcessControlMessageFPtr)(const uint8 *requestMessage, uint16 requestMessageLength,
                                          uint8 *responseBuffer, uint16 *responseBufferLength);

#define NOT_IMPL_MASK                           0x0
#define IMPLEMENTED_MASK						0x1
#define PART_OK_MASK							0x2
#define INITIALISING_SYSTEM_STATE_OK_MASK		0x4
#define INITIALISING_APPLICATION_STATE_OK_MASK	0x8
#define RUNNING_STATE_OK_MASK					0x10
#define EXCEPTION_STATE_OK_MASK					0x20
#define SOFTWARE_CORRUPTED_STATE_OK_MASK		0x40
#define INIT_SYS_APP_RUN_STATE_OK_MASK 			(INITIALISING_SYSTEM_STATE_OK_MASK | INITIALISING_APPLICATION_STATE_OK_MASK | RUNNING_STATE_OK_MASK)
#define INIT_APP_RUN_STATE_OK_MASK 				(INITIALISING_APPLICATION_STATE_OK_MASK | RUNNING_STATE_OK_MASK)
#define INIT_ALL_MASK 							(INITIALISING_SYSTEM_STATE_OK_MASK | INITIALISING_APPLICATION_STATE_OK_MASK	| RUNNING_STATE_OK_MASK | EXCEPTION_STATE_OK_MASK | SOFTWARE_CORRUPTED_STATE_OK_MASK)


/* Function for processing a received control message. */
void ProcessControlMessage(const uint8 *messageData, uint32 messageLength, 
						   ExternalInterface messageSourceInterface, 
						   const EnhancedTransmissionProtocolAddress* messageSourceAddress);

/* Performs initialisation of control message handler - this must be called at system start-up. */
void InitialiseControlMessageHandler(void);

#ifdef __cplusplus
}
#endif

#endif

