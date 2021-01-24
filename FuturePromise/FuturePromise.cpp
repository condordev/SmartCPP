// FuturePromise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>
#include <thread>
#include <algorithm>

typedef  unsigned long int ull;

void findOdd(std::promise<ull>&& oddSumPromise, ull start, ull end ) 
{
    ull oddSum = 0;
    for(ull i = start; i <=end; ++i){
        if (i & 1) {
            oddSum += i;
        }
    }
    oddSumPromise.set_value(oddSum);
}


int main()
{
    ull start = 0, end = 1900000000;

    std::promise<ull> oddPromise;
    std::future<ull> oddFuture = oddPromise.get_future();
    
    std::thread t1(findOdd, std::move(oddPromise), start, end);
    std::cout << "Thread created." << std::endl;

    std::cout << "Waiting for result." << std::endl;
    std::cout << "Result: " << oddFuture.get() << std::endl;

    std::cout << "Completed.\n";
    t1.join();
}

