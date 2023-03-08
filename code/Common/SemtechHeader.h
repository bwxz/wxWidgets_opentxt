#ifndef SEMTECH_HEADER_H
#define SEMTECH_HEADER_H

//#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include "General.h"


#ifdef __cplusplus
extern "C" {
#endif


//LENGTHS
#define HDR_HEADER_ROW_LENGTH 32
#define HDR_FILE_FORMAT_VERSION_LENGTH 3
#define HDR_HEADER_LENGTH_FIELD 2
#define HDR_RESERVED_FIELD1_LENGTH 15
#define HDR_CRC_FIELD_LENGTH 24
#define HDR_RESERVED_FIELD2_LENGTH  (HDR_HEADER_ROW_LENGTH-HDR_CRC_FIELD_LENGTH)
#define HDR_HEADER_SIZE 128


//VALUES
//internal file type
#define HDR_TYPE_HEX 0
#define HDR_TYPE_BIN 1
#define HDR_TYPE_ASCII 2


//destination
#define HDR_DEST_APP 0
#define HDR_DEST_BOOT 1
#define HDR_DEST_SELF_TEST 2
#define HDR_DEST_SETS 3
#define HDR_DEST_NETWORKAPP 4


#define FILE_NAME_LENGTH	30


struct VersionHeaderStruct
{
	uint8		fileFormatVersion[HDR_FILE_FORMAT_VERSION_LENGTH];
	uint16		topsyncHeaderLength;
	uint8		internalFileType;
	uint8		destination;
	Bool		merged;
	Bool		encrypted;
	uint32		location;
	uint32		internalFileLength;
	uint8		reserved1[HDR_RESERVED_FIELD1_LENGTH];
	uint8		releaseVersion[HDR_HEADER_ROW_LENGTH];
	uint8		crcValue[HDR_CRC_FIELD_LENGTH];
	uint8		reserved2[HDR_HEADER_ROW_LENGTH-HDR_CRC_FIELD_LENGTH];
	uint8		reserved3[HDR_HEADER_ROW_LENGTH];
};

typedef struct VersionHeaderStruct VersionHeader;


int ReadSemtechFile(const char *binFileName, const char *outputImageFileName, VersionHeader *hdr);
uint8 *ReadSemtechFileIntoBuffer(char *binFileName, VersionHeader *hdr);
int ReadSemtechFileIntoBufferPassedIn(char const *binFileName, uint8** buffer, VersionHeader *hdr);
int ReadSemtechHeader(FILE *binFile, VersionHeader *hdr);
int OpenAndReadSemtechHeader(char const *binFileName, VersionHeader *hdr);

#ifdef __cplusplus
}
#endif

#endif
