#ifndef DIRECTORY_FILE_LOCATION_H
#define DIRECTORY_FILE_LOCATION_H
#include "system/IFileLocation.h"

namespace ice
{
	namespace system
	{
		class DirectoryFileLocation : public IFileLocation
		{
		public:

			DirectoryFileLocation(const String& rootDir);

			SharedPtr<core::DataStream> openFile(const String& path, u8 streamMode);

			bool exists(const String& filename);

			String getRealPath(const String& filename);

		private:

			String m_rootDir;
		};
	}
}

#endif