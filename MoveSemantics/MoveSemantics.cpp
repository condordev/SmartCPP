// MoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.youtube.com/watch?v=ruHw7E71zBw

#include <iostream>
#include <algorithm>
#include <vector>

//using namespace std;

class Holder {

public:
    Holder(int size) : size_(size) {
        data_ = new int[size];
    }

    Holder() = default;   // compiler creates default c'tor but not know how to init Holder

    ~Holder() { 
        delete[] data_; 
    }

    Holder(const Holder& other) {   // copy c'tor -> copy other`s data to a new instance of Holder
        std::cout << "Holder copy c'tor" << std::endl;
        this->data_ = new int[other.size_];
        std::copy(other.data_, other.data_ + other.size_, this->data_);
        this->size_ = other.size_;
    }

    Holder(Holder&& other) noexcept{  // <-- rvalue reference in input  
        std::cout << "Holder move c'tor" << std::endl;
        this->data_ = other.data_;
        this->size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;
    }

    Holder& operator=(Holder&& other)     // <-- rvalue reference in input  
    {
        std::cout << "Holder move assigment" << std::endl;
        if (this == &other) return *this;
        delete[] data_;        

        data_ = other.data_;  
        size_ = other.size_;

        other.data_ = nullptr;  
        other.size_ = 0;

        return *this;
    }

    Holder& operator = (const Holder& other) {      // copy assigment operator
        std::cout << "Holder assigmnet operator" << std::endl;
        if (this == &other) return *this;           // prevent self assigment
        delete [] this->data_;                      // clear existing object`s array
        this->data_ = new int[other.size_];         // create the array again
        std::copy(other.data_, other.data_ + other.size_, this->data_);  // copy data from other
        this->size_ = other.size_;
        return *this;
    }

    int* getDataPointer() {
        return data_;
    }

private:
    size_t size_;
    int* data_;
};

Holder createHolder(int size)
{
    return Holder(size);
}


class Widget
{
public:
    const size_t numElem = 2;

    Widget() : mPtr(new int[numElem]), mInt(0){
        std::cout << "CTOR" << std::endl; 
    }

    Widget(int a, int b) : mPtr(new int[numElem]), mInt(0) {
        mPtr[0] = a;
        mPtr[1] = b;
        std::cout << "PARAM CTOR" << std::endl; 
    }
    ~Widget() { delete mPtr; }

    // copy ctor
    Widget(const Widget& other) : mPtr(new int[numElem]), mInt(other.mInt) {
        std::cout << "COPY ctor" << std::endl;
        memcpy(mPtr, other.mPtr, sizeof(int) * numElem);
    } 

    
    // move ctor
    Widget(Widget&& other)        // rvalue reference in c++11 in the move ctor
        : mPtr(other.mPtr)        // simpy move the ownership of the memory pointer from 'other' to here
        ,mInt(other.mInt)         
    {
        other.mPtr = nullptr;     // delete ownership in 'other' 
        std::cout << "MOVE ctor" << std::endl;
    }
    
    // copy assigment operator
    Widget &operator = (const Widget& other) {
        std::cout << "COPY operator" << std::endl;
        if (this == &other) {
            return *this;
        }
        this->mInt = other.mInt;
        memcpy(mPtr, other.mPtr, sizeof(int) * numElem);
        return *this;
    }

    
    // move assigment operator
    Widget& operator = (Widget&& other) {
        std::cout << "MOVE operator" << std::endl;
        if (this == &other) {
            return *this;
        }
        mPtr = other.mPtr;
        other.mPtr = nullptr;
        return *this;
    }
    
    // needed to make Widget usable (sortable) with 'sort' in main
    bool operator < (const Widget& other) const{
        return std::less<const Widget *>()(this, &other);
    }

    int * const getPointer() { return mPtr; }
    
private:
    int* mPtr = nullptr;
    int mInt;  // primitive data can not be moved, move is only for dynamic memory management (mostly pointers)
};

int main()
{
    // ***************** First example with HOLDER *******************
    Holder h1(10000); // regular constructor
    std::cout << "create h1\n";

    Holder h2 = h1;   // copy constructor, creates new object Holder h2 from h1
    std::cout << "create h2\n";
    Holder h3(h1);    // copy constructor (alternate syntax)
    std::cout << "create h3\n";

    Holder h4(5000);      
    Holder h5(6000);
    h5 = h4;          // assignment

    std::cout << "create h6\n";
    Holder h6(2);  
    int* p = h6.getDataPointer();
    //std::cout << "h6 " << p << "\n";

    // Holder h6;   //this calls default c`tor which does not know how to create  Holder

    std::cout << "createHolder\n";
    Holder h7(1000);                // regular constructor
    Holder h8(h7);                  // copy constructor (lvalue in input)
    Holder h9 = createHolder(2000); // move constructor (rvalue in input) (not shown becuae Return Value Optimization (RVO))

    h8 = h9;                        // assignment operator (lvalue in input)
    h8 = createHolder(500);         // move assignment operator (rvalue in input)

    // Here std::move has converted the lvalue h10 into an rvalue: the compiler sees such rvalue in input and 
    // then triggers the move constructor on h11. The object h11 will steal data from h10 
    Holder h10(1000);            // h10 is an lvalue
    Holder h11(std::move(h10));  // move-constructor invoked (because of rvalue in input)

   // ***************** Second example with WIDGET *******************
    
    std::cout << "create 3 identical widget via copy\n";
    Widget a;
    Widget b(a);
    Widget c;
    c = b;

    Widget d(1, 2);
    Widget e(3, 4);
    Widget f(5, 6);
        
    std::cout << "create vector\n";
    std::vector<Widget> u;
    std::cout << "pushback\n";
    u.push_back(e);
    u.push_back(d);
    u.push_back(f);

    std::cout << "1st for loop\n";
    for (Widget var : u) {
        std::cout << "Val: " << var.getPointer()[0] << ", " << var.getPointer()[1] << std::endl;
    }

    std::sort(std::begin(u), std::end(u));

    std::cout << "2st for loop\n";
    for(Widget var : u){
        std::cout << "Val: " << var.getPointer()[0] << ", " << var.getPointer()[1] << std::endl;
    }

    /*
    std::cout << "sort do a lot of swaping which needs assigments and lot of memory during copying\n";
    std::vector<Widget> v(7);
    std::sort(std::begin(v), std::end(v));
    */
    // s2 takes (not copy) the content of s
    // move cast s to an rvalue reference and pass it to s2 (proper overload will be generated) and clears s
    std::string s = "abc"; 
    std::string s2 = std::move(s);  

    do
    {
        std::cout << '\n' << "Press ENTER key to continue...";
    } while (std::cin.get() != '\n');

    return 0;
}


