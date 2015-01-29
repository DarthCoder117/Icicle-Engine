#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"

namespace ice
{
	namespace system
	{
		///@brief The FileSystem sub-system manages a virtual filesystem based on PhysicsFS.
		class FileSystem : public core::IEngineSystem
		{
		public:

			FileSystem(const core::LaunchParameters& params);

			~FileSystem();
			
			void mount(const String& path, const String& mountPoint = "");
			
			PHYSFS_File* readFile(const String& filename);
			PHYSFS_File* writeToFile(const String& filename);

			void setWriteDir(const String& writeDir);

			bool exists(const String& filename);

			bool isDirectory(const String& path);
		};
	}
}

#endif