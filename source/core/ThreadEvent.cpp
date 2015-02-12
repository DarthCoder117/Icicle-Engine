#include "core/ThreadEvent.h"
#include "core/Thread.h"

using namespace ice;
using namespace core;

#ifdef ICE_WINDOWS
ThreadEvent::ThreadEvent()
	:m_event(NULL)
{
	m_event = CreateEvent(NULL, true, false, NULL);
}

ThreadEvent::~ThreadEvent()
{
	CloseHandle(m_event);
}
#else
ThreadEvent::ThreadEvent()
	:m_signaled(false)
{

}

ThreadEvent::~ThreadEvent()
{

}
#endif

void ThreadEvent::set()
{
	#ifdef ICE_WINDOWS
	SetEvent(m_event);
	#else
	m_signaled = true;
	#endif
}

void ThreadEvent::unset()
{
	#ifdef ICE_WINDOWS
	ResetEvent(m_event);
	#else
	m_signaled = false;
	#endif
}

bool ThreadEvent::isSet()
{
	#ifdef ICE_WINDOWS
	return WaitForSingleObject(m_event, 0) != WAIT_TIMEOUT;
	#else
	return m_signaled;
	#endif
}

void ThreadEvent::wait()
{
	#ifdef ICE_WINDOWS
	WaitForSingleObject(m_event, INFINITE);
	#else
	while (!m_signaled)//This is my horrible hackish implementation and needs to be replaced by a working Linux equivalent of Win32 Events...
	{
		
	}
	#endif
}