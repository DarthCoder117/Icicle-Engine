#include "system/FileSystem.h"
#include <../3rd-party/physfs/physfs.h>

using namespace ice;
using namespace core;
using namespace system;

FileSystem::FileSystem(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
}

void FileSystem::init()
{
	
}

void FileSystem::update()
{

}

void FileSystem::shutdown()
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