#pragma once
#include "YieldInstruction.h"

namespace cpp_coroutine
{
	//	return false 종료
	class WaitWhile final : public YieldInstruction
	{
	public:
		WaitWhile(std::function<bool()> condition)
			: YieldInstruction(_TYPEID_<WaitWhile>())
			, m_condition(condition)
		{

		}
		virtual ~WaitWhile()
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
			return !m_condition();
		}

	private:
		std::function<bool()> m_condition;
	};


}