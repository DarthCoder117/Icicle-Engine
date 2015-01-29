#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "core/EngineSystem.h"
#include <string>
#include "physfs.h"

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
			
			void mount(std::string path, std::string mountPoint = "");
			
			PHYSFS_File* readFile(std::string filename);
			PHYSFS_File* writeToFile(std::string filename);

			void setWriteDir(std::string writeDir);

			bool exists(std::string filename);

			bool isDirectory(std::string path);
		};
	}
}

#endif