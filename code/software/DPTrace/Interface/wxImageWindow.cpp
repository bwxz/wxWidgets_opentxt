/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxImageWindow.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "wxImageWindow.h"

#define leftAligned ((m_alignment & wxIW_HORIZONTAL)==wxIW_LEFT)
#define rightAligned ((m_alignment & wxIW_HORIZONTAL)==wxIW_RIGHT)
#define topAligned ((m_alignment & wxIW_VERTICAL)==wxIW_TOP)
#define bottomAligned ((m_alignment & wxIW_VERTICAL)==wxIW_BOTTOM)
#define centredHorizontally ((m_alignment & wxIW_HORIZONTAL)==wxIW_CENTRE)
#define centredVertically ((m_alignment & wxIW_VERTICAL)==wxIW_CENTREV)

static wxTopLevelWindow* FindTopLevelWindow(wxWindow* window) {
	if (window->IsTopLevel()) return (wxTopLevelWindow*)window;
	wxWindow* parent = window->GetParent();
	if (!parent) return NULL;
	return FindTopLevelWindow(parent);
}

IMPLEMENT_CLASS(wxImageWindow,wxWindow)

BEGIN_EVENT_TABLE(wxImageWindow,wxWindow)
	EVT_ERASE_BACKGROUND(wxImageWindow::OnEraseBackground)
	EVT_PAINT(wxImageWindow::OnPaint)
END_EVENT_TABLE()

wxImageWindow::wxImageWindow(
	wxWindow* parent,
	wxWindowID id,
	const wxPoint &pos,
	const wxSize &size,
	long style,
	const wxString &name
) {
	Init();
	m_bitmap = wxBitmap(size.GetWidth(),size.GetHeight());
	Create(parent,id,pos,size,style,name);
}

wxImageWindow::wxImageWindow() {
	Init();
	m_bitmap = wxBitmap(0,0);
}

wxImageWindow::~wxImageWindow() {
}

void wxImageWindow::Init() {
	m_drawOnTopLevel = false;
	m_alignment = wxIW_CENTRE|wxIW_CENTREV;
	m_hOffset = m_vOffset = 0;
}

wxBitmap& wxImageWindow::getBitmap() {
	return m_bitmap;
}

void wxImageWindow::setBitmap(wxBitmap &theBitmap, const long &alignment) {
	m_bitmap = theBitmap;
	long horizontal = alignment & wxIW_HORIZONTAL;
	if (horizontal!=wxIW_LEFT && horizontal!=wxIW_RIGHT) horizontal = wxIW_CENTRE;
	long vertical = alignment & wxIW_VERTICAL;
	if (vertical!=wxIW_TOP && vertical!=wxIW_BOTTOM) vertical = wxIW_CENTREV;
	m_alignment = horizontal | vertical;
}

void wxImageWindow::DrawOnTopLevel(const bool &draw) {
	m_drawOnTopLevel = draw;
}

void wxImageWindow::Render() {
}

void wxImageWindow::OnEraseBackground(wxEraseEvent &event) {
}

void wxImageWindow::OnPaint(wxPaintEvent &event) {
	int BHoffset = 0;
	int BVoffset = 0;
	int WHoffset = 0;
	int WVoffset = 0;
	wxPoint Poffset(0,0);
	if (!leftAligned) {
		BHoffset = GetSize().GetWidth()-m_bitmap.GetWidth(); // Get difference between bitmap's & window's widths
		if (centredHorizontally) BHoffset /= 2;
		if (BHoffset<0) {
		// Bitmap is wider than window; fit window within bitmap rather than bitmap within window
			WHoffset = -BHoffset;
			BHoffset = 0;
		}
	}
	if (!topAligned) {
		BVoffset = GetSize().GetHeight()-m_bitmap.GetHeight(); // Get difference between bitmap's & window's heights
		if (centredVertically) BVoffset /= 2;
		if (BVoffset<0) {
		// Bitmap is taller than window; fit window within bitmap rather than bitmap within window
			WVoffset = -BVoffset;
			BVoffset = 0;
		}
	}
	WHoffset += GetWindowBorderSize().x / 2;
	WVoffset += GetWindowBorderSize().y / 2;
	wxMemoryDC bdc(m_bitmap);
	/** OLD **/
	/*wxPaintDC dc(this);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	dc.Blit(
		BHoffset,BVoffset,                                               // Bitmap's offset from window (if bitmap<window)
		m_bitmap.GetWidth()-WHoffset,m_bitmap.GetHeight()-WVoffset,&bdc, // Bitmap dimensions & DC
		WHoffset,WVoffset                                                // Window's offset from bitmap (if window<bitmap)
	);*/
	/** NEW **/
	wxDC* dc;
	bool usingTopLevel = false;
	if (m_drawOnTopLevel) {
		wxTopLevelWindow* topLevel = FindTopLevelWindow(this);
		if (topLevel) {
			dc = new wxWindowDC(topLevel);
			usingTopLevel = true;
			Poffset = GetScreenPosition() - topLevel->GetScreenPosition();
		} else {
			dc = new wxPaintDC(this);
		}
	} else {
		dc = new wxPaintDC(this);
	}
	if (!usingTopLevel) {
		dc->SetBackground(*wxWHITE_BRUSH);
		dc->Clear();
	}
	dc->Blit(
		BHoffset+Poffset.x, BVoffset+Poffset.y,                          // Bitmap's offset from window (if bitmap<window)
		m_bitmap.GetWidth()-WHoffset,m_bitmap.GetHeight()-WVoffset,&bdc, // Bitmap dimensions & DC
		WHoffset,WVoffset                                                // Window's offset from bitmap (if window<bitmap)
	);
	bdc.SelectObjectAsSource(wxNullBitmap);
	m_hOffset = BHoffset-WHoffset;
	m_vOffset = BVoffset-WVoffset;
	delete dc;
}

wxSize wxImageWindow::GetBitmapSize() {
	return wxSize(
		m_bitmap.GetWidth(),
		m_bitmap.GetHeight()
	);
}