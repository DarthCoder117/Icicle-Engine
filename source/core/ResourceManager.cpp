#include "core/ResourceManager.h"
#include "core/ScopedLock.h"

using namespace ice;
using namespace core;

ResourceManager* ResourceManager::m_inst = NULL;

ResourceManager::ResourceManager()
	:m_exitFlag(false)
{
	m_inst = this;

	//m_loadThread.init(&ResourceManager::loadingThread, this);
}

ResourceManager::~ResourceManager()
{
	//m_loadThread.join();
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
	//ScopedLock<Mutex> lock(m_loadQueueLock);
	//m_loadQueue.push(std::bind(&IResource::load, res, path));

	//Notify loading thread
	//m_queueConditionVar.set();

	return res;
}

void ResourceManager::onPostLoad()
{

}

void ResourceManager::registerFactory(IResourceFactory* factory)
{
	m_factories.push_back(factory);
}

void ResourceManager::loadingThread()
{
	while (!m_exitFlag)
	{
		//Pop load task from queue
		//m_loadQueueLock.lock();
		//m_loadQueue.front()();
		//m_loadQueue.pop();

		//if (m_loadQueue.empty())
		{
			//m_loadQueueLock.unlock();
			//m_queueConditionVar.wait();
		}

		//m_loadQueueLock.unlock();
	}
}