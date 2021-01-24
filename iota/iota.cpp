// iota.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

struct Generator {
    static int counter;
    Generator(int i) : state_(i) {
        std::cout << state_; 
        counter++;
    }
    int state_;
    void operator++() { state_ += state_; }

    // operator TypeName() are conversion operators. (line 32)
    // They allow objects of the class type (here Generator) to be used as if they were of type TypeName 
    operator int() { return state_; }
};

int Generator::counter = 0;
int main()
{
    // ostream_iterator ist ein Output-Iterator (write), der bei jedem Schreibzugriff den erhaltenen Wert auf den im Konstruktor 
    // übergebenen Ausgabe-Stream schreibt und optional noch einen – ebenfalls im Konstruktor übergebenen – Separator anhängt.
    std::ostream_iterator<int> os{ std::cout, " " };

    std::vector<int> data(7);
    std::iota(data.begin(), data.end(), Generator{ 2 });
    std::cout << "C'tor called " << Generator::counter << "\n";
    std::copy(data.begin(), data.end(), os);
    std::cout << "\n";

    std::vector< int > array(14,1);
    std::copy(array.begin(), array.end(), os);
    std::fill_n(os, 5, 7);
    std::cout << "\n";


    int numbers[] = { 9,9,9,9,9,9,9 };
    std::iota(numbers, numbers + 5, 2);
    std::cout << "numbers are :";
    for (int& i : numbers) std::cout << ' ' << i;
    std::cout << '\n';

    std::vector<int> data1{ 9,9,9,9,9};
    for (size_t i = 3; i < std::distance(data1.begin(), data1.end()); i++) { 
        data1.begin()[i] = i; 
    }
    std::copy(data1.begin(), data1.end(), os);
    std::cout << "\n";


    
 }

/*
* <strong>// Definition of std::copy()</strong>
template
OutputIterator copy(InputIterator first, InputIterator last,
					OutputIterator result) 
{
	while (first != last) 
	*result++ = *first++;
	return result;
}

*/

