#ifndef HASH_H
#define HASH_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32 Hash(const uint8* data, int len);
uint16 QuickHash(const uint8* data, int len);

#ifdef __cplusplus
}
#endif

#endif

