#ifndef __DELAY_MESSAGE_PROCESSING_COMMON_H__
#define __DELAY_MESSAGE_PROCESSING_COMMON_H__

#include "General.h"
#include "PtpPort.h"
#include "IEEE1588Time.h"
#include "IEEE1588InterfaceTypes.h"
#include "TwoLevelAddress.h"
#include "ToPSyncControlDriverMessages.h"

Bool ReadMode2TLV(
		PtpPort *const port,
		PortId const* sourcePortId,
		TwoLevelAddress *sourceAddress,
		MessageType messageType,
		uint8 const *const ptpMsgStart,
		uint8 const *const ptpMsgEnd,
		TsMinorMode const minMode,
		IEEE1588Time *const rxTime,
		sint64 *const cf);

Bool ReadMode2ReservedBytes(
		uint8 const *const ptpMsgStart,
		uint8 const *const ptpMsgEnd,
		uint8 const *const payloadEnd,
		TsMinorMode const minMode,
		TsTimestampFormat const tsFormat,
		uint32 embeddedOffsetSecsHi,
		uint32 embeddedOffsetSecsLo,
		uint32 embeddedOffsetNanos,
		IEEE1588Time *const rxTime,
		sint64 *const cf);

sint64 GetUpdatedMode2CF(uint8 const *const ptpMsgStart, uint32 rxTimeNanos);

sint64 CalculateCFAdjustmentFrom32BitNs(IEEE1588Time const* lastTimestamp,uint32 tlvTimestamp32BitNs);

#endif /* __DELAY_MESSAGE_PROCESSING_COMMON_H__ */
