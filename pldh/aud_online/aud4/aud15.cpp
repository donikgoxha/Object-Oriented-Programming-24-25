// Links to the lessons
// https://finki-mk.github.io/OOP/html5/oop_av6.html

// pt.2: https://finkiukim-my.sharepoint.com/personal/stefan_andonov_finki_ukim_mk/_layouts/15/stream.aspx?id=%2Fpersonal%2Fstefan%5Fandonov%5Ffinki%5Fukim%5Fmk%2FDocuments%2FRecordings%2FOOP%20grupa%203%20AV%207%202022%20snimki%2FOOP%20grupa%203%20AV%207%2D20220413%5F160714%2DMeeting%20Recording%2Emp4&referrer=StreamWebApp%2EWeb&referrerScenario=AddressBarCopied%2Eview%2E0bb21581%2D5bb3%2D47bb%2Daa79%2D84a0a0e24ba0

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class Student {
private:
    char *name;
    int *grades;
    int nGrades;
    int year;

    void copy(const Student &s) {
        this->name = new char [strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->nGrades = s.nGrades;
        grades = new int[this->nGrades];
        for (int i = 0; i < this->nGrades; i++) {
            this->grades[i] = s.grades[i];
        }
        this->year = s.year;
    }

public:
    Student(char *name = "", int year = 2001) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        nGrades = 0;
        grades = new int[0];
        this->year = year;
    }

    Student(const Student &s) {
        copy(s);
    }

    Student &operator=(const Student &s) {
        if (this != &s) {
            delete[] name;
            delete[] grades;
            copy(s);
        }
        return *this;
    }

    ~Student() {
        delete[] name;
        delete[] grades;
    }

    //prefix
    Student &operator++() {
        ++year;
        return *this;
    }

    //postfix
    Student operator++(int) {
        Student result(*this);
        ++year;
        return result;
    }

    Student &operator+=(int grade) {
        int *tmp = new int[nGrades + 1];
        for (int i = 0; i < nGrades; i++) {
            tmp[i] = grades[i];
        }
        tmp[nGrades++] = grade;
        delete[] grades;
        grades = tmp;
        return *this;
    }

    double getAverage() const {
        if (nGrades == 0) {
            return 5.0;
        }
        double sum = 0;
        for (int i = 0; i < nGrades; i++) {
            sum += grades[i];
        }
        return sum / nGrades;
    }

    friend ostream &operator<<(ostream &out, const Student &s) {
        out << s.name << " " << s.year << " " << s.getAverage() << endl;
        return out;
    }

    bool operator>(Student &student) {
        return this->getAverage() > student.getAverage();
    }
};

class Faculty {
private:
    Student *students;
    int nStudents;

    void copy(const Faculty &f) {
        this->nStudents = f.nStudents;
        students = new Student[this->nStudents];
        for (int i = 0; i < this->nStudents; i++) {
            students[i] = f.students[i];
        }
    }

public:
    Faculty() {
        nStudents = 0;
        students = new Student[0];
    }

    Faculty(Student &student) {
        copy(student);
    }

    Faculty &operator=(const Faculty &f) {
        if (this != &f) {
            delete[] students;
            copy(f);
        }
        return *this;
    }

    ~Faculty() {
        delete[] students;
    }

    Faculty &operator+=(const Student &newStudent) {
        Student *tmp = new Student[nStudents + 1];
        for (int i = 0; i < nStudents; i++) {
            tmp[i] = students[i];
        }
        tmp[nStudents++] = newStudent;
        delete[] students;
        students = tmp;
        return *this;
    }

    Faculty &operator++() {
        for (int i = 0; i < nStudents; i++) {
            ++students[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Faculty &f) {
        for (int i = 0; i < f.nStudents; i++) {
            out << f.students[i];
        }
        return out;
    }

    void prize() {
        for (int i = 0; i < nStudents; i++) {
            if (students[i].getAverage() == 10) {
                cout << students[i];
            }
        }
    }

    void highestAverage() {
        Student max = students[0];
        for (int i = 0; i < nStudents; i++) {
            if (students[i] > max) {
                max = students[i];
            }
        }
        cout << max;
    }
};


int main() {
    Student s("Stefan", 1);
    //cout << s;
    s += 6;
    s += 8;
    s += 10;
    s += 7;
    Faculty faculty;
    Student t("trajce", 2);
    t += 10;
    t += 10;
    t += 10;
    t += 10;
    Student r("riste", 2);
    r += 10;
    r += 9;
    r += 10;
    r += 8;
    faculty += s;
    faculty += t;
    faculty += r;
    cout << faculty;
    cout <<"---------"<<endl;
    ++faculty;
    cout<<faculty;
    cout <<"---------"<<endl;
    faculty.prize();
    cout <<"---------"<<endl;
    faculty.highestAverage();
    //    cout << "------" << endl;
    //    cout << s;
    //    cout << "------" << endl;
    //    cout << ++s;
    //    cout << "------" << endl;
    //    cout << s++;
    //    cout << s;
    //    cout << "------" << endl;
    //    Student sCopy(s);
    //    sCopy += 10;
    //    sCopy += 10;
    //    sCopy += 9;
    //    cout << s;
    //    cout << sCopy;
    //    cout << (sCopy > s);

    return 0;
}
