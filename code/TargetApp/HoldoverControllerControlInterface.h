/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $Workfile: HoldoverControllerControlInterface.h $
 * $Revision: 6 $
 * $Date: 3/03/09 12:08 $
 */

/**
 * \file HoldoverControllerControlInterface.h
 * This file contains the declrations of the handler routines for the Holdover Controller
 * control message set. These are messages for the configuration and management of the Time
 * Reference Source.
 */

#ifndef HOLODOVER_CONTROLLER_CONTROL_INTERFACE_H
#define HOLODOVER_CONTROLLER_CONTROL_INTERFACE_H

#include "ToPSyncInterfaceTypes.h"
#include "General.h"
#include "ToPSyncTypes.h"
#include "HoldoverController.h"

#ifdef __cplusplus
extern "C" {
#endif

ToPSyncConfigResult DoSetForceHoldover(HoldoverController* hld, Bool forceHoldover);
ToPSyncConfigResult DoGetForceHoldover(HoldoverController* hld, Bool* forcedHoldover);

ToPSyncConfigResult DoSetHoldoverDuration(HoldoverController* hld, uint32 duration);
ToPSyncConfigResult DoGetHoldoverDuration(HoldoverController* hld, uint32* duration);
ToPSyncConfigResult DoResetHoldoverData(HoldoverController* hld);
ToPSyncConfigResult DoSetHoldoverClockClass(HoldoverController* hld, ClockStratum value);
ToPSyncConfigResult DoSetReducedHoldoverClockClass(HoldoverController* hld, ClockStratum value);


//PARAMETERSDEF:HOLDOVER_CONTROLLER_SUBBLOCK_HOLDOVER_PARAMS
/*
	+ HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_DURATION, Duration value, rw, 0
	Bits[31:0]  Duration value as a signed integer.

	+ HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_RESET, Reset, w0, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= any value.

	+ HOLDOVER_CONTROLLER_PARAMS_FORCE_HOLDOVER, Disable/enable forceHoldover, rw, 0
	Bits[31:1] 	= reserved
	Bits[0] 	= 1 - ForceHoldover enabled, 0 - disabled

	+ HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_CLOCK_CLASS, clock class on entering holdover, rw, 14
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock Class from IEEE1588 Clock stratum values
				Notes: This is the value of the holdover  clock class on entering holdover

	+ HOLDOVER_CONTROLLER_PARAMS_REDUCED_HOLDOVER_CLOCK_CLASS, clock class after holdover duration, rw, 193
	Bits[31:8] 	= reserved
	Bits[7:0] 	= Clock Class from IEEE1588 Clock stratum values
				Notes: This is the value of the holdover clock class after the holdover duration has expired

*/

typedef enum
{
	HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_DURATION	= 0,
	HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_RESET		= 1,
	HOLDOVER_CONTROLLER_PARAMS_FORCE_HOLDOVER		= 2,
	HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_CLOCK_CLASS	= 3,
	HOLDOVER_CONTROLLER_PARAMS_REDUCED_HOLDOVER_CLOCK_CLASS	= 4,
	HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_TRIGGERING_NOISE_LEVEL = 5,
	HOLDOVER_CONTROLLER_PARAMS_HOLDOVER_GMID = 6,
	HOLDOVER_CONTROLLER_PARAMS_END
}mmApiHoldoverSubBlockEntryParams;

ToPSyncConfigResult mmAPIProcessSetHoldoverParams(HoldoverController* hld, uint16 startAddress, uint16 endAddress, uint32 *data);
ToPSyncConfigResult mmAPIProcessGetHoldoverParams(HoldoverController* hld, uint16 startAddress, uint16 endAddress, uint32 *data);

#ifdef __cplusplus
}
#endif

#endif
