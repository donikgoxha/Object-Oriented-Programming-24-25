#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char destinacija[100];
    double osnovnaCena;
    int rastojanie;

public:
    Transport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0) {
        strcpy(this->destinacija, destinacija);
        this->osnovnaCena = osnovnaCena;
        this->rastojanie = rastojanie;
    }

    virtual ~Transport() {
    }

    virtual float cenaTransport() const {
        return osnovnaCena;
    }

    bool operator<(const Transport &t) const {
        return this->cenaTransport() < t.cenaTransport(); // Sort by cost
    }

    const char *getDestinacija() const { return destinacija; }
    int getRastojanie() const { return rastojanie; }
};

class AvtomobilTransport : public Transport {
private:
    bool shofer;

public:
    AvtomobilTransport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0,
                       bool shofer = false) : Transport(destinacija, osnovnaCena, rastojanie) {
        this->shofer = shofer;
    }

    float cenaTransport() const override {
        return shofer ? osnovnaCena * 1.2 : osnovnaCena;
    }
};

class KombeTransport : virtual public Transport {
private:
    int brLugje;

public:
    KombeTransport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0, int brLugje = 0)
        : Transport(destinacija, osnovnaCena, rastojanie) {
        this->brLugje = brLugje;
    }

    float cenaTransport() const override {
        float discount = brLugje * 200;
        return osnovnaCena > discount ? osnovnaCena - discount : 0; // Ensure non-negative price
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &T) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (*ponudi[j] < *ponudi[i]) {
                Transport *temp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (ponudi[i]->cenaTransport() > T.cenaTransport()) {
            cout << ponudi[i]->getDestinacija() << " "
                    << ponudi[i]->getRastojanie() << " "
                    << ponudi[i]->cenaTransport() << endl;
        }
    }
}

int main() {
    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {
        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);
        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }
    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
