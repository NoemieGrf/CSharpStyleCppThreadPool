
#include <stdio.h>

#include "src/example_1_thread_create.h"
#include "src/example_2_atomic_mutex.h"
#include "src/example_3_condition_variable.h"
#include "src/example_4_semaphore.h"

int main()
{
	// Example_1::Run();

	// Example_2::Run();

	// Example_3::Run();

	Example_4::Run();

	return 0;
}