#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <core/Uncopyable.h>
#include <IcicleCommon.h>
#include "core/Error.h"

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
			Future<void> run(Function<void()> func);

		private:

			struct Task
			{
			public:

				Promise<void> m_completionPromise;
				Function<void()> m_task;
			};


			void workerThread();
			
			Mutex m_queueLock;
			Queue<Task*> m_taskQueue;///@todo This would be faster if it was a lock-free queue.

			Vector<UniquePtr<Thread> > m_threads;

			bool m_terminationFlag;
		};
	}
}

#endif //THREADPOOL_H