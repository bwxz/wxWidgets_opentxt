/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/TraceScaling.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_TRACE_SCALING_H
#define TT_TRACE_SCALING_H

#include <wx/dialog.h>
#include "Validation.h"

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class ttTraceWindow;
class ValidatorHost;

class ttTraceScalingDialog : public wxDialog, public ValidatorHost
{
	public:
		ttTraceScalingDialog(
			ttTraceWindow* parent,
			wxWindowID=wxID_ANY,
			const wxPoint &pos=wxDefaultPosition,
			const wxSize &size=wxDefaultSize
		);
		virtual ~ttTraceScalingDialog();
		/*bool Validate(wxWindow* control, const unsigned long &value);
		bool Validate(wxWindow* control, const signed long &value);
		bool Validate(wxWindow* control, const double &value);
		bool ValidateRelatively(wxWindow* control);*/

	protected:
		void OnXManual(wxCommandEvent &event);
		void OnXDivisions(wxCommandEvent &event);
		void OnYManual(wxCommandEvent &event);
		void OnYDivisions(wxCommandEvent &event);
		bool TransferDataToWindow();
		bool TransferDataFromWindow();
		bool Validate();
		wxCheckBox*    m_x_manual;
		wxStaticText*  m_x_min_label;
		wxTextCtrl*    m_x_min;
		wxStaticText*  m_x_max_label;
		wxTextCtrl*    m_x_max;
		wxStaticBox*   m_x_divs;
		wxRadioButton* m_x_divs_auto;
		wxRadioButton* m_x_divs_number;
		wxTextCtrl*    m_x_divs_number_field;
		wxRadioButton* m_x_divs_value;
		wxTextCtrl*    m_x_divs_value_field;
		wxCheckBox*    m_y_manual;
		wxStaticText*  m_y_min_label;
		wxTextCtrl*    m_y_min;
		wxStaticText*  m_y_max_label;
		wxTextCtrl*    m_y_max;
		wxStaticBox*   m_y_divs;
		wxRadioButton* m_y_divs_auto;
		wxRadioButton* m_y_divs_number;
		wxTextCtrl*    m_y_divs_number_field;
		wxRadioButton* m_y_divs_value;
		wxTextCtrl*    m_y_divs_value_field;
		wxStaticText*  m_y_ticks_label;
		wxRadioButton* m_y_ticks_best;
		wxRadioButton* m_y_ticks_min;
		wxRadioButton* m_y_ticks_max;
		wxCheckBox*    m_margins;

		bool           m_value_x_manual;
		double         m_value_x_maximum;
		double         m_value_x_minimum;
		unsigned short m_value_x_div_method;
		unsigned short m_value_x_div_number;
		double         m_value_x_div_value;
		bool           m_value_y_manual;
		double         m_value_y_maximum;
		double         m_value_y_minimum;
		unsigned short m_value_y_div_method;
		unsigned short m_value_y_div_number;
		double         m_value_y_div_value;
		unsigned short m_value_y_tick_method;

	private:
		static const long ID_X_MANUAL;
		static const long ID_X_DIVS_AUTO;
		static const long ID_X_DIVS_NUMBER;
		static const long ID_X_DIVS_VALUE;
		static const long ID_Y_MANUAL;
		static const long ID_Y_DIVS_AUTO;
		static const long ID_Y_DIVS_NUMBER;
		static const long ID_Y_DIVS_VALUE;
		DECLARE_CLASS(ttTraceScalingDialog)
		DECLARE_EVENT_TABLE()
};

#endif // TT_TRACE_SCALING_H