#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <IcicleCommon.h>
#include <iostream>
#include <sstream>

namespace ice
{
	namespace core
	{
		///@brief Contains utility functions for operating on strings
		class StringUtils
		{
		public:

			///@brief Generates an integer hash from a string (based on djb2 algorithm)
			static inline const u64 stringHash(const char* str)
			{
				u64 hash = 5381;
				int c;

				while ((c = *str++))
				{
					hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
				}

				return hash;
			}
		};
	}
}

#endif