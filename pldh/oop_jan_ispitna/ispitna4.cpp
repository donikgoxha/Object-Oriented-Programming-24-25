#include <iostream>
#include <cstring>

using namespace std;
//zad5 ispitni/kolokviumski

const int MAX = 50;

class UserExistsException {
public:
    void print() {
        cout << "The user already exists in the list!" << endl;
    }
};

enum typeC {
    STANDARD, LOYAL, VIP
};

class Customer {
protected:
    char name[51];
    char e_adresa[51];
    typeC type;
    static int basic_discount;
    static const int added_discount = 30;
    int number_products;

public:
    Customer(const char *name = " ", const char *address = " ", typeC type = STANDARD, int number = 0) : type(type),
        number_products(number) {
        strcpy(this->name, name);
        strcpy(this->e_adresa, address);
    }

    const char *getName() const {
        return name;
    }

    const char *getAddress() const {
        return e_adresa;
    }

    typeC getType() const {
        return type;
    }

    static int getDiscount() {
        return basic_discount;
    }

    static const int getPlusDiscount() {
        return added_discount;
    }

    int getNumber() const {
        return number_products;
    }

    void setType(typeC type) {
        Customer::type = type;
    }

    static void setDiscount1(int discount) {
        Customer::basic_discount = discount;
    }

    void setNumber(int number) {
        Customer::number_products = number;
    }

    ~Customer() {
    };

    friend ostream &operator<<(ostream &os, const Customer &customer);
};

int Customer::basic_discount = 10;

ostream &operator<<(ostream &o, const Customer &c) {
    o << c.name << endl;
    o << c.e_adresa << endl;
    o << c.number_products << endl;
    switch (c.type) {
        case STANDARD:
            o << "standard 0" << endl;
            break;
        case LOYAL:
            o << "loyal " << Customer::basic_discount << endl;
            break;
        case VIP:
            o << "vip " << Customer::added_discount << endl;
            break;
    }
    return o;
}

class FINKI_bookstore {
    Customer *customers;
    int n;

public:
    FINKI_bookstore(Customer *customers = 0, int n = 0) : n(n) {
        this->customers = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->customers[i] = customers[i];
        }
    }

    ~FINKI_bookstore() {
        delete[] customers;
    }

    void setCustomers(Customer *customers, int n) {
        delete[] this->customers;
        this->customers = new Customer[n];
        for (int i = 0; i < n; i++) {
            this->customers[i] = customers[i];
        }
        this->n = n;
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &other) {
        if (this != &other) {
            delete[] customers;
            this->customers = new Customer[n];
            for (int i = 0; i < n; ++i) {
                this->customers[i] = customers[i];
            }
        }
        return *this;
    }

    FINKI_bookstore &operator+=(const Customer &c) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(c.getAddress(), customers[i].getAddress()) == 0) {
                throw UserExistsException();
            }
        }

        Customer *tmp = new Customer[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = customers[i];
        }
        tmp[n++] = c;
        delete[] customers;
        customers = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &o, FINKI_bookstore &bs) {
        for (int i = 0; i < bs.n; ++i) {
            cout << bs.customers[i];
        }
        return o;
    }

    void update() {
        for (int i = 0; i < n; ++i) {
            if (customers[i].getType() == STANDARD && customers[i].getNumber() > 5) {
                customers[i].setType(LOYAL);
            } else if (customers[i].getType() == LOYAL && customers[i].getNumber() > 10) {
                customers[i].setType(VIP);
            }
        }
    }

    void setN(int n) {
        FINKI_bookstore::n = n;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;
    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException e) {
            e.print();
        }
        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
        } catch (UserExistsException e) {
            e.print();
        }
        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;
}
