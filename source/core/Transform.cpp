#include "core/Transform.h"

using namespace ice;
using namespace core;

void Transform::setPosition(const glm::vec3& position)
{
	if (m_position == position)
	{
		return;
	}

	m_position = position;

	m_worldTransform = glm::translate(glm::mat4x4(), m_position);
}