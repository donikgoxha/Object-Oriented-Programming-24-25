#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

enum tip { Mobilen, Laptop };

class InvalidProductionDate {
public:
    void print() const {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
private:
    char model[101];
    tip type;
    int godina;
    static float chasovi;

public:
    Device(const char *model = "", tip type = Mobilen, int godina = 0) {
        strcpy(this->model, model);
        this->type = type;
        this->godina = godina;
    }

    static void setPocetniCasovi(float ch) {
        chasovi = ch;
    }

    float presmetajChasovi() const {
        float vk = chasovi;
        if (godina > 2015) {
            vk += 1.5;
        }
        if (type == Laptop) {
            vk += 2;
        }
        return vk;
    }

    friend ostream &operator<<(ostream &os, const Device &d) {
        os << d.model << endl;
        os << (d.type == Mobilen ? "Mobilen" : "Laptop") << " " << (int) round
                (d.presmetajChasovi()) << endl;
        return os;
    }

    int getGodina() const {
        return godina;
    }

    const char *getModel() const {
        return model;
    }

    tip getTip() const {
        return type;
    }
};

float Device::chasovi = 1;

class MobileServis {
private:
    char adresa[101];
    Device *uredi;
    int n;

    void copy(const MobileServis &ms) {
        strcpy(adresa, ms.adresa);
        n = ms.n;
        uredi = new Device[n];
        for (int i = 0; i < n; i++) {
            uredi[i] = ms.uredi[i];
        }
    }

public:
    MobileServis(const char *adresa = "") {
        strcpy(this->adresa, adresa);
        n = 0;
        uredi = new Device[0];
    }

    MobileServis(const MobileServis &ms) {
        copy(ms);
    }

    MobileServis &operator=(const MobileServis &ms) {
        if (this != &ms) {
            delete[] uredi;
            copy(ms);
        }
        return *this;
    }

    ~MobileServis() {
        delete[] uredi;
    }

    MobileServis &operator+=(const Device &d) {
        if (d.getGodina() < 2000 || d.getGodina() > 2019) {
            throw InvalidProductionDate();
        }
        Device *tmp = new Device[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = uredi[i];
        }
        tmp[n++] = d;
        delete[] uredi;
        uredi = tmp;
        return *this;
    }

    void pecatiCasovi() const {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < n; ++i) {
            cout << uredi[i];
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate &e) {
                e.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;
}
