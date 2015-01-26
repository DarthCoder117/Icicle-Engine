#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "core/SubSystem.h"

namespace ice
{
	namespace graphics
	{
		class Graphics : public core::SubSystem<Graphics> {
		public:
			Graphics();
			
			void render();

			
		private:
		};
	}
}

#endif //GRAPHICS_H