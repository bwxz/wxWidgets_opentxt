/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Thread.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Thread.h"

#include <process.h>

#ifdef __WXDEBUG__

	const DWORD MS_VC_EXCEPTION=0x406D1388;

	#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
	#pragma pack(pop)

	void SetThreadName(unsigned int threadId, const char* threadName)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = threadId;
		info.dwFlags = 0;
		__try
		{
			RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
		}
		__except (EXCEPTION_CONTINUE_EXECUTION)
		{
		}
	}

	std::vector<ttThread*> threadObjectList;

	static wxString GetThreadPurpose(ttThreadPurpose purpose) {
		switch (purpose) {
			case threadMain:
				return "Main";
			case threadLogging:
				return "Logging";
			case threadReceiving:
				return "Receiving";
			case threadDrawing:
				return "Drawing";
			case threadPlotting:
				return "Plotting";
			case threadReading:
				return "Reading";
			case threadDestroying:
				return "Destroying";
			case threadCalculating:
				return "Calculating";
			case threadOpening:
				return "Opening";
			default:
				return "Unknown";
		}
	}

	/******************
	  wxAdvancedMutex
	******************/

	wxAdvancedMutex::wxAdvancedMutex(
		const wxString name,
		wxMutexType mutexType
	) :
		m_lockedBy(wxEmptyString),
		m_lockedById(0),
		m_lockedByThread(NULL),
		m_name(name)
	{
		m_internal = new wxMutexInternal(mutexType);

		if ( !m_internal->IsOk() ) {
			delete m_internal;
			m_internal = NULL;
		}
	}

	wxAdvancedMutex::~wxAdvancedMutex() {
		delete m_internal;
	}

	bool wxAdvancedMutex::IsOk() const {
		return m_internal != NULL;
	}

	wxMutexError wxAdvancedMutex::Lock(const wxString fileName, const int &lineNumber) {
		wxCHECK_MSG( m_internal, wxMUTEX_INVALID, _T("wxAdvancedMutex::Lock(): not initialized") );
		wxASSERT_MSG(m_lockedById!=GetCurrentThreadId()+1, _T("Attempting to lock mutex when already locked by the same thread."));

		wxString description = m_name + wxString(" @ ") + fileName.AfterLast('\\') + wxString::Format(":%i",lineNumber);
		wxMutexError result;

		if (m_lockedByThread!=NULL && m_lockedByThread->m_mutexBeingLocked!=NULL) {
		// Search for imminent deadlock
			if (wxIsMainThread()) {
			// Special check to see if the GUI mutex will cause a deadlock
				// If we're locked by a thread that's trying to lock the GUI (which is most probably held by THIS thread) it's a deadlock
				wxASSERT_MSG(m_lockedByThread->m_mutexBeingLocked!=reinterpret_cast<wxAdvancedMutex*>(1), _T("GUI mutex deadlock imminent!"));
			}
			if (m_lockedByThread->m_mutexBeingLocked!=reinterpret_cast<wxAdvancedMutex*>(1)) {
				// If we're locked by a thread that's trying to lock something locked by THIS thread, it's a deadlock
				wxASSERT_MSG(m_lockedByThread->m_mutexBeingLocked->m_lockedById!=GetCurrentThreadId()+1, _T("Deadlock imminent!"));
			}
		}

		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->GetId()==GetCurrentThreadId()) {
				(*i)->m_mutexLockingDescription = description;
				(*i)->m_mutexBeingLocked = this;

				result = m_internal->Lock();

				m_lockedById = GetCurrentThreadId()+1;
				m_lockedByThread = *i;
				m_lockedBy = GetThreadPurpose((*i)->m_purpose) + wxString(", ") + fileName.AfterLast('\\') + wxString::Format(":%i",lineNumber);
				(*i)->m_mutexesLocked.push_back(m_name);
				(*i)->m_mutexLockedDescriptions.push_back(description);
				(*i)->m_mutexLockingDescription = wxEmptyString;
				(*i)->m_mutexBeingLocked = NULL;
				return result;
			}
		}

		result = m_internal->Lock(); // Perform the lock in case it wasn't done above
		m_lockedById = GetCurrentThreadId()+1;
		m_lockedBy = wxString::Format("unknown:%i, ",GetCurrentThreadId()) + fileName.AfterLast('\\') + wxString::Format(":%i",lineNumber);
		return result;
	}

	wxMutexError wxAdvancedMutex::LockTimeout(unsigned long ms) {
		wxCHECK_MSG( m_internal, wxMUTEX_INVALID, _T("wxAdvancedMutex::Lock(): not initialized") );

		return m_internal->Lock(ms);
	}

	wxMutexError wxAdvancedMutex::TryLock() {
		wxCHECK_MSG( m_internal, wxMUTEX_INVALID, _T("wxAdvancedMutex::TryLock(): not initialized") );

		return m_internal->TryLock();
	}

	wxMutexError wxAdvancedMutex::Unlock() {
		wxCHECK_MSG( m_internal, wxMUTEX_INVALID, _T("wxAdvancedMutex::Unlock(): not initialized") );
		wxASSERT_MSG(m_lockedById!=0, _T("Attempting to unlock mutex when already unlocked."));

		wxMutexError result;

		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->GetId()==GetCurrentThreadId()) {
				m_lockedById = 0;
				m_lockedByThread = NULL;
				m_lockedBy = wxEmptyString;

				result = m_internal->Unlock();

				for (int j=(*i)->m_mutexesLocked.size()-1; j>=0; j--) {
					if ((*i)->m_mutexesLocked[j]==m_name) {
						(*i)->m_mutexesLocked.erase((*i)->m_mutexesLocked.begin()+j);
						(*i)->m_mutexLockedDescriptions.erase((*i)->m_mutexLockedDescriptions.begin()+j);
						return result;
					}
				}
			}
		}

		m_lockedById = 0;
		m_lockedBy = wxEmptyString;
		result = m_internal->Unlock(); // Perform the unlock in case it wasn't done above
		return result;
	}

	/************************
	  wxAdvancedMutexLocker
	************************/

	wxAdvancedMutexLocker::wxAdvancedMutexLocker(
		wxAdvancedMutex &mutex,
		const wxString fileName,
		const int &lineNumber
	) :
		m_isOk(false),
		m_mutex(mutex)
	{
		m_isOk = ( m_mutex.Lock(fileName,lineNumber) == wxMUTEX_NO_ERROR );
	}

	wxAdvancedMutexLocker::~wxAdvancedMutexLocker() {
		if ( IsOk() ) m_mutex.Unlock();
	}

	bool wxAdvancedMutexLocker::IsOk() const {
		return m_isOk;
	}

	/*************************
	  Global Mutex Functions
	*************************/

	/// The following three functions manipulate the debug data for mutex un-/locking operations. They do not actually lock or unlock the mutexes
	void LockGuiMutexBegin(const wxString fileName, const int &lineNumber) {
		wxString description = wxString("GUI @ ") + fileName.AfterLast('\\') + wxString::Format(":%i",lineNumber);
		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->GetId()==GetCurrentThreadId()) {
				(*i)->m_mutexLockingDescription = description;
				(*i)->m_mutexBeingLocked = reinterpret_cast<wxAdvancedMutex*>(1);
				return;
			}
		}
	}

	void LockGuiMutexEnd(const wxString fileName, const int &lineNumber) {
		wxString description = wxString("GUI @ ") + fileName.AfterLast('\\') + wxString::Format(":%i",lineNumber);
		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->GetId()==GetCurrentThreadId()) {
				(*i)->m_mutexesLocked.push_back("GUI");
				(*i)->m_mutexLockedDescriptions.push_back(description);
				(*i)->m_mutexLockingDescription = wxEmptyString;
				(*i)->m_mutexBeingLocked = NULL;
				return;
			}
		}
	}

	void UnlockGuiMutexEnd() {
		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->GetId()==GetCurrentThreadId()) {
				for (int j=(*i)->m_mutexesLocked.size()-1; j>=0; j--) {
					if ((*i)->m_mutexesLocked[j]=="GUI") {
						(*i)->m_mutexesLocked.erase((*i)->m_mutexesLocked.begin()+j);
						(*i)->m_mutexLockedDescriptions.erase((*i)->m_mutexLockedDescriptions.begin()+j);
						return;
					}
				}
			}
		}
	}

	/******************
	  Debug Functions
	******************/

	static ttThread* FindThread(const ttThreadPurpose &thread) {
		for (std::vector<ttThread*>::iterator i=threadObjectList.begin(); i<threadObjectList.end(); i++) {
			if ((*i)->m_purpose==thread) return *i;
		}
		return NULL;
	}

	/// Returns the name of the mutex the thread's trying to lock, and where this is happening
	wxString GetMutexBeingLocked(ttThreadPurpose thread) {
		ttThread* threadObject = FindThread(thread);
		if (threadObject==NULL) return "No such thread";
		wxString result = threadObject->GetLockedMutexDescription(-1);
		if (result==wxEmptyString) return "None";
		if (threadObject->m_mutexBeingLocked==NULL || threadObject->m_mutexBeingLocked==reinterpret_cast<wxAdvancedMutex*>(1)) return result + wxString(" [mutex status unknown]");
		return result + wxString(" by ") + threadObject->m_mutexBeingLocked->m_lockedBy;
	}

	/// Returns the number of the thread that locked the mutex the given thread is trying to lock, and where this is happening
	wxString GetMutexLocker(ttThreadPurpose thread) {
		ttThread* threadObject = FindThread(thread);
		if (threadObject==NULL) return "No such thread";
		if (threadObject->m_mutexBeingLocked==NULL || threadObject->m_mutexBeingLocked==reinterpret_cast<wxAdvancedMutex*>(1)) return "None";
		return threadObject->m_mutexBeingLocked->m_lockedBy;
	}

	/// Returns the name of the mutex the thread locked at a given level, and where it happens
	/// Locking mutexes is thought to form a hierarchy of locked mutexes, to which these 'levels' refer
	wxString GetMutexLocked(ttThreadPurpose thread, unsigned int level) {
		ttThread* threadObject = FindThread(thread);
		if (threadObject==NULL) return "No such thread";
		return threadObject->GetLockedMutexDescription(level);
	}

#endif // ifdef __WXDEBUG__

/*********
  Thread
*********/

#ifdef __WXDEBUG__

	ttThread::ttThread(ttThreadPurpose purpose, ThreadFunction runFunction, ttThread** mainPointerToThis, unsigned int myStackSize)
		: m_mutexBeingLocked(NULL),
		m_purpose(purpose),
		msThread(NULL),
		m_localMutex(wxMUTEX_DEFAULT),
		m_keepRunning(true),
		RunFunction(runFunction),
		RunFunctionWithPointer(NULL),
		stackSize(myStackSize),
		m_mainPointerToThis(mainPointerToThis),
		m_pointer(NULL)
	{
		if (purpose==threadMain) msThreadId = GetCurrentThreadId();
		m_name = GetThreadPurpose(purpose) + " Thread";
		threadObjectList.push_back(this);
	}

	ttThread::ttThread(ttThreadPurpose purpose, ThreadPointerFunction runFunction, void* pointer, ttThread** mainPointerToThis, unsigned int myStackSize)
		: m_mutexBeingLocked(NULL),
		m_purpose(purpose),
		msThread(NULL),
		m_localMutex(wxMUTEX_DEFAULT),
		m_keepRunning(true),
		RunFunction(NULL),
		RunFunctionWithPointer(runFunction),
		stackSize(myStackSize),
		m_mainPointerToThis(mainPointerToThis),
		m_pointer(pointer)
	{
		if (purpose==threadMain) msThreadId = GetCurrentThreadId();
		m_name = GetThreadPurpose(purpose) + " Thread";
		threadObjectList.push_back(this);
	}

#else

	ttThread::ttThread(ThreadFunction runFunction, ttThread** mainPointerToThis, unsigned int myStackSize)
		: msThread(NULL),
		m_localMutex(wxMUTEX_DEFAULT),
		m_keepRunning(true),
		RunFunction(runFunction),
		RunFunctionWithPointer(NULL),
		stackSize(myStackSize),
		m_mainPointerToThis(mainPointerToThis),
		m_pointer(NULL)
	{
	}

	ttThread::ttThread(ThreadPointerFunction runFunction, void* pointer, ttThread** mainPointerToThis, unsigned int myStackSize)
		: msThread(NULL),
		m_localMutex(wxMUTEX_DEFAULT),
		m_keepRunning(true),
		RunFunction(NULL),
		RunFunctionWithPointer(runFunction),
		stackSize(myStackSize),
		m_mainPointerToThis(mainPointerToThis),
		m_pointer(pointer)
	{
	}

#endif // ifdef __WXDEBUG__

ttThread::~ttThread()
{
}

bool ttThread::Run() {
	unsigned int (__stdcall *windowsFunction)(void*) = (unsigned int (__stdcall *)(void*))ttThread::StartThread;
	uintptr_t result = _beginthreadex(
		NULL,
		0,
		windowsFunction,
		(void*)this,
		0,
		&msThreadId
	);
	if (result==0)
	{ // Error
		delete this;
		return false;
	}
	else
	{
		msThread = (HANDLE)result;
		return true;
	}
}

unsigned int __stdcall ttThread::StartThread(void* actualThread, ...) {
	ttThread* thread = static_cast<ttThread*>(actualThread);
	HANDLE threadHandle = thread->GetHandle();
	#ifdef __WXDEBUG__
	{
		SetThreadName(thread->GetId(), thread->GetName().c_str());
	}
	#endif
	UINT result = thread->StartThisThread();

	delete thread;
	CloseHandle(threadHandle);
	return result;
}

unsigned int ttThread::StartThisThread()
{
	if (RunFunctionWithPointer!=NULL)
	{
		return RunFunctionWithPointer(this,m_pointer);
	}
	else if (RunFunction!=NULL)
	{
		return RunFunction(this);
	}
	else
	{
		return 0;
	}
}

HANDLE ttThread::GetHandle() {
	return msThread;
}

unsigned int ttThread::GetId() {
	return msThreadId;
}

#ifdef __WXDEBUG__
	const wxString& ttThread::GetName() const
	{
		return m_name;
	}
#endif

bool ttThread::KeepRunning() {
	return m_keepRunning;
}

void ttThread::EnterWorkingZone() {
	if (GetCurrentThreadId()!=msThreadId) return;
	m_localMutex.Lock();
}

void ttThread::LeaveWorkingZone() {
	if (GetCurrentThreadId()!=msThreadId) return;
	// Thread is about to destroy itself, so tell the main pointer to it that it's gone
	if (m_mainPointerToThis!=NULL) *m_mainPointerToThis = NULL;
	m_localMutex.Unlock();
}

void ttThread::Terminate() {
	m_keepRunning = false;
}

void ttThread::WaitForTermination(unsigned long timeout) {
	if (GetCurrentThreadId()==msThreadId) return;
	// Wait for it to lock (i.e. for it to first become unlocked by the thread). If successful, no need to unlock again because it's about to be (or has already been) destroyed
	if (m_localMutex.LockTimeout(timeout)==wxMUTEX_TIMEOUT)
	{ // Force temination
		//ExitThread(msThreadId);
	}
}

void ttThread::DisassociateMainPointer(ttThread** oldPointer)
{
	if (oldPointer==m_mainPointerToThis) m_mainPointerToThis = NULL;
}

#ifdef __WXDEBUG__
	wxString ttThread::GetLockedMutexDescription(int index) {
		if (index<0) return m_mutexLockingDescription;
		if (m_mutexLockedDescriptions.size()==0 || index>=m_mutexLockedDescriptions.size()) return wxString("None");
		return m_mutexLockedDescriptions[index];
	}
#endif