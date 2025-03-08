#include <iostream>
#include <string.h>
using namespace std;

//zad8 ispitni/kolokviumski

class Koncert {
protected:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    float cenaVoDenari;

public:
    Koncert(const char *naziv = "", const char *lokacija = "", double cenaBilet = 0.0) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cenaVoDenari = cenaBilet;
    }

    static void setSezonskiPopust(float newPopust) {
        sezonskiPopust = newPopust;
    }

    virtual double cena() {
        return cenaVoDenari * (1 - sezonskiPopust);
    }

    const char *getNaziv() const {
        return naziv;
    }

    float getSezonskiPopust() const {
        return sezonskiPopust;
    }

    virtual ~Koncert() {
    }
};

class ElektronskiKoncert : public Koncert {
private:
    char *dj;
    float vremetraenje;
    bool dnevna;

public:
    ElektronskiKoncert(const char *naziv = "", const char *lokacija = "", double cenaBilet = 0.0,
                       const char *djIme = "", float vremetraenje = 0.0, bool dnevna = true)
        : Koncert(naziv, lokacija, cenaBilet) {
        this->dj = new char[strlen(djIme) + 1];
        strcpy(this->dj, djIme);
        this->vremetraenje = vremetraenje;
        this->dnevna = dnevna;
    }

    double cena() override {
        double osnovnaCena = Koncert::cena();

        if (vremetraenje > 7) {
            osnovnaCena += 360;
        } else if (vremetraenje > 5) {
            osnovnaCena += 150;
        }

        if (dnevna) {
            osnovnaCena -= 50;
        } else {
            osnovnaCena += 100;
        }
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    double maxCena = koncerti[0]->cena();
    int maxIndex = 0;
    int elektronskiBr = 0;

    for (int i = 0; i < n; i++) {
        if (koncerti[i]->cena() > maxCena) {
            maxCena = koncerti[i]->cena();
            maxIndex = i;
        }
        if (dynamic_cast<ElektronskiKoncert *>(koncerti[i])) {
            elektronskiBr++;
        }
    }

    cout << "Najskap koncert: " << koncerti[maxIndex]->getNaziv() << " " << maxCena << endl;
    cout << "Elektronski koncerti: " << elektronskiBr << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    bool najden = false;
    for (int i = 0; i < n; i++) {
        if (elektronski) {
            ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (ek && strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                najden = true;
            }
        } else {
            if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                najden = true;
            }
        }
    }
    return najden;
}

float Koncert::sezonskiPopust = 0.2;

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
        // //smeni cena
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
