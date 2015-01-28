#include "core/Debug.h"
#if defined(ICE_WIN32)
#include <Windows.h>
#elif defined(ICE_ANDROID)
#include <android/log.h>
#endif
#include <iostream>


using namespace ice;
using namespace core;

List<LogListener*> Debug::m_listeners = List<LogListener*>();

bool Debug::registerListener(LogListener* listener)
{
	m_listeners.push_back(listener);
	return true;
}

bool Debug::unregisterListener(LogListener* listener)
{
	List<LogListener*>::iterator i;
	for ( i=m_listeners.begin(); i!=m_listeners.end(); ++i )
	{
		if ( *i == listener )
		{
			m_listeners.erase(i);
			return true;
		}
	}

	return false;
}

void Debug::log(LOG_LEVEL logLevel, const String& message)
{
	List<LogListener*>::iterator i;
	for (i = m_listeners.begin(); i != m_listeners.end(); ++i)
	{
		(*i)->messageLogged(logLevel, message);
	}

	String logLevelString = "";
	if (logLevel == LL_WARNING)
	{
		logLevelString = "[Warning] ";
	}
	else if (logLevel == LL_ERROR)
	{
		logLevelString = "[Error] ";
	}

	std::cout << message << "\n";
}