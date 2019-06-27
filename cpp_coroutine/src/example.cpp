

#if 1
#include <iostream>
#include <string>
#include <sstream>
#include "cpp_coroutine.h"

using namespace cpp_coroutine;

class ExampleBehaviour : public CoroutineManager
{
private:
	std::stringstream Stream;

public:
	Enumerator TaskA()
	{
		return [=](YieldReturn& yield_return)
		{
			Stream << "A1 ";
			yield_return(nullptr);

			Stream << "A2 ";
		};
	}

	Enumerator TaskB(float Param)
	{
		return [=](YieldReturn& yield_return)
		{
			Stream << "B1 ";
			yield_return(new WaitForSeconds(Param));

			Stream << "B2 ";
			yield_return(new WaitForSeconds(Param));

			Stream << "B3 ";
		};
	}

	Enumerator TaskC(float Param)
	{
		return [=](YieldReturn& yield_return)
		{
			Stream << "C1 ";
			yield_return(StartCoroutine(TaskA()));

			Stream << "C2 ";
			yield_return(StartCoroutine(TaskB(Param)));

			Stream << "C3 ";
		};
	}

	Enumerator TaskD(int Param)
	{
		return [=](YieldReturn& yield_return)
		{
			for (int i = 1; i < Param; i++)
			{
				Stream << "D" << i << " ";
				yield_return(new WaitForSeconds(0.5f));
			}
			Stream << "D" << Param << " ";
		};
	}

	void Test()
	{
		std::cout << Stream.str() << std::endl;
		Stream.str("");

		while (HasCoroutines())
		{
			ResumeCoroutines();

			auto str = Stream.str();
			if (str.size() > 0)
			{
				std::cout << str << std::endl;
				Stream.str("");
			}
		}
	}
};

int main()
{
	ExampleBehaviour foo;
	foo.StartCoroutine(foo.TaskA());
	foo.StartCoroutine(foo.TaskB(1.0f));
	foo.StartCoroutine(foo.TaskC(2.0f));
	foo.StartCoroutine(foo.TaskD(10));
	foo.Test();
	return 0;
}
#else
#include <stdio.h>
#include <ucontext.h>


static ucontext_t ctx[3];


static void
f1(char *str)
{
	puts(str);
	swapcontext(&ctx[1], &ctx[2]);
	puts("finish f1");
}


static void
f2(void)
{
	puts("start f2");
	swapcontext(&ctx[2], &ctx[1]);
	puts("finish f2");
}


class Test
{
public:
	static void Temp();
};
void Test::Temp()
{
	puts("start f2");
	swapcontext(&ctx[2], &ctx[1]);
	puts("finish f2");
}

int
main(void)
{
	char st1[8192];
	char st2[8192];


	getcontext(&ctx[1]);
	ctx[1].uc_stack.ss_sp = st1;
	ctx[1].uc_stack.ss_size = sizeof st1;
	ctx[1].uc_link = &ctx[0];
	makecontext(&ctx[1], (void(*)(void))f1, 1, "sdf");


	getcontext(&ctx[2]);
	ctx[2].uc_stack.ss_sp = st2;
	ctx[2].uc_stack.ss_size = sizeof st2;
	ctx[2].uc_link = &ctx[1];
	makecontext(&ctx[2], (void(*)(void))Test::Temp, 0);


	swapcontext(&ctx[0], &ctx[2]);
	return 0;
}


#endif