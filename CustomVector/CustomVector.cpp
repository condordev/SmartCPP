
#include <iostream>
#include "vector.h"
#include <string>     // to use std::string, std::to_string() and "+" operator acting on strings 

template<typename T>
void printArray(T data) {
    std::cout << "printArray: " << data << "\n";
}

void printVector3(const Vector3& vector) {
    std::cout << "printVector3: " << vector.x << ", " << vector.y << ", " << vector.z << "\n";
}

template<typename T>
void printVector(const Vector<T>& vector) {
    // TO DO
//    for (const& v : vector) {
//        std::cout << v << "\n";
//    }
    std::cout << "-------  printVector T ---------\n";
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout  << vector[i] << "\n";
    }
}

template<>
void printVector(const Vector<Vector3>& vector) {
    std::cout << "-------  printVector Vector3 ---------\n";
    if (0 == vector.size()) {
        std::cout << "vector is empty\n";
    }
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << "\n";
    }
}




// int a[] = { 1, 2, 3 };
// Called with our previously defined array a will implicitly instantiate the following function:
// size_t array_size(const int (&)[3]) { return 3 }
// The key is that the template takes arrays by reference. (reference to an array of ints) 
// So using a reference is necessary when we want to know the size of the passed array.
template<typename T, size_t n>
size_t array_size(const T(&)[n]) {   // size_t array_size(const int (&)[3]) { return 3 }
    return n;
}

// C++ 11 version
template<typename T, size_t S>
constexpr auto array_size_(const T(&)[S]) -> size_t
{
    return S;
}

int main()
{
    // https://stackoverflow.com/questions/437150/can-someone-explain-this-template-code-that-gives-me-the-size-of-an-array
    int a[] = { 1, 2, 3, 4, 5 };
    int* ap = a; // a pointer, size is lost
    int(&ar)[5] = a; // a reference to the array, size is not lost
    std::cout << "Sizeof(a): " << sizeof(a) << " Number of elements in a: " << (sizeof(a) / sizeof(a[0])) << "\n";
    auto size = array_size(a);
    std::cout << "array_size(a) = " << size << "\n";
    double b[] = { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << "array_size(b) = " << array_size(b) << "\n";

    std::cout << "***************************************************\n";
    std::cout << "************** Custom Array stuff *****************\n";
    std::cout << "***************************************************\n";
    Array<std::string, 2 > data;
    static_assert(data.Size() < 10, "Size is too large");
    data[0] = "Array1";
    data[1] = "Array2";
    const auto& arrayReference = data;
    std::cout << "data.size " << data.Size() << std::endl;
    std::cout << "arrayReference " << arrayReference[1] << std::endl;
    for (unsigned int i = 0;  i < data.Size(); i++) 
        data[i] = std::string("arrayno: ") += std::to_string(i);
    printArray(data[0]);

    // ******************  Vector *********************************
    Vector<std::string> vector;

    /*
    std::string str = "sometext";
    vector.pushBack(str);
    printVector(vector);

    try
    {
        std::cout << "Vector[] = " << vector[2 ] << std::endl;
    }
    catch (const std::overflow_error& msg)
    {
        std::cout << "std::overflow_error: " << msg.what();
    }
    */
    std::cout << "***************************************************\n";
    std::cout << "******************  Vector3 stuff *****************\n";
    std::cout << "***************************************************\n";


    Vector3 v0;
    //printVector3(v0);

    Vector3 v1( 1.0f, 2.0f, 3.0f );
    //printVector3(v1);

    //Vector3 v2(v1);  // attempting to call a deleted function
    //printVector3(v2);

    Vector3 v3;
    //v3 = v2;
    //printVector3(v3);

    std::cout << "******************  Vector c'tor *****************\n";
    Vector<Vector3> vec3;
    
    //std::cout << "******************  Vector pushBack *****************\n";
    //vec3.pushBack(Vector3(1.0f));  //FIRST IMPROVEMENT this are all temporaries (r value reference)
    //vec3.pushBack(Vector3(2,3,4));
    //vec3.pushBack(Vector3());

    std::cout << "******************  Vector emplaceBack *****************\n";
    //THIRD IMPROVEMENT -> emplace back : why construct the Vector3 instances
    // instead just give ma the arguments to be created directly inside the vector (variadic template)
    vec3.emplaceBack(1.0f);  
    vec3.emplaceBack(2, 3, 4);
    vec3.emplaceBack(3, 6, 7);
    printVector(vec3);

    std::cout << "******************  Vector popBack 2 *****************\n";
    vec3.popBack();
    vec3.popBack();
    printVector(vec3);

    std::cout << "******************  Vector emplaceBack *****************\n";
    vec3.emplaceBack(4.0f);
    vec3.emplaceBack(5, 1, 4);

    std::cout << "******************  Vector clear *****************\n";
    vec3.clear();
    printVector(vec3);

    //std::cin.get();
    return 0;
}

 