/*
Copyright ?2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: IP-windows.cpp $
Version     $Revision: 9 $
Date		$Date: 9/03/07 14:48 $

*/

#include "ip.hpp"
//#include <memory.h>

bool InitialiseSemtechWindowsIP(void);

using namespace Semtech;

// lint -e{528}  symbol not referenced It is there to ensure the function runs early
static bool initialised = InitialiseSemtechWindowsIP();

#define MAJOR_SOCKET_VERSION 2
#define MINOR_SOCKET_VERSION 2


static uint16 SocketVersion()
{
	uint16 result;

	result = MINOR_SOCKET_VERSION << 8 | MAJOR_SOCKET_VERSION;

	return result;
}

Semtech::IP::InterfaceNumber Semtech::IP::GetNumberOfNetworkInterfaces()
{
	Semtech::IP::InterfaceNumber result = 0;
	struct hostent *hp;
	char	hostName[IP::maxHostNameLength+1];

	gethostname(hostName, IP::maxHostNameLength);        /* who are we? */
	
	hp = gethostbyname(hostName);                 /* get our address info */
	if (hp == NULL)
	{
		/* we don't exist ! */
		return 0;
	}

	//find correct interface
	for (result = 0;; result++)
	{
		if (hp->h_addr_list[result] == NULL)
		{
			//end of list
			break;
		}
	}

	return result;
}

Semtech::IP::InterfaceNumber Semtech::IP::FindInterfaceNumber(Semtech::IP::Address const& localAddress)
{
	InterfaceNumber interfaces = GetNumberOfNetworkInterfaces();
	InterfaceNumber result = 0;
	
	for (;result < interfaces; result++)
	{
		Semtech::IP::Address interfaceAddress = GetInterfaceAddress(result);

		if (localAddress.sin_family == interfaceAddress.sin_family &&
			localAddress.sin_addr.S_un.S_addr == interfaceAddress.sin_addr.S_un.S_addr)
			break;
	}

	if (result >= interfaces)
		result = unknownInterface;

	return result;
}

Semtech::IP::Address Semtech::IP::GetInterfaceAddress(Semtech::IP::InterfaceNumber interfaceNumber)
{
	struct hostent *hp;
	struct sockaddr_in sa;
	char	hostName[IP::maxHostNameLength+1];
	
	memset(&sa, 0, sizeof(struct sockaddr_in)); /* clear our address */
	gethostname(hostName, IP::maxHostNameLength);        /* who are we? */
	
	hp = gethostbyname(hostName);                 /* get our address info */
	if (hp == NULL)
	{
		/* we don't exist !? return zeroed address */
		return sa;
	}

	sa.sin_family = hp->h_addrtype;             /* this is our host address */

	if (GetNumberOfNetworkInterfaces() > interfaceNumber)
	{
		memcpy((char *)&sa.sin_addr, hp->h_addr_list[interfaceNumber], (unsigned short) hp->h_length);   /* set address */
	}
	else
	{
		memset((char *)&sa.sin_addr, 0, (unsigned short) hp->h_length);
	}

	return sa;
}


bool InitialiseSemtechWindowsIP(void)
{
  WSADATA info;

  /* initialize the socket library */
  if (WSAStartup(SocketVersion(), &info) == SOCKET_ERROR) 
		return false;
  
  return true;
}

int operator==(Semtech::IP::Address const & left, Semtech::IP::Address const & right)
{
	if(left.sin_port != 0 && right.sin_port != 0 && left.sin_port != right.sin_port) return 0;
	if(left.sin_family != right.sin_family) return 0;
	if(left.sin_addr.S_un.S_addr != right.sin_addr.S_un.S_addr) return 0;
	
	return 1;
}
