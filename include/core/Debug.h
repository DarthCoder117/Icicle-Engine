#ifndef DEBUG_H
#define DEBUG_H
#include <IcicleCommon.h>
#include <string>
#include <vector>
#include <sstream>

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

		///@brief Interface for receiving log callbacks
		class LogListener
		{
		public:

			///@brief Called whenever debug text is logged.
			///@param message The logged message.
			virtual void messageLogged(LOG_LEVEL logLevel, const String& message) = 0;
		};

		///@brief The Debug class contains functions for logging and manipulating debug information.
		///@todo Add code coverage markers.
		class Debug
		{
		public:

			///@brief Registers a listener to receive error messages.
			///@return True on success. False if the listener has already been registered.
			static bool registerListener(LogListener* listener);
			///@brief Removes a listener from the list to receive error messages.
			///@return True on success. False if the listener can't be found.
			static bool unregisterListener(LogListener* listener);

			///@brief Print a debug message to the console and all listeners
			static void log(LOG_LEVEL logLevel, const String& message);

		private:

			static List<LogListener*> m_listeners;
		};
	}
}

#endif