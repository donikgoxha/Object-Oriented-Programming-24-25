/*
За еден автомобил (објект од класата Car) се чуваат следниве податоци:
сопственик (објект од класата Person)
датум на купување (објект од класата Date)
цена (float price), предодредена вредност 0
За класата Car потребно е да се напише метод за печатење print() и метод за добивање на цената getPrice().

Класата Date содржи три цели броеви (int year, month, day) кои претставуваат датум.
За неа треба да се напише метод за печатење print(), предодреден (default) конструктор, конструктор со
параметри и конструктор за копирање.

Класата Person содржи име и презиме (низи од максимум 20 знаци, со предодредени вредности not specified),
предодреден конструктор, конструктор со параметри и метод за печатење print().
Методот за печатење кај класата Person изгледа вака: [name] [lastName].
Методот за печатење кај класата Date изгледа вака: [year].[month].[day].
Методот за печатење кај класата Car изгледа вака:
owner.print()
date.print()
Price: [price]
Покрај тоа, потребно е да се напише метод cheaperThan(Car* cars, int numCars, float price) кој ќе ги
испечати сите објекти Car од низата cars со големина numCars чија цена е помала од price.
 */

#include<iostream>
#include <string.h>
using namespace std;

class Date {
private:
    int year, month, day;

    void copy(const Date &d) {
        this->year = d.year;
        this->month = d.month;
        this->day = d.day;
    }

public:
    Date(int year = 2000, int month = 1, int day = 1) {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    Date(const Date &d) {
        copy(d);
    }

    void print() {
        cout << year << "." << month << "." << day << endl;
    }
};

class Person {
    char name[20];
    char surname[20];

public:
    Person(const char *name = "not specified", const char *surname = "not specified") {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    void print() {
        cout << name << " " << surname << endl;
    }
};

class Car {
    Person person;
    Date date;
    float price;

public:
    Car(Person person = Person(), Date date = Date(), float price = 0) {
        this->person = person;
        this->date = date;
        this->price = price;
    }

    void print() {
        person.print();
        date.print();
        cout << "Price: " << price << endl;
    }

    float getPrice() const {
        return price;
    }

    void cheaperThan(Car *cars, int numCars, float price) {
        for (int i = 0; i < numCars; i++) {
            if (cars[i].getPrice() < price) {
                cars[i].print();
            }
        }
    }
};


int main() {
    //GIVEN MAIN
    return 0;
}
