#include <iostream>
#include <cstring>
using namespace std;
// YOUR CODE HERE

class AlcoholicDrink {
protected:
    char name[100];
    char country[100];
    float percent_alcohol;
    float basePrice;
    static float discount;

public:
    AlcoholicDrink(float percent_alcohol = 0.0, const char *name = "", const char *country = "",
                   float basePrice = 0.0) {
        this->percent_alcohol = percent_alcohol;
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->basePrice = basePrice;
    }

    virtual ~AlcoholicDrink() {
    }

    virtual float computePrice() const = 0;

    friend ostream &operator<<(ostream &out, const AlcoholicDrink &alc) {
        out << alc.name << " " << alc.country << " " << alc.computePrice();
        return out;
    }

    bool operator<(const AlcoholicDrink &alc) const {
        return computePrice() < alc.computePrice();
    }

    static void changeDiscount(float d) {
        discount = d;
    }

    static void total(AlcoholicDrink **ad, int n) {
        float total = 0.0;
        for (int i = 0; i < n; i++) {
            total += ad[i]->computePrice();
        }
        cout << "Total price: " << total << endl;
        cout << "Total price with discount: " << total * (1 - discount / 100.0) << endl;
    }
};

class Beer : public AlcoholicDrink {
private:
    bool ingredient; //barley/wheat

public:
    Beer(float percent_alcohol = 0.0, const char *name = "",
         const char *country = "", float basePrice = 0.0,
         bool ingredient = false) : AlcoholicDrink(percent_alcohol, name, country, basePrice) {
        this->ingredient = ingredient;
    }

    ~Beer() {
    }

    float computePrice() const override {
        float price = basePrice;
        if (strcmp(country, "Germany") == 0 || strcmp(country, "Germanija") == 0) {
            price += 0.05 * basePrice;
            if (ingredient) {
                price += 0.10 * basePrice;
            }
        }
        return price;
    }
};

class Wine : public AlcoholicDrink {
private:
    int year_grapes;
    char grapeType[20];

public:
    Wine(float percent_alcohol = 0.0, const char *name = "",
         const char *country = "", float basePrice = 0.0,
         int year_grapes = 0, const char *grapeType = "") : AlcoholicDrink(percent_alcohol, name, country, basePrice) {
        this->year_grapes = year_grapes;
        strcpy(this->grapeType, grapeType);
    }

    ~Wine() {
    }

    float computePrice() const override {
        float price = basePrice;
        if (strcmp(country, "Italy") == 0 || strcmp(country, "Italija") == 0) {
            price += 0.05 * basePrice;
        }
        if (year_grapes < 2005) {
            price += 0.15 * basePrice;
        }
        return price;
    }
};

void lowestPrice(AlcoholicDrink **a, int n) {
    if (n <= 0) return;
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (*(a[i]) < *a[idx]) {
            idx = i;
        }
    }
    cout << *a[idx] << endl;
}

float AlcoholicDrink::discount = 5;

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
