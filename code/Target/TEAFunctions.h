/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: TEAFunctions.h $
 * $Revision: 6 $
 * $Date: 29/11/07 15:10 $
 */
 
/**
 * \file TEAFunctions.h
 * This file implements the Tiny Encryption Algorithm. This file provides
 * an interface for decrypting incoming firmware messages.
 * TEA ref: http://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
 */

#ifndef TEA_FUNCTIONS_H
#define TEA_FUNCTIONS_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Size of the encryption key in 32-bit words.
 */
#define ENCRYPTION_KEY_LENGTH_WORDS 4

/** 
 * Default encryption Key
 */
#define DEFAULT_ENCRYPTION_KEY_WORD_0 0xABCDEF99
#define DEFAULT_ENCRYPTION_KEY_WORD_1 0x12345678
#define DEFAULT_ENCRYPTION_KEY_WORD_2 0x5a5a5a5a
#define DEFAULT_ENCRYPTION_KEY_WORD_3 0x01010101

/**
 * TEA minimum encrytpion block.
 */
#define MIN_ENCRYPTION_BLOCK_BYTES	8

/**
 * Set the encryption key. The encryption key required to correctly
 * encrypt/decrypt a block of data. The encryption key must be set
 * before performing any encryption/decryption operations.
 * \param encryptionKey     The 128-bit encryption key.
 */
void SetTEAEncryptionKey(const uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);

/**
 * Get the encryption key. This is the encryption key required to
 * correctly encrypt/decrypt a block of data.
 * \param encryptionKey     The 128-bit encryption key.
 */
void GetTEAEncryptionKey(uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);

/**
 * Decrypts a burst of data.
 * \param BurstData			Buffer containing data to be decrypted.
 *							NOTE: This buffer will be overwritten with the decrypted data.
 * \param BurstLength		Size of buffer.
 *							NOTE: The size must be multiples of MIN_ENCRYPTION_BLOCK_BYTES
 */
void DecryptBurst(uint8* BurstData, uint32 BurstLength);

/**
 * Encrypts a burst of data.
 * \param BurstData			Buffer containing data to be encrypted.
 *							NOTE: This buffer will be overwritten with the encrypted data.
 * \param BurstLength		Size of buffer. 
 *							NOTE: The size must be multiples of MIN_ENCRYPTION_BLOCK_BYTES
 */
void EncryptBurst(uint8* BurstData, uint32 BurstLength);

#ifdef __cplusplus
}
#endif

#endif