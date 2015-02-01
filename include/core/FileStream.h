#ifndef FILE_STREAM_H
#define FILE_STREAM_H
#include "core/DataStream.h"
#include "core/Uncopyable.h"
#include <cstdio>

namespace ice
{
	namespace core
	{
		class FileStream : public DataStream, public Uncopyable
		{
		public:

			FileStream();
			FileStream(const String& path, u8 streamMode = SM_READ);

			~FileStream();

			void open(const String& path, u8 streamMode = SM_READ);

			void close();

			bool isValid();

			u8 getModeFlags(){ return m_streamMode; }

			size_t write(void* data, size_t dataSz);

			size_t read(void* data, size_t dataSz);

			void seek(long int offset, SEEK_ORIGIN origin = SO_BEGIN);

			size_t tell();

			bool eof();

		protected:

			FILE* m_file;

			u8 m_streamMode;
		};
	}
}

#endif