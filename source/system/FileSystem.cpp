#include "system/FileSystem.h"
#include "core/Engine.h"
#include <physfs.h>
#include <iostream>

using namespace ice;
using namespace core;
using namespace system;

using namespace std;

FileSystem::FileSystem(const core::LaunchParameters& params)
{
	const char* argv = NULL;
	if (params.m_argc > 0)
	{
		argv = params.m_argv[0];
	}

	PHYSFS_init(argv);
	
	//Mount Engine resource dir
	string basePath = PHYSFS_getBaseDir();
	basePath = basePath.substr(0, basePath.rfind(PHYSFS_getDirSeparator()));
	basePath = basePath.substr(0, basePath.rfind(PHYSFS_getDirSeparator()));
	basePath = basePath.substr(0, basePath.rfind(PHYSFS_getDirSeparator()));
	basePath += PHYSFS_getDirSeparator();
	basePath += "resources";
	
	cout << basePath << endl;
	
	setWriteDir(basePath);
}

FileSystem::~FileSystem()
{
	PHYSFS_deinit();
}

PHYSFS_File* FileSystem::readFile(const String& filename)
{
	
	return PHYSFS_openRead(filename.c_str());
}

void FileSystem::mount(const String& path, const String& mountPoint)
{
	PHYSFS_mount(path.c_str(), mountPoint.c_str(), 1);
}

void FileSystem::setWriteDir(const String& writeDir)
{
	PHYSFS_setWriteDir(writeDir.c_str());
}

bool FileSystem::exists(const String& file)
{
	return PHYSFS_exists(file.c_str()) != 0;
}

bool FileSystem::isDirectory(const String& path)
{
	return PHYSFS_isDirectory(path.c_str()) != 0;
}