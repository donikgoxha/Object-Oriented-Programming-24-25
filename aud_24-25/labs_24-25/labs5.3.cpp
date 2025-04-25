/*
Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за името на друштвото
(динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво
(цел број).
За оваа класа да се напише:
- оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од
членовите од двете друштва, а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните
атрибути од друштвото со поголем број на членови
- оператори >, < за споредба во однос на бројот на членови во планинарските друштва
- оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и го печати
планинарското друштво што има најголем број на членови.

Input
Bistra
12
75
Kozuv
15
89
Kozjak
2
15

Result
Ime: Kozuv Turi: 15 Clenovi: 164
Najmnogu clenovi ima planinarskoto drustvo: Ime: Kozuv Turi: 15 Clenovi: 89
 */
#include <iostream>
#include <cstring>
using namespace std;

class PlDrustvo {
private:
    char *name;
    int numTours;
    int members;

    void copy(const PlDrustvo &p) {
        this->name = new char [strlen(p.name) + 1];
        strcpy(this->name, p.name);
        this->numTours = p.numTours;
        this->members = p.members;
    }

public:
    PlDrustvo(const char *name = "", int numTours = 0, int members = 0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        this->numTours = numTours;
        this->members = members;
    }

    PlDrustvo(const PlDrustvo &p) {
        copy(p);
    }

    PlDrustvo &operator=(const PlDrustvo &p) {
        if (this != &p) {
            delete[] name;
            copy(p);
        }
        return *this;
    }

    ~PlDrustvo() {
        delete[] name;
    }

    PlDrustvo operator+(const PlDrustvo &p) {
        if (members >= p.members) return PlDrustvo(name, numTours, members + p.members);
        else return PlDrustvo(p.name, p.numTours, members + p.members);
    }

    bool operator>(const PlDrustvo &p) {
        return members > p.members;
    }

    bool operator<(const PlDrustvo &p) {
        return members < p.members;
    }

    friend ostream &operator<<(ostream &o, const PlDrustvo &p) {
        o << "Ime: " << p.name << " Turi: " << p.numTours << " Clenovi: " << p.members << endl;
        return o;
    }

    int getMembers() const {
        return members;
    }
};

void najmnoguClenovi(PlDrustvo *d, int n) {
    PlDrustvo max = d[0];
    for (int i = 1; i < n; i++) {
        if (d[i] > max) {
            max = d[i];
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << max << endl;
}


int main() {
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i = 0; i < 3; i++) {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin >> ime;
        cin >> brTuri;
        cin >> brClenovi;
        PlDrustvo p(ime, brTuri, brClenovi);
        drustva[i] = p;
    }

    pl = drustva[0] + drustva[1];
    cout << pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
