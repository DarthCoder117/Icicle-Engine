#include "system/ThreadPool.h"
#include "core/ScopedLock.h"

using namespace ice;
using namespace system;

ThreadPool::ThreadPool(u32 maxThreads)
	:m_threads(maxThreads),
	m_terminationFlag(false)
{
	for (unsigned int i = 0; i < m_threads.size(); ++i)
	{
		m_threads[i].init(&ThreadPool::workerThread, this);
	}
}

ThreadPool::~ThreadPool()
{
	m_terminationFlag = true;

	//Wake up threads
	m_tasksAvailable.set();

	//Wait for all threads to finish.
	for (unsigned int i = 0; i < m_threads.size(); ++i)
	{
		m_threads[i].join();
	}
}

SharedPtr<core::ThreadEvent> ThreadPool::run(Function<void()> func)
{
	Task* task = new Task();
	task->m_completionEvent = makeShared<core::ThreadEvent>();
	task->m_task = func;

	{
		core::ScopedLock<core::Mutex> lock(m_queueLock);
		m_taskQueue.push(task);
		m_tasksAvailable.set();
	}

	return task->m_completionEvent;
}

void ThreadPool::workerThread()
{
	while (!m_terminationFlag)
	{
		//Wait for tasks to become available
		m_tasksAvailable.wait();
		m_tasksAvailable.unset();

		//Pop tasks from queue
		core::ScopedLock<core::Mutex> lock(m_queueLock);
		while (!m_taskQueue.empty())
		{
			Task* task = m_taskQueue.front();
			m_taskQueue.pop();

			//Execute task
			if (task)
			{
				task->m_task();

				try
				{
					task->m_completionEvent->set();
				}
				catch (std::future_error){}
			}
		}
	}
}

