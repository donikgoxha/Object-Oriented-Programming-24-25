#include<iostream>
#include<cstring>
using namespace std;

class Patnik {
private:
    char name[100];
    int klasa;
    bool velosiped;

public:
    Patnik(const char *name = "", int klasa = 1, bool velosiped = false) {
        strcpy(this->name, name);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }

    int getKlasa() {
        return klasa;
    }

    bool imaVelosiped() const {
        return velosiped;
    }

    friend ostream &operator<<(ostream &os, const Patnik &p) {
        os << p.name << endl << p.klasa << endl << (p.velosiped ? "1" : "0") << endl;
        return os;
    }
};

// class Voz {
// private:
//     char destination[100];
//     Patnik *patnici;
//     int n;
//     int broj_velosipedi;
//
//     void copy(const Voz &v) {
//         strcpy(this->destination, v.destination);
//         this->n = v.n;
//         this->broj_velosipedi = v.broj_velosipedi;
//         this->patnici = new Patnik[n];
//         for (int i = 0; i < n; i++) {
//             this->patnici[i] = v.patnici[i];
//         }
//     }
//
// public:
//     Voz(const char *destination = "", int broj_velosipedi = 0) {
//         strcpy(this->destination, destination);
//         this->broj_velosipedi = broj_velosipedi;
//         this->n = 0;
//         this->patnici = new Patnik[0];
//     }
//
//     Voz(const Voz &v) {
//         copy(v);
//     }
//
//     Voz &operator=(const Voz &v) {
//         if (this != &v) {
//             delete [] patnici;
//             copy(v);
//         }
//         return *this;
//     }
//
//     ~Voz() {
//         delete [] patnici;
//     }
//
//     Voz &operator+=(const Patnik &p) {
//         if (p.imaVelosiped()) {
//             int brojVeloVoVoz = 0;
//             for (int i = 0; i < n; i++) {
//                 if (patnici[i].imaVelosiped()) {
//                     brojVeloVoVoz++;
//                 }
//             }
//             if (brojVeloVoVoz >= broj_velosipedi)
//                 return *this;
//         }
//
//         Patnik *tmp = new Patnik[n + 1];
//         for (int i = 0; i < n; i++)
//             tmp[i] = patnici[i];
//         tmp[n++] = p;
//         delete[] patnici;
//         patnici = tmp;
//         return *this;
//     }
//
//     friend ostream &operator<<(ostream &os, const Voz &v) {
//         os << v.destination << endl;
//         for (int i = 0; i < v.n; i++)
//             os << v.patnici[i];
//         return os;
//     }
//
//     void patniciNemaMesto() {
//         int vkupno1 = 0, vkupno2 = 0;
//         for (int i = 0; i < n; i++) {
//             if (patnici[i].imaVelosiped()) {
//                 if (patnici[i].getKlasa() == 1)
//                     vkupno1++;
//                 else
//                     vkupno2++;
//             }
//         }
//
//         int ostanato = broj_velosipedi;
//
//         int vlegle1 = (vkupno1 <= ostanato) ? vkupno1 : ostanato;
//         ostanato -= vlegle1;
//
//         int vlegle2 = (vkupno2 <= ostanato) ? vkupno2 : ostanato;
//
//         cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << (vkupno1 - vlegle1) << endl;
//         cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << (vkupno2 - vlegle2) << endl;
//     }
// };

class Voz {
private:
    char destination[100];
    Patnik *patnici;
    int n;

    Patnik *sitePatnici;
    int site_n;

    int broj_velosipedi;

    void copy(const Voz &v) {
        strcpy(this->destination, v.destination);
        this->n = v.n;
        this->site_n = v.site_n;
        this->broj_velosipedi = v.broj_velosipedi;

        this->patnici = new Patnik[n];
        for (int i = 0; i < n; i++)
            this->patnici[i] = v.patnici[i];

        this->sitePatnici = new Patnik[site_n];
        for (int i = 0; i < site_n; i++)
            this->sitePatnici[i] = v.sitePatnici[i];
    }

public:
    Voz(const char *destination = "", int broj_velosipedi = 0) {
        strcpy(this->destination, destination);
        this->broj_velosipedi = broj_velosipedi;
        this->n = 0;
        this->site_n = 0;
        this->patnici = new Patnik[0];
        this->sitePatnici = new Patnik[0];
    }

    Voz(const Voz &v) {
        copy(v);
    }

    Voz &operator=(const Voz &v) {
        if (this != &v) {
            delete[] patnici;
            delete[] sitePatnici;
            copy(v);
        }
        return *this;
    }

    ~Voz() {
        delete[] patnici;
        delete[] sitePatnici;
    }

    Voz &operator+=(const Patnik &p) {
        // зачувување на сите обиди
        Patnik *tmpAll = new Patnik[site_n + 1];
        for (int i = 0; i < site_n; i++)
            tmpAll[i] = sitePatnici[i];
        tmpAll[site_n++] = p;
        delete[] sitePatnici;
        sitePatnici = tmpAll;

        // додавање ако има место за велосипед
        if (p.imaVelosiped()) {
            int brojVeloVoVoz = 0;
            for (int i = 0; i < n; i++) {
                if (patnici[i].imaVelosiped())
                    brojVeloVoVoz++;
            }
            if (brojVeloVoVoz >= broj_velosipedi)
                return *this;
        }

        Patnik *tmp = new Patnik[n + 1];
        for (int i = 0; i < n; i++)
            tmp[i] = patnici[i];
        tmp[n++] = p;
        delete[] patnici;
        patnici = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Voz &v) {
        os << v.destination << endl;
        for (int i = 0; i < v.n; i++)
            os << v.patnici[i];
        return os;
    }

    void patniciNemaMesto() {
        int vkupno1 = 0, vkupno2 = 0;
        for (int i = 0; i < site_n; i++) {
            if (sitePatnici[i].imaVelosiped()) {
                if (sitePatnici[i].getKlasa() == 1)
                    vkupno1++;
                else
                    vkupno2++;
            }
        }

        int ostanato = broj_velosipedi;
        int vlegle1 = (vkupno1 <= ostanato) ? vkupno1 : ostanato;
        ostanato -= vlegle1;
        int vlegle2 = (vkupno2 <= ostanato) ? vkupno2 : ostanato;

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << (vkupno1 - vlegle1) << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << (vkupno2 - vlegle2) << endl;
    }
};



int main() {
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++) {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
