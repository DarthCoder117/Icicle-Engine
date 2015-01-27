#include "system/FileSystem.h"
#include "core/Engine.h"
#include <../3rd-party/physfs/physfs.h>

using namespace ice;
using namespace core;
using namespace system;

FileSystem::FileSystem(const core::LaunchParameters& params)
{
	const char* argv = NULL;
	if (params.m_argc > 0)
	{
		argv = params.m_argv[0];
	}

	PHYSFS_init(argv);
}

FileSystem::~FileSystem()
{
	PHYSFS_deinit();
}

void FileSystem::mount(const char* path, const char* mountPoint)
{
	PHYSFS_mount(path, mountPoint, 1);
}

void FileSystem::setWriteDir(const char* writeDir)
{
	PHYSFS_setWriteDir(writeDir);
}

bool FileSystem::exists(const char* file)
{
	return PHYSFS_exists(file) != 0;
}

bool FileSystem::isDirectory(const char* path)
{
	return PHYSFS_isDirectory(path) != 0;
}