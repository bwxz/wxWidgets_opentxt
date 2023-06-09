/*
 * � Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Maths/MetricCalculation.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_METRICCALC_H
#define TT_METRICCALC_H

#include <vector>

void CalculateMetrics(const std::vector<double> &x, const std::vector<double> &y, std::vector<double> &xMtie, std::vector<double> &yMtie, std::vector<double> &xTdev, std::vector<double> &yTdev);

#endif // TT_METRICCALC_H