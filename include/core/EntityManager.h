#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/Reflection.h"
#include "core/ComponentType.h"

namespace ice
{
	namespace core
	{
		///@brief An entity ID is just a set of index and generation bits like described on the BitSquid engine blog.
		struct EntityID
		{
			EntityID()
			:m_id(0)
			{}

			EntityID(unsigned int fullID)
				:m_id(fullID)
			{}

			EntityID(unsigned int index, unsigned char generation)
				:m_id(index)
			{}

			unsigned int m_id;

			unsigned int index(){ return m_id & ENTITY_INDEX_MASK; }

			unsigned char generation(){ return (m_id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

			static const unsigned ENTITY_INDEX_BITS = 22;
			static const unsigned ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;

			static const unsigned ENTITY_GENERATION_BITS = 8;
			static const unsigned ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS) - 1;
		};

		class EntityManager;

		typedef unsigned int SystemType;

		///@brief Components are just basic structures. The only requirement for components is that they store the ID of their owning object.
		struct Component
		{
			EntityID Owner;
		};

		///@brief Interface for entity systems.
		class IEntitySystem
		{
		public:

			virtual SystemType getType() = 0;

		protected:

			static SystemType getNextSystemType()
			{
				static SystemType type = 0;
				SystemType ret = type;
				type++;
				return ret;
			}
		};

		///@brief Base interface for entity systems.
		template <typename T>
		class EntitySystem : public IEntitySystem
		{
		public:

			SystemType getType()
			{
				return EntitySystem<T>::staticGetType();
			}

			SystemType staticGetType()
			{
				static type = getNextSystemType();
				return type;
			}
		};

		class EntityManager : public IEngineSystem
		{
		public:

			EntityID create();

			bool alive(EntityID id);

			void remove(EntityID id);

		private:

			Vector<char> m_generations;

			static const unsigned int MIN_FREE_INDICES = 1024;
			Deque<unsigned int> m_freeIndices;//TODO: Use a thread safe queue

			List<IEntitySystem*> m_systems;
			Vector<IEntitySystem*> m_systemLookup;

			static Vector<List<Component*> > m_componentLists;
		};
	}
}

#endif