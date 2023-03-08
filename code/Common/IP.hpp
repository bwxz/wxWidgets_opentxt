/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: IP.hpp $
Version     $Revision: 11 $
Date		$Date: 24/07/07 15:29 $

*/

#ifndef IP_HPP  //to prevent clash with ip.h in targetapp
#define IP_HPP

#if defined(_MSC_VER) || defined (__BCPLUSPLUS__)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#endif

#include "General.h"

namespace Semtech
{
	namespace IP
	{
		typedef uint16 PortNumber;
		typedef sockaddr_storage Address;
		typedef uint32 InterfaceNumber;
		
		const int maxHostNameLength = 100;
		const int addressBytes = 4;
		const InterfaceNumber unknownInterface = 0xFFFFFFFF;
		
		Semtech::IP::Address GetInterfaceAddress(InterfaceNumber interfaceNumber = 0, uint32 family = AF_INET); 
		InterfaceNumber FindInterfaceNumber(Semtech::IP::Address const& localAddress); // unknownInterface says it is not recognised


		void ConvertAddressToString(IP::Address const& address, char *text, const int length = maxHostNameLength);

		int ReadAddress(char const text[], 
			uint8 address[], PortNumber& port);
		
		bool ReadAddress(char const text[], IP::Address& address, char const *portStr = NULL);
			/* If text holds an IP address in the format
			"nnn.nnn.nnn.nnn" or IP address and port number in
			the format "nnn.nnn.nnn.nnn:ppp" the reads them.  
			
			  If the address is read, the bytes are
			  written to the first 4 bytes (addressBytes) of address.  
			  The most significant is written to bytes 0.
			  
				If the port is read, it is written to port, if not
				port in unchanged 
				
				For int return
				  If the port and address are read 2 is returned
				  If the address only is read 1 is returned
				  If neither are read 0 is returned.  

				For bool return 
				  If the port and address are read true is returned
				  If the address only is read true is returned and port == 0
				  If neither are read 0 is returned.  

		    If text holds an IPv6 address in standard dotted notation, it will be converted 
			to an Address.
			The appended port string is only supported with an IPv4 address string when the portStr
			is NULL. If portStr is set, it will be converted to a port number and set in the address
			structure.
		*/
		uint16 GetPortNumber(IP::Address const& address);
		void SetPortNumber(IP::Address const& address, PortNumber port);
		Bool IsAddressWildcard (IP::Address const &address);
		bool CompareIPAddress(Semtech::IP::Address const & left, Semtech::IP::Address const & right, bool addressOnly = FALSE);
	}
}

inline bool operator==(Semtech::IP::Address const & a,Semtech::IP::Address const & b) {return Semtech::IP::CompareIPAddress(a, b, TRUE);}
inline bool operator!=(Semtech::IP::Address const & a,Semtech::IP::Address const & b) {return !(a == b);}

#endif

