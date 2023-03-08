#ifndef APPLICATION_INFRASTRUCTURE_INTERFACE_H
#define APPLICATION_INFRASTRUCTURE_INTERFACE_H

#include "SystemConfiguration.h"
#include "IEEE1588Messages.h"
#include "TransmissionProtocol.h"
#include "Socket.h"

#include "MqxInterface.h"

#ifdef __cplusplus
#ifdef _SIMULATOR
#include "System.hpp"
#endif
extern "C" {
#endif


struct PtpPortStructure;

typedef struct
{
	uint8  portNumber;
	uint32 virtualPortNumber;
} NetworkInterfaceId;

void TimeServer_Tick(void);

// called by application
void GetMACAddress(uint8 macNumber, EthernetAddress addressOutput);

void SendPTPUDPMessageUsingSocket(SocketHandle txSocket,
	const NetworkInterfaceId *networkInterfaceId,
	TransmissionProtocolAddress const* destinationAddress,
	uint16 destinationUdpPortNumber,
	uint8 const dataArray[], uint16 dataLength);


void ApplyTimeOffsetToHardware(IEEE1588Time const* change, uint8 timestamper);
	//+ve is forward
	// does not apply an epoch offset

void SetNodeTimerClockSource(ClockId timestamperId,uint8 ddsId);
uint8 GetNodeTimerClockSource(ClockId timestamperId);

IEEE1588Time GetHardwareTimeDifference(uint8 tested, uint8 reference);
	// +ve means tested is behind reference

#define FILTER_FLAG_HW_UDP_CHECKSUM_ENABLED	(1 << 0)
#define FILTER_FLAG_DOT1Q_ENABLED			(1 << 1)

void ConfigureHwTimestamper(uint8 connector, Bool transmit, uint8 microFilterId,
		uint32 const* searchTerms,uint32 numberOfSearchTerms);
uint32 SetFilterSearchTerm(uint8 offset, uint8 pattern, uint8 mask, Bool lastTerm, uint8 timeStampSource);
uint32 SetFilterInsertPoint(uint8 offset);
uint32 SetHardwareFilterToInsertHwUDPChksum(uint offset);

void ResetHwTimestamper(uint8 connector,Bool transmit);

void EnableMicroFilterById(uint8 connector, Bool transmit, uint8 microFilterid, Bool enable);
void EnableNetworkTimestamperTransmitIndication(uint8 timestamper, uint8 physicalPort, Bool enable);


IEEE1588Timestamp GetHardwareTime(uint8 timestamper);
void SetTimeStamper1PPSPulseWidth(uint8 timestamper,uint32 pulseWidth);
uint32 GetTimeStamper1PPSPulseWidth(uint8 timestamper);
void SetTimeStamperOutputDivisor(uint8 timestamper,uint32 divisor);
uint32 GetTimeStamperOutputDivisor(uint8 timestamper);

void InitialiseGlobalData(void);

void SetLockedOutput(Bool set);

#ifdef _ARC
	#define DisableInterrupts() _int_disable()
	#define EnableInterrupts() _int_enable()
	#define TakeMutex() 	_mutex_lock(&dataMutex)
	#define ReleaseMutex() 	_mutex_unlock(&dataMutex)  //GlobalData.h must also be included

	#ifndef PadForV1HardwareCompatibilityUDP
		#define PadForV1HardwareCompatibilityUDP() FALSE
	#endif
#else
	#define DisableInterrupts()
	#define EnableInterrupts()
	#define TakeMutex()
	#define ReleaseMutex()

	Bool PadForV1HardwareCompatibilityUDP(void);
#endif


void InitialiseHardwareForClockTimestamper(uint8 clockTimeStamper);
void SetNodeFrequencyOutputClockSource(uint8 output, uint8 clockSource);
void SetNetworkTimeStamperClockSource(uint8 timeStamper, uint8 clockSource);
uint8 GetNetworkTimeStamperClockSource(uint8 timeStamper);
void PhaseAlignTimestamperXToTimestamperY(uint8 TimestamperX, uint8 TimestamperY);
IEEE1588Timestamp ReadTimeOfLastPacketTransmission(uint32 physicalInterface,uint32 timeStamper);
void ClockTimestamperSelectDividerInput(uint8 timeStamper, uint8 input);
void Set1PPSOutputTimeSource(uint8 output, Bool enable, uint8 source);
	// if enable == FALSE source is ignored
	// source identifies a networkTimestamper i.e. zero identifies net t/s zero

void SetAll1PPSOutputPulseWidths(uint32 pulseWidthNs);
void DisableAllClockOutputs(void);

Bool NodeCanBeMaster(void);
Bool NodeAcceptsAClockInput(void);


#define RX_TIMESTAMP_BYTES 4

/* Function to send control message to an interface */
Bool SendControlMessage(const uint8 *messageData, uint32 messageLength,
                               ExternalInterface destinationInterface,
                               const EnhancedTransmissionProtocolAddress* destinationInterfaceAddress);


/* Callback for receiving message from an interface */
void ControlMessageReceived(const uint8 *messageData, uint32 messageLength,
							ExternalInterface messageSourceInterface,
							const EnhancedTransmissionProtocolAddress* messageSourceAddress);


uint8 const* GetPortIPAddress(const NetworkInterfaceId *networkInterfaceId, uint32 mHomeIndex, Bool ip6);  // returns NULL if none
uint8 GetPtpIpToS(Bool event);

ToPSyncConfigResult SetMuxInput(MuxID mux, uint8 pin, uint8 inputOption);
ToPSyncConfigResult GetMuxInput(MuxID mux, uint8 pin, uint8 *inputOption);

void EnableClockTimestamperInterrupt(uint8 id, Bool enable);
void EnableClockInterruptAfterTicks(uint8 id, uint32 ticksUntilEnable);	 //ticks == 0 does not enable

void AlertEventMessageTransmitQueue(void);

ToPSyncConfigResult DoSetMDIOData(uint8 portNumber, uint8 phyAddr, uint8 reg, uint16 data);
ToPSyncConfigResult DoGetMDIOData(uint8 portNumber, uint8 phyAddr, uint8 reg, uint16 *output);

Bool FindPhysicalAddressFromARPCache(const NetworkInterfaceId *networkInterfaceId, TransmissionProtocolAddress const *tpa, uint8 * const physAddrBuf, int *physAddrBufLen);

#ifdef _ARC
	typedef _enet_handle EthernetHandle;
#else
	typedef uint32* EthernetHandle;
	#define ETHERNET_HANDLE_MIN 0x100 //in simulation GetEthernetHandle(connector) returns (ETHERNET_HANDLE_MIN + connector)
#endif


EthernetHandle GetEthernetHandle(const NetworkInterfaceId *networkInterfaceId);

uint16 GetDeviceInputClockMonitorDetectedMask(void);
void ResetDeviceInputClockMonitorDetectedMask(void);
void EnableDeviceInputClockMonitorInterrupts(void);
void EnableDeviceInputClockMonitorActivityMonitors(void);


void InitialiseSETSMux(void);

/* For 9550/20/10 evaluation board */
void InitialiseSETSMuxConnections(ToPSyncPartNumber partNumber);

void ClockTimestamperSelectDividerInput(uint8 timestamper, uint8 input);
void ClockTimestamperSetDivisionRatio(uint8 timestamper, DividerOutput output, uint32 division); // division == 0 disables
uint16 ClockTimestamperGetDivisionRatio(uint8 timestamper, DividerOutput output);
#define DisableClockTimestamperDivider(timestamper, output) ClockTimestamperSetDivisionRatio((timestamper), (output), 0);

Bool IsHwUDPChecksumSupported(void);

ToPSyncConfigResult DoI2CRead(uint8 addr, Bool isReg, uint16 reg, uint8 dataLen, uint8 *data);
ToPSyncConfigResult DoI2CWrite(uint8 addr, Bool isReg, uint16 reg, uint8 dataLen, uint8 *data);

Bool I2CGetLockedAddressesEnabled(void);
void I2CSetLockedAddressesEnabled(Bool enableLockedAddresses);
Bool I2CAddressIsLocked(uint8 address);

#ifdef __cplusplus
}
#endif

#endif

