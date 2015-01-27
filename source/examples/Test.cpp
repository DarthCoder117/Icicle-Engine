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

int Test::start(int argc, char* argv[])
{
	cout << "Hello World!\n";

	core::LaunchParameters params;
	params.m_argc = argc;
	params.m_argv = argv;

	Engine engine(params);

	//This is where custom sub-systems would be created and registered...

	engine.startGame();

	return 0;
}
/*
int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}*/
//

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <bgfx.h>
#include <bgfxplatform.h>
int main(int argc,char* argv[])
{
	sf::VideoMode mode(800,480,32);
	sf::Window window(mode,"BGFX",sf::Style::Close);
	sf::Event event;
	bool running = true;
	
	bgfx::x11SetDisplayWindow(XOpenDisplay(0), window.getSystemHandle());
	bgfx::init();
	bgfx::reset(800,480,BGFX_RESET_VSYNC);
	
	bgfx::setDebug(BGFX_DEBUG_TEXT);
	
	bgfx::setViewClear(0,BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,0x303030FF,1.0f,0);
	
	while(running)
	{
		while(window.pollEvent(event)) if(event.type==sf::Event::Closed) running = false;
		
		bgfx::setViewRect(0,0,0,800,480);
		bgfx::submit(0);
		
		bgfx::dbgTextClear();
		//bgfx::dbgTextPrintf(0,1,0x4F,"No crash!");
		
		bgfx::frame();
	}
	
	bgfx::shutdown();
	
	window.close();
	
	return 0;
}
//START_ENGINE(Test)
