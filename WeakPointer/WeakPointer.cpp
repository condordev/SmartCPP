// https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
//

#include <iostream>

struct Player
{
	Player(std::string name) : name_(name) {};
	std::shared_ptr<Player> companion;
	~Player() { std::cout << "~Player\n"; }
	std::string name_{};
};

struct WeakPlayer
{
	WeakPlayer(std::string name) : name_(name) {};
	std::weak_ptr<WeakPlayer> companion;
	~WeakPlayer() { std::cout << "~WeakPlayer\n"; }
	std::string name_{};
};

int main()
{
	std::weak_ptr<Player>  weak1;
	std::weak_ptr<Player>  weak2;
	{
		std::shared_ptr<Player> jasmine = std::make_shared<Player>("Jasmin");
		std::shared_ptr<Player> albert = std::make_shared<Player>("Albert");

		jasmine->companion = albert; // (1)
		albert->companion = jasmine; // (2)

		weak1 = jasmine;
		weak2 = albert;

		std::cout << "weak1.use_count() = " << weak1.use_count() << "\n";
		std::cout << "weak2.use_count() = " << weak2.use_count() << "\n";

	}
	std::cout << "block ends without calling destructor ~Player()" << "\n";

	std::cout << "weak1.use_count() = " << weak1.use_count() << "\n";
	std::cout << "weak2.use_count() = " << weak2.use_count() << "\n";


	std::cout << "Create WeakPlayer()" << "\n";
	std::weak_ptr<WeakPlayer>  weak11;
	std::weak_ptr<WeakPlayer>  weak22;
	{
		std::shared_ptr<WeakPlayer> jasmine = std::make_shared<WeakPlayer>("Jasmin");
		std::shared_ptr<WeakPlayer> albert = std::make_shared<WeakPlayer>("Albert");

		jasmine->companion = albert; // (1)
		albert->companion = jasmine; // (2)

		weak11 = jasmine;
		weak22 = albert;

		std::cout << "block ends destructor ~WeakPlayer() called" << "\n";
	}

	std::cout << "weak11.use_count() = " << weak11.use_count() << "\n";
	std::cout << "weak22.use_count() = " << weak22.use_count() << "\n";
}
