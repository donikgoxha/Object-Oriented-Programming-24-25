#include <iostream>
#include <cstring>
#include <fstream>
//zad1 lani kolok
using namespace std;

class NoProductFoundException {
private:
    string category;

public:
    NoProductFoundException(const string &category = "") {
        this->category = category;
    }

    void print() {
        cout << "No products from category " << category << " were found in the store" << endl;
    }
};

class Product {
private:
    string name;
    string category;
    int price;
    int n;

public:
    Product(const string &name = "", const string &category = "", int price = 0, int n = 0) {
        this->name = name;
        this->category = category;
        this->price = price;
        this->n = n;
    }

    friend ostream &operator<<(ostream &o, const Product &p) {
        o << p.name << " (" << p.category << ") " << p.n << " x " << p.price << " = " << p.totalPrice() << endl;
        return o;
    }

    friend istream &operator>>(istream &i, Product &p) {
        getline(i, p.name);
        getline(i, p.category);
        i >> p.price;
        i >> p.n;
        i.ignore();
        return i;
    }

    int totalPrice() const { return n * price; }

    string getName() const { return name; }

    string getCategory() const { return category; }

    bool operator==(const Product &pr) {
        return this->name == pr.name;
    }
};

class Store {
private:
    Product *p;
    int n;

public:
    Store(Product *p = 0, int n = 0) {
        this->n = n;
        this->p = new Product[n];
        for (int i = 0; i < n; i++) {
            this->p[i] = p[i];
        }
    }

    ~Store() {
        delete [] p;
    }

    Store &operator+=(const Product &pr) {
        /*Product *tmp = new Product[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = p[i];
        }
        tmp[n++] = pr;
        delete [] p;
        p = tmp;
        return *this;*/
        for (int i = 0; i < n; i++) {
            if (p[i] == pr) {
                return *this;
            }
        }
        Product *tmp = new Product[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = p[i];
        }
        tmp[n++] = pr;
        delete [] p;
        p = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &o, const Store &s) {
        for (int i = 0; i < s.n; i++) {
            o << s.p[i];
        }
        return o;
    }

    Store fromCategory(string &category) {
        Store tmp;
        int counter = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].getCategory() == category) {
                tmp += p[i];
                counter++;
            }
        }
        if (counter == 0) {
            throw NoProductFoundException(category);
        }
        return tmp;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {
    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    string name;
    string cat;
    int price;
    int n;

    ifstream f("input.txt");
    Product p;
    while (f >> p) {
        s += p;
    }

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream out1("output1.txt");
    out1 << s;
    out1.close();

    ofstream out2("output2.txt");
    try {
        Store tmp = s.fromCategory(category);
        out2 << tmp;
    } catch (NoProductFoundException e) {
        e.print();
    }


    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}
