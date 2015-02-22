#ifndef COMPONENT_TYPE_H
#define COMPONENT_TYPE_H
#include <IcicleCommon.h>
#include "core/StringUtils.h"
#include "core/Uncopyable.h"

namespace ice
{
	namespace core
	{
		///@brief ComponentType stores type information about components.
		///Each new component that's created must use RegisterComponentType() to define an instance of this.
		class ComponentType
		{
		public:

			ComponentType(const String& typeName, const size_t size);

			size_t typeID(){ return m_typeID; }
			const String& typeName(){ return m_typeName; }
			unsigned int typeIndex(){ return m_typeIndex; }

			size_t size(){ return m_size; }

		private:

			size_t m_typeID;
			String m_typeName;
			unsigned int m_typeIndex;

			size_t m_size;
		};

		template <typename T>
		class ComponentTypeRegistry
		{
		public:

			static const ComponentType type;
		};

		#define RegisterComponentType(typeName) const ice::core::ComponentTypeRegistry::type = ice::core::ComponentType(#typeName, sizeof(typeName));

		///@brief Manages a list of the registered component types.
		class ComponentTypes
		{
			static unsigned int numComponentTypes(){ return m_types.size(); }

			static ComponentType* get(unsigned int idx){ return m_types[idx]; }

			template <typename T>
			static ComponentType* get()
			{
				return &ComponentTypeRegistry<T>::type;
			}

		private:

			friend class ComponentType;

			static unsigned int addComponentType(ComponentType* type);

			static Vector<ComponentType*> m_types;
		};
	}
}

#endif