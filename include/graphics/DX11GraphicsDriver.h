#ifndef DX11_GRAPHICS_DRIVER_H
#define DX11_GRAPHICS_DRIVER_H
#include "graphics/GraphicsDriver.h"
#ifdef ICE_WINDOWS
#include <system/Window.h>
#include <Windows.h>
#include <d3d11.h>
#include "graphics/DX11ShaderCompiler.h"

namespace ice
{
	namespace graphics
	{
		class DX11GraphicsDriver : public GraphicsDriver
		{
		public:

			DX11GraphicsDriver(system::Window* window, u32 flags = 0);

			~DX11GraphicsDriver();

			void reset(const glm::uvec2& resolution);

			void setViewport(const glm::vec2& vp);

			void clear(const glm::vec3& color, float depth = 1.0f, char stencil = 0);

			void present();

			const DriverCaps& getCaps();

			ShaderCompiler* getShaderCompiler();
			void setVertexShader(VertexShader* vs);
			void setPixelShader(PixelShader* ps);

			void setInputLayout(InputLayout* layout);

			void setVertexBuffer(VertexBuffer* vb, unsigned int idx);
			void unsetVertexBuffers();

			void setIndexBuffer(IndexBuffer* buffer);

			void setTexture(Texture2D* tex, unsigned int slot);

			void draw(unsigned int count, unsigned int offset);
			void drawIndexed(unsigned int offset);

			Texture2D* createTexture();
			InputLayout* createInputLayout();
			VertexBuffer* createVertexBuffer();
			IndexBuffer* createIndexBuffer();
			VertexShader* createVertexShader();
			PixelShader* createPixelShader();

			GRAPHICS_DRIVER_TYPE getDriverType();

			ID3D11Device* getD3DDevice(){ return m_device; }

		private:

			system::Window* m_window;

			u32 m_displayFlags;

			DriverCaps m_caps;

			ID3D11Device* m_device;
			ID3D11DeviceContext* m_deviceContext;
			IDXGISwapChain* m_swapChain;
			ID3D11RenderTargetView* m_backBuffer;

			IndexBuffer* m_currentIndexBuffer;

			UniquePtr<DX11ShaderCompiler> m_shaderCompiler;
		};
	}
}

#endif

#endif