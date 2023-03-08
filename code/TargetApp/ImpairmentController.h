#ifndef IMPAIRMENT_CONTROLLER_H
#define IMPAIRMENT_CONTROLLER_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "IEEE1588Time.h"
#include "impairmentControlInterface.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUMBER_OF_IMPAIRMENTS_PER_BANK (NUMBER_OF_IMPAIRMENTS_PER_API_MSG)
#define NUMBER_OF_IMPAIRMENT_BANKS 4
#define MIN_WRITTEN_BANKS_AT_START 2

/*
 * controller           - Pointer back to the controller object that this belongs to.
 * data                 - 2D array of doubles in banks so that while one bank is in use others can be renewed
 * dataBankNotEmpty     - an array, one element for each `data` bank. TRUE indicates the bank is *not* empty
 * hasHeldValidData     - a flag to indicate that initialisation of the data banks has completed. It is only
 *                        cleared when the impairment configuration is set and is set once enough delay data
 *                        has been buffered. See #define MIN_WRITTEN_BANKS_AT_START.
 * currentBank          - index into `data` array to select the current bank in use
 * direction            - m2s or s2m
 * dataRequestPeriod    - The period at which, upon a request for new impairment data, the controller will also
 *                        request a data "top-up" from the server. The "period" is in number-of-delays.
 * impairmentIndex      - This is the offset into the current data bank of the next delay to use
 * impairmentValuesUsed - A rolling counter of the number of impairments that have been used in total. Note
 *                        that the counter is only updated once a data bank has been fully used so increments
 *                        in steps of `numberOfImpairments`
 */
typedef struct
{
	struct ImpairmentControllerStruct* controller;

	double data[NUMBER_OF_IMPAIRMENT_BANKS][NUMBER_OF_IMPAIRMENTS_PER_BANK];
	Bool dataBankNotEmpty[NUMBER_OF_IMPAIRMENT_BANKS];
	Bool hasHeldValidData;
	Bool hasRequestedValidData;
	uint8 currentBank;
	Direction direction;

	uint16  dataRequestPeriod;
	uint16  impairmentIndex;
	uint32  impairmentValuesUsed;
} ImpairmentDirection;

/*
 * enabled            - As the name suggests.
 * masterPtpPortIndex - Stored internally this is just an index directly into controlData.ptpPortArray[].
 *                      When going externally to the user this will be translated so that first master port
 *                      starts at index 1.
 * masterToSlave      - holds impairment config for the master-to-slave direction
 * slaveToMaster      - holds impairment config for the slave-to-master direction
 * server             - The Ethernet/IPv4/IPv6 address of the impairment server for this controller.
 */
typedef struct ImpairmentControllerStruct
{
	Bool				enabled;
	uint8               masterPtpPortIndex;
	ImpairmentDirection masterToSlave;
	ImpairmentDirection slaveToMaster;
	EnhancedTransmissionProtocolAddress server;
} ImpairmentController;


void InitialiseImpairmentController(ImpairmentController* imp, uint8 masterPtpPortIndex);

IEEE1588Time Impair(ImpairmentController* imp, IEEE1588Time const* input, Direction direction);

void GetImpairmentConfiguration(ImpairmentController const *imp, ImpairmentConfiguration *impairmentConfiguration);

void ImpairmentDataMessageArrived(ImpairmentController* imp, uint8 direction, uint16 dataSize, uint32 offset,
								  const double data[]);

void SetImpairmentDirectionConfiguration(ImpairmentDirection* dir, ImpairmentConfiguration const* impairmentConfiguration);

#ifdef __cplusplus
}
#endif


#endif

