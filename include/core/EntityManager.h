#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/Reflection.h"
#include "core/ComponentPool.h"
#include "core/Component.h"
#include <cassert>

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

		class Entity
		{
		public:

			///@return The ID of the entity. The entity's ID consists of a 24 bit index, and an 8 bit generation value.
			EntityID getID(){ return m_id; }

			///@brief Removes this entity from the entity manager and cleans up its components.
			void remove();

			///@brief Attaches a component to this entity.
			template <typename T, typename... P>
			T* attach(P... p)
			{
				//Ensure lookup table is big enough
				unsigned int typeIdx = T::staticGetType();
				if (m_componentLookup.size() <= typeIdx)
				{
					m_componentLookup.resize(typeIdx + 1);
				}

				//Can't attach two components of same type yet...
				if (m_componentLookup[typeIdx].m_comp == NULL)
				{
					//EntityManager is responsible for allocating components so that they can be stored in one contiguous block of memory.
					T* comp = m_entityMgr->allocateComponent<T>(p...);
					comp->m_owner = this;

					//Push component to iteration list
					m_componentList.push_back(comp);

					//Store iterator to last element in list
					m_componentLookup[typeIdx].m_listIterator = m_componentList.end();
					m_componentLookup[typeIdx].m_listIterator--;
					m_componentLookup[typeIdx].m_comp = comp;

					//Add to manager update list and store iterator for later removal
					m_componentLookup[typeIdx].m_managerListIterator = m_entityMgr->addToUpdateList(comp);

					return comp;
				}

				return NULL;
			}

			///@brief Removes a component from this entity, removes it from the EntityManager's update list, and frees up its memory.
			void detach(ComponentType type);
			template <typename T> void detach(){ detach(T::staticGetType()); }

			///@return True if this entity has the specified component type, false otherwise.
			bool has(ComponentType type);
			template <typename T> bool has(){ return has(T::staticGetType()); }

			///@return The list of components attached to this entity.
			const List<IComponent*>& components(){ return m_componentList; }

			///@return A pointer to the component of the requested type, or NULL if one is not attached.
			IComponent* get(ComponentType type);
			template <typename T> T* get(){ return (T*)get(T::staticGetType()); }

			///@brief Detaches all components from this entity.
			void detachAll();

		private:

			friend class EntityManager;

			Entity(EntityID id, EntityManager* entityMgr)
				:m_id(id),
				m_entityMgr(entityMgr)
			{}

			EntityID m_id;
			EntityManager* m_entityMgr;

			struct LookupTableData
			{
				LookupTableData()
					:m_comp(NULL)
				{}

				List<IComponent*>::iterator m_listIterator;
				List<IComponent*>::iterator m_managerListIterator;
				IComponent* m_comp;
			};

			Vector<LookupTableData> m_componentLookup;
			List<IComponent*> m_componentList;
		};

		class EntityManager : public IEngineSystem
		{
		public:

			~EntityManager();

			Entity* create();

			Entity* find(EntityID id);

			bool alive(EntityID id);

			void remove(EntityID id);

			void clear();

			template <typename T, typename... P>
			T* allocateComponent(P... p)
			{
				ComponentPool<T>* pool = getComponentPool<T>();
				T* comp = (T*)pool->allocate();
				new (comp) T(p...);

				return comp;
			}

			void deallocateComponent(IComponent* c);

			List<IComponent*>::iterator addToUpdateList(IComponent* c);
			void removeFromUpdateList(List<IComponent*>::iterator c);

		private:

			Vector<List<IComponent*> > m_componentLists;

			Vector<char> m_generations;
			Vector<Entity> m_entityObjects;

			static const unsigned int MIN_FREE_INDICES = 1024;
			Deque<unsigned int> m_freeIndices;//TODO: Use a thread safe queue

			Vector<UniquePtr<IComponentPool> > m_componentPools;
			
			template <typename T>
			ComponentPool<T>* getComponentPool()
			{
				unsigned int typeIdx = T::staticGetType();
				if (m_componentPools.size() <= typeIdx)
				{
					m_componentPools.resize(typeIdx + 1);
				}

				if (m_componentPools[typeIdx].get() == NULL)
				{
					m_componentPools[typeIdx].reset(new ComponentPool<T>());
				}

				return (ComponentPool<T>*)m_componentPools[typeIdx].get();
			}
		};
	}
}

#endif