#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <core/Uncopyable.h>
#include <IcicleCommon.h>
#include <core/Error.h>
#include <core/Thread.h>
#include <core/Mutex.h>
#include <core/ThreadEvent.h>

namespace ice
{
	namespace system
	{
		class ThreadPool : core::Uncopyable
		{
		public:

			ThreadPool(u32 maxThreads);
			~ThreadPool();

			///@brief Runs a task on the thread pool.
			SharedPtr<core::ThreadEvent> run(Function<void()> func);

		private:

			struct Task
			{
			public:

				SharedPtr<core::ThreadEvent> m_completionEvent;
				Function<void()> m_task;
			};


			void workerThread();
			
			core::Mutex m_queueLock;
			Queue<Task*> m_taskQueue;///@todo This would be faster if it was a lock-free queue.

			core::ThreadEvent m_tasksAvailable;

			Vector<core::Thread> m_threads;

			bool m_terminationFlag;
		};
	}
}

#endif //THREADPOOL_H