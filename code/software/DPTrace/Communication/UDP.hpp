/*
Copyright © 2004 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name		$Workfile: UDP.hpp $
Version     $Revision: 12 $
Date		$Date: 9/03/07 14:48 $

*/

#ifndef UDP_H
#define UDP_H
#include <winsock.h>
#include "IP.hpp"
#include "General.h"

namespace Semtech
{
	namespace UDP
	{
		class Port
		{
		private:
			IP::PortNumber	portNumber;
			SOCKET sock;
			bool open;
			uint8 interfaceNumber;
			
		public:
			Port() : portNumber(0), open(false), sock(0), interfaceNumber(0) {}
			Port(Semtech::IP::PortNumber aPortNumber, uint8 interfaceNumber = 0) 
				{Open(aPortNumber, interfaceNumber);}
			
			~Port() {Close();}
			
			bool Send(Semtech::IP::Address const& destination, uint8 const data[], uint16 length);
			sint32 Receive(Semtech::IP::Address& source, uint8 data[], uint16 maxLength);
			// returns number of bytes received;
			
			bool Open(Semtech::IP::PortNumber myPortNumber = 0, uint8 interfaceNumber = 0);
				// portNumber of 0 == any port number - use for client ports
				// interfaceNumber is only needed when the card has more than 1 Network IF card

			void Close() {if (open) closesocket(sock); open = false;}
			bool JoinMulticastGroup(Semtech::IP::Address const& group);

			bool IsOpen() const {return open;}
			IP::PortNumber GetPortNumber() const {return portNumber;}
			Semtech::IP::Address GetMyAddress() const;  // includes port number
			const SOCKET& GetSocket() const;

		private:
			
			void Initialise();
		};
	}
}
#endif

