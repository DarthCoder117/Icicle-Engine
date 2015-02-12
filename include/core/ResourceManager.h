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

			Thread m_loadThread;
			void loadingThread();
			bool m_exitFlag;

			static ResourceManager* m_inst;

			ResourceCache m_cache;

			Mutex m_mainThreadCallbackLock;
			Queue<ResourceHandle<IResource> > m_mainThreadCallbacks;

			List<IResourceFactory*> m_factories;

			ThreadEvent m_resourceWaitingToLoad;
			Mutex m_loadQueueLock;

			struct LoadTaskPackage
			{
				ResourceHandle<IResource> m_resource;
				String m_path;
			};

			Queue<LoadTaskPackage> m_loadQueue;
		};
	}
}

#endif