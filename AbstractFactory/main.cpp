
#include <iostream>
#include "CarFactory.cpp"

using namespace std;

#define SIMPLE_CAR 1
//#define LUXURY_CAR 1

int main() {

#ifdef SIMPLE_CAR
	//CarFactory* factory = new SimpleCarFactory;
	std::cout << "SimpleCarFactory called" << "\n";
    std::unique_ptr<CarFactory> factory = std::make_unique<SimpleCarFactory>();

#elif LUXURY_CAR
	CarFactory* factory = new LuxuryCarFactory;
	std::unique_ptr<CarFactory> factory = std::make_unique<LuxuryCarFactory>();

#endif

	//Car* car = factory->buildWholeCar();
	std::cout << "factory->buildWholeCar() called" << "\n";
	std::unique_ptr<Car> car = factory->buildWholeCar();
	car->printDetails();

	return 0;
}
