#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    double speed;

public:
    Vehicle(double speed = 10.0) {
        cout << "Vehicle constructor called" << endl;
        this->speed = speed;
    }

    virtual void accelerate() = 0;

    virtual void print() {
        cout << "Speed: " << speed << " km/h" << endl;
    }

    virtual ~Vehicle() = default;
};

// Trashëgimi virtuale
class Car : virtual public Vehicle {
public:
    Car(double speed = 10.0) : Vehicle(speed) {
        cout << "Car constructor called" << endl;
    }

    void accelerate() override {
        speed *= 1.05;
    }

    void print() override {
        cout << "Car: ";
        Vehicle::print();
    }
};

class Jet : virtual public Vehicle {
public:
    Jet(double speed = 10.0) : Vehicle(speed) {
        cout << "Jet constructor called" << endl;
    }

    void accelerate() override {
        speed *= 1.10;
    }

    void print() override {
        cout << "Jet: ";
        Vehicle::print();
    }
};

class JetCar : public Car, public Jet {
public:
    JetCar(double speed = 10.0) : Vehicle(speed), Car(speed), Jet(speed) {
        cout << "JetCar constructor called" << endl;
    }

    void accelerate() override {
        speed *= 1.08;
    }

    void print() override {
        cout << "JetCar: ";
        Vehicle::print();
    }
};


int main() {
    Vehicle *vehicles[3];
    vehicles[0] = new Car(100);
    vehicles[1] = new Jet(1000);
    vehicles[2] = new JetCar(500);

    for (int i = 0; i < 3; i++) {
        vehicles[i]->print();
        vehicles[i]->accelerate();
        vehicles[i]->print();
        delete vehicles[i];
    }

    return 0;
}
