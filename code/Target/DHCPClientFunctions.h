#ifndef DHCP_CLIENT_FUNCTIONS_H
#define DHCP_CLIENT_FUNCTIONS_H

#include "Socket.h"

void DhcpEnable(ttUserInterface interfaceHandle);

void DhcpRequestAddressLease(ttUserInterface interfaceHandle, uint32 mHomeIndex, uint32 requestedDHCPLeaseLengthSecs);

void DhcpDisableArpProbes(ttUserInterface interfaceHandle);

#endif
