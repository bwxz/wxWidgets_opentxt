/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this
 * file is owned by Semtech Corporation (Semtech). This is an
 * unpublished work.  The content of this file must be used only for
 * the purpose for which it was supplied by Semtech or its
 * distributors. The content  of this file must not be copied or
 * disclosed unless authorised in writing by Semtech.
 */
/*
 * \file VCXCompensator.h
 *
 * The following Perforce documents are relevant:
 * 1. //topdocs/TS2/VCXO_Control/VCXO_SDS.docx [This is the most informative read]
 * 2. //topdocs/TS2/VCXO_Control/NSN_Oportunity_Study.docx
 * 3. //topdocs/TS2/VCXO_Control/VCTCXOCharacterisation.docx
 *
 * The VCXO compensator performs 3 functions.
 * 1. It acts as the s/w mux from the various PLLs to the VCXO.
 * 2. It performs the calibration of the VCXO
 * 3. Once the VCXO has been calibrated it "listens" for changes to the VCXO frequency
 *    and applies to opposing change to all other PLLs in the system to maintain their
 *    independence from the VCXO-driving PLL.
 */
#ifndef __VCXO_COMPENSATOR_H__
#define __VCXO_COMPENSATOR_H__

#include "General.h"
#include "ToPSyncInterfaceTypes.h"
#include "TimeReferenceSource.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Returns the clock ID of the PLL currently selected to drive the VCXO. If no PLL has been selected
 * to drive the PLL then the invalid clock ID "numberOfClockIds" is returned
 */
ClockId VCXOCompensator_PllDrivingVCXO(void);


/*
 * This function is called to specify which PLL will drive the VCXO. The VCXO compensation
 * is also enabled so that movements in the VCXO frequency can be cancelled out in all other phase
 * accumulators that are not driving the VCXO. This is a one shot deal... you cannot change the PLL
 * driving the VCXO once it is set.
 */
Bool VCXOCompensator_Initialise(ClockId const pll);


/*
 * If the source's clock id matches that selected to drive the VCXO, this function begins the VCXO
 * calibration. Thus, all sources, when first entering measure-frequency-offset state must call this
 * function.
 *
 * Without disturbing other software components, the DAC is set to drive the VXCO  at +25% off
 * center value. The source will then measure frequency offset and then progress to vcxo-calibration
 * stage. The transition to this stage is accomplished through the normal route in
 * TimeReferenceSource.c, namely ActionCompleteTRS(). In the VCXO-cal phase, without effecting
 * other s/w components, the DAC is set at -25% off center value and the source will do another
 * frequency offset estimation. Upon completing this, the source will then call
 * VCXOCompensator_ApplyAndCompleteOscillatorCalibrationAction().
 *
 * If the source's clock id does not match, then nothing happens.
 */
void VCXOCompensator_BeginOscillatorCalibrationIfRequired(TimeReferenceSource const *source);


/*
 * Upon completion of the vcxo-calibration phase, instead of calling the standard time reference source
 * ActionCompleteTRS() the source must call this function with the result of the second frequency offset
 * estimation. The function will then calibrate the VCXO, make the frequency offset correction and then
 * call ActionCompleteTRS() on behalf of the source, once the VCXO calibration has been made.
 */
Bool VCXOCompensator_ApplyAndCompleteOscillatorCalibrationAction(TimeReferenceSource *source, Frequency foe2);


/*
 * Function is called by the Time Reference Selector in ActionCompleteTRS() to determine whether it is
 * appropriate to make the frequency and phase jumps requested. When a node is in normal operation (i.e.,
 * not driving the VCXO) then the action should always be applied. However, when driving a VCXO the action
 * must not be applied when doing cal-a.
 */
Bool VCXOCompensator_ActionShouldBeApplied(TimeReferenceSource const *source, ActionTRS action);

Bool VCXOCompensator_CalibrationResetShouldBeApplied(TimeReferenceSource const *source, ActionTRS action);

Bool VCXOCompensator_CalibrationCompleteOrNotNeeded(void);

uint32 VCXOCompensator_GetUpdateRateMilliseconds(void);
Bool VCXOCompensator_SetUpdateRateMilliseconds(uint32 milliseconds);
Frequency VCXOCompensator_GetHardwareIntegerUnit(void);
/*
 * Function is called by the Time Reference Selector in ActionCompleteTRS() to determine whether the next
 * state after cal-a is cal-b or vcxo-cal
 */
TimeRSState VCXOCompensator_GetNextStateAfterMeasuringFrequencyCompletes(TimeReferenceSource *source, Frequency frequencyChange);
#ifdef __cplusplus
}
#endif

#endif /* ifndef __VCXO_COMPENSATOR_H__ */
