#include<iostream>
#include <cstring>
using namespace std;

class Car {
private:
    string registration;
    double fuel;

public:
    Car(string registration = "SK-0001-AA", double fuel = 0.0) {
        this->registration = registration;
        this->fuel = fuel;
    }

    void refuel(double liters) {
        if (liters > 50) return;
        fuel += liters;
        if (fuel > 50) {
            fuel = 50;
        }
    }

    void print() {
        cout << registration << " - " << fuel << " - ";
        if (fuel == 0) cout << "EMPTY" << endl;
        else if (fuel < 10) cout << "LOW" << endl;
        else cout << "ENOUGH" << endl;
    }
};


int main() {
    string command;
    Car s;
    string id;
    double liters;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> liters;
            s = Car(id, liters);
        } else if (command == "constructor2") {
            cin >> id;
            s = Car(id);
        } else if (command == "refuel") {
            cin >> liters;
            s.refuel(liters);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}
