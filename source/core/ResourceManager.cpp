#include "core/ResourceManager.h"

using namespace ice;
using namespace core;

ResourceManager* ResourceManager::m_inst = NULL;

IResource* ResourceManager::load(ResourceType type, const String& path)
{
	//Check cache first.
	IResource* res = m_cache.getResource(path);
	if (res && (res->isLoaded() || res->getLoadState() == RLS_LOADING))
	{
		return res;
	}

	//Create resource if it doesn't exist
	for (auto iter : m_factories)
	{
		res = iter->create(type);
		if (res)
		{
			res->setLoadState(RLS_LOADING);
			break;
		}
	}

	if (!res)
	{
		return NULL;
	}

	//TODO: Queue loading task
}

void ResourceManager::registerFactory(IResourceFactory* factory)
{
	m_factories.push_back(factory);
}