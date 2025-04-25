#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Profil {
private:
    char ime[15];
    int br_prijateli;
    int godina_na_ragjanje;

public:
    Profil(const char *ime = "", int br_prijateli = 0, int godina_na_ragjanje = 2004) {
        strcpy(this->ime, ime);
        this->br_prijateli = br_prijateli;
        this->godina_na_ragjanje = godina_na_ragjanje;
    }

    bool operator==(Profil p) const {
        if (strcmp(ime, p.ime) == 0) {
            return true;
        }
        return false;
    }

    bool operator>(const Profil p) const {
        return godina_na_ragjanje > p.godina_na_ragjanje;
    }

    Profil operator++() {
        br_prijateli++;
        return *this;
    }

    Profil operator++(int) {
        br_prijateli++;
        return *this;
    }

    Profil &operator+=(int f) {
        br_prijateli += f;
        return *this;
    }

    Profil operator +(int m) {
        Profil tmp(ime, br_prijateli, godina_na_ragjanje);
        tmp.br_prijateli += m;
        return tmp;
    }

    // Profil operator +(int m) {
    //     Profil tmp(ime, br_prijateli + m, godina_na_ragjanje);
    //     return tmp;
    // }

    void print() {
        cout << ime << " " << godina_na_ragjanje << " " << br_prijateli << endl;
    }

    friend ostream &operator<<(ostream &out, const Profil &p) {
        out << p.ime << " " << p.godina_na_ragjanje << " " << p.br_prijateli << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Profil &p) {
        in >> p.ime >> p.godina_na_ragjanje >> p.br_prijateli;
        return in;
    }
};


int main() {
    Profil p1("Donik", 500, 2004);
    Profil p2("haha", 5000, 2020);
    p1.print();
    p2.print();

    if (p1 == p2) {
        cout << "isti se profilite" << endl;
    } else {
        cout << "ne se isti profilite" << endl;
    }

    if (p1 > p2) {
        cout << "pogolemo e p1" << endl;
    } else {
        cout << "pogolemo e p2" << endl;
    }

    ++p1;
    p1.print();

    Profil nov = ++p1;
    nov.print();

    Profil nov2 = p2++;
    nov2.print();

    p1 += 3000;
    p1.print();


    return 0;
}
