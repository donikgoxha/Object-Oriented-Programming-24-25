#include <iostream>
#include <string>
using namespace std;

class AlcoholicDrink {
protected:
    string name;
    string country;
    float alcoholPercent;
    float basePrice;
    static int discount; // Shared among all instances

public:
    AlcoholicDrink(float alcoholPercent, const string &name, const string &country, float basePrice) {
        this->alcoholPercent = alcoholPercent;
        this->name = name;
        this->country = country;
        this->basePrice = basePrice;
    }

    virtual ~AlcoholicDrink() {
    }

    virtual float computePrice() const = 0;

    virtual float getDisplayPrice() const {
        return computePrice();
    }

    friend ostream &operator<<(ostream &out, const AlcoholicDrink &ad) {
        out << ad.name << " " << ad.country << " " << ad.getDisplayPrice();
        return out;
    }

    bool operator<(const AlcoholicDrink &other) const {
        return getDisplayPrice() < other.getDisplayPrice();
    }

    static void changeDiscount(int d) {
        discount = d;
    }

    static void total(AlcoholicDrink **ad, int n) {
        float totalPrice = 0, totalDiscounted = 0;
        for (int i = 0; i < n; ++i) {
            float price = ad[i]->computePrice();
            totalPrice += price;
            totalDiscounted += price * (1 - discount / 100.0);
        }
        cout << "Total price: " << totalPrice << endl;
        cout << "Total price with discount: " << totalDiscounted << endl;
    }
};


class Beer : public AlcoholicDrink {
    bool mainIngredientWheat;

public:
    Beer(float alcoholPercent, const string &name, const string &country, float basePrice, bool mainIngredientWheat)
        : AlcoholicDrink(alcoholPercent, name, country, basePrice) {
        this->mainIngredientWheat = mainIngredientWheat;
    }

    float computePrice() const override {
        float price = basePrice;
        if (country == "Germany") {
            price += basePrice * 0.05;
        }
        if (mainIngredientWheat) {
            price += basePrice * 0.10;
        }
        return price;
    }

    float getDisplayPrice() const override {
        return basePrice;
    }
};

class Wine : public AlcoholicDrink {
    int year;
    string grapeType;

public:
    Wine(float alcoholPercent, const string &name, const string &country, float basePrice, int year,
         const string &grapeType)
        : AlcoholicDrink(alcoholPercent, name, country, basePrice) {
        this->year = year;
        this->grapeType = grapeType;
    }

    float computePrice() const override {
        float price = basePrice;
        if (country == "Italy") {
            price += basePrice * 0.05;
        }
        if (year < 2005) {
            price += basePrice * 0.15;
        }
        return price;
    }
};

void lowestPrice(AlcoholicDrink **ad, int n) {
    if (n == 0) return;
    AlcoholicDrink *minDrink = ad[0];
    for (int i = 1; i < n; ++i) {
        if (*ad[i] < *minDrink) {
            minDrink = ad[i];
        }
    }
    cout << *minDrink << endl;
}

int AlcoholicDrink::discount = 5;

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape[20];
    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;
    } else if (testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink **ad = new AlcoholicDrink *[n];
        for (int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for (int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }
}
