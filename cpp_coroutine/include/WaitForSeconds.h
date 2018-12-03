#pragma once
#include "YieldInstruction.h"
#include <ctime>

namespace cpp_coroutine
{
	class WaitForSeconds final : public YieldInstruction
	{
	public:
		WaitForSeconds(float seconds)
			: YieldInstruction(_TYPEID_<WaitForSeconds>())
			, m_time(now() + seconds)
		{
		}
		virtual ~WaitForSeconds()
		{

		}

	private:
		// YieldInstruction을(를) 통해 상속됨
		virtual void end() override
		{
			m_time = now();
		}

		virtual bool is_ended() override
		{
			return m_time <= now();
		}

		inline float now()
		{
			return std::clock() / static_cast<float>(CLOCKS_PER_SEC);
		}

	private:
		float m_time;
	};


}