#include <iostream>
#include <cstring>
using namespace std;

//zad12 ispitni/kolokviumski

enum tip { SMARTPHONE, LAPTOP };

class InvalidProductionDate {
public:
    void message() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
    char model[100];
    tip type;
    int productionYear;
    static int basicCheckHours;

public:
    Device(char *model = "", tip type = SMARTPHONE, int productionYear = 0) {
        strcpy(this->model, model);
        this->type = type;
        this->productionYear = productionYear;
    }

    static void setPocetniCasovi(float basicWorkHours) {
        basicCheckHours = basicWorkHours;
    }

    float getTotalHours() const {
        float totalHours = basicCheckHours;
        if (type == LAPTOP) {
            totalHours += 2;
        }
        if (productionYear > 2015) {
            totalHours += 2;
        }
        return totalHours;
    }

    friend ostream &operator<<(ostream &os, const Device &device) {
        os << device.model << endl;
        os << (device.type == LAPTOP ? "Laptop " : "Mobilen ")
                << device.getTotalHours() << endl;
        return os;
    }

    int getYear() const {
        return productionYear;
    }
};

class MobileServis {
private:
    char adresa[100];
    Device *devices;
    int numDevices;


    void copy(const MobileServis &other) {
        strcpy(this->adresa, other.adresa);
        this->numDevices = other.numDevices;
        this->devices = new Device[this->numDevices];
        for (int i = 0; i < this->numDevices; i++) {
            this->devices[i] = other.devices[i];
        }
    }

public:
    MobileServis(char *adresa = "") {
        strcpy(this->adresa, adresa);
        this->numDevices = 0;
        devices = new Device[0];
    }

    MobileServis(const MobileServis &ms) {
        copy(ms);
    }

    MobileServis &operator=(const MobileServis &ms) {
        if (this != &ms) {
            delete []devices;
            copy(ms);
        }
        return *this;
    }

    MobileServis &operator+=(const Device &device) {
        if (device.getYear() < 2000 || device.getYear() > 2019) {
            throw InvalidProductionDate();
        }
        Device *tmp = new Device[numDevices + 1];
        for (int i = 0; i < numDevices; i++) {
            tmp[i] = devices[i];
        }
        tmp[numDevices++] = device;
        delete [] devices;
        devices = tmp;
        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < numDevices; i++) {
            cout << devices[i];
        }
    }

    ~MobileServis() {
        delete[] devices;
    }
};


int Device::basicCheckHours = 1;


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
                e.message();
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
                e.message();
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
                e.message();
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
                e.message();
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
                e.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    return 0;
}
