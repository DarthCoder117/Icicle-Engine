#ifndef ICICLE_COMMON_H
#define ICICLE_COMMON_H
#include <IcicleConfig.h>

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <glm/glm.hpp>

namespace ice
{
	typedef int s32;///< Signed 32-bit integer
	typedef unsigned int u32;///< Unsigned 32-bit integer
	typedef long long s64;///< Signed 64-bit integer
	typedef unsigned long long u64;///< Unsigned 64-bit integer
	typedef char s8;///< Signed 8 bit integer
	typedef unsigned char u8;///< Unsigned 8-bit char
	typedef float f32;///< Signed 32-bit floating point
	typedef double f64;///< Signed 64-bit floating point
	
	typedef glm::u8vec3 Color3;
	typedef glm::u8vec4 Color4;
	typedef glm::vec3 Color3f;
	typedef glm::vec4 Color4f;

	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;
	typedef glm::uvec2 Vec2u;
	typedef glm::uvec3 Vec3u;
	typedef glm::uvec4 Vec4u;
	typedef glm::mat4x4 Mat4x4;
	
	template <typename T> using Vector = std::vector<T>;
	template <typename T> using List = std::list<T>;
	template <typename T, typename U> using Map = std::map<T, U>;
	template <typename T, typename U> using UnorderedMap = std::unordered_map<T, U>;

	typedef std::string String;
	typedef std::wstring Stringw;
}

#endif