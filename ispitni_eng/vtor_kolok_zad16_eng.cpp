#include <iostream>
#include <cstring>
using namespace std;

// Your code here
class Pair {
private:
    char *key;
    double value;

public:
    Pair(const char *k = "", double v = 0.0) {
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

    Pair &operator++() {
        ++value;
        return *this;
    }

    Pair operator++(int) {
        Pair temp(*this);
        ++value;
        return temp;
    }

    Pair operator+(const Pair &p) const {
        const char *longer = strlen(key) >= strlen(p.key) ? key : p.key;
        if (strlen(key) == strlen(p.key)) longer = key;
        return Pair(longer, value + p.value);
    }

    const char *getKey() const { return key; }
    double getValue() const { return value; }

    friend ostream &operator<<(ostream &out, const Pair &p) {
        out << "('" << p.key << "', " << p.value << ")" << endl;
        return out;
    }

    bool operator==(const Pair &p) const {
        return strcmp(key, p.key) == 0 && value == p.value;
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

    bool operator==(const Collection &c) const {
        if (size != c.size) return false;
        for (int i = 0; i < size; ++i)
            if (!(pairs[i] == c.pairs[i])) return false;
        return true;
    }

    Pair *find(const char *key) {
        for (int i = 0; i < size; ++i)
            if (strcmp(pairs[i].getKey(), key) == 0)
                return &pairs[i];
        return nullptr;
    }
};


void read(char *k, float *v) {
    cin >> k;
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
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
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
    cout << "----- operator == -----" << endl;
    if (k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if (k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair *f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if (f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}
