/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.

Name        $Workfile: TransmissionProtocol.h $
Version     $Revision: 25 $
Date        $Date: 24/06/09 15:30 $
*/

#ifndef TRANSMISSION_PROTOCOL_ADDRESS_H
#define TRANSMISSION_PROTOCOL_ADDRESS_H

#include "General.h"
#include "IP.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  *	The types of transmission protocol.
  */
typedef enum
{
	udp4,			/**< udp over IPv4 transmission protocol */
	ethernet,		/**<Direct Ethernet transmission protocol */
	udp6,			/**< udp over IPv6 transmission protocol */
	numberOfTransmissionProtocols	/**< The number of transmission protocols */
} TransmissionProtocol;

#define IP4_ADDRESS_BYTES 4
#define IP6_ADDRESS_LENGTH 16
#define MAC_ADDRESS_LENGTH	6	/**< The length of a MAC address in bytes. */

/**
  *	The maximum number of bytes in a transmission protocol address.
  */
#define MAX_TRANSMISSION_PROTOCOL_ADDRESS_BYTES IP6_ADDRESS_LENGTH

/**
  *	Structure type defining a transmission protocol address.
  */
typedef struct
{
	TransmissionProtocol protocol : 8;	/**< The transmission protocol */
	uint8 length;						/**< The length of the transmission protocol */
	uint8 data[MAX_TRANSMISSION_PROTOCOL_ADDRESS_BYTES];	/**< The transmission protocol address bytes, stored in big endian order */
} TransmissionProtocolAddress;

typedef enum
{
	equalTPA,
	leftLessThanRightTPA,
	leftGreaterThanRightTPA
}TpaComparisonResult;


typedef uint8 EthernetAddress[MAC_ADDRESS_LENGTH];	/**< Six-byte Ethernet MAC address. */


/**
  *	Structure type defining an enhanced transmission protocol address, which includes the client
  * identifier.
  */
typedef struct
{
	TransmissionProtocolAddress node;  /**< The transmission protocol address */
	uint16 client;					/**< The client Id.  This can be a port or an Ethertype */
} EnhancedTransmissionProtocolAddress;


#define IsValidTPA(tpa) ((((tpa) != NULL) && ((tpa)->length > 0)) ? TRUE : FALSE)
#define SetInvalidTPA(tpa) ((tpa)->length = 0)
Bool HasDataTPA(TransmissionProtocolAddress const* address);

Bool AreEqualTPA(TransmissionProtocolAddress const* l, TransmissionProtocolAddress const* r);
TpaComparisonResult CompareTPAs(const TransmissionProtocolAddress *l, const TransmissionProtocolAddress *r);
TpaComparisonResult CompareTPAData(const TransmissionProtocolAddress *l, const TransmissionProtocolAddress *r);
void SetTPA(TransmissionProtocolAddress* tpa, TransmissionProtocol protocol, uint8 const data[], uint8 byteCount);
void SetTPAInvalid(TransmissionProtocolAddress* tpa);
uint32 ConvertAddressArrayToInteger(uint8 const address[]);
// only useful when address equals 4 bytes (data[0] is in most significant byte of output)
#define ConvertTPAddressToInteger(address) ConvertAddressArrayToInteger(GetTPAddressData(address))
// only useful when address equals 4 bytes (data[0] is in most significant byte of output)

TransmissionProtocolAddress ConvertIntegerIPAddressToTP(uint32 input);
// only useful when address is no bigger than 4 bytes (data[0] is in most significant byte of output)

//#define for backward compatibility
#define ConvertIntegerToTPAddressUDP ConvertIntegerIPAddressToTP

TransmissionProtocolAddress ConvertArrayToTPAddress(uint8 const input[], uint8 length, TransmissionProtocol protocol);

void SetTPAddress(TransmissionProtocolAddress* output, uint8 const input[], TransmissionProtocol protocol);

#define GetTPAddressProtocol(tpa) ((tpa)->protocol)
#define GetTPAddressData(tpa) ((tpa)->data)
#define GetTPAddressLength(tpa) ((tpa)->length)
TransmissionProtocol FindTransmissionProtocolFromEthernetFrame(uint8 const frame[]);
uint16 FindEthertypeFromProtocolId(TransmissionProtocol protocol, uint16 clientProtocolId);
uint8 GetAddressLengthFromTransmissionProtocol(TransmissionProtocol protocol);

#define IsValidETPA(etpa) IsValidTPA(&(etpa)->node)

void MapMulticastAddressToEthernetAddress(TransmissionProtocolAddress* physicalAddress,TransmissionProtocolAddress const* protocolAddress);


char const* AddressText(TransmissionProtocolAddress const* tpa);

#ifdef __cplusplus
}
#endif

#endif
