// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av8.html

// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1651063530889
#include <iostream>
#include <cstring>
using namespace std;

class Animal {
protected:
    char name[30];

public:
    Animal(char *name) {
        strcpy(this->name, name);
    }

    virtual void makeSound() = 0;
};

class Dog : public Animal {
public:
    Dog(char *name) : Animal(name) {
    }

    void makeSound() {
        cout << name << " is making the sound woof woof!" << endl;
    }
};

class Cat : public Animal {
public:
    Cat(char *name) : Animal(name) {
    }

    void makeSound() {
        cout << name << " is making the sound meow meow!" << endl;
    }
};


int main() {
    // Animal **animals = new Animal *[3];
    //
    // animals[0] = new Animal("simba");
    // //a->makeSound();
    //
    // animals[1] = new Dog("goo");
    // //goo->makeSound();
    //
    // animals[2] = new Cat("cat");
    // //cat->makeSound();
    //
    // for (int i = 0; i < 3; i++) {
    //     animals[i]->makeSound();
    // }

    int n;
    cin >> n;

    Animal **animals = new Animal *[n];

    for (int i = 0; i < n; i++) {
        int type;
        char name[30];
        cin >> type >> name;
        if (type == 1) {
            animals[i] = new Dog(name);
        } else {
            animals[i] = new Cat(name);
        }
    }

    for (int i = 0; i < n; i++) {
        animals[i]->makeSound();
    }
    return 0;
}
