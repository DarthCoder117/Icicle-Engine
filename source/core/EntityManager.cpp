#include "core/EntityManager.h"

using namespace ice;
using namespace core;

EntityID EntityManager::create()
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
		idx = m_generations.size() - 1;
	}

	return EntityID(idx, m_generations[idx]);
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