#include "core/ResourceManager.h"
#include "core/ScopedLock.h"

using namespace ice;
using namespace core;

ResourceManager* ResourceManager::m_inst = NULL;

ResourceManager::ResourceManager()
	:m_exitFlag(false)
{
	m_inst = this;

	m_loadThread.init(&ResourceManager::loadingThread, this);
}

ResourceManager::~ResourceManager()
{
	m_exitFlag = true;
	m_resourceWaitingToLoad.set();

	m_loadThread.join();
}

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

	m_cache.cacheResource(res);

	//Queue loading task
	{
		ScopedLock<Mutex> lock(m_loadQueueLock);

		LoadTaskPackage taskPackage;
		taskPackage.m_resource = res;
		taskPackage.m_path = path;

		m_loadQueue.push(taskPackage);
	}

	//Notify loading thread
	m_resourceWaitingToLoad.set();

	return res;
}

void ResourceManager::onPostLoad()
{
	while (!m_mainThreadCallbacks.empty())
	{
		ScopedLock<Mutex> lock(m_mainThreadCallbackLock);
		m_mainThreadCallbacks.front()->onPostLoad();
		m_mainThreadCallbacks.pop();
	}
}

void ResourceManager::registerFactory(IResourceFactory* factory)
{
	m_factories.push_back(factory);
}

void ResourceManager::loadingThread()
{
	while (!m_exitFlag)
	{
		if (!m_loadQueue.empty() && m_loadQueueLock.tryLock())
		{
			//Execute loading task
			LoadTaskPackage taskPackage = m_loadQueue.front();
			taskPackage.m_resource->load(taskPackage.m_path);
			m_loadQueue.pop();

			m_loadQueueLock.unlock();

			//Add to main thread callback list
			ScopedLock<Mutex> lock(m_mainThreadCallbackLock);
			m_mainThreadCallbacks.push(taskPackage.m_resource);
		}
		else
		{
			m_resourceWaitingToLoad.wait();
			m_resourceWaitingToLoad.unset();
		}
	}
}