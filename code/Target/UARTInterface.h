#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H  

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*ParseUARTMessage)(uint8 uart, uint8 byte);
Bool ConfigureUartInterface(uint8 uart, uint32 baudRate);
Bool ConfigureUartInterfaceForRecv(uint8 uart, uint32 baudRate, ParseUARTMessage parseUartMessage);
Bool DeconfigureUartInterfaceForRecv(uint8 uart);
void UARTTick(void);

#ifdef __cplusplus
}
#endif

#endif
