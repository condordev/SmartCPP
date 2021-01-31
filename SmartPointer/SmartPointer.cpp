// SmartPointer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include "BigData.h"
#include <utility>

//#define BIG_DATA_EXAMPLE 1

struct Player
{
    Player(std::string name) : name_(name) { 
     //   std::cout << "Player c`tor: " << name_ << "\n"; 
    };
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

void passUniquePointerToFunction(const std::unique_ptr<Player>& player)
{
    player->name_.append(" Christie");
    (*player).name_.append(" the Lady");
    std::cout << "passUniquePointerToFunction: " << player->name_ << "\n";
}

std::unique_ptr<Player> moveUniquePointerFromFunction()
{
    std::unique_ptr<Player> p = std::make_unique<Player>("Benny");
    std::cout << "moveUniquePointerFromFunction: " << p->name_ << "\n";
    return std::move(p);
}

void addToVector (std::vector<std::unique_ptr<Player>>& vec)
{
    std::unique_ptr<Player> p = std::make_unique<Player>("BennyToVector");
    vec.push_back(std::move(p));
}

Player* const  getRawPointer()  // fails
{
    std::unique_ptr<Player> p = std::make_unique<Player>("Martha");
    return p.get();
}


int main()
{
    {
        std::unique_ptr<Player> player = getUniquePointerToManilupateIt();
        std::cout << "Player1: " << player->name_ << "\n";

        // fails Player "Martha" is destroyed before
        // Player* pPlayer = getRawPointer();
        // std::cout << "Player2: " << pPlayer->name_ << "\n";

        passUniquePointerToFunction(player);
        std::cout << "Player1: " << player->name_ << "\n";

        player = moveUniquePointerFromFunction();  // calls destructor of player: Agatha Christie the Lady
        std::cout << "Player1 new name: " << player->name_ << "\n";

        std::unique_ptr<Player> player3 = nullptr;
        {
            auto player2 = std::make_unique<Player>("Martha");
            std::cout << "Player2: " << player2->name_ << "\n";
            player3 = std::move(player2);
        }
        std::cout << "Player3: " << player3->name_ << "\n";

        Player pcopy = *player3;
        std::cout << "pcopy is copied from " << player3->name_ << " copy`s name is: " << pcopy.name_ << "\n";
    }

    std::vector<std::unique_ptr<Player>> vec(3);
    vec[0] = std::make_unique<Player>("VecPlayer1");
    vec[1] = std::make_unique<Player>("VecPlayer2");
    auto vecplayer3 = std::make_unique<Player>("VecPlayer3");
    vec[2] = std::move(vecplayer3);
    vec.push_back(std::make_unique<Player>("VecPlayer4"));

    // vector.push_back(vecplayer5); -> does not work if not moved.
    auto vecplayer5 = std::make_unique<Player>("VecPlayer5");
    vec.push_back(std::move(vecplayer5));  // move ownership to vector

    int i = 0;
    for (const auto& vp : vec) {
        std::cout << "Vector " << "at pos [" << i << "] " << vp->name_ << "\n";
        i++;
    }

    vec.pop_back();
    std::cout << "After Vector pop_back() last element is " << vec.back()->name_ << "\n";

    {
        vec[0] = std::make_unique<Player>("VecPlayer6");
        vec[1] = std::make_unique<Player>("VecPlayer7");
    }

    i = 0;
    for (const auto& vp : vec) {
        std::cout << "Vector " << "at pos [" << i << "] " << vp->name_ << "\n";
        i++;
    }

    passUniquePointerToFunction(vec[0]);
    addToVector(vec);

    i = 0;
    for (const auto& vp : vec) {
        std::cout << "Vector " << "at pos [" << i << "] " << vp->name_ << "\n";
        i++;
    }

#ifdef BIG_DATA_EXAMPLE
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
#endif // BIG_DATA_EXAMPLE
 
 }


