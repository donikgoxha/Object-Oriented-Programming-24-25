/*
Потребно е да дизајнирате програма за систем за хотелски резервации.
За таа цел потребно е да изработите класа Room која што ќе ги има следните информации:
    број на соба - цел број
    цена за ноќевање - цел број
За оваа класа потребно е да креирате:
    Default конструктор
    Конструктор со параметри
    Copy конструктор
    Оператор =
    Функција која што ја враќа цената за едно ноќевање (getPrice)
    Функција print што ги печати информациите за собата во формат:
    [број на соба] - [цена за ноќевање] euros
Понатаму, треба да креирате класа StandardRoom. Класата треба да наследува од класата
Room и дополнително да ги има следниве информации:
    hasBalcony  - bool променлива
За оваа класа потребно е да креирате:
    Default конструктор
    Конструктор со параметри
    Функција што ја враќа цената за едно ноќевање (getPrice) која што се пресметува така што доколку собата има
    балкон, се одзема 5% од цената што ја добивате од класата Room. Доколку собата нема балкон,цената за едно
    ноќевање е онаа што ја добивате од класата Room. Пример, доколку цената за ноќевање што ја добивате од класата
    Room е 60 евра и собата има балкон, тогаш овде функцијата треба да врати 57 евра затоа што 60 - 60 0.05 = 57.
    Функција print што ги печати информациите за собата во формат:   [број на соба] - [цена за ноќевање] euros.
    Доколку има балкон додадете 'has a balcony', доколку нема балкон додадете 'without balcony'.
Понатаму, треба да креирате класа LuxuryRoom која треба да наследува од класата Room и дополнително да ги има
следниве информации:
    hasJacuzzi - bool променлива
За оваа класа потребно е да креирате:
    Default конструктор
    Конструктор со параметри
    Функција што ја враќа цената за едно ноќевање (getPrice) која што се пресметува така што доколку собата има
    џакузи, се додава 20% од цената што ја добивате од класата Room.Доколку собата нема џакузи,цената за едно ноќевање
    е онаа што ја добивате од класата Room.Пример, доколку цената за ноќевање што ја добивате од класата Room е 60 евра
    и собата има џакузи, тогаш овде функцијата треба да врати 72 евра затоа што 60 + 600.2 = 72.
    Функција print што ги печати информациите за собата во формат:    [број на соба] - [цена за ноќевање] euros.
    Доколку има џакузи додадете 'has a jacuzzi', доколку нема додадете 'without jacuzzi'.

Input
4
5
Standard 204 120 1
Luxury 205 180 1
Room 206 100
Standard 207 130 0
Luxury 208 220 1

Expected
204 - 114 euros has a balcony
205 - 216 euros has a jacuzzi
206 - 100 euros
207 - 130 euros without balcony
208 - 264 euros has a jacuzzi
 */


#include <iostream>
#include <cstring>
using namespace std;

class Room {
protected:
    int rooms;
    int price;

    void copy(const Room &r) {
        rooms = r.rooms;
        price = r.price;
    }

public:
    Room(int rooms = 0, int price = 0) {
        this->rooms = rooms;
        this->price = price;
    }

    Room(const Room &r) {
        copy(r);
    }

    Room &operator=(const Room &r) {
        if (this != &r) {
            copy(r);
        }
        return *this;
    }

    virtual ~Room() {
    }

    virtual int getPrice() const {
        return price;
    }

    virtual void print() const {
        cout << rooms << " - " << getPrice() << " euros ";
    }
};

class StandardRoom : public Room {
private:
    bool hasBalcony;

public:
    StandardRoom(int rooms = 0, int price = 0, bool hasBalcony = false) : Room(rooms, price) {
        this->hasBalcony = hasBalcony;
    }

    int getPrice() const override {
        if (hasBalcony) {
            return price - (price * 0.05);
        }
        return price;
    }

    void print() const override {
        Room::print();
        cout << (hasBalcony ? "has a balcony" : "without balcony") << endl;
    }
};

class LuxuryRoom : public Room {
private:
    bool hasJacuzzi;

public:
    LuxuryRoom(int rooms = 0, int price = 0, bool hasJacuzzi = false) : Room(rooms, price) {
        this->hasJacuzzi = hasJacuzzi;
    }

    int getPrice() const override {
        if (hasJacuzzi) {
            return price + (price * 0.2);
        }
        return price;
    }

    void print() const override {
        Room::print();
        cout << (hasJacuzzi ? "has a jacuzzi" : "without jacuzzi") << endl;
    }
};


int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        // Test Room class
        int number, price;
        cin >> number >> price;
        Room r1(number, price);
        Room r2 = r1; // Copy constructor
        Room r3;
        r3 = r1; // Assignment operator

        r1.print();
        r2.print();
        r3.print();
    } else if (testCase == 2) {
        // Test StandardRoom
        int number, price;
        bool hasBalcony;
        cin >> number >> price >> hasBalcony;

        StandardRoom sr(number, price, hasBalcony);
        sr.print();
    } else if (testCase == 3) {
        // Test LuxuryRoom
        int number, price;
        bool hasJacuzzi;
        cin >> number >> price >> hasJacuzzi;

        LuxuryRoom lr(number, price, hasJacuzzi);
        lr.print();
    } else if (testCase == 4) {
        // Polymorphism test
        int n;
        cin >> n;
        Room *rooms[100];

        for (int i = 0; i < n; ++i) {
            string type;
            cin >> type;

            int number, price;
            cin >> number >> price;

            if (type == "Standard") {
                bool hasBalcony;
                cin >> hasBalcony;
                rooms[i] = new StandardRoom(number, price, hasBalcony);
            } else if (type == "Luxury") {
                bool hasJacuzzi;
                cin >> hasJacuzzi;
                rooms[i] = new LuxuryRoom(number, price, hasJacuzzi);
            } else {
                rooms[i] = new Room(number, price);
            }
        }

        for (int i = 0; i < n; ++i) {
            rooms[i]->print();
        }

        for (int i = 0; i < n; ++i) {
            delete rooms[i];
        }
    }

    return 0;
}
