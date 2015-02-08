#include "core/Reflection.h"

using namespace ice;
using namespace core;

Vector<ClassInfo*> Reflection::m_typeList;
UnorderedMap<TypeID, ClassInfo*> Reflection::m_typeHashMap;

ClassInfo* Reflection::reflect(TypeID typeID)
{
	auto iter = m_typeHashMap.find(typeID);
	if (iter != m_typeHashMap.end())
	{
		return iter->second;
	}

	return NULL;
}

u32 Reflection::typeCount()
{
	return m_typeList.size();
}

ClassInfo* Reflection::type(u32 idx)
{
	return m_typeList[idx];
}

void Reflection::registerType(ClassInfo* reflect)
{
	TypeID typeID = reflect->type();

	m_typeList.push_back(reflect);
	m_typeHashMap[typeID] = reflect;
}

BeginReflect(ReflectTest)

EndReflect(ReflectTest)