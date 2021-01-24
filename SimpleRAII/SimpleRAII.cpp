// SimpleRAII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

/*
* memory allocation vs RAII
*/

struct Resource 
{
    int a;
    //Resource() { std::cout << "C'tor a = " << a; }
    ~Resource() { std::cout << "D'tor a = " << a << "\n"; }

    Resource(int val) : a(val) { std::cout << "C'tor with param val = " << val; }

    // tell the compiler to create a default c'tor. It does NOT init a
    Resource() = default;

    void setA(int v) { a = v; }
    void print() { std::cout << " a = " << this->a << "\n"; }
};

int main()
{
    std::cout << " ********* Create on stack 1 *********** " << "\n";
    //Resource res;
    Resource res(0);
    res.print();

    std::cout << " ********* Create on stack 2 *********** " << "\n";
    // Creating here we are zero-initialing struct, and assigning it to res2
    Resource res2 = Resource();
    res2.print();

    std::cout << " ********* Create on heap *********** " << "\n";
    Resource* r = new Resource;
    r->print();
    r->setA(1);
    // DO NOT FORGET DELETE. RAII better
    delete r;

    std::cout << " ********* Create unique_ptr *********** " << "\n";
    std::unique_ptr<Resource> ur(new Resource);
    ur->print();
    ur->setA(2);

    std::cout << " ********* Create make_unique *********** " << "\n";
    auto ar = std::make_unique<Resource>();
    ar->print();
    ar->setA(3);

    return 0;
}


