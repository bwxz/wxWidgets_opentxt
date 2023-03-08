/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: FloatCodec.h $
Version     $Revision: 4 $
Date        $Date: 29/10/07 16:03 $
*/

/**
 * \file FloatCodec.h
 * Encoding and decoding of floating point numbers for transmitting over a network.
 */

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Write a floating point value into a byte stream.
 * This function will encode a floating point value and write it into a byte stream.
 * It will take into account the endianess of the current platform, and ensure that
 * the byte stream is big endian.
 * \param value         The floating point number to be encoded.
 * \param *streamPtr    Pointer to a byte stream in which the float will be written.
 */
void WriteSingleIEEE754Float(const float value, uint8 *streamPtr);

/**
 * Read a floating point value from a byte stream.
 * This function will read a floating point number from a byte stream and decode
 * its value. It will also convert the endian representation of the byte stream
 * (big endian) to the endian representation of the local platform (big or little
 * endian).
 * \param *value        Pointer to the decoded floating point value.
 * \param *streamPtr    Pointer to a byte stream from which the float will be read.
 */
void ReadSingleIEEE754Float(float *value, const uint8 *streamPtr);

#ifdef __cplusplus
}
#endif
