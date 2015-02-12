#ifndef THREAD_EVENT_H
#define THREAD_EVENT_H
#include <IcicleCommon.h>

#ifdef ICE_WINDOWS
#include <Windows.h>
#endif

namespace ice
{
	namespace core
	{
		///@brief ThreadEvent is used to communicate among multiple threads.
		///A thread event can be set in order to wake up any threads that are waiting on it.
		///@warning Cross platform version still under construction/testing
		class ThreadEvent
		{
		public:

			ThreadEvent();

			~ThreadEvent();

			///@brief Sets the event to signal all threads that are waiting for it to wake up.
			void set();

			///@brief Unsets the event.
			void unset();

			///@return Returns whether the event is set or not without blocking. 
			bool isSet();

			///@brief Blocks the current thread until the event becomes set.
			void wait();

		private:

			#ifdef ICE_WINDOWS
			HANDLE m_event;
			#else
			Atomic<bool> m_signaled;
			#endif
		};
	}
}

#endif