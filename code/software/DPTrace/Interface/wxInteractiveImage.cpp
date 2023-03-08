/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxInteractiveImage.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "wxInteractiveImage.h"

#include <wx/dcgraph.h>

/**********************************
  INTERACTIVE IMAGE EVENTS
**********************************/

DEFINE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_CLICKED)
DEFINE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_SELECTED)
DEFINE_EVENT_TYPE(wxEVT_INTERACTIVE_IMAGE_SELECTING)

wxInteractiveImageEvent::wxInteractiveImageEvent(
	int id,
	long index,
	wxEventType commandType
) : wxNotifyEvent (
	commandType,
	id
) {
	m_index = index;
}

wxEvent* wxInteractiveImageEvent::Clone() const {
	return new wxInteractiveImageEvent(GetIndex(),GetEventType());
}

long wxInteractiveImageEvent::GetIndex() const {
	return m_index;
}

/*********************
  wxInteractiveImage
*********************/

IMPLEMENT_CLASS(wxInteractiveImage,wxImageWindow)

BEGIN_EVENT_TABLE(wxInteractiveImage,wxImageWindow)
	EVT_MOUSE_EVENTS(wxInteractiveImage::OnMouseEvent)
END_EVENT_TABLE()

wxInteractiveImage::wxInteractiveImage(
	wxWindow* parent,
	wxWindowID id,
	const unsigned char bitmap[],
	const int &length,
	const wxBitmapType &type,
	const wxPoint &pos,
	const wxSize &size,
	long style
) : wxImageWindow(parent,id,pos,size,style) {
	m_page = -1;
	m_highestIndex = -1;
	m_referencedBitmap = &bitmap[0];
	m_bitmapLength = length;
	m_bitmapType = type;
	Render();
}

wxInteractiveImage::~wxInteractiveImage() {
}

bool wxInteractiveImage::AddHitbox(const wxRect &hitbox) {
	return AddHitbox(m_highestIndex+1, hitbox);
}

bool wxInteractiveImage::AddHitbox(const long &index, const wxRect &hitbox) {
	bool indexUsed = false;
	for (unsigned long i=0; i<m_hitboxes.size(); i++) {
	// Run through initially to make sure it's not intersecting with anything
		if (m_hitboxes.at(i).region.Intersects(hitbox)) return false;
		if (m_hitboxes.at(i).index==index) indexUsed = true;
	}
	if (indexUsed) {
		if (index>=0) {
		// For positive, selectable regions, shift them up
			for (unsigned long i=0; i<m_hitboxes.size(); i++) {
				if (m_hitboxes.at(i).index>=index) m_hitboxes.at(i).index++;
			}
			m_highestIndex++;
		} else {
		// For negative, clickable regions, shift them down
			for (unsigned long i=0; i<m_hitboxes.size(); i++) {
				if (m_hitboxes.at(i).index<=index) m_hitboxes.at(i).index--;
			}
		}
	} else {
	// Still need to update highest index if a high index has been added
		if (index>m_highestIndex) m_highestIndex = index;
	}
	wxInteractiveHitbox newone = {index,hitbox};
	m_hitboxes.push_back(newone);
	return true;
}

bool wxInteractiveImage::RemoveHitbox(const long &index) {
	bool found = false;
	unsigned long listIndex = 0;
	long nextHighest = 0;
	for (unsigned long i=0; i<m_hitboxes.size(); i++) {
		if (m_hitboxes.at(i).index==index) {
		// Note item, but don't quit if we need to search for next highest
			listIndex = i;
			found = true;
		} else if (m_hitboxes.at(i).index>nextHighest) {
			nextHighest = m_hitboxes.at(i).index;
		}
	}
	if (!found) return false;
	m_hitboxes.erase(m_hitboxes.begin()+listIndex);
	if (index>=m_highestIndex) m_highestIndex = nextHighest;
	return true;
}

void wxInteractiveImage::OnMouseEvent(wxMouseEvent &event) {
	for (unsigned long i=0; i<m_hitboxes.size(); i++) {
		wxRect shifted = m_hitboxes.at(i).region;
		shifted.x += m_hOffset;
		shifted.y += m_vOffset;
		if (shifted.Contains(event.GetPosition())) {
		//if (m_hitboxes.at(i).Contains(event.GetPosition())) {
			if (event.LeftDown()) {
				if (m_hitboxes.at(i).index>=0) {
				// Selectable page
					SetSelection(m_hitboxes.at(i).index);
				} else {
				// Clickable page
					wxInteractiveImageEvent clickedEvent(GetId(),m_hitboxes.at(i).index,wxEVT_INTERACTIVE_IMAGE_CLICKED);
					clickedEvent.SetEventObject(this);
					GetEventHandler()->ProcessEvent(clickedEvent);
				}
			} else {
				SetCursor(wxCURSOR_HAND);
			}
			return;
		}
	}
	SetCursor(wxNullCursor);
}

bool wxInteractiveImage::SetSelection(const long &index) {
	if (index<0 || index==m_page) return false;
	bool found = false;
	for (unsigned long i=0; i<m_hitboxes.size(); i++) {
		if (m_hitboxes.at(i).index==index) {
			found = true;
			break;
		}
	}
	if (!found) return false;

	// 'Selecting' event
	wxInteractiveImageEvent selectingEvent(GetId(),index,wxEVT_INTERACTIVE_IMAGE_SELECTING);
	selectingEvent.SetEventObject(this);
	if (GetEventHandler()->ProcessEvent(selectingEvent) && !selectingEvent.IsAllowed()) return false;

	DoSelectionChange(index);

	// 'Selected' event
	wxInteractiveImageEvent selectedEvent(GetId(),index,wxEVT_INTERACTIVE_IMAGE_SELECTED);
	selectedEvent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(selectedEvent);
	return true;
}

bool wxInteractiveImage::ChangeSelection(const long &index) {
	if (index<0 || index==m_page) return false;
	bool found = false;
	for (unsigned long i=0; i<m_hitboxes.size(); i++) {
		if (m_hitboxes.at(i).index==index) {
			found = true;
			break;
		}
	}
	if (!found) return false;
	DoSelectionChange(index);
	return true;
}

void wxInteractiveImage::DoSelectionChange(const long &index) {
	m_page = index;
	Render();
}

void wxInteractiveImage::Render() {
	wxBitmap background = _wxConvertMemoryToBitmap(m_referencedBitmap, m_bitmapLength, m_bitmapType);
	wxBitmap tempBitmap(
		background.GetWidth(),
		background.GetHeight()
	);
	wxMemoryDC mdc(tempBitmap);
	wxGCDC dc(mdc);
	dc.Clear();
	dc.DrawBitmap(background,0,0);

	wxPen thePen(/*wxColour(191,212,255)*/*wxBLACK,2,wxDOT);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.SetPen(thePen);
	if (m_page>-1) {
		bool found = false;
		wxRect rectangle;
		for (unsigned long i=0; i<m_hitboxes.size(); i++) {
			if (m_hitboxes.at(i).index==m_page) {
				rectangle = m_hitboxes.at(i).region;
				found = true;
				break;
			}
		}
		if (found && !rectangle.IsEmpty()) {
			//rectangle.Inflate(10,10);
			//dc.DrawEllipse(rectangle);
			rectangle.Inflate(5,5);
			//dc.DrawRectangle(rectangle);
			dc.DrawRoundedRectangle(rectangle.x,rectangle.y,rectangle.GetWidth(),rectangle.GetHeight(),10);
		}
	}

	mdc.SelectObjectAsSource(wxNullBitmap);
	m_bitmap = tempBitmap;
	Refresh();
}