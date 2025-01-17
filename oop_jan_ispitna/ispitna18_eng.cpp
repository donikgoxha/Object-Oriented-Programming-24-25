#include <iostream>
#include <cstring>
using namespace std;
//zad1 ispitni/kolokviumski eng

class AlcoholicDrink {
protected:
    char name[100];
    char origin[100];
    float percentOfAlc;
    float basePrice;
    static int discount;

public:
    AlcoholicDrink(float percent = 0.0, const char *name = "", const char *origin = "", float basePrice = 0.0) {
        this->percentOfAlc = percent;
        strcpy(this->name, name);
        strcpy(this->origin, origin);
        this->basePrice = basePrice;
    }

    virtual float computePrice() const = 0;


    static void changeDiscount(int d) {
        discount = d;
    }

    virtual ~AlcoholicDrink() = default;

    bool operator<(const AlcoholicDrink &other) const {
        return this->computePrice() < other.computePrice();
    }

    friend ostream &operator<<(ostream &out, const AlcoholicDrink &a) {
        return out << a.name << " " << a.origin << " " << a.computePrice() << endl;
    }

    static void total(AlcoholicDrink **ad, int n) {
        float total = 0;
        for (int i = 0; i < n; i++) {
            total += ad[i]->computePrice();
        }
        cout << "Total price: " << total << endl;
        cout << "Total price with discount: " << total * (1 - discount / 100.0) << endl;
    }
};

class Beer : public AlcoholicDrink {
private:
    bool mainIngredient;
    // false for barley, true for wheat

public:
    Beer(float percent = 0.0, const char *name = "", const char *origin = "", float basePrice = 0.0,
         bool mainIngredient = false) : AlcoholicDrink(percent, name, origin, basePrice) {
        this->mainIngredient = mainIngredient;
    }

    float computePrice() const {
        double price = basePrice;
        if (strcmp(origin, "Germanija") == 0) {
            price += 0.05 * basePrice;
        }
        if (mainIngredient) {
            // wheat
            price += 0.10 * basePrice;
        }
        return (float) price;
    }
};

class Wine : public AlcoholicDrink {
private:
    char grapesType[50];
    int yearProduction;

public:
    Wine(float percent = 0.0, const char *name = "", const char *origin = "", float basePrice = 0.0,
         int yearProduction = 0, const char *grapesType = ""): AlcoholicDrink(percent, name, origin, basePrice) {
        this->yearProduction = yearProduction;
        strcpy(this->grapesType, grapesType);
    }

    float computePrice() const override {
        double price = basePrice;
        if (strcmp(origin, "Italija") == 0) {
            price += 0.05 * basePrice;
        }
        if (yearProduction < 2005) {
            price += 0.15 * basePrice;
        }
        return (float) price;
    }
};


void lowestPrice(AlcoholicDrink **a, int n) {
    if (n == 0) return;

    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (*a[i] < *a[minIndex]) {
            minIndex = i;
        }
    }
    cout << *a[minIndex] << endl;
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
        cout << b;
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
