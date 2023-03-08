/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/wxImageWindow.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef WXIMAGEWINDOW_H
#define WXIMAGEWINDOW_H

#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>
#include <wx/window.h>
#include "..\Resources\Images\images.h"

#define wxIW_HORIZONTAL	0x0F
#define wxIW_LEFT		0x01
#define wxIW_RIGHT		0x02
#define wxIW_CENTRE		0x03
#define wxIW_VERTICAL	0xF0
#define wxIW_TOP		0x10
#define wxIW_BOTTOM		0x20
#define wxIW_CENTREV	0x30

class wxImageWindow : public wxWindow {
	public:
		wxImageWindow();
		wxImageWindow(
			wxWindow* parent,
			wxWindowID id,
			const wxPoint &pos=wxDefaultPosition,
			const wxSize &size=wxDefaultSize,
			long style=0,
			const wxString &name = "wxImageWindow"
		);
		~wxImageWindow();
		virtual wxBitmap& getBitmap();
		virtual void setBitmap(wxBitmap &theBitmap, const long &alignment=(wxIW_CENTRE|wxIW_CENTREV));
		virtual void DrawOnTopLevel(const bool &draw=true);
		virtual void Render();
		virtual wxSize GetBitmapSize();

	protected:
		void OnEraseBackground(wxEraseEvent &event);
		void OnPaint(wxPaintEvent &event);
		void Init();
		wxBitmap m_bitmap;
		long m_alignment;
		long m_hOffset;
		long m_vOffset;
		bool m_drawOnTopLevel;

	private:
		DECLARE_CLASS(wxToPSyncImageWindow)
		DECLARE_EVENT_TABLE()
};

#endif // WXIMAGEWINDOW_H