#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H
#include "core/Component.h"

namespace ice
{
	namespace core
	{
		class IComponentPool
		{
		public:

			virtual ~IComponentPool(){}

			virtual IComponent* allocate() = 0;

			virtual void deallocate(IComponent* comp) = 0;
		};

		template <typename T, unsigned int MaxCapacity = 512>
		class ComponentPool : public IComponentPool
		{
		public:

			ComponentPool()
				:m_size(0),
				m_capacity(MaxCapacity),
				m_buffer(NULL)
			{
				m_buffer = (T*)malloc(MaxCapacity*sizeof(T));
			}

			~ComponentPool()
			{
				free(m_buffer);
			}

			IComponent* allocate()
			{
				unsigned int idx;
				if (m_freeIndices.size() > MaxCapacity / 4)
				{
					idx = m_freeIndices.front();
					m_freeIndices.pop();
				}
				else
				{
					idx = m_size;
					m_size++;

					if (m_size >= m_capacity)
					{
						return NULL;
					}
				}

				return m_buffer + idx;
			}

			void deallocate(IComponent* comp)
			{
				unsigned int idx = ((T*)comp) - m_buffer;
				
				m_freeIndices.push(idx);
			}

		private:

			Queue<unsigned int> m_freeIndices;

			unsigned int m_capacity;
			unsigned int m_size;
			T* m_buffer;
		};
	}
}

#endif