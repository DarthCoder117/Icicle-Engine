#include "system/FileSystem.h"
#include "core/Engine.h"
#include "core/Uncopyable.h"
#include <iostream>
#include <cmath>

using namespace ice;
using namespace core;
using namespace system;

using namespace std;

class PhysFSBuf : public std::streambuf, public core::Uncopyable
{
public:

	explicit PhysFSBuf(PHYSFS_file* file, size_t buffSz = 256, size_t putBack = 8)
		:m_file(file),
		m_putBack(std::max(putBack, size_t(1))),
		m_buffer(std::max(buffSz, putBack) + putBack)
	{
		char* end = &m_buffer.front() + m_buffer.size();
		setg(end, end, end);
	}

private:

	int_type underflow()
	{
		if (gptr() < egptr())
			return traits_type::to_int_type(*gptr());

		char* base = &m_buffer.front();
		char* start = base;

		if (eback() == base)
		{
			std::memmove(base, egptr() - m_putBack, m_putBack);
			start += m_putBack;
		}

		PHYSFS_sint64 n = PHYSFS_read(m_file, start, 1, m_buffer.size() - (start - base));
		if (n == 0)
		{
			return traits_type::eof();
		}

		setg(base, start, start + n);

		return traits_type::to_int_type(*gptr());
	}

private:

	PHYSFS_file* m_file;
	const size_t m_putBack;
	Vector<char> m_buffer;
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