#include "graphics/RenderSystem2D.h"
#include "graphics/ShaderCompiler.h"
#include "graphics/VertexShader.h"
#include "graphics/PixelShader.h"
#include "graphics/GraphicsDriver.h"
#include <core/Position.h>

using namespace ice;
using namespace graphics;

struct ShapeVertex
{
	ShapeVertex(const glm::vec2& pos)
		:m_pos(pos)
	{}

	glm::vec2 m_pos;
};

struct PositionBuffer
{
	glm::vec2 m_pos;
	glm::vec2 m_dimensions;
};

struct ColorBuffer
{
	glm::vec4 m_color;
};

void RenderSystem2D::init(GraphicsDriver* driver, core::World* world)
{
	m_driver = driver;
	m_world = world;

	//Compile shape vertex shader
	String shapeVsSrc =
		"cbuffer ShapePositions : register(b0)\n"
		"{\n"
		"	float2 ShapePos;\n"
		"	float2 ShapeDimensions;\n"
		"}\n"
		"\n"
		"float4 VS( float2 Pos : POSITION ) : SV_POSITION\n"
		"{\n"
		"	Pos *= ShapeDimensions;\n"
		"	Pos += ShapePos;\n"
		"	return float4(Pos, 0.0f, 1.0f);\n"
		"}\n";

	SharedPtr<ShaderBlob> compiledShapeVs = m_driver->getShaderCompiler()->compileShader(shapeVsSrc, ST_VERTEX);

	m_shapeVS = m_driver->createVertexShader();
	m_shapeVS->init(compiledShapeVs->getByteCode(), compiledShapeVs->getByteCodeSize());

	//Compile shape pixel shader
	String shapePsSrc = 
		"cbuffer ShapeColors : register(b0)\n"
		"{\n"
		"	float4 ShapeColor;\n"
		"}\n"
		"\n"
		"float4 PS( float4 Pos : SV_POSITION ) : SV_Target\n"
		"{\n"
		"	return ShapeColor;\n"
		"}\n";

	SharedPtr<ShaderBlob> compiledShapePs = m_driver->getShaderCompiler()->compileShader(shapePsSrc, ST_PIXEL);

	m_shapePS = m_driver->createPixelShader();
	m_shapePS->init(compiledShapePs->getByteCode(), compiledShapePs->getByteCodeSize());

	//Define shape input layout
	m_shapeLayout = m_driver->createInputLayout();

	InputElementDesc layout[] =
	{
		InputElementDesc("POSITION", 0, IEF_FLOAT2, 0)
	};

	m_shapeLayout->init(layout, 1);

	//Create vertex buffer
	ShapeVertex vertices[]
	{
		ShapeVertex(glm::vec2(-0.5f, 0.5f)),
		ShapeVertex(glm::vec2(0.5f, 0.5f)),
		ShapeVertex(glm::vec2(-0.5f, -0.5f)),
		ShapeVertex(glm::vec2(0.5f, -0.5f))
	};

	m_squareBuffer = m_driver->createVertexBuffer();
	m_squareBuffer->init(vertices, 4, sizeof(ShapeVertex));

	//Create constant buffers
	m_positionBuffer = m_driver->createConstantBuffer(NULL, sizeof(PositionBuffer));
	m_colorBuffer = m_driver->createConstantBuffer(NULL, sizeof(ColorBuffer));
}

void RenderSystem2D::render(RENDERING_STAGE stage)
{
	m_driver->setInputLayout(m_shapeLayout);
	m_driver->setVertexBuffer(m_squareBuffer, 0);

	m_driver->setVertexShader(m_shapeVS);
	m_driver->setPixelShader(m_shapePS);

	const List<core::IComponent*>& squareComponents = m_world->components<SquareRenderer>();
	for (auto iter : squareComponents)
	{
		SquareRenderer* square = (SquareRenderer*)iter;

		PositionBuffer buff;
		buff.m_pos = iter->owner()->get<core::Position>()->Pos;
		buff.m_dimensions = square->Dimensions;

		ColorBuffer colBuff;
		colBuff.m_color = square->Color;

		m_positionBuffer->updateBuffer(&buff);
		m_colorBuffer->updateBuffer(&colBuff);
		m_driver->setConstantBufferVS(m_positionBuffer, 0);
		m_driver->setConstantBufferPS(m_colorBuffer, 0);

		m_driver->draw(4);
	}
}