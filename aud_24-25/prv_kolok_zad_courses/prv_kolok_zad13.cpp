#include <iostream>
#include <cstring>
using namespace std;

//ова е место за вашиот код


class Zichara {
private:
    char *mesto;
    int dnevna_karta;

    void copy(const Zichara &z) {
        mesto = new char[strlen(z.mesto) + 1];
        strcpy(mesto, z.mesto);
        dnevna_karta = z.dnevna_karta;
    }

public:
    Zichara(const char *mesto = "", int dnevna_karta = 0) {
        this->mesto = new char [strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->dnevna_karta = dnevna_karta;
    }

    Zichara(const Zichara &z) {
        copy(z);
    }

    Zichara &operator=(const Zichara &z) {
        if (this != &z) {
            delete [] this->mesto;
            copy(z);
        }
        return *this;
    }

    int getCena() {
        return dnevna_karta;
    }

    ~Zichara() {
        delete[] mesto;
    }
};

class PlaninarskiDom {
private:
    char ime[15];
    int ceni[2];
    char klasa;
    bool daliZichara;
    Zichara *zichara;

    void copy(const PlaninarskiDom &pd) {
        strcpy(this->ime, pd.ime);
        this->ceni[0] = pd.ceni[0];
        this->ceni[1] = pd.ceni[1];
        this->klasa = pd.klasa;
        this->daliZichara = pd.daliZichara;
        if (pd.zichara) this->zichara = new Zichara(*pd.zichara);
        else this->zichara = nullptr;
    }

public:
    PlaninarskiDom(const char *ime = "", int *ceni = nullptr, char klasa = 'F') {
        strncpy(this->ime, ime, 15);
        this->klasa = klasa;
        this->daliZichara = false;
        this->zichara = nullptr;
        if (ceni) {
            this->ceni[0] = ceni[0];
            this->ceni[1] = ceni[1];
        } else {
            this->ceni[0] = this->ceni[1] = 0;
        }
    }


    PlaninarskiDom(const PlaninarskiDom &pd) {
        copy(pd);
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &pd) {
        if (this != &pd) {
            delete zichara;
            copy(pd);
        }
        return *this;
    }

    ~PlaninarskiDom() {
        delete zichara;
    }

    void setZichara(const Zichara &z) {
        if (zichara) delete zichara;
        zichara = new Zichara(z);
        daliZichara = true;
    }

    PlaninarskiDom &operator--() {
        if (klasa < 'F') klasa++;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const PlaninarskiDom &pd) {
        os << pd.ime << " klasa:" << pd.klasa;
        if (pd.daliZichara) os << " so Zichara";
        os << endl;
        return os;
    }

    bool operator<=(char c) const {
        return klasa >= c;
    }

    void presmetajDnevenPrestoj(int den, int mesec, int &cena) {
        if (mesec < 1 || mesec > 12 || den < 1 || den > 31) throw 1;
        bool eLetna = (mesec > 3 && mesec < 9);
        cena = eLetna ? ceni[0] : ceni[1];
        if (daliZichara && zichara) cena += zichara->getCena();
    }
};

int main() {
    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den, mesec;
    cin >> den >> mesec;
    try {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    } catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
}
