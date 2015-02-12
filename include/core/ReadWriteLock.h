#ifndef READ_WRITE_LOCK_H
#define READ_WRITE_LOCK_H
#include <IcicleCommon.h>

#ifdef ICE_WINDOWS
#include <Windows.h>
#endif

namespace ice
{
	namespace core
	{
		///@brief The ReadWriteLock allows a resource to be locked by only one writer at once, but multiple readers.
		class ReadWriteLock
		{
		public:

			ReadWriteLock();

			void lockWrite();

			bool tryLockWrite();

			void unlockWrite();

			void lockRead();

			bool tryLockRead();

			void unlockRead();

		private:

			#ifdef ICE_WINDOWS
			PSRWLOCK m_lock;
			#endif
		};
	}
}

#endif