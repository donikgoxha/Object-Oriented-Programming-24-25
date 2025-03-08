#include<iostream>
#include<cstring>
using namespace std;


class Ingredient {
private:
    char *name;
    int quantity;
    int calories;

    void copy(const Ingredient &in) {
        name = new char [strlen(in.name) + 1];
        strcpy(name, in.name);
        quantity = in.quantity;
        calories = in.calories;
    }

public:
    Ingredient(char *name = "", int quantity = 0, int calories = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->quantity = quantity;
        this->calories = calories;
    }

    Ingredient(const Ingredient &in) {
        copy(in);
    }

    ~Ingredient() {
        delete []name;
    }

    int getCalories() const {
        return calories * quantity;
    }

    Ingredient &operator=(const Ingredient &in) {
        if (this != &in) {
            delete []name;
            copy(in);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Ingredient &i) {
        return out << "- " << i.name << ": " << i.quantity << "g/ml";
    }
};


class Dish {

};

int main() {
    char name[50];
    cin >> name;
    // Create Ingredients
    Ingredient tomato(name, 200, 20);
    cin >> name;
    Ingredient onion(name, 100, 30);
    cin >> name;
    Ingredient cheese(name, 50, 50);


    cin >> name;
    // Create Dishes
    Dish salad(name);
    salad += tomato;
    salad += onion;

    cin >> name;
    Dish pizza(name);
    pizza += tomato;
    pizza += cheese;

    // Test + operator
    //Dish combinedDish = salad + pizza;
    //cout << combinedDish;

    cout << "---------------------" << endl;

    //Test = operator
    Ingredient ingredient = tomato;
    cout << ingredient;
    cout << endl;

    cout << "---------------------" << endl;

    // Test == operator
    if (salad == pizza) {
        cout << "Salad and Pizza have the same calories." << endl;
    } else {
        cout << "Salad and Pizza do not have the same calories." << endl;
    }

    cout << "---------------------" << endl;

    //Test << operator
    cout << "Salad:" << endl;
    cout << salad;

    cout << "Pizza:" << endl;
    cout << pizza;

    return 0;
}
