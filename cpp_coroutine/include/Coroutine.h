#pragma once

#include "YieldInstruction.h"

namespace cpp_coroutine
{
	class Coroutine final : public YieldInstruction
	{
		friend class YieldReturn;
		friend class CoroutineManager;
	public:
		Coroutine(Enumerator func, void* mainfiber);
		 
		virtual ~Coroutine();

	protected:
		static void __stdcall entry(void* lpParameter);

		void resume();
		void yield();

		// YieldInstruction을(를) 통해 상속됨
		virtual void end() override;
		virtual bool is_ended() override;


		inline YieldInstruction* get_yieldreturn()
		{
			return m_pyield_return;
		}

		Coroutine* get_yieldreturn_as_coroutine()
		{
			if (m_pyield_return == nullptr || m_pyield_return->GetType() != _TYPEID_<Coroutine>())
			{
				return nullptr;
			}
			return (Coroutine*)m_pyield_return;
		}

		inline void set_null_yieldreturn()
		{
			m_pyield_return = nullptr;
		}



	private:
		void* m_pmainfiber;
		void* m_pfiber;
		bool m_ended;
		Enumerator m_func;
		YieldInstruction* m_pyield_return;
		Coroutine* m_pnext;

	};

}
