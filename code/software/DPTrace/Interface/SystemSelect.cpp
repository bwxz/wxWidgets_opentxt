/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/SystemSelect.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "SystemSelect.h"

#include "Workarea.h"

#include "ToPSyncInterfaceTypes.h"

#include <wx/icon.h>
#include <wx/msgdlg.h>
#ifdef WIN32
	#undef StartDoc
	#include <wx/msw/winundef.h>
#endif
#include <wx/settings.h>

#define SUPPORTED_SYSTEMS \
	( UDPPRINT_CLK1_BRIEF | UDPPRINT_CLK1_DETAIL | UDPPRINT_CLK1_DEBUG | UDPPRINT_CLK2_BRIEF | UDPPRINT_CLK2_DETAIL | UDPPRINT_CLK2_DEBUG \
	| UDPPRINT_PTP1_BRIEF | UDPPRINT_PTP1_DETAIL | UDPPRINT_PTP1_DEBUG | UDPPRINT_PTP2_BRIEF | UDPPRINT_PTP2_DETAIL | UDPPRINT_PTP2_DEBUG \
	| UDPPRINT_NODE1_BRIEF | UDPPRINT_NODE1_DETAIL | UDPPRINT_NODE1_DEBUG | UDPPRINT_NODE2_BRIEF | UDPPRINT_NODE2_DETAIL | UDPPRINT_NODE2_DEBUG \
	| UDPPRINT_SYSTEM_BRIEF | UDPPRINT_SYSTEM_DETAIL | UDPPRINT_SYSTEM_DEBUG )

IMPLEMENT_CLASS(ttSystemSelect, wxDialog)

ttSystemSelect::ttSystemSelect(wxWindow* parent, unsigned long* const systems)
	: m_systems(systems)
{
	Create(
		parent,
		wxID_ANY,
		"Systems to Retrieve",
		wxDefaultPosition,
		wxDefaultSize,
		wxCAPTION|wxCLOSE_BOX,
		"ttSystemSelect"
	);

	wxFlexGridSizer*  fillerFlex;
	wxBoxSizer*       filler;

	wxBoxSizer* s_outer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* s_inner = new wxBoxSizer(wxVERTICAL);

	/// Tickboxes

	wxString str_basics = "Basics:";
	wxString str_details = "Details:";
	wxString str_debug = "Debug:";
	int headingWidth;
	int tempWidth;
	int headingHeight;
	GetTextExtent(str_basics,&headingWidth,NULL);
	GetTextExtent(str_details,&tempWidth,NULL);
	headingWidth = wxMax(headingWidth,tempWidth);
	GetTextExtent(str_debug,&tempWidth,NULL);
	headingWidth = wxMax(headingWidth,tempWidth);

	fillerFlex = new wxFlexGridSizer(8,4,6,6);

	fillerFlex->AddSpacer(1);
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,str_basics,wxDefaultPosition,wxSize(headingWidth,-1),wxALIGN_CENTRE),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,str_details,wxDefaultPosition,wxSize(headingWidth,-1),wxALIGN_CENTRE),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,str_debug,wxDefaultPosition,wxSize(headingWidth,-1),wxALIGN_CENTRE),
		wxSizerFlags().Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Clock PLL 1:")
	);
	fillerFlex->Add(
		m_clk1_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_clk1_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_clk1_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Clock PLL 2:")
	);
	fillerFlex->Add(
		m_clk2_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_clk2_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_clk2_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Timestamp PLL 1:"),
		wxSizerFlags().Border(wxTOP,6)
	);
	fillerFlex->Add(
		m_ptp1_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_ptp1_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_ptp1_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Timestamp PLL 2:")
	);
	fillerFlex->Add(
		m_ptp2_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_ptp2_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_ptp2_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Node-time 1:"),
		wxSizerFlags().Border(wxTOP,6)
	);
	fillerFlex->Add(
		m_node1_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_node1_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_node1_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"Node-time 2:")
	);
	fillerFlex->Add(
		m_node2_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_node2_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	fillerFlex->Add(
		m_node2_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Centre()
	);
	
	fillerFlex->Add(
		new wxStaticText(this,wxID_ANY,"System:"),
		wxSizerFlags().Border(wxTOP,6)
	);
	fillerFlex->Add(
		m_system_1 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_system_2 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);
	fillerFlex->Add(
		m_system_3 = new wxCheckBox(this,wxID_ANY,wxEmptyString),
		wxSizerFlags().Border(wxTOP,6).Centre()
	);

	s_inner->Add(fillerFlex);
	s_inner->AddSpacer(12);

	wxStaticText* text;
	s_inner->Add(
		text = new wxStaticText(this,wxID_ANY,"Note: Selecting more than a few systems may exceed the device capacity, causing some columns not to be printed.",wxDefaultPosition,wxSize(0,-1)),
		wxSizerFlags().Expand()
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
	s_inner->Add(filler, wxSizerFlags().Right());

	s_outer->Add(s_inner, wxSizerFlags(1).Expand().Border(wxALL,10));

	SetSizer(s_outer);
	s_outer->Layout();
	s_outer->Fit(this);
	text->Wrap(text->GetSize().GetWidth());
	s_outer->Layout();
	s_outer->Fit(this);
	s_outer->SetSizeHints(this);

	SetDefaultItem(ok);
	ok->SetFocus();

	CentreChildOnParent(dynamic_cast<wxTopLevelWindow*>(wxGetTopLevelParent(parent)),this);
}

ttSystemSelect::~ttSystemSelect()
{
}

bool ttSystemSelect::TransferDataToWindow()
{
	m_clk1_1->SetValue(*m_systems & UDPPRINT_CLK1_BRIEF);
	m_clk1_2->SetValue(*m_systems & UDPPRINT_CLK1_DETAIL);
	m_clk1_3->SetValue(*m_systems & UDPPRINT_CLK1_DEBUG);
	m_clk2_1->SetValue(*m_systems & UDPPRINT_CLK2_BRIEF);
	m_clk2_2->SetValue(*m_systems & UDPPRINT_CLK2_DETAIL);
	m_clk2_3->SetValue(*m_systems & UDPPRINT_CLK2_DEBUG);
	m_ptp1_1->SetValue(*m_systems & UDPPRINT_PTP1_BRIEF);
	m_ptp1_2->SetValue(*m_systems & UDPPRINT_PTP1_DETAIL);
	m_ptp1_3->SetValue(*m_systems & UDPPRINT_PTP1_DEBUG);
	m_ptp2_1->SetValue(*m_systems & UDPPRINT_PTP2_BRIEF);
	m_ptp2_2->SetValue(*m_systems & UDPPRINT_PTP2_DETAIL);
	m_ptp2_3->SetValue(*m_systems & UDPPRINT_PTP2_DEBUG);
	m_node1_1->SetValue(*m_systems & UDPPRINT_NODE1_BRIEF);
	m_node1_2->SetValue(*m_systems & UDPPRINT_NODE1_DETAIL);
	m_node1_3->SetValue(*m_systems & UDPPRINT_NODE1_DEBUG);
	m_node2_1->SetValue(*m_systems & UDPPRINT_NODE2_BRIEF);
	m_node2_2->SetValue(*m_systems & UDPPRINT_NODE2_DETAIL);
	m_node2_3->SetValue(*m_systems & UDPPRINT_NODE2_DEBUG);
	m_system_1->SetValue(*m_systems & UDPPRINT_SYSTEM_BRIEF);
	m_system_2->SetValue(*m_systems & UDPPRINT_SYSTEM_DETAIL);
	m_system_3->SetValue(*m_systems & UDPPRINT_SYSTEM_DEBUG);

	return wxDialog::TransferDataToWindow();
}

bool ttSystemSelect::TransferDataFromWindow()
{
	unsigned long newSystems = 0;

	if (m_clk1_1->GetValue()) newSystems |= UDPPRINT_CLK1_BRIEF;
	if (m_clk1_2->GetValue()) newSystems |= UDPPRINT_CLK1_DETAIL;
	if (m_clk1_3->GetValue()) newSystems |= UDPPRINT_CLK1_DEBUG;
	if (m_clk2_1->GetValue()) newSystems |= UDPPRINT_CLK2_BRIEF;
	if (m_clk2_2->GetValue()) newSystems |= UDPPRINT_CLK2_DETAIL;
	if (m_clk2_3->GetValue()) newSystems |= UDPPRINT_CLK2_DEBUG;
	if (m_ptp1_1->GetValue()) newSystems |= UDPPRINT_PTP1_BRIEF;
	if (m_ptp1_2->GetValue()) newSystems |= UDPPRINT_PTP1_DETAIL;
	if (m_ptp1_3->GetValue()) newSystems |= UDPPRINT_PTP1_DEBUG;
	if (m_ptp2_1->GetValue()) newSystems |= UDPPRINT_PTP2_BRIEF;
	if (m_ptp2_2->GetValue()) newSystems |= UDPPRINT_PTP2_DETAIL;
	if (m_ptp2_3->GetValue()) newSystems |= UDPPRINT_PTP2_DEBUG;
	if (m_node1_1->GetValue()) newSystems |= UDPPRINT_NODE1_BRIEF;
	if (m_node1_2->GetValue()) newSystems |= UDPPRINT_NODE1_DETAIL;
	if (m_node1_3->GetValue()) newSystems |= UDPPRINT_NODE1_DEBUG;
	if (m_node2_1->GetValue()) newSystems |= UDPPRINT_NODE2_BRIEF;
	if (m_node2_2->GetValue()) newSystems |= UDPPRINT_NODE2_DETAIL;
	if (m_node2_3->GetValue()) newSystems |= UDPPRINT_NODE2_DEBUG;
	if (m_system_1->GetValue()) newSystems |= UDPPRINT_SYSTEM_BRIEF;
	if (m_system_2->GetValue()) newSystems |= UDPPRINT_SYSTEM_DETAIL;
	if (m_system_3->GetValue()) newSystems |= UDPPRINT_SYSTEM_DEBUG;

	// Mask out unsupported bits
	newSystems &= SUPPORTED_SYSTEMS;

	// Apply to bitfield
	*m_systems &= ~SUPPORTED_SYSTEMS;
	*m_systems |= newSystems;

	return wxDialog::TransferDataFromWindow();
}