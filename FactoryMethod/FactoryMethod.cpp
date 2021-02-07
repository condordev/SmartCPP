// https://hackernoon.com/desing-patterns-exploring-factory-method-in-modern-c-hi1h3uvw

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <memory>
#include <functional>
#include <map>
#include <any>
#include <utility>
#include <string>

enum class PointType { cartesian, polar };

class Point {
public:
    friend class PointFactory;
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "x: " << p.x_ << " y: " << p.y_;
    }
    //  And this is the essence of the Factory Method i.e. private constructor & static method.
    static Point newCartesian(double x, double y) {
        return { x,y,PointType::cartesian };
    }
    static Point newPolar(double a, double b) {
        return { a * cos(b), a * sin(b), PointType::polar };
    }

    struct InnerFactory {
        static Point newCartesian(double x, double y) { std::cout << "calling "; return { x,y, PointType::cartesian }; }
        static Point newPolar(double r, double theta) { std::cout << "calling ";  return{ r * cos(theta), r * sin(theta),  PointType::polar }; }
    };

private:
    // Private constructor, so that object can't be created directly
    Point(const double x, const double y, PointType t) : x_(x), y_(y),type_(t)  {
        std::cout << "Point c'tor \n";
    }

    double x_, y_;
    PointType type_;
};

// If you have dedicated code for construction then while not we move it to a dedicated class. 
// And Just to do separation of concerns i.e. Single Responsibility Principle from SOLID design principles. 
// Mind that this is not the abstract factory this is a concrete factory. 
// Making the PointFactory friend class of Point we have violated the Open-Closed Principle(OCP). As friend keyword itself contrary to OCP
class PointFactory {
public:
    static Point newCartesian(double x, double y) {
        return { x, y, PointType::cartesian };
    }
    static Point newPolar(double r, double theta) {
        return { r * cos(theta), r * sin(theta), PointType::polar };
    }
};


enum class EPointType { Point2D, Point3D };
struct IPoint { 
    std::string s_;
    virtual ~IPoint() { std::cout << "~Point\n"; } 
};

struct Point2D : IPoint {  
    Point2D(std::string& s) {
        s_ = s;
        std::cout << "Point2D c'tor: " << s_ << "\n"; 
    } 
    ~Point2D() { 
        std::cout << "~Point2D\n"; 
    }
};
struct Point3D : IPoint { Point3D(std::string& s) { s_ = s;  std::cout << "Point3D c'tor: " << s_ << "\n"; } ~Point3D() { std::cout << "~Point3D\n"; } };

class PointFunctionalFactory {
    std::map< EPointType, std::function<std::unique_ptr<IPoint>(std::string)> > m_factories;

public:
    PointFunctionalFactory() {
      
        m_factories[EPointType::Point2D] = [](std::string s) {
           // std::cout << "Point2D Lambda: " << s << "\n";
            return std::make_unique<Point2D>(s);
        };

        m_factories[EPointType::Point3D] = [](std::string s) {   //m_factories[EPointType::Point2D] = lambda1;
           // std::cout << "Point3D Lambda: " << s << "\n";
            return std::make_unique<Point3D>(s);
        };
    }

    std::unique_ptr<IPoint> create(EPointType type, std::string name) {
        std::cout << "create called " << name << "\n";
        return m_factories[type](name);
    }
};

class PointContainerClient{

public:
    PointContainerClient(int number) : number_(number) {
        PointFunctionalFactory pf;

        for (int i = 1; i <= number_; i++) {
            std::string name{ "Point2D_" };
            name.append(std::to_string(i));
            container_.push_back(pf.create(EPointType::Point2D, name));

            std::string name1{ "Point3D_" };
            name1.append(std::to_string(i));
            container_.push_back(pf.create(EPointType::Point3D, name1));
        }
    }

    void printContainer() {
        for (auto const& p : container_) {
            std::cout << "Container " << (*p).s_ << "\n";
        }
    }
private:
    int number_;
    std::vector<std::unique_ptr<IPoint>> container_;

};

int main()
{
    auto p = Point::newPolar(5, M_PI_4);
    std::cout << p << "\n";
    auto p2 = Point::InnerFactory::newPolar(6, M_PI_4);
    std::cout << p2 << "\n";


    std::cout << "----  PointFunctionalFactory --- " << "\n";
    PointFunctionalFactory pf;
    auto p2D = pf.create(EPointType::Point2D,"point1");
    auto p3D = pf.create(EPointType::Point3D,"point2");
    auto p3D2 = pf.create(EPointType::Point3D,"point3");
    std::cout << " Created " << p2D.get()->s_ << "\n";
    std::cout << " Created " << p3D.get()->s_ << "\n";
    std::cout << " Created " << (*p3D2).s_ << "\n";

    std::cout << "----  PointContainerClient --- " << "\n";
    PointContainerClient client(5);
    client.printContainer();
}

