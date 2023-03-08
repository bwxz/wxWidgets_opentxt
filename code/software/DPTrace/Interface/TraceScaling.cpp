/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/TraceScaling.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "TraceScaling.h"

#include "Floats.h"
#include "Macros.h"
#include "Main.h"
#include "Trace.h"
#include "Workarea.h"
#include "wxStaticHeading.h"

#include <wx/icon.h>
#include <wx/msgdlg.h>
#include <wx/regex.h>
#ifdef WIN32
	#undef StartDoc
	#include <wx/msw/winundef.h>
#endif
#include <wx/settings.h>

#include <algorithm>
#include <Shlwapi.h>

IMPLEMENT_CLASS(ttTraceScalingDialog, wxDialog)

const long ttTraceScalingDialog::ID_X_MANUAL      = wxNewId();
const long ttTraceScalingDialog::ID_X_DIVS_AUTO   = wxNewId();
const long ttTraceScalingDialog::ID_X_DIVS_NUMBER = wxNewId();
const long ttTraceScalingDialog::ID_X_DIVS_VALUE  = wxNewId();
const long ttTraceScalingDialog::ID_Y_MANUAL      = wxNewId();
const long ttTraceScalingDialog::ID_Y_DIVS_AUTO   = wxNewId();
const long ttTraceScalingDialog::ID_Y_DIVS_NUMBER = wxNewId();
const long ttTraceScalingDialog::ID_Y_DIVS_VALUE  = wxNewId();

BEGIN_EVENT_TABLE(ttTraceScalingDialog, wxDialog)
	EVT_CHECKBOX    ( ID_X_MANUAL,      ttTraceScalingDialog::OnXManual      )
	EVT_RADIOBUTTON ( ID_X_DIVS_AUTO,   ttTraceScalingDialog::OnXDivisions   )
	EVT_RADIOBUTTON ( ID_X_DIVS_NUMBER, ttTraceScalingDialog::OnXDivisions   )
	EVT_RADIOBUTTON ( ID_X_DIVS_VALUE,  ttTraceScalingDialog::OnXDivisions   )
	EVT_CHECKBOX    ( ID_Y_MANUAL,      ttTraceScalingDialog::OnYManual      )
	EVT_RADIOBUTTON ( ID_Y_DIVS_AUTO,   ttTraceScalingDialog::OnYDivisions   )
	EVT_RADIOBUTTON ( ID_Y_DIVS_NUMBER, ttTraceScalingDialog::OnYDivisions   )
	EVT_RADIOBUTTON ( ID_Y_DIVS_VALUE,  ttTraceScalingDialog::OnYDivisions   )
END_EVENT_TABLE()

ttTraceScalingDialog::ttTraceScalingDialog(
	ttTraceWindow* parent,
	wxWindowID id,
	const wxPoint &pos,
	const wxSize &size
) {
	Create(
		parent,
		id,
		"Scaling: "+parent->GetName(),
		wxDefaultPosition,
		wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE,
		"ttTraceScalingDialog"
	);
	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));

	wxFlexGridSizer*  fillerFlex;
	wxBoxSizer*       filler;
	wxBoxSizer*       filler2;
	wxStaticBoxSizer* fillerStatic;

	wxBoxSizer* s_outer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* s_inner = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* s_top = new wxBoxSizer(wxHORIZONTAL);

	/// X-axis

	wxBoxSizer* s_x = new wxBoxSizer(wxVERTICAL);
	s_x->Add(
		new wxStaticHeading(this,wxID_ANY,"X-axis (time)"),
		wxSizerFlags().Expand().Border(wxTOP|wxBOTTOM,-2)
	);
	s_x->AddSpacer(12);

	s_x->Add(
		m_x_manual = new wxCheckBox(this,ID_X_MANUAL,"Manually specify X-axis extents")
	);
	s_x->AddSpacer(12);
	fillerFlex = new wxFlexGridSizer(2,2,6,3);
	fillerFlex->AddGrowableCol(1);
	fillerFlex->Add(
		m_x_max_label = new wxStaticText(this,wxID_ANY,"Maximum:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_x_max = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorTime<double>(&m_value_x_maximum)),
		wxSizerFlags().Expand()
	);
	fillerFlex->Add(
		m_x_min_label = new wxStaticText(this,wxID_ANY,"Minimum:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_x_min = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorTime<double>(&m_value_x_minimum)),
		wxSizerFlags().Expand()
	);
	s_x->Add(fillerFlex, wxSizerFlags().Expand());
	s_x->AddSpacer(6);
	fillerStatic = new wxStaticBoxSizer(wxVERTICAL,this,"Divisions");
	m_x_divs = fillerStatic->GetStaticBox();
	fillerStatic->AddSpacer(3);
	fillerFlex = new wxFlexGridSizer(3,2,6,3);
	fillerFlex->AddGrowableCol(1,1);
	fillerFlex->Add(
		m_x_divs_auto = new wxRadioButton(this,ID_X_DIVS_AUTO,"Automatic",wxDefaultPosition,wxDefaultSize,wxRB_GROUP),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->AddSpacer(21);
	fillerFlex->Add(
		m_x_divs_number = new wxRadioButton(this,ID_X_DIVS_NUMBER,"Number:"),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->Add(
		m_x_divs_number_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<unsigned short>(&m_value_x_div_number)),
		wxSizerFlags().Expand().Border(wxRIGHT,1)
	);
	fillerFlex->Add(
		m_x_divs_value = new wxRadioButton(this,ID_X_DIVS_VALUE,"Value:"),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->Add(
		m_x_divs_value_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorTime<double>(&m_value_x_div_value)),
		wxSizerFlags().Expand().Border(wxRIGHT,1)
	);
	fillerStatic->Add(fillerFlex, wxSizerFlags().Expand().Border(wxLEFT|wxBOTTOM|wxRIGHT,6));
	fillerStatic->AddSpacer(1);
	s_x->Add(fillerStatic, wxSizerFlags().Expand());

	s_top->Add(s_x, wxSizerFlags(1));

	s_top->AddSpacer(24);

	/// Y-axis

	wxBoxSizer* s_y = new wxBoxSizer(wxVERTICAL);
	wxString units = parent->GetUnits();
	s_y->Add(
		new wxStaticHeading(this,wxID_ANY,units.IsEmpty() ? "Y-axis" : "Y-axis ("+units+")"),
		wxSizerFlags().Expand().Border(wxTOP|wxBOTTOM,-2)
	);
	s_y->AddSpacer(12);

	s_y->Add(
		m_y_manual = new wxCheckBox(this,ID_Y_MANUAL,"Manually specify Y-axis extents")
	);
	s_y->AddSpacer(12);
	fillerFlex = new wxFlexGridSizer(2,2,6,3);
	fillerFlex->AddGrowableCol(1);
	fillerFlex->Add(
		m_y_max_label = new wxStaticText(this,wxID_ANY,"Maximum:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_y_max = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<double>(&m_value_y_maximum,NULL,units)),
		wxSizerFlags().Expand()
	);
	fillerFlex->Add(
		m_y_min_label = new wxStaticText(this,wxID_ANY,"Minimum:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_y_min = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<double>(&m_value_y_minimum,NULL,units)),
		wxSizerFlags().Expand()
	);
	s_y->Add(fillerFlex, wxSizerFlags().Expand());
	s_y->AddSpacer(6);
	fillerStatic = new wxStaticBoxSizer(wxVERTICAL,this,"Divisions");
	m_y_divs = fillerStatic->GetStaticBox();
	fillerStatic->AddSpacer(3);
	fillerFlex = new wxFlexGridSizer(3,2,6,3);
	fillerFlex->AddGrowableCol(1,1);
	fillerFlex->Add(
		m_y_divs_auto = new wxRadioButton(this,ID_Y_DIVS_AUTO,"Automatic",wxDefaultPosition,wxDefaultSize,wxRB_GROUP),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->AddSpacer(21);
	fillerFlex->Add(
		m_y_divs_number = new wxRadioButton(this,ID_Y_DIVS_NUMBER,"Number:"),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->Add(
		m_y_divs_number_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<unsigned short>(&m_value_y_div_number)),
		wxSizerFlags().Expand().Border(wxRIGHT,1)
	);
	fillerFlex->Add(
		m_y_divs_value = new wxRadioButton(this,ID_Y_DIVS_VALUE,"Value:"),
		wxSizerFlags().Border(wxLEFT|wxTOP,3)
	);
	fillerFlex->Add(
		m_y_divs_value_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<double>(&m_value_y_div_value,NULL,units)),
		wxSizerFlags().Expand().Border(wxRIGHT,1)
	);
	fillerStatic->Add(fillerFlex, wxSizerFlags().Expand().Border(wxLEFT|wxRIGHT,6));
	fillerStatic->AddSpacer(6);
	filler = new wxBoxSizer(wxVERTICAL);
	filler->Add(
		m_y_ticks_label = new wxStaticText(this,wxID_ANY,"Tick alignment:"),
		wxSizerFlags().Border(wxLEFT,19)
	);
	filler->AddSpacer(7);
	filler2 = new wxBoxSizer(wxHORIZONTAL);
	filler2->Add(
		m_y_ticks_best = new wxRadioButton(this,wxID_ANY,"Best",wxDefaultPosition,wxDefaultSize,wxRB_GROUP)
	);
	filler2->AddSpacer(6);
	filler2->Add(
		m_y_ticks_min = new wxRadioButton(this,wxID_ANY,"Min")
	);
	filler2->AddSpacer(6);
	filler2->Add(
		m_y_ticks_max = new wxRadioButton(this,wxID_ANY,"Max")
	);
	filler->Add(filler2, wxSizerFlags().Border(wxLEFT,19));
	fillerStatic->Add(filler, wxSizerFlags().Border(wxLEFT|wxBOTTOM|wxRIGHT,6));
	fillerStatic->AddSpacer(1);
	s_y->Add(fillerStatic, wxSizerFlags().Expand());

	s_top->Add(s_y, wxSizerFlags(1));

	s_inner->Add(s_top, wxSizerFlags().Expand());
	s_inner->AddSpacer(12);

	/// Misc

	s_inner->Add(
		new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxHORIZONTAL),
		wxSizerFlags().Expand()
	);
	s_inner->AddSpacer(12);
	s_inner->Add(
		m_margins = new wxCheckBox(this,wxID_ANY,"Draw margins")
	);
	s_inner->AddSpacer(12);

	/// Buttons
	filler = new wxBoxSizer(wxHORIZONTAL);
	wxButton* ok;
	filler->Add(
		ok = new wxButton(this,wxID_OK,"OK")
	);
	filler->AddSpacer(6);
	filler->Add(
		new wxButton(this,wxID_CANCEL,"Cancel")
	);
	filler->AddSpacer(6);
	filler->Add(
		new wxButton(this,wxID_APPLY,"Apply")
	);
	s_inner->Add(filler, wxSizerFlags().Right());

	s_outer->Add(s_inner, wxSizerFlags(1).Expand().Border(wxALL,10));

	SetSizer(s_outer);
	s_outer->Layout();
	s_outer->Fit(this);
	s_outer->SetSizeHints(this);

	SetDefaultItem(ok);
	ok->SetFocus();

	CentreChildOnParent(dynamic_cast<wxTopLevelWindow*>(wxGetTopLevelParent(parent)),this);
}

ttTraceScalingDialog::~ttTraceScalingDialog()
{
}

bool ttTraceScalingDialog::TransferDataToWindow()
{
	ttTraceWindow* trace = dynamic_cast<ttTraceWindow*>(GetParent());

	trace->BeginUserXUpdate();
	m_value_x_manual = !trace->GetUserXAutoScaling();
	m_value_x_maximum = trace->GetUserXMaximum();
	m_value_x_minimum = trace->GetUserXMinimum();
	m_value_x_div_method = trace->GetUserXDivisions(&m_value_x_div_number,&m_value_x_div_value);
	trace->EndUserXUpdate(true);
	trace->BeginUserYUpdate();
	m_value_y_manual = !trace->GetUserYAutoScaling();
	m_value_y_maximum = trace->GetUserYMaximum();
	m_value_y_minimum = trace->GetUserYMinimum();
	m_value_y_div_method = trace->GetUserYDivisions(&m_value_y_div_number,&m_value_y_div_value);
	m_value_y_tick_method = trace->GetUserYAlignment();
	bool margins = trace->GetUserMargins();
	trace->EndUserYUpdate(true);

	m_x_manual->SetValue(m_value_x_manual);
	switch (m_value_x_div_method)
	{
		case ttTrace_Divisions_Value:
			m_x_divs_value->SetValue(true);
			break;
		case ttTrace_Divisions_Number:
			m_x_divs_number->SetValue(true);
			break;
		default:
			m_x_divs_auto->SetValue(true);
			break;
	}

	wxCommandEvent event;
	OnXManual(event);

	m_y_manual->SetValue(m_value_y_manual);
	switch (m_value_y_div_method)
	{
		case ttTrace_Divisions_Value:
			m_y_divs_value->SetValue(true);
			break;
		case ttTrace_Divisions_Number:
			m_y_divs_number->SetValue(true);
			break;
		default:
			m_y_divs_auto->SetValue(true);
			break;
	}
	switch (m_value_y_tick_method)
	{
		case ttTrace_Align_Max:
			m_y_ticks_max->SetValue(true);
			break;
		case ttTrace_Align_Min:
			m_y_ticks_min->SetValue(true);
			break;
		default:
			m_y_ticks_best->SetValue(true);
			break;
	}

	OnYManual(event);

	m_margins->SetValue(margins);

	return wxDialog::TransferDataToWindow();
}

bool ttTraceScalingDialog::TransferDataFromWindow()
{
	ttTraceWindow* trace = dynamic_cast<ttTraceWindow*>(GetParent());

	trace->BeginUserXUpdate();
	if (m_value_x_manual)
	{
		trace->SetUserXAutoScaling(false);
		trace->SetUserXMaximum(m_value_x_maximum);
		trace->SetUserXMinimum(m_value_x_minimum);
		trace->SetUserXDivisions((ttTrace_Divisions)m_value_x_div_method,m_value_x_div_number,m_value_x_div_value);
	}
	else
	{
		trace->SetUserXAutoScaling(true);
	}
	trace->EndUserXUpdate();

	trace->BeginUserYUpdate();
	if (m_value_y_manual)
	{
		trace->SetUserYAutoScaling(false);
		trace->SetUserYMaximum(m_value_y_maximum);
		trace->SetUserYMinimum(m_value_y_minimum);
		trace->SetUserYDivisions((ttTrace_Divisions)m_value_y_div_method,m_value_y_div_number,m_value_y_div_value);
		if (m_value_y_div_method==ttTrace_Divisions_Value) trace->SetUserYAlignment((ttTrace_Align)m_value_y_tick_method);
	}
	else
	{
		trace->SetUserYAutoScaling(true);
	}
	trace->SetUserMargins(m_margins->GetValue());
	trace->EndUserYUpdate();

	trace->Render(true);

	return wxDialog::TransferDataFromWindow();
}

bool ttTraceScalingDialog::Validate()
{
	double dValue;
	unsigned short sValue;

	if (!wxDialog::Validate())
	{ // A number must be invalid
		wxMessageBox("Please ensure all values are valid numbers. The ones highlighted are either too large or improperly formatted.","Error");
		return false;
	}

	/// X-AXIS
	m_value_x_manual = m_x_manual->GetValue();
	if (m_value_x_manual)
	{ // Validate the X-axis settings

		/// X MAXIMUM
		dValue = dynamic_cast<ValidatorNumeric<double>*>(m_x_max->GetValidator())->GetValue();
		if (dValue<=0.0)
		{ // Error: Value is negative
			wxMessageBox("DPSync is very powerful timing technology, but it can't go back in time.\nPlease enter a maximum value greater than 0.","Error");
			m_x_max->GetValidator()->TransferToWindow();
			m_x_max->SetFocus();
			m_x_max->SetSelection(-1,-1);
			return false;
		}
		m_value_x_maximum = dValue;

		/// X MINIMUM
		dValue = dynamic_cast<ValidatorNumeric<double>*>(m_x_min->GetValidator())->GetValue();
		if (dValue<0.0)
		{ // Error: Value is negative
			wxMessageBox("DPSync is very powerful timing technology, but it can't go back in time.\nPlease enter a minimum value greater than or equal to 0.","Error");
			m_x_min->GetValidator()->TransferToWindow();
			m_x_min->SetFocus();
			m_x_min->SetSelection(-1,-1);
			return false;
		}
		m_value_x_minimum = dValue;

		/// BOTH X EXTENTS
		if (m_value_x_minimum==m_value_x_maximum)
		{ // Error: They're equal
			wxMessageBox("The X-axis extents are the same. Please enter different values for maximum and minimum.","Error");
			m_x_max->GetValidator()->TransferToWindow();
			m_x_min->GetValidator()->TransferToWindow();
			m_x_max->SetFocus();
			m_x_max->SetSelection(-1,-1);
			return false;
		}
		// Ensure they're the right way around
		if (m_value_x_minimum>m_value_x_maximum)
		{
			dValue = m_value_x_maximum;
			m_value_x_maximum = m_value_x_minimum;
			m_value_x_minimum = dValue;
		}
		m_x_max->GetValidator()->TransferToWindow();
		m_x_min->GetValidator()->TransferToWindow();

		/// X DIVISION VALUE
		if (m_x_divs_value->GetValue())
		{
			m_value_x_div_method = ttTrace_Divisions_Value;
			
			dValue = abs(dynamic_cast<ValidatorNumeric<double>*>(m_x_divs_value_field->GetValidator())->GetValue());
			if (dValue==0.0)
			{ // Error: Value is 0
				wxMessageBox("The X-axis division value must be greater than 0s.","Error");
				m_x_divs_value_field->GetValidator()->TransferToWindow();
				m_x_divs_value_field->SetFocus();
				m_x_divs_value_field->SetSelection(-1,-1);
				return false;
			}
			else
			{
				double range = m_value_x_maximum-m_value_x_minimum;
				if (dValue>range && !EffectivelyEqual(dValue,range,9))
				{ // Error: Value is greater than range
					// Only check for this if the extents are valid. Then also check that the value isn't greater than the range just because of floating point errors
					wxMessageBox("The X-axis division value is larger than the range on the axis. Please enter a value no larger than the difference between the maximum and minimum.","Error");
					m_x_divs_value_field->GetValidator()->TransferToWindow();
					m_x_divs_value_field->SetFocus();
					m_x_divs_value_field->SetSelection(-1,-1);
					return false;
				}
				else if (dValue<(range/255.0))
				{ // Error: Value would produce more than 256 ticks
					wxMessageBox("The division value is too small to be seen on the X-axis. Please enter a value no smaller than "+ttTraceWindow::FormatTime(range/255.0)+".","Error");
					m_x_divs_value_field->GetValidator()->TransferToWindow();
					m_x_divs_value_field->SetFocus();
					m_x_divs_value_field->SetSelection(-1,-1);
					return false;
				}
			}
			m_value_x_div_value = dValue;
			m_x_divs_value_field->GetValidator()->TransferToWindow();
		}

		/// X DIVISION NUMBER
		else if (m_x_divs_number->GetValue())
		{
			m_value_x_div_method = ttTrace_Divisions_Number;

			sValue = abs(dynamic_cast<ValidatorNumeric<double>*>(m_x_divs_number_field->GetValidator())->GetValue());
			if (sValue==0) sValue = 1;
			if (sValue>255)
			{ // Error: Too many ticks
				wxMessageBox("The X-axis division number may be no larger than 255.","Error");
				m_x_divs_number_field->GetValidator()->TransferToWindow();
				m_x_divs_number_field->SetFocus();
				m_x_divs_number_field->SetSelection(-1,-1);
				return false;
			}
			m_value_x_div_number = sValue;
			m_x_divs_number_field->GetValidator()->TransferToWindow();
		}

		/// X DIVISION AUTOMATIC
		else
		{
			m_value_x_div_method = ttTrace_Divisions_Auto;
		}
	}

	/// Y-AXIS
	m_value_y_manual = m_y_manual->GetValue();
	if (m_value_y_manual)
	{ // Validate the Y-axis settings

		/// Y MAXIMUM
		m_value_y_maximum = dynamic_cast<ValidatorNumeric<double>*>(m_y_max->GetValidator())->GetValue();

		/// Y MINIMUM
		m_value_y_minimum = dynamic_cast<ValidatorNumeric<double>*>(m_y_min->GetValidator())->GetValue();

		/// BOTH Y EXTENTS
		if (m_value_y_minimum==m_value_y_maximum)
		{ // Error: They're equal
			wxMessageBox("The Y-axis extents are the same. Please enter different values for maximum and minimum.","Error");
			m_y_max->GetValidator()->TransferToWindow();
			m_y_min->GetValidator()->TransferToWindow();
			m_y_max->SetFocus();
			m_y_max->SetSelection(-1,-1);
			return false;
		}
		// Ensure they're the right way around
		if (m_value_y_minimum>m_value_y_maximum)
		{
			dValue = m_value_y_maximum;
			m_value_y_maximum = m_value_y_minimum;
			m_value_y_minimum = dValue;
		}
		m_y_max->GetValidator()->TransferToWindow();
		m_y_min->GetValidator()->TransferToWindow();

		/// Y DIVISION VALUE
		if (m_y_divs_value->GetValue())
		{
			m_value_y_div_method = ttTrace_Divisions_Value;
			
			dValue = abs(dynamic_cast<ValidatorNumeric<double>*>(m_y_divs_value_field->GetValidator())->GetValue());
			wxString unit = dynamic_cast<ttTraceWindow*>(GetParent())->GetUnits();
			if (dValue==0.0)
			{ // Error: Value is 0
				wxMessageBox("The Y-axis division value must be greater than 0"+unit+".","Error");
				m_y_divs_value_field->GetValidator()->TransferToWindow();
				m_y_divs_value_field->SetFocus();
				m_y_divs_value_field->SetSelection(-1,-1);
				return false;
			}
			else
			{
				double range = m_value_y_maximum-m_value_y_minimum;
				if (dValue>range && !EffectivelyEqual(dValue,range,9))
				{ // Error: Value is greater than range
					// Only check for this if the extents are valid. Then also check that the value isn't greater than the range just because of floating point errors
					wxMessageBox("The Y-axis division value is larger than the range on the axis. Please enter a value no larger than the difference between the maximum and minimum.","Error");
					m_y_divs_value_field->GetValidator()->TransferToWindow();
					m_y_divs_value_field->SetFocus();
					m_y_divs_value_field->SetSelection(-1,-1);
					return false;
				}
				else if (dValue<(range/255.0))
				{ // Error: Value would produce more than 256 ticks
					wxMessageBox("The division value is too small to be seen on the Y-axis. Please enter a value no smaller than "+ttTraceWindow::FormatPreciseNumber(range/255.0,unit)+".","Error");
					m_y_divs_value_field->GetValidator()->TransferToWindow();
					m_y_divs_value_field->SetFocus();
					m_y_divs_value_field->SetSelection(-1,-1);
					return false;
				}
			}
			m_value_y_div_value = dValue;
			m_y_divs_value_field->GetValidator()->TransferToWindow();

			/// Y TICK ALIGNMENT
			if (m_y_ticks_max->GetValue())
			{
				m_value_y_tick_method = ttTrace_Align_Max;
			}
			else if (m_y_ticks_min->GetValue())
			{
				m_value_y_tick_method = ttTrace_Align_Min;
			}
			else
			{
				m_value_y_tick_method = ttTrace_Align_Auto;
			}
		}

		/// Y DIVISION NUMBER
		else if (m_y_divs_number->GetValue())
		{
			m_value_y_div_method = ttTrace_Divisions_Number;

			sValue = abs(dynamic_cast<ValidatorNumeric<double>*>(m_y_divs_number_field->GetValidator())->GetValue());
			if (sValue==0) sValue = 1;
			if (sValue>255)
			{ // Error: Too many ticks
				wxMessageBox("The Y-axis division number may be no larger than 255.","Error");
				m_y_divs_number_field->GetValidator()->TransferToWindow();
				m_y_divs_number_field->SetFocus();
				m_y_divs_number_field->SetSelection(-1,-1);
				return false;
			}
			m_value_y_div_number = sValue;
			m_y_divs_number_field->GetValidator()->TransferToWindow();
		}

		/// Y DIVISION AUTOMATIC
		else
		{
			m_value_y_div_method = ttTrace_Divisions_Auto;
		}
	}

	return true;
}

void ttTraceScalingDialog::OnXManual(wxCommandEvent &event)
{
	bool manual = m_x_manual->GetValue();
	
	m_x_min_label->Enable(manual);
	m_x_min->Enable(manual);
	m_x_max_label->Enable(manual);
	m_x_max->Enable(manual);
	m_x_divs->Enable(manual);
	m_x_divs->SetForegroundColour(manual ? wxNullColour : wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	m_x_divs->Refresh();
	m_x_divs_auto->Enable(manual);
	m_x_divs_number->Enable(manual);
	m_x_divs_number_field->Enable(manual && m_x_divs_number->GetValue());
	m_x_divs_value->Enable(manual);
	m_x_divs_value_field->Enable(manual && m_x_divs_value->GetValue());
}

void ttTraceScalingDialog::OnXDivisions(wxCommandEvent &event)
{
	bool manual = m_x_manual->GetValue();
	m_x_divs_number_field->Enable(manual && m_x_divs_number->GetValue());
	m_x_divs_value_field->Enable(manual && m_x_divs_value->GetValue());
}

void ttTraceScalingDialog::OnYManual(wxCommandEvent &event)
{
	bool manual = m_y_manual->GetValue();
	
	m_y_min_label->Enable(manual);
	m_y_min->Enable(manual);
	m_y_max_label->Enable(manual);
	m_y_max->Enable(manual);
	m_y_divs->Enable(manual);
	m_y_divs->SetForegroundColour(manual ? wxNullColour : wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
	m_y_divs->Refresh();
	m_y_divs_auto->Enable(manual);
	m_y_divs_number->Enable(manual);
	m_y_divs_number_field->Enable(manual && m_y_divs_number->GetValue());
	m_y_divs_value->Enable(manual);
	bool divValue = m_y_divs_value->GetValue();
	m_y_divs_value_field->Enable(manual && divValue);
	m_y_ticks_label->Enable(manual && divValue);
	m_y_ticks_best->Enable(manual && divValue);
	m_y_ticks_min->Enable(manual && divValue);
	m_y_ticks_max->Enable(manual && divValue);
}

void ttTraceScalingDialog::OnYDivisions(wxCommandEvent &event)
{
	bool manual = m_y_manual->GetValue();
	m_y_divs_number_field->Enable(manual && m_y_divs_number->GetValue());
	bool divValue = m_y_divs_value->GetValue();
	m_y_divs_value_field->Enable(manual && divValue);
	m_y_ticks_label->Enable(manual && divValue);
	m_y_ticks_best->Enable(manual && divValue);
	m_y_ticks_min->Enable(manual && divValue);
	m_y_ticks_max->Enable(manual && divValue);
}

/*bool ttTraceScalingDialog::Validate(wxWindow* control, const unsigned long &value)
{
	return ValidateRelatively(control);
}

bool ttTraceScalingDialog::Validate(wxWindow* control, const signed long &value)
{
	return ValidateRelatively(control);
}

bool ttTraceScalingDialog::Validate(wxWindow* control, const double &value)
{
	return ValidateRelatively(control);
}

bool ttTraceScalingDialog::ValidateRelatively(wxWindow* control)
{
	if (control==m_y_max)
	{ // Validate Y-axis maximum
		if (dynamic_cast<ValidatorNumeric<double>*>(m_y_min->GetValidator())->IsInternallyValid())
		{ // Y-axis minimum is numerically valid and can be used for validation
			double max = dynamic_cast<ValidatorNumeric<double>*>(m_y_max->GetValidator())->GetValue();
			double min = dynamic_cast<ValidatorNumeric<double>*>(m_y_min->GetValidator())->GetValue();
			if (min==max)
			{ // Should not be equal
				dynamic_cast<ValidatorNumeric<double>*>(m_y_min->GetValidator())->SetExternalValidity(false);
				return false;
			}
		}
	}
}*/