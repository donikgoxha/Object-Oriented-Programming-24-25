/*
 *link to the lesson: https://bbb-lb.finki.ukim.mk/playback/presentation/2.3/740dc1184c44f2d100ce97a5038744c4cd34f22a-1648644753777
Да се дефинира класа Word во која ќе се чуваат информации за:
Динамички алоцирана низа од знаци во која се чува содржината на зборот
Број на појавување (честота) на зборот (цел број, иницијално 1)
За класата да се имплементираат:
Потребните конструктори, деструктор, set и get методи (10)
Метод за печатење print() во формат Word: frequency (5)
Метод increaseFrequency() за зголемување на честотата за 1 (3)
Метод equals(const Word & w) за споредба дали содржината на зборот е иста со содржината на другиот збор.
При споредбата да се игнорира големината на буквите. На пример, "word" == "WoRd" се евалуира во true. (7)

Да се дефинира класа Text во која ќе се чуваат информации за:
Динамички алоцирана низа од зборови (објекти од класата Word, иницијално празна)
Големината на низата (цел број, иницијално 0).
За класата Text да се имплементираат:
Потребните конструктори, деструктор, set и get методи (10)
Метод за печатење print() што ќе ги испечати сите зборови и нивните честоти, секој во посебен ред. (5)
Метод за додавање на нов збор во текстот addWord(const Word & w). При додавање на нов збор во тексот прво
да се провери дали веќе постои збор со иста содржина. Доколку постои таков збор, потребно е само да се зголеми
честотата на зборот што веќе постои за 1. (15)
Метод getFrequencyFor(char * word) што прима збор (низа од знаци), а како резултат ја враќа фреквенцијата на тој збор.
Доколку зборот го нема во текстот, операторот треба да врати резултат -1. (10)
Get the main from down there
 */

#include <iostream>
#include <cstring>

using namespace std;

class Word {
private:
    char *content;
    int frequency;

    void copy(const Word &w) {
        this->content = new char[strlen(w.content) + 1];
        strcpy(this->content, w.content);
        this->frequency = w.frequency;
    }

public:
    Word(char *content = "", int frequency = 1) {
        this->content = new char[strlen(content) + 1];
        strcpy(this->content, content);
        this->frequency = frequency;
    }

    Word(const Word &w) {
        copy(w);
    }

    Word &operator=(const Word &w) {
        if (this != &w) {
            delete []content;
            copy(w);
        }
        return *this;
    }

    ~Word() {
        delete []content;
    }

    void print() {
        cout << content << " " << frequency << endl;
    }

    Word &increaseFrequency() {
        ++frequency;
        return *this;
    }

    int getFrequency() {
        return this->frequency;
    }

    bool equal(const Word &w) {
        if (strlen(content) != strlen(w.content)) {
            return false;
        }
        for (int i = 0; i < strlen(content); ++i) {
            if (tolower(content[i]) != tolower(w.content[i])) {
                return false;
            }
        }
        return true;
    }
};

class Text {
private:
    Word *words;
    int n;

    void copy(const Text &t) {
        this->n = t.n;
        this->words = new Word[this->n];
        for (int i = 0; i < this->n; ++i) {
            words[i] = t.words[i];
        }
    }

public:
    Text() {
        this->n = 0;
        words = new Word [0]; //initially empty
    }

    Text(const Text &t) {
        copy(t);
    }

    Text &operator=(const Text &t) {
        if (this != &t) {
            delete [] words;
            copy(t);
        }
        return *this;
    }

    void addWord(const Word &newWord) {
        for (int i = 0; i < n; ++i) {
            if (words[i].equal(newWord)) {
                words[i].increaseFrequency();
                return;
            }
        }

        Word *tmp = new Word [n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = words[i];
        }
        tmp[n++] = newWord;
        delete [] words;
        words = tmp;
    }

    void print() {
        for (int i = 0; i < this->n; ++i) {
            words[i].print();
        }
    }

    int getFrequencyFor(char *word) {
        for (int i = 0; i < n; ++i) {
            if (words[i].equal(word)) {
                return words[i].getFrequency();
            }
        }
        return -1;
    }

    ~Text() {
        delete [] words;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "TESTING WORD CONSTRUCTORS" << endl;
        Word w("OOP");
        cout << "check 1 passed" << endl;
        Word w1("OOP", 2);
        cout << "check 2 passed" << endl;
    } else if (testCase == 2) {
        cout << "TESTING WORD METHOD PRINT" << endl;
        Word w("OOP");
        w.print();
    } else if (testCase == 3) {
        cout << "TESTING WORD METHOD PRINT" << endl;
        char word[100];
        cin >> word;
        Word w(word);
        w.print();
    } else if (testCase == 4) {
        cout << "TESTING WORD COPY CONSTRUCTOR AND OPERATOR = (FOR ASSIGNMENT)" << endl;
        Word w("FINKI");
        Word w1;
        w1 = w;
        Word w2 = w1;
        w1.print();
        w2.print();
    } else if (testCase == 5) {
        cout << "TESTING WORD METHOD increaseFrequency" << endl;
        Word w("FINKI");
        int freq = w.getFrequency();
        if (freq + 1 == (w.increaseFrequency().getFrequency())) {
            cout << "increaseFrequency is implemented correctly" << endl;
        } else {
            cout << "increaseFrequency is not implemented correctly" << endl;
        }
    } else if (testCase == 6) {
        cout << "TESTING WORD METHOD equal" << endl;
        Word w("FINKI");
        Word w1("FiNkI");
        Word w2("OOP");
        cout << "FINKI" << (w.equal(w1) ? "==" : "=/=") << "FiNkI" << endl;
        cout << "FINKI" << (w.equal(w2) ? "==" : "=/=") << "OOP" << endl;
        cout << "FiNkI" << (w1.equal(w2) ? "==" : "=/=") << "OOP" << endl;
        cout << "FINKI" << (w.equal(w) ? "==" : "=/=") << "FINKI" << endl;
        cout << "FiNkI" << (w1.equal(w1) ? "==" : "=/=") << "FiNkI" << endl;
    } else if (testCase == 7) {
        cout << "TESTING TEXT, method addWord" << endl;
        Text t;
        int n;
        cin >> n;
        while (n) {
            char word[100];
            cin >> word;
            Word w(word);
            t.addWord(w);
            --n;
        }
        t.print();
    } else if (testCase == 8) {
        cout << "TESTING TEXT METHOD getFrequencyFor" << endl;
        Text t;
        t.addWord("OOP");
        t.addWord("FINKI");
        t.addWord("oop");
        t.addWord("prv");
        t.addWord("Kolokvium");
        cout << t.getFrequencyFor("OOP") << endl;
        cout << t.getFrequencyFor("prv") << endl;
        cout << t.getFrequencyFor("vtor") << endl;
    } else if (testCase == 9) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR CLASS TEXT" << endl;
        Text t;
        t.addWord("OOP");
        t.addWord("FINKI");
        t.addWord("prv");
        t.addWord("Kolokvium");
        Text t1 = t;
        Text t2;
        t2 = t1;
        t1.print();
        t2.print();
        cout << "TEST PASSED" << endl;
    }

    return 0;
}
