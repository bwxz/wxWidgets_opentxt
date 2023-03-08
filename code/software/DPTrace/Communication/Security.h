/**
 * \file Security.h
 * Implements a function to check for a security key in a particular
 * location in the hard drive. This is used to enable certain features
 * in an application when the key is present.
 */

#ifndef SECURITY_H
#define SECURITY_H

#include "TEAFunctions.h"

bool IsSemtech(void);
bool GetEncryptionKey(uint32 encyptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);

#endif