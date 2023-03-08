#ifndef MESSAGE_SEQUENCE_NUMBER_GENERATOR_H
#define MESSAGE_SEQUENCE_NUMBER_GENERATOR_H

#include "IEEE1588Messages.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	IEEE1588SequenceNumber number[numberOfMessageTypes];

} MessageSequenceNumberGenerator;

#define InitialiseMessageSequenceNumberGenerator(gen) ResetMessageSequenceNumberGenerator(gen)

void ResetMessageSequenceNumberGenerator(MessageSequenceNumberGenerator* gen);

#define GetNextSequenceNumber(gen, messageType) ((gen)->number[messageType]++)
#define GetCurrentSequenceNumber(gen, messageType) ((gen)->number[messageType])

#ifdef __cplusplus
}
#endif

#endif
