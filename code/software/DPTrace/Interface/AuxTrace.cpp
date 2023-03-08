/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/AuxTrace.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "AuxTrace.h"

#include "Floats.h"
#include "Macros.h"
#include "Main.h"
#include "TraceScaling.h"
#include "../version.h"

#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/mstream.h>
#include <wx/regex.h>
#include <wx/msw/private.h>

#include <iomanip>
#include <sstream>

/*******************
  ttAuxTraceWindow
*******************/

/*BEGIN_EVENT_TABLE(ttAuxTraceWindow, ttTraceWindow)
END_EVENT_TABLE()*/

BEGIN_EVENT_TABLE(ttAuxTraceWindow, ttTraceWindow)
	EVT_LEFT_DCLICK      ( ttAuxTraceWindow::OnMouse )
	EVT_RIGHT_DOWN       ( ttAuxTraceWindow::OnMouse )
END_EVENT_TABLE()

ttAuxTraceWindow::ttAuxTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex)
	: ttTraceWindow(parent, name, columnOffset, detailsIndex)
{
	m_waitingForData = false;
}

ttAuxTraceWindow::~ttAuxTraceWindow()
{
}

void ttAuxTraceWindow::PrepareForDestruction()
{
}

void ttAuxTraceWindow::OnMouse(wxMouseEvent &event)
{
	event.Skip(false);
}

void ttAuxTraceWindow::DoRender()
{
	if (m_rendering_thread==NULL || GetCurrentThreadId()!=m_rendering_thread->GetId()) return;
	ttThread* thisThread = m_rendering_thread;
	m_rendering_thread->EnterWorkingZone();

	int w,h;
	bool recreateGraph;
	bool newData;
	bool newIncluded;

	for (;;)
	{

		recreateGraph = false;
		newData = false;
		newIncluded = false;

		// Last point at which this routine will produce a quaranteed valid image
		// Reset the flag so if it's set by the end we know we legitimately should rerender the graph
		m_rendering_rerender = false;

		GetClientSize(&w,&h);
		// Prevent invalid bitmap & image errors
		if (w==0) w = 1;
		if (h==0) h = 1;
		if (!m_bitmapValid)
		{ // Recreate graph if physical size has changed
			recreateGraph = true;
			m_rendered_w = w;
			m_rendered_h = h;
		}

		unsigned long vectorStart_cropped = 0;
		unsigned long vectorCount_cropped = m_points_store_x.size();
		unsigned long vectorStart_new = m_points_store_x.size()-1; // So it picks the point before the newest, to create a continuous line
		unsigned long vectorCount_new = m_points_buffer_x.size()+1; // So it draw all new points plus the repeated one at the start

		m_points_store_mutex.Lock();
		m_points_buffer_mutex.Lock();

		if (!m_points_buffer_x.empty())
		{ // Prepare 'new' and main vectors
			unsigned long currentCapacity = m_points_store_x.capacity();
			if (m_points_store_x.size()+m_points_buffer_x.size() > currentCapacity)
			{ // Re-allocate main vectors
				m_points_store_x.reserve(currentCapacity*2);
				m_points_store_y.reserve(currentCapacity*2);
			}
			// Copy contents of 'new' into main
			m_points_store_x.insert(m_points_store_x.end(), m_points_buffer_x.begin(), m_points_buffer_x.end());
			m_points_store_y.insert(m_points_store_y.end(), m_points_buffer_y.begin(), m_points_buffer_y.end());
			m_points_buffer_x.clear();
			m_points_buffer_y.clear();
			vectorCount_cropped = m_points_store_x.size();
			newData = true;
		}

		m_points_buffer_mutex.Unlock();

		if (m_points_store_x.size()<2)
		{ // Can't plot one point - it creates a problem
			m_points_store_mutex.Unlock();
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			return;
		}

		// Calculate scales
		if (CalculateScaleX(&newIncluded,&vectorStart_cropped,&vectorCount_cropped,&vectorStart_new,&vectorCount_new)) recreateGraph = true;
		if (CalculateScaleY()) recreateGraph = true;

		if (recreateGraph)
		{ // Update graph from scratch
			Obliterate(m_plotter)
		}

		if (!recreateGraph && !(newData && newIncluded) && !m_rendering_rerender)
		{ // Nothing new to plot
			m_points_store_mutex.Unlock();
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			m_bitmapValid = true;
			Refresh();
			break;
		}
		
		if (m_plotter==NULL)
		{ // Create plotter

			//InitialiseChartDirector();
			m_plotter = new XYChart(w,h);
			m_plotter->setPlotArea(5,20,w-18,h-25);
			m_plotter->setClipping();
			m_plotter->addTitle(m_name.c_str(),"tahomabd.ttf",10);

			LineLayer* line = m_plotter->addLineLayer(
				DoubleArray((double*)&m_points_store_y[vectorStart_cropped],vectorCount_cropped)
			);
			line->setXData(
				DoubleArray((double*)&m_points_store_x[vectorStart_cropped],vectorCount_cropped)
			);
			m_points_store_mutex.Unlock();
			if (m_details!=NULL && m_details->scatter)
			{
				line->setLineWidth(0);
				line->getDataSet(0)->setDataSymbol(Chart::CircleShape,2,0xff0000,0xff0000);
			}
			else
			{
				line->setLineWidth(1);
			}

			// Masks
			for (std::vector<const MetricMask*>::const_iterator i=m_masks.begin(); i!=m_masks.end(); ++i)
			{
				LineLayer* mask = m_plotter->addLineLayer( DoubleArray(GetMaskY(*i), GetMaskSize(*i)), m_plotter->dashLineColor(0x000000,Chart::DashLine), (*i)->name);
				mask->setXData( DoubleArray(GetMaskX(*i), GetMaskSize(*i)) );
				mask->setLineWidth(2);
				mask->getDataSet(0)->setDataSymbol(
					( ((*i)->symbol-1) % 7 ) + 1,
					16,
					( ((*i)->symbol-1) / 7 > 0 ) ? 0x000000 : Transparent,
					0x000000
				);
			}
		
			m_plotter->yAxis()->setWidth(0);
			m_plotter->yAxis()->setLogScale(
				m_plot_y_styled_min,
				m_plot_y_styled_max,
				10.0,
				Chart::LinearTick
			);
			m_plotter->yAxis()->setLabelFormat("");
			Mark** yMarks = new Mark*[m_plot_y_axisLabels.size()];
			for (int i=0; i<m_plot_y_axisLabels.size(); ++i)
			{
				yMarks[i] = m_plotter->yAxis()->addMark(
					m_plot_y_axisLabelPoints[i],
					0x000000,
					m_plot_y_axisLabels[i].c_str(),
					/*i==m_plot_y_baseTick ? "tahomabd.ttf" : */"tahoma.ttf"
				);
				yMarks[i]->setDrawOnTop(false);
				yMarks[i]->setMarkColor(Chart::metalColor(0x333333,45),0x000000,0x000000);
			}

			m_plotter->xAxis()->setWidth(0);
			Mark** xMarks = NULL;
			if (m_plot_x_axisLabels.empty())
			{ // Use automatic X-ticking
				m_plotter->xAxis()->setLogScale(
					m_plot_x_min,
					m_plot_x_max,
					10.0,
					Chart::LinearTick
				);
				m_plotter->xAxis()->setLabelFormat("{value|,.}s");
				/*wxString format;
				if (m_plot_x_max>=86400.0)
				{ // Days & hours
					format = "{={value|d}-1}d {={value}%86400/3600}h";
				}
				else if (m_plot_x_max>=3600.0)
				{ // Hours & minutes
					format = "{value|h'h'nn}";
				}
				else
				{ // Minutes & seconds
					format = "{value|n:ss}";
				}
				m_plotter->xAxis()->setLabelFormat(format);*/
			}
			else
			{ // Use the X-ticking we defined ourselves
				m_plotter->xAxis()->setLogScale(
					m_plot_x_min,
					m_plot_x_max,
					NoValue
				);
				m_plotter->xAxis()->setLabelFormat("");
				xMarks = new Mark*[m_plot_x_axisLabels.size()];
				for (int i=0; i<m_plot_x_axisLabels.size(); ++i)
				{
					xMarks[i] = m_plotter->xAxis()->addMark(
						m_plot_x_axisLabelPoints[i],
						0x000000,
						m_plot_x_axisLabels[i].c_str(),
						"tahoma.ttf"
					);
					xMarks[i]->setDrawOnTop(false);
					xMarks[i]->setMarkColor(Chart::metalColor(0x333333,45),0x000000,0x000000);
				}
			}

			// Legend
			int legendWidth = 0;
			if (!m_masks.empty())
			{
				LegendBox* legend = m_plotter->addLegend(0,20);
				legend->setBackground(Chart::Transparent,Chart::Transparent);
				legend->setFontStyle("tahoma.ttf");
				legend->setFontSize(8);
				legend->setMargin(5,0,0,0);
				//legend->setAlignment(Chart::TopRight);
				m_plotter->layoutLegend();
				legendWidth = legend->getWidth();
			}

			m_plotter->packPlotArea(5+legendWidth,20,w-18,h);

			// Resposition legend to centre vertically
			if (legendWidth>0)
			{
				LegendBox* legend = m_plotter->getLegend();
				legend->setPos(0, 20 + (m_plotter->getPlotArea()->getHeight()-legend->getHeight())/2);
			}

			// Decimate if text is too dense
			{
				double tickSpacing = m_plotter->getPlotArea()->getHeight() / double(m_plot_y_axisLabels.size()); // The spacing
				int tickDecimation = (tickSpacing<10.0) ? (int)floor(10.0/tickSpacing)+1 : 1; // How many ticks should be represented by 1, i.e. 'show every [tickDecimation] ticks'
				int tickModulus = (m_plot_y_baseTick==-1) ? 0 : (m_plot_y_baseTick % tickDecimation); // Which of the [tickDecimation] ticks should be shown, i.e. 'show every [tickModulus]th out of [tickDecimation] ticks'
				for (int i=0; i<m_plot_y_axisLabels.size(); ++i)
				{
					if ((i % tickDecimation)!=tickModulus) yMarks[i]->setMarkColor(Chart::metalColor(0x333333,45),Transparent,0x000000);
				}
				delete[] yMarks;
			}
			if (xMarks!=NULL)
			{
				double tickSpacing = m_plotter->getPlotArea()->getWidth() / double(m_plot_x_axisLabels.size()); // The spacing
				int tickDecimation = (tickSpacing<35.0) ? (int)floor(35.0/tickSpacing)+1 : 1; // How many ticks should be represented by 1, i.e. 'show every [tickDecimation] ticks'
				for (int i=0; i<m_plot_x_axisLabels.size(); ++i)
				{
					if ((i % tickDecimation)!=0) xMarks[i]->setMarkColor(Chart::metalColor(0xcccccc,45),Transparent,0x000000);
				}
				delete[] xMarks;
			}

			m_plotter->getPlotArea()->setGridColor(
				Chart::metalColor(0x333333,45),
				Chart::metalColor(0x333333,45),
				m_plotter->getDrawArea()->dashLineColor(Chart::metalColor(0xcccccc,45),Chart::DotLine),
				m_plotter->getDrawArea()->dashLineColor(Chart::metalColor(0xcccccc,45),Chart::DotLine)
			);

		}
		else
		{ // Add to existing graph

			// Create the replacement plotter
			//InitialiseChartDirector();
			XYChart* plotter = new XYChart(w,h,0xffffff,Transparent);
			plotter->setPlotArea(
				m_plotter->getPlotArea()->getLeftX(),
				m_plotter->getPlotArea()->getTopY(),
				m_plotter->getPlotArea()->getWidth(),
				m_plotter->getPlotArea()->getHeight()
			);
			plotter->setClipping();
			if (m_plot_x_axisLabels.empty())
			{ // Use automatic X-ticking
				plotter->xAxis()->setLogScale(
					m_plot_x_min,
					m_plot_x_max,
					10.0,
					Chart::LinearTick
				);
			}
			else
			{ // Use the X-ticking we defined ourselves
				plotter->xAxis()->setLogScale(
					m_plot_x_min,
					m_plot_x_max,
					NoValue
				);
			}
			plotter->yAxis()->setLogScale(
				m_plot_y_styled_min,
				m_plot_y_styled_max,
				Chart::NoValue,
				Chart::LinearTick
			);

			// Hide as much as possible, so it's just the data being drawn
			plotter->xAxis()->setLabelFormat("");
			plotter->xAxis()->setWidth(0);
			plotter->yAxis()->setLabelFormat("");
			plotter->yAxis()->setWidth(0);
			plotter->getPlotArea()->setBackground(Transparent,Transparent,Transparent);

			// Import the previous plotter's... plot as a background
			plotter->getDrawArea()->merge(m_plotter->getDrawArea(),0,0,TopLeft,0);

			LineLayer* line = plotter->addLineLayer(
				DoubleArray((double*)&m_points_store_y[vectorStart_new],vectorCount_new)
			);
			line->setXData(
				DoubleArray((double*)&m_points_store_x[vectorStart_new],vectorCount_new)
			);
			m_points_store_mutex.Unlock();
			if (m_details!=NULL && m_details->scatter)
			{
				line->setLineWidth(0);
				line->getDataSet(0)->setDataSymbol(Chart::CircleShape,2,0xff0000,0xff0000);
			}
			else
			{
				line->setLineWidth(1);
			}

			// Swap around the plotters
			Obliterate(m_plotter)
			m_plotter = plotter;

		}

		MemBlock inMemory = m_plotter->makeChart(BMP);

		wxMemoryInputStream stream(inMemory.data,inMemory.len);
		wxImage img(stream,wxBITMAP_TYPE_BMP);
		wxBitmap* newBitmap = new wxBitmap(img);
		m_bitmap_mutex.Lock();
		if (m_bitmap) delete m_bitmap;
		m_bitmap = newBitmap;
		m_bitmap_mutex.Unlock();

		if (!m_rendering_rerender)
		{ // Not been asked to render it again in the mean time
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			m_bitmapValid = true;
			Refresh();
			break;
		}
		else
		{
			int erm=0;
		}
		// Otherwise we start again as during the previous routine we were asked to render again
	}

	thisThread->LeaveWorkingZone();
}

bool ttAuxTraceWindow::CalculateScaleX(bool* newIncluded, unsigned long* all_start, unsigned long* all_count, unsigned long* new_start, unsigned long* new_count)
{
	*newIncluded = true; // Ensure new points are plotted

	if (*m_auto_pointer_x_max>m_plot_x_max)
	{ // The data range changed, so need to rescale
		m_plot_x_initialised = false;
	}

	if (!m_plot_x_initialised)
	{ // Axis needs to be recalculated

		m_plot_x_min = 1.0;
		/*double absolute = abs(*m_auto_pointer_x_max);
		double logged = log10(absolute);
		double floored = floor(logged);
		if (EffectivelyEqual(logged,floored,9))
		{ // Use floored value, as it's very close
			m_plot_x_max = pow(10.0, floored);
		}
		else
		{ // Otherwise we should use the ceil'd value
			double ceiling = ceil(logged);
			m_plot_x_max = pow(10.0, ceiling);
		}*/
		m_plot_x_max = pow(10.0, ceil( log10( abs(*m_auto_pointer_x_max) ) ));

		m_plot_x_initialised = true;
		return true; // Axis was rescaled
	}
	else
	{
		return false; // Axis was not rescaled
	}
}

bool ttAuxTraceWindow::CalculateScaleY()
{
	wxMutexLocker userMutex(m_user_y_mutex);

	if (*m_auto_pointer_y_max>m_plot_y_max || *m_auto_pointer_y_min<m_plot_y_min)
	{ // The data range changed, so need to rescale
		m_plot_y_initialised = false;
	}

	if (!m_plot_y_initialised)
	{

		double finalMinLogged,finalMaxLogged;

		if (*m_auto_pointer_y_min==*m_auto_pointer_y_max)
		{ // Range has not yet been defined

			finalMinLogged = floor( log10( abs(*m_auto_pointer_y_min) ) );
			finalMaxLogged = ceil( log10( abs(*m_auto_pointer_y_max) ) );
			if (m_plot_y_min==m_plot_y_max)
			{ // Can't have only one magnitude plotted (one axis tick) so expand
				finalMinLogged -= 1.0;
				finalMaxLogged += 1.0;
			}

		}
		else
		{ // Range exists, so use it

			double min = *m_auto_pointer_y_min;
			double max = *m_auto_pointer_y_max;

			// The x-axis extents, as seen visually (i.e. logged, not the real values)
			double visualPlotLeft = log10(abs(m_plot_x_min));
			double visualPlotRight = log10(abs(m_plot_x_max));

			// Mask details
			size_t maskSize;
			double* maskX;
			double* maskY;

			for (size_t i=0; i<m_masks.size(); ++i)
			{ // For each mask, search for its extents and use them if they're broader
				maskSize = GetMaskSize(m_masks[i]);
				maskX = GetMaskX(m_masks[i]);
				maskY = GetMaskY(m_masks[i]);
				size_t j=0;

				// Scan through values off to the left
				for (; j<maskSize && maskX[j]<m_plot_x_min; ++j)
				{
				}
				if (j!=0 && maskSize!=m_plot_x_min)
				{ // If the first considered point is not right on the start of the x-range, interpolate between it and the previous one
					double visualXLeft = log10(abs( maskX[j-1] ));
					double visualXRight = log10(abs( maskX[j] ));
					double visualYLeft = log10(abs( maskY[j-1] ));
					double visualYRight = log10(abs( maskY[j] ));
					double gradient = (visualYRight-visualYLeft) / (visualXRight-visualXLeft);
					double visualValue = visualYLeft + (visualPlotLeft-visualXLeft)*gradient;
					double leftBorderValue = pow(10.0, visualValue);
					if (leftBorderValue<min) min = leftBorderValue;
					if (leftBorderValue>max) max = leftBorderValue;
				}

				// Scan through values in the range
				for (; j<maskSize && maskX[j]<=m_plot_x_max; ++j)
				{
					if (maskY[j] < min) min = maskY[j];
					if (maskY[j] > max) max = maskY[j];
				}

				if (j!=0 && j<maskSize && maskX[j-1]!=m_plot_x_min)
				{ // If the last considered point is not right on the end of the x-range, interpolate between it and the next one
					double visualXLeft = log10(abs( maskX[j-1] ));
					double visualXRight = log10(abs( maskX[j] ));
					double visualYLeft = log10(abs( maskY[j-1] ));
					double visualYRight = log10(abs( maskY[j] ));
					double gradient = (visualYRight-visualYLeft) / (visualXRight-visualXLeft);
					double visualValue = visualYLeft + (visualPlotRight-visualXLeft)*gradient;
					double rightBorderValue = pow(10.0, visualValue);
					if (rightBorderValue<min) min = rightBorderValue;
					if (rightBorderValue>max) max = rightBorderValue;
				}
				// Scan through values off to the right
				/*for (; j<maskSize; ++j)
				{
				}*/
			}
			
			finalMinLogged = floor( log10( abs(min) ) );
			finalMaxLogged = ceil( log10( abs(max) ) );

			m_plot_y_initialised = true; // Flag that range has been initialised

		}

		m_plot_y_min = pow(10.0, finalMinLogged);
		m_plot_y_max = pow(10.0, finalMaxLogged);
		size_t numberOfTicks = (size_t)round(finalMaxLogged) - (size_t)round(finalMinLogged) + 1;

		m_plot_y_axisLabels.resize(numberOfTicks);
		m_plot_y_axisLabelPoints.resize(numberOfTicks);

		for (size_t i=0; i<m_plot_y_axisLabels.size(); ++i)
		{
			m_plot_y_axisLabelPoints[i] = pow(10.0, finalMinLogged+(double)i);
			m_plot_y_axisLabels[i] = FormatPreciseNumber(m_plot_y_axisLabelPoints[i],"s");
		}

		m_plot_y_styled_min = m_plot_y_min;
		m_plot_y_styled_max = m_plot_y_max;

		return true; // Axis was rescaled
	}
	else
	{
		return false; // Axis wasn't rescaled
	}
}

bool ttAuxTraceWindow::WaitingForData()
{
	return false;
}

void ttAuxTraceWindow::Recalculate(const std::vector<double> &x, const std::vector<double> &y)
{
	m_points_store_mutex.Lock();

	m_data_initialised = false;
	m_points_store_x.clear();
	m_points_store_y.clear();
	m_points_store_x.reserve(x.size());
	m_points_store_y.reserve(y.size());
	for (size_t i=0; i<x.size(); ++i)
	{
		if (x[i]>=1.0 && y[i]!=0.0)
		{ // Only non-zero values are allowed, due to logarithmic scaling, and we start at 1.0 on the x-axis
			m_points_store_x.push_back(x[i]);
			m_points_store_y.push_back(y[i]);
			StoreDataExtremities(x[i],y[i]);
		}
	}

	m_points_store_mutex.Unlock();
}

void ttAuxTraceWindow::ResetMasks()
{
	m_masks.clear();
	// Invalidate drawing extents because the mask might have broader extents
	m_plot_y_initialised = false;
}

void ttAuxTraceWindow::AddMask(const MetricMask* mask)
{
	m_masks.push_back(mask);
}

/********************
  ttMtieTraceWindow
********************/

ttMtieTraceWindow::ttMtieTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex)
	: ttAuxTraceWindow(parent, name, columnOffset, detailsIndex)
{
}

ttMtieTraceWindow::~ttMtieTraceWindow()
{
}

double* ttMtieTraceWindow::GetMaskX(const MetricMask* mask) const
{
	return mask->mtie.x;
}

double* ttMtieTraceWindow::GetMaskY(const MetricMask* mask) const
{
	return mask->mtie.y;
}

size_t ttMtieTraceWindow::GetMaskSize(const MetricMask* mask) const
{
	return mask->mtie.size;
}

/********************
  ttTdevTraceWindow
********************/

ttTdevTraceWindow::ttTdevTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex)
	: ttAuxTraceWindow(parent, name, columnOffset, detailsIndex)
{
}

ttTdevTraceWindow::~ttTdevTraceWindow()
{
}

double* ttTdevTraceWindow::GetMaskX(const MetricMask* mask) const
{
	return mask->tdev.x;
}

double* ttTdevTraceWindow::GetMaskY(const MetricMask* mask) const
{
	return mask->tdev.y;
}

size_t ttTdevTraceWindow::GetMaskSize(const MetricMask* mask) const
{
	return mask->tdev.size;
}