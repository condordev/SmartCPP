// Lamda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string_view>
#include <array>
#include <algorithm>

static bool containsNut(std::string_view str) {
    return ( str.find("nut") != std::string_view::npos );
}

int main()
{
    std::array<std::string_view, 2> arr{ "apple", "walnut" };
    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

    // better with lamda as anynomous function: [captureClause](parameters) -> return types {statements;}
    found = std::find_if(arr.begin(), arr.end(),
        [](std::string_view str) {
            return (str.find("nut") != std::string_view::npos);
        });

    if (found == arr.end()){  // iterator
        std::cout << "No nuts\n";
    }
    else{
        std::cout << "Found " << *found << '\n';
    }

    ////////////////// Lamda captures /////////////////////////////
    
    std::cout << "search for: ";
    std::string search{};
    std::cin >> search;

    // this wont work!! Lamda can`t see 'search'
    /*
    auto found{ std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
        // Search for @search rather than "nut".
        return (str.find(search) != std::string_view::npos); // Error: search not accessible in this scope
     }) };
    */

    // This WORKS fine with capture argument
    auto found2{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
        return (str.find(search) != std::string_view::npos);
    }) };

    if (found2 == arr.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << *found2 << '\n';
    }

    return 0;
}

