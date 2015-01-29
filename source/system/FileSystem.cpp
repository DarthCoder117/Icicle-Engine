#include "system/FileSystem.h"
#include "core/Engine.h"
#include <iostream>

using namespace ice;
using namespace core;
using namespace system;

using namespace std;

class PhysFSBuf : public std::streambuf
{
public:

	//explicit PhysFSBuf(PHYSFS_ *fptr, std::size_t buff_sz = 256, std::size_t put_back = 8);

private:
	// overrides base class underflow()
	//int_type underflow();

	// copy ctor and assignment not implemented;
	// copying not allowed
	//FILE_buffer(const FILE_buffer &);
	//FILE_buffer &operator= (const FILE_buffer &);

private:

	//FILE *fptr_;
	//const std::size_t put_back_;
	//std::vector<char> buffer_;
};


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