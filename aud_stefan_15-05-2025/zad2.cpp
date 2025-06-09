#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class StudentFailedException {
    string id;

public:
    StudentFailedException(const string &id = "") {
        this->id = id;
    }

    void showMessage() {
        cout << "Student with id " << id << " failed the course" << endl;
    }
};

class Student {
private:
    string id;
    string name;
    string lastname;
    int point;

public:
    Student(const string &id = "", const string &name = "", const string &lastname = "", int point = 0) {
        this->id = id;
        this->name = name;
        this->lastname = lastname;
        this->point = point;
    }

    int grade() const {
        if (point >= 90) {
            return 10;
        } else if (point >= 80) {
            return 9;
        } else if (point >= 70) {
            return 8;
        } else if (point >= 60) {
            return 7;
        } else if (point >= 50) {
            return 6;
        } else {
            return 5;
        }
    }

    friend ostream &operator<<(ostream &out, const Student &s) {
        out << s.id << " " << s.name << " " << s.lastname << " " << s.point << " Grade: " << s.grade();
        return out;
    }

    friend istream &operator>>(istream &in, Student &s) {
        in >> s.id >> s.name >> s.lastname >> s.point;
    }

    friend class Results;
};

class Results {
private:
    Student students[100];
    int n;

public:
    Results() {
        this->n = 0;
    }

    Results &operator+=(const Student &s) {
        if (s.grade() == 5) {
            throw StudentFailedException();
        }
        students[n++] = s;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Results &r) {
        for (int i = 0; i < r.n; i++) {
            out << r.students[i] << " ";
        }
        return out;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {
    Results results;
    ifstream in("input.txt");
    Student s;
    string id;
    string name;
    string lastname;
    int point;

    while (!in.eof()) {
        
        try {
            results += s;
        } catch (StudentFailedException &e) {
            e.showMessage();
        }
    }

    in.close();

    ofstream out("output.txt");
    out << results;
    out.close();
    return 0;
}
