#ifndef PTP_MESSAGE_RECEIVER_H
#define PTP_MESSAGE_RECEIVER_H

#include "PtpPort.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ARC
extern uint16 ptpEthertype;
#define PtpEthertype() (ptpEthertype)
#else
uint16 PtpEthertype(); //to avoid globals in the simulator
#endif

typedef struct
{
	NodeId				sourceNodeId[NUMBER_OF_PTP_PORTS];	   // external node id
	uint8				sourcePortNumber[NUMBER_OF_PTP_PORTS]; // external port number
	IEEE1588Time		portTime[NUMBER_OF_PTP_PORTS];
	uint32				changeCount[NUMBER_OF_PTP_PORTS];
	uint8				connector[NUMBER_OF_PTP_PORTS];
	ClockId				pathDelayClockId;
	IEEE1588Time		pathDelayTime;
} PtpMessageReceiver;

void InitialisePtpMessageReceiver(void);
void PtpMessageReceiverSlowTick(void);
void SetPtpEthertype(uint16 ethertype);  // ethertype to be used for PTP/Ethernet receiption
void PtpMessageReceiverSetPathDelayClockId(ClockId PathDelayClockId);
void PtpMessageReceived(PCB_PTR pcbPtr, unsigned long int receiveTimeNanoseconds,
		unsigned char const* payloadStart, unsigned char interfaceNumber, unsigned long virtualPortNumber);

#ifdef __cplusplus
}
#endif
#endif
