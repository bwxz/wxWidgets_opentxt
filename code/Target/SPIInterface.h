/*
Copyright © 2007 Semtech Corporation, P.O. Box 6097, Camarillo, 
CA 93011-6097 U.S.A.  

All rights reserved. The copyright of the content of this file is owned 
by Semtech Corporation (Semtech).  

This is an unpublished work.  The content of this file must be used only 
for the purpose for which it was supplied by Semtech or its distributors.   
The content of this file must not be copied or disclosed unless authorised in 
writing by Semtech.  

Name        $Workfile: SPIInterface.h $
Version     $Revision: 13 $
Date        $Date: 7/11/08 10:06 $
*/
/// @cond FLASH_AND_SPI
/**
 * \file SPIInterface.h
 * Function and type declarations for the SPI Driver
 * 
 * This file describes the driver's API. It provides an explanation of how the
 * driver is used and a description of the basic API functions that comprise the
 * API.
 */

/**
  *	\defgroup SPIDriver ToPSync SPI Driver
  * The ToPSync SPI Driver provides the managed software interface which the ToPSync Control Driver can use to communicate with a ToPSync 
  * via the SPI bus interface.  It provides functions for sending and receiving application messages.  It also provides two functions which the customer must 
  * implement to read/write bytes to/from the SPI interface according to the hardware interface specification.  It also provides a function 
  * which must be called by the customer when the interrupt line goes high.
  * \ingroup ToPSyncDriver
  */

/**
  *	\defgroup SPIInterface SPI Interface
  * Software interface to the SPI bus to be used by the ToPSync Control Driver.
  * \ingroup SPIDriver
  */

/**
  *	\defgroup SPICustomerFunctions SPI Customer-Implemented Functions
  * Functions which must be implemented by the customer to enable the SPI driver to carry out its work.
  * \ingroup SPIDriver
  */


#ifndef	SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "TransmissionProtocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SPI Driver Error Codes.
 * If an error occurs, an appropriate error code can be retrieved by calling
 * the SpiGetLastError() routine.
 */
typedef enum
{
	SPI_NO_ERROR = 0,				/**< No Error */
	SPI_DRIVER_NOT_INITIALISED = 1,	/**< Spi Driver is not initialised. */
	SPI_DATA_LINK_NOT_INITIALISED,	/**< Data Link protocol is not initialised. Call GetLastError() for more details */
	SPI_SMP_NOT_INITIALISED,		/**< Shared Memory Access protocol is not initialised. Call GetLastError() for more details */
	SPI_BUFFER_OVERFLOW,			/**< A buffer overflow has occurred due to an invalid message size passed to the driver. */
	SPI_OUT_OF_MEMORY,				/**< A memory allocation call has failed. */
	SPI_UNKNOWN_FRAME_TYPE,			/**< A data link frame of unknown type has been received and discarded. */
	SPI_INVALID_FRAME_SIZE,			/**< A data link frame of invalid size has been received. */
	SPI_INVALID_FRAME_CRC,			/**< A data link frame has been received with a CRC error. */
	SPI_INVALID_FRAGM_SIZE,			/**< A SMP fragment of invalid size has been received. */
	SPI_TX_TIMEOUT,					/**< A timeout occurred while attempting to transmit a SMP fragment. */
	SPI_UNKNOWN_ERROR				/**< An unknown error has occurred. */
} SpiErrorCode;

/**
 * SPI Driver Statistics.
 * This structure holds the statistics of the SPI link. These consist of
 * statistics gathered by the two layes of the driver's protocol stack:
 * Data Link layer and Shared Memory Access Layer.
 */
typedef struct
{
	/* Data Link Protocol */
	uint	framesTransmitted;		/**< Number of Data Link frames transmitted. */
	uint	framesTransmittedError;	/**< Number of Data Link frames NOT transmitted due to an internal error. */
	uint	framesReceived;			/**< Number of Data Link frames received. */
	uint	framesReceivedError;	/**< Number of Data Link frames received in error. */
} SpiProtocolStats;



/** 
 * Callback function for passing SPI messages.
 * This callback function is registered when the driver is initialised and is used to pass a
 * received message to a higher-layer application.  If an SPI interface is present, the ToPSync Control Interface provides the callback 
 * and initialises the SPI driver.
 * \param messageData 				A pointer to a buffer tha holds the received message.
 * \param messageLength	 			The length of the message in bytes.
 * \param messageSourceInterface 	Identifies the interface over which the message was received.
 * \param messageSourceAddress		Identifies the address corresponding to the receiving interface.
 * \ingroup SPIInterface
 */
typedef void (*SpiMessageReceivedFPtr)(const uint8* messageData, uint32 messageLength, 
									   ExternalInterface messageSourceInterface, 
									   EnhancedTransmissionProtocolAddress const* messageSourceAddress);

/**
 * Initialises the SPI Driver.
 * This function is called to initialise the SPI driver, i.e. reset the protocol states,
 * allocate the appropriate buffers and register a callback function that is used to notify
 * the user that a message has been received.  This function is called by the ToPSync Control Interface upon initialisation, or can 
 * be called directly by the customer control application if the SPI driver is used standalone.
 * \param functionPtr 		A pointer to a callback function which signals that a message has been received.
 * \ingroup SPIInterface
 * \return 					True if initialisation was completed successfully, False otherwise.
 */
Bool SpiInitSpiDriver(SpiMessageReceivedFPtr functionPtr);

/** 
 * Sends an application message over the SPI interface.
 * This function is called to transmit a message over the SPI interface.  This function is called by the ToPSync Control Interface 
 * or can be called directly by the customer control application if the SPI driver is used standalone.
 * \param messageData 		A pointer to a buffer that contains the message to be transmitted..
 * \param messageLength 	The length of the message buffer in bytes.
 * \param watchdogMask		The value of the calling task's Watchdog Monitor mask.  A value of zero has no effect
 * \ingroup SPIInterface
 * \return 					True if transmission was successful, false otherwise.
 */
#ifdef _ARC 
Bool SpiSendMessage(const uint8* messageData, uint16 messageLength, uint32 watchdogMask);
#else
Bool SpiSendMessage(const uint8* messageData, uint16 messageLength);
#endif

/**
 * An interrupt is generated when an SPI message fragment is received over the SPI bus interface.  
 * This function is called by the customer when the SPI interrupt is asserted to denote that
 * a message fragment has been received. The routine will assemble and buffer SPI messages into complete application 
 * messages receive, decode and process the SPI message an, when a complete application message has been received, call 
 * the registered callback to signal the higher layer application. 
 * \ingroup SPIInterface 
 */
void SpiInterruptReceived(void);

/**
 * Retrieves the last error code.
 * This function is used to retrieve an error code when an error occurs.
 * \return 					Returns an error code of type #SpiErrorCode.
 * \ingroup SPIInterface
 */
SpiErrorCode SpiGetLastError(void);

/**
 * Returns statistics for the SPI interface.
 * This function will provide the caller with statistics for the SPI interface. This is typically
 * a count of the frames transmitted and received, frames lost or in error, etc.
 * \param protocolStatistics	A pointer to a structure of type SpiProtocolStats which holds the statistics.
 * \ingroup SPIInterface
 * \return 						TRUE if successful, FALSE otherwise.
 */
Bool SpiGetProtocolStats(SpiProtocolStats* protocolStatistics);


/**
 * Resets statistics for the SPI interface.
 * Simply sets then all to zero
 * \ingroup SPIInterface
 * \return 						TRUE if successful, FALSE otherwise.
 */
Bool SpiResetProtocolStats(void);


#ifdef __cplusplus
}
#endif

#endif /* _SPI_INTERFACE_H */

/// @endcond
