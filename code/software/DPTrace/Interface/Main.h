/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Main.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_MAIN_H
#define TT_MAIN_H

#include "..\..\common\MSCppHeapAllocDebug.h"

#include <wx/app.h>
#include <wx/frame.h>

#include "Thread.h"
#include "Trace.h"

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/checklst.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include <vector>

class ttEmptyFrame;
class ttTraceWindow;

/**************
  ToPTraceApp
**************/

class ToPTraceApp : public wxApp		//主应用
{
	public:
		bool OnInit();
		void OnInitCmdLine(wxCmdLineParser &parser);
		bool OnCmdLineParsed(wxCmdLineParser &parser);
		bool OnCmdLineError(wxCmdLineParser &parser);
		bool OnCmdLineHelp(wxCmdLineParser &parser);

	private:
		wxString      m_param_address;
		wxString      m_param_file;
		wxString      m_param_period;
		bool          m_param_start;
		bool          m_param_printAll;
		bool          m_param_minimise;
		bool          m_param_maximise;
		unsigned long m_param_systems;
};

/****************
  ToPTraceFrame
****************/

class ToPTraceFrame : public wxFrame	//主窗口
{
	public:
		ToPTraceFrame(
			const wxString &address,
			const wxString &file,
			const wxString &period,
			const bool &start,
			const bool &printAll,
			const unsigned long &systems
		);
		~ToPTraceFrame();
		static ToPTraceFrame* GetInstance();
		void DoneReadingFile();
		bool IsLogging();
		void SetError(const wxString &error);
		void ArrangeTraces(const bool &force, wxSize* areaSize=NULL);
		static void StartWaiting(const wxString &message);
		static void StopWaiting(const bool &standalone=true, const bool &force=false);
		static void SetFilename(const wxString &newName);
		void PopulateParameters();
		void InitChecklistParameters();
		wxComboBox* GetCM55address(){return m_form_address;}

	private:
		void OnSize(wxSizeEvent &event);
		void OnChar(wxKeyEvent &event);
		void OnClose(wxCloseEvent &event);
		void OnQuit(wxCommandEvent &event);
		void OnSystemsBox(wxCommandEvent &event);
		void OnSystemsButton(wxCommandEvent &event);
		void OnInitiate(wxCommandEvent &event);
		void OnChecklistSelect(wxCommandEvent &event);
		void OnChecklistCommand(wxCommandEvent &event);
		void OnPlot(wxCommandEvent &event);
		void OnAbout(wxCommandEvent &event);
		void OnMenuSelect(wxCommandEvent &event);
		void OnChangeTitleStart(wxCommandEvent &event);
		void OnChangeTitleEnd(wxCommandEvent &event);
		void OnSave(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);
		void ResetAfterLogging();
		void ResetAfterOpening();
		static unsigned int RunThreadLogging(ttThread* thread);
		static unsigned int RunThreadDrawing(ttThread* thread);
		static unsigned int RunThreadDestroying(ttThread* thread);
		static unsigned int RunThreadOpening(ttThread* thread);
		void DoLogging();
		void DoDrawing();
		void DoDestroying();
		void DoOpening();
		void ClearTraces();
		void EraseTrace(std::vector<ttTraceWindow*>::iterator &entry);
		void DisassociateTrace(std::vector<ttTraceWindow*>::iterator &entry);
		void CalculateTraceGrid(int &x, int &y, wxSize* areaSize=NULL);
		bool SaveFiles();

		ttThread* m_thread_logging;
		bool      m_running_logging;
		ttThread* m_thread_drawing;
		ttThread*                   m_thread_destroying;
		wxMutex                     m_mutex_destroying;
		std::vector<ttTraceWindow*> m_traces_destroying;
		ttThread* m_thread_opening;
		wxBoxSizer*      m_wholeArea;
		wxBoxSizer*      m_formArea;
		wxFlexGridSizer* m_traceArea;
		wxPanel* m_panel;
		wxComboBox* m_form_address;
		wxTextCtrl* m_form_period;
		wxCheckBox* m_form_printAll;
		wxCheckBox* m_form_systems_box;
		wxButton*   m_form_systems_button;
		wxButton*   m_initiator;
		wxStaticLine* m_waiting_separator;
		wxStaticText* m_waiting_text;
		wxGauge*      m_waiting_gauge;
		bool          m_isWaiting;
		wxStaticLine*   m_parameters_separator;
		wxCheckListBox* m_parameters_list;
		wxStaticText*   m_parameters_none;
		wxButton*       m_parameters_plot;
		ttEmptyFrame* m_trace_window;
		bool m_WindowCreated;
		wxString m_originalTitle;
		wxString m_specialTitle;
		wxDialog* m_titleDialog;
		wxTextCtrl* m_titleControl;
		unsigned long m_systems;
		wxString m_LastFile;

		static ToPTraceFrame* m_instance;

		static const long ID_CM55Address;
		static const long ID_SYSTEMS_BOX;
		static const long ID_SYSTEMS_BUTTON;
		static const long ID_INITIATOR;
		static const long ID_PARAMETERS_LIST;
		static const long ID_PARAMETERS_PLOT;
		static const long ID_MENU_ARRANGE;
		static const long ID_CHANGETITLE_START;
		static const long ID_CHANGETITLE_END;

		DECLARE_EVENT_TABLE()
};

/***************
  ttEmptyFrame
***************/

class ttEmptyFrame : public wxPanel
{
	public:
		ttEmptyFrame(wxWindow* parent, const wxString &message);
		void SetMessage(const wxString &message);

	private:
		wxStaticText* m_message;
};

#endif // TT_MAIN_H