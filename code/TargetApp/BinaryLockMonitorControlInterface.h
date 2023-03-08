/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: BinaryLockMonitorControlInterface.h $
 * $Revision: 6 $
 * $Date: 3/03/09 12:08 $
 */

/**
 * \file BinaryLockMonitorControlInterface.h
 * This file contains the declrations of the handler routines for the Binary Lock Monitor
 * control message set. These are messages for the configuration and management of the
 * BinaryLockMonitor.
 */

#ifndef BINARY_LOCK_MONITOR_CONTROL_INTERFACE_H
#define BINARY_LOCK_MONITOR_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "BinaryLockMonitor.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetLockedStateThresholds(BinaryLockMonitor* blm, LockedStateThresholds const* lockedStateThresholds);
ToPSyncConfigResult DoGetLockedStateThresholds(BinaryLockMonitor* blm, LockedStateThresholds* lockedStateThresholds);
ToPSyncConfigResult DoSetForceLockedUnlockedState(BinaryLockMonitor* blm, ForceLockedUnlockedState forceLockedUnlockedState);
ToPSyncConfigResult DoGetForceLockedUnlockedState(BinaryLockMonitor* blm, ForceLockedUnlockedState *forceLockedUnlockedState);
ToPSyncConfigResult DoGetLockedState(BinaryLockMonitor* blm, Bool *isLocked);

//PARAMETERSDEF:BINARY_LOCK_MONITOR_SUBBLOCK_CONFIG_PARAMS
/*
	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_ACCEPTABLE,
	Bits[31:0]  value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_UNACCEPTABLE,
	Bits[31:0] 	value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_ACCEPTABLE,
	Bits[31:0]  value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_UNACCEPTABLE,
	Bits[31:0] 	value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_ACCEPTABLE,
	Bits[31:0]  value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_UNACCEPTABLE,
	Bits[31:0] 	value as a unsigned integer.

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_FORCE_LOCK, rw, 0
	Bits[31:2]  reserved.
	Bits[1:0]	2 = Forced to UnLocked State, 1 = Forced to Locked State, 0 = Not Forced

	+ BINARY_LOCK_MONITOR_CONFIG_PARAMS_MAINTAIN_LOCK_DURING_SOURCE_SWITCH,
	Bits[31:1]  reserved.
	Bits[0]		1 = Maintain Lock, 0 = Not Maintain Lock


*/

typedef enum
{
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_ACCEPTABLE					= 0,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_SECONDS_UNACCEPTABLE 					= 1,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_ACCEPTABLE					= 2,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_ERR_GRADIENT_UNACCEPTABLE					= 3,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_ACCEPTABLE						= 4,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_FUZZY_LOCK_UNACCEPTABLE  					= 5,

	BINARY_LOCK_MONITOR_CONFIG_PARAMS_FORCE_LOCK								= 6,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_MAINTAIN_LOCK_DURING_SOURCE_SWITCH		= 7,

	BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_UNLOCKED					= 8,
	BINARY_LOCK_MONITOR_CONFIG_PARAMS_FILTER_BANDWIDTH_LOCKED					= 9

}mmApiBinaryLockMonitorSubBlockEntryParams;

//PARAMETERSDEF:BINARY_LOCK_MONITOR_TOP_SUBBLOCK_CONFIG_PARAMS
/*
    + BINARY_LOCK_MONITOR_TOP_CONFIG_PARAMS_LOCK_PIN_OUTPUT, Config to Inverse the Binary Lock Monitor Output PIN, rw, 0
      Bits[31:1] = Reserved
      Bit[0] = 1 - Output PIN is High when binary lock is Low, and Low when binary lock is High, 0 - the other way around
*/

typedef enum
{
	BINARY_LOCK_MONITOR_TOP_CONFIG_LOCK_OUTPUT_PIN								= 1
}mmApiBinaryLockMonitorTopSubBlockEntryParams;

ToPSyncConfigResult mmAPIProcessSetBinaryLockMonitorParams(BinaryLockMonitor* blm, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetBinaryLockMonitorParams(BinaryLockMonitor* blm, uint16 startAddress, uint16 endAddress, uint32 *data);

ToPSyncConfigResult mmAPIProcessSetBinaryLockMonitorTopParams(BinaryLockMonitorTop* blmt, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetBinaryLockMonitorTopParams(BinaryLockMonitorTop* blmt, uint16 startAddress, uint16 endAddress, uint32 *data);


#ifdef __cplusplus
}
#endif

#endif
