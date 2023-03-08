/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Thread.h $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#ifndef TT_THREAD_H
#define TT_THREAD_H

#include "..\..\common\MSCppHeapAllocDebug.h"

#include <wx/string.h>
#include <wx/thread.h>

#include "Windows.h"
#include <wx/msw/winundef.h>
#include <vector>

class ttThread;

typedef unsigned int (*ThreadFunction)(ttThread*); // An external function that receives a pointer to the thread that called it
typedef unsigned int (*ThreadPointerFunction)(ttThread*, void*); // An external function that also receives a custom pointer


#ifdef __WXDEBUG__

	#define AutoLockMutex(mutex,lockerName) wxAdvancedMutexLocker lockerName(mutex,wxString(__FILE__),__LINE__);
	#define LockMutex(mutex) mutex.Lock(wxString(__FILE__),__LINE__);
	#define UnlockMutex(mutex) mutex.Unlock();
	#define AutoLockGuiMutex(lockerName) \
		LockGuiMutexBegin(wxString(__FILE__),__LINE__); \
		wxMutexGuiLocker guiLock(); \
		LockGuiMutexEnd(wxString(__FILE__),__LINE__);
	#define LockGuiMutex() \
		LockGuiMutexBegin(wxString(__FILE__),__LINE__); \
		wxMutexGuiEnter(); \
		LockGuiMutexEnd(wxString(__FILE__),__LINE__);
	#define UnlockGuiMutex() \
		wxMutexGuiLeave(); \
		UnlockGuiMutexEnd();
	#define InitialiseMutex(mutex) mutex(#mutex)
	#define InitialiseMutexCustom(mutex,mutexType) mutex(#mutex,mutexType)
	#define tsMutex wxAdvancedMutex

	class ttThread;

	extern std::vector<ttThread*> threadObjectList;

	typedef enum {
		threadMain=0,
		threadLogging,
		threadReceiving,
		threadDrawing,
		threadPlotting,
		threadReading,
		threadDestroying,
		threadCalculating,
		threadOpening
	} ttThreadPurpose;

	/******************
	  wxMutexInternal (must be declared, as it's in thread.cpp)
	******************/

	class wxMutexInternal {
		public:
			wxMutexInternal(wxMutexType mutexType);
			~wxMutexInternal();
			bool IsOk() const;
			wxMutexError Lock();
			wxMutexError Lock(unsigned long ms);
			wxMutexError TryLock();
			wxMutexError Unlock();

		private:
			wxMutexError LockTimeout(DWORD milliseconds);
			HANDLE m_mutex;
			unsigned long m_owningThread;
			wxMutexType m_type;
	};

	/******************
	  wxAdvancedMutex
	******************/

	class wxAdvancedMutex {
		public:
			wxAdvancedMutex(const wxString name, wxMutexType mutexType = wxMUTEX_DEFAULT);
			~wxAdvancedMutex();
			bool IsOk() const;
			wxMutexError Lock(const wxString fileName, const int &lineNumber);
			wxMutexError LockTimeout(unsigned long ms);
			wxMutexError TryLock();
			wxMutexError Unlock();
			wxString m_lockedBy;
			unsigned int m_lockedById;
			ttThread* m_lockedByThread;

		protected:
			wxMutexInternal* m_internal;
			wxString m_name;
			friend class wxConditionInternal;
			wxDECLARE_NO_COPY_CLASS(wxAdvancedMutex);
	};

	/************************
	  wxAdvancedMutexLocker
	************************/

	class wxAdvancedMutexLocker {
		public:
			wxAdvancedMutexLocker(wxAdvancedMutex &mutex, const wxString fileName, const int &lineNumber);
			~wxAdvancedMutexLocker();
			bool IsOk() const;

		private:
			wxAdvancedMutexLocker(const wxAdvancedMutexLocker&);
			wxAdvancedMutexLocker& operator=(const wxAdvancedMutexLocker&);
			bool m_isOk;
			wxAdvancedMutex& m_mutex;
	};

	/*************************
	  Global Mutex Functions
	*************************/

	void LockGuiMutexBegin(const wxString fileName, const int &lineNumber);
	void LockGuiMutexEnd(const wxString fileName, const int &lineNumber);
	void UnlockGuiMutexEnd();

	/******************
	  Debug Functions
	******************/

	wxString GetMutexBeingLocked(ttThreadPurpose thread);
	wxString GetMutexLocker(ttThreadPurpose thread);
	wxString GetMutexLocked(ttThreadPurpose thread, unsigned int level);

#else

	#define AutoLockMutex(mutex,lockerName) wxMutexLocker lockerName(mutex);
	#define LockMutex(mutex) mutex.Lock();
	#define UnlockMutex(mutex) mutex.Unlock();
	#define AutoLockGuiMutex(lockerName) wxMutexGuiLocker guiLock();
	#define LockGuiMutex() wxMutexGuiEnter();
	#define UnlockGuiMutex() wxMutexGuiLeave();
	#define InitialiseMutex(mutex) mutex()
	#define InitialiseMutexCustom(mutex,mutexType) mutex(mutexType)
	#define tsMutex wxMutex

#endif // ifdef __WXDEBUG__


/***********
  ttThread
***********/

class ttThread {
	public:
		#ifdef __WXDEBUG__
			ttThread(ttThreadPurpose purpose, ThreadFunction runFunction, ttThread** mainPointerToThis=NULL, unsigned int myStackSize = 16384);
			ttThread(ttThreadPurpose purpose, ThreadPointerFunction runFunction, void* pointer, ttThread** mainPointerToThis=NULL, unsigned int myStackSize = 16384);
		#else
			ttThread(ThreadFunction runFunction, ttThread** mainPointerToThis=NULL, unsigned int myStackSize = 16384);
			ttThread(ThreadPointerFunction runFunction, void* pointer, ttThread** mainPointerToThis=NULL, unsigned int myStackSize = 16384);
		#endif
		virtual ~ttThread();
		bool Run();
		HANDLE GetHandle();
		unsigned int GetId();
		bool KeepRunning(); // Asks whether the thread's main while loop should continue
		void EnterWorkingZone(); // Locks the mutex, alerting the program that the thread's running
		void LeaveWorkingZone(); // Unlocks the mutex, alerting the program that the thread's not running
		void Terminate(); // Tells the thread to lower its m_keepRunning flag, this not performing another iteration of the main while loop
		void WaitForTermination(unsigned long timeout); // Waits for the mutex to become unlocked, this signifying the thread's finished
		void DisassociateMainPointer(ttThread** oldPointer); // Tells the thread not to reset the main pointer to it before it's destroyed (because it's not interested in this thread anymore)
		#ifdef __WXDEBUG__
		const wxString& GetName() const;
			wxString GetLockedMutexDescription(int index);
			wxString m_mutexLockingDescription;
			wxAdvancedMutex* m_mutexBeingLocked;
			bool mutexDescriptionChanging;
			std::vector<wxString> m_mutexesLocked;
			std::vector<wxString> m_mutexLockedDescriptions;
			ttThreadPurpose m_purpose;
		#endif

	protected:
		static unsigned int __stdcall StartThread(void* actualThread, ...);
		virtual unsigned int StartThisThread();
		HANDLE msThread;
		unsigned int msThreadId;
		wxMutex m_localMutex;
		bool m_keepRunning;
		ThreadFunction RunFunction;
		ThreadPointerFunction RunFunctionWithPointer;
		const unsigned int stackSize;
		ttThread** m_mainPointerToThis;
		void* m_pointer; // A supplied pointer, passed to the run function
		#ifdef __WXDEBUG__
			wxString m_name;
		#endif
};

#endif // TT_THREAD_H