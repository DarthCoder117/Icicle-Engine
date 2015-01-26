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

void Test::init() 
{	
	cout << "Hello World!\n";
}

START_ENGINE(Test)