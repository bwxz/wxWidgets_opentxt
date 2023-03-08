/*
Copyright ?2007 Semtech Corporation, P.O. Box 6097, Camarillo,
CA 93011-6097 U.S.A.

All rights reserved. The copyright of the content of this file is owned
by Semtech Corporation (Semtech).

This is an unpublished work.  The content of this file must be used only
for the purpose for which it was supplied by Semtech or its distributors.
The content of this file must not be copied or disclosed unless authorised in
writing by Semtech.

Name		$Workfile: ToPSyncInterfaceTypes.h $
Version     $Revision: 50 $
Date		$Date: 23/06/09 10:46 $
*/

/**
  * \file ToPSyncInterfaceTypes.h
  *	Public types used by the ToPSync Control Driver.
  */
#ifndef TOP_SYNC_INTERFACE_TYPES_H
#define TOP_SYNC_INTERFACE_TYPES_H

#include "General.h"
#include "TransmissionProtocol.h"
#include "IEEE1588InterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NUMBER_OF_PHYSICAL_PORTS
	#if NUMBER_OF_PHYSICAL_PORTS != 2
		#error _NUMBER_OF_PHYSICAL_PORTS must be 2
	#endif
#else
	#define NUMBER_OF_PHYSICAL_PORTS 2
#endif

#define NUMBER_OF_VIRTUAL_PORTS 6
#define NUMBER_OF_IP_ADDRESSES_PER_INTERFACE 16

#ifdef ARC_DEBUG  // ARC_DEBUG is defined because SeeCode debug does not show correct double values
	#define DOUBLE_TYPE float
#else
	#define DOUBLE_TYPE double
#endif

typedef DOUBLE_TYPE Frequency;	// Hz or proportion
typedef DOUBLE_TYPE Signal;
typedef DOUBLE_TYPE ElapsedTime;  // in seconds

/**
  *	The telecomms hierarchy.
  */
typedef enum
{
	ansi,	/**< ANSI telecomms hierarchy */
	etsi	/**< ETSI telecomms hierarchy */
}TelecomsHierarchy;

/**
  *	The directions of timing information.
  */
typedef enum
{
	both,	/**< Timing information from both directions. This is the default. */
	m2s,	/**< Timing information from master to slave direction. */
	s2m		/**< Timing information from slave to master direction. */
} Direction;

/**
  *	The time transport. Order is important - higher values are better
  */
typedef enum
{
	noTimeTransport,	/**< Null */
	generatedLocally,	/**< Local oscillator with no external reference */
	viaPacketNetwork,	/**< Via a packet network */
	viaWire,			/**< Via a clock input */
	hybridSource		/**< Frequency is from a wired input, time via a packet network */
} TimeTransport;

/**
  *	The 1588 message type. MessageType is not the transmitted message type
  */
//
typedef enum
{
	announceMsg, syncMsg, delayRequestMsg, followUpMsg, delayResponseMsg, signallingMsg,

	pathDelayRequestMsg, pathDelayMessageMin = pathDelayRequestMsg, pathDelayResponseMsg, pathDelayFollowUpMsg,
	managementMsg, unknownMessageType,
	numberOfMessageTypes = unknownMessageType,
} MessageType;


typedef enum
{
	ACS1790Master, /**< The addressed device is the master at address 0xC0 (b?110 000x) */
	ACS1790Slave   /**< The addressed device is the slave at address 0xC2 (b?110 001x) */
} ACS1790Address;

/**
  *	Configuration operation result codes.  Each configuration request will result in a response, indicating whether
  * the operation succeeded, and if not, the reason for the failure.
  */
typedef enum
{
	TOPSYNC_CNFG_SUCCESS,					/**< The operation succeeded. */
	TOPSYNC_CNFG_FAIL,						/**< The operation failed for an unspecified reason. */
	TOPSYNC_CNFG_EXCEPTION,					/**< The operation failed because an exception occurred. */
	TOPSYNC_CNFG_OUT_OF_RANGE,				/**< The operation failed because one or more of the parameters is out of range. */
	TOPSYNC_CNFG_ALREADY_EXISTS,			/**< The operation failed because the entity already exists or its Id is already allocated. */
	TOPSYNC_CNFG_DOES_NOT_EXIST,			/**< The operation failed because one or more entities required to perform configuration do not exist. */
	TOPSYNC_CNFG_TOPSYNC_DOES_NOT_EXIST,	/**< The ToPSync does not exist or is not communicating. */
	TOPSYNC_CNFG_CONFIGURED_ENTITIES_EXIST,	/**< The operation failed because one or more entities must be removed first. */
	TOPSYNC_CNFG_INCOMPATIBLE_MODE,			/**< The operation failed because the operation was not compatible with the current mode. */
	TOPSYNC_CNFG_INVALID_FREQUENCY,			/**< The operation failed because the frequency is not permitted with this operation. */
	TOPSYNC_CNFG_NOT_IMPLEMENTED,			/**< The operation is not implemented in this context. */
    TOPSYNC_CNFG_INVALID_SYSTEM_STATE,      /**< The operation failed because it is not permitted in the current system state */
    TOPSYNC_CNFG_INVALID_REQUEST,           /**< The operation failed because the request is not supported by this ToPSync part. */
    TOPSYNC_CNFG_INVALID_PARAMETER,         /**< The operation failed because of an invalid parameter in the request.*/
	TOPSYNC_CNFG_INVALID_SECURITY_KEY,      /**< The operation failed because of an invalid security key.*/
	TOPSYNC_CNFG_NO_MAC_ADDRESS,			/**< The mac address does not exist.*/

	/* Following result codes are for mmAPI
	 * todo: Since we are assigning new message setId we can take the opportunity to tidy up the above - remove
	 * redundant result codes, and replace ambiguous ones with something more meaningful
	 */
	TOPSYNC_CNFG_INVALID_MSG_SET,			/**< The message set is not valid.*/
	TOPSYNC_CNFG_READONLY_PARAMETER,        /**< The write failed because the parameter is read only. */
	TOPSYNC_CNFG_BUSY,						/**< A previous operation has not yet completed */
	/* Following for AVCS1790 */
	TOPSYNC_CNFG_IP_CLK_ALREADY_IN_USE
}ToPSyncConfigResult;


/**
  *	The maximum number of permitted MAC addresses
  */
#define MAX_PERMITTED_MAC_ADDRESSES 10

/**
  *	The permitted Mac Addresses array
  */
typedef EthernetAddress PermittedMacAddresses[MAX_PERMITTED_MAC_ADDRESSES];


/**
  *	The ToPSync Ethernet link speeds/modes.	Must start at zero.
  */
typedef enum
{
	HUNDRED_BASE_T_FULL_DUPLEX, /**< 100 Base-T Full Duplex. */
	HUNDRED_BASE_T_HALF_DUPLEX, /**< 100 Base-T Half Duplex. */
	TEN_BASE_T_FULL_DUPLEX,		/**< 10 Base-T Full Duplex. */
	TEN_BASE_T_HALF_DUPLEX,		/**< 10 Base-T Half Duplex. */
	ALLOW_AUTONEGOTIATON		/**< Autonegotiation. */
}LinkSpeedDuplexMode;

/**
  *	The supported oscillator technologies. Must start at zero.
  */
typedef enum
{
	CMAC_2270_STRATUM_3E_OCXO,	/**< CMAC 2270 OCXO */
	CMAC_2208_STRATUM_3E_OCXO,	/**< CMAC 2208 OCXO */
	CMAC_2747_STRATUM_3_TCXO,	/**< CMAC 2747 TCXO */
	CMAC_4190_STRATUM_3_TCXO,	/**< CMAC 4190 TCXO */
	CMAC_4191_SMC_TCXO,			/**< CMAC 4191 TCXO */
	CMAC_4968_FEMTOCELL_TCXO,	/**< Femtocell TCXO */
	DEFAULT_OCXO,				/**< Default OCXO */
	DEFAULT_TCXO,				/**< Default TCXO */
	DEFAULT_OC_TCXO,			/**< Default OC TCXO */
	NUMBER_OF_LOCAL_OSCILLATOR_TYPES
}LocalOscillatorType;

/**
  *	The PTP port state.
  */
typedef enum
{
	/**
	  *	A port in this state is considered inactive. No activity on this port shall affect the
	  * active ports of the boundary clock or of any other port in the subdomain.
	  * If fault activity on a port in this state cannot be confined to the port, then all ports
	  * shall be in this state.
      */
	portFaulty,

	/**
	  *	A port in this state is considered inactive. No activity on this port shall affect the active
	  * ports of the boundary clock or of any other port in the subdomain.
      */
	portDisabled,

	/**
	  *	Any or all ports may be in this state.
      */
	portListening,

	/**
	  *	Same as for PTP_MASTER, except that the port shall not place any non-management
	  * messages on its associated communication path.
      */
	portPreMaster,

	/**
	  *	If one port is in this state either:
	  * No active port is in the PTP_SLAVE state and the boundary clock is also the
	  * grandmaster clock of the subdomain for all communication paths for which
	  * the boundary clock communicates via a port in the PTP_MASTER state,
	  * \n or
	  * \n One active port is in the PTP_SLAVE state and the grandmaster clock of the
	  * subdomain is a clock communicating with the boundary clock directly or
	  * indirectly via the slave port. The boundary clock will be the master (but not
	  * the grandmaster) for all communication paths for which the boundary clock
	  * communicates via a port in the PTP_MASTER state.
      */
	portMaster,

	/**
	  *	Any or all ports may be in this state.
      */
	portPassive,

	/**
	  *	Any port may be in this state.
      */
	portUncalibrated,

	/**
	  *	Slave.
      */
	portSlave,

	numberOfPortStates
} PTPPortState;


#define DO_NOT_USE_CONFIGURED_PRIORITY 0
/* The value of priority assigned to a visible master is set
in AcceptableMasterController.  If the value is set to DO_NOT_USE_CONFIGURED_PRIORITY
the value received in the announce message will be used instead
*/

#define MAXIMUM_PHASE_NOISE_PAIRS 10 /**< The maximum supported number of phase-noise pairs */

/**
  *	Structure defining a single phase noise pair.
  */
typedef struct
{
	uint16 spotFrequencyHz;	/**< The spot frequency */
	sint16 phaseNoise;		/**< The phase noise */
}LocalOscillatorPhaseNoiseValue;

/**
  *	List of phase-noise values.
  */
typedef LocalOscillatorPhaseNoiseValue PhaseNoisePairs[MAXIMUM_PHASE_NOISE_PAIRS];

/**
  *	The maximum number of external (network) interfaces the system can support.
  */

/**
  *	Parameters relating to configuration of IP-over-Ethernet interface
  */
typedef struct
{
	Bool configured;					/**< Flag indicating whether the IP packet interface is configured. */
	uint32 	useDHCP;					/**< DHCP used to get IP addressing if non-zero */
	uint32  dhcpLeasePeriodRequested;	/**< DHCP lease period if DHCP used */
	uint32 	ipAddress;					/**< IP address configured manually or obtained by DHCP */
	uint32 	subnetMask;					/**< Subnet mask configured manually or obtained by DHCP */
	uint32  defaultGateway;				/**< Default gateway configured manually or obtained by DHCP */
}IpPacketInterfaceConfiguration;


/**
  *	Parameters relating to configuration of Boot IP Config
  */
typedef struct
{
//	EthernetAddress macAddress;					/**< The MAC Address */
	uint32 			useDHCP;					/**< DHCP used to get IP addressing if non-zero */
	uint32			dhcpLeasePeriodRequested;	/**< DHCP lease period if DHCP used */
	uint32 			ipAddress;					/**< IP address configured manually or obtained by DHCP*/
	uint32 			subnetMask;					/**< Subnet mask configured manually or obtained by DHCP*/
	uint32			defaultGateway;				/**< Default gateway configured manually or obtained by DHCP*/
}IpBootConfiguration;

#ifndef IPV6_ADDRESS_BYTES
#define IPV6_ADDRESS_BYTES	16
#endif

/*
 * SGMII Mode to indicate whether the port is configured as a PHY or a MAC.
 */
typedef enum
{
	SGMII_MODE_MAC,
	SGMII_MODE_PHY,
} SgmiiMode;

/**
 * Configurable Plug n Play network interface SGMII configuration bit fields
 * to allow network interface to be configured as MII or SGMII MAC/PHY.
 * The first bit shadows SgmiiMode and is kept for backwards compatability with
 * applications that do not support MII.
 *
 *  Bit 0 - network interface SGMII MAC/PHY mode
 * 	Bit 1 - network interface MII/SGMII mode
 */
#define PNP_SGMII_CONFIGURATION_PHY_BIT	(0x1 << 0)		/* 0 = MAC, 1 = PHY */
#define PNP_SGMII_CONFIGURATION_MII_BIT	(0x1 << 1)		/* 0 = SGMII, 1 = MII */

/**
 * Active physical port configuration
 */
typedef enum
{
	PHYSICAL_PORT_ACTIVE_DISABLED,
	PHYSICAL_PORT_ACTIVE_ENABLED
} PhysicalPortActiveConfig;


/**
  *	Parameters relating to configuration of Direct Ethernet interface
  */
typedef struct
{
	Bool configured;					/**< Flag indicating whether the Ethernet packet interface is configured. */
}EthernetPacketInterfaceConfiguration;

/**
  *	Statistics collected for an Ethernet interface.
  */
typedef struct
{
	uint32 receivedPackets;				/**< The number of received packets */
	uint32 receivedMissedPackets;		/**< Discarded - no free buffers available */
	uint32 receivedDiscardedPackets;	/**< Discarded -- unrecognized protocol */
	uint32 receivedErroredPackets;		/**< Discarded -- error during reception */
	uint32 receivedCrcErrors;			/**< CRC error */
	uint32 transmittedTotalPackets;		/**< The total number of packets transmitted.*/
	uint32 transmittedMissedPackets;	/**< Discarded -- transmit ring full */
	uint32 transmittedDiscardedPackets;	/**< Discarded -- bad packet */
	uint32 transmittedErroredPackets;	/**< Error during transmission  */
} EthernetInterfaceStatistics;

/**
  *	Statistics collected for an IP over Ethernet interface.
  */
typedef struct
{
	uint32 receivedPackets;				/**< The number of received packets */
	uint32 receivedMissedPackets;		/**< Discarded - no free buffers available*/
	uint32 receivedDiscardedPackets;	/**< Discarded -- unrecognized protocol */
	uint32 receivedErroredPackets;		/**< Discarded -- error during reception */
	uint32 transmittedTotalPackets;		/**< The total number of packets transmitted.*/
	uint32 transmittedMissedPackets;	/**< Discarded -- transmit ring full */
	uint32 transmittedDiscardedPackets;	/**< Discarded -- bad packet */
	uint32 transmittedErroredPackets;	/**< Error during transmission */
	uint32 receivedMulticastPackets;	/**< The number of multicast packets received */
	uint32 receivedBroadcastPackets;	/**< The number of broadcast packets received */
	uint32 transmittedMulticastPackets;	/**< The number of multicast packets transmitted */
	uint32 transmittedBroadcastPackets;	/**< The number of broadcast packets transmitted */
} IpPacketInterfaceStatistics;

/**
  *	Statistics collected for an Direct Ethernet Packet interface.
  */
typedef struct
{
	uint32 receivedPackets;					/**< The number of received packets */
	uint32 receivedMissedPackets;			/**< Discarded - no free buffers available */
	uint32 receivedDiscardedPackets;		/**< Discarded -- unrecognized protocol */
	uint32 receivedErroredPackets;			/**< Discarded -- error during reception*/
	uint32 transmittedTotalPackets;			/**< The total number of packets transmitted.*/
	uint32 transmittedMissedPackets;		/**< Discarded -- transmit ring full*/
	uint32 transmittedDiscardedPackets;		/**< Discarded -- bad packet */
	uint32 transmittedErroredPackets;		/**< Error during transmission */
} EthernetPacketInterfaceStatistics;

/**
  *	Statistics collected for the UDP Layer.
  */
typedef struct
{
	uint32 receivedPackets;					/**< The number of received packets */
	uint32 receivedMissedPackets;			/**< Discarded - no free buffers available */
	uint32 receivedDiscardedPackets;		/**< Discarded -- unrecognized protocol */
	uint32 receivedErroredPackets;			/**< Discarded -- error during reception*/
	uint32 receivedCrcErrors;				/**< CRC error */
	uint32 transmittedTotalPackets;			/**< The total number of packets transmitted.*/
	uint32 transmittedMissedPackets;		/**< Discarded -- transmit ring full */
	uint32 transmittedDiscardedPackets;		/**< Discarded -- bad packet */
	uint32 transmittedErroredPackets;		/**< Error during transmission */
} UDPLayerStatistics;



/**
 * Statistics collected for the SPI interface.
 */
typedef struct
{
	uint	framesTransmitted;		/**< Number of frames transmitted. */
	uint	framesTransmittedError;	/**< Number of frames NOT transmitted due to an internal error. */
	uint	framesReceived;			/**< Number of frames received. */
	uint	framesReceivedError;	/**< Number of frames received in error. */
} SpiInterfaceStatistics;



#define RESET_ETHERNET_STATISTICS_MASK			0x1 /**< Reset Ethernet interface packet statistics */
#define RESET_IP_STATISTICS_MASK				0x2	/**< Reset IP interface packet statistics */
#define RESET_DIRECT_ETHERNET_STATISTICS_MASK	0x4	/**< Reset Direct Ethernet interface packet statistics */
typedef uint8 ResetStatisticsMask;					/**< Reset interface packet statistics mask */

/**
  *	Structure uniquely defining/identifying a PTP port.
  */
typedef struct
{
	uint8 portNumber;						/**< The unique PTP port number */
	uint8 connector;						/**< The physical port (zero is always the first) */
	uint32 virtualInterfaceNumber;			/**< The virtual interface number */
	uint32 mHomeIndex;						/**< The multiHome index */
	/**
	 *	The transport protocol, either UDP over IP over Ethernet or directly over Ethernet.
	 */
	TransmissionProtocol protocol;
	IEEE1588Version ptpVersion;					/**< The PTP protocol version */
	uint8 ptpDomain;						/**< The PTP domain */
}PtpPortConfiguration;



/**
  *	PtpPort Transmission Addressing mode
  */
typedef enum {
	/**
	  * PTP messages transmitted to a single node are sent to that node's address. Messages transmitted to more than
	  * one node (e.g. Announce messages) are addressed to the multicast address configured (in the Network Protocol Interface).
	  * This is the default addressing mode of ToPSync.
	  */
	asAppropriate,

	/**
	  * PTP messages sent to a single node are addressed to that node (unicast). No messages are sent to more than one node.
	  */
	unicastOnly,


	/**
	  * All PTP messages are addressed to the configured multicast address. A node receiving a multicast PTP message will
	  * determine whether the message is addressed to it by examining information contained in the payload.
	  */
	multicastOnly
} PtpPortTransmissionAddressing;


/**
  * Boundary Clock enhancement message transmitting rate. The actual message transmission per second will be:
  * PacketRequest Message Per Second/2**BcTxRate
  * This means the smaller the value of BcTxRate, the higher the message transmission rate.
  */
typedef enum
{
		bcTxRateModMin = 0,
		bcTxRateMod1 = bcTxRateModMin,
		bcTxRateMod2,
		bcTxRateMod4,
		bcTxRateMod8,
		bcTxRateMod16,
		bcTxRateMod32,
		bcTxRateMod64,
		bcTxRateMod128,
		bcTxRateModMax = bcTxRateMod128
} BcTxRate;



/**
  *	Message count type.
  */
typedef struct
{
	uint32 unicast;
	uint32 multicast;
} MessageCount;

/**
  *	Statistics relating to a Visible Master.
  */
typedef struct
{
	MessageCount announce;			/**< Number of received  announce messages */
	MessageCount sync;				/**< Number of received sync messages */
	MessageCount delayResponse;		/**< Number of received delay response sync messages */
	MessageCount delayRequest;		/**< Number of transmitted delay request messages */
	MessageCount followUp;			/**< Number of received follow up messages */
}VisibleMasterStatistics;


/**
 * \brief
 */
typedef struct
{
	struct
	{
		uint32 numValid;
		uint32 numInvalid;
	} T1, T2, T3, T4;
} ExtendedVisibleMasterStatistics;

typedef struct
{
	uint32 numReceived;
	uint32 numInvalid;
	uint32 numInvalidTimestampFormat;
	uint32 numInvalidMinorMode;
	uint32 numInvalidMajorMode;
} DRMMsgTypeStatistics;

/**
 * \brief
 */
typedef struct
{
	uint32 numReceived; // Numer received
	uint32 numDropped; // Number dropped due to lack of queue space, no CM, port invalid etc..
	uint32 numInvalidPtpPortNumber;
	uint32 numSourceSelected;
	uint32 numSourceDeselected;               /*< 20 bytes */

	DRMMsgTypeStatistics  t1Replacement;      /*< 40 bytes */
	DRMMsgTypeStatistics  t2Replacement;      /*< 60 bytes */
	DRMMsgTypeStatistics  t3Replacement;      /*< 80 bytes */
	DRMMsgTypeStatistics  t4Replacement;      /*< 100 bytes */
	DRMMsgTypeStatistics  syncReplacement;    /*< 120 bytes */
	DRMMsgTypeStatistics  delayReplacement;   /*< 140 bytes */
} DRMStatistics;

/**
  *	The description of a time reference
  */
typedef struct
{
	NodeId					id;				/**< The unique node id. */
	uint16					stepsRemoved;	/**< The steps Removed. */
	ClockQuality 			quality;		/**< The master clock Quality.	*/
	uint8					priority1;		/**< The priority1 value used assigned to the master by this node.	*/
	uint8					priority2;		/**< The priority2 value used assigned to the master by this node.	*/
	TimeTransport			timeTransport;	/**< The time transport. */
} ReferenceClock;

/**
  *	Visible Master status.
  */
typedef struct
{
	uint8 visibleMasterId;							/**< The unique Id of the visible master */
	PortId portIdentity;							/**< The PTP port identity of the master. */
	TransmissionProtocolAddress protocolAddress;	/**< The protocol address of the master. */
	uint8 ptpPortNumber;							/**< The local PTP port identity.		*/
	uint8 transmittedPriority1;						/**< The priority1 value received from the master.	*/
	uint8 transmittedPriority2;						/**< The priority2 value received from the master.	*/
	ReferenceClock grandmaster;						/**< The reference clock of the grandmaster */
}VisibleMasterStatus;

/**
  *	Status information relating to timing message grants from a Visible Master.
  */
typedef struct
{
	LogMessagePeriod logGrantedAnnounceMessagePeriod;		/**< The granted announce message period, log base 2. This may differ from the value requested by the PTP port. */
	LogMessagePeriod logGrantedSyncMessagePeriod;			/**< The granted sync message period, log base 2. This may differ from the value requested by the PTP port. */
	LogMessagePeriod logGrantedDelayRequestMessagePeriod;	/**< The granted delay request message period, log base 2.  This may differ from the value requested by the PTP port. */

	LogMessagePeriod logActualAnnounceMessagePeriod;		/**< The actual annouce message period, log base 2. This may differ from the granted value. */
	LogMessagePeriod logActualSyncMessagePeriod;			/**< The actual sync message period, log base 2. This may differ from the granted value. */
	LogMessagePeriod logActualDelayRequestMessagePeriod;	/**< The actual delay request message period, log base 2.  This may differ from the granted value. */

	uint32 remainingAnnounceGrant;				/**< The remaining announce grant */
	uint32 remainingSyncGrant;					/**< The remaining sync grant */
	uint32 remainingDelayRequestGrant;			/**< The remaining delay request grant */
}MessageGrantStatus;


/**
  *	Packet delay statistics for a visible master.
  */
typedef struct
{
	Bool estimatedTimeLagValid;					/**< Indicates whether the estimated time lag is valid. */
	float estimatedTimeLag;						/**< The estimated time lag. */
	Bool estimatedNoiseValid;					/**< Indicates whether the noise estimates are valid. */
	float estimatedNoiseMasterToSlave;			/**< The estimated noise in the master to slave direction.*/
	float estimatedNoiseSlaveToMaster;			/**< The estimated noise in the slave to master direction.*/
	float estimatedPacketDelayMasterToSlave;	/**< The estimated packet delay from the master. */
	float estimatedPacketDelaySlaveToMaster;	/**< The estimated packet delay to the master. */
}VisibleMasterDelayStatistics;


/**
  *	Status information relating to PTP messages received from a visible master.
  */
typedef struct
{
	Bool receivingMulticastAnnounceMessages;		/**< Indicates whether multicast announce messages received. */
	Bool receivingUnicastAnnounceMessages;			/**< Indicates whether unicast announce messages received. */
	Bool receivingMulticastSyncMessages;			/**< Indicates whether multicast sync messages received. */
	Bool receivingUnicastSyncMessages;				/**< Indicates whether unicast sync messages received. */
	Bool missingDelayResponseMessagesNotExcessive;	/**< Indicates whether missing delay response messages excessive. */
	float periodOfReceivedAnnounceMessages;			/**< Estimated period of received announce messages. */
	float periodOfReceivedSyncMessages;				/**< Estimated period of received sync messages. */
}VisibleMasterReceivedMessageStatus;


#define MAXIMUM_ACCEPTABLE_MASTERS 10 /**< The maximum number of acceptable masters per PTP port */

/**
  *	An entry in the acceptable masters table.
  */
typedef struct
{
	TransmissionProtocolAddress address;		  /**< The address of the master. */
	PortId portId; 			/**< The PTP port identity of the master. */
	uint8 priority1; 		/**< Low values of priority1 will be selected as current master in preference to higher values. */
	uint8 priority2;	  	/**< Low values of priority2 will be selected as current master in preference to higher values if priority1 values and clock quality are identical.	*/
	Bool requestUnicastAnnounceFromMaster;	  /**< Flag indicating whether the PTP port was required to send requests to the master immediately. */
} AcceptablePartnerTableEntry;

//still need master for deprecated functions
typedef AcceptablePartnerTableEntry AcceptableMasterTableEntry;
/**
  * The address of the master
  */
typedef AcceptablePartnerTableEntry AcceptableMasterTable[MAXIMUM_ACCEPTABLE_MASTERS];


/**
  * The state of the current master
  */
typedef enum
{
    measuringFrequencyCM, /**< Estimating frequency offset */
    measuringPhaseCM,	  /**< Estimating phase offset */
    runningCM			  /**< Running */
} CurrentMasterState;


/**
  *	The current master status.
  */
typedef struct
{
	uint8 visibleMasterIndex;						/**< The Index in visibleMasterArray of the visible master that is the current master */
	CurrentMasterState state;						/**< The state of the current master */
	PortId id;										/**< The id of the current master */
	TransmissionProtocolAddress address;			/**< The address of the current master */
}CurrentMasterDetails;


/**
 * \brief
 *     Time stamp receipt statistics.
 */
typedef struct
{
	struct
	{
		uint32 numValid;                   /**< #Time stamps received that have made it into one of the timestamp stores */
		uint32 numInvalid;                 /**< #Time stamps rejected before use because they contain invalid information */
		uint32 numDroppedDueToTimeout;     /**< #Time stamps removed from the message store because they stayed there too long, i.e., we not matched to their pair */
		uint32 numDroppedDueToOverwrite;   /**< #Time stamps overwritten in the message store because they were the oldest and were overwritten so that more recent timestamps could be stored */
	} T1, T2, T3, T4;

	uint32 numM2SRxd;                      /**< #Full T1, T2 pairs received and used */
	uint32 numS2MRxd;                      /**< #Full T3, T4 pairs received and used */
} CurrentMasterTimestampStatistics;


/**
  *	The impairment configuration.
  * There is one impairment controller per MASTER PTP port.
  */
typedef struct
{
	Bool   enabled;								/**< Impairment enabled if enabled == TRUE */
	uint8  masterPtpPortIndex;					/**< The PTP port on which impairments are applied. Index into MASTER ports, starting from 1.*/
	uint16 dataReqThreshold;					/**< The impairment data request threshold */
	EnhancedTransmissionProtocolAddress server; /**< The address of the impairment server */
} ImpairmentConfiguration;


/**
  *	The identity of a Phase Locked Loop (PLL)
  */
typedef enum
{
	mainPLL,
	secondaryPLL,
	timeSmoothingPLL = secondaryPLL,
	numberOfPLLids
} PLLid;

typedef enum
{
	clockTSA				= 0,
	firstClkPLLClockId      = clockTSA,
	clockTSB				= 1,
	networkTSA				= 2,
	firstPTPPLLClockId		= networkTSA,
	networkTSB				= 3,
	networkTSC				= 4,
	firstNodeTimeClockId	= networkTSC,
	networkTSD				= 5,
	numberOfClockIds,
	invalidClockId			= 255
} ClockId;

/**
  *	The state of a time reference source. Order is important, better states must have higher numbers
  */
typedef enum
{
	voidTRS,			/**< Empty */
	invalidTRS,			/**< No time is available */
	validTRS,			/**< Time is available but the source has not been selected */
	measuringTRS,		/**< The source has been selected and is measuring freq or phase offset */
	holdoverTRS,		/**< The source was running and now in holdover */
	runningTRS			/**< The source is providing time information to the selector. */
} TimeReferenceSourceState;

/**
  *	Status and configuration information relating to a time reference source.
  */
typedef struct
{
	/**
	 * The time reference source type. This indicates whether the source is a packet source or 1PPS source.
	 */
	TimeReferenceSourceState state;	/**< The state of the source. */
	float actualPhaseLagError;	/**< The phase lag of the source. */
	float measuredNoise; /**< The measured noise. For a network master this is the mean of noise in both directions. */
}TimeReferenceSourceDetails;


/**
  *	The state of the time reference selector.
  */
typedef enum
{
	INPUT_SELECTED,		/**< An input has been selected */
	HOLDOVER			/**< The time reference selector is in holdover */
}TimeReferenceSelectorState;


/**
  *	The forced locked/unlocked state of the time reference selector.
  */
typedef enum
{
	LOCKED_UNLOCKED_STATE_NOT_FORCED,		/**< The locked/unlocked state of the time reference selector is not forced */
	LOCKED_STATE_FORCED,					/**< The time reference selector is forced to locked */
	UNLOCKED_STATE_FORCED					/**< The time reference selector is forced to unlocked */
}ForceLockedUnlockedState;


/**
  *	Statistics relating to the time reference selector.
  */
typedef struct
{
	float fuzzyLockValue;						/**< The fuzzy lock value, in the range 0.0..1.0 */
	float frequencyOutputFrequencyOffset;		/**< The frequency offset of the frequency output relative to the local crystal */
	float timeOutputFrequencyOffset;			/**< The frequency offset of the time output relative to the local crystal */
	float holdoverOffset;						/**< The holdover offset */
	float suppressingPhaseJump;					/**< The fuzzy value for suppressing phase jump. */
	float timeCorrectedOutputFrequencyOffset;   /**< The frequency offset of the corrected time output relative to the local crystal */
}TimeReferenceSelectorStatistics;


/**
  *	Thresholds used to control setting of the lock pin.
  */
typedef struct
{
	/**
	 * The acceptable phase error threshold.  The estimated phase error must be equal to or less than this value for the input to be
	 * considered acceptable and the lock pin to be raised.  Units of time.  This threshold must be equal to or less than
	 * the unacceptable phase error threshold.
	 */
	float phaseErrorSecondsAcceptable;

	/**
	 * The unacceptable phase error threshold.  The lock pin is transitioned to lowered if the estimated phase error
	 * rises above this value. In units of time.
	 */
	float phaseErrorSecondsUnacceptable;

	/**
	 * The acceptable phase error gradient threshold.  The estimated phase error gradient must be equal to or less than this value for
	 * the input to be considered acceptable and the lock pin to be raised.  No units. This threshold must be equal to or less than
	 * the unacceptable phase error gradient threshold.
	 */
	float phaseErrorGradientAcceptable;

	/**
	 * The unacceptable phase error gradient threshold.  The locked pin is transitioned to lowered if the rate of change of the
	 * estimated phase error rises above this value.  No units.
	 */
	float phaseErrorGradientUnacceptable;

	/**
	 * The acceptable fuzzy lock value threshold.  The fuzzy lock value must be equal to or above this value for
	 * the input to be considered acceptable and the lock pin to be raised.  No units. This value must be equal to or greater
	 * than the unacceptable fuzzy lock value threshold.
	 */
	float fuzzyLockAcceptable;

	/**
	 * The unacceptable fuzzy lock value threshold.  The locked pin is transitioned to lowered if the fuzzy lock
	 * value falls below this value.  No units.
	 */
	float fuzzyLockUnacceptable;
}LockedStateThresholds;


/**
  *	Parameters relating to the frequency controller.
  */
typedef struct
{
	float noisyEnvironmentLimit;				/**< The frequency controller noisy environment limit */
	float noisyLockThreshold;					/**< The frequency controllor noisy lock threshold */
}FrequencyControllerParameters;

/**
  *	The type of the transport network that ToPSync will be sending and receiving timing packets over.
  */
typedef enum
{
	ADSL_NETWORK_TYPE,			/**< ADSL network */
	WIMAX_NETWORK_TYPE,			/**< WiMax network */
	ETHERNET_NETWORK_TYPE		/**< Ethernet network */
}TransportNetworkType;


#define SOFTWARE_VERSION_LENGTH 16		/**< The maximum length of the ToPsync software version string */
#define HARDWARE_VERSION_LENGTH 4		/**< The maximum length of the ToPsync hardware version string */
#define LOCATION_IDENTIFIER_LENGTH 4	/**< The maximum length of the location identifier string */

/**
  *	The software vresion response array
  */
typedef char SoftwareVersion[SOFTWARE_VERSION_LENGTH+1];

/**
  *	The external interface types of ToPSync, including network interfaces and bus/serial link interfaces.
  * Not all interfaces are supported by all parts.
  */
typedef enum
{
	EthernetMacInterface = 0,	/**< Ethernet MAC interface. */
	EthernetIpInterface = 1,	/**< IP packet interface over Ethernet. */
	EthernetRawInterface = 2,	/**< Direct packet interface over Ethernet. */
	SpiInterface = 3,			/**< SPI bus interface. */
	UartInterface = 4			/**< UART bus interface. */
} ExternalInterfaceType;


/**
  *	The number for the external interface. This number is unique withing each interface type, but it is
  * not necessarily unique across all interface types
  */
typedef uint16 ExternalInterfaceNumber;

/**
  *	Structure uniquely identifier an external interface.
  */
typedef struct
{
	ExternalInterfaceType interfaceType;		/**< The interface type. */
	ExternalInterfaceNumber interfaceNumber;	/**< The interface number. */
} ExternalInterface;

/**
  *	The maximum physical number of external (network) interfaces the system can support.  Not all parts will
  * support all the interfaces.
  */
#define MAXIMUM_EXTERNAL_INTERFACES 9

/**
  *	List of external interfaces.
  */
typedef ExternalInterface ExternalInterfaces[MAXIMUM_EXTERNAL_INTERFACES];

/**
  *	The initial system configuration.
  */
typedef struct
{
	/**
	  *	The initial configuration of the IP packet interfaces.
	  */
	IpPacketInterfaceConfiguration ipPacketInterfaceConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	/**
	  *	The initial configuration of the Ethernet packet interfaces.
	  */
	EthernetPacketInterfaceConfiguration ethernetPacketInterfaceConfiguration[NUMBER_OF_PHYSICAL_PORTS];
	/**
	  *	The interface to be used for control messages.
	  */
	ExternalInterface controlInterface;
	/**
	  *	The UDP port on the control interface for ToPSync control API (only applicable if control interface is IP).
	  */
	uint16 managementUdpPort;
	/**
	  *	The 32-bit security key.  Value of 0 indicates security key should be ignored.
	  */
	uint32 securityKey;
	/**
	  *	The location identifier.
	  */
	uint32 locationIdentifier;
	/**
	  *	Flag indicating whether MDIO is available.
	  */
	Bool mdioAvailable;
}ToPSyncInitialSystemConfiguration;

/**
  *	Values which can be used to override the default PTP values.
  */
typedef struct
{
	/**
	  *	The UDP port used for PTP event messages.
	  */
	uint16 udpEventPortNumber;
	/**
	  *	The UDP port used for PTP general messages.
	  */
	uint16 udpGeneralPortNumber;
	/**
	  *	The IP multicast address used for multicasting PTP messages over IP interface.
	  */
	uint32 ipMulticastAddress;
	/**
	  *	The ToS field for event messages.
	  */
	uint8 eventTos;
	/**
	  *	The ToS field for event messages.
	  */
	uint8 generalTos;
	/**
	  *	The Ethertype for direct Ethernet transport of PTP messages.
	  */
	uint16 etherType;
	/**
	  *	The Ethernet multicast address used for multicasting PTP messages over direct Ethernet.
	  */
	EthernetAddress ethernetMulticastAddress;
}ToPSyncPtpSystemParameters;

/**
  *	The upload interface configuration details.
  */
typedef struct
{
	/**
	  *	The interface to be used for uploading a new image to flash for flash-based parts.
	  */
	ExternalInterface uploadInterface;
	/**
	  *	The TCP port number to be used for uploading a new image if IP interface is specified for upload.
	  */
	uint16 tcpUploadPortNumber;

}ToPSyncUploadConfiguration;


/**
  *	The types of alarms that can be reported by ToPSync.
  */
typedef enum
{
	alarmInHoldover,	/**< In Holdover */
	alarmNoCurrentMaster,	/**< No Current Master */
	alarmNoClockInput,	/**< No Clock Input */
	alarmNoTimeOfDayInput,	/**< No Time Of Day Input */
	alarmToPSyncTimeNotTAI,	/**< ToPSync Time Not TAI */
	alarmPtpPortNotOperational,	/**< PtpPort Not Operational */

	alarmVisibleMasterRefusedSyncGrantRequest,		/**< Visible Master Refused Sync Grant Request */
	alarmVisibleMasterIgnoredSyncGrantRequest,		/**< Visible Master Ignored Sync Grant Request */
	alarmVisibleMasterRefusedDlyRespGrantRequest,	/**< Visible Master Refused Dly Resp Grant Request */
	alarmVisibleMasterIgnoredDlyRespGrantRequest,	/**< Visible Master Ignored Dly Resp Grant Request */
	alarmVisibleMasterTooFewSyncMessages,	/**< Visible Master Too Few Sync Messages */
	alarmVisibleMasterTooFewFollowUpMessages,	/**< Visible Master Too Few Follow Up Messages */
	alarmVisibleMasterTooFewDelayResponseMessages,	/**< Visible Master Too Few Delay Response Messages */

	alarmAccMasterRefusedAnnounceGrantRequest,	/**< Acceptable Master Refused Announce Grant Request */
	alarmAccMasterIgnoredAnnounceGrantRequest,	/**< Acceptable Master Ignored Announce GrantRequest */
	alarmAcceptableMasterTooFewAnnounceMessages,	/**< Acceptable Master Too Few Announce Messages */

	alarmCurrentMasterTooManySyncsWithoutFollowUp,	/**< Current Master Too Many Syncs Without Follow Up - Not Implemented*/
	alarmCurrentMasterTooManyFollowUpsWithoutSync,	/**< Current Master Too Many Follow Ups Without Sync - Not Implemented*/
	alarmCurrentMasterTooManyMissingDlyResponses,	/**< Current Master Too Many Missing Dly Responses - Not Implemented*/
	alarmM2SPacketDelayVaration,	/**< M2S Packet Delay Varation */
	alarmS2MPacketDelayVaration,	/**< S2M Packet Delay Varation */

	alarmToPSyncUTCOffsetUnknown,

	alarmTDMInterrupt,	/**< TDM registers interrupt */

	alarmPathDelayInvalid, 							/**<  No valid path delay information is held */
	alarmPathDelayTooFewResponses,					/**<  Too few path delay response messages are being received */
	alarmPathDelayTooManyUnexpectedResponses, 		/**<  Too many path delay response messages are being received when no request has been sent */
	alarmPathDelayTooFewFollowUps,					/**<  Too few path delay follow up messages are being received */
	alarmPathDelayTooManyUnexpectedFollowUps,		/**<  Too many path delay follow up messages are being received when no request has been sent */

	alarmLeapSecondWarning,							/**<  A leap second is coming*/

	alarmM2SPacketDelayJump,						/**< M2S packet delay jump */
	alarmS2MPacketDelayJump,						/**< S2M packet delay jump */

	alarmBinaryLockLow,								/**< the TimeReferenceSource is binaryLock is low (out of lock) */
	alarmBinaryLockLossOfLock,						/**< the TimeReferenceSource is binaryLock is low (out of lock) and use this in calculating alarm pin */

	alarmECCError,									/**< there is an error with ecc */

	alarmUserDataReady,								/**< Some user data has arrived at the port*/

	alarmTooFewSMTLVs,								/**< The received  rate of SM TLVs is too low*/
	alarmNewSMTLVData,								/**< SM tlv data has arrived and is different from the last one*/

	numberOfAlarmTypes,
	nullAlarmCondition = numberOfAlarmTypes

} AlarmSource;


//if 33 alarms we should expect 2 words to be used.
#define ALARM_SOURCE_WORDS ((numberOfAlarmTypes / BITS_IN_ALARM_WORD) + 1)


/**
  *	The unique client identifier for the module that raised the AlarmSource
  */
typedef uint8 AlarmSourceIdentity;  /**< values between 0 and 255 are valid */

/**
  * The maximum number of Alarm Clients
 */
#define MAX_ALARM_CLIENTS 64

/**
  * The number of bits in an alarm word
 */
#define BITS_IN_ALARM_WORD  (sizeof(uint32) * 8)

/**
  * The number of alarm words
 */
#define ALARM_STATE_WORDS (MAX_ALARM_CLIENTS / BITS_IN_ALARM_WORD)

/**
  * The structure to store the array of alarms which allows up to 256 clients to be used
 */
typedef struct AlarmStateArrayStruct
{
	uint32 array[ALARM_STATE_WORDS];
}AlarmStateArray;

/**
  *	The maximum number of domain words to get 256 domain array bitfield
  */
#define DOMAIN_ARRAY_WORDS 8
/**
  * The array stores the 256 bit field for the domains required in the Network Master Table
 */
typedef struct DomainArrayStruct
{
	uint32 domainMask[DOMAIN_ARRAY_WORDS];
}DomainArray;

/**
  *	The maximum number of entries in the network master table
  */
#define MAX_NETWORK_MASTERS 32

/**
  * The number of bits in an alarm word
 */
#define BITS_IN_NMT_WORD  (sizeof(uint32) * 8)

/**
  *	The number of bitfield words in the network master table
  */
#define MASTER_BITFIELD_WORDS (MAX_NETWORK_MASTERS/BITS_IN_NMT_WORD)

/**
  * The array stores the bit field for masters in the Network Master Table
 */

typedef struct NetworkNasterStruct
{
	uint32 mastersArray[MASTER_BITFIELD_WORDS];
}MastersArray;



/**
  *	The maximum length of a filename for reporting an exception.
  */
#define MAX_LENGTH_OF_EXCEPTION_FILENAME 55

/**
  *	The maximum number of exceptions reported in an exception hierarchy.
  */
#define MAXIMUM_EXCEPTION_HIERARCHY	3

/**
  *	Structure representing a ToPSync system exception.
  */
typedef struct
{
	uint16 lineNumber;		/**< The line number in the file where the exception occurred. */
	char fileName[MAX_LENGTH_OF_EXCEPTION_FILENAME]; /**< The name of the file where the exception occurred. */
}ToPSyncSystemException;

/**
  *	The exceptions report for ToPSync
  */
typedef ToPSyncSystemException ToPSyncSystemExceptionReport[MAXIMUM_EXCEPTION_HIERARCHY];

#ifndef MAX_UNICAST_TOPSYNCS
#define MAX_UNICAST_TOPSYNCS 10
#endif

/**
  * Number of 32-bit words in the firmware upgrade
  * encryption key. Total length is 128 bits.
  */
#define FIRMWARE_ENCRYPTION_KEY_NUMBER_OF_WORDS 4

/**
  *	The encryption key storage array
  */
typedef uint32 EncryptionKey[FIRMWARE_ENCRYPTION_KEY_NUMBER_OF_WORDS];

/*
 * Size of data burst in bytes that is sent with
 * each \FirmwareBurstMsg.
 */
#define FIRMWARE_BURST_DATA_LENGTH 128

/**
  *	The firmware burst data storage array
  */
typedef uint8 FirmwareBurstData[FIRMWARE_BURST_DATA_LENGTH];

/**
  *	The state of the ToPSync system.
  */
typedef enum
{
	TOPSYNC_BOOT_STATE,						/**< The ToPSync application has just started */
	TOPSYNC_INITIALISING_SYSTEM_STATE,		/**< The ToPSync system is being initialised. */
	TOPSYNC_INITIALISING_APPLICATION_STATE,	/**< The ToPSync application is being initialised. */
	TOPSYNC_RUNNING_STATE,					/**< The ToPSync system and application have been initialised and the application is running */
	TOPSYNC_SOFTWARE_CORRUPT_STATE,			/**< The CRC check of the application image has failed. */
	TOPSYNC_EXCEPTION_STATE,				/**< A fatal exception has been detected. */
	NUMBER_OF_TOPSYNC_STATES
}ToPSyncSystemState;

/**
  *	The ToPSync Part Number.
  */
typedef enum
{
	GENERAL_PART = 0,			/**< For general-purpose evaluation and playing around. */
	ACS9590_PART = 0x00009590,	/**< ACS9590 */
	ACS9591_PART = 0x00009591,	/**< ACS9591 */
	ACS9592_PART = 0x00009592,	/**< ACS9592 */
	ACS9593_PART = 0x00009593,	/**< ACS9593 */
	ACS9550_PART = 0x00009550,	/**< ACS9550 */
	ACS9520_PART = 0x00009520,	/**< ACS9520 */
	ACS9522_PART = 0x00009522,  /**< ACS9522 */
	ACS9510_PART = 0x00009510,	/**< ACS9510 */
	ACS9521_PART = 0x00009521,	/**< ACS9521 */
	ACS9528_PART = 0x00009528,	/**< ACS9528 */
	ACS9529_PART = 0x00009529,  /**< ACS9529 */
	INVALID_PART = 0xFFFFFFFF	/**< Used when the part number is unknown */
}ToPSyncPartNumber;

/**
  *	Time codes for TOD interfaces.
  */
typedef enum
{
	UNUSED_TIME_CODE,				/**< Unused time code format */
	MOTOROLA_BINARY_TIMECODE,		/**< Motorola Binary time code format */
	NTP_V4_TIME_CODE,				/**< NTP V4 time code format */
	NMEA_0183_TIME_CODE				/**< NMEA 0183 time code format */
} TODTimeCode;


/**
  *	Available baud rates for UART Interface.
  */
typedef enum
{
	BAUD_RATE_1200 = 1200,					/**< UART baud rate 1200 */
	BAUD_RATE_2400 = 2400,					/**< UART baud rate 2400 */
	BAUD_RATE_4800 = 4800,					/**< UART baud rate 4800 */
	BAUD_RATE_9600 = 9600,					/**< UART baud rate 9600 */
	BAUD_RATE_19200 = 19200,				/**< UART baud rate 19200 */
	BAUD_RATE_38400 = 38400,				/**< UART baud rate 38400 - not supported on TS1 */
	BAUD_RATE_57600 = 57600,				/**< UART baud rate 57600 - not supported on TS1 */
	BAUD_RATE_115200 = 115200				/**< UART baud rate 115200 - not supported on TS1 */
} UartBaudRate;


/**
 * \brief ToPSync time type. Defines an IEEE 1588 time stamp. The seconds field has been split 
 *        into two fields because IEEE 1588 seconds count is 48-bit. As there is no such native 
 *        C data type that is 48 bits and not all compilers may support 64-bit integers, the 
 *        seconds count is split into the 16 most significant and 32 least significant bits, 
 *        named seconds and epoch respectively.
 */
typedef struct
{
	uint32 seconds;		/**< Least significant 32-bits of seconds count */
	uint32 nanoseconds; /**< Nanoseconds field */
	uint16 epoch;		/**< Most significant 16-bits of seconds count */
	Bool   isTAI;		/**< Flag indicating if the time is valid TAI */
} ToPSyncTime;



/**
  *	ToPSync time scale type.
  */
typedef enum
{
	epochUTC,	/**< The timescale is UTC - contains leap seconds*/
	epochTAI,	/**< The timescale is TAI - does not contain leap seconds */
	epochGPS,	/**< The timescale is GPS - does not contain leap seconds.  NOTE Many GPS receivers put out UTC not GPS time.  */
	epochARB	/**< The timescale is ARB - this is an arbitrary time scale defined by the user */
} ToPSyncTimescale;


/**
  *	ToPSync time of day type.
  */
typedef struct
{
	uint16 year;	/**< since start of Christian calendar */
	uint8 month;	/**< 1 - 12 */
	uint8 day;	 	/**< 1 - 31 (depending on month) */
	uint8 hour;		/**< 0 - 23 */
	uint8 minute;	/**< 0 - 59 */
	uint8 second;	/**< 0 - 59 */
} ToPSyncTimeOfDay;



#define TOD_SENTENCE_MAX_LENGTH 100	/**< Max length of a TOD sentence */

/**
  *	Length of the NMEA SMTI message
  */
#define SMTI_MESSAGE_LENGTH 23
#define SMTS_MESSAGE_LENGTH SMTI_MESSAGE_LENGTH


/**
  *	Max length of I2C data message
  */
#define I2C_MAX_DATA_LENGTH 32


/**
  *	Status information relating to TOD interface.
  */
typedef struct
{
	uint32 messagesReceived;	/**< The number of messages received */
	char lastSentenceReceived[TOD_SENTENCE_MAX_LENGTH];	/**< The last sentence received */
	ToPSyncTime timeLastSentenceReceived;	/**< The time the last sentence was received. This time is not adjusted for UTC */
}TODInputStatus;


#define MAX_WARNING_DAYS 400 /**< The maximum permitted value for daysToLeapSecond. */


/**
  *	Status information about grants 
  */
typedef struct
{
	TransmissionProtocolAddress		clientAddress; 	/**< The address of the client to which the grant has been issued */
	PortId							clientPortId;	/**< The identity of the client to which the grant has been issued */
	LogMessagePeriod 				logPeriod;	/**< The granted message period, log base 2. */
	uint32 							remainingDuration;	/**< The remaining grant, in seconds*/
	uint16 							ptpPortNumber;		/**< The number of the local PtPort */
} GrantStatus;



/**
  *	The id of the mux to be used
  */
typedef enum
{
	TDMBlockMux=0,	/**< Use the TDM mux (internally known as SETS) */
	PTPBlockMux,	/**< Use the PTP mux */
	OPClkBlockMux	/**< Use the OP clock mux*/
} MuxID;

/**
  *	What input to be used for the TDM mux - either use the input from the IP Clock
  * or use the other input which will be PTP (DDS or DivNx depending on what line is being set).
  * See the documentation for which line can use what input.
  * example: ToPSyncSetMuxInput(TDMBlockMux, 2, (uint8)TDMInputFrom_IpClk);
  */
typedef enum
{
    TDMInputFrom_IpClk=0,	/**< use IpClockx for the tdm input*/
    TDMInputFrom_other	/**< use opclkx or DivNx for tdm input*/
} TdmMuxInput;

/**
  *	What input to be used for the Ptp mux - either use the input from the
  * IP Clock or use the other input which will be TDM.
  * See the documentation for which line can use what input
  * example: ToPSyncSetMuxInput(PTPBlockMux, 2, (uint8)PTPInputFrom_IpClk);
  */
typedef enum
{
    PTPInputFrom_IpClk=0,	/**<use IpClockx for the ptp input*/
    PTPInputFrom_other	/**<use tdm for ptp input*/
} PtpMuxInput;

/**
  *	What input to be used for the OP Clock mux - either use the output from TDM or PTP
  * depending on what line is being set.
  * See the documentation for which line can use what input
  * example: ToPSyncSetMuxInput(OPClkBlockMux, 2, (uint8)OpClkInputFrom_TDM);
  */
typedef enum
{
    OpClkInputFrom_TDM=0,		/**<*use tdm for the input*/
    OpClkInputFrom_other	/**<use DDS for input*/
} OpClkMuxInput;


/**
  * The SPI Interface Clock Edge polarity.
  * This type is only relevant for Boot messages.
  */
typedef enum
{
	POSITIVE = 0,		/**< Bytes on the SPI interface are clocked out on the rising clock edge. */
	NEGATIVE = 1		/**< Bytes on the SPI interface are clocked out on the falling clock edge. */
} SpiClockEdgePolarity;


typedef enum
{	// Note mode 1 no longer "really" exists... it is a specific mode 2 configuration
	timestampProcessorMode2	= 0,	// Timing messages are timestamped externally.  ToPSync timestampers are turned OFF
									// Received timing messages are a mix of PTP messages and Delay Replacement Messages
	timestampProcessorMode3	= 1	// Timing messages are timestamped externally.
									// Only Delay Replacement timing messages are sent to ToPSync
} ToPSyncTimestampProcessorMode;

/**
  *	MasterLoadLimit.
  *	This type is used to set which parameter is to be used in configuring the master
  * For example the user can choose to set the maximum number of slaves etc
  *
  * example: ToPSyncSetMasterLoadLimit(toPSyncAddress, maxSlaves, 128);
  *
  */

typedef enum
{
	maxSlaves,	/**< max Slaves */

	maxTotalAnnounceRate,	/**< max Total Announce Rate*/
	maxTotalSyncRate,	/**< max Total Sync Rate*/
	maxTotalDelayResponseRate,	/**< max Total Delay Response Rate*/

	minAnnounceLogPeriod,	/**< min Announce Log Period*/
	minSyncLogPeriod,	/**< min Sync Log Period*/
	minDelayResponseLogPeriod,	/**< min Delay Response Log Period*/

	maxAnnounceGrantDuration,	/**< max Announce Grant Duration*/
	maxSyncGrantDuration,	/**< max Sync Grant Duration*/
	maxDelayResponseGrantDuration,	/**< max Delay Response GrantDuration*/
	numberOfMasterLoadLimitValues	/**< not used*/

} MasterLoadLimit;


/* cut down version of ClockPathGenericParameter for use in control driver only*/
typedef enum
{
	phaseErrorGradientCPH,
	setMaintainBinLockPinInSourceSwitchCPH,
	setFrequencyOutputsSourceCPH,
	getHoldoverValidCPH,
	setHybridTimeControllerEnabledCPH,
	getTimestampProcessorModeCPH,

	setLeapSecondWarningInSecsCPH=10
} ClockPathGenericParameterHost;


/* Hybrid binary lock monitor mode */
typedef enum
{
	monitorPTPInputHybridLock,
	monitorClockInputHybridLock,
	monitorBothInputsHybridLock,
	numberOfMonitorModesHybridLock
} HybridLockMonitorModeHost;

/* cut down version of TRSelThreshold for use in control driver only*/
typedef enum
{
	phaseErrorGradientH = 70,				/* Deprecated.  Use phaseErrorGradientCPH */
	nonRevertiveH = 80,
	nonRevertiveSameTransportH,
	setRequireTAIH,
	setRequireUTCH,
	setMaintainBinLockPinInSourceSwitchH,	/* Deprecated.  Use setMaintainBinLockPinInSourceSwitchCPH */
	setRequireFrequencyTraceableToPrimaryRefSourceH = 87,
	setFrequencyOutputsUseSmoothedTimeH,
	getHoldoverValidH = 110,
	getLockDetectorFuzzyLockValueH = 370,

	blmMonitorModeH = 400,
	blmFuzzyLockAcceptableH,		/* note these currently apply to the mainPLL */
	blmFuzzyLockUnacceptableH   	/* monitor only  (used in hybrid mode)       */


} TRSelThresholdHost;

/* cut down version of HTCParameter for use in control driver only*/
typedef enum
{
	enableHTCH,
	setModeHTCH,
	resetHTCH,

	storedDelayDurationMsHTCH = 10,
	storedDelayDurationSmHTCH,
	storedDelayDurationHTCH			//both
} HTCParameterHost;

/* cut down version of PtpPortParameter for use in control driver only*/
typedef enum
{
	setTwoStepOperationH = 0,
	setPtpPortAddressingModeH,
	setPtpPortUsePDelayH,

	setAnnounceGrantRequestThresholdH = 13,
	setSyncGrantRequestThresholdH,
	setDelayGrantRequestThresholdH,
	setAnnounceGrantRepeatPeriodH,
	setSyncGrantRepeatPeriodH,
	setDelayGrantRepeatPeriodH,	

	setNumberOfAlternateMastersH=30,
	setDomainH = 35,
	enableSpeculativeAnnounceTransmissionH = 40,
	setSpeculativeAnnounceLogPeriodH,

	setMasterPacketInterfaceSpeedH=60,
	setRenewalFlagH,
	setRefusalFlagH,

	setHybridFreqInputH=80,

	setDoNotBecomeMasterIfTaiUnknownH=70,
	setDoNotBecomeMasterIfUtcUnknownH,
	setDoNotBecomeMasterIfSourceIsNotPrsH,	/* PRS == Primary Reference Source */

	setEboundaryClockModeH = 100,
	setEboundaryClockTxRateH

} PtpPortParameterHost;

/* cut down version of ClockLockingControllerParameter for use in control driver only*/
typedef enum
{
	timeOfDayInputValidThresholdH = 200,
	timeOfDayEnableAutoLeapSecondDetectionH,
	setStepsRemovedForInputClockH

} ClockLockingControllerParameterHost;


typedef enum
{
	binLockPhaseErrorInputFilterBandwidthLockedH = 0,
	binLockPhaseErrorInputFilterBandwidthUnlockedH,
	setEnablePhaseBuildOutH,
	setUnselectedPhaseLagFilterBandwidthOpenH,
	setUnselectedPhaseLagFilterBandwidthClosedH,

} TRSrcParameterHost;


typedef enum
{
	activeSentenceH = 0,
	smtcProprietaryMessageTimeFormatH,
	smtcSmtsMessageDataH=10
} NMEA0183ParameterHost;


typedef enum
{
	getDOSProtectionActiveTimeH=0,
	getDOSProtectionActiveIncidentsH
}NetworkParameterHost;


typedef enum
{
	setResponseToPathDelayRequestsH = 0
} NetworkProtocolInterfaceParameterHost;


typedef enum
{
	getAnnounceNumberOfGrantsIssuedH,
	getAnnounceGrantsIssuedChangeCounterH,
	getSyncNumberOfGrantsIssuedH,
	getSyncGrantsIssuedChangeCounterH,
	getDelayResponseNumberOfGrantsIssuedH,
	getDelayResponseGrantsIssuedChangeCounterH
} PhysicalPortParameterHost;


typedef enum
{
	getVisibleMasterGrantsIssuedChangeCounterH
} VisibleMasterParameterHost;


typedef enum
{
	setSelectOutputClockSourceH = 0,
	setPhaseAlignedOutputClockFrequency10MHzH
} ClockOutputsParameterHost;


typedef enum
{
	setAcs1790GigabitEthernetOutputH,
	setAcs179010GigabitEthernetOutputH,
	setAcs1790HighSpeedOutputH,
	setAcs1790LowSpeedOutputH,
	getAcs1790LockedValueH,
	setAcs1790ClosedLoopH,
	setAcs1790OpenLoopH
} ACS1790ParameterHost;

/* ToPSync parameter number ranges (used by SetToPSyncParameter()  ) */
#define LD_PARAMETER_MIN								0		// deprecated
#define LD_PARAMETER_RANGE								1000	// deprecated
#define LD_PARAMETER_MAX								(LD_PARAMETER_MIN + LD_PARAMETER_RANGE - 1)		// deprecated

#define TRSEL_PARAMETER_MIN								(LD_PARAMETER_MAX + 1)  /* 1000 */
#define TRSEL_PARAMETER_RANGE							1000
#define TRSEL_PARAMETER_MAX								(TRSEL_PARAMETER_MIN + TRSEL_PARAMETER_RANGE - 1)

#define PTP_PORT_PARAMETER_MIN							(TRSEL_PARAMETER_MAX + 1)  /* 2000 */
#define PTP_PORT_PARAMETER_RANGE						1000
#define PTP_PORT_PARAMETER_MAX							(PTP_PORT_PARAMETER_MIN + PTP_PORT_PARAMETER_RANGE - 1)

#define CLOCK_INPUT_PARAMETER_MIN						(PTP_PORT_PARAMETER_MAX + 1)  /* 3000 */
#define CLOCK_INPUT_PARAMETER_RANGE						1000
#define CLOCK_INPUT_PARAMETER_MAX						(CLOCK_INPUT_PARAMETER_MIN + CLOCK_INPUT_PARAMETER_RANGE - 1)

#define TRSRC_PARAMETER_MIN								(CLOCK_INPUT_PARAMETER_MAX+1) /* 4000 */
#define TRSRC_PARAMETER_RANGE							1000
#define TRSRC_PARAMETER_MAX								(TRSRC_PARAMETER_MIN+TRSRC_PARAMETER_RANGE-1)

#define NODE_PARAMETER_MIN								(TRSRC_PARAMETER_MAX+1) /* 5000 */
#define NODE_PARAMETER_RANGE							1000
#define NODE_PARAMETER_MAX								(NODE_PARAMETER_MIN+NODE_PARAMETER_RANGE-1)

#define NMEA0183_PARAMETER_MIN							(NODE_PARAMETER_MAX +1) /*6000*/
#define NMEA0183_PARAMETER_RANGE						1000
#define NMEA0183_PARAMETER_MAX							(NMEA0183_PARAMETER_MIN + NMEA0183_PARAMETER_RANGE - 1)

#define NETWORK_PARAMETER_MIN							(NMEA0183_PARAMETER_MAX +1) /*7000*/
#define NETWORK_PARAMETER_RANGE							1000
#define NETWORK_PARAMETER_MAX							(NETWORK_PARAMETER_MIN + NETWORK_PARAMETER_RANGE - 1)

#define NETWORK_PROTOCOL_INTERFACE_PARAMETER_MIN		(NETWORK_PARAMETER_MAX +1) /*8000*/
#define NETWORK_PROTOCOL_INTERFACE_PARAMETER_RANGE		1000
#define NETWORK_PROTOCOL_INTERFACE_PARAMETER_MAX		(NETWORK_PROTOCOL_INTERFACE_PARAMETER_MIN + NETWORK_PROTOCOL_INTERFACE_PARAMETER_RANGE - 1)

#define PHYSICAL_PORT_PARAMETER_MIN						(NETWORK_PROTOCOL_INTERFACE_PARAMETER_MAX +1) /*9000*/
#define PHYSICAL_PORT_PARAMETER_RANGE					1000
#define PHYSICAL_PORT_PARAMETER_MAX						(PHYSICAL_PORT_PARAMETER_MIN + PHYSICAL_PORT_PARAMETER_RANGE - 1)

#define VISIBLE_MASTER_PARAMETER_MIN					(PHYSICAL_PORT_PARAMETER_MAX +1) /*10000*/
#define VISIBLE_MASTER_PARAMETER_RANGE					1000
#define VISIBLE_MASTER_PARAMETER_MAX					(VISIBLE_MASTER_PARAMETER_MIN + VISIBLE_MASTER_PARAMETER_RANGE - 1)

#define CLOCK_PATH_PARAMETER_MIN						(VISIBLE_MASTER_PARAMETER_MAX + 1)  /*11000*/
#define CLOCK_PATH_PARAMETER_RANGE						1000
#define CLOCK_PATH_PARAMETER_MAX						(CLOCK_PATH_PARAMETER_MIN + CLOCK_PATH_PARAMETER_RANGE - 1)

#define HYBRID_CONTROLLER_PARAMETER_MIN					(CLOCK_PATH_PARAMETER_MAX +1) /*12000*/
#define HYBRID_CONTROLLER_PARAMETER_RANGE				1000
#define HYBRID_CONTROLLER_PARAMETER_MAX					(HYBRID_CONTROLLER_PARAMETER_MIN + HYBRID_CONTROLLER_PARAMETER_RANGE - 1)

#define TIME_SMOOTHER_PARAMETER_MIN						(HYBRID_CONTROLLER_PARAMETER_MAX +1) /*13000*/
#define TIME_SMOOTHER_PARAMETER_RANGE					1000
#define TIME_SMOOTHER_PARAMETER_MAX						(TIME_SMOOTHER_PARAMETER_MIN + TIME_SMOOTHER_PARAMETER_RANGE - 1)

#define CLOCK_OUTPUTS_PARAMETER_MIN						(TIME_SMOOTHER_PARAMETER_MAX +1) /*14000*/
#define CLOCK_OUTPUTS_PARAMETER_RANGE					1000
#define CLOCK_OUTPUTS_PARAMETER_MAX						(CLOCK_OUTPUTS_PARAMETER_MIN + CLOCK_OUTPUTS_PARAMETER_RANGE - 1)

#define EXTERNAL_INTERFACES_PARAMETER_MIN				(CLOCK_OUTPUTS_PARAMETER_MAX +1) /*15000*/
#define EXTERNAL_INTERFACES_PARAMETER_RANGE				1000
#define EXTERNAL_INTERFACES_PARAMETER_MAX				(EXTERNAL_INTERFACES_PARAMETER_MIN + EXTERNAL_INTERFACES_PARAMETER_RANGE - 1)

#define ACS1790_PARAMETER_MIN							(EXTERNAL_INTERFACES_PARAMETER_MAX +1) /*16000*/
#define ACS1790_PARAMETER_RANGE							1000
#define ACS1790_PARAMETER_MAX							(ACS1790_PARAMETER_MIN + ACS1790_PARAMETER_RANGE -1)



/**
  * NMEA Setence bit field. Used to select the NMEA sentences that ToPSync will output
  * if the ToD interface is enabled.
  */
#define NMEA_RMC_SENTENCE	0x01	/**< Recommended Minimum C */
#define NMEA_GGA_SENTENCE	0x02	/**< Fix information */
#define NMEA_ZDA_SENTENCE	0x04	/**< Date and Time */
#define NMEA_SMTT_SENTENCE	0x08	/**< Semtech Time sentence */
#define NMEA_SMTF_SENTENCE	0x10	/**< Semtech Frequency sentence */
#define NMEA_SMTC_SENTENCE	0x20	/**< Semtech Time Short sentence (IRIG) */
#define NMEA_SMTI_SENTENCE	0x40 	/**< Semtech Time Information sentence */
#define NMEA_SMTS_SENTENCE	0x80 	/**< Semtech Time Status sentence */


/**
  * These are the supported time formats for the SMTC proprietary NMEA
  * Time sentence (SMTT).
  */
#define NMEA_SMTC_TIME_FORMAT_TAI	0	/**< TAI */
#define NMEA_SMTC_TIME_FORMAT_UTC	1	/**< UTC */
#define NMEA_SMTC_TIME_FORMAT_GPS	2	/**< GPS */


/**
  * These values are used to specify how the time provided by the SMTC NMEA Time sentence (SMTT)
  * will be aligned to the PPnS Clock.
  */
#define NMEA_SMTC_TIME_ALIGNMENT_TRAILING_EDGE	0	/**< Time is aligned to the preceding PPnS edge. */
#define	NMEA_SMTC_TIME_ALIGNMENT_LEADING_EDGE	1	/**< Time is aligned to the next PPnS edge. */



/**
  *	EnablePhaseOPClk.
  *	This type is used to select which Phase Output Clock to be used when setting the DDS enable
  *	register.
  *
  */
typedef enum
{
	enableDDS=0,	/**< Output Clock driven by DDS */
	enablePhOpClk0,	/**< Output Clock driven by Phase Output Clock 0 */
	enablePhOpClk1,	/**< Output Clock driven by Phase Output Clock 1 */
	enablePhOpClk2,	/**< Output Clock driven by Phase Output Clock 2 */
	enablePhOpClk3	/**< Output Clock driven by Phase Output Clock 3 */
} EnablePhaseOPClk;



/**
  *	The Best Master Clock Algorithm (BMCA) bit mask.
  *	This bit mask contains which steps are to be performed in the BMCA. If a bit is set then
  *	the corresponding step is performed.
  *	0x01	GM Priority1
  * 0x02	GM Identity
  * 0x04	GM Clock Class
  * 0x08	GM Accuracy
  * 0x10	GM offsetScaledLogVariance
  * 0x20	GM Priority2
  * 0x40	Steps Removed
  * 0x80	GM Identity values
  * The default value 0xBF, ie all steps enabled except for Steps Removed
  */
typedef uint8 BMCABitMask;

/**
  * BMCA Bitmask bit values
  */
#define BMCA_BIT_PRIORITY1 0x1
#define BMCA_BIT_ID 0x2
#define BMCA_BIT_CLOCK_CLASS 0x4
#define BMCA_BIT_ACCURACY 0x8
#define BMCA_BIT_LOG_VAR 0x10
#define BMCA_BIT_PRIORITY2 0x20
#define BMCA_BIT_STEPS_REMOVED 0x40
#define BMCA_BIT_ID_VALUES 0x80

/**
  * Default BMCA BitMask value, note steps remove test is off by default
  */
#define BMCA_BITMASK_DEFAULT 0xBF


/**
  *	BetterMasterAvailable
  *	This enumeration is used to select if there is a master available that is better than
  *	the current selected master
  *
  */
typedef enum
{
	sameAvailable=0,	/**< There is a master of the same quality available */
	betterAvailable, 	/**< There is a better master available */
	noneAvailable		/**< There are no better masters available */
} BetterMasterAvailable;



/**
  *	LCD Screens
  *	This enumeration is used to select which LCD screens should be displayed
  *
  */
typedef enum
{
	ptpSlave1Screen             = 0,    /**< The first ptp slave screen */
	ptpSlave2Screen             = 1,    /**< The second ptp slave screen */
	ptpMaster1Screen            = 2,    /**< The first ptp master screen */
	ptpMaster2Screen            = 3,    /**< The second ptp master screen */
	nodeTime1Screen             = 4,    /**< The first node time screen */
	nodeTime2Screen             = 5,    /**< The second node time screen */
	clockLocker1Screen          = 6,    /**< The first clock locker screen */
	clockLocker2Screen          = 7,    /**< The second clock locker screen */
	generalScreen               = 8,    /**< The general screen */
	ptpSlave1ModeInfScreen      = 9,    /**< The first ptp slave mode info screen */
	ptpSlave2ModeInfScreen      = 10,   /**< The first ptp slave mode info screen */
	ptpMaster1ModeInfScreen     = 11,   /**< The first ptp master mode info screen */
	ptpMaster2ModeInfScreen     = 12,   /**< The first ptp master mode info screen */
#ifdef USE_ACS1790
	userDataScreen			     = 13   /**< Screen for user defined data */
#endif

} LCDScreens;


/**
  *	The Lcd screen bit mask.
  *	This bit mask contains which screens are to be displayed on the lcd. If a bit is set then
  *	the corresponding screen is displayed.
  *	0x01	Ptp Slave 1
  * 0x02	Ptp Slave 2
  * 0x04	Ptp Master1
  * 0x08	Ptp Master 2
  * 0x10	nodeTime1
  * 0x20	nodeTime2
  * 0x40	clockLocker1
  * 0x80	clockLocker2
  * 0x100	general
  * The default value 0x1FF, ie all screens enabled
  */
typedef uint16 LcdScreenBitMask;

/**
  * BMCA Bitmask bit values */
#define LCD_BIT_PTPSLAVE1           0x0001
#define LCD_BIT_PTPSLAVE2           0x0002
#define LCD_BIT_PTPMASTER1          0x0004
#define LCD_BIT_PTPMASTER2          0x0008
#define LCD_BIT_NODETIME1           0x0010
#define LCD_BIT_NODETIME2           0x0020
#define LCD_BIT_CLOCKLOCKER1        0x0040
#define LCD_BIT_CLOCKLOCKER2        0x0080
#define LCD_BIT_GENERAL             0x0100
#define LCD_BIT_PTPSLAVE1_MODEINF   0x0200
#define LCD_BIT_PTPSLAVE2_MODEINF   0x0400
#define LCD_BIT_PTPMASTER1_MODEINF  0x0800
#define LCD_BIT_PTPMASTER2_MODEINF  0x1000


/**
  * Default LcdScreenBitMask value, 14 screens can be displayed
  */
#define LCD_BIT_MASK_DEFAULT 0x21FF

/**
  * Maximum number of lcd screens,
  */
#define LCD_MAX_NUMBER_OF_SCREENS 14

/**
  * size of the LCD bit mask for screen displau
  */
#define LCD_BIT_MASK_LEN 13

/**
  * The minimum time period a screen can be displayed for before moving on to the next screen
  */
#define LCD_MINIMUM_DISPLAY_PERIOD 0.5f

/**
  * The default time period a screen can be displayed for before moving on to the next screen
  */
#define LCD_DEFAULT_DISPLAY_PERIOD 1.0f


/**
  * The number of chars in the user data screen
  */
#define LCD_USER_DATA_LENGTH 64

/**
  *	The Udpprint output mask
  *	This bit mask contains which elements of debug output are sent in udpprintf data
  */

#define UDPPRINT_PTP_PORT1			((uint32)0x00000001)
#define UDPPRINT_PTP_PORT2			((uint32)0x00000002)
#define UDPPRINT_PTP_PORT3			((uint32)0x00000004)
#define UDPPRINT_PTP_PORT4			((uint32)0x00000008)

#define UDPPRINT_PTP_PLL1			((uint32)0x00000010)
#define UDPPRINT_PTP_ALGORITHM1		((uint32)0x00000020)
#define UDPPRINT_DELAY_MONITOR1		((uint32)0x00000040)
#define UDPPRINT_PTP_MODE_STATS1    ((uint32)0x00000080)

#define UDPPRINT_PTP_PLL2			((uint32)0x00000100)
#define UDPPRINT_PTP_ALGORITHM2		((uint32)0x00000200)
#define UDPPRINT_DELAY_MONITOR2		((uint32)0x00000400)
#define UDPPRINT_PTP_MODE_STATS2    ((uint32)0x00000800)

#define UDPPRINT_CLOCK_PLL1			((uint32)0x00001000)
#define UDPPRINT_CLOCK_PLL2			((uint32)0x00002000)

#define UDPPRINT_NODE_TIME1			((uint32)0x00010000)
#define UDPPRINT_NODE_TIME2			((uint32)0x00020000)

#define UDPPRINT_VISIBLE_MASTER		((uint32)0x00040000)

#define UDPPRINT_DAC                ((uint32)0x00080000)

#define UDPPRINT_ACS1790			((uint32)0x00100000)


/* UDP print masks */
#define UDPPRINT_CLK1_BRIEF			((uint32)0x00000001)
#define UDPPRINT_CLK1_DETAIL		((uint32)0x00000002)
#define UDPPRINT_CLK1_DEBUG			((uint32)0x00000004)
#define UDPPRINT_CLK2_BRIEF			((uint32)0x00000010)
#define UDPPRINT_CLK2_DETAIL		((uint32)0x00000020)
#define UDPPRINT_CLK2_DEBUG			((uint32)0x00000040)
#define UDPPRINT_PTP1_BRIEF			((uint32)0x00000100)
#define UDPPRINT_PTP1_DETAIL		((uint32)0x00000200)
#define UDPPRINT_PTP1_DEBUG			((uint32)0x00000400)
#define UDPPRINT_PTP2_BRIEF			((uint32)0x00001000)
#define UDPPRINT_PTP2_DETAIL		((uint32)0x00002000)
#define UDPPRINT_PTP2_DEBUG			((uint32)0x00004000)
#define UDPPRINT_NODE1_BRIEF		((uint32)0x00010000)
#define UDPPRINT_NODE1_DETAIL		((uint32)0x00020000)
#define UDPPRINT_NODE1_DEBUG		((uint32)0x00040000)
#define UDPPRINT_NODE2_BRIEF		((uint32)0x00100000)
#define UDPPRINT_NODE2_DETAIL		((uint32)0x00200000)
#define UDPPRINT_NODE2_DEBUG		((uint32)0x00400000)
#define UDPPRINT_SYSTEM_BRIEF		((uint32)0x01000000)
#define UDPPRINT_SYSTEM_DETAIL		((uint32)0x02000000)
#define UDPPRINT_SYSTEM_DEBUG		((uint32)0x04000000)

/*
 * Mask of all UDPPRINT output that can be output without encryption
 */
#define UDPPRINT_PLAINTEXT_MASK (UDPPRINT_CLK1_BRIEF | UDPPRINT_CLK1_DETAIL | \
								 UDPPRINT_CLK2_BRIEF | UDPPRINT_CLK2_DETAIL | \
								 UDPPRINT_PTP1_BRIEF | UDPPRINT_PTP1_DETAIL | \
								 UDPPRINT_PTP2_BRIEF | UDPPRINT_PTP2_DETAIL | \
								 UDPPRINT_NODE1_BRIEF | UDPPRINT_NODE1_DETAIL | \
								 UDPPRINT_NODE2_BRIEF | UDPPRINT_NODE2_DETAIL | \
								 UDPPRINT_SYSTEM_BRIEF | UDPPRINT_SYSTEM_DETAIL)



#define SMPTE_STARTING_BOUNDARY_HOPS 32
#define PTP_MIN_SM_TLV_TIMEOUT 2
#define PTP_MAX_SM_TLV_TIMEOUT 5
#define PTP_SM_TLV_TIMEOUT PTP_MAX_SM_TLV_TIMEOUT

#ifdef __cplusplus
}
#endif


#endif

