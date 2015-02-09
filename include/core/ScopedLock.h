#ifndef SCOPED_LOCK_H
#define SCOPED_LOCK_H

namespace ice
{
	namespace core
	{
		///@brief Automatic RAII lock for any lock type that implements lock() and unlock() methods.
		template <typename T>
		class ScopedLock
		{
		public:

			ScopedLock(T& syncObj)
				:m_syncObj(&syncObj)
			{
				m_syncObj->lock();
			}

			~ScopedLock()
			{
				m_syncObj->unlock();
			}

		private:

			T* m_syncObj;
		};

		template <typename T>
		class ScopedReadLock
		{
		public:

			ScopedReadLock(T& syncObj)
				:m_syncObj(&syncObj)
			{
				m_syncObj->lockRead();
			}

			~ScopedReadLock()
			{
				m_syncObj->unlockRead();
			}

		private:

			T* m_syncObj;
		};

		template <typename T>
		class ScopedWriteLock
		{
		public:

			ScopedWriteLock(T& syncObj)
				:m_syncObj(&syncObj)
			{
				m_syncObj->lockWrite();
			}

			~ScopedWriteLock()
			{
				m_syncObj->unlockWrite();
			}

		private:

			T* m_syncObj;
		};
	}
}

#endif