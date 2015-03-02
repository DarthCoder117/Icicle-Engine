#ifndef POSITION_H
#define POSITION_H
#include <IcicleCommon.h>
#include "core/Component.h"

namespace ice
{
	namespace core
	{
		class Position : public Component<Position>
		{
		public:

			glm::vec2 Pos;
		};
	}
}

#endif