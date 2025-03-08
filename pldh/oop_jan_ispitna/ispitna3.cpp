#include <iostream>
#include <cstring>
using namespace std;

//zad4 ispitni/kolokviumski

enum Size { SMALL, LARGE, FAMILY };

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float basePrice;

public:
    Pizza(char *name = "", char *ingredients = "", float price = 0.0) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->basePrice = price;
    }

    virtual float getPrice() const = 0;

    float price() const {
        return getPrice();
    }

    virtual void print(ostream &out) const = 0;

    friend ostream &operator<<(ostream &out, const Pizza &p) {
        p.print(out);
        return out;
    }

    bool operator<(const Pizza &other) const {
        return getPrice() < other.getPrice();
    }

    virtual ~Pizza() {
    }
};

class FlatPizza : public Pizza {
private:
    Size size;

public:
    FlatPizza(char *name = "", char *ingredients = "", float price = 0.0, Size size = SMALL)
        : Pizza(name, ingredients, price) {
        this->size = size;
    }

    float getPrice() const override {
        float increase;
        if (size == SMALL) increase = 0.1;
        else if (size == LARGE) increase = 0.2;
        else increase = 0.3;
        return basePrice * (1 + increase);
    }

    void print(ostream &out) const override {
        out << name << ": " << ingredients << ", ";
        if (size == SMALL) out << "small";
        else if (size == LARGE) out << "large";
        else out << "family";
        out << " - " << getPrice() << endl;
    }
};

class FoldedPizza : public Pizza {
private:
    bool whiteFlour;

public:
    FoldedPizza(char *name = "", char *ingredients = "", float price = 0.0, bool whiteFlour = true)
        : Pizza(name, ingredients, price) {
        this->whiteFlour = whiteFlour;
    }

    void setWhiteFlour(bool whiteFlour) {
        this->whiteFlour = whiteFlour;
    }

    float getPrice() const override {
        if (whiteFlour) {
            return basePrice * 1.1;
        } else {
            return basePrice * 1.3;
        }
    }

    void print(ostream &out) const override {
        out << name << ": " << ingredients << ", ";
        out << (whiteFlour ? "wf" : "nwf");
        out << " - " << getPrice() << endl;
    }
};

void expensivePizza(Pizza **pizzas, int n) {
    if (n == 0) return;

    Pizza *mostExpensive = pizzas[0];
    for (int i = 1; i < n; i++) {
        if (mostExpensive->getPrice() < pizzas[i]->getPrice()) {
            mostExpensive = pizzas[i];
        }
    }
    cout << *mostExpensive;
}

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
