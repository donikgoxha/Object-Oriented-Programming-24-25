//kolokvimuska from courses zad1
#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    Pop,
    Rap,
    Rock
};

class Pesna {
private:
    char *name;
    int duration;
    tip type;

    void copy(const Pesna &p) {
        this->name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        this->duration = p.duration;
        type = p.type;
    }

public:
    //constructor
    Pesna(char *name = "", int duration = 0, tip t = Pop) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->duration = duration;
        this->type = t;
    }

    //copy constructor
    Pesna(const Pesna &p) {
        copy(p);
    }

    Pesna &operator=(const Pesna &p) {
        if (this != &p) {
            delete[]name;
            copy(p);
        }
        return *this;
    }

    ~Pesna() {
        delete[] name;
    }

    void pecati() const {
        cout << '"' << name << '"' << "-" << duration << "min" << endl;
    }

    char *getName() const {
        return name;
    }

    int getDuration() const {
        return duration;
    }

    tip getType() const {
        return type;
    }
};

class CD {
private:
    Pesna pesni[10];
    int numberOfSongs;
    int maxDuration;

public:
    CD(int maxDuration = 0) {
        this->numberOfSongs = 0;
        this->maxDuration = maxDuration;
    }

    void dodadiPesna(const Pesna &p) {
        int vkupnoVreme = 0;
        for (int i = 0; i < numberOfSongs; i++) {
            vkupnoVreme += pesni[i].getDuration();
        }

        if (numberOfSongs < 10 && (vkupnoVreme + p.getDuration() <= maxDuration)) {
            pesni[numberOfSongs++] = p;
        }
    }

    void pecatiPesniPoTip(tip t) const {
        for (int i = 0; i < numberOfSongs; i++) {
            if (pesni[i].getType() == t) {
                pesni[i].pecati();
            }
        }
    }

    void pecati() const {
        for (int i = 0; i < numberOfSongs; i++) {
            pesni[i].pecati();
        }
    }

    Pesna getPesna(int i) const {
        return pesni[i];
    }

    int getBroj() const {
        return numberOfSongs;
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
