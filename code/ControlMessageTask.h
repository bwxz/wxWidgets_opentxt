#ifndef CONTROL_MESSAGE_TASK_H
#define CONTROL_MESSAGE_TASK_H

#include "ToPSyncInterfaceTypes.h"
#include "IEEE1588Time.h"
#include "Socket.h"
#include "ApplicationInfrastructureInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOCKET_CONTROLLER_CONFIG_UPD_PHYSICAL (1 << 0)
#define SOCKET_CONTROLLER_CONFIG_UPD_VIRTUAL (1 << 1)
#define SOCKET_CONTROLLER_CONFIG_UPD_MHOMEINDEX (1 << 2)
#define SOCKET_CONTROLLER_CONFIG_UPD_PROTOCOL (1 << 3)
#define SOCKET_CONTROLLER_CONFIG_UPD_UDPPORT (1 << 4)

#define SOCKET_CONTROLLER_CONFIG_ALL_FLAGS \
		(SOCKET_CONTROLLER_CONFIG_UPD_PHYSICAL | \
		 SOCKET_CONTROLLER_CONFIG_UPD_VIRTUAL | \
		 SOCKET_CONTROLLER_CONFIG_UPD_MHOMEINDEX | \
		 SOCKET_CONTROLLER_CONFIG_UPD_PROTOCOL | \
		 SOCKET_CONTROLLER_CONFIG_UPD_UDPPORT)

typedef struct {
	uint32 configured;
	NetworkInterfaceId networkInterfaceId;
	uint32 mHomeIndex;
	uint8 protocol;
	uint16 udpPort;
} SocketControllerConfiguration;

extern SocketControllerConfiguration initialNetworkControlInterfaceConfiguration;

void InitialseControlInterface(void);
void InitialseControlInterfaceFromInitialSystemConfiguration(void);
ToPSyncConfigResult ConfigureControlInterfaceSocket(const SocketControllerConfiguration *socketConfiguration);
void CloseControlInterfaceSocket(void);

uint8 ControlInterfaceNetworkPhysicalPortGet(void);
uint32 ControlInterfaceNetworkVirtualPortGet(void);
uint32 ControlInterfaceNetworkMhomeIndexGet();
uint8 ControlInterfaceNetworkProtocolGet();
uint16 ControlInterfaceNetworkUDPPortGet();
Bool ControlInterfaceIsSocketConfigured(void);

#ifdef __cplusplus
}
#endif

#endif
