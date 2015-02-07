#include "core/Thread.h"

using namespace ice;
using namespace core;

u32 Thread::getID()
{
	if (m_thread)
	{
		return (u32)m_thread->get_id().hash();
	}

	return 0;
}

void Thread::join(u32 waitTimeMs)
{
	if (m_thread)
	{
		m_thread->join();
	}
}

u32 Thread::Current::getCurrentThreadID()
{
	return std::this_thread::get_id().hash();
}

void Thread::Current::sleep(u32 timeMs)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(timeMs));
}

void Thread::Current::yield()
{
	std::this_thread::yield();
}