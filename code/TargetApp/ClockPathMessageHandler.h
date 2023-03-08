#ifndef CLOCK_PATH_MESSAGE_HANDLER_H
#define CLOCK_PATH_MESSAGE_HANDLER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef NOT_USED
void ReactToSetSuppressPhaseJumpMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                          uint8 *responseBuffer, uint16 *responseBufferLength);
#endif

void ReactToGetSuppressPhaseJumpMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                          uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetHoldoverAveragingPeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetHoldoverAveragingPeriodMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetHoldoverDurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetHoldoverDurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetForceHoldoverMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetForceHoldoverMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                      uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToResetHoldoverDataMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                       uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetOutputClockFrequencySmootherEnableMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOutputClockFrequencySmootherEnableMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                     uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToSetOutputClockFrequencySmootherConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                               uint8 *responseBuffer, uint16 *responseBufferLength);

void ReactToGetOutputClockFrequencySmootherConfigurationMsg(const uint8 *requestMessage, uint16 requestMessageLength, 
                                                     uint8 *responseBuffer, uint16 *responseBufferLength);



#ifdef __cplusplus
}
#endif

#endif
