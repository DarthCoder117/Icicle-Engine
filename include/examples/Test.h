#ifndef TEST_H
#define TEST_H
#include "core/Uncopyable.h"

namespace ice 
{
	namespace test
	{
		class Test : public core::Uncopyable 
		{
		public:
			Test();
			void start();
		};
	}
}

#endif //TEST_H