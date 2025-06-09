#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde
class Vozac {
protected:
    char name[100];
    int age;
    int numRaces;
    bool isVeteran;

    void copy(const Vozac &other) {
        strcpy(this->name, other.name);
        this->age = other.age;
        this->numRaces = other.numRaces;
        this->isVeteran = other.isVeteran;
    }

public:
    Vozac(const char *name = "", int age = 0, int numRaces = 0, bool isVeteran = false) {
        strcpy(this->name, name);
        this->age = age;
        this->numRaces = numRaces;
        this->isVeteran = isVeteran;
    }


    Vozac(const Vozac &other) {
        copy(other);
    }

    Vozac &operator=(const Vozac &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }


    virtual ~Vozac() {
    }

    virtual float zarabotuvachkaPoTrka() const = 0;

    virtual float danok() const = 0;

    friend ostream &operator<<(ostream &out, const Vozac &v) {
        out << v.name << endl << v.age << endl << v.numRaces << endl;
        if (v.isVeteran) cout << "VETERAN" << endl;
        return out;
    }

    bool operator ==(const Vozac &other) const {
        return this->zarabotuvachkaPoTrka() == other.zarabotuvachkaPoTrka();
    }
};

class Avtomobilist : public Vozac {
private:
    float autoPrice;

public:
    Avtomobilist(const char *name = "", int age = 0, int numRaces = 0, bool isVeteran = false,
                 float autoPrice = 0.0)
        : Vozac(name, age, numRaces, isVeteran) {
        this->autoPrice = autoPrice;
    }

    float zarabotuvachkaPoTrka() const override {
        return autoPrice / 5.0;
    }

    float danok() const override {
        float danok = zarabotuvachkaPoTrka();
        if (numRaces > 10) return danok * 0.15;
        else return danok * 0.10;
    }
};

class Motociklist : public Vozac {
private:
    int motorHP;

public:
    Motociklist(const char *name = "", int age = 0, int numRaces = 0, bool isVeteran = false, int motorHP = 0)
        : Vozac(name, age, numRaces, isVeteran) {
        this->motorHP = motorHP;
    }

    float zarabotuvachkaPoTrka() const override {
        return motorHP * 20.0;
    }

    float danok() const override {
        float danok = zarabotuvachkaPoTrka();
        if (isVeteran) return danok * 0.25;
        else return danok * 0.20;
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*v[i] == *vx)
            count++;
    }
    return count;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
