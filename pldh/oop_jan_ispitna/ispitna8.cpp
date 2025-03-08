#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;
//zad10 ispitni/kolokviumski

class NegativnaVrednost {
public:
    NegativnaVrednost() {
    }
};

class Oglas {
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;

public:
    Oglas(const char *naslov = "", const char *kategorija = "", const char *opis = "", float cena = 0.0) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }

    bool operator>(const Oglas &o) {
        return cena > o.cena;
    }

    friend ostream &operator<<(ostream &out, const Oglas &o) {
        return out << o.naslov << endl << o.opis << endl << o.cena << " evra" << endl;
    }

    const char *getKategorija() {
        return kategorija;
    }

    float getCena() const {
        return cena;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *oglasi;
    int brojOglasi;

public:
    Oglasnik(const char *ime = "") {
        strcpy(this->ime, ime);
        this->brojOglasi = 0;
        this->oglasi = new Oglas[0];
    }

    ~Oglasnik() {
        delete [] oglasi;
    }

    Oglasnik &operator+=(const Oglas &o) {
        if (o.getCena() < 0) {
            throw NegativnaVrednost();
        }
        Oglas *temp = new Oglas[brojOglasi + 1];
        for (int i = 0; i < brojOglasi; i++) {
            temp[i] = oglasi[i];
        }
        temp[brojOglasi++] = o;
        delete [] oglasi;
        oglasi = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Oglasnik &o) {
        out << o.ime << endl;
        for (int i = 0; i < o.brojOglasi; i++) {
            out << o.oglasi[i] << endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < brojOglasi; i++) {
            if (strcmp(k, oglasi[i].getKategorija()) == 0) {
                cout << oglasi[i] << endl;
            }
        }
    }

    void najniskaCena() {
        if (brojOglasi == 0) return;

        int najniskaCena = 0;
        float najniska = oglasi[najniskaCena].getCena();

        for (int i = 0; i < brojOglasi; i++) {
            if (najniskaCena > oglasi[i].getCena()) {
                najniska = oglasi[i].getCena();
                najniskaCena = i;
            }
        }
        cout << oglasi[najniskaCena];
    }
};

int main() {
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);
    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost) {
                cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
            }
        }
        cout << ogl;
    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost) {
                cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    }


    return
            0;
}
