/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: TopSyncControlDriverMessageUtilities.hpp $
 * $Revision: 46 $
 * $Date: 17/06/09 21:28 $
 */

/**
 * \file ToPSyncControlDriverMessageUtilities.hpp
 * This is a utility class for constructing the necessary control/management
 * messages. The caller of the function takes responsibility for deallocating the
 * memory.
 */

#ifndef TOPSYNC_CONTROL_DRIVER_MESSAGE_UTILITIES_HPP
#define TOPSYNC_CONTROL_DRIVER_MESSAGE_UTILITIES_HPP

#include "General.h"
#include "ToPSyncControlDriverMessages.h"
#include "ToPSyncControlDriverCommonMessages.h"
#include <string>

namespace Semtech
{
    class ControlMessageUtilities
    {
        public:
			static std::string* CreateGetImpairmentsResponseMsg(uint8 direction, uint32 offset, uint16 numberOfImpairments,
                                                                      const uint8 impairmentsBuffer[]);
			static std::string* CreateAddAcceptablePartnerMsg(const uint8 ptpPortNumber,
																	const TransmissionProtocolAddress address,
																	const PortId portId,
																	const uint8 priority1,
																	const uint8 priority2,
																	const Bool requestUnicastAnnounceFromMaster,
                                                                                                                                        const Bool slave);
			static std::string* CreateAddEthernetPacketInterfaceMsg(const uint8 portNumber);
			static std::string* CreateAddIpPacketInterfaceMsg(const uint8 portNumber);
			static std::string* CreateConfigurePtpPortMsg(const PtpPortConfiguration ptpPort);
			static std::string* CreateDeconfigurePtpPortMsg(const uint8 ptpPortNumber);
			static std::string* CreateDeleteAcceptableParterMsg(const uint8 ptpPortNumber, const TransmissionProtocolAddress address, const PortId portId, const Bool  slave);
			static std::string* CreateDeleteEthernetPacketInterfaceMsg(const uint8 portNumber);
			static std::string* CreateDeleteIpPacketInterfaceMsg(const uint8 portNumber);
	 		static std::string* CreateGetOnePPSOutputClockEnabledMsg(const uint8 output);
			static std::string* CreateGetOnePPSOutputClockPulseWidthMsg(const uint8 output);
			static std::string* CreateGetAcceptablePartnerTableEntryMsg(const uint8 ptpPortNumber, const uint8 entryNumber, const Bool slave);
			static std::string* CreateGetConfiguredPhaseLagMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetCurrentMasterMsg(void);
			static std::string* CreateGetDefaultEthernetMacAddressMsg(const uint8 portNumber);
			static std::string* CreateGetDelayToUseMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetEthernetInterfaceStatisticsMsg(const uint8 portNumber);
			static std::string* CreateGetEthernetLinkSpeedAndDuplexModeMsg(const uint8 portNumber);
			static std::string* CreateGetEthernetLinkStatusMsg(const uint8 portNumber);
			static std::string* CreateGetEthernetMacAddressMsg(const uint8 portNumber);
			static std::string* CreateGetEthernetPacketInterfaceStatisticsMsg(const uint8 portNumber);
			static std::string* CreateGetEthernetPacketInterfaceStatusMsg(const uint8 portNumber);
			static std::string* CreateGetExternalInterfacesMsg(void);
			static std::string* CreateGetFilterBandwidthsMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetForceHoldoverMsg(const Bool time);
			static std::string* CreateGetForceLockedUnlockedStateMsg(void);
			static std::string* CreateGetFrequencyControllerParametersMsg(void);
			static std::string* CreateGetHardwareVersionMsg(void);
			static std::string* CreateGetHoldoverAveragingPeriodMsg(void);
			static std::string* CreateGetImpairmentConfigurationMsg(uint16 impairmentController);
			static std::string* CreateGetInitialFrequencyMeasurementParametersMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetInitialSystemConfigurationMsg(void);
			static std::string* CreateGetIpPacketInterfaceConfigurationMsg(const uint8 portNumber);
			static std::string* CreateGetIpPacketInterfaceStatisticsMsg(const uint8 portNumber);
			static std::string* CreateGetIpPacketInterfaceStatusMsg(const uint8 portNumber);
			static std::string* CreateGetLocalOscillatorPhaseNoisePairsMsg(void);
			static std::string* CreateGetLocalOscillatorStratumLevelMsg(void);
			static std::string* CreateGetLocalOscillatorTypeMsg(void);
			static std::string* CreateGetLockedStateMsg(void);
			static std::string* CreateGetLockedStateThresholdsMsg(void);
			static std::string* CreateGetMacAddressFilteringEnabledMsg(const uint8 portNumber);
			static std::string* CreateGetMaxPhaseErrorBeforePhaseRealignmentMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetMaximumFrequencyOffsetMsg(void);
			static std::string* CreateGetMDIOLinkAvailabilityMsg(const uint8 portNumber);
			static std::string* CreateGetMessageGrantStatusMsg(const uint8 visibleMasterId);
			static std::string* CreateGetNoiseAnalyserBandwidthsMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetNoiseAnalyserNumberOfFiltersMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetOutputClockFrequencyEnabledMsg(const uint8 output);
			static std::string* CreateGetOutputClockFrequencyMsg(const uint8 output);
			static std::string* CreateGetOutputClockFrequencySmootherConfigurationMsg(void);
			static std::string* CreateGetOutputClockFrequencySmootherEnableMsg(void);
			static std::string* CreateGetPermittedMacAddressesMsg(const uint8 portNumber);
			static std::string* CreateGetPhaseAlignedOutputClockFrequencyMsg(const uint8 output);
			static std::string* CreateGetTimeCorrectionConfigurationMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetTimeCorrectionDampingFactorMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetProportionalAndIntegralGainsMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetPtpPortConfigurationMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetPtpPortStateMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetRequestedAnnounceMessagePeriodMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetRequestedDelayRequestMessagePeriodMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetRequestedSyncMessagePeriodMsg(const uint8 ptpPortNumber);
			static std::string* CreateGetSecondsSinceLastResetMsg(void);
			static std::string* CreateGetSecurityKeyMsg(void);
			static std::string* CreateGetSelectedTimeReferenceSourceMsg(void);
			static std::string* CreateGetSoftwareVersionMsg(void);
			static std::string* CreateGetSPIBusStatisticsMsg(void);
			static std::string* CreateGetSuppressPhaseJumpMsg(void);
			static std::string* CreateGetTimeReferenceSelectorStatisticsMsg(void);
			static std::string* CreateGetTimeReferenceSourceMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateGetTODOutputConfigurationMsg(const uint8 onePPSOutput, const uint8 uartOutput);
			static std::string* CreateGetToPSyncLocationMsg(void);
			static std::string* CreateGetToPSyncPartNumberMsg(void);
			static std::string* CreateGetToPSyncPtpSystemParametersMsg(void);
			static std::string* CreateGetToPSyncSystemExceptionsMsg(void);
			static std::string* CreateGetToPSyncSystemStateMsg(void);
			static std::string* CreateGetToPSyncUploadConfigurationMsg(void);
			static std::string* CreateGetVisibleMasterDelayStatisticsMsg(const uint8 visibleMasterId);
			static std::string* CreateGetVisibleMasterMsg(const uint8 visibleMasterId);

			static std::string* CreateGetVisibleMasterStatisticsMsg(const uint8 visibleMasterId);
			static std::string* CreateGetVisibleMastersMsg(void);
			static std::string* CreateResetHoldoverDataMsg(void);
			static std::string* CreateResetNetworkInterfaceStatisticsMsg(const uint8 portNumber, const ResetStatisticsMask mask);
			static std::string* CreateResetSPIBusStatisticsMsg(void);
			static std::string* CreateResetVisibleMasterStatisticsMsg(const uint8 visibleMasterId);
			static std::string* CreateRestartAutonegotiationMsg(const uint8 portNumber);
			static std::string* CreateSetOnePPSOutputClockEnabledMsg(const uint8 output, const Bool enabled);
			static std::string* CreateSetOnePPSOutputClockPulseWidthMsg(const uint8 output, const uint32 pulseWidth);
			static std::string* CreateSetConfiguredPhaseLagMsg(const TimeTransport sourceType, const uint8 id, const float configuredPhaseLag);
			static std::string* CreateSetDelayToUseMsg(const uint8 ptpPortNumber, const Bool masterToSlaveDelayUsed, const Bool slaveToMasterDelayUsed);
			static std::string* CreateSetEthernetInterfaceEnabledMsg(const uint8 portNumber, const Bool enabled);
			static std::string* CreateSetEthernetLinkSpeedAndDuplexModeMsg(const uint8 portNumber, const LinkSpeedDuplexMode linkSpeedDuplexMode);
			static std::string* CreateSetEthernetMacAddressMsg(const uint8 portNumber, const EthernetAddress macAddress);
			static std::string* CreateSetEthernetPacketInterfaceEnabledMsg(const uint8 portNumber, const Bool enabled);
			static std::string* CreateSetFilterBandwidthsMsg(const TimeTransport sourceType, const uint8 id,
															 const Frequency lockedMasterToSlaveFilterBandwidth,
															 const Frequency lockedSlaveToMasterFilterBandwidth,
															 const Frequency unlockedMasterToSlaveFilterBandwidth,
															 const Frequency unlockedSlaveToMasterFilterBandwidth);
			static std::string* CreateSetForceHoldoverMsg(const Bool time, const Bool forceHoldover);
			static std::string* CreateSetForceLockedUnlockedStateMsg(const ForceLockedUnlockedState forceLockedUnlockedState);
			static std::string* CreateSetFrequencyControllerParametersMsg(const FrequencyControllerParameters frequencyControllerParameters);
			static std::string* CreateSetHoldoverAveragingPeriodMsg(const uint32 holdoverAveragingPeriod);
			static std::string* CreateSetImpairmentConfigurationMsg(const ImpairmentConfiguration impairmentConfiguration);
			static std::string* CreateSetInitialFrequencyMeasurementParametersMsg(const TimeTransport sourceType, const uint8 id,
																				  const uint16 initialFrequencyMeasurementDuration,
																				  const uint16 minimumFrequencyMeasurementSamples);
			static std::string* CreateSetInitialSystemConfigurationMsg(const ToPSyncInitialSystemConfiguration systemConfiguration);
			static std::string* CreateSetIpPacketInterfaceEnabledMsg(const uint8 portNumber, const Bool enabled);
			static std::string* CreateSetLocalOscillatorPhaseNoisePairsMsg(const uint16 noOfValues, const PhaseNoisePairs phaseNoisePairs);
			static std::string* CreateSetLocalOscillatorStratumLevelMsg(const ClockStratum stratumLevel);
			static std::string* CreateSetLocalOscillatorTypeMsg(const LocalOscillatorType localOscillatorType);
			static std::string* CreateSetLockedStateThresholdsMsg(const LockedStateThresholds lockedStateThresholds);
			static std::string* CreateSetMacAddressFilteringEnabledMsg(const uint8 portNumber, const Bool enabled);
			static std::string* CreateSetMaxPhaseErrorBeforePhaseRealignmentMsg(const TimeTransport sourceType, const uint8 id, const ElapsedTime maximumPhaseError);
			static std::string* CreateSetMaximumFrequencyOffsetMsg(const float maximumFrequencyOffset);
			static std::string* CreateSetNoiseAnalyserBandwidthsMsg(const TimeTransport sourceType, const uint8 id,
																	const Frequency noiseAnalyserOpenBandwidth,
																	const Frequency noiseAnalyserClosedBandwidth);
			static std::string* CreateSetNoiseAnalyserNumberOfFiltersMsg(const TimeTransport sourceType, const uint8 id, const uint8 numberOfFilters);
			static std::string* CreateSetOutputClockFrequencyEnabledMsg(const uint8 output, const Bool enable);
			static std::string* CreateSetOutputClockFrequencyMsg(const uint8 output, const uint32 frequencyInHertz);
			static std::string* CreateSetOutputClockFrequencySmootherConfigurationMsg(const Frequency lockedBandwidth, const Frequency unlockedBandwidth);
			static std::string* CreateSetOutputClockFrequencySmootherEnableMsg(const Bool enabled);
			static std::string* CreateSetPermittedMacAddressesMsg(const uint8 portNumber,
																  const uint8 numberOfMacAddresses,
																  const EthernetAddress macAddresses[MAX_PERMITTED_MAC_ADDRESSES]);
			static std::string* CreateSetPhaseAlignedOutputClockFrequencyMsg(const uint8 output, const uint32 divisor);
			static std::string* CreateSetTimeCorrectionConfigurationMsg(const TimeTransport sourceType,
																		const uint8 id,
																		const Bool enabled,
																		const uint32 monitoringPeriod);
			static std::string* CreateSetTimeCorrectionDampingFactorMsg(const TimeTransport sourceType,
															            const uint8 id,
															            const float dampingFactor);
			static std::string* CreateSetProportionalAndIntegralGainsMsg(const TimeTransport sourceType, const uint8 id,
																		 const double unlockedProportionalGain,
																		 const double lockedProportionalGain,
																		 const double unlockedIntegralGain,
																		 const double lockedIntegralGain);
			static std::string* CreateSetPtpPortEnabledMsg(const uint8 ptpPortNumber, const Bool enabled);
			static std::string* CreateSetPtpPortStateMsg(const uint8 ptpPortNumber, const PTPPortState ptpPortState);
			static std::string* CreateSetRequestedAnnounceMessagePeriodMsg(const uint8 ptpPortNumber, const sint8 logPeriod, const uint32 grantDuration);
			static std::string* CreateSetRequestedDelayRequestMessagePeriodMsg(const uint8 ptpPortNumber, const sint8 logPeriod, const uint32 grantDuration);
			static std::string* CreateSetRequestedSyncMessagePeriodMsg(const uint8 ptpPortNumber, const sint8 logPeriod, const uint32 grantDuration);
			static std::string* CreateSetSuppressPhaseJumpMsg(const Bool phaseJumpSuppressionEnabled);
			static std::string* CreateSetTODOutputConfigurationMsg(const uint8 onePPSOutput, const uint8 uartOutput, const Bool enabled, const TODTimeCode timeCode, const UartBaudRate uartBaudRate);
			static std::string* CreateSetToPSyncPtpSystemParametersMsg(const ToPSyncPtpSystemParameters ptpSystemParameters);
			static std::string* CreateSetToPSyncSystemExceptionsConfigurationsMsg(const Bool reportExceptionsUnsolicited);
			static std::string* CreateSetToPSyncSystemStateMsg(const ToPSyncSystemState newSystemState);
			static std::string* CreateSetToPSyncUploadConfigurationMsg(const ToPSyncUploadConfiguration uploadConfiguration);
			static std::string* CreateUpgradeFirmwareMsg(const uint32 encryptionKey[FIRMWARE_ENCRYPTION_KEY_NUMBER_OF_WORDS]);
			static std::string* CreateFirmwareBurstMsg(const uint8 burstData[FIRMWARE_BURST_DATA_LENGTH], const uint16 burstDataSize, const uint16 burstNumber);
			static std::string* CreateFirmwareCrcMsg(const uint32 receivedCrc);

			static std::string* CreateSetAcceptablePartnerTableRequiredMsg(const uint8 ptpPortNumber, const Bool enabled, const Bool slave);
			static std::string* CreateGetAcceptablePartnerTableRequiredMsg(const uint8 ptpPortNumber, const Bool slave);
                        static std::string* ControlMessageUtilities::CreateDeleteAcceptablePartnerMsg(const uint8 ptpPortNumber, const TransmissionProtocolAddress address, const PortId portId, const Bool slave);

			static std::string* CreateSetTimeReferenceSourceConfigurationMsg(const TimeTransport sourceType, const uint8 id, const ReferenceClockConfiguration timeReferenceSourceConfiguration);
			static std::string* CreateGetTimeReferenceSourceConfigurationMsg(const TimeTransport sourceType, const uint8 id);
			static std::string* CreateToPSyncDiscoveryMsg(void);


			static std::string* CreateGetV1PadMsg(const uint8 ptpPortNumber);
			static std::string* CreateSetV1PadMsg(const uint8 ptpPortNumber, const Bool enable, const Bool force);
			static std::string* CreateGetTODInputConfigurationMsg(const uint8 onePPSInput, const uint8 uartInput);
			static std::string* CreateSetTODInputConfigurationMsg(const uint8 onePPSInput, const uint8 uartInput, const Bool enabled, const TODTimeCode timeCode, const UartBaudRate uartBaudRate);
			static std::string* CreateGetTODInputStatusMsg(const uint8 uart);
			static std::string* CreateSetUTCOffsetMsg(const uint8 onePPS, const sint16 utcOffset, const Bool isValid);
			static std::string* CreateGetUTCOffsetMsg(const uint8 onePPS);
			static std::string* CreateSetImpendingLeapSecondMsg(const uint8 onePPS, const Bool set, const uint16 daysToLeapSecond, const Bool positive);
			static std::string* CreateGetDaysToLeapSecondMsg(const uint8 onePPS);
			static std::string* CreateGetToPSyncTimeMsg(void);

            static std::string* CreateSetMUXInputMsg(MuxID muxId, uint8 line, uint8 muxValue);
            static std::string* CreateGetMUXInputMsg(MuxID muxId, uint8 line);
            static std::string* CreateSetPtpInputClockFrequency(uint8 ptpInputClock, uint32 frequencyInHertz);
            static std::string* CreateGetPtpInputClockFrequency(uint8 ptpInputClock);
            static std::string* CreateSetPtpInputClockEnabled(uint8 ptpInputClock, Bool enabled);
            static std::string* CreateGetPtpInputClockEnabled(uint8 ptpInputClock);
            static std::string* CreateSetPtpInputClockSelected(uint8 ptpInputClock);
            static std::string* CreateGetPtpInputClockSelected(void);
            static std::string* CreateGetHoldoverDurationMsg(void);
            static std::string* CreateSetHoldoverDurationMsg(uint32 holdoverDuration);

            static std::string* CreateGetPtpNodeIdMsg();
            static std::string* CreateSetPtpNodeIdMsg(NodeId id);
            static std::string* CreateGetDefaultPtpNodeIdMsg();

            static std::string* CreateSetNumberOfMissingAnnounceMessagesToDeclareMasterFailedMsg(uint8 ptpPortNumber, uint16 numberOfAnnounceMessages);
            static std::string* CreateGetNumberOfMissingAnnounceMessagesToDeclareMasterFailedMsg(uint8 ptpPortNumber);

            static std::string* CreateSetLockDetectorThresholdMultipleMsg(float multiple);
            static std::string* CreateGetLockDetectorThresholdMultipleMsg();

            static std::string* CreateSETSReadMsg(uint8 address);
            static std::string* CreateSETSWriteMsg(uint8 address, uint8 value);

            static std::string* CreateSetMasterLoadLimitMsg(MasterLoadLimit limitType, uint32 value);
            static std::string* CreateGetMasterLoadLimitMsg(MasterLoadLimit limitType);
            static std::string* CreateGetNodeUTCOffsetMsg();
            static std::string* CreateSetReductionInClockStratumMsg(ClockStratum reductionInClockStratum);
            static std::string* CreateGetReductionInClockStratumMsg();
            static std::string* CreateSetEnablePtpPortMasterOperationMsg(uint8 ptpPortNumber, Bool enable);
            static std::string* CreateGetEnablePtpPortMasterOperationMsg(uint8 ptpPortNumber);
            static std::string* CreateSetEnablePtpPortSlaveOperationMsg(uint8 ptpPortNumber, Bool enable);
            static std::string* CreateGetEnablePtpPortSlaveOperationMsg(uint8 ptpPortNumber);

            static std::string* CreateSetAlarmClientEnabledMsg(AlarmSource source, AlarmSourceIdentity clientId, Bool enable);
            static std::string* CreateGetAlarmClientEnabledMsg(AlarmSource source, AlarmSourceIdentity clientId);
            static std::string* CreateSetAlarmEnabledMsg(AlarmSource source, Bool enable);
            static std::string* CreateGetAlarmEnabledMsg(AlarmSource source);
            static std::string* CreateGetAlarmSetMsg(AlarmSource source, Bool masked);
            static std::string* CreateGetAnyAlarmsSetMsg();

            static std::string* CreateSetPPSOutputSourceMsg(uint8 output, PLLid source);
            static std::string* CreateGetPPSOutputSourceMsg(uint8 output);
            static std::string* CreateSetPPSOutputPeriodMsg(uint8 output, uint8 outputPeriod);
            static std::string* CreateGetPPSOutputPeriodMsg(uint8 output);
            static std::string* CreateSetTimeReferenceSourcePLLBandwidthMsg(TimeTransport timeSource, uint8 id, PLLid pllId, Bool locked, float bandwidth);
            static std::string* CreateGetTimeReferenceSourcePLLBandwidthMsg(TimeTransport timeSource, uint8 id, PLLid pllId, Bool locked);

            static std::string* CreateSetToPSyncParameterMsg(uint16 parameterNumber, float parameterValue);
            static std::string* CreateGetToPSyncParameterMsg(uint16 parameterNumber);
            static std::string* CreateGetGenericParameter1IdMsg(uint8 id, uint16 parameterNumber);
            static std::string* CreateSetGenericParameter1IdMsg(uint8 id, uint16 parameterNumber, float parameterValue);
            static std::string* CreateGetGenericParameter2IdMsg(uint8 id1, uint8 id2, uint16 parameterNumber);
            static std::string* CreateSetGenericParameter2IdMsg(uint8 id1, uint8 id2, uint16 parameterNumber, float parameterValue);

            static std::string* CreateSetAcceptorQuantileMsg(TimeTransport timeSource, uint8 id, Direction direction, uint16 value);
            static std::string* CreateGetAcceptorQuantileMsg(TimeTransport timeSource, uint8 id, Direction direction);

            static std::string* CreateSetNonRevertiveOperationMsg(Bool enabled);
            static std::string* CreateGetNonRevertiveOperationMsg();
            static std::string* CreateSetNonRevertiveOperationOnSameTransportMsg(Bool enabled);
            static std::string* CreateGetNonRevertiveOperationOnSameTransportMsg();
            static std::string* CreateGetMessagePeriodMsg(const uint8 ptpPortNumber,	const MessageType messageType,
                                                        const Bool  multicast, const Bool required);
            static std::string* CreateSetMessagePeriodMsg(const uint8 ptpPortNumber, const MessageType messageType,
                                                        const Bool multicast, const Bool required,
                                                        const LogMessagePeriod logPeriod, const uint32 grantDuration);
            static std::string* CreateSetPtpPortAddressingModeMsg(const uint8 ptpPortNumber, const PtpPortTransmissionAddressing mode);
            static std::string* CreateGetPtpPortAddressingModeMsg(const uint8 ptpPortNumber);
            static std::string* CreateSetForcePtpPortTwoStepOperationMsg(const uint8 ptpPortNumber, const Bool force);
            static std::string* CreateGetForcePtpPortTwoStepOperationMsg(const uint8 ptpPortNumber);
            static std::string* CreateGetPhaseErrorGradientMsg();
            static std::string* CreateSetSpeculativeUnicastAnnounceLogMessagePeriodMsg(uint8 ptpPortNumber, LogMessagePeriod logMessagePeriod);
            static std::string* CreateGetSpeculativeUnicastAnnounceLogMessagePeriodMsg(uint8 ptpPortNumber);
            static std::string* CreateSetEnableSpeculativeUnicastAnnounceTransmissionMsg(uint8 ptpPortNumber, Bool enable);
            static std::string* CreateGetEnableSpeculativeUnicastAnnounceTransmissionMsg(uint8 ptpPortNumber);

            static std::string* CreateSetMaxNumberOfAlternateMastersMsg(uint8 ptpPortNumber, uint8 numMasters);
            static std::string* CreateGetMaxNumberOfAlternateMastersMsg(uint8 ptpPortNumber);

            static std::string* CreateGetMDIODataMsg(uint8 portNumber, uint8 phyAddr, uint8 reg);
            static std::string* CreateSetMDIODataMsg(uint8 portNumber, uint8 phyAddr, uint8 reg, uint16 data);

            static std::string* CreateSetRequireSourceProvidesCorrectTAIMsg(Bool require);
            static std::string* CreateGetRequireSourceProvidesCorrectTAIMsg();
            static std::string* CreateSetRequireSourceProvidesCorrectUTCMsg(Bool require);
            static std::string* CreateGetRequireSourceProvidesCorrectUTCMsg();
            static std::string* CreateSetMaintainBinLockDuringSourceSwitchMsg(Bool set);
            static std::string* CreateGetMaintainBinLockDuringSourceSwitchMsg();

            static std::string* CreateSetEnableAutomaticLeapSecondDetectionMsg(Bool enable);
            static std::string* CreateGetEnableAutomaticLeapSecondDetectionMsg();
            static std::string* CreateSetTimeOfDayMessagePersistenceThresholdMsg(uint8 persistenceThreshold);
            static std::string* CreateGetTimeOfDayMessagePersistenceThresholdMsg();
            static std::string* CreateSetBinLockPhaseErrorInputFilterBandwidthLockedMsg(TimeTransport sourceType, uint8 id, float bandwidth);
            static std::string* CreateSetBinLockPhaseErrorInputFilterBandwidthUnlockedMsg(TimeTransport sourceType, uint8 id, float bandwidth);
            static std::string* CreateGetBinLockPhaseErrorInputFilterBandwidthLockedMsg(TimeTransport sourceType, uint8 id);
            static std::string* CreateGetBinLockPhaseErrorInputFilterBandwidthUnlockedMsg(TimeTransport sourceType, uint8 id);

            static std::string* CreateGetDenialOfServiceProtectionActiveTimeMsg();
            static std::string* CreateGetDenialOfServiceProtectionActiveIncidentsMsg();

            static std::string* CreateSetDoNotBecomeMasterWhenTaiIsUnknownMsg(uint8 ptpPortNumber, Bool set);
            static std::string* CreateGetDoNotBecomeMasterWhenTaiIsUnknownMsg(uint8 ptpPortNumber);
            static std::string* CreateSetDoNotBecomeMasterWhenUtcIsUnknownMsg(uint8 ptpPortNumber, Bool set);
            static std::string* CreateGetDoNotBecomeMasterWhenUtcIsUnknownMsg(uint8 ptpPortNumber);

            static std::string* CreateSetPPSInputTimeMsg(uint8 onePPSInput, ToPSyncTime timeInput, ToPSyncTimescale timeScale);

            static std::string* CreateSetMasterPacketInterfaceSpeedMsg(uint8 ptpPortNumber, float speed);
            static std::string* CreateGetMasterPacketInterfaceSpeedMsg(uint8 ptpPortNumber);

            
            static std::string* CreateSetNPIAcceptPathRequestMessagesMsg(uint8 physicalPortNumber, TransmissionProtocol protocol, Bool enable);
            static std::string* CreateGetNPIAcceptPathRequestMessagesMsg(uint8 physicalPortNumber, TransmissionProtocol protocol);
            static std::string* CreateGetAnnounceNumberOfGrantsIssuedMsg(uint8 ptpPortNumber);
            static std::string* CreateGetSyncNumberOfGrantsIssuedMsg(uint8 ptpPortNumber);
            static std::string* CreateGetDelayResponseNumberOfGrantsIssuedMsg(uint8 ptpPortNumber);

            static std::string* CreateGetAnnounceGrantsIssuedChangeCounterMsg(uint8 ptpPortNumber);
            static std::string* CreateGetSyncGrantsIssuedChangeCounterMsg(uint8 ptpPortNumber);
            static std::string* CreateGetDelayResponseGrantsIssuedChangeCounterMsg(uint8 ptpPortNumber);
            static std::string* CreateGetIssuedGrantDetailsMsg(uint8 ptpPortNumber, MessageType messageType, uint16 index);

            static std::string* CreateSetFrequencyOutputsToFollowTimeSmootherMsg(Bool enable);
            static std::string* CreateGetFrequencyOutputsToFollowTimeSmootherMsg();

            static std::string* CreateSetPtpPortPathDelayRequestTransmissionEnabledMsg(uint8 ptpPortNumber, Bool enable);
            static std::string* CreateGetPtpPortPathDelayRequestTransmissionEnabledMsg(uint8 ptpPortNumber);

            static std::string* CreateSetEnablePhaseBuildOutMsg(TimeTransport timeSource, uint8 id, Bool enable);
            static std::string* CreateGetEnablePhaseBuildOutMsg(TimeTransport timeSource, uint8 id);
            static std::string* CreateSetUnselectedPhaseLagFilterBandwidthOpenMsg(TimeTransport timeSource, uint8 id, Frequency bandwidth);
            static std::string* CreateSetUnselectedPhaseLagFilterBandwidthCloseMsg(TimeTransport timeSource, uint8 id, Frequency bandwidth);
            static std::string* CreateGetUnselectedPhaseLagFilterBandwidthOpenMsg(TimeTransport timeSource, uint8 id);
            static std::string* CreateGetUnselectedPhaseLagFilterBandwidthCloseMsg(TimeTransport timeSource, uint8 id);

            static std::string* CreateSetRequireFrequencyTraceableToPrimaryRefSourceMsg(Bool require);
            static std::string* CreateGetRequireFrequencyTraceableToPrimaryRefSourceMsg();
            static std::string* CreateSetDoNotBecomeMasterIfSourceIsNotPrsMsg(uint8 ptpPortNumber, Bool set);
            static std::string* CreateGetDoNotBecomeMasterIfSourceIsNotPrsMsg(uint8 ptpPortNumber);

            static std::string* CreateSetPPSInputTimeOfDayMsg(uint8 onePPSInput, ToPSyncTimeOfDay timeInput, ToPSyncTimescale timeScale);
                                           
            static std::string* CreateGetHoldoverValidityMsg(void);
            /* The next function is not ready to be tested*/
// 			static std::string* CreateImpairmentDataMessageArrivedMsg(const uint16 impairmentController,
// 																	const uint8 direction,
// 																	const uint16 dataSize,
// 																	const uint32 offset,
// 																	const uint8 data[MAX_NEW_IMPAIRMENT_DATA]);

        private:
            static uint32 mSecurityKey;
	};
}

#endif
