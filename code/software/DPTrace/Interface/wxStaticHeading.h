/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxStaticHeading.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef WXSTATICHEADING_H
#define WXSTATICHEADING_H

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>

class wxStaticTextImproved;

class wxStaticHeading : public wxPanel {
	public:
		wxStaticHeading(
			wxWindow* parent,
			wxWindowID id,
			const wxString &label,
			const wxPoint &pos = wxDefaultPosition,
			const wxSize &size = wxDefaultSize,
			long style = wxALIGN_LEFT,
			const wxString &name = "wxStaticHeading"
		);
		~wxStaticHeading();
		virtual bool Show(bool show=true);
		wxString GetLabel();
		void SetLabel(const wxString &label);
		long GetOrientation();
		void SetOrientation(const long &orientation);
		virtual bool AcceptsFocus() const;
		virtual bool AcceptsFocusRecursively() const;
		virtual bool AcceptsFocusFromKeyboard() const;

	protected:
		void OnFocus(wxFocusEvent &event);
		void OnChildFocus(wxChildFocusEvent &event);
		wxStaticLine* m_left;
		wxStaticLine* m_right;
		wxStaticTextImproved* m_label;
		wxFlexGridSizer* m_sizer;
		long m_orientation;

	private:
		DECLARE_CLASS(wxStaticHeading)
		DECLARE_EVENT_TABLE()
};

#endif // WXSTATICHEADING_H