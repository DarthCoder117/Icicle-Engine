#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H
#include <IcicleCommon.h>
#include "core/Resource.h"
#include "core/Mutex.h"
#include "core/ReadWriteLock.h"
#include <map>

namespace ice
{
	namespace core
	{
		///@brief Manages cacheing resources for later use. The resource cache is completely thread safe.
		class ResourceCache
		{
		public:

			///@brief Adds the resource to the cache.
			void cacheResource(IResource* res);

			///@return An already cached resource (or NULL if the resource was not found).
			IResource* getResource(const String& name);

			///@return True if the resource is stored in this cache, false otherwise.
			bool hasResource(IResource* res);

			///@brief Removes a resource from the cache.
			void removeResource(const String& name);

			///@brief Clears the entire cache.
			void removeAllResources(){ m_cache.clear(); }

			///@brief Renames a cached resource.
			///The resource instance's name will be updated, as will the entry in the cache. 
			///However, the old cache entry is kept so that paths that are not updated will still refer to the same resource.
			void renameResource(IResource* resource, const String& newName);
			///@brief Renames a cached resource.
			///The resource instance's name will be updated, as will the entry in the cache. 
			///However, the old cache entry is kept so that paths that are not updated will still refer to the same resource.
			void renameResource(const String& currentName, const String& newName);

		private:

			Map<String, ResourceHandle<IResource> > m_cache;

			core::Mutex m_cacheLock;
		};
	}
}

#endif