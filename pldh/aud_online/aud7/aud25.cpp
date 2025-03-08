// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av9.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1651668005815
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Vehicle {
protected:
    int acceleration;

public:
    Vehicle() {
        acceleration = 0;
        cout << "Vehicle constructor" << endl;
    }

    virtual void accelerate() {
        cout << "Vehicle accelerate" << endl;
        acceleration++;
    }

    virtual ~Vehicle() {
        // Made destructor virtual
        cout << "Vehicle destructor" << endl;
    }

    int getAcceleration() const {
        // Added const
        return acceleration;
    }
};

class Car : virtual public Vehicle {
public:
    Car() {
        cout << "Car constructor" << endl;
    }

    void accelerate() override {
        // Added override keyword
        cout << "Car accelerate" << endl;
        acceleration += 2; // Direct modification instead of calling parent twice
    }

    virtual void drive() {
        cout << "Car is driving" << endl;
    }

    virtual ~Car() override {
        // Added virtual and override
        cout << "Car destructor" << endl;
    }
};

class Jet : virtual public Vehicle {
public:
    Jet() {
        cout << "Jet constructor" << endl;
    }

    void accelerate() override {
        // Added override keyword
        cout << "Jet accelerate" << endl;
        acceleration += 50;
    }

    virtual void fly() {
        cout << "Jet is flying" << endl;
    }

    virtual ~Jet() override {
        // Added virtual and override
        cout << "Jet destructor" << endl;
    }
};

class JetCar : public Jet, public Car {
public:
    JetCar() {
        cout << "Jet car constructor" << endl;
    }

    void accelerate() override {
        // Added missing accelerate override
        cout << "JetCar accelerate" << endl;
        acceleration += 25; // Custom acceleration for JetCar
    }

    void drive() override {
        cout << "JetCar is driving" << endl; // Fixed text
    }

    void fly() override {
        cout << "JetCar is flying" << endl; // Fixed text
    }

    ~JetCar() override {
        cout << "Jet car destructor" << endl;
    }
};

int main() {
    JetCar jetcar;
    jetcar.fly();
    jetcar.drive();
    jetcar.accelerate();
    cout << jetcar.getAcceleration() << endl;

    return 0;
}
