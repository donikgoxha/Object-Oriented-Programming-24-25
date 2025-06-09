#include <iostream>
#include <cstring>
using namespace std;

// your code here
class Character {
private:
    char ch;

public:
    // Constructor
    Character(char c = '\0') : ch(c) {
    }

    // Getter for the character
    char getChar() const {
        return ch;
    }

    // Setter for the character
    void setChar(char c) {
        ch = c;
    }

    // Overload << operator for printing
    friend ostream &operator<<(ostream &os, const Character &cc) {
        os << cc.ch;
        return os;
    }

    // Overload == operator for comparing two Character objects
    bool operator==(const Character &other) const {
        return ch == other.ch;
    }
};

// CharSequence class
class CharSequence {
private:
    Character *sequence;
    int length;

public:
    // Default constructor
    CharSequence() : sequence(nullptr), length(0) {
    }

    // Constructor from a C-string
    CharSequence(const char *str) {
        length = strlen(str);
        sequence = new Character[length];
        for (int i = 0; i < length; ++i) {
            sequence[i] = Character(str[i]);
        }
    }

    // Copy constructor
    CharSequence(const CharSequence &other) {
        length = other.length;
        sequence = new Character[length];
        for (int i = 0; i < length; ++i) {
            sequence[i] = other.sequence[i];
        }
    }

    // Destructor
    ~CharSequence() {
        delete[] sequence;
    }

    // Assignment operator
    CharSequence &operator=(const CharSequence &other) {
        if (this != &other) {
            delete[] sequence;
            length = other.length;
            sequence = new Character[length];
            for (int i = 0; i < length; ++i) {
                sequence[i] = other.sequence[i];
            }
        }
        return *this;
    }

    // Overload [] operator for accessing the i-th element
    Character &operator[](int i) {
        if (i < 0 || i >= length) {
            throw out_of_range("Index out of range");
        }
        return sequence[i];
    }

    // Overload += operator for adding a new Character object
    CharSequence &operator+=(const Character &c) {
        Character *newSequence = new Character[length + 1];
        for (int i = 0; i < length; ++i) {
            newSequence[i] = sequence[i];
        }
        newSequence[length] = c;
        delete[] sequence;
        sequence = newSequence;
        ++length;
        return *this;
    }

    // Overload == operator for comparing two CharSequence objects
    bool operator==(const CharSequence &other) const {
        if (length != other.length) {
            return false;
        }
        for (int i = 0; i < length; ++i) {
            if (!(sequence[i] == other.sequence[i])) {
                return false;
            }
        }
        return true;
    }

    // Method to count occurrences of a character
    int count(char c) const {
        int count = 0;
        for (int i = 0; i < length; ++i) {
            if (sequence[i].getChar() == c) {
                ++count;
            }
        }
        return count;
    }

    // Convert all characters to uppercase
    CharSequence toUpperCase() const {
        CharSequence result;
        for (int i = 0; i < length; ++i) {
            char upperChar = toupper(sequence[i].getChar());
            result += Character(upperChar);
        }
        return result;
    }

    // Overload << operator for printing
    friend ostream &operator<<(ostream &os, const CharSequence &cs) {
        for (int i = 0; i < cs.length; ++i) {
            os << cs.sequence[i];
        }
        return os;
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
        cout << cs.count('e') << endl;
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
