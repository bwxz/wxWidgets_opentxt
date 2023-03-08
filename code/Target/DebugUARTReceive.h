#ifndef DEBUG_UART_RECEIVE_H
#define DEBUG_UART_RECEIVE_H

void DebugRxInit(void);
void DebugRxParser(uint8 uart, uint8 rxCh);

#endif
