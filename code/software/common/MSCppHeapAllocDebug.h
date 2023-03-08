/**
 * $Id: //topsync/mainline/utilities/common/MSCppHeapAllocDebug.h#1 $
 * $DateTime: 2011/01/18 14:43:24 $
 * $Change: 19524 $
 * $Revision: #1 $
 * 
 * Use this to allow memory leak dumps resulting from the new
 * operator to display the filename and line from which the original
 * allocation was made.
 *
 * NOTE: THIS ONLY APPLIES WHEN BUILDING ON WINDOWS WITH MICROSOFT
 * COMPILER! 
 *
 * NOTE: THIS MUST THE THE *VERY FIRST* INCLUDE IN THE FILE AND MUST
 * BE INCLUDED IN EACH C FILE THAT IS TO BE HEAP-ALLOC DEBUGGED
 *
 * See "_CRTDBG_MAP_ALLOC does not work as expected"
 *     http://support.microsoft.com/kb/140858
 * See "Finding Memory Leaks Using the CRT Library"
 *     http://msdn.microsoft.com/en-us/library/x98tx3cf(v=VS.100).aspx 
 */
#ifndef __MS_CPP_HEAP_ALLOC_DEBUG_H__
#define __MS_CPP_HEAP_ALLOC_DEBUG_H__

#if defined(_MSC_VER) && (_MSC_VER > 1300)

#ifdef _DEBUG
   #ifndef _CRTDBG_MAP_ALLOC
      #define _CRTDBG_MAP_ALLOC
   #endif
   #include <stdlib.h>
   #include <crtdbg.h>
   #define MYDEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define new MYDEBUG_NEW   
#endif // _DEBUG

#endif // _MSC_VER

#endif // __MS_CPP_HEAP_ALLOC_DEBUG_H__

