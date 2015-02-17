#ifndef DX11_INPUT_LAYOUT_H
#define DX11_INPUY_LAYOUT_H
#include "graphics/InputLayout.h"
#ifdef ICE_WINDOWS
#include <d3d11.h>
#include "graphics/DX11GraphicsDriver.h"

namespace ice
{
	namespace graphics
	{
		class DX11InputLayout : public InputLayout
		{
		public:

			DX11InputLayout(GraphicsDriver* driver)
				:InputLayout(driver),
				m_device(((DX11GraphicsDriver*)driver)->getD3DDevice())
			{}

			~DX11InputLayout();

			void init(InputElementDesc elements[], unsigned int numElements);

			ID3D11InputLayout* getD3DLayout(){ return m_layout; }

		protected:

			void generateShaderSignature();

			GraphicsDriver* m_driver;

			ID3D11Device* m_device;

			ID3D11InputLayout* m_layout;
		};
	}
}

#endif

#endif