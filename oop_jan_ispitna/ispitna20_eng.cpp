#include <iostream>
#include <cstring>
class CharSequence;
using namespace std;
//zad3 ispitni/kolokviumski eng


class Character {
private:
    char c;

public:
    Character(char c = '\0') : c(c) {
    }

    void setChar(char newC) { c = newC; }
    char getChar() const { return c; }


    bool operator==(const Character &other) const {
        return c == other.c;
    }

    friend ostream &operator<<(ostream &out, const Character &character) {
        out << character.c;
        return out;
    }

    Character &operator=(char newC) {
        c = newC;
        return *this;
    }
};

class CharSequence {
private:
    Character *array;
    int length;

    void copy(const CharSequence &other) {
        length = other.length;
        array = new Character[length];
        for (int i = 0; i < length; i++) {
            array[i] = other.array[i];
        }
    }

public:
    CharSequence() {
        length = 0;
        array = nullptr;
    }

    CharSequence(const char *str) {
        length = strlen(str);
        array = new Character[length];
        for (int i = 0; i < length; i++) {
            array[i] = Character(str[i]);
        }
    }

    CharSequence(const CharSequence &other) {
        copy(other);
    }

    ~CharSequence() {
        delete[] array;
    }

    CharSequence &operator=(const CharSequence &other) {
        if (this != &other) {
            delete[] array;
            copy(other);
        }
        return *this;
    }

    Character &operator[](int index) {
        return array[index];
    }

    const Character &operator[](const int index) const {
        return array[index];
    }

    CharSequence &operator+=(const Character &c) {
        Character *temp = new Character[length + 1];
        for (int i = 0; i < length; i++) {
            temp[i] = array[i];
        }
        temp[length] = c;
        delete[] array;
        array = temp;
        length++;
        return *this;
    }

    bool operator==(const CharSequence &cs) const {
        if (length != cs.length) return false;
        for (int i = 0; i < length; i++) {
            if (!(array[i] == cs.array[i])) return false;
        }
        return true;
    }

    int operator[](char c) const {
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (array[i].getChar() == c) count++;
        }
        return count;
    }

    CharSequence toUpperCase() const {
        CharSequence result;
        result.length = length;
        result.array = new Character[length];
        for (int i = 0; i < length; i++) {
            result.array[i] = Character(toupper(array[i].getChar()));
        }
        return result;
    }

    friend ostream &operator<<(ostream &out, const CharSequence &cs) {
        for (int i = 0; i < cs.length; i++) {
            out << cs.array[i];
        }
        return out;
    }
};


int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if (n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if (n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for (int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if (n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs(
            "If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if (n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if (n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}
