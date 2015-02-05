#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/ResourceCache.h"
#include "core/ResourceFactory.h"

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

			ResourceManager()
			{
				m_inst = this;
			}

			///@brief Creates a resource and loads it resource into memory asynchronously.
			///@warning The type of resource returned may differ from the type passed to the function:
			///if a resource with the same name exists, then it will be returned instead.
			IResource* load(ResourceType type, const String& path);
			template <typename T>
			T* load(const String& path)
			{
				return (T*)load(T::getClassType(), path);
			}

			void registerFactory(IResourceFactory* factory);

			ResourceCache& getResourceCache(){ return m_cache; }

		private:

			static ResourceManager* m_inst;

			ResourceCache m_cache;

			Queue<ResourceHandle<IResource> > m_mainThreadCallbacks;

			List<IResourceFactory*> m_factories;
		};
	}
}

#endif