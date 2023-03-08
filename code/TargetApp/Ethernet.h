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
#ifndef ETHERNET_H
#define ETHERNET_H

#define MAC_ADDRESS_LENGTH 6
#define ETHERNET_PREAMBLE_LENGTH 8 /* Including SYNC octet*/
#define ETHERNET_HEADER_LENGTH 14
#define ETHERNET_FCS_LENGTH 4

#define ETHERNET_DESTINATION_ADDRESS_OFFSET 0
#define ETHERNET_SOURCE_ADDRESS_OFFSET MAC_ADDRESS_LENGTH
#define ETHERTYPE_OFFSET(ethernetPayloadOffset)	((ethernetPayloadOffset) - 2)	/* Ethertype is immediately before payload */
#define MIN_ETHERNET_FRAME_LENGTH 64
#define MIN_ETHERNET_FRAME_PAYLOAD_LENGTH (MIN_ETHERNET_FRAME_LENGTH - ETHERNET_HEADER_LENGTH - ENET_FRAMESIZE_TAIL)

#define DOT1Q_HEADER_LENGTH 4

#endif
