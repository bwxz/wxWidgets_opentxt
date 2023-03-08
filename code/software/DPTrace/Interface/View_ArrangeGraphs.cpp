/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/View_ArrangeGraphs.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "View_ArrangeGraphs.h"

#include "Floats.h"
#include "Macros.h"
#include "Main.h"
#include "Options.h"
#include "Trace.h"
#include "Workarea.h"

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

// Converts a single ratio value into two relative numbers, e.g. 1.25 -> 5:4
void RatioSingleToDouble(const double &single, double &doubleX, double &doubleY)
{
	double x,y,remainder,multiplier,finalMultiplier;
	// Set starting values, relative to 1
	if (single<1.0)
	{ // y>x, so y may not be an integer
		x = 1.0;
		y = 1.0 / single;
		remainder = y - floor(y);
	}
	else
	{ // x>y, so x may not be an integer
		x = single;
		y = 1.0;
		remainder = x - floor(x);
	}
	finalMultiplier = 1.0;
	// Improve representation, e.g. 1.33:1 -> 4:3
	while (!EffectivelyZero(remainder,-3))
	{ // Keep multiplying up. The final multiplier will turn the real number into an integer, and will be an integer itself so the other component will remain one
		multiplier = 1.0/remainder;
		finalMultiplier *= multiplier;
		remainder = multiplier - floor(multiplier); // Definiltely want non-integer part of multiplier, not finalMultiplier. Though I couldn't tell you why, mathematically
	}
	doubleX = round(x*finalMultiplier);
	doubleY = round(y*finalMultiplier);
}

IMPLEMENT_CLASS(ArrangeGraphsDialog, wxDialog)

BEGIN_EVENT_TABLE(ArrangeGraphsDialog, wxDialog)
	EVT_RADIOBUTTON ( wxID_ANY, ArrangeGraphsDialog::OnMethod )
END_EVENT_TABLE()

ArrangeGraphsDialog::ArrangeGraphsDialog(
	wxWindow* parent
) {
	
	m_regKey = new wxRegKey(registryBase,REGKEY_BASE);
	if (!m_regKey->Exists()) m_regKey->Create();

	Create(
		parent,
		wxID_ANY,
		"Arrange Graphs",
		wxDefaultPosition,
		wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE,
		"ArrangeGraphsDialog"
	);
	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));

	wxFlexGridSizer*  fillerFlex;
	wxBoxSizer*       filler;

	wxBoxSizer* s_outer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* s_inner = new wxBoxSizer(wxVERTICAL);

	s_inner->Add(
		new wxStaticText(this,wxID_ANY,"Arrange graphs by:")
	);
	s_inner->AddSpacer(11);

	fillerFlex = new wxFlexGridSizer(3,2,6,3);
	fillerFlex->Add(
		m_columns = new wxRadioButton(this,wxID_ANY,"Number of &columns:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_columns_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<unsigned short>(&m_value_columns))
	);
	m_columns_field->SetMinSize(wxSize(50,-1));
	fillerFlex->Add(
		m_rows = new wxRadioButton(this,wxID_ANY,"Number of &rows:"),
		wxSizerFlags().Border(wxTOP,3)
	);
	fillerFlex->Add(
		m_rows_field = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<unsigned short>(&m_value_rows))
	);
	m_rows_field->SetMinSize(wxSize(50,-1));
	fillerFlex->Add(
		m_ratio = new wxRadioButton(this,wxID_ANY,"Best fit for &aspect ratio:"),
		wxSizerFlags().Border(wxTOP,3)
	);
		filler = new wxBoxSizer(wxHORIZONTAL);
		filler->Add(
			m_ratio_x = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<double>(&m_value_ratio_x))
		);
		m_ratio_x->SetMinSize(wxSize(50,-1));
		filler->Add(
			new wxStaticText(this,wxID_ANY," : "),
			wxSizerFlags().Border(wxTOP,3)
		);
		filler->Add(
			m_ratio_y = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,0,ValidatorNumeric<double>(&m_value_ratio_y))
		);
		m_ratio_y->SetMinSize(wxSize(50,-1));
	fillerFlex->Add(
		filler
	);
	s_inner->Add(fillerFlex);
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

ArrangeGraphsDialog::~ArrangeGraphsDialog()
{
	delete m_regKey;
}

bool ArrangeGraphsDialog::TransferDataToWindow()
{
	m_value_method = graphArrangement_method;
	m_value_columns = graphArrangement_columns;
	m_value_rows = graphArrangement_rows;
	RatioSingleToDouble(graphArrangement_ratio,m_value_ratio_x,m_value_ratio_y);

	switch (m_value_method)
	{
		case arrangeRows:
			m_rows->SetValue(true);
			break;
		case arrangeColumns:
			m_columns->SetValue(true);
			break;
		default:
			m_ratio->SetValue(true);
			break;
	}
	wxCommandEvent event;
	OnMethod(event);

	return wxDialog::TransferDataToWindow();
}

bool ArrangeGraphsDialog::TransferDataFromWindow()
{
	switch (m_value_method)
	{
		case arrangeRows:
			m_regKey->SetValue(REGKEY_GA_ROWS,m_value_rows);
			m_regKey->SetValue(REGKEY_GA_METHOD,arrangeRows);
			graphArrangement_rows = m_value_rows;
			graphArrangement_method = arrangeRows;
			break;
		case arrangeColumns:
			m_regKey->SetValue(REGKEY_GA_COLUMNS,m_value_columns);
			m_regKey->SetValue(REGKEY_GA_METHOD,arrangeColumns);
			graphArrangement_columns = m_value_columns;
			graphArrangement_method = arrangeColumns;
			break;
		default:
			m_regKey->SetValue(REGKEY_GA_RATIO,wxString::Format("%lu:%lu",(unsigned long)m_value_ratio_x,(unsigned long)m_value_ratio_y));
			m_regKey->SetValue(REGKEY_GA_METHOD,arrangeRatio);
			graphArrangement_ratio = m_value_ratio_x / m_value_ratio_y;
			graphArrangement_method = arrangeRatio;
			break;
	}

	dynamic_cast<ToPTraceFrame*>(GetParent())->ArrangeTraces(false);

	return wxDialog::TransferDataFromWindow();
}

bool ArrangeGraphsDialog::Validate()
{
	if (!wxDialog::Validate())
	{ // A number must be invalid
		wxMessageBox("Please ensure all values are valid numbers. The ones highlighted are either too large or improperly formatted.","Error");
		return false;
	}

	// Columns
	if (m_columns->GetValue())
	{
		m_value_method = arrangeColumns;
		m_value_columns = dynamic_cast<ValidatorNumeric<unsigned short>*>(m_columns_field->GetValidator())->GetValue();
	}

	// Rows
	else if (m_rows->GetValue())
	{
		m_value_method = arrangeRows;
		m_value_rows = dynamic_cast<ValidatorNumeric<unsigned short>*>(m_rows_field->GetValidator())->GetValue();
	}

	// Aspect ratio
	else
	{
		m_value_method = arrangeRatio;
		RatioSingleToDouble(
			abs(dynamic_cast<ValidatorNumeric<double>*>(m_ratio_x->GetValidator())->GetValue())
			/ abs(dynamic_cast<ValidatorNumeric<double>*>(m_ratio_y->GetValidator())->GetValue()),
			m_value_ratio_x,
			m_value_ratio_y
		);

		m_ratio_x->GetValidator()->TransferToWindow();
		m_ratio_y->GetValidator()->TransferToWindow();
	}
	
	return true;
}

void ArrangeGraphsDialog::OnMethod(wxCommandEvent &event)
{
	Freeze();

	m_columns_field->Enable(m_columns->GetValue());
	m_rows_field->Enable(m_rows->GetValue());
	m_ratio_x->Enable(m_ratio->GetValue());
	m_ratio_y->Enable(m_ratio->GetValue());

	Thaw();
}