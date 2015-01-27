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

int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}

//START_ENGINE(Test)