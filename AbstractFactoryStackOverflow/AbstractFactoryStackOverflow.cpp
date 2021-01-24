// https://stackoverflow.com/questions/27282453/factory-pattern-using-unique-ptr-in-c



//#define FIRST_EXAMPLE 1
//#define SECOND_EXAMPLE 1
//#define THIRD_EXAMPLE 1
#define EXAMPLE4 1

#ifdef FIRST_EXAMPLE

#include <iostream>
#include <map>
class A;

class A_Factory {
public:
	A_Factory() {}
	virtual A* create() = 0;
};

class A {
public:
	A() {}
	static void registerType(int n, A_Factory* factory) {
		get_factory_instance()[n] = factory;
	}

	static A* create(int n) {
		A* A_instance = get_factory_instance()[n]->create();
		return A_instance;
	}

	virtual void setMyID(int n) {}
	virtual void I_am() { std::cout << "I am A\n"; }
	virtual ~A() {}

protected:
	int MyID;
	static std::map<int, A_Factory*>& get_factory_instance() {
		static std::map<int, A_Factory*> map_instance;
		return map_instance;
	}
};

class B : public A {
public:
	B() {}
	void Foo() {}
	void I_am() { std::cout << "I am B " << MyID << "\n"; }
	void setMyID(int n) { MyID = n; }
	~B() {}

private:
};

class B_Factory : public A_Factory {
public:
	B_Factory() { A::registerType(1, this); }
	A* create() { return new B(); }
};

static B_Factory b0_factory;

void caller() {}

int main() {
	A* b1 = A::create(1);
	A* b2 = A::create(1);
	b1->setMyID(10);
	b2->setMyID(20);
	b1->I_am();
	b2->I_am();
	delete b1;
	delete b2;

	return 0;
}

#elif SECOND_EXAMPLE
//UNIQUE POINTER VERSION 

#include <iostream>
#include <map>
#include <memory>

class A;

class A_Factory {
public:
	A_Factory() {}
	virtual std::unique_ptr<A> create_unique() = 0;
};

class A {
public:
	A() {}
	static void registerType(int n, A_Factory* factory) {
		get_factory_instance()[n] = factory;
	}
	static std::unique_ptr<A> create_unique(int n) {
		std::unique_ptr<A> A_instance = std::move(get_factory_instance()[n]->create_unique());
		return A_instance;
	}

	virtual void setMyID(int n) {}
	virtual void I_am() { std::cout << "I am A\n"; }
	virtual ~A() {}

protected:
	int MyID;
	static std::map<int, A_Factory*>& get_factory_instance() {
		static std::map<int, A_Factory*> map_instance;
		return map_instance;
	}
};

class B : public A {
public:
	B() {}
	void Foo() {}
	void I_am() { std::cout << "I am B " << MyID << "\n"; }
	void setMyID(int n) { MyID = n; }
	~B() {}

private:
};

class B_Factory : public A_Factory {
public:
	B_Factory() { A::registerType(1, this); }

	std::unique_ptr<A> create_unique() {
		std::unique_ptr<A> ptr_to_B(new B);
		return ptr_to_B;
	}
};

static B_Factory b0_factory;

void caller() {}

int main() {
	std::unique_ptr<A> b1 = std::move(A::create_unique(1));
	std::unique_ptr<A> b2 = std::move(A::create_unique(1));
	b1->setMyID(10);
	b2->setMyID(20);
	b1->I_am();
	b2->I_am();

	return 0;
}

#elif THIRD_EXAMPLE

#include <iostream>

// Abstract definitions 
class GUIComponent {
public:
	virtual ~GUIComponent() = default;
	virtual void draw() const = 0;
};
class Frame : public GUIComponent {};
class Button : public GUIComponent {};
class Label : public GUIComponent {};

class GUIFactory {
public:
	virtual ~GUIFactory() = default;
	virtual std::unique_ptr<Frame> createFrame() = 0;
	virtual std::unique_ptr<Button> createButton() = 0;
	virtual std::unique_ptr<Label> createLabel() = 0;
	static std::unique_ptr<GUIFactory> create(const std::string& type);
};

class WindowsFactory : public GUIFactory {
private:
	class WindowsFrame : public Frame {
	public:
		void draw() const override { std::cout << "I'm a Windows-like frame" << std::endl; }
	};
	class WindowsButton : public Button {
	public:
		void draw() const override { std::cout << "I'm a Windows-like button" << std::endl; }
	};
	class WindowsLabel : public Label {
	public:
		void draw() const override { std::cout << "I'm a Windows-like label" << std::endl; }
	};
public:
	std::unique_ptr<Frame> createFrame() override { return std::make_unique<WindowsFrame>(); }
	std::unique_ptr<Button> createButton() override { return std::make_unique<WindowsButton>(); }
	std::unique_ptr<Label> createLabel() override { return std::make_unique<WindowsLabel>(); }
};

class LinuxFactory : public GUIFactory {
private:
	class LinuxFrame : public Frame {
	public:
		void draw() const override { std::cout << "I'm a Linux-like frame" << std::endl; }
	};
	class LinuxButton : public Button {
	public:
		void draw() const override { std::cout << "I'm a Linux-like button" << std::endl; }
	};
	class LinuxLabel : public Label {
	public:
		void draw() const override { std::cout << "I'm a Linux-like label" << std::endl; }
	};
public:
	std::unique_ptr<Frame> createFrame() override { return std::make_unique<LinuxFrame>(); }
	std::unique_ptr<Button> createButton() override { return std::make_unique<LinuxButton>(); }
	std::unique_ptr<Label> createLabel() override { return std::make_unique<LinuxLabel>(); }
};

std::unique_ptr<GUIFactory> GUIFactory::create(const std::string& type) {
	if (type == "windows") return std::make_unique<WindowsFactory>();
	return std::make_unique<LinuxFactory>();
}

// User code 
void buildInterface(GUIFactory& factory) {
	auto frame = factory.createFrame();
	auto button = factory.createButton();
	auto label = factory.createLabel();

	frame->draw();
	button->draw();
	label->draw();
}

int main(int argc, char* argv[]) {
	if (argc < 2) return 1;
	auto guiFactory = GUIFactory::create(argv[1]);
	buildInterface(*guiFactory);
}

#elif EXAMPLE4

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

struct Data {
	int id;
	std::string name = { "Hallo" };
	void print() { std::cout << name << "\n"; }
};

class DataFactory {
public:
	static std::map<int, Data*>& getFactoryInstance() {
		static std::map<int, Data*> map_instance;
		return map_instance;
	}
};

struct SimpleDataDeleterFunctor {
	void operator()(Data* p) {
		std::cout << "SimpleDataDeleterFunctor called" << "\n";
		//p->ReleaseElements();
		delete p;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	for (auto& el : vec) {
		os << el << ' ';
	}
	return os;
}

int main()
{
	std::vector<std::string> vec = {
		"Hello", "from", "GCC" "!"
	};

	{
		auto map = DataFactory::getFactoryInstance();
		std::unique_ptr<Data, SimpleDataDeleterFunctor> ptr(new Data());

		map[0] = ptr.get();

		ptr->print();

		map.find(0)->second->print();
	}

	std::cout << vec << std::endl;
}

#endif
