/*
Да се креира структура Engine во која што ќе се чуваат податоци за коњска сила
/ horsepower (int) и вртежен момент / torque (int).
Потоа, да се креира структура Car во која што ќе  се чуваат податоци името на
производителот (char array) , која година е произведена колата (int) и кој мотор
/ engine (Engine) која што го користи/

На почетокот се внесува број N што озналува колку коли ќе се читаат од влез.

Да се направи функцијата:
void printCars(...) која што ќе ги земе двете коли кои имаат најмала коњска сила, и од нив две,
ќе ја испечати колата што има поголем вртежен момент.
 */

#include<iostream>
using namespace std;

struct Engine {
    int horsepower;
    int torque;
};

struct Car {
    char name[100];
    int year;
    Engine engine;
};

void printCars(Car *cars, int n) {
    if (n < 2) {
        cout << "Not enough cars to compare" << endl;
    }

    int min1 = 0, min2 = 1;
    if (cars[min1].engine.horsepower > cars[min2].engine.horsepower) {
        swap(min1, min2);
    }

    for (int i = 2; i < n; i++) {
        if (cars[i].engine.horsepower < cars[min1].engine.horsepower) {
            min2 = min1;
            min1 = i;
        } else if (cars[i].engine.horsepower < cars[min2].engine.horsepower) {
            min2 = i;
        }
    }
    int index = (cars[min1].engine.torque > cars[min2].engine.torque) ? min1 : min2;
    cout << "Car with higher torque: " << cars[index].name << " " << cars[index].year << endl;
}


int main() {
    int n;
    cin >> n;
    Car cars[100];

    for (int i = 0; i < n; ++i) {
        cin >> cars[i].name >> cars[i].year >> cars[i].engine.horsepower >> cars[i].engine.torque;
    }

    printCars(cars, n);
    return 0;
}
