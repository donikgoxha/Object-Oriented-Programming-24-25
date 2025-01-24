#include <iostream>
#include <cstring>
using namespace std;

// your code here
class Word {
private:
    char *word;

    void copy(const Word &w) {
        word = new char[strlen(w.word) + 1];
        strcpy(word, w.word);
    }

public:
    Word(const char *w = "UNDEFINED") {
        word = new char[strlen(w) + 1];
        strcpy(word, w);
    }

    Word(const Word &w) {
        copy(w);
    }

    Word &operator=(const Word &w) {
        if (this != &w) {
            delete[] word;
            copy(w);
        }
        return *this;
    }

    ~Word() {
        delete[] word;
    }

    void print() {
        cout << word;
    }
};

class Sentence {
private:
    Word *words;
    int numWords;
    int capacity;

    void reSize() {
        Word *tmp = new Word[capacity + 10];
        for (int i = 0; i < numWords; ++i) {
            tmp[i] = words[i];
        }
        delete[] words;
        words = tmp;
        capacity += 10;
    }

public:
    Sentence(int cap = 10) {
        capacity = cap;
        numWords = 0;
        words = new Word[capacity];
    }

    Sentence(const Sentence &s) {
        capacity = s.capacity;
        numWords = s.numWords;
        words = new Word[capacity];
        for (int i = 0; i < numWords; ++i) {
            words[i] = s.words[i];
        }
    }

    ~Sentence() {
        delete[] words;
    }

    void add(const Word &w) {
        if (numWords == capacity) {
            reSize();
        }
        words[numWords++] = w;
    }

    void print() {
        for (int i = 0; i < numWords; ++i) {
            words[i].print();
            if (i < numWords - 1) cout << " ";
        }
        cout << endl;
    }

    void swap(int i, int j) {
        if (i >= 0 && i < numWords && j >= 0 && j < numWords) {
            Word tmp = words[i];
            words[i] = words[j];
            words[j] = tmp;
        }
    }
};


int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SWAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}
