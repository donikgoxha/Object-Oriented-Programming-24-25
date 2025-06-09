#include <iostream>
#include <cstring>

using namespace std;

enum Type {
    Success,
    Partial,
    Failure
};

class Satellite {
private:
    char name[50];
    char operatorcountry[50];

public:
    Satellite(char *name = "", char *operatorcountry = "") {
        strcpy(this->name, name);
        strcpy(this->operatorcountry, operatorcountry);
    }

    void print() {
        cout << name << " " << "(" << operatorcountry << ")" << endl;
    }
};

class Misija {
private:
    Satellite s;
    char date[11];
    int dataTransmitted;
    Type t;

public:
    Misija(Satellite s = Satellite(), char *Satellite = "01.01.2025", int dataTransmitted = 0, Type t = Success) {
        this->s = s;
        strcpy(this->date, date);
        this->dataTransmitted = dataTransmitted;
        this->t = t;
    }

    void print() {
        cout << "Mission date: " << date << endl;
        cout << "Mission details:" << endl;
        s.print();
        cout << "Data: " << dataTransmitted << "TB" << endl;
        cout << "Type ";
        if (t == Success) {
            cout << "Success" << endl;
        }
        if (t == Partial) {
            cout << "Partial" << endl;
        }
        if (t == Failure) {
            cout << "Failure" << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore();

    char name[50];
    char country[50];
    char date[11];
    int dataTransmitted;
    int t;

    Misija misii[100];

    for (int i = 0; i < n; i++) {
        cin.getline(date, 11);
        cin.getline(name, 50);
        cin.getline(country, 50);
        cin >> dataTransmitted;
        cin >> t;
        cin.ignore();
        Satellite sc(name, country);
        misii[i] = Misija(sc, date, dataTransmitted, (Type) t);
    }
    for (int i = 0; i < n; i++) {
        misii[i].print();
        cout << endl;
    }
    return 0;
}
