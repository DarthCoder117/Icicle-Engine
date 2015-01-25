#include "examples/Test.h"

#include <iostream>

#include <SFML/Window.hpp>

#include "core/Engine.h"


using namespace ice;
using namespace core;
using namespace test;

using namespace std;

Test::Test() {
	
}

void Test::start() {

	sf::Window window(sf::VideoMode(800, 600), "Icicle Engine example");

	Engine engine(&window);
	
	cout << "Hello World!\n";
}


int main() {
	Test t;
	t.start();
}