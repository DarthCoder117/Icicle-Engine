#include "core/Mutex.h"

using namespace ice;
using namespace core;

Mutex::Mutex()
{
	#ifdef ICE_WINDOWS
	InitializeCriticalSection(&m_mutex);
	#endif
}

Mutex::~Mutex()
{
	#ifdef ICE_WINDOWS
	DeleteCriticalSection(&m_mutex);
	#endif
}

void Mutex::lock()
{
	#ifdef ICE_WINDOWS
	EnterCriticalSection(&m_mutex);
	#else
	m_mutex.lock();
	#endif
}

bool Mutex::tryLock()
{
	#ifdef ICE_WINDOWS
	return TryEnterCriticalSection(&m_mutex) == TRUE;
	#else
	return m_mutex.try_lock();
	#endif
}

void Mutex::unlock()
{
	#ifdef ICE_WINDOWS
	LeaveCriticalSection(&m_mutex);
	#else
		m_mutex.unlock();
	#endif
}