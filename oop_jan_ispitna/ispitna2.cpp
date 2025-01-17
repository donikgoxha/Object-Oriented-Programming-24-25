#include <iostream>
#include <string.h>
using namespace std;
//zad2 ispitni/kolokviumski

class Vozac {
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool vet;

public:
    Vozac(char *ime = "", int vozrast = 0, int trki = 0, bool vet = false) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->trki = trki;
        this->vet = vet;
    }

    virtual float zarabotuvackaPoTrka() const = 0;

    virtual float danok() const = 0;

    friend ostream &operator<<(ostream &out, const Vozac &vozac) {
        out << vozac.ime << endl << vozac.vozrast << endl << vozac.trki << endl;
        if (vozac.vet) {
            out << "VETERAN" << endl;
            return out;
        }
    }

    bool operator==(const Vozac &v) const {
        return this->zarabotuvackaPoTrka() == v.zarabotuvackaPoTrka();
    }

    virtual ~Vozac() {
    }
};

class Avtomobilist : public Vozac {
private:
    double cena;

public:
    Avtomobilist(char *ime = "", int vozrast = 0, int trki = 0, bool vet = false, double cena = 0.0) : Vozac(
        ime, vozrast, trki, vet) {
        this->cena = cena;
    }

    float zarabotuvackaPoTrka() const override {
        return cena / 5;
    }

    float danok() const override {
        float zarabotka = zarabotuvackaPoTrka();
        if (trki > 10) {
            return zarabotka * 0.15;
        }
        return zarabotka * 0.10;
    }
};

class Motociklist : public Vozac {
private:
    int mokjnost;

public:
    Motociklist(char *ime = "", int vozrast = 0, int trki = 0, bool vet = false, int mokjnost = 0) : Vozac(
        ime, vozrast, trki, vet) {
        this->mokjnost = mokjnost;
    }

    float zarabotuvackaPoTrka() const override {
        return mokjnost * 20;
    }

    float danok() const override {
        float zarabotka = zarabotuvackaPoTrka();
        if (vet) {
            return zarabotka * 0.25;
        }
        return zarabotka * 0.20;
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *x) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (*v[i] == *x) {
            counter++;
        }
    }
    return counter;
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
