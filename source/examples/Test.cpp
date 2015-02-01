#include "examples/Test.h"

#include <iostream>

#include <core/Engine.h>
#include <core/Debug.h>
#include <core/FileStream.h>
#include "SFML/System.hpp"


using namespace ice;
using namespace core;
using namespace graphics;
using namespace system;
using namespace test;

using namespace std;


int Test::start(int argc, char* argv[])
{
 	core::LaunchParameters params;
	params.m_argc = argc;
 	params.m_argv = argv;

 	Engine engine(params);
 	
 	//This is where custom sub-systems would be created and registered...
 
	engine.getFileSystem().mount("test");
	SharedPtr<core::DataStream> stream = engine.getFileSystem().openFile("test-text.txt");

	size_t streamSz = stream->getSize();
	char* buffer = (char*)malloc(streamSz+1);
	stream->read((void*)buffer, streamSz);
	buffer[streamSz] = NULL;

	stream->close();

 	engine.startGame();
	
/*
	sf::Thread t(test1);
	sf::Thread t2(test2);
	
	t.launch();
	t2.launch();
	
	for(int i = 0; i < 10; i++)
		cout << "THREAD Main \n";
	*/

	return 0;
}

int main(int argc, char* argv[])
{
	Test test;
	return test.start(argc, argv);
}

//START_ENGINE(Test)
