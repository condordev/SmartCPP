
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
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << "print1: " << vector[i] << "\n";
    }
}

template<>
void printVector(const Vector<Vector3>& vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << "print2: " << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << "\n";
    }
}

int main()
{
    Array<std::string, 2 > data;
    static_assert(data.Size() < 10, "Size is too large");
    data[0] = "Array1";
    data[1] = "Array2";
    const auto& arrayReference = data;
    std::cout << "data.size" << data.Size() << std::endl;
    std::cout << "arrayReference" << arrayReference[1] << std::endl;
    for (unsigned int i = 0;  i < data.Size(); i++) 
        data[i] = std::string("arrayno: ") += std::to_string(i);
    printArray(data[0]);

    // ******************  Vector *********************************
    Vector<std::string> vector;

    vector.pushBack("str1");
    vector.pushBack("str2");
    vector.pushBack("str3");

    printVector(vector);

    try
    {
        std::cout << "Vector[] = " << vector[2 ] << std::endl;
    }
    catch (const std::overflow_error& msg)
    {
        std::cout << "std::overflow_error: " << msg.what();
    }

    std::cout << "******************  Vector3 stuff*****************\n";

    Vector3 v0;
    //printVector3(v0);

    Vector3 v1( 1.0f, 2.0f, 3.0f );
    //printVector3(v1);

    Vector3 v2(v1);
    //printVector3(v2);

    Vector3 v3;
    v3 = v2;
    //printVector3(v3);

    std::cout << "******************  Vector c'tor*****************\n";
    Vector<Vector3> vec3;
    
    std::cout << "******************  Vector pushBack*****************\n";
    //vec3.pushBack(Vector3(1.0f));  //FIRST IMPROVEMENT this are all temporaries (r value reference)
    //vec3.pushBack(Vector3(2,3,4));
    //vec3.pushBack(Vector3());

    std::cout << "******************  Vector emplaceBack*****************\n";
    //THIRD IMPROVEMENT -> emplace back : why construct the Vector3 instances
    // instead just give ma the arguments to be created directly inside the vector (variadic template)
    vec3.emplaceBack(1.0f);  
    vec3.emplaceBack(2, 3, 4);
    vec3.emplaceBack();

    std::cout << "******************  Vector print*****************\n";
    printVector(vec3);

    std::cin.get();
    return 0;
}

 