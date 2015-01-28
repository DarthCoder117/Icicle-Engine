#include "examples/Test.h"

#include <iostream>

#include "core/Engine.h"
#include "SFML/System.hpp"

using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;
using namespace test;

using namespace std;

void test1(){
	for(int i = 0; i < 10; i++) {
		sf::sleep(sf::milliseconds(i));
		cout << "THREAD 1 \n";
	}
}


void test2(){
	for(int i = 0; i < 10; i++){
		sf::sleep(sf::milliseconds(i));
		cout << "THREAD 2 \n";
	}
}


int Test::start(int argc, char* argv[])
{
// 	cout << "Hello World!\n";
// 
// 	core::LaunchParameters params;
// 	params.m_argc = argc;
// 	params.m_argv = argv;
// 
// 	Engine engine(params);
// 	
// 	//This is where custom sub-systems would be created and registered...
// 
// 	engine.startGame();

	sf::Thread t(test1);
	sf::Thread t2(test2);
	
	t.launch();
	t2.launch();
	
	for(int i = 0; i < 10; i++)
		cout << "THREAD Main \n";
	
	return 0;
}

int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}

//START_ENGINE(Test)
