/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Macros.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_MACROS_H
#define TT_MACROS_H

#define Obliterate(pointer) \
	if (pointer!=NULL) \
	{ \
		delete pointer; \
		pointer = NULL; \
	}

#define CloseHandleSafely(handle) \
	if (handle!=INVALID_HANDLE_VALUE) CloseHandle(handle); \
	handle = INVALID_HANDLE_VALUE;

#define round(number) \
	( ( ( (number)-floor(number) ) < 0.5 ) \
	? floor(number) \
	: ceil(number) )

#define DecimalMagnitude(number) \
	( ( (number) == 0.0 ) \
	? 0 \
	: log10(abs(number)) )

/* 
  Converts a macro'd icon resource ID into a call to wxIcon("#id"), which wxWidgets needs to get an icon from a resource.
  E.g.
    wxICON_FROM_RESOURCE(AN_ICONS_FRIENDLY_NAME)
	becomes
	wxIcon("#123")
*/
#define wxICON_FROM_RESOURCE(x) wxICON_FROM_RESOURCE2(x)
#define wxICON_FROM_RESOURCE2(x) wxIcon("#"#x)

#endif // TT_MACROS_H