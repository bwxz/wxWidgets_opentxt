#ifndef MESSAGE_RATE_GRANTOR_H
#define MESSAGE_RATE_GRANTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "General.h"
#include "PtpPort.h"
#include "TransmissionProtocol.h"
#include "SampleDivider.h"

typedef uint32 GrantedRatePG; // messages per GRANTED_RATE_MULTIPLE_PG seconds;
#define GRANTED_RATE_MULTIPLE_PG 16

typedef struct
{
	uint32							secsRemaining;  // zero == grant is forever
	GrantedRatePG					rate;
	uint16							division;		// only transmit one 1 in division ticks
	uint16							count;
	PtpPort							*myPort;		// NULL == empty
	TransmissionProtocolAddress		client;
	PortId const *					portId;

	uint32							grantUsed; 		// number of messages sent (decremented by allowance each second)
	uint32							maxGrantUsed;	// max credit available
	uint32							allowance;		// per tick
	Bool							forcedGrant;
} GrantRecord;

typedef struct PassiveMessageRateGrantorStruct
{
	//Storage
	GrantRecord*	recordArray;
	GrantRecord*	arrayEnd;
	GrantRecord*	firstFreeRecord;
	uint16			arrayElements;

	//Fixed Configuration
	uint16			maxGrantsFixed;
	GrantedRatePG	maxTotalRateFixed;

	//Configuration
	uint16			maxGrants;
	GrantedRatePG	maxTotalRate;
	uint32			maxGrantDuration;

	LogMessagePeriod minClientLogPeriod;	//set only by SetMinClientLogPeriodPMRG
	float			maxClientRate;			//set only by SetMinClientLogPeriodPMRG

	//Operation
	GrantRecord*	nextRecordForTimeout;  // next record to decrement secsRemaining field

	GrantedRatePG	grantedRate;
	uint16			grantsIssued;

	SampleDivider	timeoutTimer;
	/* timeoutTimer controls the decrementing of record.secsRemaining*/

	SampleDivider	actionTimer;
	/*actionTimer controls the decrementing of record.grantUsed or the
	calling of the sendMessage(...) function
	*/

	uint16 			changeCounter[NUMBER_OF_PTP_MASTER_PORTS];

	GrantRecord** shadowPtrArray;
	GrantRecord** shadowPtrArrayEnd;
	uint16 		  shadowPtrArrayElements;
} PassiveMessageRateGrantor;

void InitialisePassiveMessageRateGrantor(PassiveMessageRateGrantor* grantor,
		 uint16 maxGrants, uint32 maxTotalMsgPerSec,
		 LogMessagePeriod minClientLogPeriod,
		 uint32 maxGrantDuration,
		 ElapsedTime slowTickPeriod);

void SlowTickPMRG(PassiveMessageRateGrantor* grantor);

void GrantRequestReceivedPMRG(PassiveMessageRateGrantor* grantor, PtpPort const* port,
				uint32* duration, LogMessagePeriod* logPeriod, TransmissionProtocolAddress const* client,
				PortId const *portId, Bool forcedGrant);

void CancelGrantPMRG(PassiveMessageRateGrantor* grantor, TransmissionProtocolAddress const* client, PtpPort const *port, Bool forcedGrant);
void CancelGrantAllGrantsOnPortPMRG(PassiveMessageRateGrantor* grantor, PtpPort const* port);

//Bool RequestUseOfGrantPMRG(PassiveMessageRateGrantor* grantor, TransmissionProtocolAddress const* client);
Bool RequestUseOfGrantUsingAddressPMRG(PassiveMessageRateGrantor* grantor, TransmissionProtocol protocol, uint8 const address[], PtpPort const *port);
/* Returns true if usable.
*/

Bool SetMinClientLogPeriodPMRG(PassiveMessageRateGrantor* grantor, LogMessagePeriod logPeriod);
#define GetMinClientLogPeriodPMRG(g) ((g)->minClientLogPeriod)

Bool SetMaxGrantsPMRG(PassiveMessageRateGrantor* grantor, uint16 maxGrants);
#define GetMaxGrantsPMRG(g)    ((g)->maxGrants)

Bool SetMaxRatePMRG(PassiveMessageRateGrantor* grantor, uint16 maxRate);
#define GetMaxRatePMRG(g)    ((g)->maxTotalRate / GRANTED_RATE_MULTIPLE_PG)

#define SetMaxDurationPMRG(g, d) ((g)->maxGrantDuration = (d))
#define GetMaxDurationPMRG(g)    ((g)->maxGrantDuration)

#define GetChangeCounterByPtpPortPMRG(g, masterIndex)	((g)->changeCounter[masterIndex])

uint16 GetNumberOfGrantsIssuedPMRG(PassiveMessageRateGrantor* grantor);
uint16 GetNumberOfGrantsIssuedPMRGByPtpPort(PassiveMessageRateGrantor* grantor, PtpPort const * port);
ToPSyncConfigResult GetIssuedGrantDetailsPMRG(PassiveMessageRateGrantor* grantor, uint16 index, GrantStatus *grantStatus);
ToPSyncConfigResult GetIssuedGrantDetailsByPtpPortPMRG(PassiveMessageRateGrantor* grantor, PtpPort const * port, uint16 index, GrantStatus *grantStatus);



#ifdef __cplusplus
}
#endif

#endif

