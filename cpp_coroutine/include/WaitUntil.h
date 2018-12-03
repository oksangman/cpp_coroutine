#if !defined(_WAITUNTIL_H_)
#define _WAITUNTIL_H_
#include "YieldInstruction.h"

namespace cpp_coroutine
{
	//	return true 종료
	class WaitUntil final : public YieldInstruction
	{
	public:
		WaitUntil(std::function<bool()> condition)
			: YieldInstruction(_TYPEID_<WaitUntil>())
			, m_condition(condition)
		{

		}
		virtual ~WaitUntil()
		{

		}

	private:
		// YieldInstruction을(를) 통해 상속됨
		virtual void end() override
		{
			m_condition = []() {
				return false;
			};
		}

		virtual bool is_ended() override
		{
			return m_condition();
		}

	private:
		std::function<bool()> m_condition;
	};


}
#endif