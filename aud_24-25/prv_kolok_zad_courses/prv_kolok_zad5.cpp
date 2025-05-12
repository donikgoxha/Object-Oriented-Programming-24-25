#include <iostream>
#include <cstring>
using namespace std;

class Gitara {
private:
    char serial[25];
    float buyprice;
    int yearOfProd;
    char type[40];

public:
    Gitara(const char *type = "", const char *serial = "", int yearOfProd = 0, float buyprice = 0.0) {
        strcpy(this->type, type);
        strcpy(this->serial, serial);
        this->yearOfProd = yearOfProd;
        this->buyprice = buyprice;
    }

    Gitara(const Gitara &other) {
        strcpy(serial, other.serial);
        strcpy(type, other.type);
        yearOfProd = other.yearOfProd;
        buyprice = other.buyprice;
    }

    Gitara &operator=(const Gitara &other) {
        if (this != &other) {
            strcpy(serial, other.serial);
            strcpy(type, other.type);
            yearOfProd = other.yearOfProd;
            buyprice = other.buyprice;
        }
        return *this;
    }

    bool daliIsti(Gitara &g) {
        return strcmp(serial, g.serial) == 0;
    }

    void pecati() {
        cout << serial << " " << type << " " << buyprice << endl;
    }

    const char *getTip() {
        return type;
    }

    const char *getSeriski() {
        return serial;
    }

    float getNabavna() {
        return buyprice;
    }

    int getGodina() {
        return yearOfProd;
    }
};

class Magacin {
private:
    char name[30];
    char location[60];
    Gitara *gitari;
    int n;
    int since;

    void copy(const Magacin &other) {
        strcpy(this->name, other.name);
        strcpy(this->location, other.location);
        this->since = other.since;
        this->n = other.n;
        this->gitari = new Gitara[n];
        for (int i = 0; i < n; i++) {
            gitari[i] = other.gitari[i];
        }
    }

public:
    Magacin(const char *name = "", const char *location = "", int since = 0) {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->since = since;
        this->n = 0;
        this->gitari = nullptr;
    }

    Magacin(const Magacin &other) {
        copy(other);
    }

    Magacin &operator=(const Magacin &other) {
        if (this != &other) {
            delete [] gitari;
            copy(other);
        }
        return *this;
    }

    ~Magacin() {
        delete [] gitari;
    }

    void dodadi(Gitara g) {
        Gitara *tmp = new Gitara [n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = gitari[i];
        }
        tmp[n++] = g;
        delete [] gitari;
        gitari = tmp;
    }

    void prodadi(Gitara p) {
        int num = 0;
        for (int i = 0; i < n; i++) {
            if (!gitari[i].daliIsti(p)) {
                num++;
            }
        }
        Gitara *tmp = new Gitara [num];
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (!gitari[i].daliIsti(p)) {
                tmp[index++] = gitari[i];
            }
        }
        delete [] gitari;
        gitari = tmp;
        n = num;
    }

    double vrednost() const {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += gitari[i].getNabavna();
        }
        return sum;
    }

    void pecati(bool daliNovi) const {
        cout << name << " " << location << endl;
        for (int i = 0; i < n; i++) {
            if (!daliNovi || gitari[i].getGodina() > since) {
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
