/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this
 * file is owned by Semtech Corporation (Semtech). This is an
 * unpublished work.  The content of this file must be used only for
 * the purpose for which it was supplied by Semtech or its
 * distributors. The content  of this file must not be copied or
 * disclosed unless authorised in writing by Semtech.
 *
 * $Id: //topsync/releasesTs2/R2.3.0/TargetApp/ToPAssert.h#1 $
 * $DateTime: 2015/10/27 10:10:59 $
 * $Change: 33006 $
 * $Revision: #1 $
 */
#ifndef __TOP_ASSERT_H___
#define __TOP_ASSERT_H__
#include "General.h"

#ifdef DEBUG_USE_ASSERTIONS
  #define ToPASSERT_GLUE(a,b) a ## b
  #define ToPASSERT_COMPILE_TIME2(cond, line) typedef ToPASSERT_GLUE(topsync_compile_time_assert_failed_at_line_, line)[(cond) ? 1 : -1];
  #define ToPASSERT_COMPILE_TIME(cond) ToPASSERT_COMPILE_TIME2(cond, __LINE__)
  #define ToPASSERT(x) ToPASSERT_Function( ((x) ? TRUE : FALSE), #x, __LINE__, __FILE__, __FUNCTION__)
  void ToPASSERT_Function(Bool condition, char const *msg, uint32 lineNo, char const *fileName, char const *funcName);
#else
  #define ToPASSERT(x) do {} while(0)
#define ToPASSERT_COMPILE_TIME(cond)
#endif

#endif /* __TOP_ASSERT_H__ */
