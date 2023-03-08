#ifndef VISIBLE_MASTER_H
#define VISIBLE_MASTER_H

#include "General.h"
#include "ApplicationInfrastructureInterface.h"
#include "MessageStore.h"
#include "TransmissionProtocol.h"
#include "TwoLevelAddress.h"
#include "VisibleMasterDirection.h"
#include "UTCOffsetController.h"
#include "MessageSequenceNumberGenerator.h"
#include "AlarmClient.h"
#include "AlarmMonitor.h"
#include "AcceptablePartnerController.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	// Order is important
	invalidVM,				// no master visible
	validatingVM,			// master has been seen but fewer than PTP_FOREIGN_MASTER_THRESHOLD messages have been seen
	tooFewTimingMessagesVM,	// timing message contract granted but not honoured
	notOfInterestVM,		// master is neither the selected nor better than the selected master
	requestingContractVM,	// at least PTP_FOREIGN_MASTER_THRESHOLD announce seen, timing message contract requested
	validVM					// everything is lovely
} VMState;

typedef enum
{
	announceMessageReceivedEvent,
	contractRefused,
	contractGranted,
	announceMessageTimeout,
} EventVM;


typedef struct VisibleMasterStruct
{
	VMState							state;

	struct PtpPortStruct*			port; //port through which master messages sent/received - normally fixed

	PortId							id;
	TwoLevelAddress 				address;
	VisibleMasterDirection			masterToSlave;
	VisibleMasterDirection  		slaveToMaster;
	UTCOffsetController				utcOffsetController;
	MessageSequenceNumberGenerator	messageSequenceNumberGenerator;


	ReferenceClock					grandmaster;
	uint8							transmittedPriority1; // value transmitted by master (may not be used by this node)
	uint8							transmittedPriority2; // value transmitted by master (may not be used by this node)
	Bool							twoStep;

	LogMessagePeriod				logAnnouncePeriod;
	uint16							announcePeriodTicks; // in units of tickPeriod
	uint16							ticksToAnnounceLost;

	uint32							messageCount[numberOfMessageTypes][NUMBER_OF_BOOL_VALUES];
									// 2nd index is TRUE if unicast - not all message types are used
	Bool							lockOut;
	uint32							waitToRestoreTicksRemaining;
	Bool							fromValidWhenWaitToRestoreIsActive; //when leaving valid when wait to restore is active


	ExtendedVisibleMasterStatistics vmExtStats;
} VisibleMaster;


typedef enum
{
	getVisibleMasterGrantsIssuedChangeCounter,
	getVisibleMasterState
} VisibleMasterParameter;


void InitialiseVisibleMaster(VisibleMaster* master, uint8 masterIndexNumber,
							 struct AlarmMonitorStruct* alarmMonitor);

void ResetVisibleMaster(VisibleMaster* master);
void DeleteVisibleMaster(VisibleMaster* master);

void CreateVisibleMaster(VisibleMaster* master, struct PtpPortStruct* port,
							TwoLevelAddress const* sourceAddress,
							AnnounceMessage const* message);
						// create a new record - returns TRUE on success

void VisibleMasterPortConfigurationHasChanged(VisibleMaster* master);

//excludes Announce (or V1 Sync) messages
//The following three functions return FALSE if the message is not accepted (and TLVs should not be read)
Bool VisibleMasterReactToSyncMessage(VisibleMaster* master,MessageHeader* header);
Bool VisibleMasterReactToFollowUpMessage(VisibleMaster* master,MessageHeader* header);
Bool VisibleMasterReactToDelayResponseMessage(VisibleMaster* master,MessageHeader* header);

void VisibleMasterReactToAnnounceMessage(VisibleMaster* master,
			AnnounceMessage const* message,
			TwoLevelAddress const* sourceAddress,
			AcceptablePartnerRecord const* acceptableMasterRecord,
			IEEE1588Time const* receiveTime,
			IEEE1588Time const* currentTime, uint8 isMulticast);
// including V1 Sync message

void VisibleMasterDelayRequestMessageTransmitted(VisibleMaster* master);

void VisibleMasterSlowTick(VisibleMaster* master);
#define VisibleMasterFastTick(mst) FastTickVisibleMasterDirection(&(mst)->slaveToMaster)
void VisibleMasterRequestTimingMessageGrant(VisibleMaster* master, MessageType messageType,
											LogMessagePeriod requestedLogPeriod, uint32 requestedDuration);

ReferenceClockComparison IsLeftMasterBetterThanRight(VisibleMaster const* left, VisibleMaster const* right,
		BMCABitMask const mask);

float Variance(VisibleMaster* master);
float Drift(VisibleMaster* master);


void UpdateVisibleMasterAnnouncePeriod(VisibleMaster* master, LogMessagePeriod logAnnouncePeriod);
void VisibleMasterTimeUpdatePeriodHasBeenGranted(VisibleMaster* master,
			MessageType messageType, LogMessagePeriod logPeriod, uint32 durationInSecs); //durationInSecs == 0 means period refused

void VisibleMasterTimingMessagesGrantCancelled(VisibleMaster* master, MessageType messageType);


#define VisibleMasterReadMessageCount(mst, type, unicast) ((mst)->messageCount[type][unicast])
#define ResetVisibleMasterReadMessageCount(mst) (memset((mst)->messageCount,0,sizeof(uint32)*numberOfMessageTypes*NUMBER_OF_BOOL_VALUES))
#define VisibleMasterExists(mst) ((mst)->state > invalidVM)
#define VisibleMasterIsSelected(mst) ((mst)->currentMaster != NULL)
#define VisibleMasterIsGood(mst) ((mst)->state == validVM)
#define VisibleMasterUTCOffsetKnown(mst) UTCOffsetValid(&(mst)->utcOffsetController)
#define VisibleMasterIsPRS(mst) ((mst)->grandmaster.quality.stratum <= primaryReference)
#define VisibleMasterWaitToRestoreTicksRemaining(mst) ((mst)->waitToRestoreTicksRemaining)

#define StateVM(vm) ((vm)->state)
#define ActiveVMDirection(vm,dir) ((dir)==m2s ? ActiveVMD(&(vm)->masterToSlave) : ActiveVMD(&(vm)->slaveToMaster))
#define GetVMDirectionMsg(vmd,msg) ((msg)==syncMsg ? &(vmd)->masterToSlave : &(vmd)->slaveToMaster)
#define SetVisibleMasterRequestedGrantDuration(vm,msg,d) SetVisibleMasterDirectionRequestedGrantDuration(GetVMDirectionMsg(vm,msg),(d))
#define SetVisibleMasterRequestedLogPeriod(vm,msg,p) SetVisibleMasterDirectionRequestedLogPeriod(GetVMDirectionMsg(vm,msg),(p))
#define SetVisibleMasterAcceptableLogPeriod(vm,msg,p) SetVisibleMasterDirectionAcceptableLogPeriod(GetVMDirectionMsg(vm,msg),(p))
#define VisibleMasterGetNextSequenceNumber(vm, messageType) GetNextSequenceNumber(&(vm)->messageSequenceNumberGenerator, (messageType))
#define VisibleMasterSendingTimingMessages(vm) ((vm)->state == validVM || (vm)->state == tooFewTimingMessagesVM || \
												((vm)->state == requestingContractVM && TimingMessageGrantIsActiveVMD(&(vm)->slaveToMaster)))
#define SetVisibleMasterGrantRequestThreshold(vm,msg,t) SetVisibleMasterDirectionGrantRequestThreshold(GetVMDirectionMsg(vm,msg),(t))
#define GetVisibleMasterGrantRequestThreshold(vm,msg) GetVisibleMasterDirectionGrantRequestThreshold(GetVMDirectionMsg(vm,msg))
#define SetVisibleMasterGrantRepeatPeriod(vm,msg,p) SetVisibleMasterDirectionGrantRepeatPeriod(GetVMDirectionMsg(vm,msg),(p))
#define GetVisibleMasterGrantRepeatPeriod(vm,msg) GetVisibleMasterDirectionGrantRepeatPeriod(GetVMDirectionMsg(vm,msg))

LogMessagePeriod LogTimingPeriodVM(VisibleMaster const* master, Direction direction);

#define TimingMessageGrantSituationGoodVM(vm) \
	(TimingMessageGrantSituationGoodVMD(&(vm)->masterToSlave) && \
	TimingMessageGrantSituationGoodVMD(&(vm)->slaveToMaster)) // grant given or grant not needed


#define TimingMessageGrantIsFulfilledVM(vm) \
	(TimingMessageGrantIsFulfilledVMD(&(vm)->masterToSlave) && TimingMessageGrantIsFulfilledVMD(&(vm)->slaveToMaster))

Bool VisibleMasterTimescaleIsAcceptable(VisibleMaster const* master);
	//returns FALSE if clock path required UTC/UTC/PRS and master doesn't provide it

//Private functions
void EventReceivedVM(VisibleMaster* master, EventVM event);
LogMessagePeriod FindAnnouncePeriodFromMessage(VisibleMaster const* master, AnnounceMessage const* message);
	//returns UNDEFINED_LOG_PERIOD on failure

char const* StateTextVM(VMState state);

void EnableGrantRequestsVM(VisibleMaster* master, Bool enable);
void VisibleMasterSetUpForcedGrantState(VisibleMaster* master, PortId *id, TwoLevelAddress const* sourceAddress);
void EnableForcedGrantVM(VisibleMaster* master, LogMessagePeriod delayReqLogPerio, Bool enable);
void VisibleMasterUseAccMasterMsgRates(VisibleMaster* master, PortId *id, TwoLevelAddress const* sourceAddress);
#ifdef __cplusplus
}
#endif

#endif
