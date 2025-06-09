#include<iostream>
#include<string.h>
using namespace std;

class Delo {
private:
    char ime[50];
    int godina;
    char zemja[50];

public:
    Delo(const char *ime = "", int godina = 2000, const char *zemja = "") {
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->zemja, zemja);
    }

    const char *getIme() const { return ime; }
    int getGodina() const { return godina; }
    const char *getZemja() const { return zemja; }

    void setIme(const char *i) { strcpy(ime, i); }
    void setGodina(int g) { godina = g; }
    void setZemja(const char *z) { strcpy(zemja, z); }

    bool operator==(const Delo &d) const {
        return strcmp(ime, d.ime) == 0;
    }

    ~Delo() {
    }
};


class Pretstava {
protected:
    Delo delo;
    int brojProdadeni;
    char data[15];

public:
    Pretstava(const Delo &delo, int brojProdadeni, const char *data) {
        this->delo = delo;
        this->brojProdadeni = brojProdadeni;
        strcpy(this->data, data);
    }

    Delo getDelo() const { return delo; }
    int getBrojProdadeni() const { return brojProdadeni; }
    const char *getData() const { return data; }

    void setDelo(Delo delo) { this->delo = delo; }
    void setData(const char *d) { strcpy(data, d); }
    void setBrojProdadeni(int bp) { brojProdadeni = bp; }

    virtual int cena() const {
        int m = 0, n = 0;

        if (delo.getGodina() >= 1901) m = 50;
        else if (delo.getGodina() >= 1801) m = 75;
        else m = 100;

        if (strcmp(delo.getZemja(), "Italija") == 0) n = 100;
        else if (strcmp(delo.getZemja(), "Rusija") == 0) n = 150;
        else n = 80;

        return m + n;
    }
};

class Balet : public Pretstava {
protected:
    static int cenaBalet;

public:
    Balet(const Delo &delo, int brojProdadeni, const char *data): Pretstava(delo, brojProdadeni, data) {
    }

    static void setCenaBalet(int c) { cenaBalet = c; }

    int cena() const override {
        return Pretstava::cena() + cenaBalet;
    }
};


int Balet::cenaBalet = 150;

class Opera : public Pretstava {
public:
    Opera(const Delo &d, int b, const char *dat) : Pretstava(d, b, dat) {
    }
};

int prihod(Pretstava **pole, int n) {
    int vkupno = 0;
    for (int i = 0; i < n; i++) {
        vkupno += pole[i]->getBrojProdadeni() * pole[i]->cena();
    }
    return vkupno;
}

int brojPretstaviNaDelo(Pretstava **pole, int n, const Delo &d) {
    int broj = 0;
    for (int i = 0; i < n; i++) {
        if (pole[i]->getDelo() == d) {
            broj++;
        }
    }
    return broj;
}

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
        break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
        break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl;
            else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl;
            else cout << "Ne se isti" << endl;
        }
        break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
        break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
        break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
        break;
    };


    return 0;
}
