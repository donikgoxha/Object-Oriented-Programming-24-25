// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av9.html
//pt.2: https://finkiukim-my.sharepoint.com/personal/stefan_andonov_finki_ukim_mk/_layouts/15/stream.aspx?id=%2Fpersonal%2Fstefan%5Fandonov%5Ffinki%5Fukim%5Fmk%2FDocuments%2FRecordings%2FOOP%20grupa%203%20AV11%202022%20snimki%2FOOP%20GR3%20AV11%2D20220511%5F161712%2DMeeting%20Recording%2Emp4&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2E32f1fac2%2D88b3%2D46b0%2Da463%2D7b925d216685
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

class NegativeValueException {
private:
    char productName[50];

public:
    NegativeValueException(char *name) {
        strcpy(productName, name);
    }

    void showMessage() {
        cout << "The product " << productName << " cannot have negative value for the price!" << endl;
    }
};

class Discount {
public:
    static float EUR_TO_MKD;
    static float USD_TO_MKD;

    virtual float discountPrice() = 0;

    virtual float getPrice() = 0;

    virtual void printRule() = 0;
};

class Product {
protected:
    char name[50];
    float price;

public:
    Product(char *name = "", float price = 0.0) {
        strcpy(this->name, name);
        this->price = price;
    }

    ~Product() {
    }

    void changePrice(float newPrice) {
        if (newPrice < 0) {
            throw NegativeValueException(this->name);
        }
        this->price = price;
    }
};

class FoodProduct : public Product, public Discount {
public:
    FoodProduct(char *name = "", float price = 0.0) : Product(name, price) {
    }

    float discountPrice() override {
        return price; // Fixed: removed ()
    }

    float getPrice() override {
        return price * Discount::EUR_TO_MKD;
    }

    void printRule() override {
        cout << "No discount for food products" << endl;
    }
};

class Drinks : public Product, public Discount {
private:
    bool isAlcohol;

public:
    Drinks(char *name = "", float price = 0.0, bool isAlcohol = false)
        : Product(name, price), isAlcohol(isAlcohol) {
    }

    float discountPrice() override {
        if (isAlcohol && price > 20.0) {
            return getPrice() * 0.95;
        }
        if (!isAlcohol && strcmp(name, "coca-cola") == 0) {
            return getPrice() * 0.90;
        }
        return getPrice();
    }

    float getPrice() override {
        return price * Discount::EUR_TO_MKD;
    }

    void printRule() {
        cout << "Alcohol product with getPrice larger than 20EUR -> 5%; Coca-cola 10%;" << endl;
    }
};

class Cosmetics : public Product, public Discount {
public:
    Cosmetics(char *name = "", float price = 0.0) : Product(name, price) {
    }

    float discountPrice() override {
        float priceInUSD = (price * Discount::EUR_TO_MKD) / Discount::USD_TO_MKD;
        if (priceInUSD > 20.0) {
            return getPrice() * 0.86;
        }
        if (price > 5.0) {
            return getPrice() * 0.88;
        }
        return getPrice();
    }

    float getPrice() override {
        return price * Discount::EUR_TO_MKD;
    }

    void printRule() {
        cout << "Price is USD > 20$ -> 14%; getPrice in EUR > 5EUR -> 12%" << endl;
    }
};

float Discount::EUR_TO_MKD = 61.5;
float Discount::USD_TO_MKD = 58.4;

int main() {
    int n = 0;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("leb", 0.5);
    d[n++] = new Drinks("viski", 22, true);
    d[n++] = new FoodProduct("sirenje", 6.2);
    d[n++] = new Drinks("votka", 10, true);
    d[n++] = new Cosmetics("krema", 12);
    d[n++] = new Drinks("coca-cola", 1.2, false);
    d[n++] = new Cosmetics("parfem", 60);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << endl;
        cout << d[i]->getPrice() << endl;
        cout << d[i]->discountPrice() << endl;
        d[i]->printRule();
    }

    for (int i = 0; i < n; i++) {
        Cosmetics *cosmeticsTrial = dynamic_cast<Cosmetics *>(d[i]);
        if (cosmeticsTrial != 0) {
            int newPrice;
            cin >> newPrice;
            try {
                cosmeticsTrial->changePrice(newPrice);
            }
            catch (NegativeValueException e) {
                e.showMessage();
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i + 1 << endl;
        cout << d[i]->getPrice() << endl;
        cout << d[i]->discountPrice() << endl;
        d[i]->printRule();
    }
    return 0;
}
