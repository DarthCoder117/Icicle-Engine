#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

namespace ice
{
	namespace core
	{
		typedef unsigned int ComponentType;

		class Entity;

		///@brief Components are just basic structures. The only requirement for components is that they store the ID of their owning object.
		class IComponent
		{
		public:

			IComponent()
				:m_owner(NULL)
			{}

			virtual ~IComponent(){}

			virtual ComponentType getType() = 0;

			Entity* owner(){ return m_owner; }

		protected:

			friend class Entity;

			Entity* m_owner;

			static ComponentType nextComponentType()
			{
				static ComponentType counter = 0;
				ComponentType ret = counter;
				counter++;
				return ret;
			}
		};

		template <typename T, typename BaseClass = IComponent>
		class Component : public BaseClass
		{
		public:

			virtual ComponentType getType()
			{
				return T::staticGetType();
			}

			static ComponentType staticGetType()
			{
				static ComponentType type = IComponent::nextComponentType();
				return type;
			}
		};
	}
}

#endif