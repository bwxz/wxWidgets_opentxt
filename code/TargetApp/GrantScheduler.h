#ifndef GRANT_SCHEDULER_H
#define GRANT_SCHEDULER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "SampleDivider.h"
#include "TwoLevelAddress.h"
#include "PtpPort.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef sint32 GSGrantedRate; // messages per GRANTED_RATE_MULTIPLE_GS seconds;
#define GRANTED_RATE_MULTIPLE_GS 16

typedef struct GrantTxRecordStruct
{
	struct PtpPortStruct			*port;		// NULL == empty
	uint32							messagesRemaining;
	TwoLevelAddress					address;
	PortId const *					portId;
	struct GrantTxRecordStruct*		next;
	IEEE1588SequenceNumber			sequenceNumber;
	Bool							twoStep; //when two step is true, multiply any rates by TWO_STEP_RESOURCE_MULTIPLE
	Bool 							forcedGrant;
} GrantTxRecord;



typedef struct
{
	//Initial configuration values
	struct GrantSchedulerStruct*	grantScheduler;
	LogMessagePeriod				logPeriod;

	//Operation
	GrantTxRecord*			head; // of queue
	GrantTxRecord*			next; // in queue
	uint16					grants; // number in list
	uint16					grants2Step; // number in list that are 2 step grants
	SampleDivider			sampleDivider;
} GrantRateScheduler;



typedef struct GrantSchedulerStruct
{
	//Initial configuration values
		void (*sendMessage) (struct PtpPortStruct* port,
			TwoLevelAddress *destinationAddress,	//destinationAddress->protocol may be invalid if address being unknown
			IEEE1588SequenceNumber sequenceNumber,
			LogMessagePeriod logMessagePeriod);

	LogMessagePeriod		minLogMessagePeriodFixed;	// min period issued
	LogMessagePeriod		maxLogMessagePeriodFixed;
	uint16					maxGrantsFixed;
	GSGrantedRate			maxTotalRateFixed;  //per GRANTED_RATE_MULTIPLE_GS secs

	//Configured values
	uint16					maxGrants;
	GSGrantedRate			maxTotalRate; //per GRANTED_RATE_MULTIPLE_GS secs
	LogMessagePeriod		minPermittedLogMessagePeriod;  // scheduler will not issue new grants below this period
	Bool					transmitLogMessagePeriod;
	uint32					maxDuration;

	//Constant values
	GrantTxRecord*			emptyRecordStore;
	GrantTxRecord*			emptyRecordStoreEnd;
	uint8					ratesInUse; // (maxLogMessagePeriod - minLogMessagePeriod)
	GrantRateScheduler*		rateScheduler;  //array of numberOfSchedulers

	uint16 					changeCounter[NUMBER_OF_PTP_MASTER_PORTS];

} GrantScheduler;


// one of the two function pointers MUST be set
void InitialiseGrantScheduler(GrantScheduler* grantScheduler,
		void (*sendMessageFunction) (struct PtpPortStruct* port,
			TwoLevelAddress *destinationAddress,
			IEEE1588SequenceNumber sequenceNumber,
			LogMessagePeriod txLogMessagePeriod),

		Bool transmitLogMessagePeriod,
		uint16 maxGrants,
		uint32 maxTotalRate,
		LogMessagePeriod minLogMessagePeriod,
		LogMessagePeriod maxLogMessagePeriod,
		uint32 maxDuration,
		ElapsedTime tickPeriod);

void ResetGrantScheduler(GrantScheduler* grantScheduler);

void RequestTxGrant(GrantScheduler* grantScheduler,
		struct PtpPortStruct *port,
		LogMessagePeriod* logPeriod, // updated with issued period
		Bool twoStep,  // requires more load
		uint32* duration,  // updated with issued duration (maybe zero)
		TwoLevelAddress const* address,
		PortId  const *portId,
		Bool	forcedGrant);

void GrantSchedulerTick(GrantScheduler* grantScheduler);

void GrantSchedulerCancelGrant(GrantScheduler* grantScheduler, struct PtpPortStruct* port,
							   TransmissionProtocolAddress const* address, Bool forcedGrant);

void GrantSchedulerCancelAllGrantsByPort(GrantScheduler* grantScheduler, struct PtpPortStruct const* port);

Bool GrantSchedulerSetMaxTotalRate(GrantScheduler* grantScheduler, uint32 input);
#define GrantSchedulerGetMaxTotalRate(gs)      ((gs)->maxTotalRate / GRANTED_RATE_MULTIPLE_GS)

Bool GrantSchedulerSetMaxGrants(GrantScheduler* grantScheduler, uint16 maxGrants);
#define GrantSchedulerGetMaxGrants(gs)    ((gs)->maxGrants)

Bool GrantSchedulerSetMinPerClientLogPeriod(GrantScheduler* grantScheduler, LogMessagePeriod logPeriod);
#define GrantSchedulerGetMinPerClientLogPeriod(gs) ((gs)->minPermittedLogMessagePeriod);

#define GrantSchedulerSetMaxDuration(g, d) ((g)->maxDuration = (d))
#define GrantSchedulerGetMaxDuration(g)    ((g)->maxDuration)

#define GrantSchedulerGetChangeCounterByPtpPort(g, masterIndex)  ((g)->changeCounter[masterIndex])


uint16 GrantSchedulerGetNumberOfGrantsIssued(GrantScheduler* grantScheduler);
uint16 GrantSchedulerGetNumberOfGrantsIssuedByPtpPort(GrantScheduler* grantScheduler, PtpPort const * port);
ToPSyncConfigResult GrantSchedulerGetIssuedGrantDetails(GrantScheduler* grantScheduler, uint16 index, GrantStatus *grantStatus);
ToPSyncConfigResult GrantSchedulerGetIssuedGrantDetailsByPtpPort(GrantScheduler* grantScheduler, PtpPort const * port, uint16 index, GrantStatus *grantStatus);

#ifdef __cplusplus
}
#endif

#endif
