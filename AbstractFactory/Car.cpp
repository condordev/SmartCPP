#include <iostream>
using namespace std;

struct SimpleTireDeleterFunctor;

class Tire {
protected:
	string name;
	int presure;
public:
	Tire(string n, int presure) :name(n), presure(presure) { std::cout << "Tire c'tor called" << "\n"; };
	string getName() { return name; }
	int getPresure() { return presure; }
};

class SimpleTire : public Tire {
public:
	SimpleTire(int pr) : Tire("SimpleTire", pr) { std::cout << "SimpleTire c'tor called" << "\n"; }
};
class LuxuryTire : public Tire {
public:
	LuxuryTire() : Tire("LuxuryTire", 100) { std::cout << "LuxuryTire c'tor called" << "\n"; }
};

class Body {
protected:
	string name;
	int strength;
public:
	Body(string n, int strength) :name(n), strength(strength) { std::cout << "Body c'tor called" << "\n"; }
	string getName() { return name; }
	int getStrength() { return strength; }
};

class SimpleBody : public Body {
public:
	SimpleBody() : Body("SimpleBody", 75) { std::cout << "SimpleBody c'tor called" << "\n"; }
};
class LuxuryBody : public Body {
public:
	LuxuryBody() : Body("LuxuryBody", 100) { std::cout << "LuxuryBody c'tor called" << "\n"; }
};


class Car {
protected:
	string name;
	std::unique_ptr<Tire> tire;
	std::unique_ptr<Body> body;
public:
	Car(string n) :name(n) { tire = nullptr; body = nullptr; std::cout << "Car c'tor called" << "\n";}
	void setTire(std::unique_ptr<Tire> t) { tire = std::move(t); }
	void setBody(std::unique_ptr<Body> b) { body = std::move(b); }

	void printDetails() {
		cout << endl << "Car: " << name << endl;
		cout << "Tire: " << tire->getName() << " Presure: " << tire->getPresure() << endl;
		cout << "Body: " << body->getName() << " Strength: " << body->getStrength() << endl << endl;
	}
};

/*
class Car {
protected:
	string name;
	Tire* tire;
	Body* body;
public:
	Car(string n) :name(n) { tire = nullptr; body = nullptr; }
	void setTire(Tire* t) { tire = t; }
	void setBody(Body* b) { body = b; }

	void printDetails() {
		cout << endl << "Car: " << name << endl;
		cout << "Tire: " << tire->getName() << " Presure: " << tire->getPresure() << endl;
		cout << "Body: " << body->getName() << " Strength: " << body->getStrength() << endl << endl;
	}
};
*/