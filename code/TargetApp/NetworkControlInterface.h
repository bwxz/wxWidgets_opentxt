/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 */
#ifndef NETWORKCONTROLINTERFACE_H_
#define NETWORKCONTROLINTERFACE_H_

#include "General.h"
#include "ToPSyncInterfaceTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * MMAPI_NETWORK_PARAMS Block Description
 ******************************************************************************/

//SUBBLOCKSDEF:MMAPI_NETWORK_PARAMS
//SUBBLOCKSDEF:MMAPI_NETWORK_PARAMS
typedef enum
{
	NETWORK_PARAMS_SUBBLOCK_ARP_CONFIG = 0,				/* Network Parameters for ARP */
	NETWORK_PARAMS_SUBBLOCK_NETWORK_CONFIG = 1,			/* Parameters for ICMP Configuration */
	NETWOK_PARAMS_SUBBLOCK_CONFIG_END
} mmApiNetworkSubBlock;

//PARAMETERSDEF:NETWORK_PARAMS_SUBBLOCK_ARP_CONFIG
/*
	+ NETWORK_PARAMS_ARP_CONFIG_FLUSH, flush the arp table, rw, 0
	  Bits[31:1] = Reserved
	  Bits[0:0] = Flush the arp table. Valid values:
		  1 - Flush IPv4 entries
*/
typedef enum
{
	NETWORK_PARAMS_ARP_CONFIG_FLUSH = 0,
	NETWORK_PARAMS_SUBBLOCK_CONFIG_END
} mmApiNetworkParamsSubBlockConfig;



//PARAMETERSDEF:NETWORK_PARAMS_SUBBLOCK_NETWORK_CONFIG
/*
	+ NETWORK_PARAMS_NETWORK_CONFIG_ENABLE_ECHO_PING, enable echo ping, rw, 1
	  Note that the stack needs to have been compiled with echo ping config enabled for this enable/disable setting to have an effect.
	  Bits[31:1] = Reserved
	  Bits[0:0] = 0 - disable echo ping
				  1 - enable echo ping
*/
typedef enum
{
	NETWORK_PARAMS_NETWORK_CONFIG_ENABLE_ECHO_PING = 0,
	NETWORK_PARAMS_TRECK_CONFIG_END
} mmApiNetworkParamsSubBlockTreckConfig;


ToPSyncConfigResult mmApiSetNetworkConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);
ToPSyncConfigResult mmApiGetNetworkConfig(uint16 subBlock, uint16 offset, uint32 length, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif /* NETWORKCONTROLINTERFACE_H_ */
