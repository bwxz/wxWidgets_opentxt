#ifndef DELAYMESSAGEHANDLER_H
#define DELAYMESSAGEHANDLER_H

#include "General.h"
#include "IEEE1588Time.h"
#include "PtpPort.h"
#include "TwoLevelAddress.h"

#define MAX_DELAY_MESSAGE_SIZE	42

typedef struct
{
	MESSAGE_HEADER_STRUCT			header;
	ExternalInterfaceType           sourceInterface;
	uint8							data[MAX_DELAY_MESSAGE_SIZE];
} ToPSyncDelayMessage;

/* Called from SPI interface when delay message has been received*/
void DelayMessageReceived(ExternalInterfaceType sourceInterface, uint8 const* messageData, uint32 messageLength);

/* Called on system startup to create message queue for Delay Message */
void InitialiseDelayMessageHandler(void);

/* Opens receive queue for delay messages */
void StartDelayMessageReceiver(void);

/* Called from delay message processing thread
 * Returns TRUE if message processed
 *         FALSE if queue was empty
 */
Bool DelayMessageHandler(void);

#endif /* DELAYMESSAGEHANDLER_H */
