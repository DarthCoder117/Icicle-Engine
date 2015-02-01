#ifndef I_FILE_LOCATION_H
#define I_FILE_LOCATION_H
#include <IcicleCommon.h>
#include <core/Uncopyable.h>
#include <core/DataStream.h>

namespace ice
{
	namespace system
	{
		class IFileLocation : public core::Uncopyable
		{
		public:

			///@brief Open a file from this location.
			virtual SharedPtr<core::DataStream> openFile(const String& path, u8 streamMode) = 0;

			///@return True if the file exists within this FileLocation, or false if it does not.
			virtual bool exists(const String& filename) = 0;

			///@return The full OS path or URL to the file (if applicable) 
			virtual String getRealPath(const String& filename) = 0;
		};
	}
}

#endif