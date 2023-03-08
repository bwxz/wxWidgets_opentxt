#ifndef DELAYSOURCE_H
#define DELAYSOURCE_H

#include "General.h"
#include "IEEE1588.h"
#include "IEEE1588Time.h"
#include "UTCOffsetController.h"
#include "ToPSyncInterfaceTypes.h"

typedef struct DelaySourceStruct
{
	Bool							active;
	PortId							id;		//ID of port on source sending messages
	struct PtpPortStruct*			port;

	LogMessagePeriod 				logT1T2MessagePeriod;
	LogMessagePeriod 				logT3T4MessagePeriod;

	UTCOffsetController				utcOffsetController;

	ReferenceClock					referenceClock;

	ExtendedVisibleMasterStatistics vmExtStats; // In the APIs the delay source will spoof a VM in mode 3

} DelaySource;

#define LogTimingPeriodDelaySource(source, dir) ((dir == m2s) ? (source)->logT1T2MessagePeriod : (source)->logT3T4MessagePeriod)

void DelaySourceInitialise(DelaySource* delaySource);
void ResetDelaySource(DelaySource* delaySource);

void UpdateDelaySource(DelaySource* delaySource,struct PtpPortStruct* port,uint8 const* data);

#endif
