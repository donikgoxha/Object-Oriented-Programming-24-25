#include <iostream>

using namespace std;

class Product {
protected:
    string id;
    float price;

public:
    Product(string id = "PROD-123456", float price = 10.0) : id(id), price(price) {
    }

    ~Product() {
    }

    void print() {
        cout << id << " " << price << " ";
    }
};

class DiscountProduct : public Product {
private:
    int discount;

public:
    DiscountProduct(string id = "PROD-123456", float price = 10.0, int discount = 10) : Product(id, price) {
        if (discount > 0 && discount < 100) {
            this->discount = discount;
        } else {
            this->discount = 10;
        }
    }

    float calculatePrice() {
        return price * (100 - discount) / 100;
    }


    void print() {
        Product::print();
        cout << discount << endl;
    }
};


DiscountProduct *createDicsProducts(int n) {
    DiscountProduct *discProducts = new DiscountProduct[n];
    string id;
    float price;
    int disc;
    for (int i = 0; i < n; i++) {
        cin >> id >> price >> disc;
        discProducts[i] = DiscountProduct(id, price, disc);
    }
    return discProducts;
}


int main() {
    int testCase;
    cin >> testCase;

    switch (testCase) {
        case 1: {
            DiscountProduct discountProduct;
            discountProduct.print();
            break;
        }
        case 2: {
            DiscountProduct discountProduct("CS101", 50, 5);
            discountProduct.print();
            DiscountProduct discountProduct1("CS102", 70, 10);
            discountProduct1.print();
            break;
        }
        case 3: {
            DiscountProduct discountProduct("CS101", 50, 105);
            discountProduct.print();
            DiscountProduct discountProduct1("CS102", 70, 0);
            discountProduct1.print();
            break;
        }
        case 4: {
            DiscountProduct discountProduct("CS101", 40, 20);
            cout << discountProduct.calculatePrice();
            break;
        }
        case 5: {
            int n;
            cin >> n;
            DiscountProduct *discountProducts = createDicsProducts(n);
            for (int i = 0; i < n; i++) {
                discountProducts[i].print();
            }
            delete [] discountProducts;
            break;
        }
        default: {
            int n;
            cin >> n;

            DiscountProduct *discountProducts = createDicsProducts(n);
            for (int i = 0; i < n; i++) {
                discountProducts[i].print();
            }
            for (int i = 0; i < n; i++) {
                cout << discountProducts[i].calculatePrice() << endl;
            }
            delete [] discountProducts;
            break;
        }
    }
}
