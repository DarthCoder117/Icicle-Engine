#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		///@brief Flags for flexible vertex formats.
		enum VERTEX_ELEMENT
		{
			VE_POSITION = 0x01,///< Corresponds to the SV_POSITION semantic, float4 vertex position. All vertices must have a POSITION.

			VE_TEXCOORD0 = 0x02,///< Texture coordinates, float2...
			VE_TEXCOORD1 = 0x04,
			VE_TEXCOORD2 = 0x08,
			VE_TEXCOORD3 = 0x10,
			VE_TEXCOORD4 = 0x20,
			VE_TEXCOORD5 = 0x40,
			VE_TEXCOORD6 = 0x80,
			VE_TEXCOORD7 = 0x100,

			VE_NORMAL = 0x200,///< Surface normals. This is a float3 type element.

			VE_DIFFUSE_COLOR = 0x400,///< Vertex diffuse color for per-vertex diffuse color information. This is a float4 type element.
			VE_SPECULAR_COLOR = 0x800,///< Vertex diffuse color for per-vertex diffuse color information. This is a float4 type element.

			VE_WORLD_POSITION = 0x1000///< The world position of the vertex (used for lighting)
		};

		class InputLayout
		{
		public:

			InputLayout(GraphicsDriver* driver)
				:m_driver(driver)
			{}

			virtual ~InputLayout(){}

			virtual void init(unsigned int vertexFormat) = 0;

		protected:

			GraphicsDriver* m_driver;
		};
	}
}

#endif