#include<iostream>
#include<cstring>
using namespace std;


class FudbalskaEkipa {
protected:
    char trener[100];
    int golovi[10];

public:
    FudbalskaEkipa(const char *coach, int *goals) {
        strncpy(trener, coach, 99);
        trener[99] = '\0';
        for (int i = 0; i < 10; i++) {
            golovi[i] = goals[i];
        }
    }

    virtual int uspeh() const = 0;

    friend ostream &operator<<(ostream &os, const FudbalskaEkipa &team) {
        os << team.getIme() << "\n" << team.trener << "\n" << team.uspeh() << "\n";
        return os;
    }

    virtual const char *getIme() const = 0;

    FudbalskaEkipa &operator+=(int newGoal) {
        for (int i = 0; i < 9; i++) {
            golovi[i] = golovi[i + 1];
        }
        golovi[9] = newGoal;
        return *this;
    }

    bool operator>(const FudbalskaEkipa &other) const {
        return uspeh() > other.uspeh();
    }
};

class Klub : public FudbalskaEkipa {
private:
    char ime[100];
    int tituli;

public:
    Klub(const char *coach, int *goals, const char *name, int titles)
        : FudbalskaEkipa(coach, goals) {
        strncpy(ime, name, 99);
        ime[99] = '\0';
        tituli = titles;
    }

    int uspeh() const override {
        int sumGolovi = 0;
        for (int i = 0; i < 10; i++) {
            sumGolovi += golovi[i];
        }
        return sumGolovi * 3 + tituli * 1000;
    }

    const char *getIme() const override {
        return ime;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char drzava[100];
    int nastapi;

public:
    Reprezentacija(const char *coach, int *goals, const char *country, int appearances)
        : FudbalskaEkipa(coach, goals) {
        strncpy(drzava, country, 99);
        drzava[99] = '\0';
        nastapi = appearances;
    }

    int uspeh() const override {
        int sumGolovi = 0;
        for (int i = 0; i < 10; i++) {
            sumGolovi += golovi[i];
        }
        return sumGolovi * 3 + nastapi * 50;
    }

    const char *getIme() const override {
        return drzava;
    }
};

void najdobarTrener(FudbalskaEkipa **teams, int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (*teams[i] > *teams[maxIndex]) {
            maxIndex = i;
        }
    }
    cout << *teams[maxIndex];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
