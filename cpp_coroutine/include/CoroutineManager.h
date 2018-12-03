#pragma once

#include <list>
#include <vector>

#include "Coroutine.h"

namespace cpp_coroutine
{
	class CoroutineManager
	{
	public:
		CoroutineManager();
		~CoroutineManager();

		Coroutine* StartCoroutine(Enumerator enumerator);
		void StopCoroutine(Coroutine* coro);
		void StopAllCoroutines();

		void ResumeCoroutines();
		bool HasCoroutines();

	private:
		Coroutine* push_coroutine(Coroutine* coro);
		Coroutine* pop_coroutine(Coroutine* coro);
		bool valid_resume(Coroutine *p);
	private:
		std::vector<Coroutine*> m_coroutines;
		void* m_pfiber;
	};

}
