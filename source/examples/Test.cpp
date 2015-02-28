#include "examples/Test.h"

#include <iostream>

#include <core/Engine.h>
#include <core/Debug.h>
#include <core/FileStream.h>

#include <core/Reflection.h>

#include <system/LinuxWindow.h>
#include <system/Win32Window.h>

#include <core/ResourceManager.h>

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;
using namespace test;

using namespace std;

class TestComponent : public Component<TestComponent>
{
public:

	~TestComponent()
	{
		printf("Destroyed\n");
	}

	unsigned int testNum;
};

int Test::start(int argc, char* argv[])
{
	core::LaunchParameters params;
	params.m_argc = argc;
	params.m_argv = argv;

	#if defined(ICE_WINDOWS)
	Win32Window window;
	#elif defined(ICE_LINUX)
	LinuxWindow window;
	#endif
	Engine engine(params, window);
	
	engine.init();

	Entity* ent = engine.getEntityManager().create();
	TestComponent* testComp = ent->attach<TestComponent>();
	printf("Attached TestComponent\n");
	testComp->testNum = 10;

	if (!ent->has<TestComponent>())
	{
		printf("Does not have TestComponent\n");
	}
	if (ent->has<TestComponent>())
	{
		printf("Has TestComponent\n");
	}

	ent->detach<TestComponent>();
	printf("Detached TestComponent\n");

	if (!ent->has<TestComponent>())
	{
		printf("Does not have TestComponent\n");
	}
	if (ent->has<TestComponent>())
	{
		printf("Has TestComponent\n");
	}

 	engine.startGame();

	return 0;
}

int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}

//START_ENGINE(Test)
