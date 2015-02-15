#ifndef GUI_H
#define GUI_H

#include <IcicleCommon.h>

#include "core/Uncopyable.h"
#include "core/EngineSystem.h"
#include "system/InputSystem.h"
#include "system/Window.h"

#include "SFML/System.hpp"

namespace ice
{
	namespace gui
	{
		class Gui : public core::IEngineSystem, public system::KeyEventListener, public system::MouseEventListener, public system::TextEventListener, public system::WindowEventListener
		{
		public:
			Gui();
			
			void start();
			
			void update();
			
			void shutdown();
			
		private:
			virtual void onKeyEvent(system::KeyEvent event);
			virtual void onMouseEvent(system::MouseEvent event);
			virtual void onTextEvent(system::TextEvent event);
			virtual void onWindowEvent(system::WindowEvent event);
		private:
			Vec2 m_lastMousePos;
			sf::Clock m_clock;
			
		private:
		};
	}
}

#endif