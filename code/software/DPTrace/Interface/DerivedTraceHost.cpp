/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/DerivedTraceHost.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "DerivedTraceHost.h"

#include "AuxTrace.h"
#include "Macros.h"
#include "Masks.h"
#include "Options.h"
#include "SystemSelect.h"
#include "View_ArrangeGraphs.h"
#include "Workarea.h"
#include "wxInteractiveImage.h"
#include "../resource.h"
#include "../version.h"
#include "../Communication/Security.h"
#include "../Communication/UDP.hpp"
#include "../Maths/MetricCalculation.h"

#include "ToPSyncInterfaceTypes.h"

#include <wx/apptrait.h>
#include <wx/cmdline.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/tokenzr.h>
#include <wx/msw/msvcrt.h>

#include <Commctrl.h>

std::vector<ttDerivedTraceHost*> derivedListeners;
 wxMutex                         derivedListeners_mutex;

unsigned int ReadFromFile(ttThread* thread, void* extra);

/*********************
  ttDerivedTraceHost
*********************/

const long ttDerivedTraceHost::ID_REFRESH    = wxNewId();
const long ttDerivedTraceHost::ID_MASKS_LIST = wxNewId();

BEGIN_EVENT_TABLE(ttDerivedTraceHost, wxFrame)
	EVT_CHECKLISTBOX   ( ID_MASKS_LIST, ttDerivedTraceHost::OnChecklistCheck   )
    EVT_LISTBOX        ( ID_MASKS_LIST, ttDerivedTraceHost::OnChecklistSelect  )
	EVT_SIZE           (                ttDerivedTraceHost::OnSize             )
    EVT_CHAR_HOOK      (                ttDerivedTraceHost::OnChar             )
    EVT_BUTTON         ( ID_REFRESH,    ttDerivedTraceHost::OnRefresh          )
	EVT_CLOSE          (                ttDerivedTraceHost::OnClose            )
END_EVENT_TABLE()

ttDerivedTraceHost::ttDerivedTraceHost(wxTopLevelWindow* parent, ttTraceWindow* dataSource, const wxString &title)
	: wxFrame(parent, wxID_ANY, dataSource->GetName()+": "+title, wxDefaultPosition, wxSize(600,400), wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU | wxMAXIMIZE_BOX | wxRESIZE_BORDER),
	m_thread_drawing(NULL),
	m_thread_calculating(NULL),
	m_traceArea(NULL),
	m_WindowCreated(false),
	m_dataSource(dataSource),
	m_columnOffset(dataSource->GetColumnOffset()),
	m_fileReader(NULL),
	m_continueReadingFromFile(false)
{
	m_masks.push_back(&etsi_pdh);
	m_masks.push_back(&etsi_prc);
	m_masks.push_back(&etsi_sec);
	m_masks.push_back(&etsi_ssu);
	m_masks.push_back(&g823_pdh);
	m_masks.push_back(&g823_prc);
	m_masks.push_back(&g823_sec);
	m_masks.push_back(&g823_ssu);
	m_masks.push_back(&g824_ds1);

	SetMinSize(wxSize(600,400));

	SetIcon(wxICON_FROM_RESOURCE(ICON_TOPTRACE_EMPTY));

	/** CONTENTS **/

	m_panel = new wxPanel(this,wxID_ANY);

	m_wholeArea = new wxBoxSizer(wxHORIZONTAL);
	m_formArea = new wxBoxSizer(wxVERTICAL);

	/** Form **/

	wxBoxSizer* filler = new wxBoxSizer(wxHORIZONTAL);
	filler->Add(
		m_refresh = new wxButton(m_panel,ID_REFRESH,"Refresh")
	);
	m_formArea->Add(filler, wxSizerFlags().Left());
	
	/** Plot options **/

	m_formArea->Add(
		m_masks_separator = new wxStaticLine(m_panel,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL),
		wxSizerFlags().Expand().Border(wxTOP|wxBOTTOM,12)
	);
	m_formArea->Add(
		new wxStaticText(m_panel,wxID_ANY,"Masks:"),
		wxSizerFlags().Border(wxBOTTOM,3)
	);
	m_formArea->Add(
		m_masks_list = new wxCheckListBox(m_panel,ID_MASKS_LIST),
		wxSizerFlags(1).Expand()
	);
	for (std::vector<const MetricMask*>::const_iterator i=m_masks.begin(); i!=m_masks.end(); ++i)
	{
		m_masks_list->Append((*i)->name);
	}

	m_wholeArea->Add(m_formArea, wxSizerFlags().Border(wxALL,10).Expand());

	m_wholeArea->Add(
		m_trace_window = new ttEmptyFrame(m_panel,"Logging has not been started."),
		wxSizerFlags(1).Expand()
	);
	m_trace_window->Show(false);
	
	m_traces.push_back(m_mtie = new ttMtieTraceWindow(m_panel,dataSource->GetName()+" (MTIE)",m_dataSource->GetColumnOffset(),-1));
	m_traces.push_back(m_tdev = new ttTdevTraceWindow(m_panel,dataSource->GetName()+" (TDEV)",m_dataSource->GetColumnOffset(),-1));

	m_WindowCreated = true;

	m_panel->SetSizer(m_wholeArea);
	m_wholeArea->Layout();
	
	m_masks_list->SetFocus();
	SetDefaultItem(m_refresh);

	// Add to list. Must be done after graphs are created or else they'll set the host's source to themselves because they follow the same column
	derivedListeners_mutex.Lock();
	derivedListeners.push_back(this);
	derivedListeners_mutex.Unlock();

	// Refresh graphs using an event so that it's done after the frame's been correctly sized
	GetEventHandler()->QueueEvent(new wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED,ID_REFRESH));
}

ttDerivedTraceHost::~ttDerivedTraceHost()
{
}

void ttDerivedTraceHost::OnSize(wxSizeEvent &event)
{
	if (!m_WindowCreated) return;

	ArrangeTraces(false,&event.GetSize());
	event.Skip();
}

void ttDerivedTraceHost::OnChar(wxKeyEvent &event)
{
	if (event.GetKeyCode()==WXK_ESCAPE)
	{ // Terminate something
		Close();
		return;
	}

	else
	{
		event.Skip();
	}
}

void ttDerivedTraceHost::OnClose(wxCloseEvent &event)
{
	// Hide, to give the impression of an immediate response
	Show(false);

	// Terminate threads
	if (m_thread_drawing!=NULL) m_thread_drawing->Terminate();
	// Wait for them to end
	if (m_thread_drawing!=NULL) m_thread_drawing->WaitForTermination(5000);
	// Disassociate them
	m_thread_drawing = NULL;
	ClearTraces();

	derivedListeners_mutex.Lock();
	for (std::vector<ttDerivedTraceHost*>::iterator i=derivedListeners.begin(); i!=derivedListeners.end(); ++i)
	{
		if (*i==this)
		{
			derivedListeners.erase(i);
			break;
		}
	}
	derivedListeners_mutex.Unlock();

	if (m_thread_drawing!=NULL) m_thread_drawing->DisassociateMainPointer(&m_thread_drawing);
	if (m_dataSource!=NULL) m_dataSource->DerivedLost();

	Destroy();
}

void ttDerivedTraceHost::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void ttDerivedTraceHost::OnRefresh(wxCommandEvent &event)
{
	RefreshGraphs();
}

void ttDerivedTraceHost::OnChecklistCheck(wxCommandEvent &event)
{
	RedrawMasks();
}

void ttDerivedTraceHost::OnChecklistSelect(wxCommandEvent &event)
{
	int selected = event.GetSelection();
	m_masks_list->Check(selected,!m_masks_list->IsChecked(selected));
	m_masks_list->SetSelection(-1);

	// Render graphs with new mask selection
	RedrawMasks();
}

/*unsigned int ttDerivedTraceHost::RunThreadDestroying()
{
	if (m_instance==NULL || m_instance->m_thread_destroying==NULL || GetCurrentThreadId()!=m_instance->m_thread_destroying->GetId()) return -1;

	m_instance->m_thread_destroying->EnterWorkingZone();

	m_instance->DoDestroying();

	if (m_instance!=NULL && m_instance->m_thread_destroying!=NULL) m_instance->m_thread_destroying->LeaveWorkingZone();
	return 0;
}*/

/*void ttDerivedTraceHost::DoDestroying()
{
	for (;;)
	{
		m_mutex_destroying.Lock();

		if (m_traces_destroying.empty())
		{ // Terminate this thread
			m_thread_destroying = NULL;
			m_mutex_destroying.Unlock();
			break;
		}

		delete *(m_traces_destroying.begin());
		m_traces_destroying.erase(m_traces_destroying.begin());

		m_mutex_destroying.Unlock();
	}
}*/

void ttDerivedTraceHost::RefreshGraphs()
{
	if (m_refresh->GetLabelText()!="Cancel")
	{ // Refresh plots

		if (m_dataSource!=NULL)
		{ // Recalculate from source data directly, but do so in another thread
			
			#ifdef __WXDEBUG__
				m_thread_calculating = new ttThread(threadCalculating,RunThreadCalculating,this,&m_thread_calculating);
			#else
				m_thread_calculating = new ttThread(RunThreadCalculating,this,&m_thread_calculating);
			#endif
			m_thread_calculating->Run();
			m_refresh->SetLabelText("Cancel");

		}
		else
		{ // Don't have the source trace any more, so read data from file

			// Clear local store
			m_points_store_mutex.Lock();
			m_points_store_x.clear();
			m_points_store_y.clear();
			m_points_store_mutex.Unlock();

			m_continueReadingFromFile = true;
			#ifdef __WXDEBUG__
				m_fileReader = new ttThread(threadReading,ReadFromFile,&m_continueReadingFromFile,&m_fileReader);
			#else
				m_fileReader = new ttThread(ReadFromFile,&m_continueReadingFromFile,&m_fileReader);
			#endif
			m_fileReader->Run();
			m_refresh->SetLabelText("Cancel");

		}

	}
	else
	{ // Cancel file read and/or recalculation

		m_continueReadingFromFile = false;
		if (m_fileReader!=NULL) m_fileReader->Terminate();
		if (m_fileReader!=NULL) m_fileReader->WaitForTermination(5000);
		m_fileReader = NULL;

		if (m_thread_calculating!=NULL) m_thread_calculating->Terminate();
		if (m_thread_calculating!=NULL) m_thread_calculating->WaitForTermination(5000);
		m_thread_calculating = NULL;

		m_refresh->SetLabelText("Refresh");
			
	}
}

void ttDerivedTraceHost::RedrawMasks()
{
	m_mtie->ResetMasks();
	m_tdev->ResetMasks();
	for (size_t i=0; i<m_masks.size(); ++i)
	{
		if (m_masks_list->IsChecked(i))
		{
			m_mtie->AddMask(m_masks[i]);
			m_tdev->AddMask(m_masks[i]);
		}
	}
	m_mtie->Render(true);
	m_tdev->Render(true);
}

void ttDerivedTraceHost::ClearTraces()
{
	for (std::vector<ttTraceWindow*>::iterator i=m_traces.begin(); i!=m_traces.end(); )
	{
		EraseTrace(i); // 'i' will be changed by the function
	}
	ArrangeTraces(false);
}

void ttDerivedTraceHost::EraseTrace(std::vector<ttTraceWindow*>::iterator &entry)
{
	delete (*entry);
	entry = m_traces.erase(entry);
}

void ttDerivedTraceHost::DisassociateTrace(std::vector<ttTraceWindow*>::iterator &entry)
{ // Renders a ttTraceWindow safe for asynchronous destruction
	(*entry)->PrepareForDestruction();
	(*entry)->Show(false);
	if (m_traceArea!=NULL) m_traceArea->Detach(*entry);
	entry = m_traces.erase(entry);
}

void ttDerivedTraceHost::ArrangeTraces(const bool &force, wxSize* areaSize)
{
	int cols,rows;
	CalculateTraceGrid(cols,rows,areaSize);

	Freeze();

	if (m_traceArea!=NULL)
	{ // Check if it needs rearranging - DOES NOT ACCOUNT FOR EMPTY 'CELLS', e.g. five traces arranged in a 3*2 grid
		if (
			!force
			&& m_traceArea->GetColWidths().size()==cols
			&& m_traceArea->GetRowHeights().size()==rows
			&& m_traceArea->GetItemCount()==m_traces.size()
		)
		{ // Trace sizer already contains the right number of plots
			Thaw();
			return;
		}
		// Start from scratch
		m_wholeArea->Remove(m_traceArea);
		m_traceArea = NULL;
	}

	if (!m_traces.empty())
	{ // Create & populate the trace area
		m_trace_window->Show(false);
		m_traceArea = new wxFlexGridSizer(rows,cols,0,0);
		for (int i=0; i<cols; ++i)
		{
			m_traceArea->AddGrowableCol(i,1);
		}
		for (int i=0; i<rows; ++i)
		{
			m_traceArea->AddGrowableRow(i,1);
		}

		for (std::vector<ttTraceWindow*>::iterator i=m_traces.begin(); i!=m_traces.end(); ++i)
		{
			m_traceArea->Add(
				(*i),
				wxSizerFlags(1).Expand()
			);
		}

		m_wholeArea->Add(m_traceArea, wxSizerFlags(1).Expand());
	}
	else
	{
		m_trace_window->Show(true);
	}
	if (areaSize==NULL)
	{ // Not called from size event, so must be refreshed now
		m_wholeArea->Layout();
	}

	Thaw();
}

void ttDerivedTraceHost::CalculateTraceGrid(int &x, int &y, wxSize* areaSize)
{
	if (m_traces.empty())
	{
		x = y = 0;
		return;
	}
	if (areaSize==NULL)
	{
		areaSize = &GetClientSize();
	}

	switch (graphArrangement_method)
	{
		case arrangeRows:
			y = wxMin(graphArrangement_rows,m_traces.size());
			x = (int)ceil((double)m_traces.size() / (double)y);
			break;
		case arrangeColumns:
			x = wxMin(graphArrangement_columns,m_traces.size());
			y = (int)ceil((double)m_traces.size() / (double)x);
			break;
		default:
			{
				/**
				  Equation for the number of columns is:
					sqr( ( [grid's aspect ratio] / [desired graph aspect ratio] ) * [number of graphs] )
				  Then round that (up OR down as appropriate).
				**/
				double columns = pow(
					(
						(
							(double)(areaSize->x-214)
							/
							(double)areaSize->y
						)
						/
						graphArrangement_ratio
					)
					*
					(double)m_traces.size()
					,
					0.5
				);

				if (columns-floor(columns) < 0.5)
				{
					x = (int)floor(columns);
				}
				else
				{
					x = (int)ceil(columns);
				}

				y = (int)ceil((double)m_traces.size() / (double)x);
			}
			break;
	}
}

void ttDerivedTraceHost::DoneReadingFile()
{
	m_continueReadingFromFile = false;

	// Perform calculation in another thread
	#ifdef __WXDEBUG__
		m_thread_calculating = new ttThread(threadCalculating,RunThreadCalculating,this,&m_thread_calculating);
	#else
		m_thread_calculating = new ttThread(RunThreadCalculating,this,&m_thread_calculating);
	#endif
	m_thread_calculating->Run();
}

void ttDerivedTraceHost::SourceLost()
{
	SetSource(NULL);
}

void ttDerivedTraceHost::SetSource(ttTraceWindow* source)
{
	m_dataSource = source;
}

unsigned int ttDerivedTraceHost::GetColumnOffset() const
{
	return m_columnOffset;
}

bool ttDerivedTraceHost::WaitingForData() const
{
	return m_continueReadingFromFile;
}

void ttDerivedTraceHost::ReceiveData(const double &x, const double &y)
{
	m_points_store_mutex.Lock();
	m_points_store_x.push_back(x);
	m_points_store_y.push_back(y);
	m_points_store_mutex.Unlock();
}

unsigned int ttDerivedTraceHost::RunThreadCalculating(ttThread* thread, void* host)
{
	thread->EnterWorkingZone();

	unsigned int result = static_cast<ttDerivedTraceHost*>(host)->DoCalculating();

	thread->LeaveWorkingZone();

	return result;
}

unsigned int ttDerivedTraceHost::DoCalculating()
{
	std::vector<double> xMtie,yMtie,xTdev,yTdev;

	if (m_dataSource!=NULL)
	{ // Acquire data from the source trace

		// Acquire data vectors from source
		const std::vector<double>* x = NULL;
		const std::vector<double>* y = NULL;
		m_dataSource->AcquireData(x,y);

		// Recalculate with it immediately
		CalculateMetrics(*x,*y,xMtie,yMtie,xTdev,yTdev);

		// Release data vectors to source
		m_dataSource->ReleaseData();

	}
	else
	{ // Use stored data retrieved from file
		
		m_points_store_mutex.Lock();
		CalculateMetrics(m_points_store_x,m_points_store_y,xMtie,yMtie,xTdev,yTdev);
		m_points_store_mutex.Unlock();

	}

	// Re-render metric graphs
	m_mtie->Recalculate(xMtie,yMtie);
	m_tdev->Recalculate(xTdev,yTdev);
	m_mtie->ResetMasks();
	m_tdev->ResetMasks();
	for (size_t i=0; i<m_masks.size(); ++i)
	{
		if (m_masks_list->IsChecked(i))
		{
			m_mtie->AddMask(m_masks[i]);
			m_tdev->AddMask(m_masks[i]);
		}
	}
	m_mtie->Render(true);
	m_tdev->Render(true);

	m_refresh->SetLabelText("Refresh");

	return 0;
}