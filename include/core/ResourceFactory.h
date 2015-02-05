#ifndef RESOURCE_FACTORY_H
#define RESOURCE_FACTORY_H
#include <IcicleCommon.h>
#include "core/Uncopyable.h"
#include "core/Resource.h"

namespace ice
{
	namespace core
	{
		///@brief Creates resources given a resource type.
		///For automatically implementing a factory, use the template version: ResourceFactory<T, P...>
		class IResourceFactory : public Uncopyable
		{
		public:

			virtual ~IResourceFactory(){}

			virtual IResource* create(ResourceType type) = 0;
		};

		///@brief Template version of resource factory with support for default parameters passed to constructor.
		template <typename T, typename P...>
		class ResourceFactory
		{
		public:

			IResource* create(ResourceType type)
			{
				if (type == T::getClassType())
				{
					return new T(P...);
				}

				return NULL;
			}
		};
	}
}

#endif