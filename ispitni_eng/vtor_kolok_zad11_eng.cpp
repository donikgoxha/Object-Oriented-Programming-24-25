#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;

public:
    IceCream(const char *name = "", const char *ingredients = "", float price = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->price = price;
        this->discount = 0;
    }

    IceCream(const IceCream &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        strcpy(ingredients, other.ingredients);
        price = other.price;
        discount = other.discount;
    }

    IceCream &operator=(const IceCream &other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            strcpy(ingredients, other.ingredients);
            price = other.price;
            discount = other.discount;
        }
        return *this;
    }

    ~IceCream() {
        delete[] name;
    }

    void setDiscount(int d) {
        if (d < 0 || d > 100) {
            throw d;
        }
        discount = d;
    }

    void setName(char *newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    IceCream &operator++() {
        discount += 5;
        if (discount > 100) discount = 100;
        return *this;
    }

    IceCream operator+(const char *extra) {
        char *newName = new char[strlen(name) + strlen(extra) + 2];
        strcpy(newName, name);
        strcat(newName, " + ");
        strcat(newName, extra);

        IceCream temp(newName, ingredients, price + 10);
        temp.discount = discount;
        delete[] newName;
        return temp;
    }

    friend ostream &operator<<(ostream &out, const IceCream &ic) {
        out << ic.name << ": " << ic.ingredients << " " << ic.price;
        if (ic.discount > 0) {
            float discountedPrice = ic.price * (1 - ic.discount / 100.0);
            out << " (" << discountedPrice << ")";
        }
        return out;
    }
};

class IceCreamShop {
private:
    char name[50];
    IceCream *icecreams;
    int count;

public:
    IceCreamShop(const char *name = "") {
        strcpy(this->name, name);
        icecreams = nullptr;
        count = 0;
    }

    IceCreamShop(const IceCreamShop &other) {
        strcpy(name, other.name);
        count = other.count;
        icecreams = new IceCream[count];
        for (int i = 0; i < count; i++) {
            icecreams[i] = other.icecreams[i];
        }
    }

    IceCreamShop &operator=(const IceCreamShop &other) {
        if (this != &other) {
            delete[] icecreams;
            strcpy(name, other.name);
            count = other.count;
            icecreams = new IceCream[count];
            for (int i = 0; i < count; i++) {
                icecreams[i] = other.icecreams[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] icecreams;
    }

    IceCreamShop &operator+=(const IceCream &ic) {
        IceCream *tmp = new IceCream[count + 1];
        for (int i = 0; i < count; i++) {
            tmp[i] = icecreams[i];
        }
        tmp[count] = ic;
        delete[] icecreams;
        icecreams = tmp;
        count++;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const IceCreamShop &shop) {
        out << shop.name << endl;
        for (int i = 0; i < shop.count; i++) {
            out << shop.icecreams[i] << endl;
        }
        return out;
    }
};


int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;
        // your exception handling code
        try {
            cin >> discount;
            ic1.setDiscount(discount);
        } catch (int d) {
            cout << "Invalid discount value: " << d << endl;
        }
    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
