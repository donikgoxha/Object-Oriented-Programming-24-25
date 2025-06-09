// Потребно е да креирате систем за членство во една теретана. За таа цел, најпрво ќе креирате една класа Membership со информации за:
//
// име на членот - низа од максимум 50 знаци
// ден на зачленување - низа од максимум 11 знаци (2025-05-05)
// месечна членарина - цел број
// За основната класа треба да креирате:
//
// Default конструктор
// Конструктор со параметри
// Copy конструктор
// Оператор =
// Функција која ќе ја враќа вредноста на месечната членарина (getMonthlyFee)
// Функција print што ги печати информациите за членот во формат:
// [име и презиме] - [датум на зачленување]
//
//
// Понатаму потребно е да развиете две класи: BasicMembership и VIPMembership
//
// Класата BasicMembership треба да содржи информација isMorningMembership - boolean вредност за тоа дали членот смее да вежба само до 15:00.
//
//
//
// За оваа класа потребно е да креирате:
//
// Default конструктор
// Конструктор со параметри
// Функција што ќе ја враќа вредноста на месечната членарина (getMonthlyFee), пресметана така што доколку членот смее да вежба само до 15:00, добива 25% попуст на основната месечна членарина. Пример: Доколку месечната членарина е 2000 денари и членот вежба само наутро, оваа функција ќе врати вредност 1500 денари (2000-0.25*2000 = 1500), инаку се добива стандардната висина на месечната членарина.
// Функција print што ги печати информациите за членот во формат:
// [име и презиме] - [датум на зачленување] - [месечна членарина] - [вежба до 15:00 - yes/no]
//
//
// Вашата теретана е многу модерна и има спа која е пристаплива само за VIP членовите. Класата VIPMembership треба да содржи информации за:
// дали членот го користи спа просторот - boolean вредност
// колку часа членот вежбал со тренер - цел број
// За оваа класа потребно е да креирате:
//
// Default конструктор
// Конструктор со параметри
// Функција што ќе ја враќа вредноста на месечната членарина (getMonthlyFee), пресметана така што доколку членот го користи спа просторот, висината се зголемува за 1000 денари. Во пресметката се додава и бројот на часови со тренер. Цена на еден час е 150 денари. Пример: Основната членарина е 2000 денари. Членот го користи спа просторот и вежбал 10 часа со тренер: 2000 + 1000 + 10*150 = 4500 денари.
// Функција print што ги печати информациите за членот во формат:
// [име и презиме] - [датум на зачленување] - [месечна членарина] - [користи спа - yes/no] - [вкупна сума платена за тренер]
//
// Input
// 2
// John
// 2025-01-01
// 2000
// 1 10
// Mark
// 2025-03-06
// 1400
// 1
// Result
// John - 2025-01-01 - 4500 - yes - 1500
// Mark - 2025-03-06 - 1050 - yes
#include <iostream>
#include <cstring>
using namespace std;

class Membership {
private:
    char name[100];
    char entryDate[11];
    int price;

    void copy(const Membership &m) {
        strcpy(this->name, m.name);
        strcpy(this->entryDate, m.entryDate);
        this->price = m.price;
    }

public:
    Membership(const char *name = "", const char *entryDate = "", int price = 0) {
        strcpy(this->name, name);
        strcpy(this->entryDate, entryDate);
        this->price = price;
    }

    Membership(const Membership &m) {
        copy(m);
    }

    Membership &operator=(const Membership &m) {
        if (this != &m) {
            copy(m);
        }
        return *this;
    }

    virtual int getMonthlyFee() const {
        return price;
    }

    virtual void print() const {
        cout << name << " - " << entryDate << endl;
    }
};

class BasicMembership : public Membership {
private:
    bool isMorningMembership;

public:
    BasicMembership(const char *name = "", const char *entryDate = "", int price = 0,
                    bool isMorningMembership = false) : Membership(name, entryDate, price) {
        this->isMorningMembership = isMorningMembership;
    }

    BasicMembership(const Membership &m, bool isMorningMembership = false)
        : Membership(m) {
        this->isMorningMembership = isMorningMembership;
    }

    int getMonthlyFee() const override {
        if (isMorningMembership) {
            return Membership::getMonthlyFee() * 0.75;
        }
        return Membership::getMonthlyFee();
    }

    void print() const override {
        Membership::print();
        cout << " - " << getMonthlyFee()
                << " - " << (isMorningMembership ? "yes" : "no") << endl;
    }
};


class VIPMembership : public Membership {
private:
    bool isUsingSPA;
    int trainerHours;

public:
    VIPMembership(const char *name = "", const char *entryDate = "", int price = 0, bool isUsingSPA = false,
                  int trainerHours = 0): Membership(name, entryDate, price) {
        this->isUsingSPA = isUsingSPA;
        this->trainerHours = trainerHours;
    }

    VIPMembership(const Membership &m, bool isUsingSPA = false, int trainerHours = 0) : Membership(m) {
        this->isUsingSPA = isUsingSPA;
        this->trainerHours = trainerHours;
    }

    int getMonthlyFee() const override {
        int total = Membership::getMonthlyFee();
        if (isUsingSPA) {
            total += 1000;
        }
        total += trainerHours * 150;
        return total;
    }

    void print() const override {
        Membership::print();
        cout << " - " << getMonthlyFee()
                << " - " << (isUsingSPA ? "yes" : "no")
                << " - " << (trainerHours * 150) << endl;
    }
};

int main() {
    int n;
    cin >> n;
    char name[50];
    char dateJoined[11];
    int membershipPrice;

    for (int i = 0; i < n; i++) {
        cin >> name;
        cin >> dateJoined;
        cin >> membershipPrice;

        Membership m = Membership(name, dateJoined, membershipPrice);

        if (i % 2) {
            bool isMorningMembership;
            cin >> isMorningMembership;
            BasicMembership bm = BasicMembership(m, isMorningMembership);
            bm.print();
        } else {
            bool usesSpa;
            int numOfHoursWithTrainer;
            cin >> usesSpa >> numOfHoursWithTrainer;
            VIPMembership vm = VIPMembership(m, usesSpa, numOfHoursWithTrainer);
            vm.print();
        }
    }

    return 0;
}
