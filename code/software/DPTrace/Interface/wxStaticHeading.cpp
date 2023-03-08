/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxStaticHeading.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "wxStaticHeading.h"
#include "wxStaticTextImproved.h"

IMPLEMENT_CLASS(wxStaticHeading,wxPanel)

BEGIN_EVENT_TABLE(wxStaticHeading,wxPanel)
	EVT_SET_FOCUS(wxStaticHeading::OnFocus)
	EVT_CHILD_FOCUS(wxStaticHeading::OnChildFocus)
END_EVENT_TABLE()

wxStaticHeading::wxStaticHeading(
	wxWindow* parent,
	wxWindowID id,
	const wxString &label,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString &name
) : wxPanel(parent,id,pos,size,wxTAB_TRAVERSAL,name) {
	m_left = new wxStaticLine(this,wxID_ANY);
	m_right = new wxStaticLine(this,wxID_ANY);
	m_label = new wxStaticTextImproved(this,wxID_ANY,label);

	m_sizer = new wxFlexGridSizer(1,3,0,0);
	m_sizer->AddGrowableCol(0,1);
	m_sizer->AddGrowableCol(2,1);
	wxBoxSizer* s_left = new wxBoxSizer(wxHORIZONTAL);
	s_left->Add(m_left, wxSizerFlags(1).Centre().Border(wxRIGHT,6));
	m_sizer->Add(s_left, wxSizerFlags().Expand().Border(wxTOP,1));
	m_sizer->Add(m_label);
	wxBoxSizer* s_right = new wxBoxSizer(wxHORIZONTAL);
	s_right->Add(m_right, wxSizerFlags(1).Centre().Border(wxLEFT,5));
	m_sizer->Add(s_right, wxSizerFlags().Expand().Border(wxTOP,1));

	wxFont labelFont = m_label->GetFont();
	labelFont.SetWeight(wxFONTWEIGHT_BOLD);
	m_label->SetFont(labelFont);

	SetOrientation(style);

	SetSizer(m_sizer);
	m_sizer->Layout();
	m_sizer->Fit(this);
	AcceptFocus(false);
}

wxStaticHeading::~wxStaticHeading() {
}

bool wxStaticHeading::Show(bool show) {
	bool result = wxPanel::Show(show);

	Refresh();
	Update();

	return result;
}

wxString wxStaticHeading::GetLabel() {
	return m_label->GetLabel();
}

void wxStaticHeading::SetLabel(const wxString &label) {
	m_label->SetLabel(label);
}

long wxStaticHeading::GetOrientation() {
	return m_orientation;
}

void wxStaticHeading::SetOrientation(const long &orientation) {
	m_orientation = orientation & (wxALIGN_LEFT|wxALIGN_CENTRE_HORIZONTAL|wxALIGN_RIGHT);
	if ((m_orientation & wxALIGN_RIGHT) == wxALIGN_RIGHT) {
		m_left->Show(true);
		m_right->Show(false);
	} else if ((m_orientation & wxALIGN_CENTRE_HORIZONTAL) == wxALIGN_CENTRE_HORIZONTAL) {
		m_left->Show(true);
		m_right->Show(true);
	} else {
		m_left->Show(false);
		m_right->Show(true);
	}
}

// Control may still be focused if it's the first 'control' on its parent. If so, move on to next control
void wxStaticHeading::OnFocus(wxFocusEvent &event) {
	if (!GetParent()) return;
	const wxWindowList &children = GetParent()->GetChildren();
	if (children.GetCount()<2) return; // Nothing to do if there's only one child (us)
	bool getNextOne = false;
	for (wxWindowList::const_iterator i = children.begin(), end = children.end(); i != end; ++i) {
		wxWindow* const window = *i;
		if (getNextOne) {
			window->SetFocus();
			return;
		}
		if (window==this) getNextOne = true;
	}
}

void wxStaticHeading::OnChildFocus(wxChildFocusEvent &event) {
}

// The following three functions stop most focus events from happening
bool wxStaticHeading::AcceptsFocus() const {
	return false;
}

bool wxStaticHeading::AcceptsFocusRecursively() const {
	return false;
}

bool wxStaticHeading::AcceptsFocusFromKeyboard() const {
	return false;
}