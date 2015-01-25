#include "examples/Test.h"

#include <iostream>

#include <SFML/Window.hpp>

#include "core/Engine.h"
#include <SFML/Window.hpp>


using namespace ice;
using namespace core;
using namespace test;

using namespace std;

Test::Test() {
	
}

void Test::start() {
	sf::Window* window = new sf::Window(sf::VideoMode(800, 600), "Icicle Engine example");
	
	Engine engine(window);
	engine.startGame();
	cout << "Hello World!\n";
}


int main() {
	Test t;
	t.start();
}