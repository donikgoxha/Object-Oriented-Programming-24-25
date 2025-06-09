/*
Write a class Chocolate that contains the following data for a chocolate bar:
name - the name of the chocolate, a string of up to 100 characters;
price - the standard retail price of a package of chocolates
To the class, write a default constructor and a parameterized constructor. Overload the << operator to print objects
from the class in the following format: [name]: $[price].

Then define the class ChocolateFactory, which contains the following data for a chocolate factory:
products - a dynamically allocated array of Chocolate objects
weeklyProduction - a dynamically allocated array of integers, where weeklyProduction[i] indicates how many
packages of products[i] the factory produces weekly
numProducts - the number of types of chocolates the factory offers.
For the class, define a parameterized constructor, destructor, as well as the following methods:
weeklyIncome() which calculates the total value of chocolates the factory produces weekly
operators < and > for comparing two factories based on weekly earnings
operator + which results in a new factory with combined production of the two factories
operator << for printing the object in the following format:
[product0] x [weeklyProduction0]
[product1] x [weeklyProduction2]
...
[productN] x [weeklyProductionN]
$[weeklyIncome]/wk
Do not modify the main function. Submissions without dynamic allocation of memory are also accepted.
 */

#include<iostream>
#include<cstring>
using namespace std;

class Chocolate {
private:
    char name[100];
    int price;

public:
    Chocolate(const char *name = "", int price = 0) {
        strcpy(this->name, name);
        this->price = price;
    }

    int getPrice() const {
        return price;
    }

    const char *getName() const {
        return name;
    }

    friend ostream &operator<<(ostream &os, const Chocolate &c) {
        os << c.name << ": $" << c.price;
        return os;
    }
};

class ChocolateFactory {
private:
    Chocolate *products;
    int *weeklyProduction;
    int numProducts;

public:
    ChocolateFactory(Chocolate *products, int *weeklyProduction, int numProducts) {
        this->numProducts = numProducts;
        this->products = new Chocolate[numProducts];
        this->weeklyProduction = new int[numProducts];

        for (int i = 0; i < numProducts; ++i) {
            this->products[i] = products[i];
            this->weeklyProduction[i] = weeklyProduction[i];
        }
    }

    ~ChocolateFactory() {
        delete[] products;
        delete[] weeklyProduction;
    }

    int weeklyIncome() const {
        int income = 0;
        for (int i = 0; i < numProducts; ++i) {
            income += products[i].getPrice() * weeklyProduction[i];
        }
        return income;
    }

    friend bool operator<(const ChocolateFactory &cf1, const ChocolateFactory &cf2) {
        return cf1.weeklyIncome() < cf2.weeklyIncome();
    }

    friend bool operator>(const ChocolateFactory &cf1, const ChocolateFactory &cf2) {
        return cf1.weeklyIncome() > cf2.weeklyIncome();
    }

    ChocolateFactory operator+(const ChocolateFactory &other) const {
        int newSize = numProducts + other.numProducts;
        Chocolate *newProducts = new Chocolate[newSize];
        int *newProduction = new int[newSize];

        for (int i = 0; i < numProducts; ++i) {
            newProducts[i] = products[i];
            newProduction[i] = weeklyProduction[i];
        }
        for (int i = 0; i < other.numProducts; ++i) {
            newProducts[numProducts + i] = other.products[i];
            newProduction[numProducts + i] = other.weeklyProduction[i];
        }

        ChocolateFactory result(newProducts, newProduction, newSize);
        delete[] newProducts;
        delete[] newProduction;
        return result;
    }

    friend ostream &operator<<(ostream &os, const ChocolateFactory &cf) {
        for (int i = 0; i < cf.numProducts; ++i) {
            os << cf.products[i] << " x " << cf.weeklyProduction[i] << endl;
        }
        os << "$" << cf.weeklyIncome() << "/wk" << endl;
        return os;
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
