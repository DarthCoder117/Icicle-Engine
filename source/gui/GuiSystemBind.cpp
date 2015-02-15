#include "gui/GuiSystemBind.h"

#include <iostream>

using namespace ice;
using namespace gui;
using namespace Rocket;
using namespace Core;

//The GetElapsedTime() function should simply return the number of seconds that have elapsed since the start of the application. 
float GuiSystemBind::GetElapsedTime()
{
	return m_clock.restart().asSeconds();
}

/**
 *  The LogMessage() function is called whenever Rocket generates a message.
 *  type is one of the logging type, Rocket::Core::Log::ERROR for error messages, 
 *  Rocket::Core::Log::ASSERT for failed internal assertions (debug library only),
 *  Rocket::Core::Log::WARNING for non-fatal warnings, or Rocket::Core::Log::INFO for generic information messages.
 *  The message parameter is the actual message itself. 
 *  The function should return true if program execution should continue, or false to generate an interrupt to break execution. 
 *  This can be useful if you are running inside a debugger to see exactly what an application is doing to trigger a certain message. 
 */
bool GuiSystemBind::LogMessage(Log::Type type, const String& message)
{	
	switch (type) {
		case Log::Type::LT_ERROR:
			std::cout << "[Gui error] ";
		break;
		case Log::Type::LT_WARNING:
			std::cout << "[Gui warning] ";
		break;
		case Log::Type::LT_INFO:
			std::cout << "[Gui info] ";
		break;
		default:
			std::cout << "[Gui log] ";
		break;
	}
	
	std::cout << message.CString() << std::endl;
	return true;
}


/**
 *  TranslateString() is called whenever a text element is constructed from an RML stream. 
 *  This allows the application to send all text read from file through its string tables.
 *  i nput is the raw text read from the RML. translated should be set to the final text to be given to the text element to render.
 *  The total number of changes made to the raw text should be retu*rned; 
 *  If the number is greater than 0 libRocket will recursively call your translate function to process any new text that was added to the stream (watchout for infinite recursion). 
 *  If your translation function does all the recursion itself, you can safely return 0 on every call.
 *  Note that the translated text can include RML tags and they will be processed as if they were in the original stream; this can be used, 
 *  for example, to substitute images for certain tokens. 
 */
int GuiSystemBind::TranslateString(String& translated, const String& input)
{
	//TODO currently no translating just raw text output
	translated = input;
	return 0;
}

