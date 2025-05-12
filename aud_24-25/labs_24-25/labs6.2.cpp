#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina {
protected:
    char *adresa;
    int kvadratura;
    int cena_na_kvadrat;

    void copy(const Nedviznina &n) {
        this->adresa = new char [strlen(n.adresa) + 1];
        strcpy(this->adresa, n.adresa);
        this->kvadratura = n.kvadratura;
        this->cena_na_kvadrat = n.cena_na_kvadrat;
    }

public:
    Nedviznina(const char *adresa = "", int kvadratura = 0, int cena_na_kvadrat = 0) {
        this->adresa = new char [strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->kvadratura = kvadratura;
        this->cena_na_kvadrat = cena_na_kvadrat;
    }

    Nedviznina(const Nedviznina &n) {
        copy(n);
    }

    Nedviznina &operator=(const Nedviznina &n) {
        if (this != &n) {
            delete [] adresa;
            copy(n);
        }
        return *this;
    }

    virtual int cena() const {
        return kvadratura * cena_na_kvadrat;
    }

    virtual void pecati() const {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cena_na_kvadrat << endl;
    }

    virtual double danokNaImot() const {
        double danok = cena() * 0.05;
        return danok * 1.0;
    }

    const char *getAdresa() const {
        return adresa;
    }

    virtual ~Nedviznina() {
        delete [] adresa;
    }

    friend istream &operator>>(istream &in, Nedviznina &n) {
        char tmp[100];
        in >> tmp >> n.kvadratura >> n.cena_na_kvadrat;
        delete[] n.adresa;
        n.adresa = new char[strlen(tmp) + 1];
        strcpy(n.adresa, tmp);
        return in;
    }
};

class Vila : public Nedviznina {
private:
    int danokLuks;

public:
    Vila(const char *adresa = "", int kvadratura = 0, int cena_na_kvadrat = 0, int danokLuks = 0): Nedviznina(
        adresa, kvadratura, cena_na_kvadrat) {
        this->danokLuks = danokLuks;
    }

    double danokNaImot() const override {
        return Nedviznina::danokNaImot() + (kvadratura * cena_na_kvadrat * danokLuks) / 100.00;
    }

    void pecati() const override {
        cout << adresa << ", Kvadratura: " << kvadratura
                << ", Cena po Kvadrat: " << cena_na_kvadrat
                << ", Danok na luksuz: " << danokLuks << endl;
    }

    friend istream &operator>>(istream &is, Vila &v) {
        char tempAdresa[100];
        is >> tempAdresa >> v.kvadratura >> v.cena_na_kvadrat >> v.danokLuks;
        delete[] v.adresa;
        v.adresa = new char[strlen(tempAdresa) + 1];
        strcpy(v.adresa, tempAdresa);
        return is;
    }
};

int main() {
    Nedviznina n;
    Vila v;
    cin >> n;
    cin >> v;
    n.pecati();
    cout << "Danok za: " << n.getAdresa() << ", e: " << n.danokNaImot() << endl;
    v.pecati();
    cout << "Danok za: " << v.getAdresa() << ", e: " << v.danokNaImot() << endl;
    return 0;
}
