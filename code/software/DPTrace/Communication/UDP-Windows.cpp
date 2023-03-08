/*
Copyright ?2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: UDP-Windows.cpp $
Version     $Revision: 14 $
Date		$Date: 29/04/08 15:27 $

*/

#include "UDP.hpp"

using namespace Semtech;

bool Semtech::UDP::Port::Open(Semtech::IP::PortNumber myPortNumber, uint8 myInterfaceNumber)
{

	if (myInterfaceNumber!=IP::unknownInterface && myInterfaceNumber>=IP::GetNumberOfNetworkInterfaces()) return false;

	portNumber = myPortNumber;
	interfaceNumber = myInterfaceNumber;

	struct sockaddr_in sa;
	int		addressSize = sizeof(sa);
	BOOL allowBroadcast = TRUE;
	
	sock = ::socket(AF_INET, SOCK_DGRAM, 0);        /* create the socket */
	if (sock == INVALID_SOCKET)
	{
		/* we don't exist !? */
		goto fail;
	}

	if (interfaceNumber==IP::unknownInterface)
	{ // Don't bind to a specific interface/address
		memset(&sa, 0, sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{ // Bind to the given interface
		sa = GetMyAddress();
	}
	sa.sin_port = htons(portNumber);

	//lint -e{740}  Info -- Unusual pointer cast (incompatible indirect types)
	if (bind(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == SOCKET_ERROR) 
	{
		closesocket(sock);
		goto fail;
	}


	if (setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char*)&allowBroadcast,sizeof(BOOL)) == SOCKET_ERROR)
	{
		closesocket(sock);
		goto fail;
	}

	//lint -e{740}  Info -- Unusual pointer cast (incompatible indirect types)
	if (getsockname(sock,(struct sockaddr *)&sa,&addressSize) == SOCKET_ERROR)
	{
		closesocket(sock);
		goto fail;
	}

	portNumber = ntohs(sa.sin_port);

	open = true;
	return open;

fail:
	open = false;
	return open;
}



bool Semtech::UDP::Port::Send(IP::Address const& destination, uint8 const data[], uint16 length)
{

	//lint -e{740}  Info -- Unusual pointer cast (incompatible indirect types)
	if (sendto(sock,(char*)data,length,0,(struct sockaddr *)&destination, sizeof(destination)) != length)
	{
		//int error = WSAGetLastError();
		return false;
	}
	return true;
}

//lint -e{771} Symbol 'bytesReceived' (line 108) conceivably not initialized
sint32 Semtech::UDP::Port::Receive(IP::Address& source, uint8 data[], uint16 maxLength)
		// MUST BE THREAD SAFE
{
	int addressSize = sizeof(IP::Address);
	sint32 bytesReceived;
	bool failed = false;

	do
	{
	//lint -e{740}  Info -- Unusual pointer cast (incompatible indirect types)
		bytesReceived = recvfrom(sock,(char*)data,maxLength,0, (struct sockaddr *)&source, &addressSize);

		if (bytesReceived >= 0) break;

		int error = WSAGetLastError();

		switch(error)
		{
		case WSAEMSGSIZE:
		case WSAECONNRESET:
		case WSAEINTR:
			break;

		case WSAENOTSOCK:
			// thread termiated
			failed = true;
			break;

		default:
			failed = true;
			break;
		}
	}
	while (!failed);

	if (failed) bytesReceived = -1;

	return bytesReceived;
}

bool Semtech::UDP::Port::JoinMulticastGroup(Semtech::IP::Address const& group)
{
	struct ip_mreq FAR groupStructure;

	groupStructure.imr_multiaddr = group.sin_addr;
	groupStructure.imr_interface = GetMyAddress().sin_addr;

	int result = setsockopt (sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
						(char *)&groupStructure, sizeof(groupStructure));

	return (result == 0 ? true : false);
}

const SOCKET& Semtech::UDP::Port::GetSocket() const
{
	return sock;
}

Semtech::IP::Address Semtech::UDP::Port::GetMyAddress() const
{
	struct sockaddr_in sa = IP::GetInterfaceAddress(interfaceNumber);

	sa.sin_port = htons(portNumber);    /* this is our port number or may be 0 (for any port)*/

	return sa;
}