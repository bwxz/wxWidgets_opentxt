#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <mqx.h>
#include <bsp.h>
#include <enet.h>
#include <timer.h>
#include <mutex.h>
#include <lwevent.h>

#include "General.h"
#include "TopSyncTypes.h"
#include "TimeServerControl.h"
#include "SocketController.h"
#include "DebugPrintController.h"
#include "EventMessageController.h"
/*   Task Templates  */
extern TASK_TEMPLATE_STRUCT  MQX_template_list[];

/* Task indices */
#define TIME_TASK_INDEX							10
#define EVENT_TASK_INDEX 						11
#define REACT_TO_SOCKET_MESSAGE_TASK_INDEX 		12
#define REACT_TO_STACK_BYPASS_MESSAGE_TASK_INDEX 	13
#define CTRL_MSG_HANDLER_TASK_INDEX				14
#define DELAY_RESP_SEND_TASK_INDEX  			15
#define EVENT_MSG_SEND_TASK_INDEX				16
#define NETWORK_LINK_TASK_INDEX					17
#define IDLE_TASK_INDEX							18
#define IMAGE_UPLOAD_TASK_INDEX					19

#define TIME_EVENT_FUNCTION_STACK 0x400L


extern MUTEX_STRUCT dataMutex; // protects application data

extern LWEVENT_STRUCT eventGroup;
extern _pool_id ctrlMessagePool;
extern _pool_id delayReplacementMessagePool;

extern ControlData controlData;
extern SocketController socketController;
extern DebugPrintController printController;
extern EventMessageController eventMessageController;
extern SoftwareVersion	AppSoftwareVersion;


extern uint32 timerEventCount;
extern uint32 enableClockInterruptsAtTimerEventCount[NUMBER_OF_CLOCK_PLLS]; // interrupts enabled when timerEvent reaches this value

// semaphore defines
#define MESSAGE_SEND_SEMAPHORE_MAX 1

// eventGroup events
#define EVENT_REQUEST_EVENT_PACKET_SEND				0x00000001
#define EVENT_TIMER_TICK							0x00000004
#define EVENT_CLOCKTSA_EDGE_CAPTURE					0x00000008
#define EVENT_CLOCKTSB_EDGE_CAPTURE					0x00000002
#define EVENT_SPI_DATA_RECEIVED			 			0x00000010
#define EVENT_APP_STATE_CHANGE						0x00000020
#define EVENT_DLY_RQ_MESSAGE_RX						0x00000040
#define EVENT_PTP_MESSAGE_RX						0x00000080
#define EVENT_MMM_POSTED_READ_COMPLETE				0x00000100
#define EVENT_DLY_REPLACEMENT_MSG_RX				0x00000200
#define EVENT_NODE_TIME1_PPS						0x00000400
#define EVENT_NODE_TIME2_PPS						0x00000800
#define EVENT_PACKET_SEND_NETTSA_PORT0_COMPLETE	 	0x00001000
#define EVENT_PACKET_SEND_NETTSA_PORT1_COMPLETE	 	0x00002000
#define EVENT_PACKET_SEND_NETTSB_PORT0_COMPLETE	 	0x00004000
#define EVENT_PACKET_SEND_NETTSB_PORT1_COMPLETE	 	0x00008000
#define EVENT_PACKET_SEND_NETTSC_PORT0_COMPLETE		0x00010000
#define EVENT_PACKET_SEND_NETTSC_PORT1_COMPLETE		0x00020000
#define EVENT_PACKET_SEND_NETTSD_PORT0_COMPLETE		0x00040000
#define EVENT_PACKET_SEND_NETTSD_PORT1_COMPLETE		0x00080000

// Tasks
void CreateTask (uint index, uint32 parameter);
void MainTask (uint_32   InitialisationDataPtr);
void ReactToSocketMessageTask (uint_32   parameter);
void ReactToStackBypassMessageTask (uint_32   parameter);
void TimeControlledTask (uint_32   parameter);
void EventTask (uint_32   parameter);
void ControlMessageHandlerTask(uint_32 parameter);
void DelayResponseMessageSendTask(uint_32 parameter);
void EventMessageTransmitTask(uint_32 parameter);
#ifdef TS2D_ASIC
void NetworkLinkTask(uint_32 parameter);
#endif
void IdleTask(uint_32 parameter);			// idle task must NEVER suspend
void LCDTickTask(uint_32 parameter);

/* Task stack size */
#define EVENT_TASK_STACK 							0x1000L
#define REACT_TO_SOCKET_MESSAGE_TASK_STACK			0x1000L
#define REACT_TO_STACK_BYPASS_MESSAGE_TASK_STACK 	0x1000L
#define TIME_TASK_STACK								0x1000L
#define CTRL_MSG_HANDLER_TASK_STACK					0x1000L
#define DELAY_RESP_SEND_TASK_STACK					0x800L
#define EVENT_MSG_SEND_TASK_STACK					0x800L
#define NETWORK_LINK_TASK_STACK						0x800L
#define IDLE_TASK_STACK 							0x400L
#define RTCS_STACK_SIZE 							0x800L
#define IMAGE_UPLOAD_TASK_STACK						0x1000L

/* Task priorities.  Low number = high priority */
#define TIME_EVENT_TASK_PRIORITY					11L
#define EVENT_TASK_PRIORITY							12L
#define TIME_TASK_PRIORITY							13L
#define EVENT_MSG_SEND_TASK_PRIORITY				14L
/* This should not be lower priority than REACT_TO_MESSAGE_TASK_PRIORITY
   or CTRL_MSG_RECEIVE_TASK_PRIORITY */
#define CTRL_MSG_HANDLER_TASK_PRIORITY				15L

#define INITIALISATION_TASK_PRIORITY				16L
#define REACT_TO_SOCKET_MESSAGE_TASK_PRIORITY		17L
#define REACT_TO_STACK_BYPASS_MESSAGE_TASK_PRIORITY	17L

#define DELAY_RESP_SEND_TASK_PRIORITY				18L
#define NETWORK_LINK_TASK_PRIORITY					19L
#define IMAGE_UPLOAD_TASK_PRIORITY					20L
#define IDLE_TASK_PRIORITY							21L		//must be lower than any other task


/* TopSync Control Driver message definitions */
#define MAX_CONTROL_MSG_SIZE			MAX_MESSAGE_SIZE
#define MAX_NUMBER_OF_CTRL_MESSAGES 	2
#define QUEUE_FOR_CTRL_MSGS   			MSGQ_FIRST_USER_QUEUE

/* TopSync Delay Replacement message definitions */
#define MAX_NUMBER_OF_DELAY_REPLACEMENT_MESSAGES 	8
#define QUEUE_FOR_DELAY_REPLACEMENT_MSGS   			(QUEUE_FOR_CTRL_MSGS + 1)

/* Range limits for boot checksum */
#define BOOT_CRC_CHECK_START	0x011E0000
#define BOOT_CRC_CHECK_END		0x011FFFFC

typedef struct
{
	MESSAGE_HEADER_STRUCT			header;
	uint8							data[MAX_CONTROL_MSG_SIZE];
	uint32							length;
	ExternalInterface				sourceInterface;
	EnhancedTransmissionProtocolAddress		sourceAddress;
} ControlMessage;

typedef struct
{
	uint32 taskHasRunMask;		//1
	uint32 ticksSinceReset;		//2
} WatchdogResetDataStruct;

extern _Uncached uint32 resetDataMagicNumber;
extern _Uncached uint32 resetDataResetCount;
extern _Uncached WatchdogResetDataStruct currentResetData;
extern _Uncached WatchdogResetDataStruct previousResetData;

#define CRASH_DATA_MAGIC_NUMBER 0xFAF5A145

#endif

