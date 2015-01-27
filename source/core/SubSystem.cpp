#include "core/SubSystem.h"

using namespace ice;
using namespace core;

void ISubSystem::onRegistered(Engine* engine)
{
	m_engine = engine;
}