#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H
#include <IcicleCommon.h>

namespace ice
{
	namespace graphics
	{
		class GraphicsDriver;

		enum INPUT_ELEMENT_FORMAT
		{
			IEF_FLOAT,
			IEF_FLOAT2,
			IEF_FLOAT3,
			IEF_FLOAT4
		};

		struct InputElementDesc
		{
			InputElementDesc(const String& semanticName, unsigned int semanticIdx, INPUT_ELEMENT_FORMAT format, unsigned int inputSlot)
				:m_semanticName(semanticName),
				m_semanticIdx(semanticIdx),
				m_format(format),
				m_inputSlot(inputSlot)
			{}

			String m_semanticName;
			unsigned int m_semanticIdx;

			INPUT_ELEMENT_FORMAT m_format;

			unsigned int m_inputSlot;
		};

		class InputLayout
		{
		public:

			InputLayout(GraphicsDriver* driver)
				:m_driver(driver)
			{}

			virtual ~InputLayout(){}

			virtual void init(InputElementDesc elements[], unsigned int numElements) = 0;

		protected:

			GraphicsDriver* m_driver;
		};
	}
}

#endif