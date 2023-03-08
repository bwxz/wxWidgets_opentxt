/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxStaticTextImproved.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "wxStaticTextImproved.h"

IMPLEMENT_CLASS(wxStaticTextImproved,wxStaticText)

wxStaticTextImproved::wxStaticTextImproved(
	wxWindow* parent,
	wxWindowID id,
	const wxString &label,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString &name
) : wxStaticText(parent,id,label,pos,size,style,name) {
}

wxStaticTextImproved::~wxStaticTextImproved() {
}

bool wxStaticTextImproved::Show(bool show) {
	bool result = wxStaticText::Show(show);

	Refresh();
	Update();

	return result;
}