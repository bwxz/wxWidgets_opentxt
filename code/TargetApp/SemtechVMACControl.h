#ifndef SEMTECH_VMAC_CONTROL_H
#define SEMTECH_VMAC_CONTROL_H

#include "MqxInterface.h"
#include "NetworkInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

// These functions are defined in eninit.c, which is part of MQX

void SetMessageReceivedStackBypassFunctionPointer(
	void (*newPointer) (PCB_PTR pcbPtr,
		unsigned long int receiveTimeNanoseconds,
		unsigned char const* payloadStart,
		unsigned char portNumber,
		unsigned long virtualPortNumber));

void SetDelayRequestMessageReceivedStackBypassFunctionPointer(
	void (*newPointer) (PCB_PTR pcbPtr, 
		unsigned long int receiveTimeNanoseconds,
		unsigned char* payloadStart,
		unsigned char portNumber,
		unsigned long virtualPortNumber));

void SetStackBypassEthertype(unsigned short int ethertype);
void SetUDPTimestampedPort(unsigned short int port);
void SetUDPStackBypassPort(unsigned short int port);

void SetGetVirtualPortIdForInterfaceFunctionPointer(
	unsigned char (*newPointer) (void *interfaceHandle, unsigned *vlanPortId));

//****************************************************/
/* Overload control */

/****************************************************/
/* 
	Two methods of defining the maximum acceptable rate for overload control
	are used in this file
	
	It is not possible to use a mixture of the two methods
	
	1.  The method used in 4.9.7 and before.  This calls 
	SetPacketCreditLimits(unsigned char event1588, 
	signed creditMax, signed creditIncrement) to set the acceptable 
	rate for 1588 event packets (event1588 is true) or for all other
	packet types (event1588 is false).  The function sets the maximum
	number of 'credits' that can be accumulated ('creditMax') and the 
	amount by which each call to PacketCreditTick() increments the number 
	of credits.  
	
	The credit system works by decrementing each a counter each time a 
	packet is received.  If the counter reaches zero, packet reception is
	disabled.  
	
	2.	This method uses SetPacketCreditLimit(unsigned creditMax) to set 
	the number of packets that may be received between calls to 
	PacketCreditReset().  This allows a low priority task to repeatedly 
	call PacketCreditReset().  If the processor is overloaded, the task 
	will not run and packet reception will be disabled.
	
	Common API
	void InitialisePacketReceiveControlPtr(void (*enableEthernetReceipt) (unsigned char portNumber,
																		  unsigned char enable));
	//Sets the command that the OS will call to enable or disable packet reception

	Method 1
	void PacketCreditTick(void);  // The packet credits must in incremented

	
	Method 2	
	void PacketCreditReset(void);	
	//The number of packets that may be received is returned to 
	void SetPacketCreditLimit(unsigned limit); 
	// if InitialisePacketReceiveControlPtr has been called, only 'limit' 
	Ethernet packets will be received before	PacketCreditReset() is called 

*/

//Common Functions
void InitialisePacketReceiveControlPtr(void (*enableEthernetReceipt) (unsigned char portNumber, unsigned char enable));

//Method 1
void SetPacketCreditLimits(unsigned char event1588, signed creditMax, signed creditIncrement);
void ChangePacketCreditRate(unsigned char event1588, signed creditMax, signed creditIncrement);
void PacketCreditTick(void);

//Method 2
void SetPacketCreditLimit(uint8 portNumber, unsigned limit);
	/* if InitialisePacketReceiveControlPtr has been called, only limit Ethernet packets will be received before
		PacketCreditReset() is called 
	*/
void PacketCreditReset(uint8 portNumber);

//for DoS
unsigned char IsPacketReceiptEnabled();
uint32 GetNumberOfDoSIncidents();

//****************************************************/


#ifdef __cplusplus
}
#endif

#endif
