#include "core/ResourceCache.h"
#include <cassert>

using namespace ice;
using namespace core;

void ResourceCache::cacheResource(IResource* res)
{
	if (!res)
	{
		return;
	}

	ScopedLock<Mutex> lock(m_cacheLock);
	
	#ifdef ICE_DEBUG
	for (auto iter : m_cache)
	{
		assert(iter.second->getPath() != res->getPath());
	}
	#endif

	m_cache[res->getPath()].reset(res);
}

bool ResourceCache::hasResource(IResource* res)
{
	ScopedLock<Mutex> lock(m_cacheLock);

	auto iter = m_cache.find(res->getPath());
	if (iter != m_cache.end())
	{
		return true;
	}

	return false;
}

IResource* ResourceCache::getResource(const String& name)
{
	if (!name.empty())
	{
		ScopedLock<Mutex> lock(m_cacheLock);

		auto iter = m_cache.find(name);
		if (iter != m_cache.end())
		{
			return iter->second;
		}
	}

	return NULL;
}

void ResourceCache::removeResource(const String& name)
{
	ScopedLock<Mutex> lock(m_cacheLock);
	m_cache.erase(name);
}

void ResourceCache::renameResource(IResource* resource, const String& newName)
{
	renameResource(resource->getPath(), newName);
}

void ResourceCache::renameResource(const String& currentName, const String& newName)
{
	ScopedLock<Mutex> lock(m_cacheLock);

	auto iter = m_cache.find(currentName);
	if (iter != m_cache.end())
	{
		m_cache[newName] = iter->second;
		iter->second->m_path = newName;
	}
}