
#include <thread>
#include <Windows.h>

namespace Grf
{
	template<typename T>
	T LoadConsume(T const* addr)
	{
		T v = *const_cast<T const volatile*>(addr);
		// __memeory_barrier();
		MemoryBarrier();
		return v;
	}

	template<typename T>
	void StoreRelease(T* addr, T v)
	{
		MemoryBarrier();
		*const_cast<T volatile*>(addr) = v;
	}

	size_t const CACHE_LINE_SIZE = 64;

	template<typename T>
	class ConcurrentQueue
	{
	private:	// Struct Define
		struct Node
		{
			Node* next;
			T value;
		};

	public:


	private:
		Node* _tail;
		char _cacheLinePad[CACHE_LINE_SIZE];

		Node* _head;
		Node* _first;
		Node* _tailCopy;


	};

}