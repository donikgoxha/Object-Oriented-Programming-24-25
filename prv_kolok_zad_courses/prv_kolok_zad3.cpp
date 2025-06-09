#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord {
private:
    char ID[12];
    char name[50];
    float buyprice;
    float sellprice;
    int actionsBought;

    void copy(const StockRecord &sr) {
        strcpy(this->ID, sr.ID);
        strcpy(this->name, sr.name);
        this->buyprice = sr.buyprice;
        this->sellprice = sr.sellprice;
        this->actionsBought = sr.actionsBought;
    }

public:
    StockRecord(const char *ID = "", const char *name = "", float buyprice = 0, int actionsBought = 0) {
        strcpy(this->ID, ID);
        strcpy(this->name, name);
        this->buyprice = buyprice;
        this->actionsBought = actionsBought;
        this->sellprice = buyprice;
    }

    StockRecord(const StockRecord &sr) {
        copy(sr);
    }

    StockRecord &operator=(const StockRecord &sr) {
        if (this != &sr) {
            copy(sr);
        }
        return *this;
    }

    void setNewPrice(double c) {
        sellprice = c;
    }

    double value() const {
        return actionsBought * sellprice;
    }

    double profit() const {
        return actionsBought * (sellprice - buyprice);
    }

    friend ostream &operator<<(ostream &os, const StockRecord &sr) {
        os << sr.name << " " << sr.actionsBought << " " << sr.buyprice << " " << sr.sellprice << " " << sr.profit() <<
                endl;
        return os;
    }
};

class Client {
private:
    char nameClient[60];
    int ID;
    StockRecord *companies;
    int n;

    void copy(const Client &c) {
        strcpy(this->nameClient, c.nameClient);
        this->ID = c.ID;
        this->n = c.n;
        this->companies = new StockRecord[n];
        for (int i = 0; i < n; ++i)
            this->companies[i] = c.companies[i];
    }

public:
    Client(const char *name = "", int ID = 0) {
        strcpy(this->nameClient, name);
        this->ID = ID;
        this->n = 0;
        this->companies = nullptr;
    }

    Client(const Client &c) {
        copy(c);
    }

    Client &operator=(const Client &c) {
        if (this != &c) {
            delete[] companies;
            copy(c);
        }
        return *this;
    }

    ~Client() {
        delete[] companies;
    }

    Client &operator+=(const StockRecord &sr) {
        StockRecord *tmp = new StockRecord[n + 1];
        for (int i = 0; i < n; ++i)
            tmp[i] = companies[i];
        tmp[n] = sr;
        delete[] companies;
        companies = tmp;
        ++n;
        return *this;
    }

    double totalValue() const {
        double total = 0;
        for (int i = 0; i < n; ++i)
            total += companies[i].value();
        return total;
    }

    friend ostream &operator<<(ostream &out, const Client &c) {
        out << c.ID << " " << c.totalValue() << endl;
        for (int i = 0; i < c.n; ++i)
            out << c.companies[i];
        return out;
    }
};


// ne menuvaj vo main-ot

int main() {
    int test;
    cin >> test;

    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;
}
