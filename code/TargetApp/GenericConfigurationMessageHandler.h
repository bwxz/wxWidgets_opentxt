#ifndef GENERIC_CONFIGURATION_MESSAGE_HANDLER_H
#define GENERIC_CONFIGURATION_MESSAGE_HANDLER_H

#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

void ReactToSetToPSyncParameterMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetToPSyncParameterMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGenericSetOneIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGenericGetOneIdMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);
void ReactToGenericSetTwoIdMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGenericGetTwoIdMsg(const uint8 *requestMessage, uint16 requestMessageLength,
                                                      uint8 *responseBuffer, uint16 *responseBufferLength);

#ifdef __cplusplus
}
#endif

#endif
