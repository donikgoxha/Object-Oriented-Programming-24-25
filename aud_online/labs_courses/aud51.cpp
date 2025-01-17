#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class InvalidOperation {
public:
    const char *what() const throw() {
        return "Conference duration exceeded";
    }
};

class Speaker {
private:
    string name;
    string presentation;
    int duration;

public:
    Speaker(string name = "", string presentation = "", int duration = 0) {
        this->name = name;
        this->presentation = presentation;
        this->duration = duration;
    }

    string getName() const {
        return name;
    }

    string getPresentation() const {
        return presentation;
    }

    int getDuration() const {
        return duration;
    }

    void setName(string name) {
        this->name = name;
    }

    void setPresenation(string presentation) {
        this->presentation = presentation;
    }

    int getDuration() {
        return this->duration;
    }


    friend ostream &operator<<(ostream &out, const Speaker &speaker) {
        return out << speaker.name << " - " << speaker.presentation << ", " << speaker.duration;
    }
};

class Conference {
private:
    static int MAXDURATION;
    string code;
    string date;
    vector<Speaker> speakers;

public:
    Conference() = default;

    Conference(string code, string date) {
        this->code = code;
        this->date = date;
    }

    Conference(const Conference &other) {
        code = other.code;
        date = other.date;
        speakers = other.speakers;
    }

    Conference &operator=(const Conference &other) {
        if (this != &other) {
            code = other.code;
            date = other.date;
            speakers = other.speakers;
        }
        return *this;
    }

    string getCode() const {
        return code;
    }

    string getDate() const {
        return date;
    }

    void setCode(string code) {
        this->code = code;
    }

    void setDate(string date) {
        this->date = date;
    }

    static void setMaxDuration(int duration) {
        MAXDURATION = duration;
    }

    static int getMaxDuration() {
        return MAXDURATION;
    }

    Conference &operator+=(const Speaker &speaker) {
        int total_duration = 0;
        for (const Speaker &s: speakers) {
            total_duration += s.getDuration();
        }
        if (total_duration + speaker.getDuration() > MAXDURATION) {
            throw InvalidOperation();
        }
        speakers.push_back(speaker);
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Conference &conf) {
        return out << conf.code << " - " << conf.date << ", " << conf.speakers.size();
    }

    bool operator>(const Conference &other) const {
        return speakers.size() > other.speakers.size();
    }

    bool operator==(const Conference &other) const {
        return date == other.date;
    }

    void longestPresentation() const {
        if (speakers.empty()) return;

        const Speaker *longest = &speakers[0];
        for (const Speaker &s: speakers) {
            if (s.getDuration() > longest->getDuration()) {
                longest = &s;
            }
        }
        cout << "Longest Presentation: " << *longest << endl;
    }
};

int Conference::MAXDURATION = 360;

int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0) {
        cout << "Speaker constructor" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "Speaker copy-constructor and operator=" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Speaker c1 = speaker2;
        Speaker c3;
        c3 = speaker2;
        cout << c3 << endl;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "Speaker operator print" << endl;
        Speaker speaker1("Aleksandar Stojmenski", "Introduction to C++", 60);
        Speaker speaker2("Stefan Andonov", "Object-Oriented Programming", 120);
        Speaker speaker3("Boban Joksimoski", "Computer Animation", 180);
        cout << speaker1 << endl;
        cout << speaker2 << endl;
        cout << speaker3 << endl;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 3) {
        cout << "Conference class" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference conference("CONF001", "2023-07-01");
        conference += speaker1;
        conference += speaker2;
        conference += speaker3;

        cout << conference << endl;
    } else if (testCase == 4) {
        cout << "Conference constructors" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference c("CONF001", "2023-07-01");
        c += speaker1;
        c += speaker2;
        Conference c1, c2 = c;
        c1 = c;
        c2 += speaker3;
        cout << c1 << endl;
        cout << c2 << endl;
    } else if (testCase == 5) {
        cout << "Conference operator> constructors" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);

        Conference c("CONF001", "2023-07-01");
        c += speaker1;
        c += speaker2;
        Conference c1, c2 = c;
        c2 += speaker3;
        if (c2 > c) {
            cout << "PASSED" << endl;
        }
    } else if (testCase == 6) {
        cout << "longestPresentation and comparison" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        Conference conference("CONF001", "2023-07-01");

        conference += speaker1;
        conference += speaker2;
        conference += speaker3;

        cout << "Conference: " << conference << endl;

        conference.longestPresentation();

        // Test case for comparison operators
        Conference conference2("CONF002", "2023-07-01");
        conference2 += speaker1;
        conference2 += speaker2;

        if (conference > conference2) {
            cout << "CONF001 has more speakers than CONF002." << endl;
        } else {
            cout << "CONF001 has fewer speakers than CONF002." << endl;
        }

        // Test case for exceeding duration limit
        Speaker speaker4("Sarah Adams", "Advanced C++ Programming", 240);
    } else if (testCase == 7) {
        cout << "Exception handling" << endl;
        cout << "longestPresentation and comparison" << endl;
        Speaker speaker1("John Doe", "Introduction to C++", 60);
        Speaker speaker2("Jane Smith", "Object-Oriented Programming", 120);
        Speaker speaker3("David Johnson", "Data Structures and Algorithms", 180);
        Conference conference("CONF001", "2023-07-01");
        conference += speaker1;
        conference += speaker2;
        conference += speaker3;
        Conference conference2("CONF002", "2023-07-01");
        conference2 += speaker1;
        conference2 += speaker2;
        if (conference > conference2) {
            cout << "CONF001 has more speakers than CONF002." << endl;
        } else {
            cout << "CONF001 has fewer speakers than CONF002." << endl;
        }
        Speaker speaker4("Sarah Adams", "Advanced C++ Programming", 240);
        try {
            conference += speaker4;
        } catch (InvalidOperation &e) {
            cout << e.what() << endl;
        }
    } else if (testCase == 8) {
        Conference conference4("CONF004", "2023-07-01");
        Conference conference5("CONF005", "2023-07-01");

        Speaker speaker9("Alex Turner", "Network Security", 120);
        Speaker speaker10("Olivia Parker", "Artificial Intelligence", 180);

        conference4 += speaker9;
        conference5 += speaker10;

        cout << "Conference 4: " << conference4 << endl;
        cout << "Conference 5: " << conference5 << endl;

        if (conference4 == conference5) {
            cout << "Conference 4 and Conference 5 have the same date." << endl;
        } else {
            cout << "Conference 4 and Conference 5 have different dates." << endl;
        }
    } else if (testCase == 9) {
        Conference conference3("CONF003", "2023-07-01");

        Conference::setMaxDuration(1000);
        Speaker speaker5("Michael Brown", "Web Development", 180);
        Speaker speaker6("Emily Davis", "Machine Learning", 240);
        Speaker speaker7("Robert Wilson", "Software Engineering", 120);

        conference3 += speaker5;
        conference3 += speaker6;
        conference3 += speaker7;

        cout << "Conference 3: " << conference3 << endl;

        Speaker speaker8("Jessica Lee", "Database Management", 180);


        conference3 += speaker8;
        cout << conference3;
    }
    return 0;
}
