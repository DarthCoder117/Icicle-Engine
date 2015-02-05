#include "core/Resource.h"
#include "core/ResourceCache.h"

using namespace ice;
using namespace core;

IResource::IResource()
	:m_state(RLS_UNLOADED),
	m_loadedPromise(new Promise<void>()),
	m_partiallyLoadedPromise(new Promise<void>()),
	m_refCount(0)
{
	m_loadedFuture = m_loadedPromise->get_future();
	m_partiallyLoadedFuture = m_partiallyLoadedPromise->get_future();
}

RESOURCE_LOAD_STATE IResource::getLoadState()
{
	return m_state;
}

bool IResource::isLoaded()
{
	return (m_state != RLS_UNLOADED) && (m_state != RLS_LOADING);
}

void IResource::wait()
{
	while (m_state != RLS_LOADED)
	{
		m_loadedFuture.wait();
	}
}

void IResource::waitPartial()
{
	while (m_state != RLS_PARTIALLY_LOADED)
	{
		m_partiallyLoadedFuture.wait();
	}
}

void IResource::setLoadState(RESOURCE_LOAD_STATE state)
{
	if (state == RLS_UNLOADED && m_state != RLS_UNLOADED)//If changing to unloaded state...
	{
		//Reset futures
		m_loadedPromise.reset(new Promise<void>());
		m_loadedFuture = m_loadedPromise->get_future();
		m_partiallyLoadedPromise.reset(new Promise<void>());
		m_partiallyLoadedFuture = m_partiallyLoadedPromise->get_future();
	}
	else if (state == RLS_PARTIALLY_LOADED && m_state != RLS_PARTIALLY_LOADED)//If changing to partially loaded state...
	{
		m_partiallyLoadedPromise->set_value();
	}
	else if (state == RLS_PARTIALLY_LOADED && m_state != RLS_PARTIALLY_LOADED)//If changing to loaded state...
	{
		m_loadedPromise->set_value();
	}

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