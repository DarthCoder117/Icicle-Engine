#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/ResourceCache.h"
#include "core/ResourceFactory.h"
#include "core/Thread.h"
#include "core/ThreadEvent.h"

namespace ice
{
	namespace core
	{
		///@brief Manages creation and loading of resources and contains the resource cache.
		class ResourceManager : public core::IEngineSystem
		{
		public:

			static ResourceManager* instance()
			{
				return m_inst;
			}

			ResourceManager();

			~ResourceManager();

			///@brief Creates a resource and loads it resource into memory asynchronously.
			///@warning The type of resource returned may differ from the type passed to the function:
			///if a resource with the same name exists, then it will be returned instead.
			IResource* load(ResourceType type, const String& path);
			template <typename T>
			T* load(const String& path)
			{
				return (T*)load(T::getClassType(), path);
			}

			///@brief Registers a resource factory with the manager.
			void registerFactory(IResourceFactory* factory);

			///@brief Called internally to create graphics resources from the rendering thread.
			void onPostLoad();

			ResourceCache& getResourceCache(){ return m_cache; }

		private:

			//Thread m_loadThread;
			void loadingThread();
			bool m_exitFlag;

			static ResourceManager* m_inst;

			ResourceCache m_cache;

			Queue<ResourceHandle<IResource> > m_mainThreadCallbacks;

			List<IResourceFactory*> m_factories;

			//Mutex m_loadQueueLock;
			//ThreadEvent m_queueConditionVar;
			//Queue<Function<void()> > m_loadQueue;
		};
	}
}

#endif