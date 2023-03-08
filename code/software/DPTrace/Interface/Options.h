/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Options.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_OPTIONS_H
#define TT_OPTIONS_H

#include <wx/msw/registry.h>

extern wxRegKey registryBase;

extern bool verbose;
extern bool runningGui;

extern unsigned short graphArrangement_method;
extern unsigned short graphArrangement_columns;
extern unsigned short graphArrangement_rows;
extern double         graphArrangement_ratio;

enum
{
	arrangeRatio,
	arrangeColumns,
	arrangeRows
};

#define REGKEY_BASE       "Options"
#define REGKEY_GA_COLUMNS "Graph layout columns"
#define REGKEY_GA_ROWS    "Graph layout rows"
#define REGKEY_GA_RATIO   "Graph layout aspect ratio"
#define REGKEY_GA_METHOD  "Graph layout method"

#endif // TT_OPTIONS_H