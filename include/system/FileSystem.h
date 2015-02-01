#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <IcicleCommon.h>
#include "core/EngineSystem.h"
#include "core/DataStream.h"
#include "system/IFileLocation.h"
#include <iostream>

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
			
			static FileSystem* instance()
			{
				return m_inst;
			}

			SharedPtr<core::DataStream> openFile(const String& path, u8 streamMode = core::SM_READ);

			///@brief Adds a new file location based on the path.
			void mount(const String& path);
			///@brief Adds a new file location manually based on the type and the parameters passed.
			template <typename T, typename... P>
			void mount(P... p)
			{
				m_fileLocations.push_back(new T(p...));
			}
			
			bool exists(const String& filename);

		private:

			static FileSystem* m_inst;

			List<IFileLocation*> m_fileLocations;
		};
	}
}

#endif