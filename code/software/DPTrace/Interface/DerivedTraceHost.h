/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/DerivedTraceHost.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_DERIVEDTRACEHOST_H
#define TT_DERIVEDTRACEHOST_H

#include "..\..\common\MSCppHeapAllocDebug.h"

#include <wx/app.h>
#include <wx/frame.h>

#include "Main.h"
#include "Thread.h"
#include "Trace.h"

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include <vector>

struct MetricMask;
class ttDevicedTraceHost;
class ttMtieTraceWindow;
class ttTdevTraceWindow;

extern std::vector<ttDerivedTraceHost*> derivedListeners;
extern wxMutex                          derivedListeners_mutex;

/*********************
  ttDerivedTraceHost
*********************/

class ttDerivedTraceHost : public wxFrame
{
	public:
		ttDerivedTraceHost(wxTopLevelWindow* parent, ttTraceWindow* dataSource, const wxString &title);
		~ttDerivedTraceHost();
		void DoneReadingFile();
		void ArrangeTraces(const bool &force, wxSize* areaSize=NULL);
		void SourceLost();
		void SetSource(ttTraceWindow* source);
		void RefreshGraphs();
		unsigned int GetColumnOffset() const;
		void ReceiveData(const double &x, const double &y);
		bool WaitingForData() const;

	private:
		void OnSize(wxSizeEvent &event);
		void OnChar(wxKeyEvent &event);
		void OnClose(wxCloseEvent &event);
		void OnQuit(wxCommandEvent &event);
		void OnRefresh(wxCommandEvent &event);
		void OnChecklistCheck(wxCommandEvent &event);
		void OnChecklistSelect(wxCommandEvent &event);
		//static unsigned int RunThreadDestroying();
		//void DoDestroying();
		void ClearTraces();
		void EraseTrace(std::vector<ttTraceWindow*>::iterator &entry);
		void DisassociateTrace(std::vector<ttTraceWindow*>::iterator &entry);
		void CalculateTraceGrid(int &x, int &y, wxSize* areaSize=NULL);
		void RedrawMasks();
		static unsigned int RunThreadCalculating(ttThread* thread, void* host);
		unsigned int DoCalculating();

		ttThread* m_thread_drawing;
		//ttThread*                   m_thread_destroying;
		//wxMutex                     m_mutex_destroying;
		//std::vector<ttTraceWindow*> m_traces_destroying;
		ttThread* m_thread_calculating;
		wxBoxSizer*      m_wholeArea;
		wxBoxSizer*      m_formArea;
		wxFlexGridSizer* m_traceArea;
		wxPanel* m_panel;
		wxButton*   m_refresh;
		wxStaticLine*   m_masks_separator;
		wxCheckListBox* m_masks_list;
		ttEmptyFrame* m_trace_window;
		bool m_WindowCreated;
		ttTraceWindow* m_dataSource;
		const unsigned int  m_columnOffset;
		ttThread* m_fileReader;
		bool m_continueReadingFromFile;
		
		std::vector<ttTraceWindow*> m_traces;
		ttMtieTraceWindow* m_mtie;
		ttTdevTraceWindow* m_tdev;
		std::vector<const MetricMask*> m_masks;

		// Local store for when source trace is absent
		std::vector<double> m_points_store_x;
		std::vector<double> m_points_store_y;
		wxMutex m_points_store_mutex;

		static const long ID_REFRESH;
		static const long ID_MASKS_LIST;

		DECLARE_EVENT_TABLE()
};

#endif // TT_DERIVEDTRACEHOST_H