#include "core/ComponentType.h"

using namespace ice;
using namespace core;

Vector<ComponentType*> ComponentTypes::m_types;

unsigned int ComponentTypes::addComponentType(ComponentType* type)
{
	m_types.push_back(type);
	return m_types.size() - 1;
}

ComponentType::ComponentType(const String& typeName, const size_t size)
	:m_typeID(StringUtils::stringHash(typeName.c_str())),
	m_typeIndex(0),
	m_typeName(typeName),
	m_size(size)
{
	m_typeIndex = ComponentTypes::addComponentType(this);
}