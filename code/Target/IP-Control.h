#ifndef IP_CONTROL_H
#define IP_CONTROL_H

#include "General.h"
#include "Socket.h"
#include "GlobalData.h"


SocketHandle OpenUDPSocket(const NetworkInterfaceId *networkInterfaceId, uint16 udpPort, TransmissionProtocolAddress *tpa, Bool enableUDPCheckSum, Bool detachFromTask, uint8 tos);
	// returns socket handle if successful or -1 on failure
	// local addres may be INADDR_ANY (0) or IP address of interface we went to bind to

Bool UpdateSocketMulticastGroupMembership(SocketHandle socketHandle,
		TransmissionProtocolAddress *localIpAddress,
		const NetworkInterfaceId *networkInterfaceId,
		TransmissionProtocolAddress *multicastGroup,
		Bool add); //add == FALSE means drop
	// returns true on success
#endif
