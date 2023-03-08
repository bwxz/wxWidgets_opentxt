#ifndef SYSTEM_CONFIGURATION_H
#define SYSTEM_CONFIGURATION_H

#include "ToPSyncTypes.h"
#include "ControlLoopConfiguration.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PTP_DOMAIN
	#define PTP_DOMAIN 0
#endif

#define DEFAULT_PACKET_ANALYSER_ALGORITHM	stableFloor
#define DEFAULT_LOCK_DETECTOR_MODE			DEFAULT_PACKET_ANALYSER_ALGORITHM

#define DEFAULT_FREQUENCY_ONLY_ENABLE_STATUS			FALSE
#define DEFAULT_FREQUENCY_ONLY_CLAMP_THRESH_HI			1.0e-01f
#define DEFAULT_FREQUENCY_ONLY_USE_DIRECTION			both;

#define MINIMUM_TRAFFIC_COMPRESSING_COEF				0.0f
#define MAXIMUM_TRAFFIC_COMPRESSING_COEF				7.0f
#define DEFAULT_TRAFFIC_COMPRESSING_COEF				3.0f
#define MINIMUM_TRAFFIC_COMPRESS_PROTECT_THRESH_HI		1.00e-07f
#define MAXIMUM_TRAFFIC_COMPRESS_PROTECT_THRESH_HI		5.00e-07f
#define DEFAULT_TRAFFIC_COMPRESS_PROTECT_THRESH_HI		2.50e-07f
#define DEFAULT_TRAFFIC_COMPRESS_PROTECT_THRESH_LO		1.00e-07f

#define MINIMUM_SLIDING_WINDOW_SIZE_IN_SEC				5
#define MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC				60

#define MINIMUM_SLIDING_WINDOW_IN_SAMPLE					45
#define MINIMUM_SLIDING_WINDOW_IN_SAMPLE_FAST_CALIBRATION	3

#define DEFAULT_MAX_SLIDING_WINDOW_SIZE_IN_SEC			MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC
#define EBC_MAXIMUM_SLIDING_WINDOW_SIZE_IN_SEC			50			//maximum sliding window size in eBC mode

#define DEFAULT_NOISE_COMPENSATION_ENABLE_STATUS		TRUE
#define DEFAULT_TRAFFIC_ADAPTIVE_FILTER_ENABLE_STATUS	TRUE
#define DEFAULT_PHTH_SELECTION_ENABLE_STATUS			TRUE

//paremeter relating to median delay filter
#define MAX_MEDIAN_DELAY_NUMBER_SAMPLE					240			//equivalent to 30 second search window, given 8 sample per second
#define MIN_MEDIAN_DELAY_NUMBER_SAMPLE					80			//equivalent to 10 second search window, given 8 sample per second
#define MAX_MEDIAN_DELAY_MEDIAN_POINT					0.75f
#define MIN_MEDIAN_DELAY_MEDIAN_POINT					0.0f
#define DEFAULT_MEDIAN_DELAY_STATE						medianDelayAdaptive

//parameter relating to sparse delay filter
#define MIN_SPARSE_DELAY_JUMP_IN_SECOND					1.0e-06f
#define DEFAULT_SPARSE_DELAY_JUMP_IN_SECOND				4.0e-06f
#define MIN_SPARSE_DELAY_RATE_PER_100_SECONDS			1
#define MAX_SPARSE_DELAY_RATE_PER_100_SECONDS			10
#define DEFAULT_SPARSE_DELAY_RATE_PER_100_SECONDS		4
#define MARGIN_FOR_AFTER_SAMPLE_SKIP_TIMER				2
#define DEFAULT_TIMER_AFTER_SKIP_SAMPLE					((100/DEFAULT_SPARSE_DELAY_RATE_PER_100_SECONDS+MARGIN_FOR_AFTER_SAMPLE_SKIP_TIMER)*SLOW_TICKS_PER_SECOND);

#define DISABLE_DEEPLOCK


//the following lock detector noise floor will be used for dpa algorithm
#define LOCK_DETECTION_NOISE_FLOOR	1.0e-07

#define DEFAULT_PTP_PORT 0
#define DEFAULT_PHYSICAL_PORT_ENTITY 0 //This is not the same as GetPhysicalPort()
#define DEFAULT_PTP_PROTOCOL udp4
#define DEFAULT_PTP_PORT_ADDRESSING_MODE asAppropriate
#define DEFAULT_INTERFACE_RATE (100000000/8) //100M in byte/sec
#define DEFAULT_PTP_PORT_MASTERS_OF_INTEREST	2 // this is the number of masters which which the port will attempt to establish communication. Must not be less than 1
#define DEFAULT_VIRTUAL_PORT 0
#define DEFAULT_MHOME_INDEX	0

#define NUMBER_OF_ACTIVE_PHYSICAL_PORTS 2	// Number of active physical interfaces
#define NUMBER_OF_PTP_MASTER_PORTS 2
#define NUMBER_OF_PTP_SLAVE_PORTS 2
#define NUMBER_OF_PTP_PORTS 		(NUMBER_OF_PTP_MASTER_PORTS + NUMBER_OF_PTP_SLAVE_PORTS)
#define INDEX_OF_FIRST_SLAVE_PORT 	(0)
#define INDEX_OF_FIRST_MASTER_PORT 	(NUMBER_OF_PTP_SLAVE_PORTS)
#define NUMBER_OF_CURRENT_MASTERS 	(NUMBER_OF_PTP_SLAVE_PORTS)
#define NUMBER_OF_CLOCK_PATHS 2

#define NUMBER_OF_TOD_INTERFACES 2
#define NUMBER_OF_CLOCK_PLLS 2 // 1 PPS etc
#define NUMBER_OF_FREQUENCY_OUTPUTS 16
#define NUMBER_OF_1PPS_OUTPUTS_USED 4 // 4 exist but only two are used (**do not change as it used for Phase Clock Control**)
#define NUMBER_OF_1PPS_OUTPUTS_ACTIVE 2

#define INDEX_OF_CLOCK_INPUTS_FOR_RAC		(0)
#define INDEX_OF_CURRENT_MASTERS_FOR_RAC	(0)

#define DEFAULT_CLOCK_PATH 0
#define DEFAULT_NETWORK_TIMESTAMPER 0
#define DEFAULT_CLOCK_TIMESTAMP_CONTROLLER 0
#define DEFAULT_1PPS_INPUT 0 // Index of first clock timestamper
#define DEFAULT_PTP_PORT 0
#define PPSnS_OUTPUT 1 //This PPS output is configurable to be PPnS, where n may be greater than 1

//want input clocks for ts2 to use clock 1 (not 0 as per ts1)
#define DEFAULT_1PPS_INPUT_FOR_9520_PNP 1

#define ACS9528_DEFAULT_IPCLK0_FREQ	(1)
#define ACS9528_DEFAULT_IPCLK1_FREQ	(25000000)
#define ACS9528_DEFAULT_IPCLK2_FREQ	(25000000)
#define ACS9528_DEFAULT_CLKPLL1_IPCLK	(0)
#define ACS9528_DEFAULT_CLKPLL2_IPCLK	(1)

//Time measurement parameters
#define MII_CLOCK_PERIOD ((Signal)40e-9f)
#define TIMESTAMP_CLOCK_PERIOD 8e-9f //this corresponds to the timestamp phase reference clock period in the ASIC spec.
#define NETWORK_TIME_MEASUREMENT_GRANULARITY MII_CLOCK_PERIOD
#define CLOCK_TIME_MEASUREMENT_GRANULARITY TIMESTAMP_CLOCK_PERIOD

#define TIME_SERVER_TICK_PERIOD ((ElapsedTime) 3.90625e-3) /* At 1/256 ticks per second this is the period */
#define TIME_SERVER_TICKS_PER_SECOND ((uint32) (1.0/ TIME_SERVER_TICK_PERIOD + 0.5))
#define LCD_UPDATE_PERIOD ((ElapsedTime) 100e-3)
#define PRINT_CONTROLLER_TICK_PERIOD_SECS ((ElapsedTime) 250e-3)
#define ROUTER_CONTROLLER_TICK_PERIOD_SECS ((ElapsedTime) 2)
#define ALARM_PIN_TICK_PERIOD_SECS ((ElapsedTime) 250e-3)
#define ETHERNET_RATE_CHECK_PERIOD_SECS	((ElapsedTime) 250e-3)
#define RECEIVE_QUEUE_TICK_PERIOD_SECS ((ElapsedTime) 250e-3)
#define TRECK_TICK_PERIOD_SEC ((ElapsedTime)20e-3)
#define USER_DATA_TICK_PERIOD_SECS ((ElapsedTime) 250e-3)

#define PRINT_CONTROLLER_UDP_PORT 323
#define EVENT_MESSAGE_CONTROLLER_UDP_PORT 325

// max user data is 64 words (=256 bytes). Signalling header is 44 bytes, plus rest of user data tlv=10bytes
//so the below needs to be at least 310 bytes.
#define MAX_MESSAGE_SIZE 320  //including timestamp bytes
// system rejects messages that equal or exceed MAX_MESSAGE_SIZE

// density packet acceptor values
#define DPA_MIN_NUMBER_OF_LISTS 2
#define DPA_MAX_NUMBER_OF_LISTS 20
#define DPA_DEFAULT_NUMBER_OF_LISTS 10


//Estimates
#define MAX_TRANSMIT_DELAY_SECONDS 2e-3
#define MAX_TRANSMIT_DELAY_NANOSECONDS ((uint32) (MAX_TRANSMIT_DELAY_SECONDS * NANO_SECONDS_PER_SECOND))

#define NUMBER_OF_FOREIGN_MASTERS 7
#define NUMBER_OF_VISIBLE_MASTERS 10

#if NUMBER_OF_VISIBLE_MASTERS > 32
	#error FindVisibleMasterMask(..) assumes _NUMBER_OF_VISIBLE_MASTERS is smaller than word size
#endif

#ifndef MAX_DELAY_REQUEST_RATE
	#define MAX_DELAY_REQUEST_RATE 128
#endif

#ifndef USE_DHCP
	#define USE_DHCP 1
#endif

#define SLOW_TICK_PERIOD_NS 250000000  // 250ms
#define SLOW_TICK_PERIOD_MS 250
#define SLOW_TICK_PERIOD_SECS ((ElapsedTime) SLOW_TICK_PERIOD_NS / NANO_SECONDS_PER_SECOND)
#define SLOW_TICK_PERIOD_TICKS ((uint)(SLOW_TICK_PERIOD_SECS / TIME_SERVER_TICK_PERIOD + 0.5f))
#define SLOW_TICKS_PER_SECOND ((uint) (NANO_SECONDS_PER_SECOND/SLOW_TICK_PERIOD_NS))

#define CLOCK_PLL_FASTER_UPDATE_PERIOD (TIME_SERVER_TICK_PERIOD * 8)
#define CLOCK_PLL_FASTER_UPDATE_TICKS ((uint)(CLOCK_PLL_FASTER_UPDATE_PERIOD / TIME_SERVER_TICK_PERIOD + 0.5f))

#define NODE_TIME_FASTER_UPDATE_PERIOD (TIME_SERVER_TICK_PERIOD * 8)
#define NODE_TIME_FASTER_UPDATE_TICKS ((uint)(NODE_TIME_FASTER_UPDATE_PERIOD / TIME_SERVER_TICK_PERIOD + 0.5f))

#if !defined(PHYSICAL_PORT_CONFIGURATION_PORT0)
	#define PHYSICAL_PORT_CONFIGURATION_PORT0 	PHYSICAL_PORT_CONFIGURATION_PORT_ACTIVE
#endif

#if !defined(PHYSICAL_PORT_CONFIGURATION_PORT1)
	#define PHYSICAL_PORT_CONFIGURATION_PORT1 	0
#endif

#if !defined(VLAN_ID_PORT0)
	#define VLAN_ID_PORT0 	((uint32)0)
#endif

#if !defined(VLAN_ID_PORT1)
	#define VLAN_ID_PORT1 	((uint32)0)
#endif

#if !defined(IP4_IS_CONFIGURED_PORT00)
	#define IP4_IS_CONFIGURED_PORT00 	((uint32)0x1)
#endif

#if !defined(IP4_IS_CONFIGURED_PORT10)
	#define IP4_IS_CONFIGURED_PORT10 	((uint32)0)
#endif

#ifndef IP4_USE_DHCP_PORT00
	#define IP4_USE_DHCP_PORT00 USE_DHCP
#endif

#ifndef IP4_USE_DHCP_PORT10
	#define IP4_USE_DHCP_PORT10 USE_DHCP
#endif

#if IP4_USE_DHCP_PORT00 == 0
	#if !defined(IP4_ADDR_PORT000)
		#define IP4_ADDR_PORT000		((uint32) 0xc0a802C9L)	 // 192.168.2.201
	#endif
	#if !defined(IP4_SUBNET_MASK_PORT000)
		#define IP4_SUBNET_MASK_PORT000 	((uint32) 0xFFFFFF00L)
	#endif
#else
	#if !defined(IP4_ADDR_PORT000)
	 	#define IP4_ADDR_PORT000		((uint32) 0)
	#endif
	#if !defined(IP4_SUBNET_MASK_PORT000)
	 	#define IP4_SUBNET_MASK_PORT000 ((uint32) 0)
	#endif
#endif

#if !defined(IP4_DEFAULT_GATEWAY_ADDR_PORT00)
	#define IP4_DEFAULT_GATEWAY_ADDR_PORT00 0
#endif

#if IP4_USE_DHCP_PORT10 == 0
	#if !defined(IP4_ADDR_PORT10)
		#define IP4_ADDR_PORT100		((uint32) 0xc0a802CAL)	 // 192.168.2.202
	#endif
	#if !defined(IP4_SUBNET_MASK_PORT10)
		#define IP4_SUBNET_MASK_PORT100	((uint32) 0xFFFFFF00L)
	#endif
#else
	#if !defined(IP4_ADDR_PORT100)
	 	#define IP4_ADDR_PORT100		((uint32) 0)
	#endif
	#if !defined(IP4_SUBNET_MASK_PORT100)
	 	#define IP4_SUBNET_MASK_PORT100 ((uint32) 0)
	#endif
#endif

#if !defined(IP4_DEFAULT_GATEWAY_ADDR_PORT10)
	#define IP4_DEFAULT_GATEWAY_ADDR_PORT10 0
#endif


#if !defined(DHCP_LEASE_LENGTH)
	#define DHCP_LEASE_LENGTH (60 * 60 * 24 * 7)
#endif

#if !defined(IP6_CONFIGURED_PORT00)
	#define IP6_CONFIGURED_PORT00	 	((uint32)0)
#endif

#if !defined(IP6_CONFIGURED_PORT10)
	#define IP6_CONFIGURED_PORT10 		((uint32)0)
#endif

#if !defined(IP6_ADDR_ALLOCATION_PORT00)
	#define	IP6_ADDR_ALLOCATION_PORT00	IP6_ADDR_AUTO
#endif

#if !defined(IP6_ADDR_ALLOCATION_PORT10)
	#define	IP6_ADDR_ALLOCATION_PORT10	IP6_ADDR_AUTO
#endif

#if !defined(IP6_ADDR_PORT000)
	#define IP6_ADDR_PORT000	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#endif

#if !defined(IP6_ADDR_PORT100)
	#define IP6_ADDR_PORT100	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#endif

#if !defined(IP6_DEFAULT_PREFIX_LENGTH)
	#define IP6_DEFAULT_PREFIX_LENGTH 64
#endif

#if !defined(IP6_PREFIX_LENGTH_PORT000)
	#define IP6_PREFIX_LENGTH_PORT000 IP6_DEFAULT_PREFIX_LENGTH
#endif

#if !defined(IP6_PREFIX_LENGTH_PORT100)
	#define IP6_PREFIX_LENGTH_PORT100 IP6_DEFAULT_PREFIX_LENGTH
#endif

#if !defined(IP6_DEFAULT_GATEWAY_PORT0)
	#define IP6_DEFAULT_GATEWAY_PORT0 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#endif

#if !defined(IP6_DEFAULT_GATEWAY_PORT1)
	#define IP6_DEFAULT_GATEWAY_PORT1 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#endif

#ifndef WORST_STRATUM_THAT_CAN_BE_MASTER
	#define WORST_STRATUM_THAT_CAN_BE_MASTER stratum4
#endif

#ifndef LOG_MAX_TIME_UPDATE_PERIOD
	#define LOG_MAX_TIME_UPDATE_PERIOD 4  // == log of  MAX_TIME_UPDATE_PERIOD (the two values MUST match)
#endif

#ifndef MAX_TIME_UPDATE_PERIOD
	#define MAX_TIME_UPDATE_PERIOD 16 // == antilog of  LOG_MAX_TIME_UPDATE_PERIOD (the two values MUST match)
#endif

#define PLL_MAX_OFFSET 1e-3f
#define COARSE_ALIGNMENT_THRESHOLD 2
#define MEAN_ACCEPTANCE_MIN 0.02f
#define DELAY_REQUEST_RESPONSE_TIME_SECS 1.0f
#define DELAY_REQUEST_RESPONSE_TIME_TICKS (DELAY_REQUEST_RESPONSE_TIME_SECS/SLOW_TICK_PERIOD_SECS + 0.99999999f)
#define SYNC_TO_FOLLOWUP_TIME_TICKS 4
#define MAX_STORED_DELAY_REQUEST_MESSAGES  (MAX_DELAY_REQUEST_RATE * DELAY_REQUEST_RESPONSE_TIME_SECS + 0.9f)
#define MAX_STORED_SYNC_MESSAGES 8
#define MAX_STORED_DELAY_REQUEST_RX_TIMES  8

#define EXTERNAL_TIMESTAMPING_HOLDOFF_TIME   10
#define EXTERNAL_TIMESTAMPING_HOLDOFF_TICKS  ((EXTERNAL_TIMESTAMPING_HOLDOFF_TIME/SLOW_TICK_PERIOD_SECS)  + 0.9f)

#define MAX_DLY_RQ_MESSAGES_PER_TICK 100
#define MAX_PACKETS_RECEIVED_BETWEEN_IDLE_TASK_RUNS 1000

#define DEFAULT_MAX_FREQUENCY_OFFSET ((Frequency) 25e-6)	//of this node w.r.t. local oscillator

//Density packet acceptor size definitions
#define DPA_DEFAULT_MAX_NUMBER_OF_RECORDS 2000
#define DPA_DEFAULT_MIN_TARGET_NUMBER_OF_RECORDS 200
#define DPA_MIN_VALID_NUMBER_OF_RECORDS DPA_MIN_TARGET_NUMBER_OF_RECORDS
#define DPA_MAX_TIME_TO_VALID 40.0
#define DPA_MAX_UNLOCKED_TIME_STORAGE 120.0 // max time that an locked system stores data

#define DPA_DEFAULT_MINIMUM_LOCK_VALUE 0.6f
	// when locked is below this value the Acceptor stores 'minimumElements'
	// when locked is above this value the Acceptor stores more elements pro rata to maximumElements
#define DPA_DEFAULT_MAXIMUM_LOCK_VALUE 0.95f
	// when locked is above this value the Acceptor stores 'maximumElements'
	// when locked is above this value the Acceptor stores fewer elements pro rata to minimumElements

#define DPA_DEFAULT_MAX_INPUT_NOISE 1.5e-6
	// the value of input noise that will set the Acceptor to its maximum length

#define FREQUENCY_MEASUREMENT_TIME ((ElapsedTime) 30.0) // time over which the initial frequency offset is measured
#define FREQUENCY_MEASUREMENT_TIME_FAST_CALIBRATION ((ElapsedTime) 3.0) // time over which the initial frequency offset is measured for fast calibration
#define MIN_FREQUENCY_MEASUREMENT_PACKETS 16 // min number of packets over which the initial frequency offset is measured

#define CLOCK_LOCKING_FREQUENCY_MEASUREMENT_TIME   10.0f 	/**< Default frequency measurement period for 1PPS locking */

#define FTA_NOISY_ENVIRONMENT_LIMIT 2.0e-6   // when the measured noise is above this value, the enviroment is considered noisy.

#define MAX_FILTER_CHAIN_LENGTH 2

#if MAX_FILTER_CHAIN_LENGTH < NETWORK_FILTER_CHAIN_LENGTH
	#error _MAX_FILTER_CHAIN_LENGTH must not be less than _NETWORK_FILTER_CHAIN_LENGTH
#endif

#define FREQ_AVERAGER_UNLOCKED_FILTER_BANDWIDTH				(NETWORK_UNLOCKED_PLL_FILTER_BANDWIDTH/10)
#define FREQ_AVERAGER_LOCKED_FILTER_BANDWIDTH				(NETWORK_LOCKED_PLL_FILTER_BANDWIDTH/10)
#define LOCK_MONITOR_UNLOCKED_BANDWIDTH						(NETWORK_UNLOCKED_PLL_FILTER_BANDWIDTH/10)
#define LOCK_MONITOR_LOCKED_BANDWIDTH						(NETWORK_LOCKED_PLL_FILTER_BANDWIDTH/10)
#define UNSELECTED_NETWORK_SOURCE_FILTER_BANDWIDTH_OPEN		(NETWORK_UNLOCKED_PLL_FILTER_BANDWIDTH/2)
#define UNSELECTED_NETWORK_SOURCE_FILTER_BANDWIDTH_CLOSED	(NETWORK_LOCKED_PLL_FILTER_BANDWIDTH/10)
#define UNSELECTED_CLOCK_SOURCE_FILTER_BANDWIDTH_OPEN		(CLOCK_UNLOCKED_FILTER_BANDWIDTH/1)
#define UNSELECTED_CLOCK_SOURCE_FILTER_BANDWIDTH_CLOSED		(CLOCK_LOCKED_FILTER_BANDWIDTH/3)

// Lock parameters
#define FC_VN_LOCK_THRESHOLD 0.7f

// Noise analyser
#define NOISE_ANALYSER_OPEN_BANDWIDTH		0.1f
#define NOISE_ANALYSER_CLOSED_BANDWIDTH		0.01f
#define NUMBER_OF_NOISE_ANALYSER_FILTERS	1
#define DEFAULT_NOISE_ALARM_ON_THRESHOLD	500e-6
#define DEFAULT_NOISE_ALARM_OFF_THRESHOLD	100e-6


#define FC_NOISY_ENVIRONMENT_LIMIT 1.0e-7
// when the measured noise is above this value, the enviroment is considered noisy.

/* Binary lock parameters */

#define BINARY_LOCK_PHASE_GOOD ((Signal) 1e-6)
#define BINARY_LOCK_PHASE_BAD ((Signal) 5e-6)
#define BINARY_LOCK_GRADIENT_GOOD ((Frequency) 1e-9)
#define BINARY_LOCK_GRADIENT_BAD ((Frequency) 2.5e-9)
#define BINARY_LOCK_FUZZY_GOOD 0.5f
#define BINARY_LOCK_FUZZY_BAD 0.25f

#define MAX_LOG_ANNOUNCE_PERIOD 6
#define MIN_LOG_ANNOUNCE_PERIOD -4
#define MAX_LOG_TIMING_PERIOD 4
#define MIN_LOG_TIMING_PERIOD -7
#define MEAN_UNICAST_ANNOUNCE_CLIENT_RATE 2
#ifdef TS2D_ASIC
#define CLIENT_RATE_LIMIT (256 * 32)	// or equivalent (64 x 128)
#else
#define CLIENT_RATE_LIMIT (80 * 32)		// spec is to handle 80 slaves at 32/sec
#endif
#define MEAN_UNICAST_TIMING_CLIENT_RATE ((CLIENT_RATE_LIMIT) / (MAX_UNICAST_TIMING_GRANTS))
#define MAX_LOG_PATH_DELAY_PERIOD MAX_LOG_TIMING_PERIOD
/* Unicast negotiation parameters */

//Master Unicast negotiation parameters
#ifdef TS2D_ASIC
#define MAX_UNICAST_ANNOUNCE_GRANTS 1024
#else
#define MAX_UNICAST_ANNOUNCE_GRANTS 128
#endif
#define MAX_UNICAST_TIMING_GRANTS MAX_UNICAST_ANNOUNCE_GRANTS
#define MAX_UNICAST_ANNOUNCE_GRANT_RATE (MAX_UNICAST_ANNOUNCE_GRANTS * MEAN_UNICAST_ANNOUNCE_CLIENT_RATE)
#define MAX_UNICAST_SYNC_GRANT_RATE (MAX_UNICAST_TIMING_GRANTS * MEAN_UNICAST_TIMING_CLIENT_RATE)
#define MAX_GRANT_DURATION 300
#define MAX_ACCEPTABLE_MASTERS 10
#define MAX_ACCEPTABLE_SLAVES MAX_UNICAST_ANNOUNCE_GRANTS

// Multicast parameters
#define DEFAULT_MULTICAST_ANNOUNCE_LOG_PERIOD 1
#define DEFAULT_MULTICAST_TIMING_LOG_PERIOD 1

// Slave Unicast negotiation parameters
#define DEFAULT_UNICAST_GRANT_REQUEST_DURATION 250
#define DEFAULT_UNICAST_REQUEST_REPEAT_THRESHOLD 20
#define DEFAULT_UNICAST_REQUEST_REPEAT_PERIOD 2
#define LOG_PERIOD_ACCEPTABLE_MARGIN ((LogMessagePeriod)2)

#define DEFAULT_UNICAST_ANNOUNCE_LOG_PERIOD_REQUESTED ((LogMessagePeriod)1)

#define DEFAULT_UNICAST_TIMING_LOG_PERIOD_REQUESTED ((LogMessagePeriod)-5)

#define ANNOUNCE_REQUEST_POLL_PERIOD 1.0


/* Holdover parameters */
#define HOLDOVER_MAX_AVERAGING_PERIOD (6 * 60 * 60)
#define HOLDOVER_DEFAULT_AVERAGING_PERIOD (2 * 60 * 60)
#define HOLDOVER_MIN_AVERAGING_PERIOD 30
#define HOLDOVER_TIME_TO_FULLY_VALID (2 * 60)
#define DEFAULT_HOLDOVER_DURATION ((ElapsedTime)(60 * 60)) //1 hour
#define DEFAULT_HOLDOVER_QUALITY_REDUCTION 10
#define HOLDOVER_DEFAULT_PLL_ID	mainPLL

// Assumed quality of 1PPS
#define ONE_PPS_CLOCK_STRATUM                      primaryReference
#define ONE_PPS_CLOCK_IDENTITY                     atom
#define ONE_PPS_CLOCK_LOG_VARIANCE                 0
#define DEFAULT_ASSUMED_CLOCK_INPUT_NOISE			100e-9

//Hybrid time controller
#define HTC_SAMPLES_TO_VALID (200)
#define HTC_MAX_HISTORY_SECS (25 * 60 * 60) //one day + 1 hour
#define HTC_MAX_TIME_GRANULARITY_SECS (15 * 60)  // max time between times that old delays are retired
#define HTC_DEFAULT_HISTORY_SECS HTC_MAX_HISTORY_SECS


//leap second warning in secs
#define LEAP_SECOND_WARNING_SECS (24*60*60) //one day


/******************************************************************************************
  Start of System dependent constants
******************************************************************************************/
// Common
#define DEFAULT_PULSE_WIDTH_1_PPS_NS 	100000000UL	  // 0.1 secs
#define MAX_PULSE_WIDTH_NS				400000000UL   // 0.4 secs
#define TOD_SEND_WAIT_SECS				0.1f
#define TOD_SEND_WAIT_TICKS				((uint32) (TOD_SEND_WAIT_SECS * TIME_SERVER_TICKS_PER_SECOND))

#define BINARY_LOCK_MONITOR_FILTER_BANDWIDTH_DIVISION 10
#define BINARY_LOCK_MONITOR_FILTER_CHAIN_LENGTH 1

#define LOW_NOISE_MAX 15e-6f
#define HIGH_NOISE_MIN 50e-6f

#define FINAL_LIST_DENSITY_RATIO 0.2f


// SETS configuration
#define SETS_TOP_SYNC_INPUT 8 	// I9


#define SETS_MASTER_REF_INPUT_PRI 2 	// I3
#define SETS_MASTER_REF_INPUT_10MHz	11 //I12
#define SETS_MASTER_REF_INPUT_8KHz	7 //I8

#define SETS_TOP_SYNC_PRIORITY 2
#define SETS_MASTER_REF_PRIORITY 1

#define SETS_TOPSYNC_OUTPUT_ASIC 0	//T01

#define SETS_INPUT_DIVISION_RATIO 1250  //10MHz

#define EVAL_BOARD_SETS_PRIMARY_RATE_OUTPUT 2 //T03
#define PRODUCT_19_44MHZ_OUTPUT 2
#define PRODUCT_155MHZ_OUTPUT_A 5
#define PRODUCT_155MHZ_OUTPUT_B 6

//General
#define GRANDMASTER_MAX_STEPS_REMOVED 200

#ifndef USE_LCD
	#define USE_LCD 1
#endif

#define MAX_UDPPRINTF_MESSAGE_SIZE 1000 //Must be smaller than value in udpprint and toplogger (== 1024)


#ifndef UART_0_ENABLED
	#define UART_0_ENABLED 1
#endif

#ifndef UART_1_ENABLED
	#define UART_1_ENABLED 1
#endif

#ifndef TOD_UART_BAUD_RATE
	#define TOD_UART_BAUD_RATE BAUD_RATE_4800	//default baud rate for NMEA
#endif

#ifndef DEBUG_UART__BAUD_RATE
	#define DEBUG_UART_BAUD_RATE BAUD_RATE_115200 //default baud rate for TS2D debug
#endif

#ifndef TOD_UART_PORT
	#define TOD_UART_PORT 0
#endif

#ifndef TOD_TIME_CODE
	#define TOD_TIME_CODE NMEA_0183_TIME_CODE
#endif

#define PRINT_CONTROLLER_UART_PORT 1
	
#define DEFAULT_TOD_MSG_PERSISTANCE 2
#define DEFAULT_TOD_MAX_MISSED_INPUTS 5

#ifndef UART_BUFFER_POLL_PERIOD
	#define UART_BUFFER_POLL_PERIOD	100e-3
#endif

#define TX_ANNOUNCE_PCBS (MAX_UNICAST_ANNOUNCE_GRANT_RATE / TIME_SERVER_TICKS_PER_SECOND + 1) //round up
#ifdef TS2D_ASIC
#define TX_SYNC_PCBS 128
#define TX_DELAY_RESPONSE_PCBS 64
#else
#define TX_SYNC_PCBS 20
#define TX_DELAY_RESPONSE_PCBS 10
#endif
#define TX_EVENT_PTP_PCBS 6
#define TX_GENERAL_PTP_PCBS 4 // to allow for non-event PTP messages

#ifdef TS2D_ASIC
#define DELAY_REQUEST_Q_SIZE 256
#define STACK_BYPASS_Q_SIZE 80
#else
#define DELAY_REQUEST_Q_SIZE 40
#define STACK_BYPASS_Q_SIZE 25
#endif
#define EVENT_MESSSAGE_TX_Q_SIZE (TX_SYNC_PCBS + TX_EVENT_PTP_PCBS)

//frequencies for software clock locking
typedef enum { CLOCK_2K, CLOCK_8K, CLOCK_1PPS } CLClockInputFrequency;

#define MAX_UDP_SOCKETS ((NUMBER_OF_PTP_PORTS * 2) + 3)
	// Each PTP port requires 1 for general 1 for event and each ToPSync requires 1 for udpprint, 1 for control, 1 for alarm message

//Path delay
#define PATH_DELAY_IP_MULTICAST_ADDRESS 0xE000006B  //224.0.0.107
#define PATH_DELAY_IPV6_MULTICAST_ADDRESS 	{ 0xFF, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6B }
#ifdef TOPSYNC_PATH_DELAY_TEST_SETUP
/*
 * The multicast mac address used for path delay packets is 01-08-C2-00-00-0E. This is shared with the
 * Link-Layer Discovery Protocol and these packets may not be forwarded by a switch. For bench testing
 * with a switch define PATH_DLEAY_TEST_SETUP and use 01-1B-19-00-00-00. See IEEE 1588 specification
 * Annex F.
 */
#define PATH_DELAY_MAC_MULTICAST_ADDRESS_3MSB 0x011B19
#define PATH_DELAY_MAC_MULTICAST_ADDRESS_3LSB 0x000000
#else
#define PATH_DELAY_MAC_MULTICAST_ADDRESS_3MSB 0x0180C2
#define PATH_DELAY_MAC_MULTICAST_ADDRESS_3LSB 0x00000E
#endif

//defaults for initialSystemConfiguration
#define DEFAULT_SUBDOMAIN_IP_ADDRESS  		0xE0000181UL
#define DEFAULT_PTP_IPV6_MULTICAST_ADDRESS	{ 0xFF, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1, 0x81 }
#define DEFAULT_CONTROL_INTERFACE_TYPE 		EthernetIpInterface
#define DEFAULT_UPLOAD_INTERFACE_TYPE 		SpiInterface
#define DEFAULT_UPLOAD_INTERFACE_ID			0
#define UDP_MANAGEMENT_PORT_NUMBER			2000

#define SECURITY_KEY 						0
#ifdef MDIO_ENABLE
/*
 * The TS2D FPGA board sets the ethernet phy to be 10MHz and half-duplex. 
 * MDIO is not used by default because there have been issues in customer 
 * configurations that use different ethernet phys. However it is tricky
 * to modify the TS2D FPGA board so MDIO is enabled for the FPGA and it
 * will auto-negotiate 100MHz and full-duplex when connected to an appropriate 
 * network.
 */
#define MDIO_AVAILABLE 						TRUE
#else
#define MDIO_AVAILABLE 						FALSE
#endif
#define LOCATION_IDENTIFIER 				0
#define EVENT_TOS							0xB8
#define GENERAL_TOS							0x00
#define TCP_UPLOAD_PORT_NUMBER				1000

#define DEFAULT_NETWORK_CONTROL_INTERFACE_PROTOCOL udp4
#define DEFAULT_NETWORK_DEBUG_INTERFACE_PROTOCOL udp4

#define DEFAULT_ALARM_MESSAGE_CONTROLLER_INTERFACE_PROTOCOL udp4

#define EVENT_RESTART_PERIOD 1
#define EVENT_RESTART_DURATION (15*60)


#if defined(_ARC) && !defined(APP_SOFTWARE_VERSION)
	#error "Software version not specified."
#endif




#ifdef __cplusplus
}
#endif

#endif
