#include "CoroutineManager.h"

namespace cpp_coroutine
{
	CoroutineManager::CoroutineManager()
	{
		m_swicher.InitMain();
	}


	CoroutineManager::~CoroutineManager()
	{
	}

	Coroutine* CoroutineManager::StartCoroutine(Enumerator enumerator)
	{
		return push_coroutine(new Coroutine(enumerator, &m_swicher));
	}

	void CoroutineManager::StopCoroutine(Coroutine * coro)
	{
		YieldInstruction* temp = nullptr;
		while (coro != nullptr)
		{
			temp = coro->get_yieldreturn();
			coro->end();

			coro = CastCoroutine(temp);
		}

		if (temp != nullptr)
			temp->end();
	}

	void CoroutineManager::StopAllCoroutines()
	{
		for (Coroutine *p : m_coroutines)
		{
			StopCoroutine(p);
		}
	}

	void CoroutineManager::ResumeCoroutines()
	{
		std::vector<Coroutine*> temp_coro;
		temp_coro.swap(m_coroutines);

		//for (Coroutine* coro : temp_coro)
		for (int i=0; i<temp_coro.size(); ++i)
		{
			Coroutine* coro = temp_coro[i];
			if (!valid_resume(coro))
			{
				continue;
			}

			while (coro != nullptr)
			{
				coro->resume();
				if (!coro->is_ended())
				{
					push_coroutine(coro);
					break;
				}
				coro = pop_coroutine(coro);
			}
		}
	}

	bool CoroutineManager::HasCoroutines()
	{
		return !m_coroutines.empty();
	}

	Coroutine* CoroutineManager::push_coroutine(Coroutine* coro)
	{	
		if (coro == nullptr)
			return nullptr;


		Coroutine* temp = CastCoroutine(coro->get_yieldreturn());
		if (temp == nullptr)
		{
			m_coroutines.push_back(coro);
		}
		else
		{
			temp->m_pnext = coro;
		}
		return coro;
	}

	Coroutine* CoroutineManager::pop_coroutine(Coroutine* coro)
	{
		Coroutine* pnext = coro->m_pnext;
		delete coro;
		return pnext;
	}

	bool CoroutineManager::valid_resume(Coroutine *p)
	{
		YieldInstruction* yield = p->get_yieldreturn();
		
		if (yield == nullptr)
			return true;
		
		
		if (yield->is_ended())
		{
			p->set_null_yieldreturn();
			delete yield;
			return true;
		}
		m_coroutines.push_back(p);
		return false;
	}

}
