#pragma once
#include "YieldInstruction.h"

namespace cpp_coroutine
{
	//	return false ����
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
		// YieldInstruction��(��) ���� ��ӵ�
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