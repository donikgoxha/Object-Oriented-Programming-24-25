#include <iostream>
#include <cstring>
using namespace std;
//YOUR CODE HERE!

class Scholarship;

class Student {
private:
    char name[100];
    char surname[100];
    char faculty[100];
    float average;
    static double totalStudents;
    static double finkiStudents;

public:
    Student() {
        strcpy(name, "");
        strcpy(surname, "");
        strcpy(faculty, "");
        average = 0.0;
        totalStudents++;
    }

    Student(const char *name, const char *surname, const char *faculty, float average) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->faculty, faculty);
        this->average = average;
        totalStudents++;
        if (finkiStudent()) { finkiStudents++; }
    }


    Student(const Student &other) {
        strcpy(this->name, other.name);
        strcpy(this->surname, other.surname);
        strcpy(this->faculty, other.faculty);
        this->average = other.average;
        totalStudents++;
        if (strcmp(faculty, "FINKI") == 0) {
            finkiStudents++;
        }
    }


    bool finkiStudent() const {
        return (strcmp(faculty, "FINKI") == 0 && average > 9);
    }

    const char *getName() const { return name; }
    const char *getSurname() const { return surname; }
    const char *getFaculty() const { return faculty; }
    float getAverage() const { return average; }

    friend class Scholarship;

    friend void studentsWithScholarship(Scholarship &scholarship, int num_students);
};

double Student::totalStudents = 0;
double Student::finkiStudents = 0;

class Scholarship {
private:
    char companyName[100];
    Student students[100];
    int numStudents;
    static float sumFinki;
    static int countFinki;
    static float avgFinki;

public:
    Scholarship() {
        strcpy(companyName, "");
        numStudents = 0;
    }

    Scholarship(const char *companyName) {
        strcpy(this->companyName, companyName);
        numStudents = 0;
    }

    void addStudent(const Student &s) {
        if (numStudents < 100) {
            students[numStudents++] = s;
            if (s.finkiStudent()) {
                sumFinki += s.getAverage();
                countFinki++;
                avgFinki = sumFinki / countFinki;
            }
        }
    }


    void print() {
        cout << "Scholarship name: " << companyName << ", total applicants: " << numStudents << endl;
    }

    friend class Student;

    friend void studentsWithScholarship(Scholarship &scholarship, int num_students);
};

float Scholarship::sumFinki = 0.0;
int Scholarship::countFinki = 0;
float Scholarship::avgFinki = 0.0;

void studentsWithScholarship(Scholarship &scholarship, int num_students) {
    Student winners[100];
    int cnt = 0;

    for (int i = 0; i < scholarship.numStudents; i++)
        if (scholarship.students[i].finkiStudent())
            winners[cnt++] = scholarship.students[i];

    for (int i = 0; i < cnt - 1; i++) {
        for (int j = 0; j < cnt - i - 1; j++) {
            if (winners[j].getAverage() < winners[j + 1].getAverage()) {
                Student tmp = winners[j];
                winners[j] = winners[j + 1];
                winners[j + 1] = tmp;
            }
        }
    }
    cout << "FINKI students with a scholarship" << endl;

    for (int i = 0; i < 3; i++)
        cout << winners[i].getName() << " " << winners[i].getSurname() << " "
                << winners[i].getFaculty() << " " << winners[i].getAverage() << endl;

    double perc = 0;
    if (Student::totalStudents > 0) {
        perc = Student::finkiStudents * 100.0f / Student::totalStudents;
    }

    cout << "Scholarship data shows that " << perc << "% of applicants are from FINKI, with an average grade of " <<
            Scholarship::avgFinki << endl;
}


//DO NOT CHANGE THE MAIN FUNCTION!
int main() {
    char name[50], surname[50], faculty[50], scholarship_name[50];
    float average_grade;
    int n, case_;
    cin >> case_;
    if (case_ == 0)
    //Testing Student constructor
    {
        cout << "--Testing finkiStudent method--" << endl;
        Student s("Ana", "Denkova", "BAS", 9.89);
        cout << s.finkiStudent();
    } else if (case_ == 1) {
        //Testing addStudent and print method
        cout << "--Testing addStudent and print method--" << endl;
        Scholarship sc("ITCompany");
        Student s("Ana", "Denkova", "BAS", 9.89);
        sc.addStudent(s);
        sc.print();
    } else if (case_ == 2) {
        cin >> scholarship_name;
        Scholarship sc(scholarship_name);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> name >> surname >> faculty >> average_grade;
            Student s = Student(name, surname, faculty, average_grade);
            sc.addStudent(s);
        }
        sc.print();
        studentsWithScholarship(sc, n);
    }
    return 0;
}
