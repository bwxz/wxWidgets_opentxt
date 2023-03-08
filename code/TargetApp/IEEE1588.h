#ifndef IEEE1588_H
#define IEEE1588_H

#include "General.h"
#include "ToPSyncTypes.h"
#include "IEEE1588InterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


// System constants

#define PTP_V1_UUID_LENGTH ETHERNET_ADDRESS_BYTES

#define PTP_CODE_STRING_LENGTH		4
#define PTP_V1_SUBDOMAIN_NAME_LENGTH 16
#define PTP_V1_SUBDOMAIN_STRING_LENGTH (PTP_V1_SUBDOMAIN_NAME_LENGTH+1)
#define PTP_MAX_MANAGEMENT_PAYLOAD_SIZE 90
#define PTP_FOREIGN_MASTER_THRESHOLD 2

// UDP port numbers
#define EVENT_PORT_NUMBER 			319
#define GENERAL_PORT_NUMBER 		320

#define DEFAULT_PRIORITY			128
#define MIN_PRIORITY				255

#define V2_LOG_VARIANCE_OFFSET		0x8000
#define V2_LOG_VARIANCE_UNKNOWN		0x7FFF


// Ethertype
#define ETHERTYPE_PTP 0x88F7

#define MIN_PTP_VERSION				1
#define MAX_PTP_VERSION				2
#define NUMBER_OF_PTP_VERSIONS		(MAX_PTP_VERSION + 1 - MIN_PTP_VERSION)

typedef enum {
	PTP_CLOSED = 0,
	PTP_ETHER  = 1,
	PTP_FFBUS  = 4,
	PTP_PROFIBUS  = 5,
	PTP_LON = 6,
	PTP_DNET = 7,  // DeviceNet
	PTP_SDS = 8,
	PTP_CONTROLNET = 9,
	PTP_CANOPEN = 10,
	PTP_IEEE1394 = 243,
	PTP_IEEE802_11A = 244,
	PTP_IEEE_WIRELESS = 245,
	PTP_INFINIBAND = 246,
	PTP_BLUETOOTH = 247,
	PTP_IEEE802_15_1 = 248,
	PTP_IEEE1451_3 = 249,
	PTP_IEEE1451_5 = 250,
	PTP_USB = 251,
	PTP_ISA = 252,
	PTP_PCI = 253,
	PTP_VXI = 254,
	PTP_DEFAULT = 255
} CommunicationTechnology;


#define V1_CLOCK_ID_SIZE	4
// WARNING code will have to change if length of following Ids is less than 3
#define V1_ATOM_CLOCK_ID "ATOM"
#define V1_GPS_CLOCK_ID "GPS"
#define V1_NTP_CLOCK_ID "NTP"
#define V1_HAND_CLOCK_ID "HAND"
#define V1_INIT_CLOCK_ID "INIT"
#define V1_DFLT_CLOCK_ID "DFLT"

#define IEEE1588_FOREIGN_MASTER_SYNC_MESSAGE_MULTIPLE 4
	// number of foreign master sync messages is measured over 4 sync periods (PTP_FOREIGN_MASTER_TIME_WINDOW)
#define IEEE1588_MIN_NUMBER_OF_FOREIGN_MASTER_SYNC_MESSAGES 2
	// min number of foreign master messages received during during PTP_FOREIGN_MASTER_TIME_WINDOW
	// for the master to remain recognised (PTP_FOREIGN_MASTER_THRESHOLD)

#define IEEE1588_PTP_ANNOUNCE_RECEIPT_TIMEOUT 3 //SMPTE default is 3
	// Number of sync periods to wait in listening start.  Should be 10 but this is too long

#define IEEE1588_VISIBLE_MASTER_MISSING_ANNOUNCE_MESSAGES 5
	// number of missing messages before a port decides master is no longer reachable (PTP_SYNC_INTERVAL_TIMEOUT)
	// should be 10 but this is way too long

#define PTP_LOG_VARIANCE_THRESHOLD 256U
#define MIN_PTP_PORT_ID 1


#define UnknownIEEE1588Domain 0xFFFF


NodeId CreateNodeIdFromMACAddress(EthernetAddress const address);

Bool PortIdsEqual(PortId const* left, PortId const* right);
Bool PortIdsEqualWithPortAsWildcard(PortId const* left, PortId const* right);
Bool ValidPortId(PortId const* id);
#define NullPortId(id) (!ValidPortId(id))
void SetPortIdToNull(PortId* id);

Bool NodeIdsEqual(NodeId const* left, NodeId const* right);
Bool ValidNodeId(NodeId const* id);
#define NullNodeId(id) (!ValidNodeId(id))
void SetNodeIdToNull(NodeId* id);

Bool LeftPortIdLessThanRight(PortId const* left, PortId const* right);


#define ReferenceClockIsExternal(ref) ((ref)->timeTransport != noTimeTransport \
	&& (ref)->timeTransport != generatedLocally)


typedef struct
{
	enum  {neitherB, leftB, rightB}				better;
	enum  {noReason, byQuality, byTopology, byTieBreak} reason;

} ReferenceClockComparison;

ReferenceClockComparison IsLeftReferenceBetterThanRight(
		PortId const* leftOwnPort, PortId const* leftRemotePort, ReferenceClock const* leftReference,
		PortId const* rightOwnPort,PortId const* rightRemotePort,ReferenceClock const* rightReference,
		BMCABitMask const bitmask);

ReferenceClockComparison IsLeftReferenceBetterByQualityThanRight(
		ReferenceClock const* leftReference,
		ReferenceClock const* rightReference,
		BMCABitMask const bitmask);

void SetReferenceClockToDefaultValue(ReferenceClock* reference);


#ifdef __cplusplus

bool ConvertTextToClockQuality(char const text[], ClockQuality& clockQuality);
// returns true if the text contained correct information

#endif


#ifdef __cplusplus
}
#endif

#endif
