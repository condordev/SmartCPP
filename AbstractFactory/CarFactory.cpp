#include "Car.cpp"

class CarFactory {
private:
	std::unique_ptr<Car> car;
protected:
	virtual std::unique_ptr<Tire> buildTire() = 0;
	virtual std::unique_ptr<Body> buildBody() = 0;
	// much more product's parts could come here... 
public:
	virtual std::unique_ptr<Car>  buildWholeCar() = 0;
	virtual ~CarFactory() = default;
};

struct SimpleTireDeleterFunctor {
	void operator()(SimpleTire* p) {
		std::cout << "SimpleTireDeleterFunctor called" << "\n";
		//p->ReleaseElements();
		delete p;
	}
};

class SimpleCarFactory : public CarFactory {
	std::unique_ptr<Tire> buildTire() {
		std::cout << "SimpleCarFactory::buildTire called" << "\n";
		//std::unique_ptr<SimpleTire, SimpleTireDeleterFunctor> ptr(new SimpleTire(79));
		std::unique_ptr<SimpleTire> ptr = std::make_unique<SimpleTire>(79);
		return ptr;
	}

	std::unique_ptr<Body> buildBody() {
		std::cout << "SimpleCarFactory::buildBody called" << "\n";
		return std::make_unique<SimpleBody>();
	}

	std::unique_ptr<Car> buildWholeCar() {
		std::cout << "SimpleCarFactory::buildWholeCar called" << "\n";
		auto car = std::make_unique<Car>("SimpleCar");
		car->setTire(buildTire());
		car->setBody(buildBody());
		return car;
	}
};

class LuxuryCarFactory : public CarFactory {
	std::unique_ptr<Tire> buildTire() {
		return std::make_unique<LuxuryTire>();
	}

	std::unique_ptr<Body> buildBody() {
		return std::make_unique<LuxuryBody>();
	}
	std::unique_ptr<Car> buildWholeCar() {
		std::cout << "LuxuryCarFactory::buildWholeCar called" << "\n";
		auto car = std::make_unique<Car>("LuxuryCar");
		car->setTire(buildTire());
		car->setBody(buildBody());
		return car;
	}
};


/*
class CarFactory {
private:
	Car* car;
protected:
	virtual Tire* buildTire() = 0;
	virtual Body* buildBody() = 0;
	// much more product's parts could come here... 
public:
	virtual Car* buildWholeCar() = 0;
};

class SimpleCarFactory : public CarFactory {
	Tire* buildTire() {
		return new SimpleTire();
	}

	Body* buildBody() {
		return new SimpleBody();
	}

	Car* buildWholeCar() {
		Car* car = new Car("SimpleCar");
		car->setTire(buildTire());
		car->setBody(buildBody());
		return car;
	}
};

class LuxuryCarFactory : public CarFactory {
	Tire* buildTire() {
		return new LuxuryTire();
	}
	Body* buildBody() {
		return new LuxuryBody();
	}
	Car* buildWholeCar() {
		Car* car = new Car("LuxuryCar");
		car->setTire(buildTire());
		car->setBody(buildBody());
		return car;
	}
};
*/
