#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "core/SubSystem.h"

namespace ice
{
	namespace system
	{
		///@brief The FileSystem sub-system manages a virtual filesystem based on PhysicsFS.
		class FileSystem : public core::SubSystem<FileSystem>
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