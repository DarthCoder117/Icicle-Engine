#include "core/SubSystem.h"

using namespace ice;
using namespace core;

void ISubSystem::onInit(Engine* engine)
{
	m_engine = engine;

	init();
}