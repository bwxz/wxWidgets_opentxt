#ifndef TLV_PARSER_H
#define TLV_PARSER_H

#include "General.h"
#include "IEEE1588Messages.h"
#include "SMPTEData.h"

#ifdef __cplusplus
extern "C" {
#endif


void GenerateUnicastGrantRequestOrResponseTLV(uint8** dataPtr, 
	MessageType messageType, LogMessagePeriod logMessagePeriod, uint32 duration, Bool grant, Bool renewalFlag);

void GenerateUnicastCancelAcknowledgeTLV(uint8** dataPtr, MessageType messageType);

void GenerateUnicastCancelTLV(uint8** data, MessageType messageType);
void GenerateUserDataTLV(uint8** data, uint32 const *userData, uint16 userDataLengthInWords);
void GenerateUserDataAckTLV(uint8** data);
void GenerateSmpteDataTLV(uint8** data, SmpteData const *inData);

#ifdef __cplusplus
}
#endif

#endif
