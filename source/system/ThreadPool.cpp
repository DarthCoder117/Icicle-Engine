#include "system/ThreadPool.h"

using namespace ice;
using namespace system;

//TODO: Implement the worker threads...

ThreadPool::ThreadPool(u32 maxThreads)
	:m_threads(maxThreads),
	m_terminationFlag(false)
{
	Vector<UniquePtr<Thread> >::iterator iter;
	for (iter = m_threads.begin(); iter != m_threads.end(); ++iter)
	{
		iter->reset(new Thread(&ThreadPool::workerThread, this));
	}
}

ThreadPool::~ThreadPool()
{
	m_terminationFlag = true;

	//Wait for all threads to finish.
	Vector<UniquePtr<Thread> >::iterator iter;
	for (iter = m_threads.begin(); iter != m_threads.end(); ++iter)
	{
		(*iter)->join();
	}
}

Future<void> ThreadPool::run(Function<void()> func)
{
	Promise<void> promise = Promise<void>{};
	Future<void> future = promise.get_future();

	Task* task = new Task();
	task->m_completionPromise = std::move(promise);
	task->m_task = func;

	{
		ScopedLock<Mutex> lock(m_queueLock);
		m_taskQueue.push(task);
	}

	return future;
}

void ThreadPool::workerThread()
{
	while (!m_terminationFlag)
	{
		Task* task = NULL;
		{
			ScopedLock<Mutex> lock(m_queueLock);
			task = m_taskQueue.front();
			m_taskQueue.pop();
		}

		if (task)
		{
			task->m_task();

			try
			{
				task->m_completionPromise.set_value();
			}
			catch (std::future_error){}
		}
	}
}

