#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include "TransmissionProtocol.h"
#include "ToPSyncTypes.h"
#include "Socket.h"
#include "SystemConfiguration.h"
#include "NetworkInterfaces.h"

#ifdef _ARC
  #include "MqxInterface.h"
  #include <mutex.h>
#else
  typedef struct { int dummy; } MUTEX_STRUCT;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PRINT_BUFFER_MAGIC 0xcd05cd05

/*
 * Transports for debug messages. This is treated as a bitfield. 
 */
typedef enum
{
	debutTransportNone = 0x0,
	debugTransportUdp =  (1 << 0), /* 0x1 */
	debugTransportUart = (1 << 1)  /* 0x2 */
} DebugPrintTransport;

/*
 * Sources for debug messages. This is treated as a bitfield.
 */
typedef enum
{
	debugSourceNone = 0x0,
	debugSourceGeneral = (1 << 0),  /* 0x1 */
	debugSourcePrintlog = (1 << 1)  /* 0x2 */
} DebugPrintSource;

/*
 * Number of debug sources.
 */
#define DEBUG_SOURCE_CNT 2

/*
 * Severities for debug messages.
 */
typedef enum
{
	debugSeverityNone,
	debugSeverityWarning,
	debugSeverityDebug,
	debugSeverityInfo,
} DebugPrintSeverity;


#define DEGUG_PRINT_FORMAT_ENCRYPTED_TEXT	0x0
#define DEBUG_PRINT_FORMAT_PLAIN_TEXT		0x1

//values for Debug print function
typedef struct
{
	// printlog timeout for UDP transport
	ElapsedTime tickPeriod;
	uint32 ticksToTimeout;
	uint32 ticksToPrint;
	uint32 printPeriodTicks;
	Bool   enabled;
	Bool   printTopLine;

	uint32 numValidRequestsSeen;
	uint32 numInvalidRequestsSeen;

	// Generic debug parameters
	DebugPrintTransport transport;
	DebugPrintSource source;
	DebugPrintSeverity severity[DEBUG_SOURCE_CNT + 1];

	uint32 outputMask;
	uint8  outputFormat;

	// transport specific parameters
	NetworkInterfaceId networkInterfaceId;
	uint32 mHomeIndex;
	uint16 myUdpPort;
	EnhancedTransmissionProtocolAddress destination;
	Bool socketConfigured;
	SocketHandle socketHandle; //udp only
	uint8 activeUART;
    uint8 networkProtocol;	// ipv4 or ipv6

	/* Eventually the entire module should be semaphore protected with it's own semaphore rather than relying
	 * on the big data lock. But for now the semaphore just protects the message buffer. This buffer used to
	 * exist in targetprintf() on the stack, but putting 1KB on the stack can cause stack overflows, as was
	 * found to be the case. Putting it here instead. The reason semaphore protection is added is because not
	 * all tasks use the big data lock, so can't rely on this for concurrency protection any more. */
	MUTEX_STRUCT mutex;
	char printBuffer[MAX_UDPPRINTF_MESSAGE_SIZE + 4u]; /* +4u to put a magic number at end of buffer so we can detect buffer overflows */
} DebugPrintController;

void InitialiseDebugPrintController(
	DebugPrintController* ctl, ElapsedTime tickPeriod);

void DebugPrintControllerTick(DebugPrintController* ctl);

void SetDebugPrintPeriod(DebugPrintController* ctl, ElapsedTime printPeriod);

void EnableDebugPrintSource(DebugPrintController* ctl, DebugPrintSource source, DebugPrintSeverity severity);
void DisableDebugPrintSource(DebugPrintController *ctl, DebugPrintSource source);
#ifdef TS2D_UART_RECEIVE
Bool GetSourceFromStr(char *sourceStr, DebugPrintSource *source);
Bool GetSeverityFromStr(char *severityStr, DebugPrintSeverity *severity);
#endif
const char *GetDebugPrintSeverityStr(DebugPrintSeverity severity);
#ifdef TS2D_UART_RECEIVE
void ShowDebugPrintSources(DebugPrintController *ctl, char *msg, int32 len);
#endif
void OpenDebugPrintPort(DebugPrintController* ctl, DebugPrintTransport transport);
void EnableDebugPrintPort(DebugPrintController* ctl, DebugPrintTransport transport, EnhancedTransmissionProtocolAddress const* sourceAddress);
void DisableDebugPrintPort(DebugPrintController* ctl, DebugPrintTransport transport);

Bool PrintTopLine(DebugPrintController* ctl);
Bool ReadyToPrint(DebugPrintController* ctl);
Bool DebugPrintPossible(DebugPrintController* ctl, DebugPrintSource src, DebugPrintSeverity severity);

void dbgprintf(DebugPrintSource source, DebugPrintSeverity severity, const char * __format, ...);
void dbgprintfdefault(const char * __format, ...);

//Function pointer functions
void MessageReceivedFromSocketDebugPrintController(void* ctl,
		EnhancedTransmissionProtocolAddress const* sourceAddress,
		uint8 const data[], uint16 dataLength);

void TransportServiceStateChangeDebugPrintController(void* ctl, 
		SocketHandle socketHandle, uint16 udpPort); 



#define DebugPrintEnabled(ctl) ((ctl)->enabled)
#define GetDebugPrintPeriod(ctl) ((ctl)->printPeriodTicks * (ctl)->tickPeriod)
#define GetSocketHandle(ctl) ((ctl)->socketHandle) // NO_SOCKET if invalid

#ifdef __cplusplus
}
#endif

#endif
