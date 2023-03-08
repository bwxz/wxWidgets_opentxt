/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxInteractiveImage.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef WXINTERACTIVEIMAGE_H
#define WXINTERACTIVEIMAGE_H

#include <wx/event.h>
#include "wxImageWindow.h"

#include <vector>

/*********
  EVENTS
*********/

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_CLICKED, -1)
	DECLARE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_SELECTED, -1)
	DECLARE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_SELECTING, -1)
END_DECLARE_EVENT_TYPES()

class wxInteractiveImageEvent : public wxNotifyEvent {
	public:
		wxInteractiveImageEvent(
			int id,
			long index,
			wxEventType commandType = wxEVT_INTERACTIVE_IMAGE_CLICKED
		);
		wxEvent* Clone() const;
		long GetIndex() const;

	protected:
		long m_index;
};

typedef void (wxEvtHandler::*wxInteractiveImageEventFunction)(wxInteractiveImageEvent&);

#define EVT_INTERACTIVE_IMAGE_CLICKED(id,fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_INTERACTIVE_IMAGE_CLICKED, id, wxID_ANY, \
    (wxObjectEventFunction) (wxEventFunction) \
    wxStaticCastEvent(wxInteractiveImageEventFunction, & fn ), (wxObject *) NULL ),
#define EVT_INTERACTIVE_IMAGE_SELECTED(id,fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_INTERACTIVE_IMAGE_SELECTED, id, wxID_ANY, \
    (wxObjectEventFunction) (wxEventFunction) \
    wxStaticCastEvent(wxInteractiveImageEventFunction, & fn ), (wxObject *) NULL ),
#define EVT_INTERACTIVE_IMAGE_SELECTING(id,fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_INTERACTIVE_IMAGE_SELECTING, id, wxID_ANY, \
    (wxObjectEventFunction) (wxEventFunction) \
    wxStaticCastEvent(wxInteractiveImageEventFunction, & fn ), (wxObject *) NULL ),

/*********************
  wxInteractiveImage
*********************/

typedef struct {
	long index;
	wxRect region;
} wxInteractiveHitbox;

class wxInteractiveImage : public wxImageWindow {
	public:
		wxInteractiveImage(
			wxWindow* parent,
			wxWindowID id,
			const unsigned char bitmap[],
			const int &length,
			const wxBitmapType &type,
			const wxPoint &pos=wxDefaultPosition,
			const wxSize &size=wxDefaultSize,
			long style=0
		);
		~wxInteractiveImage();
		bool AddHitbox(const wxRect &hitbox);
		bool AddHitbox(const long &index, const wxRect &hitbox);
		bool RemoveHitbox(const long &index);
		bool SetSelection(const long &index);
		bool ChangeSelection(const long &index);
		void Render();

	protected:
		void OnMouseEvent(wxMouseEvent &event);
		void DoSelectionChange(const long &index);
		std::vector<wxInteractiveHitbox> m_hitboxes;
		long m_page;
		const unsigned char* m_referencedBitmap;
		int m_bitmapLength;
		wxBitmapType m_bitmapType;
		long m_highestIndex;

	private:
		DECLARE_CLASS(wxInteractiveImage)
		DECLARE_EVENT_TABLE()
};

#endif// WXINTERACTIVEIMAGE_H