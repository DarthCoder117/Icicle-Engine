#include "system/FileSystem.h"
#include "system/DirectoryFileLocation.h"
#include <core/Engine.h>
#include <core/Uncopyable.h>

using namespace ice;
using namespace core;
using namespace system;

FileSystem* FileSystem::m_inst = NULL;

FileSystem::FileSystem()
{
	m_inst = this;
}

FileSystem::~FileSystem()
{
	for (auto iter : m_fileLocations)
	{
		delete iter;
	}
}

SharedPtr<core::DataStream> FileSystem::openFile(const String& path, u8 streamMode)
{
	for (auto iter : m_fileLocations)
	{
		SharedPtr<core::DataStream> stream = iter->openFile(path, streamMode);
		if (stream->isValid())
		{
			return stream;
		}
	}

	return SharedPtr<core::DataStream>(NULL);
}

void FileSystem::mount(const String& path)
{
	mount<DirectoryFileLocation>(path);
}

bool FileSystem::exists(const String& file)
{
	for (auto iter : m_fileLocations)
	{
		if (iter->exists(file))
		{
			return true;
		}
	}

	return false;
}
