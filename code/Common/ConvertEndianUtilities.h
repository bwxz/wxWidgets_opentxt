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

#ifndef CONVERT_ENDIAN_UTILITIES_HPP
#define CONVERT_ENDIAN_UTILITIES_HPP

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* This function will take a little endian uint32 or a uint16 and convert to host byte order.
eg if the host is big endian then the bytes in the data will be swapped
*/
uint32 ConvertToHostByteOrder(uint32 data, uint8 lengthInBytes);


#ifdef __cplusplus
}
#endif

#endif