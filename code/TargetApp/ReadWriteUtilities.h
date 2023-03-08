/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: ReadWriteUtilities.h $
Version     $Revision: 12 $
Date        $Date: 29/10/07 16:03 $
*/

#ifndef READ_WRITE_UTILITIES_HPP
#define READ_WRITE_UTILITIES_HPP

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

void WriteInteger(uint8** dataPtr, uint32 value, uint8 bytes);
uint32 ReadInteger(uint8 const ** dataPtr, uint8 bytes);
Bool ReadBoolean(uint8 const ** dataPtr);  // value stored in a single byte
void WriteBoolean(uint8** dataPtr, Bool value);

/* The following functions were added to perform read/writes on
 * the messages required by the GUI. These include multibyte structures
 * and floating point data that need to be encoded into a byte stream.
 */ 
void WriteFloat(uint8 **dataPtr, float value);
float ReadFloat(uint8 const **dataPtr);

void ReadNodeId(uint8 const** data, NodeId* nodeId);
void WriteNodeId(uint8** data, NodeId const* nodeId);

void ReadPortId(uint8 const** data, PortId* portId);
void WritePortId(uint8** data, PortId const* portId);


void WriteCorrectionField(uint8 **data, sint32 correction);


/* This function will take a uint32 or a uint16 and convert to host byte order.
eg if the host is big endian then the bytes in the data will be swapped
*/
uint32 ConvertToHostByteOrder(uint32 data, uint8 lengthInBytes);

#ifdef __cplusplus
}
#endif

#endif
