#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <IcicleCommon.h>
#include "core/Component.h"

namespace ice
{
	namespace core
	{
		class Transform : public Component<Transform>
		{
		public:

			void setPosition(const glm::vec3& position);
			const glm::vec3& getPosition(){ return m_position; }

			const glm::mat4x4& getWorldTransform(){ return m_worldTransform; }

		private:

			glm::mat4x4 m_worldTransform;

			glm::vec3 m_position;
		};
	}
}

#endif