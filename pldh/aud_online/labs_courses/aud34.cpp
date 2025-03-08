#include <iostream>
#include <cstring>

using namespace std;

class Product {
private:
    char name[100];
    int id;
    char category[100];
    double price;
    int quantity;

public:
    Product(const char *name = "", int id = 0, const char *category = "", double price = 0, int quantity = 0) {
        strcpy(this->name, name);
        this->id = id;
        strcpy(this->category, category);
        this->price = price;
        this->quantity = quantity;
    }

    int getID() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    const char *getName() const {
        return name;
    }

    void setName(const char *n) {
        strncpy(name, n, 99);
        name[99] = '\0';
    }

    const char *getCategory() const {
        return category;
    }

    void setCategory(const char *s) {
        strncpy(category, s, 99);
        category[99] = '\0';
    }

    void print() {
        cout << "Name: " << getName() << ", " << "Id: " << getID() << ", " << "Price: " << getPrice() << ", " <<
                "Quantity: " << getQuantity() << endl;
    }
};

void printByCategory(Product *products, int n, const char *category) {
    double totalSum = 0;
    bool found = false;

    cout << "Category: " << category << endl;

    for (int i = 0; i < n; i++) {
        if (strcmp(products[i].getCategory(), category) == 0) {
            products[i].print();
            totalSum += products[i].getPrice() * products[i].getQuantity();
            found = true;
        }
    }

    if (found) {
        cout << "Total sum : " << totalSum << endl;
    } else {
        cout << "No products in category " << category << "!" << endl;
    }
}

int main() {
    int m;
    cin >> m;
    if (m == 0) {
        cout << "---Testing constructor with arguments and print()---" << "\n";
        char name[100] = {'B', 'o', 'o', 'k', '\0'};
        int id = 1;
        char category[100] = {'B', 'o', 'o', 'k', 's', '\0'};
        double price = 14.99;
        int quantity = 3;

        Product products(name, id, category, price, quantity);
        products.print();
    } else if (m == 1) {
        cout << "---Testing get and set methods---" << "\n";
        char name[100] = {'B', 'o', 'o', 'k', '\0'};
        int id = 1;
        char category[100] = {'B', 'o', 'o', 'k', 's', '\0'};
        double price = 14.99;
        int quantity = 3;
        Product product;
        product.setName(name);
        product.setId(id);
        product.setCategory(category);
        product.setPrice(price);
        product.setQuantity(quantity);
        cout << "Name: " << product.getName() << endl;
        cout << "Id: " << product.getID() << endl;
        cout << "Category: " << product.getCategory() << endl;
        cout << "Price: " << product.getPrice() << endl;
        cout << "Quantity: " << product.getQuantity() << endl;
    } else if (m == 2) {
        const int numProducts = 8;
        Product products[numProducts];
        for (int i = 0; i < numProducts; ++i) {
            char name[100];
            int id;
            char category[100];
            double price;
            int quantity;

            cin >> name >> id >> category >> price >> quantity;
            products[i] = Product(name, id, category, price, quantity);
        }


        cout << "---Testing function---" << "\n";
        printByCategory(products, numProducts, "Electronics");
        cout << endl;
        printByCategory(products, numProducts, "Clothing");
        cout << endl;
        printByCategory(products, numProducts, "Books");
    }
    return 0;
}
