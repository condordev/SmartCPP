// SharedPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>


class Position
{
public:
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;

    Position() { x_ = 0;  y_ = 0;  z_ = 0; };
    Position(int x, int y, int z) : x_(x), y_(y), z_(z) {};
};

struct Astreoid {
    Position position_;
    int damage_ = 10;
public:
    explicit Astreoid(const int damage) : damage_(damage) { }
    std::ostream& printMe(std::ostream& os) {
        return  os << "My Damage: " << damage_ ;
    }
 };

struct Some {
    int x;
};

void useless(std::shared_ptr<Some> p) {
    //Change the underlying object
    p->x = 20;
}

void cheat(std::shared_ptr<Astreoid> p) {
    //Change the underlying object
    p->damage_ = 20000;
}

struct deleter
{
    void operator()(int* p)
    {
        delete p;
    }
};


void spam() {

    //Create/initialize shared_ptr<Some>
    auto one = std::shared_ptr<Some>(new Some());

    //Another shared_ptr<Some> pointing nowhere 
    std::shared_ptr<Some> two;

    //Change the underlying object
    one->x = 10;

    //Read through shared_ptr
    std::cout << "x: " << one->x << "\n"; //x: 10

    //Pass to a function by value. This increases the ref count.
    useless(one);

    //Underlying object is changed
    std::cout << "x: " << one->x << "\n"; //x: 20

    //Assign to another shared_ptr
    two = one;

    //'one' and 'two' are pointing to the same object
    std::cout << std::boolalpha << (one.get() == two.get()) << "\n"; //true

    /*  On Return:
    1. 'one' and 'two' are destroyed
    2.  Ref count reaches zero
    3. 'Some' is destroyed */

    auto sp = std::make_shared<std::string>("Hello");
    std::cout << *sp << "\n";

    std::vector<std::shared_ptr<Astreoid>> astreoids{
        std::make_shared<Astreoid>(5),
        std::make_shared<Astreoid>(15)
    };

    astreoids.push_back(std::make_shared<Astreoid>(20));

    for (const auto& a : astreoids) {
        a.get()->printMe(std::cout) << " Ref Count: " << a.use_count() << "\n"; //@1 Ref Count: 1;
    }

    { // block
        auto a1 = astreoids.at(0); // make a copy
        std::cout << "a1 Ref Count: " << a1.use_count() << "\n"; //@1 Ref Count: 2
        std::cout << "astreoids[0] Ref Count: " << astreoids.at(0).use_count() << "\n"; //@1 Ref Count: 2

        cheat(a1);

    }

    std::cout << "astreoids[0] Ref Count after block leaved: " << astreoids.at(0).use_count() << "\n"; //@1 Ref Count: 2
    std::cout << "astreoids[0] after cheat(a1)" << astreoids.at(0).get()->damage_ << "\n"; //@1 Ref Count: 2

    std::cout << "astreoids size" << astreoids.size() << "\n";
    std::cout << "(bool)astreoids.at(0) == " << std::boolalpha << (bool)astreoids.at(0) << std::endl;
    // astreoids.at(0).reset();
    std::cout << "(bool)astreoids.at(0) == " << std::boolalpha << (bool)astreoids.at(0) << std::endl;

    auto a2 = astreoids.at(2);
    std::cout << "astreoids.at(2)->damage_" << astreoids.at(2)->damage_ << "\n";
    astreoids.pop_back();
    std::cout << "a2 Ref Count: " << a2.use_count() << "\n"; //@1 Ref Count: 2
    //std::cout << "astreoids[2] Ref Count: " << astreoids.at(2).use_count() << "\n"; //@1 Ref Count: 2
    a2.get()->damage_;

    std::cout << "a2.get()->damage_ " << a2.get()->damage_ << "\n";
    std::cout << "astreoids size" << astreoids.size() << "\n";

    a2.reset();
    std::cout << "a2 Ref Count: " << a2.use_count() << "\n";
}

int main()
{
    spam();
}


