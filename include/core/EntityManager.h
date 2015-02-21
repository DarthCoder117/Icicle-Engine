#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/Reflection.h"

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
		class Entity;

		///@brief Class for managing entities using an object oriented interface.
		class Entity
		{
		public:

			Entity()
				:m_id(0),
				m_entityMgr(NULL)
			{}

			Entity(EntityID id, EntityManager* entityMgr)
				:m_id(id),
				m_entityMgr(entityMgr)
			{}

			bool isAlive();

			void remove();

			EntityID getID(){ return m_id; }

			EntityManager* getEntityManager(){ return m_entityMgr; }

		private:

			EntityID m_id;
			EntityManager* m_entityMgr;
		};

		class EntityManager : public IEngineSystem
		{
		public:

			Entity& create();

			Entity& get(EntityID id);

			bool alive(EntityID id);

			void remove(EntityID id);

		private:

			Vector<char> m_generations;

			static const unsigned int MIN_FREE_INDICES = 1024;
			Deque<unsigned int> m_freeIndices;//TODO: Use a thread safe queue

			Vector<Entity> m_entityObjects;
		};
	}
}

#endif