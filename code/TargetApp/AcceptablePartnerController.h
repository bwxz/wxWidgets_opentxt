#ifndef ACCEPTABLE_PARTNERS_H
#define ACCEPTABLE_PARTNERS_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "IEEE1588.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PtpPortStruct;

#define FORCED_GRANT_UNICAST_TX_ENABLE_ANNOUNCE		  (1 << 0x0)
#define FORCED_GRANT_UNICAST_TX_ENABLE_SYNC			  (1 << 0x1)
#define FORCED_GRANT_UNICAST_TX_ENABLE_DELAY_RESPONSE (1 << 0x2)

#define FORCED_GRANT_UNICAST_TX_ENABLE_ALL (FORCED_GRANT_UNICAST_TX_ENABLE_ANNOUNCE | \
											FORCED_GRANT_UNICAST_TX_ENABLE_SYNC | \
											FORCED_GRANT_UNICAST_TX_ENABLE_DELAY_RESPONSE)
typedef struct
{
	TransmissionProtocolAddress partnerAddress; //ValidTPA() function is not used - addressValid is used instead
	PortId						partnerPortId; //ValidPortId() function is not used - ipValid is used instead
	uint8						priority1;
	uint8						priority2;
	struct PtpPortStruct*		localPort;

	Bool						valid:1;
	Bool						partnerAddressValid:1;  // indicates partnerAddress is valid
	Bool						partnerPortIdValid:1;
	Bool						unicast;
	Bool						enable;
	Bool						forcedGrant;
	Bool						useMessageRates;
	LogMessagePeriod			delayReqLogPeriod; //used in either acc master forced grant or when getting periods from acc table
	LogMessagePeriod			announceLogPeriod; //used in either acc slave forced grant or when getting periods from acc table
	LogMessagePeriod			syncLogPeriod; //used in either acc slave forced grant or when getting periods from acc table
	LogMessagePeriod			delayRespLogPeriod; //used in either acc slave forced grant or when getting periods from acc table
	LogMessagePeriod			requiredDelayReqLogPeriod;
	LogMessagePeriod			requiredAnnounceLogPeriod;
	LogMessagePeriod			requiredSyncLogPeriod;
	uint32						grantDuration;
	Bool						requirePrs;
	Bool						requireTai;
	Bool						requireUtc;
	BMCABitMask					overrideBitMask;
	uint8						overridePriority1;
	ClockStratum				overrideClockClass;
	ClockAccuracy				overrideAccuracy;
	OffsetScaledLogVariance		overrideLogVar;
	uint8						overridePriority2;
	uint16						overrideStepsRemoved;
	uint8						umcIndex;
	uint32						forced_grant_unicast_tx_enable;
} AcceptablePartnerRecord;

typedef struct
{
	AcceptablePartnerRecord* array;
	AcceptablePartnerRecord* end;
	uint16					 numberOfEntriesWords;
	uint32				   * entriesBitField;
	uint8					 ptpPortIndex;
	AcceptablePartnerRecord** shadowPtrArray;
	AcceptablePartnerRecord** shadowPtrEnd;
} AcceptablePartnerController;

/*the shadow ptr array contains pointers to each record in the AST in TPA order and is used or binary chopping
 * to make retrieval of entries from AST quicker.
 */


#define BITS_IN_ENTRY_WORD 32
#define SetBitFieldEntryHigh(ptr, entryId) (ptr->entriesBitField[entryId / BITS_IN_ENTRY_WORD] |= (1 << (entryId % BITS_IN_ENTRY_WORD)))
#define SetBitFieldEntryLow(ptr, entryId)  (ptr->entriesBitField[entryId / BITS_IN_ENTRY_WORD] &= ~(1 << (entryId % BITS_IN_ENTRY_WORD)))



void InitialiseAcceptablePartnerController(AcceptablePartnerController* apc,
		uint16 maxRecords, uint8 ptpPortIndex);

void ResetAcceptablePartnerController(AcceptablePartnerController* apc);

Bool AddAcceptablePartner(AcceptablePartnerController* apc,
		struct PtpPortStruct* localPort,
		TransmissionProtocolAddress const* partnerAddress, PortId const* partnerPortId,
		// either partnerAddress OR partnerPortId may be null but not both
		uint8 priority1, uint8 priority2, Bool forMaster, Bool unicast);

Bool AddAcceptableSlaveShadowPtrArray(AcceptablePartnerController* apc,
		AcceptablePartnerRecord *record);


Bool RemoveAcceptablePartner(AcceptablePartnerController* apc,
		struct PtpPortStruct const* localPort,
		TransmissionProtocolAddress const* partnerAddress,
		PortId const* partnerPortId, Bool forMaster); //returns TRUE when partner found and removed

Bool RemoveAcceptableSlaveShadowPtrArray(AcceptablePartnerController* apc,
		AcceptablePartnerRecord *record); //returns TRUE when partner found and removed


void RemovePortFromAcceptablePartnerController(AcceptablePartnerController* apc,
		struct PtpPortStruct* localPort);

AcceptablePartnerRecord* FindPartnerRecord(AcceptablePartnerController* apc,
		struct PtpPortStruct const* localPort,
		TransmissionProtocolAddress const* partnerAddress, PortId const* partnerPortId);
		// If partnerAddress is not valid, parameter MUST be NULL
		// If partnerPortId is not valid,  parameter MUST be NULL

AcceptablePartnerRecord* FindPartnerRecordExactMatch(AcceptablePartnerController* apc,
		struct PtpPortStruct const* localPort,
		TransmissionProtocolAddress const* partnerAddress, PortId const* partnerPortId);

AcceptablePartnerRecord* FindPartnerRecordBestMatch(AcceptablePartnerController* apc,
		struct PtpPortStruct const* localPort,
		TransmissionProtocolAddress const* partnerAddress, PortId const* partnerPortId);

uint16 GetNumberOfAPCRecords(AcceptablePartnerController* apc);
AcceptablePartnerRecord * GetAPCRecord(AcceptablePartnerController* apc, uint index);

uint16 GetNumberOfAPCRecordsOnPort(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort);
AcceptablePartnerRecord* GetAPCRecordOnPort(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort,uint index);

AcceptablePartnerRecord* FindPartnerRecordExactMatchChop(AcceptablePartnerController* apc,
		struct PtpPortStruct const* localPort,
		TransmissionProtocolAddress const* partnerAddress, PortId const* partnerPortId);

AcceptablePartnerRecord* FindPartnerRecordExactMatchChopShadowPtrArray(AcceptablePartnerController* apc,
		TransmissionProtocolAddress const* partnerAddress);

ToPSyncConfigResult AccMasterSetData(AcceptablePartnerController *apc, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult AccMasterGetData(AcceptablePartnerController *apc, uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
AcceptablePartnerRecord* SetEnablePartner(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool enable);
Bool GetEnablePartner(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool *enable);

AcceptablePartnerRecord* SetForcedGrantPartner(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool forcedGrant,
		LogMessagePeriod delayReqLogPeriod, LogMessagePeriod delayRespLogPeriod, LogMessagePeriod announceLogPeriod, LogMessagePeriod syncLogPeriod);

Bool GetForcedGrantPartner(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool *forcedGrant,
		LogMessagePeriod *delayReqLogPeriod, LogMessagePeriod *delayRespLogPeriod, LogMessagePeriod *announceLogPeriod, LogMessagePeriod *syncLogPeriod);

AcceptablePartnerRecord* SetUseMessageRates(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool useMessageRates,
		LogMessagePeriod desiredAnnounceLogPeriod, LogMessagePeriod desiredSyncLogPeriod, LogMessagePeriod desiredDelayReqLogPeriod,
		LogMessagePeriod requiredAnnounceLogPeriod, LogMessagePeriod requiredSsyncLogPeriod, LogMessagePeriod requiredDelayReqLogPeriod,
		uint32 grantDuration);

Bool GetUseMessageRates(AcceptablePartnerController* apc, struct PtpPortStruct const* localPort, uint index, Bool *useMessageRates,
		LogMessagePeriod *desiredAnnounceLogPeriod, LogMessagePeriod *desiredSyncLogPeriod, LogMessagePeriod *desiredDelayReqLogPeriod,
		LogMessagePeriod *requiredAnnounceLogPeriod, LogMessagePeriod *requiredSyncLogPeriod, LogMessagePeriod *requiredDelayReqLogPeriod,
		uint32 *grantDuration);


#ifdef __cplusplus
}
#endif


#endif

