/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $File: //topsync/releasesTs2/R2.3.0/Target/CRCFunctions.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */
 
/**
 * \file CRCFunctions.h
 * Contains public function declarations for CRC implementation.
 * Used by PlugPlayBoot.c, ProductBoot.c and APIFunctions.c
 */

#ifndef CRC_FUNCTIONS_H
#define CRC_FUNCTIONS_H

#include "General.h"

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
uint32 GetCRC(uint32 const* Start, uint32 const* End);

/**
 * Time Delay Function
 * This function is called to cause a delay, in number of seconds, by running a loop
 * for the number of cycles required to delay the processor by approximately 1 second.
 * \param value 		number of seconds to delay
 */ 
void TimeDelay(int value);

#endif
