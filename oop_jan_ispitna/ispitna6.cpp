#include<iostream>
#include<string.h>
using namespace std;
//zad7 ispitni/kolokviumski

class OutOfBoundException {
public:
    void message() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

public:
    Karticka(const char *smetka = "", int pin = 0, bool povekjePin = false) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = povekjePin;
    }

    virtual int tezinaProbivanje() {
        int temp = pin;
        int count = 0;
        while (temp) {
            count++;
            temp /= 10;
        }
        return count;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    const char *getSmetka() {
        return smetka;
    }

    friend ostream &operator<<(ostream &os, Karticka &k) {
        os << k.smetka << ": " << k.tezinaProbivanje();
        return os;
    }

    virtual ~Karticka() {
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    static const int P = 4;
    int *dodatniPinovi;
    int brojPinovi;

public:
    SpecijalnaKarticka(char *smetka, int pin) : Karticka(smetka, pin) {
        povekjePin = true;
        brojPinovi = 0;
        dodatniPinovi = new int[P];
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &spk) : Karticka(spk.smetka, spk.pin) {
        povekjePin = spk.povekjePin;
        brojPinovi = spk.brojPinovi;
        dodatniPinovi = new int[P];
        for (int i = 0; i < brojPinovi; i++)
            dodatniPinovi[i] = spk.dodatniPinovi[i];
    }

    int tezinaProbivanje() override {
        return Karticka::tezinaProbivanje() + brojPinovi;
    }

    SpecijalnaKarticka &operator+=(int pin) {
        if (brojPinovi >= P)
            throw OutOfBoundException();
        dodatniPinovi[brojPinovi++] = pin;
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[] dodatniPinovi;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;

public:
    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

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
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0 && karticki[i]->getDopolnitelenPin()) {
                try {
                    *dynamic_cast<SpecijalnaKarticka *>(karticki[i]) += novPin;
                } catch (OutOfBoundException &e) {
                    e.message();
                }
                break;
            }
        }
    }

    ~Banka() {
        for (int i = 0; i < broj; i++)
            delete karticki[i];
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
