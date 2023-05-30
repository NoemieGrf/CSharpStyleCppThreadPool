#include <stdio.h>
#include <thread>

#include "example_1_thread_create.h"

namespace Example_1
{
	void ThreadJob()
	{
		printf("Message From Sub Thread\n");
	}

	void Run()
	{
		// Create From Function
		std::thread thread1(ThreadJob);

		// Create From Lambda
		std::thread thread2([] {
			ThreadJob();
			});

		thread1.join();
		thread2.join();
	}
}