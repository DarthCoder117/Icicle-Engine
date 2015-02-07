#ifndef THREAD_H
#define THREAD_H
#include <IcicleCommon.h>

namespace ice
{
	namespace core
	{
		///@brief Wrapper around thread implementation.
		///The current implementation just wraps std::thread for portability.
		class Thread
		{
		public:

			Thread()
			{}

			template <typename F, typename... P>
			Thread(F&& f, P&&... p)
				:m_thread(new std::thread(f, p...))
			{}

			template <typename F, typename... P>
			void init(F&& f, P&&... p)
			{
				m_thread.reset(new std::thread(f, p...));
			}

			///@return True if the thread has been succesfully created, false otherwise.
			bool isValid(){ return m_thread != NULL; }

			///@brief Waits for the thread to finish executing. The default is to wait indefinitely.
			void join(u32 waitTimeMs = (u32)-1);

			///@return This thread object's thread ID.
			u32 getID();

			///@brief Functions to manipulate the current thread.
			class Current
			{
			public:

				///@brief Returns the thread ID of the current thread of execution.
				static u32 getCurrentThreadID();

				///@brief Sleeps the current thread for the specified number of milliseconds.
				static void sleep(u32 timeMs);

				///@brief Yields the remainder of this thread's timeslice.
				static void yield();
			};

		protected:

			UniquePtr<std::thread> m_thread;
		};
	}
}

#endif