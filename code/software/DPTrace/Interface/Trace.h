/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Trace.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_TRACE_H
#define TT_TRACE_H

#include "..\..\common\MSCppHeapAllocDebug.h"

#include <wx/window.h>
#include "Thread.h"

#include <chartdir.h>

#include <wx/bitmap.h>
#include <wx/thread.h>

#include <vector>

#define KNOWN_FIELDS 215

class ttDerivedTraceHost;
class ttTraceThread;
class ttTraceWindow;

typedef struct
{
	unsigned int columnOffset;
	wxString     name;
	int          detailsIndex;
} ttParameter;

typedef struct
{
	wxString nameRaw;
	wxString nameFriendly;
	wxString unit;
	double   max;
	double   min;
	double   div;
	bool     scatter;
} ttParameterDetails;

typedef enum
{
	ttTrace_Align_Auto,
	ttTrace_Align_Min,
	ttTrace_Align_Max
} ttTrace_Align;

typedef enum
{
	ttTrace_Divisions_Auto,
	ttTrace_Divisions_Value,
	ttTrace_Divisions_Number
} ttTrace_Divisions;

typedef enum
{
	ttTrace_Extent_Valid,
	ttTrace_Extent_Lower,
	ttTrace_Extent_Higher
} ttTrace_ExtentValidity;

extern std::vector<ttTraceWindow*> traces;
extern wxMutex                     traces_mutex;
extern std::vector<ttParameter>    parameters;
extern bool	                       parametersValidated;
extern wxMutex                     parameters_mutex;
extern std::vector<ttTraceWindow*> parameterListeners;
extern ttParameterDetails          parameterDetails[KNOWN_FIELDS];

/****************
  ttTraceWindow
****************/

class ttTraceWindow : public wxWindow
{
	public:
		ttTraceWindow(wxWindow* parent, const std::vector<ttParameter>::iterator &parameter);
		ttTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex);
		void CommonConstructor(const wxString &name, const unsigned int &columnOffset, const int &detailsIndex);
		~ttTraceWindow();
		virtual void PrepareForDestruction();
		void Render(const bool &force=false);
		virtual void DoRender();
		void WriteToBuffer(const double &x, const double &y);
		void WriteToStore(const double &x, const double &y);
		virtual bool WaitingForData();
		void DataReady();
		unsigned int GetColumnOffset() const;
		wxString GetName() const;
		wxString GetUnits() const;
		void GetCurrentYScale(double* max, double* min, double* div) const;
		bool GetUserXAutoScaling() const;
		double GetUserXMaximum() const;
		double GetUserXMinimum() const;
		ttTrace_Divisions GetUserXDivisions(unsigned short* number, double* value) const;
		bool GetUserYAutoScaling() const;
		double GetUserYMaximum() const;
		double GetUserYMinimum() const;
		ttTrace_Divisions GetUserYDivisions(unsigned short* number, double* value) const;
		ttTrace_Align GetUserYAlignment() const;
		bool GetUserMargins() const;
		void SetUserXAutoScaling(const bool &value);
		void SetUserXMaximum(const double &value);
		void SetUserXMinimum(const double &value);
		void SetUserXDivisions(const ttTrace_Divisions &method, const unsigned short &number, const double &value);
		void BeginUserXUpdate();
		void EndUserXUpdate(const bool &readonly=false);
		void SetUserYAutoScaling(const bool &value);
		void SetUserYMaximum(const double &value);
		void SetUserYMinimum(const double &value);
		void SetUserYDivisions(const ttTrace_Divisions &method, const unsigned short &number, const double &value);
		void SetUserYAlignment(const ttTrace_Align &value);
		void BeginUserYUpdate();
		void EndUserYUpdate(const bool &readonly=false);
		void SetUserMargins(const bool &value);
		static wxString FormatTime(const double &value, short magnitude=10);
		static wxString FormatPreciseNumber(const double &number, const wxString &unit=wxEmptyString, const int &precisionMagnitude=-1);
		void AcquireData(const std::vector<double>* &x, const std::vector<double>* &y);
		void ReleaseData();
		void DerivedLost();

	protected:
		void OnErase(wxEraseEvent &event);
		void OnPaint(wxPaintEvent &event);
		void OnSize(wxSizeEvent &event);
		void OnMouse(wxMouseEvent &event);
		void OnCommand(wxCommandEvent &event);
		void StoreDataExtremities(const double &x, const double &y);
		virtual bool CalculateScaleX(bool* newIncluded, unsigned long* all_start, unsigned long* all_count, unsigned long* new_start, unsigned long* new_count);
		virtual void CalculateScaleX(double min, double max);
		virtual void CalculateScaleX(double min, double max, unsigned short divs);
		virtual void CalculateScaleX(double min, double max, double div);
		virtual bool CalculateScaleY();
		virtual void CalculateScaleY(double min, double max);
		virtual void CalculateScaleY(double min, double max, unsigned short divs);
		virtual void CalculateScaleY(double min, double max, double div, ttTrace_Align align=ttTrace_Align_Auto);
		static short GetTimeMagnitude(const double &value, bool* losingPrecision=NULL);
		static wxString GetScaledUnits(const int &magnitude, const wxString &unit);

		wxMenu* m_menu;

		long m_rendered_w;
		long m_rendered_h;
		bool m_waitingForData;

		wxBitmap* m_bitmap;
		bool      m_bitmapValid;
		wxMutex   m_bitmap_mutex;
		XYChart*  m_plotter;

		ttTraceThread* m_rendering_thread;
		bool           m_rendering_rerender;

		unsigned int        m_columnOffset;
		wxString            m_name;
		ttParameterDetails* m_details;

		bool   m_data_initialised;
		double m_data_x_max;
		double m_data_x_min;
		bool   m_data_y_invalidated;
		double m_data_y_max;
		double m_data_y_min;

		double   m_plot_x_max;
		double   m_plot_x_min;
		double   m_plot_x_div;
		bool     m_plot_x_initialised;
		std::vector<wxString> m_plot_x_axisLabels;
		std::vector<double>   m_plot_x_axisLabelPoints;
		double   m_plot_y_max;
		double   m_plot_y_min;
		double   m_plot_y_styled_max;
		double   m_plot_y_styled_min;
		double   m_plot_y_div;
		int      m_plot_y_baseTick;
		bool     m_plot_y_initialised;
		std::vector<wxString> m_plot_y_axisLabels;
		std::vector<double>   m_plot_y_axisLabelPoints;
		wxString m_plot_axisLabel;

		std::vector<double> m_points_store_x;
		std::vector<double> m_points_store_y;
		wxMutex             m_points_store_mutex;
		std::vector<double> m_points_buffer_x;
		std::vector<double> m_points_buffer_y;
		wxMutex             m_points_buffer_mutex;

		static const double m_auto_x_min;
		//static const double m_auto_x_max;
		//static const double m_auto_y_min;
		//static const double m_auto_y_max;
		double* m_auto_pointer_x_min;
		double* m_auto_pointer_x_max;
		double* m_auto_pointer_x_div;
		double* m_auto_pointer_y_min;
		double* m_auto_pointer_y_max;
		double* m_auto_pointer_y_div;

		unsigned long          m_crop_x_min_index;
		double                 m_crop_x_min_value;
		ttTrace_ExtentValidity m_crop_x_min_valid;
		unsigned long          m_crop_x_max_index;
		double                 m_crop_x_max_value;
		ttTrace_ExtentValidity m_crop_x_max_valid;
		unsigned long          m_crop_y_min_index;
		double                 m_crop_y_min_value;
		bool                   m_crop_y_min_valid;
		unsigned long          m_crop_y_max_index;
		double                 m_crop_y_max_value;
		bool                   m_crop_y_max_valid;

		bool              m_user_styleMargins;
		wxMutex           m_user_x_mutex;
		bool              m_user_x_autoScale;
		double            m_user_x_min;
		double            m_user_x_max;
		double            m_user_x_div_value;
		unsigned short    m_user_x_div_number;
		ttTrace_Divisions m_user_x_div_method;
		bool              m_user_x_initialised_extents;
		bool              m_user_x_initialised_divs;
		wxMutex           m_user_y_mutex;
		bool              m_user_y_autoScale;
		double            m_user_y_min;
		double            m_user_y_max;
		double            m_user_y_div_value;
		unsigned short    m_user_y_div_number;
		ttTrace_Divisions m_user_y_div_method;
		ttTrace_Align     m_user_y_align;
		bool              m_user_y_initialised_extents;
		bool              m_user_y_initialised_divs;

		ttDerivedTraceHost* m_derived;
		
		static const long ID_MENU_CONFIGURE;
		static const long ID_MENU_AUTO;
		static const long ID_MENU_LOCKY;
		static const long ID_MENU_DERIVE;
		static const long ID_MENU_ADOPT;
		DECLARE_EVENT_TABLE()
};

/****************
  ttTraceThread
****************/

class ttTraceThread : public ttThread {
	public:
		#ifdef __WXDEBUG__
			ttTraceThread(const wxString &name, ttTraceWindow* window);
		#else
			ttTraceThread(ttTraceWindow* window);
		#endif
		virtual ~ttTraceThread();

	private:
		virtual UINT StartThisThread();
		ttTraceWindow* m_window;
};

#endif // TT_TRACE_H