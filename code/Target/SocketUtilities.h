/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */

/**
 * SocketUtilities.h
 */
#ifndef SOCKETUTILITIES_H_
#define SOCKETUTILITIES_H_

#include "General.h"
#include "TransmissionProtocol.h"
#include <trsocket.h>

size_t GetSockaddrLength(const struct sockaddr_storage *ss);
void InitialiseSockaddr(struct sockaddr_storage *ss, uint8 family, const void *data, uint16 port);
void GetAddressDataFromSockAddr(struct sockaddr_storage *ss, uint8 *address, uint8 *addressLength);
uint8 GetSockaddrFamilyFromTPA(const TransmissionProtocolAddress *tpa);
void InitialiseETPAFromSockaddr(EnhancedTransmissionProtocolAddress *etpa, const struct sockaddr_storage *ss);

#endif /* SOCKETUTILITIES_H_ */
