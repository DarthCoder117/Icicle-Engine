#include "core/EntityManager.h"

using namespace ice;
using namespace core;

bool Entity::isAlive()
{
	return m_entityMgr->alive(m_id);
}

void Entity::remove()
{
	m_entityMgr->remove(m_id);
}

Entity& EntityManager::create()
{
	unsigned int idx = 0;
	if (m_freeIndices.size() > MIN_FREE_INDICES)
	{
		idx = m_freeIndices.front();
		m_freeIndices.pop_front();
	}
	else
	{
		m_generations.push_back(0);
		m_entityObjects.push_back(Entity());
		idx = m_generations.size() - 1;
	}

	EntityID entID(idx, m_generations[idx]);
	m_entityObjects[idx] = Entity(entID, this);

	return m_entityObjects[idx];
}

Entity& EntityManager::get(EntityID id)
{
	return m_entityObjects[id.index()];
}

bool EntityManager::alive(EntityID id)
{
	return m_generations[id.index()] == id.generation();
}

void EntityManager::remove(EntityID id)
{
	unsigned int idx = id.index();
	m_generations[idx]++;
	m_freeIndices.push_back(idx);
}