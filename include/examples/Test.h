#ifndef TEST_H
#define TEST_H
#include <core/Uncopyable.h>

namespace ice 
{
	namespace test
	{
		class Test : public core::Uncopyable
		{
		public:

			int start(int argc, char* argv[]);
		};
	}
}

#endif //TEST_H