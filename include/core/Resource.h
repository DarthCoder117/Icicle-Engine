#ifndef RESOURCE_H
#define RESOURCE_H
#include <IcicleCommon.h>
#include "core/Reflection.h"
#include "core/Uncopyable.h"

namespace ice
{
	namespace core
	{
		enum RESOURCE_LOAD_STATE
		{
			RLS_UNLOADED,
			RLS_LOADING,
			RLS_PARTIALLY_LOADED,
			RLS_LOADED
		};

		class ResourceManager;
		class ResourceCache;

		///@brief Base resource interface. Don't derive from this, use Resource<T> instead.
		class IResource : public Uncopyable
		{
		public:

			IResource();

			virtual ~IResource(){}

			///@brief Should load the resource from the specified path.
			///Usually this is just a path to open a stream from the FileSystem, but if some resource types need to use weird path types, then they can.
			///This method is usually called from a seperate loading thread, so creation of graphics objects, or anything else that must be done synchronously can be done in onPostLoad.
			virtual void load(const String& path) = 0;

			///@brief Called from the rendering thread when the resource is finished loading.
			virtual void onPostLoad(){}

			///@brief Unloads the resource from memory.
			virtual void unload() = 0;

			///@brief Sets the load state of this resource and the associated futures. 
			void setLoadState(RESOURCE_LOAD_STATE state);
			///@return The current load state of the resource.
			///Some resources can be partially loaded which means they are available to use, but may be lower resolution or limited in some other way.
			///It is up to the individual resource implementations to define what constitutes being partially loaded vs fully loaded.
			RESOURCE_LOAD_STATE getLoadState();

			///@return True if the resource has been loaded, false otherwise.
			bool isLoaded();

			virtual ResourceType getType() = 0;

			///@brief Adds a reference to this resource for the resource manager to track.
			void addRef();
			///@brief Releases a reference to this resource for the resource manager to track.
			void release();

			///@return How many references to this resource exist.
			unsigned int getRefCount();

			///@brief Sets the path/name of this resource.
			void setPath(const String& path);
			///@return The path/name of the resource.
			const String& getPath(){ return m_path; }

			///@brief Called internally by the resource cache when a resource is added.
			void onCached(ResourceCache* cache);

			friend class ResourceCache;

		protected:

			void partiallyLoaded()
			{
				setLoadState(RLS_PARTIALLY_LOADED);
			}

			void loaded()
			{
				setLoadState(RLS_LOADED);
			}

		private:

			Atomic<RESOURCE_LOAD_STATE> m_state;

			Atomic<unsigned int> m_refCount;

			String m_path;

			ResourceCache* m_cache;
		};

		///@brief Base class for resources.
		template <typename T>
		class Resource : public IResource
		{
		public:

			static ResourceType getClassType()
			{
				static ResourceType type = typeid(T).hash_code();
				return type;
			}

			ResourceType getType()
			{
				return T::getClassType();
			}
		};

		///@brief Serves as a handle to a resource instance and automatically updates reference counts.
		template <typename T>
		class ResourceHandle
		{
		public:

			ResourceHandle()
				:m_ptr(NULL)
			{}

			ResourceHandle(T* ptr)
				:m_ptr(ptr)
			{
				if (m_ptr)
					m_ptr->addRef();
			}

			ResourceHandle(const ResourceHandle<T>& oth)
				:m_ptr(oth.m_ptr)
			{
				if (m_ptr)
					m_ptr->addRef();
			}

			~ResourceHandle()
			{
				if (m_ptr)
					m_ptr->release();
			}

			bool isValid() const
			{
				return m_ptr != NULL;
			}

			T* get() const
			{
				return m_ptr;
			}

			void reset(T* ptr)
			{
				if (m_ptr)
					m_ptr->release();

				m_ptr = ptr;

				if (m_ptr)
					m_ptr->addRef();
			}

			T* operator->()
			{
				return m_ptr;
			}

			const T* operator->() const
			{
				return m_ptr;
			}

			T& operator*()
			{
				return *m_ptr;
			}

			const T& operator*() const
			{
				return *m_ptr;
			}

			operator T*()
			{
				return m_ptr;
			}

			ResourceHandle<T>& operator= (const ResourceHandle<T> &rhs)
			{
				reset(rhs.get());

				return *this;
			}

			ResourceHandle<T>& operator= (T* rhs)
			{
				reset(rhs);

				return *this;
			}

		private:

			T* m_ptr;
		};
	}
}

#endif