#ifndef PTP_PORT_H
#define PTP_PORT_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "TwoLevelAddress.h"
#include "IP.h"
#include "IEEE1588Messages.h"
#include "NetworkProtocolInterface.h"
#include "AcceptablePartnerController.h"
#include "UnicastMasterController.h"
#include "MessageSequenceNumberGenerator.h"
#include "MessageStore.h"
#include "PathDelayController.h"
#include "AlarmClient.h"
#include "PacketControlBlockAllocator.h"
#include "IpHeaderUtilities.h"

#include "TLVIdentities.h"
#include "DelaySource.h"

#include "CurrentMaster.h"
#include "VisibleMaster.h"
#include "VisibleMasterArray.h"

#include "ToPSyncControlDriverMessages.h"
#include "ImpairmentController.h"
#include "UserData.h"
#include "SMPTEData.h"

#ifndef _ARC
	#define _Inline
#endif


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NUMBER_TICKS_IN_DATA_REMAIN_VALID		(120*SLOW_TICKS_PER_SECOND)	
#define NUM_FRONT_BC_CHANGED_COUNT_PERIOD			(90*SLOW_TICKS_PER_SECOND)	//need to be longer than the sliding window length
#define HOLDOFF_TIMER_RESET						(-1)
#define PTP_PORT_CHANGE_COUNT_INVALID			(-1)

struct ImpairmentControllerStruct;
struct ClockLockingControllerStruct;

typedef enum
{
		bcEncryptionMin = 0,
		bcEncryptionAlg0 = bcEncryptionMin,
		bcEncryptionAlg1,
		bcEncryptionMax = bcEncryptionAlg1
} BcEncryption;

typedef enum
{
		bcUseGceMin = 0,
		bcGceNormal = bcUseGceMin,
		bcSlave_UseZeroedGce,
		bcMaster_SendGceOnly = bcSlave_UseZeroedGce,
		bcSlave_UseExternalGce,
		bcMaster_SendSceOnly = bcSlave_UseExternalGce,
		bcSlaveUseGceMax = bcSlave_UseExternalGce,
		bcMaster_SendZeroedGceOnly,
		bcMasterUseGceMax = bcMaster_SendZeroedGceOnly
} BcUseGce;

typedef enum
{
		portTimeOut,
		alignedToMaster,
		unalignedToMaster,
		faultDetected,
		faultCleared,
		portIsNowEnabled,
		portIsNowDisabled
} PortEvent;  // from IEEE 1588 Fig 9


typedef struct {
	LogMessagePeriod		idealLogPeriod; // UNDEFINED_LOG_PERIOD == disabled
	LogMessagePeriod		acceptableLogPeriod;  //not used for multicast
	uint32					grantSeconds;  //not used for multicast

} MessagePeriodStore;

typedef struct
{
	uint16 length;
	TemplateVersion version; // incremented each time the template data changes
	uint8 data[1]; // must be last element - the rest of the template is stored in the next element
} MessageTemplate;

typedef struct
{
	//for boundary clock
	Bool								enabled;			//0=disabled, 1=enabled
#ifndef SMTC_BC_USE_ACC_DELAY
	uint32								inGrandClockError;
	uint32								stageClockError;
	uint32								exGrandClockError;
#else
	uint32								outAccDelayM2S;
	uint32								outAccDelayS2M;
#endif

	uint16								ticksInDataRemainValid;
	uint16								tickCountDownNumFrontBCChanged;
	BcTxRate							txRate;					//valid for Master port
	BcTxRate							rxRate;					//valid for Slave port
	BcEncryption						encryption;
	uint8								inNumFrontBC;				//number of front active BCs, received from previous BC
	uint8								outNumFrontBC;				//number of front active BCs, sent to next BC
	BcUseGce							useGrandClockError;		//different meaning for slave or master port

	//statistics for monitering
	uint32								numberTlvReceived;

#ifdef SMTC_BC_USE_ACC_DELAY
	ElapsedTime							inAccDelayM2S;
	ElapsedTime							inAccDelayS2M;
	uint16								delayOffset;			//in unit of mini-second;
#endif

} EboundaryClock;

typedef struct
{
	Bool									acceptMulticastTimingMessages; //if no unicast grant is operational
	Bool									enableUnicastGrantRequests;
} PtpPortDirectionConfiguration;

typedef struct PtpPortModeConfigStruct
{
	ToPSyncTimestampProcessorMode		mode;

	struct {
		Mode2MasterSetupParameters          master;
		Mode2SlaveSetupParameters           slave;
	} ptpMode;

	struct {
		TsMinorMode       minorMode;
		TsTimestampFormat tsFormat;
	} timestampProcessorMode;
} PtpPortModeConfig;

typedef enum
{
		trafficProfileMin = 0,
		normalLoadTraffic = trafficProfileMin,
		heavyLoadTraffic,
		microWaveLink,
		ADSLLink,
		
		trafficProfileMax = ADSLLink
} NetworkTrafficProfile;


#define UNICAST_GRANT_REQUEST_ACCEPT_ANNOUNCE		(1 << 0x0)
#define UNICAST_GRANT_REQUEST_ACCEPT_SYNC			(1 << 0x1)
#define UNICAST_GRANT_REQUEST_ACCEPT_DELAY_RESPONSE	(1 << 0x2)

#define UNICAST_GRANT_REQUEST_ACCEPT_ALL (UNICAST_GRANT_REQUEST_ACCEPT_ANNOUNCE | \
										  UNICAST_GRANT_REQUEST_ACCEPT_SYNC | \
										  UNICAST_GRANT_REQUEST_ACCEPT_DELAY_RESPONSE)

typedef struct PtpPortStruct
{
	//configuration
	PortId									id;

	ClockId									clockId;	// timestamper aligned to ptp port

	VisibleMasterArray						visibleMasterArray;
	struct VisibleMasterStruct*				selectedVisibleMaster;
	CurrentMaster*							currentMaster;

	Bool									enabled; // false if disabled by configuration
	NetworkProtocolSubInterface*			networkSubInterface; // NULL when port is not configured
	IEEE1588Domain							domain;
	PtpPortTransmissionAddressing			transmissionAddressing;
	Bool									isMasterPort;		// TRUE: master only port, FALSE slave only port (set on init)
	Bool									beSlaveEvenWhenMastersTimeIsNotUsed;
	Bool									enablePaddingV1UDP;
	Bool									forceTwoStepOperation; // when master
	Bool									becomeMasterOnlyIfTaiKnown;
	Bool									becomeMasterOnlyIfUtcKnown;
	Bool									becomeMasterOnlyIfSourceIsPrimaryReference; // only if source is Primary Reference
	uint8									numberOfAlternateMasters;
	InterfaceBytePerSec						masterInterfaceRate;

	struct
	{
		Bool enabled;						//configured
		Bool forced;						//configured
		uint16 slowTicksToRequestTimeout;		//add least one node is requesting is padding
		// padding is active if forced OR (ticksToRequestTimeout > 0 AND enabled)
	} paddingV1Udp;

	struct
	{
		PtpPortDirectionConfiguration		masterToSlave;
		PtpPortDirectionConfiguration		slaveToMaster;
	} directionConfiguration;


	struct
	{
		MessagePeriodStore						requestedMessagePeriod[numberOfMessageTypes][NUMBER_OF_BOOL_VALUES];
			// right index is 1 if multicast, 0 if not
				// not all entries are used
		uint16									requestThreshold[numberOfMessageTypes];
		uint16									repeatPeriod[numberOfMessageTypes];
		Bool									renewalFlag;
		Bool									refusalFlag;
	} grantConfiguration;



	TimeSourceConfiguration					configuration;

	AcceptablePartnerController*			acceptableMasterController;
	AcceptablePartnerController*			acceptableSlaveController;

	UnicastMasterController*				unicastMasterController;
	struct ImpairmentControllerStruct*		impairmentController;

	// operation
	PTPPortState							state;
		// state is never portFaulty or portDisabled
		// portFaulty is represented by PtpPortServiceLayerOperational() being FALSE
		// disabled is represented by enabled being FALSE
		// when disabled or fault state == portPassive

	/* The change counter is required to ensure that received messages extracted
	 * from a message queue are up to date.  A phase jump or change of selected
	 * visible master can mean that messages already in the queue are obsolete.
	 * By tagging the message with the change counter value and comparing
	 * against the current value obsolete messages can be discarded.
	 * (This is only required for messages with receive time stamps)
	 */
	uint32									changeCount;
	MessageSequenceNumberGenerator			messageSequenceNumberGenerator;
	IEEE1588SequenceNumber					lastSignallingMsgSeqNo;

	uint32									ticksToStateChangeTimeOut;

	SampleDivider							multicastAnnounceMessageSendTimer;
	SampleDivider							multicastSyncMessageSendTimer;
	SampleDivider							pathDelayMessageSendTimer;
	struct VisibleMasterStruct*				bestMaster; // that is visible on the port
	uint8									numberOfBetterMasters;	//that are visible on the port
	PathDelayController						pathDelayController;
	AlarmClient								notOperationalAlarm;
	Bool									enableForcedMaster;
	uint16									forcedMasterIndex;
	Bool									nonRevertiveSourceSelectionOnPtpPort;
											// note this is NOT the same as non revertive operation
											// for Node Time source selection

	struct
	{
		MessageFlags						flags;
		UTCOffset							utcOffset; //utcOffset must be updated with flags - to ensure it is consistent with the leap second indicators

		Bool								twoStep; //transmits follow messages
		Bool								tooCloseToEpochRollover; // too close to send timingMessage
		Bool								paddingActive; //v1 compatibility padding is active
	}cache; // cachedData is updated by tick

	// templates are updated by slow tick
	struct
	{
		Bool			valid;
		uint32 			mask;		// used to ensure that different template versions
		uint32 			increment;  // are used for different ports

		MessageTemplate sync;
		uint8			syncBuffer[TRANSPORT_HEADER_LENGTH + V2_TIMING_MESSAGE_LENGTH + V2_UDP6_WHITE_SPACE -1];	//-1 because the first byte is last element of MessageTemplate

		MessageTemplate delayResponse;
		uint8			delayResponseBuffer[TRANSPORT_HEADER_LENGTH + V2_DELAY_RESPONSE_LENGTH + V2_UDP6_WHITE_SPACE -1];

		MessageTemplate delayResponseWithBcTlv;
		uint8			delayResponseWithBcTlvBuffer[TRANSPORT_HEADER_LENGTH + V2_DELAY_RESPONSE_LENGTH + V2_UDP6_WHITE_SPACE + SMTC_BC_TLV_LENGTH -1];

		MessageTemplate announce;
		uint8			announceBuffer[TRANSPORT_HEADER_LENGTH + V2_ANNOUNCE_MESSAGE_LENGTH + V2_UDP6_WHITE_SPACE -1];
	} messageTemplate;

	// Number of missing Announce messages before a master is considered lost from the network.
	uint16 numberOfMissingAnnounceMessagesToMasterLost;
	uint16 annnounceReceiptTimeout;

	// enhanced boundary clock
	EboundaryClock							eboundaryClock;

	struct
	{
		sint32				timeoutValueTicks;	// configurable timeout value
		sint32				ticksToTimeout;		// counter to timeout
							/* Note: holdoff.ticksToTimeout  > 0 when timer running
							 *								== 0 when expired
							 *								== HOLDOFF_TIMER_RESET (-1) when not active
							 */
	} holdoff;

	uint32 numMsgsOfUnknownTypeRxd;
	uint32 numMsgsTooShortRxd;
	uint32 numMsgsRxdForDisabledPort;
	uint32 numMsgsRxdFromUnknownSrc;

	BMCABitMask 							bmcaBitMask; //steps to perform in BMCA
	uint32 									waitToRestoreSlowTicks;

	struct
	{
		uint8					connector;
		TransmissionProtocol	protocol;
		IEEE1588Version 		ptpVersion;
		IEEE1588Domain			domain;
		uint32					virtualInterfaceNumber;
		uint32 					mHomeIndex;
	} shadowConfigure;


	/*
	 * PTP port modes. A port can be configured to be PTP-mode or timestamp processor mode, previously known as
	 * mode 2 and mode 3 respectively. Mode 1 is now just a flavour of "PTP-mode". */
	struct
	{
		PtpPortModeConfig       configLive;   /*< The configuration being actively used - should NEVER change while
		                                          the PTP port is active/configured */
		PtpPortModeConfig       configShadow; /*< The configuration entered into the mmAPI registers. These values are
		                                          copied into the live config, and the port configured appropriately
		                                          when the port is enabled, having been disabled/deconfigured */

		/* The following data structures store internal data relating to the LIVE config */
		/* PTP mode, a.k.a mode 2, specific */
		struct
		{
			/* This is a small stash that is used to pass information from the TLV parsing routines back to the
			 * caller. */
			struct
			{
				Bool			valid;
				Bool            hasSeconds;
				uint32			ns;
				uint32          s;
				uint16          epoch;
				sint32          subNanos;
			} tlvTimestampStash;
		} ptpMode;

		/* Timestamp processor mode, a.k.a mode 3, specific */
		struct
		{
			/* The delay source is the equivalent of a master */
			DelaySource delaySource;
		} timestampProcessorMode;

	} mode;

	uint8 primaryReferenceUsedInFreqTraceFlag;
	uint8 freqTraceOverride; //bit 1 is whether to override or not, bit 0 is value it should have
	UserData	userData; //can be sent /received in our own tlvs between devices
	AlarmClient	userDataReadyAlarm;
	uint8		ptpArrayIndex;
	NetworkTrafficProfile	networkTrafficProfile;
	uint32 unicast_grant_request_accept;
	Bool 		alwaysRespondToUnicastDelays;

	struct
	{
		TwoLevelAddress sourceAddress;
		PortId			sourceId;
		uint8		startingBoundaryHops;
		uint8		hops;
		ManagementActionField action;
	}managementMessageReceived;

	SmpteControl smpteControl;


} PtpPort;


// Enumerations identifying parameters.  A subset of the enumerations is also used in PtpPortParameterHost, and must use the same values
typedef enum
{
	setTwoStepOperation = 0,
	setPtpPortAddressingMode,
	setPtpPortUsePDelay,
	setPtpPortPDelayResponseEnable,

	setMulticastAnnounceLogPeriod = 10,
	setMulticastSyncLogPeriod,
	setMulticastDelayRequestLogPeriod,
	setAnnounceGrantRequestThreshold,
	setSyncGrantRequestThreshold,
	setDelayGrantRequestThreshold,
	setAnnounceGrantRepeatPeriod,
	setSyncGrantRepeatPeriod,
	setDelayGrantRepeatPeriod,


	setPortVersionUnused = 20,
	setBeSlaveEvenWhenMastersTimeIsNotUsed,
	setAnnounceReceiptTimeout,
	setAlwaysRespondToUnicastDelays,

	setNumberOfAlternateMasters = 30,

	setDomain = 35,
	setPtpClockId = 36,
	setPtpHoldoffTimer = 37,	// value in *seconds*
	setPrsFreqTraceValue = 38,

	setNetworkTrafficProfile = 39,
	setFreqTraceOverride = 40,

	minDirectionalPortParameter = 50,
	acceptMulticastTimingMessages = minDirectionalPortParameter,
	enableUnicastGrantRequests,

	setMasterPacketInterfaceSpeed = 60,
	setRenewalFlag,
	setRefusalFlag,

	setDoNotBecomeMasterIfTaiUnknown=70,
	setDoNotBecomeMasterIfUtcUnknown,
	setDoNotBecomeMasterIfSourceIsNotPrs,	//PRS == Primary Reference Source

	setHybridFreqInput=80,

	setEboundaryClockEnable = 100,
	setEboundaryClockTxRate,
	setEboundaryClockEncryption,
	setEboundaryClockUseGce,
	setEboundaryClockExternalGce,
	setEboundaryClockInternalGce,
	setEboundaryClockStageError,
	setEboundaryClockRxRate,
	setEboundaryClockNumberTlvReceived,

	ptpPortMSMin = 200,

	ptpPortSMMin = 400,

	ptpPortBothDirMin = 600,
	ptpPortBothDirMax = 799

} PtpPortParameter;

void PtpPortInitialise(PtpPort* port, PortId const* id,
						ClockId ptpClock,
						uint16 numberOfVisibleMasters,
						UnicastMasterController* unicastMasterController,
						ElapsedTime slowTickPeriod, ElapsedTime tickPeriod,
						struct AlarmMonitorStruct* alarmMonitor,
						Bool isMaster,
						CurrentMaster* currentMaster,
						Bool renewalFlag,
						ImpairmentController *impairCtrlr,
						uint8 arrayIndex);

Bool PtpPortConfigure(PtpPort* port,
				NetworkInterfaceId *networkInterfaceId,
				uint32 mHomeIndex,
				TransmissionProtocol transmissionProtocol,
				uint8						domain,
				PtpPortTransmissionAddressing transmissionAddressing
);

void PtpPortDeconfigure(PtpPort* port);

void PtpPortReset(PtpPort* port);

void PtpPortConfigurationUpdated(PtpPort* port);
#define PtpPortPhaseOffsetApplied(port) PathDelayControllerPhaseJump(&(port)->pathDelayController)

void PtpPortFastTick(PtpPort* port); // called each tick

void PtpPortSlowTick(PtpPort* port);
	// called each SLOW_TICK_PERIOD_SECS.

void PtpPortInputChanged(PtpPort* port);

Bool PtpPortAllocateCurrentMasterToPort(PtpPort* port,CurrentMaster* currentMaster);
Bool PtpPortRemoveAllCurrentMastersFromPort(PtpPort* port);
void PtpPortAssignClockLockingControllerToHybridController(PtpPort* port,
		struct ClockLockingControllerStruct* clControl);
void PtpPortEnable(PtpPort* port, Bool enable);
#define PtpPortUseAcceptableMasterController(port, amc) 	((port)->acceptableMasterController = (amc))
#define PtpPortUseAcceptableSlaveController(port, asc) 	((port)->acceptableSlaveController = (asc))
#define PtpPortUsingAcceptableMasterController(port)  	((port)->acceptableMasterController != NULL)
Bool PtpPortSetRequestedMessagePeriod(PtpPort* port, MessageType messageType,
					Bool multicast, Bool required, LogMessagePeriod logPeriod, uint32 grantDuration);
	// grantDuration is ignored when multicast is TRUE OR when grantDuration == 0
	// if require == FALSE - the rate is the requested rate

Bool PtpPortGetRequestedMessagePeriod(PtpPort* port, MessageType messageType,
					Bool multicast, Bool required, LogMessagePeriod *logPeriod, uint32 *grantDuration);

Bool PtpPortSetGrantRequestTheshold(PtpPort* port, MessageType messageType, uint16 grantThreshold);
Bool PtpPortSetGrantRepeatPeriod(PtpPort* port, MessageType messageType, uint16 grantRepeatPeriod);

void PtpPortDeleteAllVisibleMasters(PtpPort* port);

#define GetIdealLogMessagePeriod(port, messageType, multicast) \
	((port)->grantConfiguration.requestedMessagePeriod[messageType][multicast].idealLogPeriod)

#define GetAcceptableUnicastLogMessagePeriod(port, messageType) \
	((port)->grantConfiguration.requestedMessagePeriod[messageType][FALSE].acceptableLogPeriod)

#define GetIdealUnicastGrantDuration(port, messageType) \
	((port)->grantConfiguration.requestedMessagePeriod[messageType][FALSE].grantSeconds)

#define GetGrantRequestThreshold(port, messageType) \
	((port)->grantConfiguration.requestThreshold[messageType])

#define GetGrantRepeatPeriod(port, messageType) \
	((port)->grantConfiguration.repeatPeriod[messageType])


void PtpPortEnableDelayRequestTransmission(PtpPort* port, Bool enable);
void PtpPortAllowUnicastTransmission(PtpPort* port, Bool enable);
uint32 GetIdealGrantDuration(PtpPort const* port, MessageType messageType, Bool multicast);


void PtpPortMessageReceived(PtpPort* port,
						 TwoLevelAddress * sourceAddress,
						 uint8 const data[], uint16 dataLength,
						 IEEE1588Time const* receiveTime,
						 uint32 changeCount, uint8 isMulticast);

void PtpPortDelayMessageReceived(ExternalInterfaceType sourceInterface, PtpPort* port, uint8 const* data);

void PtpPortDelayRequestMessageTransmitted(PtpPort* port, VisibleMaster* master,
			IEEE1588Timestamp const* transmitTimestamp, IEEE1588SequenceNumber sequenceNumber);
void EventMessageTransmittedfromPtpPort(PtpPort* port, MessageType messageType, IEEE1588SequenceNumber sequenceNumber,
						Bool unicast, TwoLevelAddress * address, IEEE1588Timestamp const* transmitTimestamp);

void PortEventDetected(PtpPort* port, PortEvent event);
PTPPortState PortGetState(PtpPort const* port);

void SetPtpPortTransmissionType(PtpPort* port, PtpPortTransmissionAddressing txType);
#define GetPtpPortTransmissionType(port) ((port)->transmissionAddressing)
#define PtpPortIsConfigured(port) ((port)->networkSubInterface != NULL)
#define PtpPortIsEnabled(port) ((port)->enabled)
#define PtpPortForceTwoStepOperation(port,set) ((port)->forceTwoStepOperation = (set))
#define PtpPortTwoStepOperationIsForced(port) ((port)->forceTwoStepOperation)
#define PtpPortIsTwoStep(port) ((port)->cache.twoStep)
Bool EnablePtpPortToBecomeMaster(PtpPort* port, Bool enable);
Bool EnablePtpPortToBecomeSlave(PtpPort* port, Bool enable);
#define PtpPortCanBeMaster(port) ((port)->isMasterPort)
#define PtpPortCanBeSlave(port) (!(port)->isMasterPort)
#define PtpPortBeSlaveEvenWhenMastersTimeIsNotUsed(port) ((port)->beSlaveEvenWhenMastersTimeIsNotUsed)
Bool IsThisMasterBetterThanMe(PtpPort const* ptpPort, struct VisibleMasterStruct const* master); //must be visible via this port
#define SetMaxNumberOfAlternateMasters(port,a) ((port)->numberOfAlternateMasters = (a))
#define GetMaxNumberOfAlternateMasters(port) ((port)->numberOfAlternateMasters)
#define BestMasterVisibleOnPort(port) ((port)->bestMaster)
#define MaxOfMastersOfInterestOnPtpPort(port) ((port)->maxOfMastersOfInterest)

void SetPtpPortMasterInterfaceSpeed(PtpPort* port, float masterInterfaceSpeed); // masterIntefaceSpeed is in bit/s
void SetDomain(PtpPort* port, IEEE1588Domain value);
Bool SetPtpPortTimebase(PtpPort* port, ClockId clockId);

Bool PtpPortReactToSignallingMessage(PtpPort* port, uint8 const** data);
Bool PtpPortReactToPathDelayMessage(PtpPort* port, MessageType messageType, IEEE1588Time const* rxTime, uint8 const** data);
// message is not too short - this has already been checked
Bool PtpPortReactToManagementMessage(PtpPort* port, uint8 const** data, TwoLevelAddress const * address, PortId const *portId);


void PtpPortParseSuffix(PtpPort* port,
					PortId const* sourceId,
					TwoLevelAddress * sourceAddress,
					uint8 const** data,
					uint8 const* end);

#define PtpPortPathDelayInformationInvalid(port) PathDelayControllerDataInvalid(&(port)->pathDelayController)
//returns FALSE if path delay operation is enabled AND the data is not valid

#define PtpPortPathDelayInformationValid(port) PathDelayControllerDataValid(&(port)->pathDelayController)
//returns TRUE if path delay operation is enabled AND the data is valid

#define PtpPortPathDelayValue(port)  PathDelayControllerValue(&(port)->pathDelayController)

IEEE1588Time GetTimePtpPort(PtpPort const* port); // must not be called when port is not configured

IEEE1588SequenceNumber PtpPortGetNextSequenceNumber(PtpPort* port, MessageType messageType,
					PortId const* portId, TransmissionProtocolAddress const* address);

//private functions
void UpdatePortState(PtpPort* port);
Bool ShouldIBeGrandmaster(PtpPort const* port);
void PortSetState(PtpPort* port, PTPPortState newState);

#define PortGetNextSequenceNumber(port, messageType) GetNextSequenceNumber(&(port)->messageSequenceNumberGenerator, (messageType))
#define PortGetCurrentSequenceNumber(port, messageType) GetCurrentSequenceNumber(&(port)->messageSequenceNumberGenerator, (messageType))

#define PtpPortServiceLayerOperational(port)\
 (PtpPortIsConfigured(port) && NPSIIsOperational(port->networkSubInterface))

void PtpPortUpdateCache(PtpPort* port, IEEE1588Time const* currentTime); //currentTime may be NULL
// must be called at least twice per sec, with currentTime not null


//Send message functions
UDPChecksumType GetUDPChecksumTypeForPtpMsg(NetworkProtocolInterface* networkInterface, MessageType msgType);

void PTPPortSendAnnounce(PtpPort* port,
			TwoLevelAddress *destinationAddress,	// destinationAddress->physical may be invalid, indicating that an ARP request needs to be done
			IEEE1588SequenceNumber sequenceNumber, LogMessagePeriod logMessagePeriod);

_Inline void PtpPortSendEventMessage(PtpPort* port, MessageType messageType,
			TwoLevelAddress *destinationAddress,//no longer const as physical address may get updated by arp cache
			struct VisibleMasterStruct* destinationVisibleMaster,
			IEEE1588SequenceNumber sequenceNumber, LogMessagePeriod logMessagePeriod,
			IEEE1588Time const* time, sint32 correction, PortId* const destinationPortId);

void PTPPortSendSync(PtpPort* port,
			TwoLevelAddress *destinationAddress, // if NULL, the message must be sent to the multicast address, also no longer const as physical address may get updated by arp cache
			IEEE1588SequenceNumber sequenceNumber, LogMessagePeriod logMessagePeriod);

void PTPPortSendFollowUp(PtpPort* port,
			TwoLevelAddress * destinationAddress,
			IEEE1588SequenceNumber sequenceNumber,
			IEEE1588Time const* transmitTime);

void PTPPortSendDelayResponse(PtpPort* port,
			TwoLevelAddress * destinationAddress,
			PortId const* destination,
			const uint8 receivedDelayRequest[],
			IEEE1588Time const* receiveTime,
			sint64 newCorrectionField);

void PtpPortSendUserData(PtpPort* port, TransmissionProtocolAddress const * sourceAddress,
		uint32 const* data, uint16 lengthInWords);

void PtpPortSendUserDataAck(PtpPort* port, TwoLevelAddress * sourceAddress, PortId const *sourceId);

void PtpPortWriteSignallingMessage(PtpPort* port, uint8 ** data, IEEE1588SequenceNumber sequenceNumber,
			PortId const* targetPort, TwoLevelAddress const* address);

void PtpPortWriteManagementMessage(PtpPort* port, uint8 ** data,
		IEEE1588SequenceNumber sequenceNumber,
		PortId const* targetPort, TwoLevelAddress const* address, LogMessagePeriod period,
		uint8 const startingBoundaryHops, uint8 const hops, ManagementActionField const action);

void PtpPortSendSmpteData(PtpPort* port, TwoLevelAddress * targetAddress, uint8 hops, SmpteData * const data);


Bool IsMyClockReferenceOkayToBeMasterPtpPort(PtpPort const* port);
Bool IsMyClockReferenceOkayToBeSlavePtpPort(PtpPort const* port);

// Unicast negotiation functions
void PtpPortRequestUnicastGrant(PtpPort* port, MessageType messageType,
						TwoLevelAddress * grantorAddress,
						PortId const* grantorId,
						IEEE1588SequenceNumber sequenceNumber,
						LogMessagePeriod logPeriod, uint32 requestedDurationSecs);

Bool SemtechTLVParser(
		uint8 const **tlvInfoStart,
		uint32 tlvInfoLen,
		uint32 organizationSubType,
		IEEE1588Time *const time,
		sint32 *const subNanos);
void PtpPortRequestCancelUnicastGrant(PtpPort* port, MessageType messageType,
						TwoLevelAddress * grantorAddress,
						PortId const* grantorId,
						IEEE1588SequenceNumber sequenceNumber);

void PtpPortParseTLV(PtpPort* port, PortId const* sourceId,
						TwoLevelAddress * sourceAddress,
						struct VisibleMasterStruct* master, // may be NULL
						uint8 const** data, uint8 const* end);
#define GetSelectorPtpPort(port) GetNodeTimeTRSelCP(port->clockPath)

// enhanced Boundary clock encryption function
void BoundaryClockTlvEncrypt(uint32 *data, BcEncryption algorithm);

//Private functions
void PtpPortSendGeneralMessage(PtpPort* port,
		TwoLevelAddress * destinationAddress,	// if NULL send to multicast address
		uint8 messageBuffer[], uint16 messageLength);

void ConfigurePtpMasterOnPhysicalPort(PtpPort* port);
void ConfigurePtpSlaveOnPhysicalPort(PtpPort* port);
void DeconfigurePtpMasterOnPhysicalPort(PtpPort* port);
void DeconfigurePtpSlaveOnPhysicalPort(PtpPort* port);

void UpdateMessageTemplates(PtpPort* port, IEEE1588Time const* currentTime);
void UpdateFastDelayResponseOperation(PtpPort const* port);

void UpdatePCBDataFromTemplate(PCBAllocatorElement* element, MessageTemplate* msgTemplate);
uint8 GetLocalGrandmasterClockClass(PtpPort const* port);
Bool PtpPortUseLocalIDForExternalGMID(PtpPort const* port);
char const* PortStateText(PTPPortState state);
void PrintPtpPort(PtpPort const* port, char** ptrptr, long *bufferSize, Bool title);
void PrintPtpPortSummary952x(PtpPort const* port, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintPtpPortMasterSummary952x(PtpPort const* port, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintPtpPortDetail952x(PtpPort const* port, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintPtpPortMode2_3Debug952x(PtpPort const* port, uint8 index, char** ptrptr, long *bufferSize, Bool title);
void PrintPtpPortDebug952x(PtpPort const* port, uint8 index, char** ptrptr, long *bufferSize, Bool title);





#define PtpPortGetNumberOfMissingAnnounceMessagesToMasterLost(port)	port->numberOfMissingAnnounceMessagesToMasterLost
Bool PtpPortIsBetterMasterAvailable(PtpPort const* port, BetterMasterAvailable *available);
Bool PtpPortSetMasterLockOut(PtpPort const* port, uint16 visMasterIndex, Bool enable);
Bool PtpPortGetMasterLockOut(PtpPort const* port, uint16 visMasterIndex, Bool *enable);
Bool PtpPortGetMasterWaitToRestoreTicks(PtpPort const* port, uint16 visMasterIndex, uint32 *ticks);

#ifdef __cplusplus
}
#endif


#endif

