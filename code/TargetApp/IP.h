/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.

*/




#ifndef IP_H
#define IP_H

#include "Ethernet.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IP4_HEADER_LENGTH						20
#define IP6_MIN_HEADER_LENGTH					40
#define UDP_HEADER_LENGTH						 8

#define IP4_PACKET_LENGTH_OFFSET				 2
#define IP6_PACKET_LENGTH_OFFSET				 4
#define IP4_PACKET_IDENTIFICATION_OFFSET		 4
#define IP4_PACKET_FLAG_FRAGMENT_OFFSET   		 6
#define IP4_PACKET_TTL_OFFSET			 		 8
#define IP4_PACKET_PROTOCOL_OFFSET				 9
#define IP4_PACKET_CHECKSUM_OFFSET				10
#define IP4_PACKET_SOURCE_ADDRESS_OFFSET 		12
#define IP6_PACKET_SOURCE_ADDRESS_OFFSET		 8
#define IP4_PACKET_DESTINATION_ADDRESS_OFFSET 	16
#define IP6_PACKET_DESTINATION_ADDRESS_OFFSET	24
#define IP6_PACKET_FIRST_NEXT_HEADER_OFFSET		 6
#define IP6_PACKET_HOP_LIMIT_OFFSET				 7

#define IP4_PACKET_IDENTIFICATION_SIZE			 2
#define IP4_PACKET_CHECKSUM_SIZE				 2
#define IP4_PROTOCOL_ID_SIZE					 2
#define IP6_NEXT_HEADER_SIZE					 1

#define PTP_IP_TTL 							    64
#define UDP_PROTOCOL_ID 						17
#define ETHERTYPE_DOT1Q						0x8100
#define ETHERTYPE_IP4 						0x0800
#define ETHERTYPE_IP6						0x86DD
#define IP4_ADDRESS_LENGTH 						 4
#define IP6_ADDRESS_LENGTH						16
#define IP6_ADDRESS_PREFIX_LENGTH				 8
#define IP6_INTERFACE_IDENTIFIER_LENGTH			 8

#define UDP_SOURCE_PORT_OFFSET 					 0
#define UDP_DEST_PORT_OFFSET 					 2
#define UDP_LENGTH_OFFSET 						 4
#define UDP_CHECKSUM_OFFSET 					 6

#define UDP_PORT_SIZE							 2
#define UDP_CHECKSUM_SIZE						 2
#define UDP_LENGTH_SIZE							 2

/*
 * TRANSPORT_HEADER_LENGTH includes transport, internet and link header lengths and is used to allocate packets
 * that may have dot1q and ipv6 headers.
 */
#define TRANSPORT_HEADER_LENGTH (ETHERNET_HEADER_LENGTH + DOT1Q_HEADER_LENGTH + IP6_MIN_HEADER_LENGTH + UDP_HEADER_LENGTH)

typedef union
{
		uint8  byte[sizeof(uint32)];
		uint32 word;
} IPAddress;


#define Read2ByteIPField(msg) ((msg)[0] << 8 | (msg)[1])

#define Write2ByteIPField(msg, data) \
	((msg)[0] = (uint8)((data) >> 8), (msg)[1] = (uint8) (data))
#define Write4ByteIPField(msg, data) \
	((msg)[0] = (uint8)((data) >> 24), (msg)[1] = (uint8) (data >> 16), (msg)[2] = (uint8) (data >> 8), (msg)[3] = (uint8) data)

extern uint16 ipIdentifierGlobal; // value (and endianness) doesn't matter (always access via GetNextIPIdentifier();
#define GetIpIdentifier() (++ipIdentifierGlobal)

#ifdef __cplusplus
}
#endif

#endif
