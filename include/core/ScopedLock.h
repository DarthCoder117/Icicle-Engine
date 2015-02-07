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
	}
}

#endif