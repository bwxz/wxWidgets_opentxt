#ifndef IP_HEADER_UTILITIES_H
#define IP_HEADER_UTILITIES_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

void WriteIp4Header(uint8 data[], uint8 tos,
		uint8 ttl, uint8 protocol, uint8 const sourceAddress[], uint8 const destinationAddress[],
		uint16 length);  // length is length of PAYLOAD (excluding header)

Bool WriteIp4HeaderTemplate(uint8* ptr, uint8 tos,
	uint8 ttl, uint8 protocol, uint8 const sourceAddress[],
	uint16 length);	 // length is length of PAYLOAD (excluding header)
//returns true if the header has changed

void WriteIp6Header(uint8 data[], uint8 tos,
		uint8 ttl, uint8 protocol, uint8 const sourceAddress[], uint8 const destinationAddress[],
		uint16 length);  // length is length of PAYLOAD (excluding header)

Bool WriteIp6HeaderTemplate(uint8* ptr, uint8 tos,
	uint8 ttl, uint8 protocol, uint8 const sourceAddress[],
	uint16 length);	 // length is length of PAYLOAD (excluding header)
//returns true if the header has changed

uint16 CalculateIP4HeaderChecksum(uint8 const ipHeader[]);
void SetIP4HeaderChecksum(uint8* ipHeader);	 // Header is assumed to be 20 bytes - result is Big Endian

typedef enum
{
	noUDPChecksum,			/* the software clears the UDP header checksum */
	packetUDPChecksum,		/* the software generates and writes the UDP header checksum */
	hwUDPChecksum,			/* an interim checksum is passed to the hardware and it generates the final checksum */
} UDPChecksumType;

void WriteUDPHeader(uint8 udpPacket[],
		uint16 sourcePort, uint16 destinationPort, uint16 length); // length is length of PAYLOAD (excluding header)

Bool WriteUDPHeaderTemplate(uint8* ptr,
	uint16 sourcePort, uint16 destinationPort, uint16 length); // length is length of PAYLOAD (excluding header)

uint16 CalculateUDPHeaderChecksum(uint8 const ipPacket[], uint8 const udpPacket[]);
void SetUDPHeaderChecksum(uint8 *ethernetFrame, uint8 udpPacket[], UDPChecksumType udpChecksumType, uint16 checksum, ClockId clockId);

#ifdef __cplusplus
}
#endif

#endif
