#include "system/DirectoryFileLocation.h"
#include <core/FileStream.h>
#if defined(ICE_LINUX)
#include <unistd.h>
#elif defined(ICE_WINDOWS)
#include <Windows.h>
#endif

using namespace ice;
using namespace system;

DirectoryFileLocation::DirectoryFileLocation(const String& rootDir)
	:m_rootDir(rootDir)
{
	if (m_rootDir[m_rootDir.size() - 1] != '/')
	{
		m_rootDir.append("/");
	}
}

SharedPtr<core::DataStream> DirectoryFileLocation::openFile(const String& path, u8 streamMode)
{
	return makeShared<core::FileStream>(m_rootDir+path, streamMode);
}

bool DirectoryFileLocation::exists(const String& filename)
{
	#if defined(ICE_LINUX)
	return access((m_rootDir+filename).c_str(), F_OK ) != -1;
	#elif defined(ICE_WINDOWS)
	DWORD dwAttrib = GetFileAttributes((m_rootDir+filename).c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	#else
	core::FileStream stream = core::FileStream(m_rootDir+filename, core::SM_READ);
	bool doesExist = stream.isValid();
	stream.close();
	return doesExist;
	#endif
}

String DirectoryFileLocation::getRealPath(const String& filename)
{
	return m_rootDir + filename;
}