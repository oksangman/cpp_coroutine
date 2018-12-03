#include "YieldReturn.h"
#include "Coroutine.h"

namespace cpp_coroutine
{
	YieldReturn::YieldReturn(Coroutine * coro)
		: m_pcoro(coro)
	{

	}

	void YieldReturn::operator()(YieldInstruction * yi)
	{
		m_pcoro->m_pyield_return = yi;
		m_pcoro->yield();
	}
}
