/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_PLATFORM_H_HEADER_GUARD
#define BGFX_PLATFORM_H_HEADER_GUARD

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

/*
 * Copyright 2010-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BX_PLATFORM_H_HEADER_GUARD
#define BX_PLATFORM_H_HEADER_GUARD

#define BX_COMPILER_CLANG           0
#define BX_COMPILER_CLANG_ANALYZER  0
#define BX_COMPILER_GCC             0
#define BX_COMPILER_MSVC            0
#define BX_COMPILER_MSVC_COMPATIBLE 0

#define BX_PLATFORM_ANDROID    0
#define BX_PLATFORM_EMSCRIPTEN 0
#define BX_PLATFORM_FREEBSD    0
#define BX_PLATFORM_IOS        0
#define BX_PLATFORM_LINUX      0
#define BX_PLATFORM_NACL       0
#define BX_PLATFORM_OSX        0
#define BX_PLATFORM_QNX        0
#define BX_PLATFORM_RPI        0
#define BX_PLATFORM_WINDOWS    0
#define BX_PLATFORM_WINRT      0
#define BX_PLATFORM_XBOX360    0

#define BX_CPU_ARM  0
#define BX_CPU_JIT  0
#define BX_CPU_MIPS 0
#define BX_CPU_PPC  0
#define BX_CPU_X86  0

#define BX_ARCH_32BIT 0
#define BX_ARCH_64BIT 0

#define BX_CPU_ENDIAN_BIG    0
#define BX_CPU_ENDIAN_LITTLE 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(__clang__)
// clang defines __GNUC__ or _MSC_VER
#	undef  BX_COMPILER_CLANG
#	define BX_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#	if defined(__clang_analyzer__)
#		undef  BX_COMPILER_CLANG_ANALYZER
#		define BX_COMPILER_CLANG_ANALYZER 1
#	endif // defined(__clang_analyzer__)
#	if defined(_MSC_VER)
#		undef  BX_COMPILER_MSVC_COMPATIBLE
#		define BX_COMPILER_MSVC_COMPATIBLE _MSC_VER
#	endif // defined(_MSC_VER)
#elif defined(_MSC_VER)
#	undef  BX_COMPILER_MSVC
#	define BX_COMPILER_MSVC _MSC_VER
#	undef  BX_COMPILER_MSVC_COMPATIBLE
#	define BX_COMPILER_MSVC_COMPATIBLE _MSC_VER
#elif defined(__GNUC__)
#	undef  BX_COMPILER_GCC
#	define BX_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "BX_COMPILER_* is not defined!"
#endif //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__) || defined(_M_ARM)
#	undef  BX_CPU_ARM
#	define BX_CPU_ARM 1
#	define BX_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__) || defined(__mips_isa_rev) // defined(mips)
#	undef  BX_CPU_MIPS
#	define BX_CPU_MIPS 1
#	define BX_CACHE_LINE_SIZE 64
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#	undef  BX_CPU_PPC
#	define BX_CPU_PPC 1
#	define BX_CACHE_LINE_SIZE 128
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
#	undef  BX_CPU_X86
#	define BX_CPU_X86 1
#	define BX_CACHE_LINE_SIZE 64
#else // PNaCl doesn't have CPU defined.
#	undef  BX_CPU_JIT
#	define BX_CPU_JIT 1
#	define BX_CACHE_LINE_SIZE 64
#endif //

#if defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) || defined(__ppc64__)
#	undef  BX_ARCH_64BIT
#	define BX_ARCH_64BIT 64
#else
#	undef  BX_ARCH_32BIT
#	define BX_ARCH_32BIT 32
#endif //

#if BX_CPU_PPC
#	undef  BX_CPU_ENDIAN_BIG
#	define BX_CPU_ENDIAN_BIG 1
#else
#	undef  BX_CPU_ENDIAN_LITTLE
#	define BX_CPU_ENDIAN_LITTLE 1
#endif // BX_PLATFORM_

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_XBOX_VER)
#	undef  BX_PLATFORM_XBOX360
#	define BX_PLATFORM_XBOX360 1
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#   include <windows.h>
#	if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#		undef  BX_PLATFORM_WINDOWS
#		if !defined(WINVER) && !defined(_WIN32_WINNT)
#			if BX_ARCH_64BIT
//				When building 64-bit target Win7 and above.
#				define WINVER 0x0601
#				define _WIN32_WINNT 0x0601
#			else
//				Windows Server 2003 with SP1, Windows XP with SP2 and above
#				define WINVER 0x0502
#				define _WIN32_WINNT 0x0502
#			endif // BX_ARCH_64BIT
#		endif // !defined(WINVER) && !defined(_WIN32_WINNT)
#		define BX_PLATFORM_WINDOWS _WIN32_WINNT
#	else
#		undef  BX_PLATFORM_WINRT
#		define BX_PLATFORM_WINRT 1
#	endif
#elif defined(__VCCOREVER__)
// RaspberryPi compiler defines __linux__
#	undef  BX_PLATFORM_RPI
#	define BX_PLATFORM_RPI 1
#elif defined(__native_client__)
// NaCl compiler defines __linux__
#	include <ppapi/c/pp_macros.h>
#	undef  BX_PLATFORM_NACL
#	define BX_PLATFORM_NACL PPAPI_RELEASE
#elif defined(__ANDROID__)
// Android compiler defines __linux__
#	include <android/api-level.h>
#	undef  BX_PLATFORM_ANDROID
#	define BX_PLATFORM_ANDROID __ANDROID_API__
#elif defined(__linux__)
#	undef  BX_PLATFORM_LINUX
#	define BX_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#	undef  BX_PLATFORM_IOS
#	define BX_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#	undef  BX_PLATFORM_OSX
#	define BX_PLATFORM_OSX 1
#elif defined(EMSCRIPTEN)
#	undef  BX_PLATFORM_EMSCRIPTEN
#	define BX_PLATFORM_EMSCRIPTEN 1
#elif defined(__QNX__)
#	undef  BX_PLATFORM_QNX
#	define BX_PLATFORM_QNX 1
#elif defined(__FreeBSD__)
#	undef  BX_PLATFORM_FREEBSD
#	define BX_PLATFORM_FREEBSD 1
#else
#	error "BX_PLATFORM_* is not defined!"
#endif //

#define BX_PLATFORM_POSIX (0 \
|| BX_PLATFORM_ANDROID \
|| BX_PLATFORM_EMSCRIPTEN \
|| BX_PLATFORM_FREEBSD \
|| BX_PLATFORM_IOS \
|| BX_PLATFORM_LINUX \
|| BX_PLATFORM_NACL \
|| BX_PLATFORM_OSX \
|| BX_PLATFORM_QNX \
|| BX_PLATFORM_RPI \
)

#ifndef  BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS
#	define BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS 0
#endif // BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS

#if BX_COMPILER_GCC
#	define BX_COMPILER_NAME "GCC " \
BX_STRINGIZE(__GNUC__) "." \
BX_STRINGIZE(__GNUC_MINOR__) "." \
BX_STRINGIZE(__GNUC_PATCHLEVEL__)
#elif BX_COMPILER_CLANG
#	define BX_COMPILER_NAME "Clang " \
BX_STRINGIZE(__clang_major__) "." \
BX_STRINGIZE(__clang_minor__) "." \
BX_STRINGIZE(__clang_patchlevel__)
#elif BX_COMPILER_MSVC
#	if BX_COMPILER_MSVC >= 1800
#		define BX_COMPILER_NAME "MSVC 12.0"
#	elif BX_COMPILER_MSVC >= 1700
#		define BX_COMPILER_NAME "MSVC 11.0"
#	elif BX_COMPILER_MSVC >= 1600
#		define BX_COMPILER_NAME "MSVC 10.0"
#	elif BX_COMPILER_MSVC >= 1500
#		define BX_COMPILER_NAME "MSVC 9.0"
#	else
#		define BX_COMPILER_NAME "MSVC"
#	endif //
#endif // BX_COMPILER_

#if BX_PLATFORM_ANDROID
#	define BX_PLATFORM_NAME "Android " \
BX_STRINGIZE(BX_PLATFORM_ANDROID)
#elif BX_PLATFORM_EMSCRIPTEN
#	define BX_PLATFORM_NAME "asm.js " \
BX_STRINGIZE(__EMSCRIPTEN_major__) "." \
BX_STRINGIZE(__EMSCRIPTEN_minor__) "." \
BX_STRINGIZE(__EMSCRIPTEN_tiny__)
#elif BX_PLATFORM_FREEBSD
#	define BX_PLATFORM_NAME "FreeBSD"
#elif BX_PLATFORM_IOS
#	define BX_PLATFORM_NAME "iOS"
#elif BX_PLATFORM_LINUX
#	define BX_PLATFORM_NAME "Linux"
#elif BX_PLATFORM_NACL
#	define BX_PLATFORM_NAME "NaCl " \
BX_STRINGIZE(BX_PLATFORM_NACL)
#elif BX_PLATFORM_OSX
#	define BX_PLATFORM_NAME "OSX"
#elif BX_PLATFORM_QNX
#	define BX_PLATFORM_NAME "QNX"
#elif BX_PLATFORM_RPI
#	define BX_PLATFORM_NAME "RaspberryPi"
#elif BX_PLATFORM_WINDOWS
#	define BX_PLATFORM_NAME "Windows"
#elif BX_PLATFORM_WINRT
#	define BX_PLATFORM_NAME "WinRT"
#endif // BX_PLATFORM_

#if BX_CPU_ARM
#	define BX_CPU_NAME "ARM"
#elif BX_CPU_MIPS
#	define BX_CPU_NAME "MIPS"
#elif BX_CPU_PPC
#	define BX_CPU_NAME "PowerPC"
#elif BX_CPU_JIT
#	define BX_CPU_NAME "JIT-VM"
#elif BX_CPU_X86
#	define BX_CPU_NAME "x86"
#endif // BX_CPU_

#if BX_ARCH_32BIT
#	define BX_ARCH_NAME "32-bit"
#elif BX_ARCH_64BIT
#	define BX_ARCH_NAME "64-bit"
#endif // BX_ARCH_

#if BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && BX_COMPILER_MSVC
#	pragma warning(error:4062) // ENABLE warning C4062: enumerator'...' in switch of enum '...' is not handled
#	pragma warning(error:4121) // ENABLE warning C4121: 'symbol' : alignment of a member was sensitive to packing
//#	pragma warning(error:4127) // ENABLE warning C4127: conditional expression is constant
#	pragma warning(error:4130) // ENABLE warning C4130: 'operator' : logical operation on address of string constant
#	pragma warning(error:4239) // ENABLE warning C4239: nonstandard extension used : 'argument' : conversion from '*' to '* &' A non-const reference may only be bound to an lvalue
//#	pragma warning(error:4244) // ENABLE warning C4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
#	pragma warning(error:4245) // ENABLE warning C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
#	pragma warning(error:4263) // ENABLE warning C4263: 'function' : member function does not override any base class virtual member function
#	pragma warning(error:4265) // ENABLE warning C4265: class has virtual functions, but destructor is not virtual
#	pragma warning(error:4431) // ENABLE warning C4431: missing type specifier - int assumed. Note: C no longer supports default-int
#	pragma warning(error:4545) // ENABLE warning C4545: expression before comma evaluates to a function which is missing an argument list
#	pragma warning(error:4549) // ENABLE warning C4549: 'operator' : operator before comma has no effect; did you intend 'operator'?
#	pragma warning(error:4701) // ENABLE warning C4701: potentially uninitialized local variable 'name' used
#	pragma warning(error:4706) // ENABLE warning C4706: assignment within conditional expression
#	pragma warning(error:4100) // ENABLE warning C4100: '' : unreferenced formal parameter
#	pragma warning(error:4189) // ENABLE warning C4189: '' : local variable is initialized but not referenced
#	pragma warning(error:4505) // ENABLE warning C4505: '' : unreferenced local function has been removed
#endif // BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && BX_COMPILER_MSVC

#endif // BX_PLATFORM_H_HEADER_GUARD


namespace bgfx
{
	struct RenderFrame
	{
		enum Enum
		{
			NoContext,
			Render,
			Exiting,

			Count
		};
	};

	/// WARNING: This call should be only used on platforms that don't
	/// allow creating separate rendering thread. If it is called before
	/// to bgfx::init, render thread won't be created by bgfx::init call.
	RenderFrame::Enum renderFrame();
}

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>

namespace bgfx
{
	///
	void androidSetWindow(::ANativeWindow* _window);

} // namespace bgfx

#elif BX_PLATFORM_IOS
namespace bgfx
{
	///
	void iosSetEaglLayer(void* _layer);

} // namespace bgfx

#elif BX_PLATFORM_FREEBSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI
#	include <X11/Xlib.h>

namespace bgfx
{
	///
	void x11SetDisplayWindow(::Display* _display, ::Window _window);

} // namespace bgfx

#elif BX_PLATFORM_NACL
#	include <ppapi/c/ppb_graphics_3d.h>
#	include <ppapi/c/ppb_instance.h>

namespace bgfx
{
	typedef void (*PostSwapBuffersFn)(uint32_t _width, uint32_t _height);

	///
	bool naclSetInterfaces(::PP_Instance, const ::PPB_Instance*, const ::PPB_Graphics3D*, PostSwapBuffersFn);

} // namespace bgfx

#elif BX_PLATFORM_OSX
namespace bgfx
{
	///
	void osxSetNSWindow(void* _window);

} // namespace bgfx

#elif BX_PLATFORM_WINDOWS
#	include <windows.h>

namespace bgfx
{
	///
	void winSetHwnd(::HWND _window);

} // namespace bgfx

#elif BX_PLATFORM_WINRT
#   include <Unknwn.h>

namespace bgfx
{
    ///
    void winrtSetWindow(IUnknown* _window);

} // namespace bgfx

#endif // BX_PLATFORM_

#if defined(_SDL_H)
// If SDL.h is included before bgfxplatform.h we can enable SDL window
// interop convenience code.

#	include <SDL2/SDL_syswm.h>

namespace bgfx
{
	///
	inline bool sdlSetWindow(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) )
		{
			return false;
		}

#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
		x11SetDisplayWindow(wmi.info.x11.display, wmi.info.x11.window);
#	elif BX_PLATFORM_OSX
		osxSetNSWindow(wmi.info.cocoa.window);
#	elif BX_PLATFORM_WINDOWS
		winSetHwnd(wmi.info.win.window);
#	endif // BX_PLATFORM_

		return true;
	}

} // namespace bgfx

#elif defined(_glfw3_h_)
// If GLFW/glfw3.h is included before bgfxplatform.h we can enable GLFW3
// window interop convenience code.

#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
#		define GLFW_EXPOSE_NATIVE_X11
#		define GLFW_EXPOSE_NATIVE_GLX
#	elif BX_PLATFORM_OSX
#		define GLFW_EXPOSE_NATIVE_COCOA
#		define GLFW_EXPOSE_NATIVE_NSGL
#	elif BX_PLATFORM_WINDOWS
#		define GLFW_EXPOSE_NATIVE_WIN32
#		define GLFW_EXPOSE_NATIVE_WGL
#	endif //
#	include <GLFW/glfw3native.h>

namespace bgfx
{
	inline void glfwSetWindow(GLFWwindow* _window)
	{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
		::Display* display = glfwGetX11Display();
		::Window window = glfwGetX11Window(_window);
		x11SetDisplayWindow(display, window);
#	elif BX_PLATFORM_OSX
		void* id = glfwGetCocoaWindow(_window);
		osxSetNSWindow(id);
#	elif BX_PLATFORM_WINDOWS
		HWND hwnd = glfwGetWin32Window(_window);
		winSetHwnd(hwnd);
#	endif BX_PLATFORM_WINDOWS
	}

} // namespace bgfx

#endif // defined(_SDL_H)

#endif // BGFX_PLATFORM_H_HEADER_GUARD
