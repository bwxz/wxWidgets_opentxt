/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: ControlMessageValidation.h $
 * $Revision: 17 $
 * $Date: 5/06/09 12:13 $
 */

/**
 * \file ControlMessageValidation.h
 * Contains the function and type declarations for processing of control messages. 
 */

#ifndef CONTROL_MESSAGE_VALIDATION_H
#define CONTROL_MESSAGE_VALIDATION_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PORT_DOES_NOT_EXIST (-1)
	
Bool IsEthernetPortValid(uint8 EthernetPort);
Bool IsIpPacketInterfaceValid(uint8 interface);
Bool IsEthernetPacketInterfaceValid(uint8 interface);
Bool IsClockInputIdValid(uint8 clockInput);
Bool IsClockOutputValid(uint8 clockOutput);
Bool IsOnePPSOutputValid(uint8 onePPSOutput);
Bool IsTODUartOutputPortValid(uint8 uartOutput);
Bool IsPTPInputClockValid(uint8 onePPSInput);
Bool IsTODUartInputPortValid(uint8 uartInput);
Bool IsTimeCodeValid(TODTimeCode timeCode);
Bool IsBaudRateValid(UartBaudRate baudRate);
Bool IsPhaseAlignedOutputValid(uint8 phaseAlignedOutput);
Bool IsPhysicalPortIdValid(uint8 physicalPort);  //internal physical port number (starting from zero)
Bool IsClockPathIdValid(uint8 clockPath);
Bool IsPtpPortValid(uint8 ptpPort);
Bool IsNetworkProtocolInterfaceIdValid(uint8 port, TransmissionProtocol protocol);
Bool IsPLLIdValid(PLLid pll);
#define IsTimeReferenceSelectorIdValid(id) IsPLLIdValid(id)
Bool IsPtpPortIpValid(void);
Bool IsPtpPortEthernetValid(void);
Bool IsPtpPortStateValid(PTPPortState state);
Bool IsLocalOscillatorTypeValid(LocalOscillatorType type);
Bool IsLocalOscillatorStratumLevelValid(ClockStratum stratum);
Bool IsClockAccuracyValid(ClockAccuracy accuracy);
Bool IsTimeSourceEnumerationValid(TimeSource timeSource);
Bool IsForceLockedUnlockedStateEnumerationValid(ForceLockedUnlockedState forceLockedUnlockedState);
Bool IsLinkSpeedDuplexModeValid(LinkSpeedDuplexMode linkSpeedDuplexMode);
Bool IsToPSyncSystemStateValueValid(ToPSyncSystemState systemState);
Bool IsTimeSourceValid(TimeTransport timeSource, uint8 id);
#define IsHybridTimeControllerIdValid(id) IsClockPathIdValid(id)
#define IsTimeSmootherIdValid(id) IsClockPathIdValid(id)
Bool IsVisibleMasterIdValid(uint8 id);
Bool IsInputFreqValid(uint32 freqHertz);

sint8 ConvertExternalPortNumber(uint8 external);
sint8 ConvertInternalPortNumber(uint8 internal);
sint8 ConvertExternalPtpPortNumber(uint8 external);
sint8 ConvertInternalPtpPortNumber(uint8 internal);
sint8 ConvertInternalTimeSourceId(TimeTransport timeSource, uint8 id);
sint8 ConvertExternalTimeSourceId(TimeTransport timeSource, uint8 id);
sint8 ConvertInternalMasterPtpPortIndexToExternal(uint8 internal);
sint8 ConvertExternalMasterPtpPortIndexToInternal(uint8 external);

#ifdef __cplusplus
}
#endif

#endif

