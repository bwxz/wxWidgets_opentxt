#ifndef TARGET_HARDWARE_DEBUG_H
#define TARGET_HARDWARE_DEBUG_H
#include <stdarg.h>
#include "DebugPrintController.h"

void OpenDebugPrintPortUdp(DebugPrintController* ctl);
void CloseDebugPrintPortUdp(DebugPrintController* ctl);
void EnableDebugPrintPortUdp(DebugPrintController* ctl, EnhancedTransmissionProtocolAddress const* sourceAddress);
Bool DebugPrintPossibleUdp(DebugPrintController *ctl);
void ShowDebugPrintUdp(DebugPrintController* ctl, char *msg);
void EnableDebugPrintPortUart(DebugPrintController* ctl, uint8 activeUart);
void DisableDebugPrintPortUart(DebugPrintController* ctl, uint8 uartPort);
void DebugUartSendMessage(char *message, unsigned short length);
Bool DebugPrintPossibleUart(DebugPrintController *ctl);
void ShowDebugPrintUart(DebugPrintController* ctl, char msg[]);
void targetprintf(DebugPrintController* ctl, const char *__format, va_list argptr);

#endif
