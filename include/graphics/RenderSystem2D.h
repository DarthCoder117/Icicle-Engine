#ifndef RENDER_SYSTEM_2D
#define RENDER_SYSTEM_2D
#include "graphics/RenderEventListener.h"
#include <core/World.h>
#include <core/Component.h>

namespace ice
{
	namespace graphics
	{
		///@brief Renders the entity attached to as a square. Requires a Position component.
		class SquareRenderer : public core::Component<SquareRenderer>
		{
		public:

			SquareRenderer(const glm::vec2& dimensions=glm::vec2(1.0f, 1.0f), const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
				:Dimensions(dimensions),
				Color(color)
			{}

			glm::vec2 Dimensions;
			glm::vec4 Color;
		};

		class GraphicsDriver;
		class VertexShader;
		class PixelShader;
		class InputLayout;
		class VertexBuffer;
		class ConstantBuffer;

		class RenderSystem2D : public RenderEventListener
		{
		public:

			void init(GraphicsDriver* driver, core::World* world);

			void render(RENDERING_STAGE stage);

		private:

			GraphicsDriver* m_driver;
			core::World* m_world;

			VertexShader* m_shapeVS;
			PixelShader* m_shapePS;

			InputLayout* m_shapeLayout;

			VertexBuffer* m_squareBuffer;

			ConstantBuffer* m_positionBuffer;
			ConstantBuffer* m_colorBuffer;
		};
	}
}

#endif