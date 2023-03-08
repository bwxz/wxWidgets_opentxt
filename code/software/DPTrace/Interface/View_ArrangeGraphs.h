/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/View_ArrangeGraphs.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_VIEW_ARRANGEGRAPHS_H
#define TT_VIEW_ARRANGEGRAPHS_H

#include <wx/dialog.h>
#include "Validation.h"

#include <wx/button.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/msw/registry.h>

class ValidatorHost;

void RatioSingleToDouble(const double &single, double &doubleX, double &doubleY);

class ArrangeGraphsDialog : public wxDialog, public ValidatorHost
{
	public:
		ArrangeGraphsDialog(
			wxWindow* parent
		);
		virtual ~ArrangeGraphsDialog();

	protected:
		void OnMethod(wxCommandEvent &event);
		bool TransferDataToWindow();
		bool TransferDataFromWindow();
		bool Validate();
		wxRegKey* m_regKey;
		wxRadioButton* m_columns;
		wxTextCtrl*    m_columns_field;
		wxRadioButton* m_rows;
		wxTextCtrl*    m_rows_field;
		wxRadioButton* m_ratio;
		wxTextCtrl*    m_ratio_x;
		wxTextCtrl*    m_ratio_y;

		unsigned short m_value_method;
		unsigned short m_value_columns;
		unsigned short m_value_rows;
		double         m_value_ratio_x;
		double         m_value_ratio_y;

	private:
		DECLARE_CLASS(ArrangeGraphsDialog)
		DECLARE_EVENT_TABLE()
};

#endif // TT_VIEW_ARRANGEGRAPHS_H