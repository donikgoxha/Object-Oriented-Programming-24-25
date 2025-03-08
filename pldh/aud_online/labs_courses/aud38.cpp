#include<iostream>
#include<cstring>
using namespace std;

class Ingredient {
private:
    char *name;
    double quantity;
    double calories;

    void copy(const Ingredient &i) {
        name = new char[strlen(i.name) + 1];
        strcpy(name, i.name);
        quantity = i.quantity;
        calories = i.calories;
    }

public:
    //Ingredient() = default;

    Ingredient(const char *name = "", double quantity = 0.0, double calories = 0.0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        this->quantity = quantity;
        this->calories = calories;
    }

    Ingredient(const Ingredient &i) {
        copy(i);
    }

    double getTotalCalories() const {
        return quantity * calories;
    }

    Ingredient &operator=(const Ingredient &i) {
        if (this != &i) {
            delete[] name;
            copy(i);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Ingredient &i) {
        return out << i.name << ": " << i.quantity;
    }

    ~Ingredient() {
        delete [] name;
    }
};

class Dish {
private:
    Ingredient *ingredients;
    char *dishName;
    int ingredientCount;

    void copy(const Dish &d) {
        dishName = new char[strlen(d.dishName) + 1];
        strcpy(dishName, d.dishName);
        ingredientCount = d.ingredientCount;
        ingredients = new Ingredient[ingredientCount];
        for (int i = 0; i < ingredientCount; i++) {
            ingredients[i] = d.ingredients[i];
        }
    }

public:
    //Dish() = default;

    Dish(const char *name = "") {
        dishName = new char[strlen(name) + 1];
        strcpy(dishName, name);
        ingredients = nullptr;
        ingredientCount = 0;
    }

    Dish(const Dish &d) {
        copy(d);
    }

    ~Dish() {
        delete[] dishName;
        delete [] ingredients;
    }

    double getTotalCalories() const {
        double total = 0;
        for (int i = 0; i < ingredientCount; i++) {
            total += ingredients[i].getTotalCalories();
        }
        return total;
    }

    Dish operator+(const Dish &other) const {
        Dish result(this->dishName);
        result.ingredientCount = this->ingredientCount + other.ingredientCount;
        result.ingredients = new Ingredient[result.ingredientCount];

        for (int i = 0; i < this->ingredientCount; i++) {
            result.ingredients[i] = this->ingredients[i];
        }
        for (int i = 0; i < other.ingredientCount; i++) {
            result.ingredients[this->ingredientCount + i] = other.ingredients[i];
        }
        return result;
    }

    Dish &operator+=(const Ingredient &ing) {
        Ingredient *temp = new Ingredient[ingredientCount + 1];
        for (int i = 0; i < ingredientCount; i++) {
            temp[i] = ingredients[i];
        }
        temp[ingredientCount] = ing;
        delete[] ingredients;
        ingredients = temp;
        ingredientCount++;
        return *this;
    }

    bool operator==(const Dish &other) const {
        return getTotalCalories() == other.getTotalCalories();
    }

    friend ostream &operator<<(ostream &out, const Dish &dish) {
        out << "Dish: " << dish.dishName << endl;
        for (int i = 0; i < dish.ingredientCount; i++) {
            out << "- " << dish.ingredients[i] << "g/ml" << endl;
        }
        out << "Total Calories: " << dish.getTotalCalories() << endl;
        return out;
    }
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
    const Dish combinedDish = salad + pizza;
    cout << combinedDish;

    cout << "---------------------" << endl;

    //Test = operator
    Ingredient ingredient = tomato;
    cout << ingredient<< "g/ml";
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
