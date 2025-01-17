#include <iostream>
#include <cstring>
using namespace std;
//zad11 ispitni/kolokviumski eng

class InvalidDiscountValue {
private:
    int v;

public:
    InvalidDiscountValue(int v) : v(v) {
    }

    int getValue() const {
        return v;
    }
};

class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;


    void copy(const IceCream &ic) {
        this->name = new char [strlen(ic.name) + 1];
        strcpy(this->name, ic.name);
        strcpy(this->ingredients, ic.ingredients);
        this->price = ic.price;
        this->discount = ic.discount;
    }

public:
    IceCream(const char *name = "", const char *ingredients = "", float price = 0.0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->price = price;
        this->discount = 0;
    }

    IceCream(const IceCream &ic) {
        copy(ic);
    }

    IceCream &operator=(const IceCream &ic) {
        if (this != &ic) {
            delete [] name;
            copy(ic);
        }
        return *this;
    }

    void setDiscount(int discount) {
        if (discount < 1 || discount > 100) {
            throw InvalidDiscountValue(discount);
        }
        this->discount = discount;
    }

    void setName(char *name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    IceCream &operator++() {
        discount += 5;
        return *this;
    }

    IceCream operator+(const char *addon) {
        char *newName = new char[strlen(this->name) + strlen(addon) + 2];
        strcpy(newName, this->name);
        strcat(newName, " + ");
        strcat(newName, addon);

        IceCream result(*this);
        delete[] result.name;
        result.name = newName;
        result.price += 10;
        return result;
    }

    friend ostream &operator<<(ostream &out, const IceCream &ic) {
        out << ic.name << ": " << ic.ingredients << " " << ic.price;
        if (ic.discount > 0) {
            float discounted = ic.price * (100 - ic.discount) / 100.0;
            out << " (" << discounted << ")";
        }
        return out;
    }

    ~IceCream() {
        delete [] name;
    }

    friend class IceCreamShop;
};


class IceCreamShop {
    char name[50];
    IceCream *icecreams;
    int num;
    int capacity;

    void copy(const IceCreamShop &ic) {
        strcpy(this->name, ic.name);
        this->num = ic.num;
        this->capacity = ic.capacity;
        this->icecreams = new IceCream[capacity];
        for (int i = 0; i < num; i++) {
            this->icecreams[i] = ic.icecreams[i];
        }
    }

public:
    IceCreamShop(const char *name = "") {
        strcpy(this->name, name);
        this->num = 0;
        this->capacity = 10;
        this->icecreams = new IceCream[capacity];
    }

    IceCreamShop(const IceCreamShop &ic) {
        copy(ic);
    }

    IceCreamShop &operator=(const IceCreamShop &ic) {
        if (this != &ic) {
            delete [] icecreams;
            copy(ic);
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] icecreams;
    }

    IceCreamShop &operator+=(const IceCream &ic) {
        if (num == capacity) {
            capacity *= 2;
            IceCream *temp = new IceCream[capacity];
            for (int i = 0; i < num; i++)
                temp[i] = icecreams[i];
            delete[] icecreams;
            icecreams = temp;
        }
        icecreams[num++] = ic;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os << shop.name << endl;
        for (int i = 0; i < shop.num; i++)
            os << shop.icecreams[i] << endl;
        return os;
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
        cout << "OPERATOR <<" << endl;
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
        } catch (InvalidDiscountValue &e) {
            cout << "Invalid discount value: " << e.getValue() << endl;
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
