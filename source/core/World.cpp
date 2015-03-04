#include "core/World.h"
#include "core/Engine.h"

using namespace ice;
using namespace core;

void Entity::remove()
{
	detachAll();
	m_world->remove(m_id);
}

void Entity::detach(ComponentType type)
{
	if (!m_componentLookup[type].m_comp)
	{
		return;
	}

	m_componentLookup[type].m_comp->detach();

	//Remove from manager's update list and free component memory
	m_world->removeFromUpdateList(m_componentLookup[type].m_managerListIterator);
	m_world->deallocateComponent(m_componentLookup[type].m_comp);

	//Clear entry in lookup table
	m_componentLookup[type].m_comp = NULL;

	//Erase from list
	m_componentList.erase(m_componentLookup[type].m_listIterator);
	m_componentLookup[type].m_listIterator = m_componentList.end();
}

void Entity::detachAll()
{
	for (auto iter : m_componentList)
	{
		detach(iter->getType());
	}
}

bool Entity::has(ComponentType type)
{
	if (m_componentLookup.size() <= type)
	{
		return false;
	}

	return m_componentLookup[type].m_comp != NULL;
}

IComponent* Entity::get(ComponentType type)
{
	if (!has(type))
	{
		return NULL;
	}

	return m_componentLookup[type].m_comp;
}

World::~World()
{
	clear();
}

void World::init(Engine* engine)
{
	engine->registerUpdateListener(this);
}

Entity* World::create()
{
	//Calculate next ID
	unsigned int idx = 0;
	if (m_freeIndices.size() > MIN_FREE_INDICES)
	{
		idx = m_freeIndices.front();
		m_freeIndices.pop_front();
	}
	else
	{
		m_generations.push_back(0);
		m_entityObjects.push_back(Entity(0, this));
		idx = m_generations.size() - 1;
	}

	EntityID entId(idx, m_generations[idx]);
	m_entityObjects[idx] = Entity(entId, this);
	return &m_entityObjects[idx];
}

Entity* World::find(EntityID id)
{
	return &m_entityObjects[id.index()];
}

bool World::alive(EntityID id)
{
	return m_generations[id.index()] == id.generation();
}

void World::remove(EntityID id)
{
	unsigned int idx = id.index();
	m_generations[idx]++;
	m_freeIndices.push_back(idx);
}

const List<IComponent*>& World::components(ComponentType type)
{
	if (m_componentLists.size() <= type)
	{
		m_componentLists.resize(type + 1);
		m_initLists.resize(type + 1);
	}

	return m_componentLists[type];
}

void World::clear()
{
	//This can probably be optimized...

	for (auto componentList : m_componentLists)
	{
		for (auto comp : componentList)
		{
			deallocateComponent(comp);
		}
	}

	m_entityObjects.clear();
	m_freeIndices.clear();
	m_generations.clear();
}

void World::deallocateComponent(IComponent* c)
{
	IComponentPool* pool = m_componentPools[c->getType()].get();
	c->~IComponent();
	pool->deallocate(c);
}

List<IComponent*>::iterator World::addToUpdateList(IComponent* c)
{
	ComponentType type = c->getType();
	if (m_componentLists.size() <= type)
	{
		m_componentLists.resize(type + 1);
		m_initLists.resize(type + 1);
	}

	//Component lists store components for update every frame.
	m_componentLists[type].push_back(c);
	List<IComponent*>::iterator ret = m_componentLists[type].end();
	ret--;
	return ret;
}

void World::removeFromUpdateList(List<IComponent*>::iterator c)
{
	ComponentType type = (*c)->getType();
	assert(m_componentLists.size() > type);

	m_componentLists[type].erase(c);
}

void World::update()
{
	for (auto componentList : m_componentLists)//Iterate first over component type
	{
		for (auto comp : componentList)//Update all components of the same type at the same time
		{
			//Initialize components that need to be
			if (!(comp->getFlags() & CF_INITIALIZED))
			{
				comp->attach();
				comp->setFlags(comp->getFlags() | CF_INITIALIZED);
			}

			comp->update();
		}
	}
}