#pragma once

#include <windows.h>
#include <functional>

#ifndef STACK_LIMIT
#define STACK_LIMIT (1024*1024)
#endif

namespace cpp_coroutine
{
	using TYPE_INFO = void*;

	template <typename T> TYPE_INFO _TYPEID_()
	{
		return reinterpret_cast<TYPE_INFO>(&_TYPEID_<T>);
	}
	
	class YieldReturn;
	using Enumerator = std::function<void(YieldReturn&)>;

}

