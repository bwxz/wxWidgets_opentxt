/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Workarea.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Workarea.h"

static wxRegion totalWorkArea;

wxRegion GetTotalWorkArea() {
	totalWorkArea.Clear();
	EnumDisplayMonitors(NULL, NULL, AddToWorkArea, 0);
	return totalWorkArea;
}

BOOL CALLBACK AddToWorkArea(
	HMONITOR hMonitor,
	HDC hdcMonitor,
	LPRECT lprcMonitor,
	LPARAM dwData
) {
	// Can't use lprcMonitor as it's the entire size of the screen
	// Need work area, i.e. area without taskbar etc.
	MONITORINFO monitorInfo;
	memset(&monitorInfo,0,sizeof(MONITORINFO));
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(hMonitor, &monitorInfo);

	wxRect rect = wxRect(
		wxPoint(monitorInfo.rcWork.left,monitorInfo.rcWork.top),
		wxPoint(monitorInfo.rcWork.right,monitorInfo.rcWork.bottom)
	);
	totalWorkArea.Union(rect);
	return (BOOL)true;
}

wxTopLevelWindow* FindTopLevelWindow(wxWindow* window) {
	if (window->IsTopLevel()) return (wxTopLevelWindow*)window;
	wxWindow* parent = window->GetParent();
	if (!parent) return NULL;
	return FindTopLevelWindow(parent);
}

void CentreChildOnParent(wxTopLevelWindow* parent, wxTopLevelWindow* child)
{
	if (parent==NULL || child==NULL) return;

	/** Perform the initial centering **/

	wxRect rect(parent->GetScreenRect());
	wxPoint childPos(rect.x, rect.y);
	wxSize childSize = child->GetSize();

	// Centre horizontally
	childPos.x += (rect.width-childSize.x) / 2;
	// 'Centre' vertically
	childPos.y += (double)(rect.height-childSize.y) * 0.45;

	child->Move(childPos);

	/** Ensure at least the title bar is clickable, otherwise the dialog may not be usable **/

	wxRegion workArea = GetTotalWorkArea();

	TITLEBARINFO barInfo;
	memset(&barInfo,0,sizeof(TITLEBARINFO));
	barInfo.cbSize = sizeof(TITLEBARINFO);
	GetTitleBarInfo(GetHwndOf(child), &barInfo);
	wxRect titleBar = wxRect(
		wxPoint(barInfo.rcTitleBar.left,barInfo.rcTitleBar.top),
		wxPoint(barInfo.rcTitleBar.right,barInfo.rcTitleBar.bottom)
	);

	if (workArea.Contains(titleBar)==wxOutRegion) {
	// Title bar not in work area, so cannot be moved/seen
	// Move window to reasonable location: the 'centre' of primary monitor's work area
		RECT primaryWorkArea;
		memset(&primaryWorkArea,0,sizeof(RECT));
		SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&primaryWorkArea, 0);
		childPos.x = primaryWorkArea.left;
		childPos.y = primaryWorkArea.top;

		if ((primaryWorkArea.right-primaryWorkArea.left)>childSize.x) {
		// Center horizontally
			childPos.x += (primaryWorkArea.right-primaryWorkArea.left-childSize.x) / 2;
		}
		if ((primaryWorkArea.bottom-primaryWorkArea.top)>childSize.y) {
		// 'Centre' vertically
			childPos.y += (double)(primaryWorkArea.bottom-primaryWorkArea.top-childSize.y) * 0.45;
		}

		child->Move(childPos);
	}
}