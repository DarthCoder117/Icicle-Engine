#include "examples/Test.h"

#include <iostream>

#include <SFML/Window.hpp>

#include "core/Engine.h"
#include <SFML/Window.hpp>


using namespace ice;
using namespace core;
using namespace graphics;
using namespace test;

using namespace std;

Test::Test() {
	
}

void Test::start() {	
	Engine engine;
	
	engine.startGame();
	
	cout << "Hello World!\n";
}

// #include <iostream>
// 
// #include <SFML/System.hpp>
// #include <SFML/Window.hpp>
// 
// #include <bgfx.h>
// #include <bgfxplatform.h>

int main() {
	Test t;
	t.start();
// 		sf::VideoMode mode(800,480,32);
// 		sf::Window* window = new sf::Window(mode,"BGFX",sf::Style::Close);
// 		sf::Event event;
// 		bool running = true;
// 		
// 		bgfx::x11SetDisplayWindow(XOpenDisplay(0), window->getSystemHandle());
// 		bgfx::init(bgfx::RendererType::OpenGL);
// 		bgfx::reset(800,480,BGFX_RESET_VSYNC);
// 		
// 		bgfx::setDebug(BGFX_DEBUG_TEXT);
// 		
// 		bgfx::setViewClear(0,BGFX_CLEAR_COLOR_BIT | BGFX_CLEAR_DEPTH_BIT,0x303030FF,1.0f,0);
// 		
// 		while(running)
// 		{
// 			while(window->pollEvent(event)) if(event.type==sf::Event::Closed) running = false;
// 			
// 			bgfx::setViewRect(0,0,0,800,480);
// 			bgfx::submit(0);
// 			
// 			bgfx::dbgTextClear();
// 			//bgfx::dbgTextPrintf(0,1,0x4F,"No crash!");
// 			
// 			bgfx::frame();
// 		}
// 		
// 		bgfx::shutdown();
// 		
// 		window->close();
// 		
// 		return 0;
	
}