#ifndef TWO_LEVEL_ADDRESS_H
#define TWO_LEVEL_ADDRESS_H

#include "TransmissionProtocol.h"
#include "General.h"

typedef struct
{
	TransmissionProtocolAddress		protocol;
	TransmissionProtocolAddress		physical;
} TwoLevelAddress;

void SetTwoLevelAddressInvalid(TwoLevelAddress* add);

#endif




