#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

namespace ice
{
	namespace core
	{
		class Uncopyable
		{
		public:

			Uncopyable(){}
			virtual ~Uncopyable(){}
			
		private:

			Uncopyable(const Uncopyable& oth);
			Uncopyable& operator=(const Uncopyable& rhs);
		};
	}
}

#endif