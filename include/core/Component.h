#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

namespace ice
{
	namespace core
	{
		typedef unsigned int ComponentType;

		class Entity;

		enum COMPONENT_FLAGS
		{
			CF_INITIALIZED = 0x01
		};

		///@brief Components are just basic structures. The only requirement for components is that they store the ID of their owning object.
		class IComponent
		{
		public:

			IComponent()
				:m_owner(NULL),
				m_flags(0)
			{}

			virtual ~IComponent(){}

			///@brief Called when after the component has been attached to an entity.
			virtual void attach(){}

			///@brief Called when the component is detached from an entity.
			virtual void detach(){}

			///@brief Called every update tick.
			virtual void update(){}

			void setFlags(char flags){ m_flags = flags; }

			char getFlags(){ return m_flags; }

			virtual ComponentType getType() = 0;

			Entity* owner(){ return m_owner; }

		protected:

			friend class Entity;

			Entity* m_owner;

			char m_flags;

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