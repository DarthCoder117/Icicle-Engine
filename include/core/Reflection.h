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
		class Reflectable;

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

		class ClassInfo
		{
		public:

			ClassInfo()
				:m_parentClass(NULL)
			{}

			virtual const char* name() = 0;

			virtual TypeID type() = 0;

			virtual size_t size() = 0;

			ClassInfo* parent(){ return m_parentClass; }

			bool inheritsFrom(ClassInfo* parentClass)
			{
				ClassInfo* p = parent();
				while (p)
				{
					if (p == parentClass)
					{
						return true;
					}

					p = p->parent();
				}

				return false;
			}

			template <typename T>
			bool inheritsFrom()
			{
				return inheritsFrom(T::staticReflect());
			}

		protected:

			ClassInfo* m_parentClass;
		};

		///@brief Begins a reflection block
		#define BeginReflect(ClassType)\
		static ice::core::ClassInfo* staticReflect(){ return ClassType::MetaClass::instance(); }\
		ice::core::ClassInfo* reflect(){ return ClassType::staticReflect(); }\
		class MetaClass : public ice::core::ClassInfo\
		{\
		public:\
		static MetaClass* instance(){ static MetaClass* inst = new MetaClass(); return inst; }\
		const char* name(){ return #ClassType; }\
		ice::core::TypeID type(){ static ice::core::TypeID hashID = ice::core::StringUtils::stringHash(#ClassType); return hashID; }\
		size_t size(){ return sizeof(ClassType); }\
		private:\
		MetaClass(){

		#define ParentClass(ClassType) m_parentClass = ClassType::MetaClass::instance();

		///@brief Ends a reflection block
		#define EndReflect(ClassType)}}; public:

		///@brief Reflectable object interface.
		class Reflectable
		{
		public:

			virtual ~Reflectable(){}

			virtual ClassInfo* reflect() = 0;
		};

		//TEST
		class ReflectParent : public Reflectable
		{
		public:

			BeginReflect(ReflectParent);
			
			EndReflect(ReflectParent);
		};

		class ReflectTest : public ReflectParent
		{
		public:

			BeginReflect(ReflectTest);
			ParentClass(ReflectParent);
			EndReflect(ReflectTest);

		private:

			unsigned int m_field1;
			float m_field2;
		};
	}
}

#endif