
#include <stdio.h>
#include <Windows.h>
#include <functional>
#include <stdio.h>

#include "src/concurrent_queue.hpp"

void TestLockConcurrentQueue()
{
	Grf::LockConcurrentQueue<int> q {};

	bool producerFinishWork = false;

	auto producerFunc = [&q](int id)
	{
		for (int i = 0; i < 100; i++)
		{
			q.Enqueue(i);
			printf("Producer %d: %d\n", id, i);
			std::this_thread::sleep_for(std::chrono::microseconds(10 * id));
		}
	};
	
	auto consumerFunc = [&q, &producerFinishWork](int id)
	{
		while (true)
		{
			if (q.Empty())
			{
				if (producerFinishWork)
					break;

				std::this_thread::sleep_for(std::chrono::microseconds(5));
			}
			else
			{
				int result = 0;
				int* pResult = &result;
				if (q.TryDequeue(pResult))
					printf("Consumer %d: %d\n", id, result);
				else
					std::this_thread::sleep_for(std::chrono::microseconds(5));
			}
		}
	};

	std::thread theadProducer1 {[producerFunc]{producerFunc(1);}};
	std::thread theadProducer2 {[producerFunc]{producerFunc(2);}};
	std::thread theadProducer3 {[producerFunc]{producerFunc(3);}};

	std::thread theadConsumer1 {[consumerFunc] { return consumerFunc(1); }};
	std::thread theadConsumer2 {[consumerFunc] { return consumerFunc(2); }};

	theadProducer1.join();
	theadProducer2.join();
	theadProducer3.join();

	producerFinishWork = true;

	theadConsumer1.join();
	theadConsumer2.join();
}

void TestCasConcurrentQueue()
{
	Grf::CasConcurrentQueue<int> q {};

	bool producerFinishWork = false;

	auto producerFunc = [&q](int id)
	{
		for (int i = 0; i < 100; i++)
		{
			q.Enqueue(i);
			printf("Producer %d: %d\n", id, i);
			std::this_thread::sleep_for(std::chrono::microseconds(10 * id));
		}
	};
	
	auto consumerFunc = [&q, &producerFinishWork](int id)
	{
		while (true)
		{
			if (q.Empty())
			{
				if (producerFinishWork)
					break;

				std::this_thread::sleep_for(std::chrono::microseconds(5));
			}
			else
			{
				int result = 0;
				int* pResult = &result;
				if (q.TryDequeue(pResult))
					printf("Consumer %d: %d\n", id, result);
				else
					std::this_thread::sleep_for(std::chrono::microseconds(5));
			}
		}
	};

	std::thread theadProducer1 {[producerFunc]{producerFunc(1);}};
	std::thread theadProducer2 {[producerFunc]{producerFunc(2);}};
	std::thread theadProducer3 {[producerFunc]{producerFunc(3);}};

	std::thread theadConsumer1 {[consumerFunc] { return consumerFunc(1); }};
	std::thread theadConsumer2 {[consumerFunc] { return consumerFunc(2); }};

	theadProducer1.join();
	theadProducer2.join();
	theadProducer3.join();

	producerFinishWork = true;

	theadConsumer1.join();
	theadConsumer2.join();
}

int main()
{
	TestLockConcurrentQueue();

	system("pause");

	return 0;
}