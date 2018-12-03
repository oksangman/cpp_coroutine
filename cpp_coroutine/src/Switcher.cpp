
#include "Switcher.h"
#include "Coroutine.h"


namespace cpp_coroutine 
{
#if _MSC_VER
	Switcher::Switcher()
		: m_fiber(nullptr)
		, m_bCoroutine(true)
	{
	}

	Switcher::~Switcher()
	{
		if (m_bCoroutine)
			DeleteFiber(m_fiber);
	}

	void Switcher::InitMain()
	{
		m_fiber = ConvertThreadToFiber(nullptr);
		m_bCoroutine = false;
	}
	void Switcher::InitCoroutine(Coroutine *coro, Switcher* pmain)
	{
		m_fiber = CreateFiber(STACK_LIMIT, &Coroutine::entry, coro);
	}
	void Switcher::Swap(Switcher* pmain)
	{
		SwitchToFiber(m_fiber);
	}


#else
	Switcher::Switcher()
		: m_stack(nullptr)
	{
	}

	Switcher::~Switcher()
	{
		if (m_stack != nullptr)
		{
			delete[] m_stack;
		}
	}
	void Switcher::InitMain()
	{
	}
	void Switcher::InitCoroutine(Coroutine* coro, Switcher* pmain)
	{
		m_stack = new char[STACK_LIMIT];
		m_ctx.uc_stack.ss_sp = m_stack;
		m_ctx.uc_stack.ss_size = STACK_LIMIT;
		m_ctx.uc_link = &(pmain->m_ctx);

		makecontext(&m_ctx, (void (*)(void))(&Coroutine::entry), 0);
	}
	void Switcher::Swap(Switcher* pmain)
	{
		swapcontext(&pmain->m_ctx, &m_ctx);
	}
#endif

}