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
 * \file ImageUploadControlInterface.h
 * This file contains the declarations of the routines for the Image Upload
 * control message set.
 */

#ifndef IMAGE_UPLOAD_H
#define IMAGE_UPLOAD_H

#include <mqx.h>
#include <mutex.h>
#include <lwevent.h>
#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "TransmissionProtocol.h"


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_IMAGE_UPLOAD_FILENAME_LENGTH 33

typedef enum {
	IMAGE_UPLOAD_FIRMWARE = 0,
	IMAGE_UPLOAD_PNP      = 1
} ImageUploadId;

typedef enum {
	IMAGE_UPLOAD_COMMAND_START	 = 0,
	IMAGE_UPLOAD_COMMAND_VERIFY = 1,
	IMAGE_UPLOAD_COMMAND_DECRYPT  = 2,
	IMAGE_UPLOAD_COMMAND_PROGRAM_NETWORK_UPLOAD  = 3,
	IMAGE_UPLOAD_COMMAND_MAX_NUMBER,
} ImageUploadCommand;

typedef enum {
	IMAGE_UPLOAD_STATE_IDLE      	= 0,
	IMAGE_UPLOAD_STATE_ACTIVE       = 1,
	IMAGE_UPLOAD_STATE_ERROR        = 2,
} ImageUploadState;

typedef enum {
	IMAGE_UPLOAD_ERROR_NONE         = 0,
	IMAGE_UPLOAD_ERROR_TIMEOUT      = 1,
	IMAGE_UPLOAD_ERROR_CRC_FAILURE  = 2,
	IMAGE_UPLOAD_ERROR_INCOMPATIBLE = 3,
	IMAGE_UPLOAD_DISABLED           = 4,
} ImageUploadError;

typedef enum {
	IMAGE_UPLOAD_PROTOCOL_MMAPI	= 0,
	IMAGE_UPLOAD_PROTOCOL_TFTP	= 1
} ImageUploadProtocol;

// configurable parameters
typedef struct {
	ImageUploadProtocol			protocol;

	uint32						size;
	uint32						crc;
	uint32						securityKey[2];
	uint32						blockSize;

	EnhancedTransmissionProtocolAddress address;
	char						filename[MAX_IMAGE_UPLOAD_FILENAME_LENGTH];

	ImageUploadId				id;
} ImageUploadControlParameters;

typedef struct {
	ImageUploadState				state;
	ImageUploadError				error;
	uint32*							bufferStart;
	uint32							bufferSize;
	uint32*							blockStart;
	uint32							blockNumber;

	ImageUploadControlParameters 	external;
	ImageUploadControlParameters 	internal;

	MUTEX_STRUCT 					mutex;			// task synchronisation
	LWEVENT_STRUCT 					event;

	uint32 							enable;		// enable upload operations
} ImageUploadControl;

void ImageUploadInitialise(ImageUploadControl* control,uint32* bufferStart,uint32 bufferSize);
Bool ImageUploadDoCommand(ImageUploadId id,ImageUploadCommand command);

Bool ImageUploadWriteData(ImageUploadId id,uint32 blockOffset, uint32 words, uint32 const* data);
Bool ImageUploadReadData(ImageUploadId id,uint32 blockOffset, uint32 words, uint32* data);
Bool ImageUploadSetBlockNumber(ImageUploadId id,uint32 blockNumber);
uint32 ImageUploadGetBlockNumber(ImageUploadId id);

Bool ImageUploadGetState(ImageUploadId id,ImageUploadState* state);
Bool ImageUploadGetError(ImageUploadId id,ImageUploadError* error);
Bool ImageUploadGetEnable(ImageUploadId id,Bool* enable);
Bool ImageUploadSetEnable(ImageUploadId id,Bool enable);

void ImageUploadTask(uint32  parameter);

ImageUploadControlParameters* ImageUploadGetParameters(ImageUploadId id);

#ifdef __cplusplus
}
#endif

#endif

