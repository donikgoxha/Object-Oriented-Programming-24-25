#include <iostream>
#include <cstring>
using namespace std;

enum tip { POP, RAP, ROK };

class Pesna {
private:
    char *name;
    int duration;
    tip type;

    void copy(const Pesna &p) {
        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);
        duration = p.duration;
        type = p.type;
    }

public:
    Pesna(const char *name = "", int duration = 0, tip type = POP) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->duration = duration;
        this->type = type;
    }

    Pesna(const Pesna &other) {
        copy(other);
    }

    void pecati() {
        cout << "\"" << name << "\"-" << duration << "min" << endl;
    }

    ~Pesna() {
        delete [] name;
    }

    Pesna &operator=(const Pesna &other) {
        if (this != &other) {
            delete [] name;
            copy(other);
        }
        return *this;
    }

    int getDuration() {
        return duration;
    }

    tip getType() {
        return type;
    }
};

class CD {
private:
    Pesna pesni[10];
    int n;
    int CDduration;

public:
    CD(int CDduration = 60) {
        this->CDduration = CDduration;
        n = 0;
    }

    void dodadiPesna(Pesna p) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += pesni[i].getDuration();
        }
        if (n < 10 && (total + p.getDuration() <= CDduration)) {
            pesni[n++] = p;
        }
    }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < n; i++) {
            if (pesni[i].getType() == t) {
                pesni[i].pecati();
            }
        }
    }

    int getBroj() {
        return n;
    }

    Pesna getPesna(int i) {
        return pesni[i];
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);
    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);
    }

    return 0;
}
