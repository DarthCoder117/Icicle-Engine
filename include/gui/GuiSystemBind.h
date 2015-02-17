#ifndef GUISYSTEMBIND_H
#define GUISYSTEMBIND_H

#include <Rocket/Core/SystemInterface.h>
#include <SFML/System/Clock.hpp>

namespace ice
{
	namespace gui
	{
		class GuiSystemBind : public Rocket::Core::SystemInterface
		{
		public:
			// Get the number of seconds elapsed since the start of the application.
			virtual float GetElapsedTime();
			
			// Translate the input string into the translated string.
			virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input);
			
			// Log the specified message.
			virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
		private:
			sf::Clock m_clock;
		};
	}
}

#endif // GUISYSTEMBIND_H
