/*
Copyright ?2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
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

#ifndef IP_H
#define IP_H

#if defined(_MSC_VER) || defined (__BCPLUSPLUS__)
#include <winsock.h>
#endif

#include "General.h"

namespace Semtech
{
	namespace IP
	{
		typedef uint16 PortNumber;
		typedef sockaddr_in Address;
		typedef uint8 InterfaceNumber;
		
		const int maxHostNameLength = 100;
		const int addressBytes = 4;
		const InterfaceNumber unknownInterface = 0xFF;
		
		Semtech::IP::Address GetInterfaceAddress(InterfaceNumber interfaceNumber = 0); 
		InterfaceNumber FindInterfaceNumber(Semtech::IP::Address const& localAddress); // unknownInterface says it is not recognised
		InterfaceNumber GetNumberOfNetworkInterfaces();


		void ConvertAddressToString(IP::Address& address, char *text);

		int ReadAddress(char const text[], 
			uint8 address[], PortNumber& port);
		
		bool ReadAddress(char const text[], IP::Address& address);
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
				  
		*/
		inline uint16 GetPortNumber(IP::Address& address) {return ntohs(address.sin_port);}
		inline void SetPortNumber(IP::Address& address, PortNumber port) {address.sin_port = htons(port);}
	}
}

int operator==(Semtech::IP::Address const &,Semtech::IP::Address const &);
inline int operator!=(Semtech::IP::Address const &a,Semtech::IP::Address const &b) {return !(a == b);}

#endif

