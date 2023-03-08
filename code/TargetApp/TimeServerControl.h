#ifndef TIME_SERVER_CONTROL_H
#define TIME_SERVER_CONTROL_H

#include "PhysicalPort.h"
#include "NetworkProtocolInterface.h"
#include "ClockTimestampControl.h"
#include "ClockPath.h"
#include "ImpairmentController.h"
#include "AlarmMonitor.h"
#include "PPSController.h"
#include "PacketControlBlockAllocator.h"
#include "DelayRequestReceiver.h"
#include "MessageReceiveQueue.h"
#include "EventMessageTransmitQueue.h"
#include "NetworkMasterTable.h"
#include "PtpMessageReceiver.h"
#include "ToPSyncControlDriverMessages.h"
#include "DelayMonitor.h"
#include "BinaryLockMonitor.h"
#include "LcdDisplay.h"

#ifdef  __cplusplus
extern "C" {
#endif


typedef struct
{
	//Infrastructure - must be initialised before system starts
	PCBAllocator						announcePCBAllocator;
	PCBAllocator						syncPCBAllocator;
	PCBAllocator						delayResponsePCBAllocator;
	PCBAllocator						delayResponseWithBcTlvPCBAllocator;
	PCBAllocator						generalPtpPCBAllocator;
	PCBAllocator						eventPtpPCBAllocator;

	DelayRequestReceiver				delayRequestReceiver[NUMBER_OF_PTP_MASTER_PORTS];
	PtpMessageReceiver					ptpMessageReceiver;
	MessageReceiveQueue					stackBypassReceiveQueue;
	EventMessageTransmitQueue			eventMessageTransmitQueue;


	//Configuration
	ReferenceClock						localReferenceClock;	// including nodeId

	//Components
	uint32								numberOfVirtualInterfacesConfigured;
	EthernetInterfaceConfiguration		ethernetConfiguration[NUMBER_OF_ACTIVE_PHYSICAL_PORTS];
	NetworkInterfaceConfiguration 		networkInterfaces[NUMBER_OF_ACTIVE_PHYSICAL_PORTS][NUMBER_OF_VIRTUAL_PORTS];
	PhysicalPort						physicalPortArray[NUMBER_OF_ACTIVE_PHYSICAL_PORTS];
	NetworkProtocolInterface 			networkProtocolInterfaceArray[NUMBER_OF_PTP_PORTS];
	ClockLockingController				clockLockerArray[NUMBER_OF_CLOCK_PLLS];
	CurrentMaster						currentMasterArray[NUMBER_OF_CURRENT_MASTERS];

	AcceptablePartnerController 		acceptableMasterController[NUMBER_OF_PTP_SLAVE_PORTS];
	AcceptablePartnerController			acceptableSlaveController[NUMBER_OF_PTP_MASTER_PORTS];

	PtpPort								ptpPortArray[NUMBER_OF_PTP_PORTS];
	ClockPath							clockPath[NUMBER_OF_CLOCK_PATHS];
	ImpairmentController				impairmentControllerArray[NUMBER_OF_PTP_MASTER_PORTS]; /* One impairment controller per master PTP port. */
	UnicastMasterController 			unicastMasterController;
	AlarmMonitor						alarmMonitor;
	BinaryLockMonitorTop				binaryLockMonitorTop;
	DelayMonitor						delayMonitor[NUMBER_OF_CURRENT_MASTERS];
	PPSController						ppsController[NUMBER_OF_1PPS_OUTPUTS_USED];
	EpochController						epochController[numberOfClockIds]; // one per hardware timestamper
	NetworkMasterTable					networkMasterTable;
	Lcd									lcdDisplay;

	ClockId								frequencyOutputSource[NUMBER_OF_FREQUENCY_OUTPUTS];
	HardwareFrequencyController			hardwareFrequencyController[numberOfClockIds];

	// general
	uint32								tickCount;
	uint32								secsSinceReset;

	DRMStatistics                       drmStatistics;

	struct
	{
	DRMStatistics                       drmStatistics;
		uint32	numberOfPtpSlavePorts;	// Note: this is NOT the max number of ports set at compile time
		uint32	numberOfPtpMasterPorts;	// it is the number set via the part number/other config methods
		uint32	numberOfEnabledClockPlls;
	} hardwareLimit;

	struct
	{
		uint8 address;
		uint32 reg;
	} i2c_mmAPIShadows;
} ControlData;

extern ControlData* controlDataPtr;

void InitialiseTimeServerControlInfrastructure(void);
void InitialiseTimeServerControl(void);

void ResetTimeServerControl(void);
void ReactToReceivedMessage(void); //only called when stackBypassReceiveQueue is not empty

PtpPort* FindMasterPtpPort(NetworkInterfaceId *networkInterfaceId, TransmissionProtocol	transmissionProtocol, IEEE1588Domain domain);

PhysicalPort *FindPhysicalPort(uint8 physicalPortNumber);

TimeReferenceSource* FindInputSource(uint8 sourceId);
TimeReferenceSource const* GetTimeReferenceSourceByClockId(ClockId clockId);
ReferenceClock const* GetReferenceClockByClockId(ClockId clockId);
PtpPort* FindPTPPortByClockId(ClockId clockId);
void UpdateHardwareFrequencyOffset(ClockId id,Frequency newFrequency);
void SyncHardwareFrequencyOffset(ClockId destId,ClockId sourceId);
Frequency GetHardwareFrequencyOffset(ClockId id);

#define GetSecondaryPLLLag1588() GetHardwareTimeDifference(secondaryPLL, mainPLL)
Signal GetSecondaryPLLLag(void);

ReferenceClock const* GetLocalReferenceClock(void);
void SetLocalReferenceClock(ReferenceClock const* refClock);

Bool SetInputClockFrequency(uint8 ptpInputClock, uint32 frequencyInHertz);
uint32 GetInputClockFrequency(uint8 ptpInputClock);

/* notification from source to node time */
void NotifyNodeTimeInputChange(ClockId clockId);

/* functions to retrieve time from hardware clocks */
IEEE1588Time GetTime(ClockId id);
uint16       GetEpoch(ClockId id, IEEE1588Timestamp const* now);
void 		 SetEpoch(ClockId id, IEEE1588Time const* time);
void ApplyTimeOffset(ClockId id, IEEE1588Time const* change);
IEEE1588Time const* GetApproxTime(ClockId id);
void SetFrequencyOutputSource(uint8 output, ClockId source);
ClockId GetFrequencyOutputSource(uint8 output);

uint32 GetNumberOfPtpSlavePorts(void);
uint32 GetNumberOfPtpMasterPorts(void);

typedef enum
{
	enableDelayPrinting,
	getDelayPrintingState,

	enablePtpErrorMonitor = 10,

	setNodeTimeInputMux=20,

	setOscillatorFrequencyOffset=30,
} ToPSyncParameter;

#define MODE4_NODE_TIME_TOO_NEAR_TOS_THRESHOLD_NSECS 950000000 /* 50ms from top of second */
#define MODE4_CF_LOWER_THRESHOLD_NSECS (-500000000) /* -500ms from top of second */
#define MODE4_CR_UPPER_THRESHOLD_NSECS (1000000000) /* 900ms from top of second */


#ifdef USE_ACS1790
void SlowTickCalcSecsSinceEpochForNAB();
#endif


#ifdef  __cplusplus
}  //extern "C"
#endif

#endif

