#include<iostream>
#include<cstring>
using namespace std;

class Chocolate {
private:
    char name[101];
    double price;

public:
    Chocolate(char *n = "", double price = 0.0) {
        strcpy(name, n);
        this->price = price;
    }

    friend ostream &operator<<(ostream &out, const Chocolate &ch) {
        return out << ch.name << ": $" << ch.price;
    }

    int getPrice() const {
        return price;
    }

    ~Chocolate() {
    }
};

class ChocolateFactory {
private:
    Chocolate *products;
    int *weeklyProduction;
    int numProducts;

public:
    ChocolateFactory(Chocolate p[], int w[], int n) {
        numProducts = n;
        products = new Chocolate[n];
        weeklyProduction = new int[n];

        for (int i = 0; i < n; i++) {
            products[i] = p[i];
            weeklyProduction[i] = w[i];
        }
    }

    ~ChocolateFactory() {
        delete[] products;
        delete[] weeklyProduction;
    }

    double weeklyIncome() const {
        double total = 0;
        for (int i = 0; i < numProducts; i++) {
            total += products[i].getPrice() * weeklyProduction[i];
        }

        return total;
    }

    bool operator<(const ChocolateFactory &other) const {
        return weeklyIncome() < other.weeklyIncome();
    }


    bool operator>(const ChocolateFactory &other) const {
        return weeklyIncome() > other.weeklyIncome();
    }


    friend ostream &operator<<(ostream &os, const ChocolateFactory &cf) {
        for (int i = 0; i < cf.numProducts; i++) {
            os << cf.products[i] << " x " << cf.weeklyProduction[i] << "\n";
        }
        os << "$" << cf.weeklyIncome() << "/wk" << endl;
        return os;
    }

    ChocolateFactory operator+(const ChocolateFactory &other) const {
        int newSize = numProducts + other.numProducts;
        Chocolate *newProducts = new Chocolate[newSize];
        int *newProduction = new int[newSize];

        for (int i = 0; i < numProducts; i++) {
            newProducts[i] = products[i];
            newProduction[i] = weeklyProduction[i];
        }

        for (int i = 0; i < other.numProducts; i++) {
            newProducts[numProducts + i] = other.products[i];
            newProduction[numProducts + i] = other.weeklyProduction[i];
        }

        ChocolateFactory result(newProducts, newProduction, newSize);
        delete[] newProducts;
        delete[] newProduction;
        return result;
    }
};


int main() {
    int testCase;
    char name[100];
    int price;

    Chocolate products[100];
    int weeklyProduction[100];

    cin >> testCase;
    if (testCase == 0) {
        cout << "Testing Chocolate print operator:" << endl;
        for (int i = 0; i < 10; ++i) {
            cin >> name >> price;
            cout << Chocolate(name, price) << endl;
        }
    } else if (testCase == 1) {
        cout << "Testing ChocolateFactory print operator:" << endl;

        for (int i = 0; i < 10; ++i) {
            cin >> name >> price;
            products[i] = Chocolate(name, price);
            cin >> weeklyProduction[i];
        }

        ChocolateFactory cf(products, weeklyProduction, 10);
        cout << cf << endl;
    } else if (testCase == 2) {
        cout << "Testing ChocolateFactory comparison operators:" << endl;

        for (int i = 0; i < 3; ++i) {
            cin >> name >> price >> weeklyProduction[i];
            products[i] = Chocolate(name, price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products, weeklyProduction, 3);

        for (int i = 0; i < 4; ++i) {
            cin >> name >> price >> weeklyProduction[i];
            products[i] = Chocolate(name, price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products, weeklyProduction, 4);

        cout << cf1 << cf2;

        cout << "< operator: " << (cf1 < cf2 ? "PASS" : "FAIL") << endl;
        cout << "> operator: " << (cf2 > cf1 ? "PASS" : "FAIL") << endl;
    } else if (testCase == 3) {
        cout << "Testing ChocolateFactory sum operator:" << endl;

        for (int i = 0; i < 5; ++i) {
            cin >> name >> price >> weeklyProduction[i];
            products[i] = Chocolate(name, price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products, weeklyProduction, 5);
        for (int i = 0; i < 5; ++i) {
            cin >> name >> price >> weeklyProduction[i];
            products[i] = Chocolate(name, price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products, weeklyProduction, 5);

        cout << cf1 + cf2;
    }
}
