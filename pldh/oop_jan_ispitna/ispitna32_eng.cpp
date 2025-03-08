#include <iostream>
#include <cstring>
using namespace std;

//Your code here
class Tickets {
protected:
    static int discount;
    int ID[12];
    char event[100];
    float basePrice;

public:
    Tickets(const int *ID = nullptr, const char *event = "", float basePrice = 0.0) {
        for (int i = 0; i < 12; i++) {
            this->ID[i] = ID[i];
        }
        strcpy(this->event, event);
        this->basePrice = basePrice;
    }

    virtual ~Tickets() {
    }

    bool falsifikat(int from, int to) {
        int last_four = ID[8] * 1000 + ID[9] * 100 + ID[10] * 10 + ID[11];
        return !(last_four >= from && last_four <= to);
    }

    static void changeDiscount(int d) {
        discount = d;
    }

    virtual float presmetajCena() const = 0;

    friend ostream &operator<<(ostream &out, const Tickets &t) {
        for (int i = 0; i < 12; i++) {
            out << t.ID[i];
        }
        out << "-" << t.event << "-" << t.presmetajCena();
        return out;
    }
};

class Online : public Tickets {
    bool premium;

public:
    Online(const int *ID = nullptr, const char *event = "", float basePrice = 0.0, bool premium = false) : Tickets(
        ID, event, basePrice) {
        this->premium = premium;
    }

    float presmetajCena() const override {
        float price = basePrice;
        if (premium) price *= 0.85;
        return price * (1 - discount / 100.0);
    }
};

class Offline : public Tickets {
    bool seatReservation;

public:
    Offline(const int *ID = nullptr, const char *event = "", float basePrice = 0.0,
            bool seatReservation = false) : Tickets(
        ID, event, basePrice) {
        this->seatReservation = seatReservation;
    }

    float presmetajCena() const override {
        float price = basePrice;
        if (seatReservation) price *= 1.1;
        return price * (1 - discount / 100.0);
    }
};

void vkupenPrihod(Tickets **t, int n, int from, int to) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        if (!t[i]->falsifikat(from, to)) {
            total += t[i]->presmetajCena();
        }
    }
    cout << total << endl;
}

int Tickets::discount = 0;


// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION
int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;
    } else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets **t = new Tickets *[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0) {
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            } else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    } else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets **t = new Tickets *[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<price<<endl;
            if (i % 2 == 0) {
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            } else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;
    }
}
