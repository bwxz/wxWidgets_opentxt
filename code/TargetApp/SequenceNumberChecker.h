#ifndef SEQUENCE_NUMBER_CHECKER_H
#define SEQUENCE_NUMBER_CHECKER_H


#include "IEEE1588InterfaceTypes.h"
#include "General.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
	IEEE1588SequenceNumber	lastAcceptableSequenceNumber;
	uint16					testsSinceLastAcceptableNumber;

} SequenceNumberChecker;


#define InitialiseSequenceNumberChecker(snc) ResetSequenceNumberChecker(snc)
void ResetSequenceNumberChecker(SequenceNumberChecker* snc); 

Bool IsSequenceNumberAcceptable(SequenceNumberChecker* snc, IEEE1588SequenceNumber input); 

#ifdef __cplusplus
}
#endif

#endif