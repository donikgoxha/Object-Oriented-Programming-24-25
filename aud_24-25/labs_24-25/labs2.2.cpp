/*
Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:
модел (низа од карактери не подолга од 20 карактери)
број на модел (цел број)
година на издавање (цел број)
За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор,
деструктор и доколку има потреба get методи. Исто така да се дефинира и фунцкија за печатење на
информации за класата која ќе печати во следниот формат
„(модел) (број на модел) release year: (година на издавање)“.
Потоа да се дефинира класа Owner во која се чуваат следните информации:
име (низа од карактери не подолга од 20 карактери)
презиме (низа од карактери не подолга од 20 карактери)
мобилен телефон (објект од класа MobilePhone)
Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба
get методи. Исто така да се дефинира и функција за печатење на информации за класата која ќе печати
во следниот формат:
„(име) (презиме) has a mobile phone: (информации за мобилен телефон)“
 */

#include<iostream>
#include <string.h>
using namespace std;

class MobilePhone {
private:
    char model[20];
    int numModel;
    int prodYear;

    void copy(const MobilePhone &other) {
        strcpy(model, other.model);
        numModel = other.numModel;
        prodYear = other.prodYear;
    }

public:
    MobilePhone(const char *model = "iPhone", int numModel = 111111, int prodYear = 2025) {
        strcpy(this->model, model);
        this->numModel = numModel;
        this->prodYear = prodYear;
    }

    MobilePhone(const MobilePhone &mp) {
        strcpy(this->model, mp.model);
        this->numModel = mp.numModel;
        this->prodYear = mp.prodYear;
    }

    ~MobilePhone() = default;

    void print() {
        cout << model << " " << numModel << " " << "Release year: " << prodYear << endl;
    }
};

class Owner {
    char name[20];
    char surname[20];
    MobilePhone mobile;

public:
    Owner(const char *name = "default", const char *surname = "default", MobilePhone mobile = MobilePhone()) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->mobile = mobile;
    }

    ~Owner() = default;

    void print() {
        cout << name << " " << surname << " has mobile phone: " << endl;
        mobile.print();
    }
};

int main() {
    //GIVEN MAIN
    return 0;
}
