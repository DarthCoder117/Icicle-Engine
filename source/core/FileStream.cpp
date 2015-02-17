#include "core/FileStream.h"
#include <cassert>

using namespace ice;
using namespace core;

FileStream::FileStream()
	:m_file(NULL),
	m_streamMode(0)
{

}

FileStream::FileStream(const String& path, u8 streamMode) : FileStream()
{
	open(path, streamMode);
}

FileStream::~FileStream()
{
	
}

void FileStream::open(const String& path, u8 streamMode)
{
	if (m_file)
	{
		//Already opened
		return;
	}

	const char* mode = "rb";
	if (streamMode == SM_WRITE)
	{
		mode = "wb";
	}
	else if (streamMode == SM_APPEND)
	{
		mode = "ab";
	}
	else if (streamMode == SM_BOTH)
	{
		mode = "r+b";
	}

	m_file = fopen(path.c_str(), mode);
}

void FileStream::close()
{
	if (m_file)
	{
		fclose(m_file);
	}
}

bool FileStream::isValid()
{
	return m_file != NULL;
}

size_t FileStream::write(void* data, size_t dataSz)
{
	assert(m_file != NULL);
	return fwrite(data, 1, dataSz, m_file);
}

size_t FileStream::read(void* data, size_t dataSz)
{
	assert(m_file != NULL);
	return fread(data, 1, dataSz, m_file);
}

void FileStream::seek(long int offset, SEEK_ORIGIN origin)
{
	assert(m_file != NULL);
	fseek(m_file, offset, origin);
}

size_t FileStream::tell()
{
	assert(m_file != NULL);
	return ftell(m_file);
}

bool FileStream::eof()
{
	assert(m_file != NULL);
	return feof(m_file) == 0;
}