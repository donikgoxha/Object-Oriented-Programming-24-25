/*
Да се дефинира класа Device, која чува податоци за паметен домашен уред.
Класата Device се состои од следните полиња:
• Име (текстуална низа од 50 знаци)
• Потрошувачка на енергија (цел број)
• Категорија (енумерациски тип: security, kitchen или entertainment)
• Цена (double)
• Статус (boolean)

За оваа класа да се обезбедат потребните конструктори и get/set методи
Да се имплементира метода print() со којашто ќе се печатат информациите за електронскиот уред
во следниот формат:
(име) ([категорија]) - Power: (потрошувачка на енергија]W Price: [цена]$ Status: [ON|OFF]
Да се имплементира метода void togglePower() која го менува статусот на уредот во вклучен ако е
исклучен и обратно.
Да се имплементира метода void increasePowerConsumption(int watts) која ја зголемува потрошувачката
на енергија на уредот за дадена вредност.

Да се дефинира класа SmartHome, во која се чуваат следните информации:
• Име (текстуална низа од 50 знаци)
• Идентификациски број (цел број)
• Листа на уреди (низа со максимум 100 објекти од класа Device)
• Број на уреди (број на елементи во листа на уреди, иницијално е 0).

За оваа класа да се дефинираат потребните конструктори, деструктор и get/set методи.
Идентификацискиот број за секој дом е единствен и неговата почетна вредност е 100. Да се обезбеди
генерирање на овој број така што првиот дом има идентификациски број 101 (100+1),
вториот 103 (101+2), третиот 106(103+3), ...
Да се имплементира метода print() која ќе ги печати информациите за еден дом во следен формат:
[идентификациски број]: [име]
Devices:
(печатење на сите уреди]
Да се имплементираат следните методи во класата SmartHome:
• addDevice(const Device&) за додавање нов електронски уред во домот. Електронските уреди се
управуваат на следниот начин: не смее да се дозволи додавање на уред со исто име во иста категорија,
доколку се најде таков тогаш да се испечати порака Device already exists!".
• void toggle AllDevicesByCategory(Category category), која го изменува статусот на сите електронски
уреди во домот кои припаѓаат на таа категорија.
• void increasePowerConsumptionForCategory(int watts, Category category), каде ќе се зголеми
потрошувачката на енергија на сите уреди од дадена категорија.

Да се дефинира глобална функција:
SmartHome& mostAutomatedHome(SmartHome "smartHomes, int n)
која прима низа од објекти од класата SmartHome и бројот на домови. Како резултат оваа функција
враќа кој дом има најмногу електронски уреди. Доколку повеќе домови имаат ист број на електронски
уреди, се враќа последниот!
 */


#include <iostream>
#include <cstring>
using namespace std;

enum Category { SECURITY, KITCHEN, ENTERTAINMENT };

const char *categoryToString(Category c) {
    switch (c) {
        case SECURITY: return "security";
        case KITCHEN: return "kitchen";
        case ENTERTAINMENT: return "entertainment";
        default: return "unknown";
    }
}

class Device {
private:
    char name[50]{};
    int powerConsumption;
    Category category;
    double price;
    bool status;

public:
    explicit Device(const char *name = "", int power, Category category = KITCHEN, double price = 0.0,
                    bool status = false) {
        strcpy(this->name, name);
        this->powerConsumption = power;
        this->category = category;
        this->price = price;
        this->status = status;
    }


    const char *getName() const { return name; }
    int getPower() const { return powerConsumption; }
    Category getCategory() const { return category; }
    double getPrice() const { return price; }
    bool getStatus() const { return status; }

    void setName(const char *name) { strcpy(this->name, name); }
    void setPower(int power) { this->powerConsumption = power; }
    void setCategory(Category c) { this->category = c; }
    void setPrice(double p) { this->price = p; }
    void setStatus(bool s) { this->status = s; }

    void togglePower() { status = !status; }

    void increasePowerConsumption(int watts) { powerConsumption += watts; }

    void print() const {
        cout << name << " (" << categoryToString(category) << ") - Power: "
                << powerConsumption << "W Price: " << price << "$ Status: "
                << (status ? "ON" : "OFF") << endl;
    }
};

class SmartHome {
private:
    char name[50];
    int id;
    Device devices[100];
    int deviceCount;

    static int idSeed;

public:
    SmartHome(const char *name) {
        strcpy(this->name, name);
        this->id = idSeed += (deviceCount == 0 ? 1 : deviceCount + 1);
        deviceCount = 0;
    }

    ~SmartHome() {
    }

    const char *getName() const { return name; }
    int getId() const { return id; }
    int getDeviceCount() const { return deviceCount; }

    void print() const {
        cout << id << ": " << name << endl;
        cout << "Devices:" << endl;
        for (int i = 0; i < deviceCount; i++) {
            devices[i].print();
        }
    }

    void addDevice(const Device &d) {
        for (int i = 0; i < deviceCount; i++) {
            if (strcmp(devices[i].getName(), d.getName()) == 0 &&
                devices[i].getCategory() == d.getCategory()) {
                cout << "Device already exists!" << endl;
                return;
            }
        }

        if (deviceCount < 100) {
            devices[deviceCount++] = d;
        }
    }

    void toggleAllDevicesByCategory(Category cat) {
        for (int i = 0; i < deviceCount; i++) {
            if (devices[i].getCategory() == cat) {
                devices[i].togglePower();
            }
        }
    }

    void increasePowerConsumptionForCategory(int watts, Category cat) {
        for (int i = 0; i < deviceCount; i++) {
            if (devices[i].getCategory() == cat) {
                devices[i].increasePowerConsumption(watts);
            }
        }
    }
};

int SmartHome::idSeed = 100;

SmartHome &mostAutomatedHome(SmartHome *homes, int n) {
    int maxDevices = homes[0].getDeviceCount();
    int idx = 0;
    for (int i = 1; i < n; i++) {
        int currentDevices = homes[i].getDeviceCount();
        if (currentDevices >= maxDevices) {
            maxDevices = currentDevices;
            idx = i;
        }
    }
    return homes[idx];
}

int main() {
    //main given by the quiz
    return 0;
}
