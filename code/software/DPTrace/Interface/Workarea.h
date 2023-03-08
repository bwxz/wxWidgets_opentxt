/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Workarea.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef WORKAREA_H
#define WORKAREA_H

#include <wx/region.h>
#include <wx/toplevel.h>
#include <wx/msw/private.h>

wxRegion GetTotalWorkArea();
BOOL CALLBACK AddToWorkArea(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

wxTopLevelWindow* FindTopLevelWindow(wxWindow* window);
void CentreChildOnParent(wxTopLevelWindow* parent, wxTopLevelWindow* child);

#endif // WORKAREA_H