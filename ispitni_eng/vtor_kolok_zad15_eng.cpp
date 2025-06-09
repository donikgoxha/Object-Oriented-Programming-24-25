#include <iostream>
#include <cstring>
using namespace std;

class Pair {
private:
    char *key;
    int value;

public:
    Pair(const char *k = "", int v = 0) {
        key = new char[strlen(k) + 1];
        strcpy(key, k);
        value = v;
    }

    Pair(const Pair &p) {
        key = new char[strlen(p.key) + 1];
        strcpy(key, p.key);
        value = p.value;
    }

    Pair &operator=(const Pair &p) {
        if (this != &p) {
            delete[] key;
            key = new char[strlen(p.key) + 1];
            strcpy(key, p.key);
            value = p.value;
        }
        return *this;
    }

    ~Pair() {
        delete[] key;
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

    Pair operator*(const Pair &p) const {
        const char *shorter = strlen(key) <= strlen(p.key) ? key : p.key;
        if (strlen(key) == strlen(p.key)) shorter = p.key;
        return Pair(shorter, value * p.value);
    }

    int getValue() const { return value; }

    friend ostream &operator<<(ostream &out, const Pair &p) {
        out << "'" << p.key << "' -> " << p.value << endl;
        return out;
    }
};

class Collection {
private:
    Pair *pairs;
    int size;

public:
    Collection() {
        pairs = nullptr;
        size = 0;
    }

    Collection(const Collection &c) {
        size = c.size;
        pairs = new Pair[size];
        for (int i = 0; i < size; ++i)
            pairs[i] = c.pairs[i];
    }

    Collection &operator=(const Collection &c) {
        if (this != &c) {
            delete[] pairs;
            size = c.size;
            pairs = new Pair[size];
            for (int i = 0; i < size; ++i)
                pairs[i] = c.pairs[i];
        }
        return *this;
    }

    ~Collection() {
        delete[] pairs;
    }

    Collection &operator+=(const Pair &p) {
        Pair *temp = new Pair[size + 1];
        for (int i = 0; i < size; ++i)
            temp[i] = pairs[i];
        temp[size++] = p;
        delete[] pairs;
        pairs = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Collection &c) {
        out << "Size: " << c.size << endl;
        for (int i = 0; i < c.size; ++i)
            out << c.pairs[i];
        return out;
    }

    bool operator<(const Collection &c) const {
        long long prod1 = 1, prod2 = 1;
        for (int i = 0; i < size; ++i) prod1 *= pairs[i].getValue();
        for (int i = 0; i < c.size; ++i) prod2 *= c.pairs[i].getValue();
        return prod1 < prod2;
    }

    int greater(int val) const {
        int count = 0;
        for (int i = 0; i < size; ++i)
            if (pairs[i].getValue() > val) count++;
        return count;
    }
};

void read(char *k, int *v) {
    cin >> k >> *v;
}


int main() {
    char key[50];
    int value;
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
