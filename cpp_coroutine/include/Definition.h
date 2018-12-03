#if !defined(_DEFINITION_H_)
#define _DEFINITION_H_

#if _MSC_VER
#include <windows.h>
#else
#if defined(__APPLE__) && defined(__MACH__)
#define _XOPEN_SOURCE
#include <ucontext.h>
#else
#include <ucontext.h>
#endif
#endif

#include <functional>

#ifndef STACK_LIMIT
#define STACK_LIMIT (1024*1024)
#endif

namespace cpp_coroutine
{
#if _MSC_VER
	using TYPE_INFO = void*;

	class YieldReturn;
	using Enumerator = std::function<void(YieldReturn&)>;
#else
	typedef void* TYPE_INFO;

	class YieldReturn;
	typedef std::function<void(YieldReturn&)> Enumerator;
#endif

	template <typename T> TYPE_INFO _TYPEID_()
	{
		return reinterpret_cast<TYPE_INFO>(&_TYPEID_<T>);
	}

}

#ifndef nullptr
#define nullptr NULL
#endif

#endif
