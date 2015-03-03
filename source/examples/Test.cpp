#include "examples/Test.h"

#include <iostream>

#include <core/Engine.h>
#include <core/Debug.h>
#include <core/FileStream.h>

#include <core/Reflection.h>

#include <system/LinuxWindow.h>
#include <system/Win32Window.h>

#include <core/ResourceManager.h>

#include <core/Position.h>
#include <graphics/RenderSystem2D.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;
using namespace test;

using namespace std;

int Test::start(int argc, char* argv[])
{
	#if defined(ICE_WINDOWS)
	Win32Window window;
	#elif defined(ICE_LINUX)
	LinuxWindow window;
	#endif
	Graphics graphics(window);

	Engine engine(window, graphics);
	
	Entity* ent = engine.entities().create();
	Position* pos = ent->attach<Position>();
	pos->Pos = glm::vec2(0.0f, 0.2f);
	SquareRenderer* renderer = ent->attach<SquareRenderer>();
	renderer->Dimensions = glm::vec2(1.2f, 0.7f);
	renderer->Color = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);

 	engine.startGame();

	return 0;
}

int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}

//START_ENGINE(Test)
