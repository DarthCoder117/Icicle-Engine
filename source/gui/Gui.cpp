#include "gui/Gui.h"

#include "core/Debug.h"

#include "GLFW/glfw3.h"

using namespace ice;
using namespace core;
using namespace gui;

Gui::Gui() : m_lastMousePos(glm::vec2(0.0f, 0.0f))
{
	m_clock.restart();
}

void Gui::start()
{
	Debug::info("Initilalising the Gui renderer");
	
	
}

void Gui::update()
{

}


void Gui::onKeyEvent(system::KeyEvent event)
{

	
}

void Gui::onMouseEvent(system::MouseEvent event)
{

}

void Gui::onTextEvent(system::TextEvent event)
{
	
}
/*
void Gui::onWindowEvent(system::WindowEvent event)
{

}*/

void Gui::onWindowEvent(system::WindowEvent event)
{

}

void Gui::shutdown()
{
	
}
