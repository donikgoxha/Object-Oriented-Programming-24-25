#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here

enum Size { small, big, family };

class Pizza {
protected:
    char name[21];
    char ingredients[101];
    double initialPrice;

    void copy(const Pizza &p) {
        strcpy(this->name, p.name);
        strcpy(this->ingredients, p.ingredients);
        this->initialPrice = p.initialPrice;
    }

public:
    Pizza(const char *name = "", const char *ingredients = "", double initialPrice = 0.0) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->initialPrice = initialPrice;
    }

    Pizza(const Pizza &p) {
        copy(p);
    }

    Pizza &operator=(const Pizza &p) {
        if (this != &p) {
            copy(p);
        }
        return *this;
    }

    virtual ~Pizza() {
    }

    virtual double price() const = 0;

    virtual void print(ostream &out) const = 0;

    friend ostream &operator<<(ostream &out, const Pizza &p) {
        p.print(out);
        return out;
    }

    bool operator <(const Pizza &p) const {
        return this->price() < p.price();
    }
};

class FlatPizza : public Pizza {
private:
    Size size;

public:
    FlatPizza(const char *name = "", const char *ingredients = "", float basePrice = 0.0, Size size = small)
        : Pizza(name, ingredients, basePrice), size(size) {
    }

    double price() const override {
        float multiplier = 1.0;
        if (size == small) multiplier = 1.1;
        else if (size == big) multiplier = 1.2;
        else if (size == family) multiplier = 1.3;
        return initialPrice * multiplier;
    }

    void print(ostream &out) const override {
        out << name << ": " << ingredients << ", ";
        if (size == small) out << "small";
        else if (size == big) out << "big";
        else if (size == family) out << "family";
        out << " - " << price() << endl;
    }
};

class FoldedPizza : public Pizza {
private:
    bool whiteFlour;

public:
    FoldedPizza(const char *name = "", const char *ingredients = "", float basePrice = 0.0)
        : Pizza(name, ingredients, basePrice), whiteFlour(true) {
    }

    void setWhiteFlour(bool wf) {
        whiteFlour = wf;
    }

    double price() const override {
        if (whiteFlour) return initialPrice * 1.1;
        else return initialPrice * 1.3;
    }

    void print(ostream &out) const override {
        out << name << ": " << ingredients << ", ";
        out << (whiteFlour ? "wf" : "nwf") << " - " << price() << endl;
    }
};

void expensivePizza(Pizza **pizzas, int n) {
    int idx = 0;
    float maxPrice = pizzas[0]->price();
    for (int i = 1; i < n; ++i) {
        if (pizzas[i]->price() > maxPrice) {
            maxPrice = pizzas[i]->price();
            idx = i;
        }
    }
    cout << *pizzas[idx];
}


// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;
    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;
    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;
    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {
            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {
                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;
            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);
    }
    return 0;
}
