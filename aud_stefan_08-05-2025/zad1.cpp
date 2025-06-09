#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Animal {
protected:
    string name;
    int age;

public:
    Animal(const string &name, int age) {
        this->name = name;
        this->age = age;
    }

    virtual void sound() const = 0;

    //pure virtual method, the class is abstract

    virtual void print() const {
        cout << name << " " << age << endl;
    }

    friend Animal *youngestDog(Animal **animals, int n);
};

class Cat : virtual public Animal {
public:
    Cat(const string &name, int age): Animal(name, age) {
    }

    void sound() const override {
        cout << "MJAUUUUU" << endl;
    }

    void print() const override {
        cout << "Cat: ";
        Animal::print();
    }
};

class Dog : virtual public Animal {
public:
    Dog(const string &name, int age): Animal(name, age) {
    }

    void sound() const override {
        cout << "AF AF AF AF" << endl;
    }

    void print() const override {
        cout << "Dog: ";
        Animal::print();
    }
};

Animal *youngestDog(Animal **animals, int n) {
    Animal *min = nullptr;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<Dog *>(animals[i])) {
            if (min == nullptr || animals[i]->age < min->age) {
                min = animals[i];
            }
        }
    }
    return min;
}


int main() {
    int N;
    cin >> N;

    Animal **animals = new Animal *[N];

    for (int i = 0; i < N; ++i) {
        string type, name;
        int age;
        cin >> type >> name >> age;

        if (type == "Dog") {
            animals[i] = new Dog(name, age);
        } else if (type == "Cat") {
            animals[i] = new Cat(name, age);
        } else {
            cout << "Unknown animal type!" << endl;
            --i; // retry the input for this index
            continue;
        }
    }

    for (int i = 0; i < N; ++i) {
        animals[i]->print();
        animals[i]->sound();
    }

    cout << "Youngest Dog: " << endl;
    youngestDog(animals, N)->print();


    for (int i = 0; i < N; ++i) {
        delete animals[i]; // cleanup
    }

    return 0;
}
