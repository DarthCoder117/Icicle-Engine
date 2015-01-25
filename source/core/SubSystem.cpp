#include "core/SubSystem.h"

using namespace ice;
using namespace core;

SubSystemType ISubSystem::m_nextType = 0;

SubSystemType ISubSystem::getNextType()
{
	m_nextType++;
	return m_nextType;
}