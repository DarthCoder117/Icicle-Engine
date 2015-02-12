#ifndef MUTEX_H
#define MUTEX_H
#include <IcicleCommon.h>

#ifdef ICE_WINDOWS
#include <Windows.h>
#endif

namespace ice
{
	namespace core
	{
		///@brief Mutual exclusion lock. On Windows this is implemented using a critical section for performance.
		///On other platforms this serves as a wrapper around std::mutex.
		class Mutex
		{
		public:

			Mutex();

			~Mutex();

			void lock();

			bool tryLock();

			void unlock();

		private:

			#ifdef ICE_WINDOWS
			CRITICAL_SECTION m_mutex;
			#else
			std::mutex m_mutex;
			#endif
		};
	}
}

#endif