#if !defined(_SWITCHER_H_)
#define _SWITCHER_H_

#include "Definition.h"

namespace cpp_coroutine
{
	class Coroutine;
	class Switcher
	{
	public:
		Switcher();
		~Switcher();

		void InitMain();
		void InitCoroutine(Coroutine*, Switcher*);
		void Swap(Switcher*);



	private:
#if _MSC_VER
		void* m_fiber;
		bool m_bCoroutine;
#else
		ucontext_t m_ctx;
		char* m_stack;
#endif
	};
}
#endif
