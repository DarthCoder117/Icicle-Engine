#ifndef DATA_STREAM_H
#define DATA_STREAM_H
#include <IcicleCommon.h>
#include "core/Error.h"

namespace ice
{
	namespace core
	{
		enum STREAM_MODE
		{
			SM_READ = 0x01,
			SM_WRITE = 0x02,
			SM_APPEND = 0x04,
			SM_BOTH = SM_READ | SM_WRITE
		};

		enum SEEK_ORIGIN
		{
			SO_BEGIN,
			SO_CURRENT,
			SO_END
		};

		///@brief DataStream 
		class DataStream
		{
		public:

			virtual ~DataStream(){}

			///@brief Close the stream.
			virtual void close() = 0;

			///@return Should return true if the stream was properly created and is usable for reading/writing.
			virtual bool isValid() = 0;

			///@return The supported STREAM_MODE flags
			virtual u8 getModeFlags() = 0;

			///@return True if the stream can be read from, false if not.
			bool canRead(){ return getModeFlags() & SM_READ; }
			///@return True if the stream can be written or appended to, false if not.
			bool canWrite(){ return (getModeFlags() & SM_WRITE) || (getModeFlags() & SM_APPEND); }

			///@brief Writes data to the stream.
			///@param data Pointer to the data to write to the stream.
			///@param dataSz The size (in bytes) of the data to write to the stream.
			///@return The number of bytes actually written.
			virtual size_t write(void* data, size_t dataSz) = 0;

			///@brief Attempts to read data from the stream.
			///@param data Pointer to where the data read from the stream will be stored.
			///@param dataSz How many bytes to try and read from the stream.
			///@return The number of bytes actually read.
			virtual size_t read(void* data, size_t dataSz) = 0;

			///@brief Changes the stream pointer's position.
			virtual void seek(long int offset, SEEK_ORIGIN origin = SO_BEGIN) = 0;

			///@return The stream pointer's current position.
			virtual size_t tell() = 0;

			///@return Whether or not the end of the stream was reached.
			virtual bool eof() = 0;

			///@return The stream's size in bytes.
			size_t getSize()
			{
				size_t lastPos = tell();
				seek(0, SO_END);
				size_t sz = tell();
				seek(lastPos);
				return sz;
			}

			template <typename T>
			void write(const T& data)
			{
				write(&data, sizeof(T));
			}

			template <typename T>
			T read()
			{
				T ret;
				read((void*)&ret, sizeof(T));
				return ret;
			}

			operator bool()
			{
				return isValid();
			}
		};
	}
}

#endif