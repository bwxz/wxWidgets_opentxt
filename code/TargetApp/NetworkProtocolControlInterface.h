#ifndef NETWORK_PROTOCOL_CONTROL_INTERFACE_H
#define NETWORK_PROTOCOL_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"

#ifdef __cplusplus
extern "C" {
#endif



ToPSyncConfigResult DoSetNetworkProtocolInterfaceParameter(uint8 port, TransmissionProtocol protocol, uint16 parameter, float value);
ToPSyncConfigResult DoGetNetworkProtocolInterfaceParameter(uint8 port, TransmissionProtocol protocol, uint16 parameter, float *value);

#ifdef __cplusplus
}
#endif

#endif

