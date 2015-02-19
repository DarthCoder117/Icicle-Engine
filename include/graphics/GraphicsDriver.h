#ifndef GRAPHICS_DRIVER_H
#define GRAPHICS_DRIVER_H
#include <IcicleCommon.h>
#include <core/Uncopyable.h>
#include "graphics/Texture2D.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/InputLayout.h"
#include "graphics/ShaderCompiler.h"
#include "graphics/VertexShader.h"
#include "graphics/PixelShader.h"

namespace ice
{
	namespace graphics
	{
		enum GRAPHICS_DRIVER_TYPE
		{
			GDT_DIRECT3D11,
			GDT_OPENGL,
			GDT_UNKNOWN
		};

		struct DriverCaps
		{
		public:

			bool concurrentCreation;///< Whether or not the driver supports creating resources in a seperate thread
		};

		enum DISPLAY_FLAGS
		{
			DF_FULLSCREEN = 0x01
		};

		class GraphicsDriver : public core::Uncopyable
		{
		public:

			virtual ~GraphicsDriver(){}

			///@brief Recreates the graphics devices with a different resolution/other settings.
			virtual void reset(const Vec2u& resolution) = 0;

			///@brief Changes the viewport size.
			virtual void setViewport(const Vec2& vp) = 0;

			///@brief Clears the current render target to prepare for the next frame.
			virtual void clear(const Color3f& color, float depth = 1.0f, char stencil = 0) = 0;

			///@brief Presents the rendered backbuffer to the screen.
			virtual void present() = 0;

			///@return The driver capabilities.
			virtual const DriverCaps& getCaps() = 0;

			///@return The shader compiler.
			virtual ShaderCompiler* getShaderCompiler() = 0;
			///@brief Sets the vertex shader that will be used for drawing.
			virtual void setVertexShader(VertexShader* vs) = 0;
			///@brief Sets the pixel shader that will be used for drawing.
			virtual void setPixelShader(PixelShader* ps) = 0;

			///@brief Sets the input layout to use for rendering.
			virtual void setInputLayout(InputLayout* layout) = 0;

			///@brief Sets a vertex buffer for drawing.
			virtual void setVertexBuffer(VertexBuffer* vb, unsigned int slot) = 0;
			///@brief Unsets all vertex buffers.
			virtual void unsetVertexBuffers() = 0;

			///@brief Sets an index buffer for drawing.
			virtual void setIndexBuffer(IndexBuffer* buffer) = 0;

			///@brief Sets a 2D texture to be used for drawing.
			virtual void setTexture(Texture2D* tex, unsigned int slot) = 0;

			///@brief Draws the currently set vertex buffer(s).
			///@param count The number of vertices in the vertex buffer(s) to draw.
			///@param offset The offset to the first starting vertex.
			virtual void draw(unsigned int count, unsigned int offset=0) = 0;
			///@param Draws the currently set vertex buffer(s) using the currently set index buffer.
			///@param offset The offset to the first starting vertex.
			virtual void drawIndexed(unsigned int offset=0) = 0;

			///@brief Creates a 2D texture resource.
			///The texture must be initialized afterwards.
			virtual Texture2D* createTexture() = 0;
			///@brief Creates a vertex buffer.
			///The vertex buffer must be initialized afterwards.
			virtual VertexBuffer* createVertexBuffer() = 0;
			///@brief Creates an index buffer.
			///The index buffer must be initialized afterwards.
			virtual IndexBuffer* createIndexBuffer() = 0;
			///@brief Creates a vertex shader.
			///The vertex shader must be initialized afterwards.
			virtual VertexShader* createVertexShader() = 0;
			///@brief Creates a pixel shader.
			///The pixel shader must be initialized afterwards.
			virtual PixelShader* createPixelShader() = 0;

			virtual GRAPHICS_DRIVER_TYPE getDriverType() = 0;
		};
	}
}

#endif