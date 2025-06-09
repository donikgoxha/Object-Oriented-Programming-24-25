#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
//место за вашиот код

class NegativnaVrednost {
public:
    void message() const {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cena_vo_evra;

public:
    Oglas(const char *naslov = "", const char *kategorija = "", const char *opis = "", float cena_vo_evra = 0.0) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena_vo_evra = cena_vo_evra;
    }

    bool operator >(const Oglas &o) const {
        return this->cena_vo_evra > o.cena_vo_evra;
    }

    friend ostream &operator<<(ostream &os, const Oglas &o) {
        os << o.naslov << endl;
        os << o.opis << endl;
        os << o.cena_vo_evra << " evra" << endl;
    }

    float getCena() const {
        return cena_vo_evra;
    }

    const char *getKategorija() const {
        return kategorija;
    }

    const char *getOpis() const {
        return opis;
    }

    const char *getNaslov() const {
        return naslov;
    }
};

class Oglasnik {
private:
    char ime_oglasnik[21];
    Oglas *oglasi;
    int n;

    void copy(const Oglasnik &o) {
        strcpy(ime_oglasnik, o.ime_oglasnik);
        this->n = o.n;
        this->oglasi = new Oglas[o.n];
        for (int i = 0; i < o.n; ++i) {
            this->oglasi[i] = o.oglasi[i];
        }
    }

public:
    Oglasnik(const char *ime_oglasnik = "") {
        strcpy(this->ime_oglasnik, ime_oglasnik);
        this->n = 0;
        this->oglasi = new Oglas [this->n];
    }

    Oglasnik(const Oglasnik &o) {
        copy(o);
    }

    ~Oglasnik() {
        delete [] oglasi;
    }

    Oglasnik &operator=(const Oglasnik &o) {
        if (this != &o) {
            delete [] oglasi;
            copy(o);
        }
        return *this;
    }

    Oglasnik &operator+=(const Oglas &o) {
        if (o.getCena() < 0) {
            NegativnaVrednost nv;
            nv.message();
            return *this;
        }
        Oglas *tmp = new Oglas[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = oglasi[i];
        }
        tmp[n++] = o;
        delete [] oglasi;
        oglasi = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Oglasnik &o) {
        os << o.ime_oglasnik << endl;
        for (int i = 0; i < o.n; ++i) {
            os << o.oglasi[i].getNaslov() << endl
                    << o.oglasi[i].getOpis() << endl
                    << o.oglasi[i].getCena() << " evra" << endl
                    << endl;
        }
        return os;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < n; i++) {
            if (strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout << oglasi[i] << endl;
            }
        }
    }

    void najniskaCena() {
        if (n == 0) return;
        int min = 0;
        for (int i = 0; i < n; i++) {
            if (oglasi[i].getCena() < oglasi[min].getCena()) {
                min = i;
            }
        }
        cout << oglasi[min];
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
            ogl += o;
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
            ogl += o;
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

    return 0;
}
