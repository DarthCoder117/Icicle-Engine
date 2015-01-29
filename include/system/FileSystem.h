#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include <iostream>
#include <physfs.h>

namespace ice
{
	namespace system
	{
		enum OPEN_MODE
		{
			OM_READ = 0x01,
			OM_WRITE = 0x02,
			OM_BOTH = OM_READ | OM_WRITE
		};

		///@brief The FileSystem sub-system manages a virtual filesystem based on PhysicsFS.
		class FileSystem : public core::IEngineSystem
		{
		public:

			FileSystem(const core::LaunchParameters& params);

			~FileSystem();
			
			void mount(const String& path, const String& mountPoint = "");
			
			std::iostream openFile(const String& filename, u8 openMode=OM_READ);

			void setWriteDir(const String& writeDir);

			bool exists(const String& filename);

			bool isDirectory(const String& path);
		};
	}
}

#endif