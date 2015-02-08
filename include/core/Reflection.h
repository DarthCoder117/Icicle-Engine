#ifndef REFLECTION_H
#define REFLECTION_H
#include <IcicleCommon.h>
#include "core/StringUtils.h"

namespace ice
{
	namespace core
	{
		typedef u64 TypeID;

		class ClassInfo;
		class IReflectable;

		class Reflection
		{
		public:

			static ClassInfo* reflect(TypeID typeID);
			
			///@return The number of reflectable types with meta-information
			static u32 typeCount();
			///@return The class ifnormation for the tpye at the specified index.
			static ClassInfo* type(u32 idx);

		private:

			friend class ClassInfo;
			static void registerType(ClassInfo* reflect);

			static Vector<ClassInfo*> m_typeList;
			static UnorderedMap<TypeID, ClassInfo*> m_typeHashMap;
		};

		template <typename T>
		class TypeRegistry
		{
		public:

			static ClassInfo* const info;
		};

		class ClassInfo
		{
		public:

			virtual const char* name() = 0;

			virtual TypeID type() = 0;

			virtual size_t size() = 0;
		};

		///@brief Begins a reflection block
		#define BeginReflect(ClassType)\
		class ClassType##_MetaClass : public ice::core::ClassInfo\
		{\
		public:\
		const char* name(){ return #ClassType; }\
		ice::core::TypeID type(){ static ice::core::TypeID hashID = ice::core::StringUtils::stringHash(#ClassType); return hashID; }\
		size_t size(){ return sizeof(ClassType); }\
		ClassType##_MetaClass(){

		///@brief Ends a reflection block
		#define EndReflect(ClassType)\
		}}; \
		ClassType##_MetaClass g_##ClassType##_instance;\
		ClassInfo* const ice::core::TypeRegistry<ClassType>::info = &g_##ClassType##_instance;

		///@brief Reflectable object interface.
		///@warning Inherit from Reflectable<T> instead of this interface.
		class IReflectable
		{
		public:

			virtual ~IReflectable(){}

			virtual ClassInfo* reflect() = 0;
		};

		///@brief Base class for types that need to be reflectable.
		template <typename T>
		class Reflectable : public IReflectable
		{
		public:

			static ClassInfo* staticReflect()
			{
				return TypeRegistry<T>::info;
			}

			ClassInfo* reflect()
			{
				return T::staticReflect();
			}
		};

		//TEST
		class ReflectTest : public Reflectable<ReflectTest>
		{
		public:

		private:

			unsigned int m_field1;
			float m_field2;
		};
	}
}

#endif