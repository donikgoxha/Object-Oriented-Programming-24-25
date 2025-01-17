#include <iostream>
#include <cstring>
using namespace std;
//zad15 ispitni/kolokviumski eng

class Pair {
    char *key;
    int value;

public:
    Pair(char *key = "", int value = 0) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }

    Pair(const Pair &p) {
        this->key = new char[strlen(p.key) + 1];
        strcpy(this->key, p.key);
        this->value = p.value;
    }

    ~Pair() { delete[] key; }

    Pair &operator=(const Pair &p) {
        if (this != &p) {
            delete [] key;
            this->key = new char[strlen(p.key) + 1];
            strcpy(this->key, p.key);
            this->value = p.value;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Pair &p) {
        return out << "'" << p.key << "'" << " -> " << p.value << endl;
    }

    Pair &operator--() {
        --value;
        return *this;
    }

    Pair operator--(int) {
        Pair temp(*this);
        --value;
        return temp;
    }

    Pair operator*(const Pair &other) {
        int myKeyLength = strlen(key);
        int otherKeyLength = strlen(other.key);
        char *keyToUse;

        if (myKeyLength == otherKeyLength) {
            keyToUse = other.key;
        } else if (myKeyLength < otherKeyLength) {
            keyToUse = key;
        } else {
            keyToUse = other.key;
        }

        return Pair(keyToUse, value * other.value);
    }

    int getValue() { return value; }
};

class Collection {
protected:
    Pair **pairs;
    int size;

public:
    Collection() {
        this->pairs = nullptr;
        this->size = 0;
    }

    Collection(const Collection &c) {
        size = c.size;
        pairs = new Pair *[size];
        for (int i = 0; i < size; i++) {
            pairs[i] = new Pair(*c.pairs[i]);
        }
    }

    Collection &operator+=(const Pair &p) {
        Pair **temp = new Pair *[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = pairs[i];
        }
        temp[size++] = new Pair(p);
        delete[] pairs;
        pairs = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Collection &c) {
        out << "Size: " << c.size << endl;
        for (int i = 0; i < c.size; i++) {
            out << *c.pairs[i];
        }
        return out;
    }

    bool operator<(const Collection &other) {
        int thisProduct = 1;
        int otherProduct = 1;
        for (int i = 0; i < size; ++i) {
            thisProduct *= pairs[i]->getValue();
        }
        for (int i = 0; i < other.size; i++) {
            otherProduct *= other.pairs[i]->getValue();
        }
        return thisProduct < otherProduct;
    }

    int greater(int value) {
        int counter = 0;
        for (int i = 0; i < size; ++i) {
            if (pairs[i]->getValue() > value) {
                ++counter;
            }
        }
        return counter;
    }

    ~Collection() {
        for (int i = 0; i < this->size; i++) {
            delete this->pairs[i];
        }
        delete [] pairs;
    }
};

void read(char *k, float *v) {
    cin.getline(k, 50);
    cin.ignore();
    cin >> *v;
}

int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
    Pair p = p1 * p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator < -----" << endl;
    if (k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if (k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}
