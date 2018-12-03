#include "Coroutine.h"
#include "YieldReturn.h"

namespace cpp_coroutine
{
	Coroutine::Coroutine(Enumerator func, void * mainfiber)
		: YieldInstruction(_TYPEID_<Coroutine>())
		, m_func(func)
		, m_pmainfiber(mainfiber)
		, m_ended(false)
		, m_pnext(nullptr)
		, m_pyield_return(nullptr)
	{
		m_pfiber = CreateFiber(STACK_LIMIT, entry, this);
	}

	Coroutine::~Coroutine()
	{
		DeleteFiber(m_pfiber);
	}

	void __stdcall Coroutine::entry(void * lpParameter)
	{
		Coroutine* pcoro = (Coroutine*)lpParameter;
		YieldReturn yr(pcoro);

		pcoro->m_func(yr);

		pcoro->end();
		pcoro->yield();
	}

	void Coroutine::resume()
	{
		SwitchToFiber(m_pfiber);
	}

	void Coroutine::yield()
	{
		SwitchToFiber(m_pmainfiber);
	}

	void Coroutine::end()
	{
		m_ended = true;
	}

	bool Coroutine::is_ended()
	{
		return m_ended;
	}
}