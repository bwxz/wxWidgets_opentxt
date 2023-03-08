/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/SystemSelect.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_SYSTEMSELECT_H
#define TT_SYSTEMSELECT_H

#include <wx/dialog.h>

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>

class ttSystemSelect : public wxDialog
{
	public:
		ttSystemSelect(
			wxWindow* parent,
			unsigned long* const systems
		);
		virtual ~ttSystemSelect();

	protected:
		bool TransferDataToWindow();
		bool TransferDataFromWindow();

	private:
		wxCheckBox* m_clk1_1;
		wxCheckBox* m_clk1_2;
		wxCheckBox* m_clk1_3;
		wxCheckBox* m_clk2_1;
		wxCheckBox* m_clk2_2;
		wxCheckBox* m_clk2_3;
		wxCheckBox* m_ptp1_1;
		wxCheckBox* m_ptp1_2;
		wxCheckBox* m_ptp1_3;
		wxCheckBox* m_ptp2_1;
		wxCheckBox* m_ptp2_2;
		wxCheckBox* m_ptp2_3;
		wxCheckBox* m_node1_1;
		wxCheckBox* m_node1_2;
		wxCheckBox* m_node1_3;
		wxCheckBox* m_node2_1;
		wxCheckBox* m_node2_2;
		wxCheckBox* m_node2_3;
		wxCheckBox* m_system_1;
		wxCheckBox* m_system_2;
		wxCheckBox* m_system_3;
		unsigned long* const m_systems;

	DECLARE_CLASS(ttSystemSelect)
};

#endif // TT_SYSTEMSELECT_H