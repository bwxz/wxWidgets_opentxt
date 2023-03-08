#ifndef SYSTEM_MANAGEMENT_H
#define SYSTEM_MANAGEMENT_H

#include "ToPSyncTypes.h"
#include "General.h"


#ifdef __cplusplus
extern "C"
{
#endif

ToPSyncConfigResult DoGetHardwareVersion(uint32 *hardwareVersion);
ToPSyncConfigResult DoGetSoftwareVersion(char *softwareVersion);
ToPSyncConfigResult DoGetToPSyncPartNumber(ToPSyncPartNumber *topSyncPartNumber);
ToPSyncConfigResult DoGetSecondsSinceLastReset(uint32 *systemUpTime);
ToPSyncConfigResult DoGetStoredBootChecksum(uint32 *bootChecksum);
ToPSyncConfigResult DoGetCalculatedBootChecksum(uint32 *bootChecksum);
ToPSyncConfigResult DoGetToPSyncLocation(uint32 *locationId);
ToPSyncConfigResult DoSetToPSyncSystemState(ToPSyncSystemState newSystemState);
ToPSyncConfigResult DoGetToPSyncSystemState(ToPSyncSystemState *systemState);
ToPSyncConfigResult DoSetInitialSystemConfiguration(const ToPSyncInitialSystemConfiguration *systemConfiguration);
ToPSyncConfigResult DoGetInitialSystemConfiguration(ToPSyncInitialSystemConfiguration *systemConfiguration);
ToPSyncConfigResult DoSetToPSyncPtpSystemParameters(const ToPSyncPtpSystemParameters *ptpSystemParameters);
ToPSyncConfigResult DoGetToPSyncPtpSystemParameters(ToPSyncPtpSystemParameters *ptpSystemParameters);
ToPSyncConfigResult DoSetToPSyncUploadConfiguration(const ToPSyncUploadConfiguration *uploadConfiguration);
ToPSyncConfigResult DoGetToPSyncUploadConfiguration(ToPSyncUploadConfiguration *uploadConfiguration);
ToPSyncConfigResult DoGetSecurityKey(uint32 *securityKey);
ToPSyncConfigResult DoSetIpPacketInterfaceConfiguration(uint8 portNumber, const IpPacketInterfaceConfiguration* ipPacketInterfaceConfiguration);

#ifdef __cplusplus
}
#endif


#endif
