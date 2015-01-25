#include "examples/Test.h"

#include <iostream>

#include "core/Engine.h"


using namespace ice;
using namespace core;
using namespace test;

using namespace std;

Test::Test() {
	
}

void Test::start() {
	Engine engine;
	
	engine.buildTest();
}


int main() {
	Test t;
	t.start();
}