#include <iostream>
#include <cstring>
#include <string>
using namespace std;


class IndexOutOfBounds {
private:
    int index;
    string message;

public:
    IndexOutOfBounds(int idx) : index(idx) {
        message = "Index '" + to_string(index) + "' is out of bounds";
    }

    const string &getMessage() const {
        return message;
    }
};

class String {
private:
    char *array;
    int length;

public:
    String(const char *content) {
        length = strlen(content);
        array = new char[length];
        for (int i = 0; i < length; i++) {
            array[i] = content[i];
        }
    }

    ~String() {
        delete[] array;
    }

    char operator[](int index) const {
        if (index < 0 || index >= length) {
            throw IndexOutOfBounds(index);
        }
        return array[index];
    }

    friend class StringBuilder;
};

class StringBuilder {
private:
    char *array;
    int size;
    int capacity;

public:
    StringBuilder(int cap) : capacity(cap), size(0) {
        array = new char[capacity];
    }

    ~StringBuilder() {
        delete[] array;
    }

    StringBuilder &operator+=(const String &str) {
        int required_size = size + str.length;

        if (required_size > capacity) {
            int new_capacity = capacity * 2;
            while (new_capacity < required_size) {
                new_capacity *= 2;
            }

            char *new_array = new char[new_capacity];
            for (int i = 0; i < size; i++) {
                new_array[i] = array[i];
            }

            delete[] array;
            array = new_array;
            capacity = new_capacity;
        }

        for (int i = 0; i < str.length; i++) {
            array[size + i] = str.array[i];
        }
        size += str.length;

        return *this;
    }

    friend ostream &operator<<(ostream &os, const StringBuilder &sb) {
        os << "Capacity: " << sb.capacity << endl;
        os << "Size: " << sb.size << endl;
        os << "Contents: ";
        for (int i = 0; i < sb.size; i++) {
            os << sb.array[i];
        }
        return os;
    }
};

int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;

        cout << "s[" << x << "] = ";
        try {
            cout << s[x] << endl;
        } catch (const IndexOutOfBounds &e) {
            cout << e.getMessage() << endl;
        }

        sb += s;
    }
    cout << sb;
    return 0;
}
