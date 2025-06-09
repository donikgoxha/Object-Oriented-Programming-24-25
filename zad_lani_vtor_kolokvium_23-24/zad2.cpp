#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class StudentFailedException {
private:
    string id;

public:
    StudentFailedException(const string &id = "") {
        this->id = id;
    }

    void print() const {
        cout << "Student with id " << id << " failed the course" << endl;
    }
};

class Student {
private:
    string id;
    string name;
    string surname;
    int point;

public:
    Student(const string &id = "", const string &name = "", const string &surname = "", int point = 0) {
        this->id = id;
        this->name = name;
        this->surname = surname;
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
        out << s.id << " " << s.name << " " << s.surname << " " << s.point << " Grade: " << s.grade() << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Student &s) {
        getline(in, s.id);
        getline(in, s.name);
        getline(in, s.surname);
        in >> s.point;
        in.ignore();
        return in;
    }

    friend class Results;
};

class Results {
private:
    Student *students;
    int n;

    void copy(const Results &other) {
        this->n = other.n;
        this->students = new Student[other.n];
        for (int i = 0; i < n; i++) {
            this->students[i] = other.students[i];
        }
    }

public:
    Results() {
        n = 0;
        students = nullptr;
    }

    Results(const Results &other) {
        copy(other);
    }

    Results &operator=(const Results &other) {
        if (this != &other) {
            delete[] students;
            copy(other);
        }
        return *this;
    }

    ~Results() {
        delete[] students;
    }

    Results &operator +=(const Student &s) {
        if (s.grade() == 5) {
            throw StudentFailedException(s.id);
        }
        Student *tmp = new Student[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = students[i];
        }
        tmp[n] = s;
        delete[] students;
        students = tmp;
        n++;

        return *this;
    }

    friend ostream &operator<<(ostream &out, const Results &r) {
        for (int i = 0; i < r.n; i++) {
            out << r.students[i];
        }
        return out;
    }

    Results withGrade(int grade) {
        Results r;
        for (int i = 0; i < n; i++) {
            if (students[i].grade() == grade) {
                r += students[i];
            }
        }
        return r;
    }

    int getCount() const {
        return n;
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
    wtf();

    Results results;
    //TO DO your code here
    //TO DO Read the students from the file and add them in `results`
    string id, name, surname;
    int points;
    ifstream in("input.txt");


    while (in >> id >> name >> surname >> points) {
        Student s(id, name, surname, points);
        try {
            results += s;
        } catch (StudentFailedException &e) {
            e.print();
        }
    }
    in.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TO DO Save the results in the files output1.txt and output2.txt after this line
    ofstream out1("output1.txt");
    out1 << results;
    out1.close();

    Results results2 = results.withGrade(grade);
    ofstream out2("output2.txt");
    if (results2.getCount() == 0) {
        out2 << "None" << endl;
    } else {
        out2 << results2;
    }
    out2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}
