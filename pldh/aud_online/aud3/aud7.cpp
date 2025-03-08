#include <iostream>
#include <cstring>

using namespace std;

// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av5.html
// https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648042101186

class String {
private:
    char *content; // dynamic allocated memory
public:
    //2in1 constructor
    String(char *cptr = "") {
        //1. allocate memory za this -> cptr
        this->content = new char[strlen(cptr) + 1];
        //2. copy content
        strcpy(this->content, cptr);
    }

    String(const String &other) {
        this->content = new char[strlen(other.content) + 1];
        strcpy(this->content, other.content);
    }

    ~String() {
        delete[] content;
    }

    String &operator=(const String &s) {
        if (this == &s) {
            //prevent self assignment
            delete [] content;
            this->content = new char[strlen(s.content) + 1];
            strcpy(this->content, s.content);
        }
        return *this;
    }
};

int main() {
    String strings[10]; //10 pati povikuvanje na default constructor

    return 0;
}
