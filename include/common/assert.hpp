#ifndef __ASSERT_HPP__
#define __ASSERT_HPP__

#include <filesystem>
#include <log.hpp>

#if defined(_MSC_VER)
	#define GFX_DEBUGBREAK() __debugbreak()
#elif defined(__llvm__)
	#define GFX_DEBUGBREAK() __builtin_trap()
#else
	#define GFX_DEBUGBREAK()
#endif

#define GFX_EXPAND_MACRO(x) x
#define GFX_STRINGIFY_MACRO(x) #x

#define GFX_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { GFX##type##ERROR(msg, __VA_ARGS__); GFX_DEBUGBREAK(); } }
#define GFX_INTERNAL_ASSERT_WITH_MSG(type, check, ...) GFX_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define GFX_INTERNAL_ASSERT_NO_MSG(type, check) GFX_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", GFX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define GFX_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define GFX_INTERNAL_ASSERT_GET_MACRO(...) GFX_EXPAND_MACRO( GFX_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, GFX_INTERNAL_ASSERT_WITH_MSG, GFX_INTERNAL_ASSERT_NO_MSG) )

#define GFX_ASSERT(...) GFX_EXPAND_MACRO( GFX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )

#endif // !__ASSERT_HPP__
