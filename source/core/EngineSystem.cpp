#include "core/EngineSystem.h"

using namespace ice;
using namespace core;

void IEngineSystem::onRegistered(Engine* engine)
{
	m_engine = engine;
}