#if !defined(_YIELDINSTRUCTION_H_)
#define _YIELDINSTRUCTION_H_
#include "Definition.h"


namespace cpp_coroutine
{
	class YieldInstruction
	{
		friend class CoroutineManager;

	public:
		TYPE_INFO GetType() { return m_type; }

	protected:
		YieldInstruction(TYPE_INFO InType)
			: m_type(InType)
		{
		}

		virtual ~YieldInstruction()
		{
		}
		virtual void end() = 0;
		virtual bool is_ended() = 0;

	protected:
		TYPE_INFO m_type;
	};

	class Coroutine;
	inline Coroutine* CastCoroutine(YieldInstruction * yield)
	{
		if (yield == nullptr || yield->GetType() != _TYPEID_<Coroutine>())
		{
			return nullptr;
		}
		return (Coroutine*)yield;
	}
}
#endif