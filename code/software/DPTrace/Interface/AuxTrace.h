/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/AuxTrace.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_AUXTRACE_H
#define TT_AUXTRACE_H

#include "Trace.h"

#include "Masks.h"

/*******************
  ttAuxTraceWindow
*******************/

class ttAuxTraceWindow : public ttTraceWindow
{
	public:
		ttAuxTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex);
		~ttAuxTraceWindow();
		void PrepareForDestruction();
		void DoRender();
		bool WaitingForData();
		void Recalculate(const std::vector<double> &x, const std::vector<double> &y);
		void ResetMasks();
		void AddMask(const MetricMask* mask);

	protected:
		void OnMouse(wxMouseEvent &event);
		bool CalculateScaleX(bool* newIncluded, unsigned long* all_start, unsigned long* all_count, unsigned long* new_start, unsigned long* new_count);
		bool CalculateScaleY();
		std::vector<const MetricMask*> m_masks;
		virtual double* GetMaskX(const MetricMask* mask) const = 0;
		virtual double* GetMaskY(const MetricMask* mask) const = 0;
		virtual size_t GetMaskSize(const MetricMask* mask) const = 0;
	
		DECLARE_EVENT_TABLE()
};

/********************
  ttMtieTraceWindow
********************/

class ttMtieTraceWindow : public ttAuxTraceWindow
{
	public:
		ttMtieTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex);
		~ttMtieTraceWindow();

	protected:
		double* GetMaskX(const MetricMask* mask) const;
		double* GetMaskY(const MetricMask* mask) const;
		size_t GetMaskSize(const MetricMask* mask) const;
};

/********************
  ttTdevTraceWindow
********************/

class ttTdevTraceWindow : public ttAuxTraceWindow
{
	public:
		ttTdevTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex);
		~ttTdevTraceWindow();

	protected:
		double* GetMaskX(const MetricMask* mask) const;
		double* GetMaskY(const MetricMask* mask) const;
		size_t GetMaskSize(const MetricMask* mask) const;
};

#endif // TT_AUXTRACE_H