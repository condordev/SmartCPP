#include <mutex>
#include <thread>
#include <iostream>

// Our mutex
std::mutex myMutex;

// Function executed by multiple threads
void printFunc() {
	myMutex.lock();
	std::cout << "Printing from a thread!\n";

	// if you forget unlock -> you create a deadlock or imagine an exception happens in the critical section and unlock is never called
	myMutex.unlock();
}

// Function executed by multiple threads but with a lock guard
void betterPrintFunc() {

	// RAII makes sure that mutex is destroyed. Simply wraps the mutex in a c`tor -> d'tor guard
	std::lock_guard<std::mutex> g(myMutex);
	std::cout << "Printing from a thread!\n";
}

int main() {
	// Call our old-fashioned function
	std::thread t1(printFunc);
	std::thread t2(printFunc);
	t1.join();
	t2.join();

	// Call our better function using RAII
	std::thread t3(betterPrintFunc);
	std::thread t4(betterPrintFunc);
	t3.join();
	t4.join();

	return 0;
}
