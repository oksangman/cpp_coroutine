#pragma once

namespace cpp_coroutine
{
	class Coroutine;
	class YieldInstruction;
	class YieldReturn
	{
	public:
		YieldReturn(Coroutine *coro);

		void operator()(YieldInstruction *yi);

	private:
		Coroutine *m_pcoro;
	};
}