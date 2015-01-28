#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "core/EngineSystem.h"

namespace ice
{
	namespace system
	{
		///@brief The FileSystem sub-system manages a virtual filesystem based on PhysicsFS.
		class FileSystem : public core::EngineSystem<FileSystem>
		{
		public:

			FileSystem(const core::LaunchParameters& params);

			~FileSystem();
			
			void mount(const char* path, const char* mountPoint = "");

			void setWriteDir(const char* writeDir);

			bool exists(const char* file);

			bool isDirectory(const char* path);
		};
	}
}

#endif