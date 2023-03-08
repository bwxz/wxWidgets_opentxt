/*
Copyright ?2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: IP.cpp $
Version     $Revision: 6 $
Date		$Date: 3/04/07 18:04 $

*/

#include "IP.hpp"
#include <stdio.h>

using namespace Semtech;

int IP::ReadAddress(char const text[], uint8 address[], PortNumber& port)
{
	int readPort = 0;
	int addressArray[addressBytes];

	int valuesRead = sscanf(text,"%u.%u.%u.%u:%u",
		addressArray,
		addressArray+1,
		addressArray+2,
		addressArray+3,
		&readPort
		);

	if (valuesRead < addressBytes) return 0;

	int i;
	for (i = 0; i < addressBytes; i++)
		address[i] = (uint8) addressArray[i];

	int result = valuesRead == 5 ? 2 : 1;

	if (valuesRead == 5)
		port = (PortNumber) readPort;

	return result;
}

bool IP::ReadAddress(char const text[], IP::Address& address)
{
	uint8 nodeAddress[addressBytes]; // length of node address
	PortNumber port = 0;

	int result = ReadAddress(text,nodeAddress,port);

	if (result < 1)
		return false;
	
	address.sin_family = AF_INET;

	if (port != 0)
		address.sin_port = htons(port);

	address.sin_addr.s_addr = 0;

	address.sin_addr.S_un.S_un_b.s_b1 = nodeAddress[0];
	address.sin_addr.S_un.S_un_b.s_b2 = nodeAddress[1];
	address.sin_addr.S_un.S_un_b.s_b3 = nodeAddress[2];
	address.sin_addr.S_un.S_un_b.s_b4 = nodeAddress[3];

	return true;

}

void IP::ConvertAddressToString(IP::Address& address, char *text)
{
        sprintf(text,"%d.%d.%d.%d", address.sin_addr.S_un.S_un_b.s_b1,address.sin_addr.S_un.S_un_b.s_b2,
                address.sin_addr.S_un.S_un_b.s_b3,address.sin_addr.S_un.S_un_b.s_b4);
}




