/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Floats.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Floats.h"

#include "Macros.h"

#include <wx/utils.h>

#include <math.h>

bool EffectivelyZero(const double &value, const int &precision)
{
	return ( int(round( value/pow(10.0,precision) )) == 0 );
}

bool EffectivelyEqual(const double &first, const double &second, const int precision)
{
	// Initial quick check
	if (first==second)
	{
		return true;
	}
	else
	{
		double firstRounded;
		double secondRounded;
		int firstMagnitude = int(floor( log10(abs( first )) ));
		int secondMagnitude = int(floor( log10(abs( second )) ));
		int magnitude = wxMax(firstMagnitude,secondMagnitude);
		firstRounded = round( first*pow(10.0,precision-magnitude) );
		secondRounded = round( second*pow(10.0,precision-magnitude) );

		return (firstRounded==secondRounded);
	}
}

bool LosingPrecision(const double value, const int precision)
{
	int magnitude = int(floor( log10(abs( value )) ));
	double unrounded = value*pow(10.0,precision-magnitude);
	double rounded = round( unrounded );
	return (rounded!=unrounded);
}