#ifndef CLOCK_INPUTS_H
#define CLOCK_INPUTS_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C"
{
#endif

ToPSyncConfigResult DoGetTODInputConfiguration(uint8 onePPSInput, uint8 uartInput,
      											Bool* enabled, TODTimeCode* timeCode,UartBaudRate* uartBaudRate);
ToPSyncConfigResult DoSetTODInputConfiguration(uint8 onePPSInput, uint8 uartInput,
      							 				Bool enabled, TODTimeCode timeCode, UartBaudRate uartBaudRate);
ToPSyncConfigResult DoGetTODInputStatus(uint8 uart, TODInputStatus* status);
ToPSyncConfigResult DoSetUTCOffset(uint8 onePPS, sint16 utcOffset, Bool isValid);
ToPSyncConfigResult DoGetUTCOffset(uint8 onePPS, sint16* utcOffset, Bool* isValid);
ToPSyncConfigResult DoGetUTCOffsetSource(TimeTransport timeSource, uint8 id, sint16* utcOffset, Bool* isValid);
ToPSyncConfigResult DoSetUTCOffsetSource(TimeTransport timeSource, uint8 id, sint16 utcOffset, Bool isValid);
ToPSyncConfigResult DoSetImpendingLeapSecond(uint8 onePPS, Bool set, uint16 daysToLeapSecond, Bool positive);
ToPSyncConfigResult DoSetImpendingLeapSecondSource(TimeTransport timeSource, uint8 id, Bool set, uint16 daysToLeapSecond, Bool positive);
ToPSyncConfigResult DoGetDaysToLeapSecond(uint8 onePPS, sint16* daysToLeapSecond, Bool* positive);
ToPSyncConfigResult DoGetDaysToLeapSecondNode(sint16* daysToLeapSecond, Bool* positive);
ToPSyncConfigResult DoGetDaysToLeapSecondSource(TimeTransport timeSource, uint8 id, sint16* daysToLeapSecond, Bool* positive);

ToPSyncConfigResult DoSetPTPInputClockFrequency(uint8 ptpInputClock, uint32 frequencyInHertz);
ToPSyncConfigResult DoGetPTPInputClockFrequency(uint8 ptpInputClock, uint32 *frequencyInHertz);

ToPSyncConfigResult DoSetPTPInputClockEnabled(uint8 ptpInputClock, Bool enabled);
ToPSyncConfigResult DoGetPTPInputClockEnabled(uint8 ptpInputClock, Bool *enabled);

ToPSyncConfigResult DoSetPTPInputClockSelected(uint8 ptpInputClock);
ToPSyncConfigResult DoGetPTPInputClockSelected(Bool* enabled, uint8 *ptpInputClock);

ToPSyncConfigResult DoSetPPSInputTime(uint8 ptpInputClock, ToPSyncTime const* inputTime, ToPSyncTimescale timescale);
ToPSyncConfigResult DoSetPPSInputTimeOfDay(uint8 ptpInputClock, ToPSyncTimeOfDay const* inputTime, ToPSyncTimescale timescale);

ToPSyncConfigResult DoSetClockLockingControllerParameter(uint8 id, uint16 parameter, float value);
ToPSyncConfigResult DoGetClockLockingControllerParameter(uint8 id, uint16 parameter, float* value);


#ifdef __cplusplus
}
#endif


#endif
