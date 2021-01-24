// SmartPointer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include "BigData.h"
#include <utility>

struct Player
{
    Player(std::string name) : name_(name) {};
    std::weak_ptr<Player> companion;
    ~Player() { std::cout << "~Player: " << name_ << "\n"; }
    std::string name_{};
};

std::unique_ptr<Player> getUniquePointerToManilupateIt()
{
    std::unique_ptr<Player> p = std::make_unique<Player>("Agatha");
    return p;
    // also return std::make_unique<Player>();
}

Player* const  getRawPointer()
{
    std::unique_ptr<Player> p = std::make_unique<Player>("Martha");
    return p.get();
}

int main()
{
    std::vector<std::unique_ptr<BigData>> bigdata;
    bigdata.push_back(make_unique<BigData>(100, L"Data", L"Me"));
    bigdata.push_back(make_unique<BigData>(200, L"Data1", L"Me1"));

    // Pass by const reference when possible to avoid copying.
    for (const auto& data : bigdata)
    {
        wcout << L"Number: " << data->getNumber() << L" Title: " << data->titel << L" Author: " << data->author << endl;
    }

    auto p = make_unique<BigData>(300, L"Data2", L"Me2");
    p->print();
    auto p1 = make_unique<BigDataBase>(400);
    p1->print();

    unique_ptr<BigData> p2 = std::move(p);

    p2->print();

    std::unique_ptr<Player> player = getUniquePointerToManilupateIt();
    std::cout << "Player1: " << player->name_ << "\n";

    // fails
    Player* pPlayer = getRawPointer();
    std::cout << "Player2: " << pPlayer->name_ << "\n";
 
 }


