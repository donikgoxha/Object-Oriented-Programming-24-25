// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av5.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648042101186

#include<iostream>

using namespace std;

class Array {
private:
    int *content;
    int capacity;
    int size;

    void copy(const Array &other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->content = new int[this->capacity];
        //strcpy(this->content, other.content)
        for (int i = 0; i < this->size; i++) {
            this->content[i] = other.content[i];
        }
    }

public:
    Array(int capacity = 10) {
        this->capacity = capacity;
        this->content = new int[capacity];
        this->size = 0;
    }

    Array(const Array &other) {
        copy(other);
    }

    Array &operator=(const Array &other) {
        if (this != &other) {
            delete[] content;
            copy(other);
        }
        return *this;
    }

    ~Array() {
        delete[] content;
    }

    void add(int number) {
        if (size < capacity) {
            content[size++] = number;
        } else {
            //1. move all elements and the new element in a temp content
            capacity *= 2;
            int *tmp = new int[capacity];
            for (int i = 0; i < size; i++) {
                tmp[i] = content[i];
            }
            tmp[size++] = number;
            delete[] content;
            content = tmp;
        }
    }

    void change(int a, int b) {
        for (int i = 0; i < size; i++) {
            if (content[i] == a) {
                content[i] = b;
            }
        }
    }

    int countOccurrences(int number) {
        int counter = 0;
        for (int i = 0; i < size; i++) {
            if (content[i] == number) {
                ++counter;
            }
        }
        return counter;
    }

    void deleteAll(int number) {
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (content[i] != number) {
                content[j++] = content[i];
            }
        }

        this->size = j;
    }

    void print() {
        cout << "Capacity: " << capacity << endl;
        cout << "Size: " << size << endl;
        cout << "Percentage filled: " << (100.0 * size) / capacity << "%" << endl;
        for (int i = 0; i < size; i++) {
            if (i != size - 1) {
                cout << content[i] << ", ";
            } else {
                cout << content[i];
            }
        }
        cout << endl;
    }


};

int main() {
    Array a;
    a.print();
    for (int i = 0; i < 10; i++) {
        a.add(i);
    }
    cout << "--------" << endl;
    a.print();
    cout << "--------" << endl;
    a.add(1);
    a.print();
    for (int i = 1; i <= 10; i++) {
        a.add(i);
    }
    cout << "--------" << endl;
    a.print();
    cout << "--------" << endl;
    a.change(2, 1);
    a.print();
    cout << "--------" << endl;
    a.deleteAll(1);
    a.print();
    return 0;
}