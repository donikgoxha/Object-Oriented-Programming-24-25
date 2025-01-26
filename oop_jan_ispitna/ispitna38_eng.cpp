#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class StudentFailedException : public exception {
public:
    const char *what() const noexcept override {
        return "Student failed the course";
    }
};

class Student {
protected:
    string indeks;
    string name;
    string lastName;
    int examPoints;

public:
    Student(const string &indeks, const string &name, const string &last_name, int exam_points)
        : indeks(indeks),
          name(name),
          lastName(last_name),
          examPoints(exam_points) {
    }

    int grade() const {
        if (examPoints < 50) return 5;
        if (examPoints < 60) return 6;
        if (examPoints < 70) return 7;
        if (examPoints < 80) return 8;
        if (examPoints < 90) return 9;
        return 10;
    }

    friend ostream &operator<<(ostream &out, const Student &s) {
        return out << s.indeks << " " << s.name << " " << s.lastName << " " << s.examPoints << " Grade: " << s.grade()
               << endl;
    }

    string getIndeks() const {
        return indeks;
    }

    int getExamPoints() const {
        return examPoints;
    }
};

class Results {
    Student **students;
    int size;

public:
    Results()
        : students(nullptr),
          size(0) {
    }

    ~Results() {
        for (int i = 0; i < size; i++) {
            delete students[i];
        }
        delete[] students;
    }

    void operator+=(const Student &s) {
        if (s.getExamPoints() < 50) {
            throw StudentFailedException();
        }
        Student **temp = new Student *[size + 1];
        for (int i = 0; i < size; i++) {
            temp[i] = students[i];
        }
        temp[size] = new Student(s);
        delete[] students;
        students = temp;
        size++;
    }

    Results withGrade(int grade) {
        Results result;
        for (int i = 0; i < size; i++) {
            if (students[i]->grade() == grade) {
                result += *students[i];
            }
        }
        return result;
    }

    friend ostream &operator<<(ostream &out, const Results &r) {
        if (r.size == 0) {
            out << "None" << endl;
        }
        for (int i = 0; i < r.size; i++) {
            out << *r.students[i];
        }
        return out;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(cin, line)) {
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

    ifstream fin("input.txt");
    string index, first, last;
    int points;

    while (fin >> index >> first >> last >> points) {
        try {
            Student student(index, first, last, points);
            results += student;
        } catch (StudentFailedException &e) {
            cout << "Student with id " << index << " failed the course" << endl;
        }
    }

    int grade;
    cin >> grade;

    ofstream fout("output1.txt");
    //fout << "All students: " << endl;
    fout << results;

    Results gradeResults = results.withGrade(grade);
    ofstream fout2("output2.txt");
    //fout2 << "Grade report for grade " << grade << ":" << endl;
    fout2 << gradeResults;

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");

    return 0;
}
