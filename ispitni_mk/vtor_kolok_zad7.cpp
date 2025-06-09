//
// Created by Donik Goxha on 14-Apr-25.
//
#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException {
public:
    OutOfBoundException() {
    }

    void print() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

public:
    Karticka(char *smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    virtual ~Karticka() {
    }

    virtual int tezinaProbivanje() const {
        int temp = pin;
        int digits = 0;
        while (temp > 0) {
            digits++;
            temp /= 10;
        }
        return digits;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    char *getSmetka() {
        return smetka;
    }

    friend ostream &operator<<(ostream &out, const Karticka &k) {
        out << k.smetka << ": " << k.tezinaProbivanje();
        return out;
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    int *dopolnitelniPin;
    int brojPin;
    static const int P = 4;

public:
    SpecijalnaKarticka(char *smetka, int pin) : Karticka(smetka, pin) {
        dopolnitelniPin = nullptr;
        brojPin = 0;
        povekjePin = true;
    }

    ~SpecijalnaKarticka() {
        delete[] dopolnitelniPin;
    }

    SpecijalnaKarticka &operator+=(int novPin) {
        if (brojPin >= P) {
            throw OutOfBoundException();
        }

        int *temp = new int[brojPin + 1];
        for (int i = 0; i < brojPin; i++) {
            temp[i] = dopolnitelniPin[i];
        }
        temp[brojPin] = novPin;

        delete[] dopolnitelniPin;
        dopolnitelniPin = temp;
        brojPin++;

        return *this;
    }

    int tezinaProbivanje() const override {
        return Karticka::tezinaProbivanje() + brojPin;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;

public:
    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else {
                this->karticki[i] = new Karticka(*karticki[i]);
            }
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) {
            delete karticki[i];
        }
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i] << endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if (sk != nullptr) {
                    try {
                        *sk += novPin;
                    } catch (OutOfBoundException &e) {
                        e.print();
                    }
                }
                break;
            }
        }
    }

    bool postoiKarticka(char *smetka) const {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                return true;
            }
        }
        return false;
    }

    int getBrojKarticki() const {
        return broj;
    }

    char *getNaziv() {
        return naziv;
    }
};

int Banka::LIMIT = 7;

int main() {
    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete [] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();
}
