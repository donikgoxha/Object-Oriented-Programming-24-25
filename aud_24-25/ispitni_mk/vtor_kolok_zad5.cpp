#include <iostream>
#include <cstring>

using namespace std;
const int MAX = 50;

enum typeC { STANDARD, LOYAL, VIP };

class UserExistsException {
public:
    const char* message() const {
        return "The user already exists in the list!";
    }
};

class Customer {
protected:
    char name[50];
    char email[50];
    typeC type;
    static int sale;
    static const int extraSale;
    int n;

public:
    Customer(const char *name = "", const char *email = "", typeC type = STANDARD, int n = 0) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = type;
        this->n = n;
    }

    static void setDiscount(int d) {
        sale = d;
    }

    const char *getEmail() const {
        return email;
    }

    typeC getType() const {
        return type;
    }

    int getNumProducts() const {
        return n;
    }

    void promote() {
        if (type == STANDARD && n > 5) {
            type = LOYAL;
        } else if (type == LOYAL && n > 10) {
            type = VIP;
        }
    }

    friend ostream &operator<<(ostream &os, const Customer &c) {
        os << c.name << endl;
        os << c.email << endl;
        os << c.n << endl;

        if (c.type == STANDARD) {
            os << "standard 0" << endl;
        }
        else if (c.type == LOYAL) {
            os << "loyal " << c.sale << endl;
        }
        else if (c.type == VIP) {
            os << "vip " << (c.sale + c.extraSale) << endl;
        }
        return os;
    }
};

int Customer::sale = 10;
const int Customer::extraSale = 20;

class FINKI_bookstore {
private:
    Customer* customers;
    int n;
    int capacity;

    void copy(const FINKI_bookstore& other) {
        this->n = other.n;
        this->capacity = other.capacity;
        this->customers = new Customer[this->capacity];
        for(int i = 0; i < this->n; i++) {
            this->customers[i] = other.customers[i];
        }
    }

public:
    FINKI_bookstore(int capacity = 10) {
        this->capacity = capacity;
        this->n = 0;
        this->customers = new Customer[this->capacity];
    }

    FINKI_bookstore(const FINKI_bookstore& other) {
        copy(other);
    }

    FINKI_bookstore& operator=(const FINKI_bookstore& other) {
        if(this != &other) {
            delete [] customers;
            copy(other);
        }
        return *this;
    }

    ~FINKI_bookstore() {
        delete [] customers;
    }

    void setCustomers(Customer* customers, int n) {
        delete [] this->customers;
        this->n = n;
        this->capacity = n;
        this->customers = new Customer[this->capacity];
        for(int i = 0; i < n; i++) {
            this->customers[i] = customers[i];
        }
    }

    void update() {
        for(int i = 0; i < n; i++) {
            customers[i].promote();
        }
    }

    FINKI_bookstore& operator+=(const Customer& c) {
        // Check if customer with same email exists
        for(int i = 0; i < n; i++) {
            if(strcmp(customers[i].getEmail(), c.getEmail()) == 0) {
                throw UserExistsException();
            }
        }

        // Resize if needed
        if(n == capacity) {
            capacity *= 2;
            Customer* temp = new Customer[capacity];
            for(int i = 0; i < n; i++) {
                temp[i] = customers[i];
            }
            delete [] customers;
            customers = temp;
        }

        customers[n++] = c;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const FINKI_bookstore& fc) {
        for(int i = 0; i < fc.n; i++) {
            os << fc.customers[i];
        }
        return os;
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

        c.setDiscount(5);

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
        fc += c;

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
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch(UserExistsException& e) {
            cout << e.message() << endl;
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
