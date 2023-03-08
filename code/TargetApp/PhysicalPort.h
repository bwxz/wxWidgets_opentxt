#ifndef PHYSICAL_PORT_H
#define PHYSICAL_PORT_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "IEEE1588.h"
#include "IEEE1588Time.h"
#include "PassiveMessageRateGrantor.h"
#include "GrantScheduler.h"
#include "NetworkInterfaces.h"


#ifdef __cplusplus
extern "C" {
#endif

struct PtpPortStruct;

typedef struct PhysicalPortStruct
{
	//Configuration
	uint8						connector;
	InterfaceBytePerSec			interfaceRate;

	//Operation
	GrantScheduler				announceMessageController;
	GrantScheduler				syncMessageController;
	PassiveMessageRateGrantor	delayResponseMessageController;
} PhysicalPort;

typedef enum
{
	getAnnounceNumberOfGrantsIssued,
	getAnnounceGrantsIssuedChangeCounter,
	getSyncNumberOfGrantsIssued,
	getSyncGrantsIssuedChangeCounter,
	getDelayResponseNumberOfGrantsIssued,
	getDelayResponseGrantsIssuedChangeCounter
} PhysicalPortParameter;

Bool FindPhysicalPortIndex(NetworkInterfaceId *networkInterfaceId, uint32 *physicalPortIndex);
Bool GetNextPhysicalPortIndex(uint32 *physicalPortIndex);

void InitialisePhysicalPort(PhysicalPort* port, uint8 connector,
							uint16 maxAnnounceGrants,
							uint16 maxTimingGrants,
							uint32 maxTotalAnnounceRate,
							uint32 maxTotalSyncRate,
							uint32 maxTotalDelayResponseRate,
							LogMessagePeriod minLogAnnouncePeriod,
							LogMessagePeriod maxLogAnnouncePeriod,
							LogMessagePeriod minLogTimingPeriod,
							LogMessagePeriod maxLogTimingPeriod,
							uint16 maxGrantDurationSecs,
							ElapsedTime slowTickPeriod,
							ElapsedTime fastTickPeriod);

void ResetPhysicalPort(PhysicalPort* port);
void PhysicalPortFastTick(PhysicalPort* port);
void PhysicalPortSlowTick(PhysicalPort* port);
void PhysicalPortCancelAllGrantsOnPtpPort(PhysicalPort* port, struct PtpPortStruct const* ptpPort);

void ConfigurePhysicalPortTimestampers(PhysicalPort const* port,Bool transmit,
		uint8 microFilterId,uint32 const* searchTerms, uint32 numberOfSearchTerms);
void DeconfigurePhysicalPortTimestampers(PhysicalPort const* port,Bool transmit, uint8 microFilterId);

void ConfigurePtpOperationOnPhysicalPort(PhysicalPort const* port, NetworkProtocolInterface const* protocolInterface,PtpPort const* ptpPort,Bool master,ClockId timestamper);
void DeonfigurePtpOperationOnPhysicalPort(PhysicalPort const* port, NetworkProtocolInterface const* protocolInterface,PtpPort const* ptpPort,Bool master);

void PhysicalPortDelayResponseGrantRequestReceived(PhysicalPort* port, PtpPort const* ptpPort,
				uint32* duration, LogMessagePeriod* logPeriod, TransmissionProtocolAddress const* client,
				PortId const *portId, Bool forcedGrant);

void ConfigurePtpPortSlaveOperationOnPhysicalPort(PhysicalPort const* port, NetworkProtocolInterface const* protocolInterface,PtpPort const* ptpPort,ClockId timestamper);

#define GetInterfaceRate(p) ((p)->interfaceRate)

#ifdef __cplusplus
}
#endif


#endif

