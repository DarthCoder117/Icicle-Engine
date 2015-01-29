#ifndef DEBUG_H
#define DEBUG_H

#include <IcicleCommon.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace ice
{
	namespace core
	{
		enum LOG_LEVEL
		{
			LL_INFO,
			LL_WARNING,
			LL_ERROR
		};

		///@brief The Debug class contains functions for logging and manipulating debug information.
		///@todo Add code coverage markers.
		class Debug
		{
		public:
			template <typename... Args>
			static void info(Args... args) { log(LL_INFO, args...); }
			static void warn(const String& message) { log(LL_WARNING, message); }
			static void error(const String& message) { log(LL_ERROR, message); }

			
			template<typename Arg>
			static void log(LOG_LEVEL logLevel, const Arg& arg) {
				#ifdef ICE_DEBUG
				if (logLevel == LL_WARNING)
				{
					std::cout << "[Warning] ";
				}
				else if (logLevel == LL_ERROR)
				{
					std::cout << "[Error] ";
				}
				std::cout << arg << std::endl;
				#endif
			}
			
			///@brief Print a debug message to the console and all listeners
			template<typename Arg, typename... Args>
			static void log(LOG_LEVEL logLevel, const Arg& arg, const Args&... args)
			{
				#ifdef ICE_DEBUG
				std::cout << arg;
				log(logLevel, args...);
				#endif
			}

		private:
		};
	}
}

#endif