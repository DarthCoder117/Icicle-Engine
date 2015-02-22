#include "core/Resource.h"
#include "core/ResourceCache.h"

using namespace ice;
using namespace core;

IResource::IResource()
	:m_state(RLS_UNLOADED),
	m_refCount(0)
{

}

RESOURCE_LOAD_STATE IResource::getLoadState()
{
	return m_state;
}

bool IResource::isLoaded()
{
	return (m_state != RLS_UNLOADED) && (m_state != RLS_LOADING);
}

void IResource::setLoadState(RESOURCE_LOAD_STATE state)
{
	m_state = state;
}

void IResource::addRef()
{
	m_refCount++;
}

void IResource::release()
{
	if (m_refCount > 0)
	{
		m_refCount--;
	}
}

unsigned int IResource::getRefCount()
{
	return m_refCount;
}

void IResource::setPath(const String& path)
{
	if (m_cache)
	{
		m_cache->renameResource(m_path, path);
	}
}

void IResource::onCached(ResourceCache* cache)
{
	m_cache = cache;
}