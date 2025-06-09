#include <iostream>
#include <cstring>
using namespace std;

class Koncert {
private:
    char naziv[21];
    char lokacija[21];
    float cena_na_bilet;
    static float sezonski_popust;

public:
    Koncert(const char *naziv = "", const char *lokacija = "", float cena_na_bilet = 0.0) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cena_na_bilet = cena_na_bilet;
    }

    virtual ~Koncert() {
    }

    virtual float cena() const {
        return cena_na_bilet * (1 - sezonski_popust / 100);
    }

    static void setSezonskiPopust(float popust) {
        if (popust < 1.0f) {
            sezonski_popust = popust * 100;
        } else {
            sezonski_popust = popust;
        }
    }

    static float getSezonskiPopust() {
        return sezonski_popust / 100;
    }

    const char *getNaziv() const {
        return naziv;
    }
};

float Koncert::sezonski_popust = 20.0;

class ElektronskiKoncert : public Koncert {
private:
    char *imeDJ;
    float casovi;
    bool dnevna;

    void copy(const ElektronskiKoncert &ek) {
        imeDJ = new char[strlen(ek.imeDJ) + 1];
        strcpy(imeDJ, ek.imeDJ);
        casovi = ek.casovi;
        dnevna = ek.dnevna;
    }

public:
    ElektronskiKoncert(const char *naziv = "", const char *lokacija = "", float cena_na_bilet = 0.0,
                       const char *imeDJ = "", float casovi = 0, bool dnevna = true)
        : Koncert(naziv, lokacija, cena_na_bilet) {
        this->imeDJ = new char[strlen(imeDJ) + 1];
        strcpy(this->imeDJ, imeDJ);
        this->casovi = casovi;
        this->dnevna = dnevna;
    }

    ElektronskiKoncert(const ElektronskiKoncert &ek) : Koncert(ek) {
        copy(ek);
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &ek) {
        if (this != &ek) {
            Koncert::operator=(ek);
            delete[] imeDJ;
            copy(ek);
        }
        return *this;
    }

    ~ElektronskiKoncert() {
        delete[] imeDJ;
    }

    float cena() const override {
        float finalCena = Koncert::cena();
        if (casovi > 7) finalCena += 360;
        else if (casovi > 5) finalCena += 150;
        finalCena += dnevna ? -50 : 100;
        return finalCena;
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    float maxCena = koncerti[0]->cena();
    int maxIndex = 0;
    int brojElektronski = 0;
    for (int i = 0; i < n; i++) {
        if (koncerti[i]->cena() > maxCena) {
            maxCena = koncerti[i]->cena();
            maxIndex = i;
        }
        if (dynamic_cast<ElektronskiKoncert *>(koncerti[i])) {
            brojElektronski++;
        }
    }
    cout << "Najskap koncert: " << koncerti[maxIndex]->getNaziv() << " " << maxCena << endl;
    cout << "Elektronski koncerti: " << brojElektronski << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if ((!elektronski || dynamic_cast<ElektronskiKoncert *>(koncerti[i])) &&
            strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
            cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
            found = true;
        }
    }
    return found;
}


int main() {
    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {
        //Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {
        //cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {
        //ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust " << s.
                getSezonskiPopust() << endl;
    } else if (tip == 4) {
        //cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {
        //najskapKoncert
    } else if (tip == 6) {
        //prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {
        //prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;
    } else if (tip == 8) {
        //smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
