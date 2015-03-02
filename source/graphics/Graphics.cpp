#include "graphics/Graphics.h"
#include <IcicleConfig.h>
#include <core/ResourceManager.h>
#include "graphics/Texture2D.h"

#ifdef ICE_WINDOWS
#include <Windows.h>
#include "graphics/DX11GraphicsDriver.h"
#else
#include <GLFW/glfw3.h>
#endif

#include "core/Debug.h"

using namespace ice;
using namespace graphics;

Graphics::Graphics(system::Window* window, GRAPHICS_DRIVER_TYPE driverType)
	:m_window(window)
{
	m_windowSize = m_window->getWindowSize();
	m_window->registerWindowEventListener(this);
}

class GraphicsResourceFactory : public core::IResourceFactory
{
public:

	GraphicsResourceFactory(Graphics* graphics)
		:m_graphics(graphics)
	{}

	core::IResource* create(ResourceType type)
	{
		if (type == Texture2D::getClassType())
		{
			return m_graphics->getDriver()->createTexture();
		}

		return NULL;
	}

private:

	Graphics* m_graphics;
};

struct SimpleVertex
{
	SimpleVertex(const glm::vec3& pos)
		:m_pos(pos.x, pos.y, pos.z),
		m_norm(1.0f)
	{}

	glm::vec3 m_pos;
	glm::vec3 m_norm;
};

void Graphics::start()
{
	core::ResourceManager::instance()->registerFactory(new GraphicsResourceFactory(this));

	#if defined(ICE_WINDOWS)
	m_driver.reset(new DX11GraphicsDriver(m_window));
	#elif defined(ICE_LINUX)

	#endif

	//TEMPORARY TEST

	//Compile vertex shader
	String vsSrc = "float4 VS( float3 Pos : POSITION ) : SV_POSITION\n"
	"{\n"
	"	return float4(Pos, 1.0f);\n"
	"}";

	SharedPtr<ShaderBlob> compiledVs = m_driver->getShaderCompiler()->compileShader(vsSrc, ST_VERTEX);

	m_vs = m_driver->createVertexShader();
	m_vs->init(compiledVs->getByteCode(), compiledVs->getByteCodeSize());

	//Compile pixel shader
	String psSrc = "float4 PS( float4 Pos : SV_POSITION ) : SV_Target\n"
	"{\n"
	"	return float4( 1.0f, 1.0f, 0.0f, 1.0f );\n"
	"}";

	SharedPtr<ShaderBlob> compiledPs = m_driver->getShaderCompiler()->compileShader(psSrc, ST_PIXEL);

	m_ps = m_driver->createPixelShader();
	m_ps->init(compiledPs->getByteCode(), compiledPs->getByteCodeSize());

	//Create input layout
	m_vertLayout = m_driver->createInputLayout();

	InputElementDesc layout[] =
	{
		InputElementDesc("POSITION", 0, IEF_FLOAT3, 0)
	};

	m_vertLayout->init(layout, 1);

	m_driver->setInputLayout(m_vertLayout);

	//Create vertex buffer
	SimpleVertex vertices[]
	{
		SimpleVertex(glm::vec3(0.0f, 0.5f, 0.5f)),
		SimpleVertex(glm::vec3(0.5f, -0.5f, 0.5f)),
		SimpleVertex(glm::vec3(-0.5f, -0.5f, 0.5f))
	};

	m_vertBuffer = m_driver->createVertexBuffer();
	m_vertBuffer->init(vertices, 3, sizeof(SimpleVertex));

	//Setup render states
	m_driver->setVertexBuffer(m_vertBuffer, 0);
}

void Graphics::shutdown()
{
	
}

void Graphics::render() 
{
	glm::vec3 clearColor(0.6f, 0.6f, 0.6f);
	m_driver->clear(clearColor);

	//Draw stuff...

	//TEST
	m_driver->setPixelShader(m_ps);
	m_driver->setVertexShader(m_vs);
	m_driver->draw(3);

	//END OF TEST

	m_driver->present();
}

void Graphics::onWindowEvent(const system::WindowEvent& evt)
{
	if (evt.type == system::WindowEvent::RESIZED) 
	{
		m_windowSize = evt.size;

		if (m_driver)
		{
			m_driver->reset(m_windowSize);
			m_driver->setViewport(m_windowSize);
		}
	}
}