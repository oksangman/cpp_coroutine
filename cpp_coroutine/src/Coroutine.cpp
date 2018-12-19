#include "Coroutine.h"
#include "YieldReturn.h"

namespace cpp_coroutine
{
	Coroutine::Coroutine(Enumerator func, Switcher* pmainswitcher)
		: YieldInstruction(_TYPEID_<Coroutine>())
		, m_func(func)
		, m_pmainswitcher(pmainswitcher)
		, m_ended(false)
		, m_pnext(nullptr)
		, m_pyield_return(nullptr)
	{
		m_switcher.InitCoroutine(const_cast<Coroutine*>(this), m_pmainswitcher);
	}

	Coroutine::~Coroutine()
	{
	}
#if _MSC_VER
	void __stdcall Coroutine::entry(void * lpParameter)
	{
		Coroutine* pcoro = (Coroutine*)lpParameter;
#else
	void Coroutine::entry(Coroutine* pcoro)
	{
#endif
		YieldReturn yr(pcoro);

		pcoro->m_func(yr);

		pcoro->end();
		pcoro->yield();
	}

	void Coroutine::resume()
	{
		m_switcher.Swap(m_pmainswitcher);
	}

	void Coroutine::yield()
	{
		m_pmainswitcher->Swap(&m_switcher);
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
