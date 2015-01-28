#ifndef LAUNCH_PARAMETERS_H
#define LAUNCH_PARAMETERS_H

#include <IcicleCommon.h>
#include <glm/vec2.hpp>


namespace ice
{
	namespace core
	{
		
		
		struct LaunchParameters
		{
			LaunchParameters()
				:m_windowName("Icicle Engine Window"),
				m_windowSize(800, 600),
				m_argc(0),
				m_argv(NULL)
			{}

			String m_windowName;///< The name in the title bar of the window on paltforms where this is applicable.
			Vec2u m_windowSize;///< The size of the render window in pixels.

			int m_argc;///< argc from main() on platforms where this is applicable.
			char** m_argv;///< argv from main() on platforms where this is applicable.
		};
	}
}

#endif