/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: CRCFunctions.h $
 * $Revision: 5 $
 * $Date: 4/02/08 12:42 $
 */
 
/**
 * \file CRCFunctions.h
 * Contains public function declarations for CRC implementation.
 * Used by PlugPlayBoot.c, ProductBoot.c and APIFunctions.c
 */

#ifndef CRC_FUNCTIONS_H
#define CRC_FUNCTIONS_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * CRC Polynomial Definition
 */
#define CRC_POLYNOMIAL		0x04c11db7

/**
 * Calculate the CRC for a given area of memory
 * This function is called to calculate a 32-bit CRC of a specified area of memory.
 * \param Start 		The address of the start byte in the CRC'ed area.
 * \param End			The address of the end byte in the CRC'ed area.
 * \return 				32-bit CRC
 */
uint32 GetCRC(uint32 Start, uint32 End);

/**
 * Calculates the CRC for a given buffer of a given length.
 * This function will generate a 32-bit CRC from the specified block
 * of data of a known length. This function is needed by the ToPSync
 * manager GUI.
 *
 * Please note that this function will only work for a firmware buffer
 * of length (1024*512). This is because the firmware CRC is calculated
 * by taking into account only a portion of the firmware buffer, leaving
 * out the IP addressing configuration (as these are volatile settings).
 * This function uses suitable offsets to achieve that.
 *
 * \param buffer		Pointer to the firmware buffer.
 * \param length		Size of buffer. (should be (1024*512))
 * \return				The 32-bit CRC.
 */
uint32 GetCrcFromBuffer(uint8* buffer, uint32 length);



/**
 * Calculates the CRC for a given buffer from a start offset and a given length
 * This function will generate a 32-bit CRC from the specified block
 * of data of a known length. 
 *
 * Please note that this function will only work for a firmware buffer
 * of length (1024*512). This is because the firmware CRC is calculated
 * by taking into account only a portion of the firmware buffer, leaving
 * out the IP addressing configuration (as these are volatile settings).
 * This function uses suitable offsets to achieve that.
 *
 * \param buffer		Pointer to the firmware buffer.
 * \param startOffset	The offset in the buffer with which to start the CRC from
 * \param length		The length of the data to calculate the CRC
 * \return				The 32-bit CRC.
 */
uint32 GetCrcFromBufferUsingOffset(uint8* buffer, uint32 startOffset, uint32 length);


#ifdef __cplusplus
}
#endif

#endif
