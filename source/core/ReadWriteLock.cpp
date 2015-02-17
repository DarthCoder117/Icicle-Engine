#include "core/ReadWriteLock.h"

using namespace ice;
using namespace core;

ReadWriteLock::ReadWriteLock()
{
	#ifdef ICE_WINDOWS
	InitializeSRWLock(m_lock);
	#endif
}

void ReadWriteLock::lockWrite()
{
	#ifdef ICE_WINDOWS
	AcquireSRWLockExclusive(m_lock);
	#endif
}

bool ReadWriteLock::tryLockWrite()
{
	#ifdef ICE_WINDOWS
	return TryAcquireSRWLockExclusive(m_lock) != 0;
	#else
	return 0;
	#endif
}

void ReadWriteLock::unlockWrite()
{
	#ifdef ICE_WINDOWS
	#pragma warning(suppress: 26110)
	ReleaseSRWLockExclusive(m_lock);
	#endif
}

void ReadWriteLock::lockRead()
{
	#ifdef ICE_WINDOWS
	AcquireSRWLockShared(m_lock);
	#endif
}

bool ReadWriteLock::tryLockRead()
{
	#ifdef ICE_WINDOWS
	return TryAcquireSRWLockShared(m_lock) != 0;
	#else
	return 0;
	#endif
}

void ReadWriteLock::unlockRead()
{
	#ifdef ICE_WINDOWS
	ReleaseSRWLockShared(m_lock);
	#endif
}