#include <stdio.h>
#include <thread>

#include "example_1_thread_create.h"

namespace Example_1
{
	class TestClass
	{
	public:
		int a;
		int b;
		int c;

	public:
		TestClass(int a_, int b_, int c_)
			: a(a_)
			, b(b_)
			, c(c_)
		{
		}

		void PrintValue() const
		{
			printf("TestClass Value: %d, %d, %d\n", a, b, c);
		}
	};

	void VoidThreadJob()
	{
		printf("Message From Thread\n");
	}

	void ParameterThreadJob(int id, size_t n)
	{
		for (auto i = 0; i < n; i++)
			printf("Message From Thread %d: %d\n", id, i);
	}

	void ReferenceParameterThreadJob(TestClass& testCalss, const TestClass& constTestClass)
	{
		testCalss.a = 3;
		testCalss.b = 2;
		testCalss.c = 1;
		testCalss.PrintValue();
		constTestClass.PrintValue();
	}

	void VoidThreadCreate()
	{
		printf("Void Thread Create: \n");

		// Create From Function
		std::thread voidThread1(VoidThreadJob);

		// Create From Lambda
		std::thread voidThread2([] {
			VoidThreadJob();
			});

		voidThread1.join();
		voidThread2.join();

		printf("\n");
	}

	void ParameterThreadCreate()
	{
		printf("Parameter Thread Create: \n");

		std::thread parameterThread1(ParameterThreadJob, 1, 5);
		std::thread parameterThread2(ParameterThreadJob, 2, 5);
		std::thread parameterThread3(ParameterThreadJob, 3, 5);
		std::thread parameterThread4(ParameterThreadJob, 4, 5);
		std::thread parameterThread5(ParameterThreadJob, 5, 5);

		parameterThread1.join();
		parameterThread2.join();
		parameterThread3.join();
		parameterThread4.join();
		parameterThread5.join();

		printf("\n");
	}

	void ReferenceParameterThreadCreate()
	{
		printf("Reference Parameter Thread Create: \n");

		TestClass testCalss(1, 2, 3);
		testCalss.PrintValue();

		TestClass testCalssConst(5, 6, 7);
		testCalssConst.PrintValue();

		std::thread referenceParameterThread(
			ReferenceParameterThreadJob,
			std::ref(testCalss),
			std::cref(testCalssConst));

		referenceParameterThread.join();
	}

	void Run()
	{
		VoidThreadCreate();
		ParameterThreadCreate();
		ReferenceParameterThreadCreate();

		// thread��join����detach�Ļ���������ʱ����쳣
	}
}