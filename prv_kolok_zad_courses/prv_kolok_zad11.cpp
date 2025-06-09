#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
    char *name;
    bool male; //true = male ,false = female
    int age;

    void copy(const Ucesnik &other) {
        this->name = new char [strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->male = other.male;
        this->age = other.age;
    }

public:
    Ucesnik(const char *name = "", bool male = false, int age = 0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        this->male = male;
        this->age = age;
    }

    Ucesnik(const Ucesnik &u) {
        copy(u);
    }

    Ucesnik &operator=(const Ucesnik &u) {
        if (this != &u) {
            delete [] name;
            copy(u);
        }
        return *this;
    }

    ~Ucesnik() {
        delete [] name;
    }

    bool operator>(const Ucesnik &u) const {
        return age > u.age;
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &u) {
        out << u.name << endl << (u.male ? "mashki" : "zhenski") << endl << u.age << endl;
        return out;
    }

    int getVozrast() {
        return age;
    }
};


class Maraton {
    char lokacija[100];
    Ucesnik *ucesnici;
    int n;

public:
    Maraton(const char *lokacija = "") {
        strcpy(this->lokacija, lokacija);
        this->n = 0;
        this->ucesnici = nullptr;
    }

    Maraton(const Maraton &m) {
        strcpy(this->lokacija, m.lokacija);
        this->n = m.n;
        this->ucesnici = new Ucesnik[n];
        for (int i = 0; i < n; ++i) {
            this->ucesnici[i] = m.ucesnici[i];
        }
    }

    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            delete [] ucesnici;
            strcpy(this->lokacija, m.lokacija);
            this->n = m.n;
            this->ucesnici = new Ucesnik[n];
            for (int i = 0; i < n; ++i) {
                this->ucesnici[i] = m.ucesnici[i];
            }
        }
        return *this;
    }

    ~Maraton() {
        delete [] ucesnici;
    }

    Maraton &operator +=(const Ucesnik &u) {
        Ucesnik *tmp = new Ucesnik [n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = this->ucesnici[i];
        }
        tmp[n++] = u;
        delete [] ucesnici;
        ucesnici = tmp;
        return *this;
    }

    double prosecnoVozrast() {
        if (n == 0) {
            return 0;
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += this->ucesnici[i].getVozrast();
        }
        return (double) sum / n;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < n; ++i) {
            if (ucesnici[i].getVozrast() < u.getVozrast()) {
                cout << ucesnici[i];
            }
        }
    }
};


// vashiot kod ovde

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
