/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Masks.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_MASKS_H
#define TT_MASKS_H

#include <wx/string.h>

/*template <class T>
struct Pair
{
	T x;
	T y;
};

template <class T>
struct ArrayPair
{
	size_t size;
	Pair<T>* values;
};*/

template <class T>
struct ArrayPair
{
	size_t size;
	T* x;
	T* y;
};

struct MetricMask
{
	wxString name;
	ArrayPair<double> mtie;
	ArrayPair<double> tdev;
	int symbol;
};

extern MetricMask g823_pdh;
extern MetricMask g823_prc;
extern MetricMask g823_sec;
extern MetricMask g823_ssu;
extern MetricMask g824_ds1;
extern MetricMask etsi_pdh;
extern MetricMask etsi_prc;
extern MetricMask etsi_sec;
extern MetricMask etsi_ssu;

#endif // TT_FLOATS_H