#ifndef TIME_OF_DAY_INTERFACE_H
#define TIME_OF_DAY_INTERFACE_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "TimeOfDay.h"
#include "ClockPath.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct  {
	int locked;
	char timeFormat;
		// T = TAI
		// U = UTC
		// G = GPS
		// N = No epoch
} tGPSstatus;

/*
 * TOD transmit bit mask. Used to indicate which UARTs TOD date should
 * be transmitted on.
 */
#define TOD_TX_UART_0			(0x01 << 0)
#define TOD_TX_UART_1			(0x01 << 1)
#define TOD_TX_UART_MASK(uart)	(0x01 << (uart))

extern tGPSstatus GPSstatusRx;

void TransmitToD(ClockPath const *clockPath, uint8 uart, ToPSyncTimeOfDay const* utcTimeOfDay,
		IEEE1588Time const* taiTime, tGPSstatus const* gpsStatus);
void DeliverToD(uint8 uart, ToPSyncTimeOfDay const* time, ToPSyncTimescale timescale);
void SendToPSyncGPSTime(ClockPath *clockPath, uint8 uart);
void ToDInterfaceTransmit(uint8 clockPathIndex);

/*
 * TOD interface accessors
 */
Bool TODInterfaceReceiveEnabledSet(uint8 uart, Bool receiveEnabled);
Bool TODInterfaceReceiveEnabledGet(uint8 uart, Bool *receiveEnabled);
Bool TODInterfaceTransmitEnabledSet(uint8 uart, Bool transmitEnabled);
Bool TODInterfaceTransmitEnabledGet(uint8 uart, Bool *transmitEnabled);
Bool TODInterfaceReceiveTODModeSet(uint8 uart, TODTimeCode receiveTODMode);
Bool TODInterfaceReceiveTODModeGet(uint8 uart, TODTimeCode *receiveTODMode);
Bool TODInterfaceTransmitTODModeSet(uint8 uart, TODTimeCode transmitTODMode);
Bool TODInterfaceTransmitTODModeGet(uint8 uart, TODTimeCode *transmitTODMode);
Bool TODInterfaceBaudRateSet(uint8 uart, UartBaudRate baudRate);
Bool TODInterfaceBaudRateGet(uint8 uart, UartBaudRate *baudRate);
Bool TODInterfaceReceiveClockLockerIndexSet(uint8 uart, uint8 receiveClockLockerIndex);
Bool TODInterfaceReceiveClockLockerIndexGet(uint8 uart, uint8 *receiveClockLockerIndex);
Bool TODInterfaceTransmitClockPathIndexSet(uint8 uart, uint8 transmitClockPathIndex);
Bool TODInterfaceTransmitClockPathIndexGet(uint8 uart, uint8 *transmitClockPathIndex);

#ifdef __cplusplus
}
#endif


#endif

