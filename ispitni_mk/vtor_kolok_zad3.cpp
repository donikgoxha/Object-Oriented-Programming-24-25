#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class NoCourseException {
    string text;

public:
    NoCourseException(string text) {
        this->text = text;
    }

    void print() {
        cout << "Demonstratorot so indeks " << text << " ne drzi laboratoriski vezbi" << endl;
    }
};

class Kurs {
    char name[50];
    int credits;

    void copy(const Kurs &other) {
        credits = other.credits;
        strcpy(name, other.name);
    }

public:
    Kurs(const char *name = "", int credits = 0) {
        strcpy(this->name, name);
        this->credits = credits;
    }

    Kurs(const Kurs &other) {
        copy(other);
    }

    Kurs &operator=(const Kurs &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    ~Kurs() {
    }

    void print() {
        cout << name << " " << credits << "ECTS";
    }

    char *getName() {
        return name;
    }
};

class Student {
protected:
    int indexofstudent;
    int *grades;
    int numofgrades;

    void copy(const Student &other) {
        indexofstudent = other.indexofstudent;
        numofgrades = other.numofgrades;
        for (int i = 0; i < numofgrades; i++) grades[i] = other.grades[i];
    }

public:
    Student(int indexofstudent = 0, int *grades = {}, int numofgrades = 0) {
        this->indexofstudent = indexofstudent;
        this->numofgrades = numofgrades;
        this->grades = new int[numofgrades + 1];
        for (int i = 0; i < numofgrades; i++) {
            this->grades[i] = grades[i];
        }
    }

    Student(const Student &other) {
        copy(other);
    }

    Student &operator=(const Student &other) {
        if (this != &other) {
            delete[] grades;
            copy(other);
        }
        return *this;
    }

    virtual ~Student() {
        delete[] grades;
    }

    virtual int getBodovi() {
        if (numofgrades == 0) return 0;
        int average = 0;
        for (int i = 0; i < numofgrades; i++) {
            if (grades[i] > 5) average++;
        }
        return average * 100 / numofgrades;
    }

    virtual void print() {
        cout << indexofstudent << endl;
    }
};

class Predavach {
protected:
    char *nameproffessor;
    Kurs *courses;
    int numofcourses;

    void copy(const Predavach &other) {
        nameproffessor = new char[strlen(other.nameproffessor) + 1];
        strcpy(nameproffessor, other.nameproffessor);
        numofcourses = other.numofcourses;
        courses = new Kurs[numofcourses + 1];
        for (int i = 0; i < numofcourses; i++) courses[i] = other.courses[i];
    }

public:
    Predavach(const char *nameproffessor = "", Kurs *courses = nullptr, int numofcourses = 0) {
        this->nameproffessor = new char[strlen(nameproffessor) + 1];
        strcpy(this->nameproffessor, nameproffessor);
        this->numofcourses = numofcourses;
        this->courses = new Kurs[numofcourses + 1];
        for (int i = 0; i < numofcourses; i++) {
            this->courses[i] = courses[i];
        }
    }

    Predavach(const Predavach &other) {
        copy(other);
    }

    Predavach &operator=(const Predavach &other) {
        if (this != &other) {
            delete[] nameproffessor;
            delete[] courses;
            copy(other);
        }
        return *this;
    }

    virtual ~Predavach() {
        delete[] nameproffessor;
        delete[] courses;
    }

    Kurs *getCourses() {
        return courses;
    }

    int getNumofCourses() {
        return numofcourses;
    }

    const char *getName() {
        return nameproffessor;
    }
};

class Demonstrator : public Student, public Predavach {
    int numofhours;

    void copy(const Demonstrator &other) {
        numofhours = other.numofhours;
    }

public:
    Demonstrator(int indexofstudent, int *grades = {}, int numofgrades = 0, const char *nameofdemonstrator = "",
                 Kurs *courses = nullptr, int numofcourses = 0, int numofhours = 0)
        : Student(indexofstudent, grades, numofgrades), Predavach(nameofdemonstrator, courses, numofcourses) {
        this->numofhours = numofhours;
    }

    Demonstrator(const Demonstrator &other)
        : Student(other), Predavach(other) {
        copy(other);
    }

    Demonstrator &operator=(const Demonstrator &other) {
        if (this != &other) {
            Student::operator=(other);
            Predavach::operator=(other);
            copy(other);
        }
        return *this;
    }

    ~Demonstrator() override {
    }

    int getBodovi() override {
        int initial = Student::getBodovi();
        if (numofcourses == 0) throw NoCourseException(to_string(indexofstudent));
        return initial + (20 * numofhours) / numofcourses;
    }

    void print() override {
        cout << indexofstudent << ": " << nameproffessor << " (";
        for (int i = 0; i < numofcourses; i++) {
            courses[i].print();
            if (i != numofcourses - 1) cout << ", ";
        }
        cout << ")" << endl;
    }

    int getnumofhours() {
        return numofhours;
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    int maks = 0;
    int indexi = 0;
    for (int i = 0; i < n; i++) {
        try {
            if (maks < studenti[i]->getBodovi()) {
                maks = studenti[i]->getBodovi();
                indexi = i;
            }
        } catch (NoCourseException &e) {
            e.print();
        }
    }
    cout << "Maksimalniot broj na bodovi e:" << maks << endl;
    return *studenti[indexi];
}

void pecatiDemonstratoriKurs(char *kurs, Student **studenti, int n) {
    cout << "Demonstratori na " << kurs << " se:" << endl;
    for (int i = 0; i < n; i++) {
        Demonstrator *d = dynamic_cast<Demonstrator *>(studenti[i]);
        if (d != nullptr) {
            Kurs *k = d->getCourses();
            int br = d->getNumofCourses();
            for (int j = 0; j < br; j++) {
                if (strcmp(k[j].getName(), kurs) == 0) {
                    d->print();
                    break;
                }
            }
        }
    }
}

int main() {
    int testCase;
    cin >> testCase;

    //test case 1

    if (testCase == 1) {
        cout << "-----TEST Demonstrator-----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        char name[100];
        int numberKursevi = 0;
        cin.ignore();
        cin >> name;
        cin >> numberKursevi;
        Kurs kursevi[numberKursevi];

        for (int i = 0; i < numberKursevi; i++) {
            char nameCourse[100];
            int credits;
            cin >> nameCourse;
            cin >> credits;
            kursevi[i] = Kurs(nameCourse, credits);
        }

        int weekClasses;
        cin >> weekClasses;

        Demonstrator d = Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);
        cout << "Objekt od klasata Demonstrator e kreiran" << endl;
    }

    //test case 2

    else if (testCase == 2) {
        cout << "-----TEST pecati-----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        Student s = Student(index, grades, numberGrades);
        s.print();
    }

    //test case 3

    else if (testCase == 3) {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        Student s = Student(index, grades, numberGrades);
        cout << "Broj na bodovi: " << s.getBodovi() << endl;
    }

    //test case 4

    else if (testCase == 4) {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        char name[100];
        int numberKursevi;
        cin.ignore();
        cin >> name;
        cin >> numberKursevi;
        Kurs kursevi[numberKursevi];

        for (int i = 0; i < numberKursevi; i++) {
            char nameCourse[100];
            int credits;
            cin >> nameCourse;
            cin >> credits;
            kursevi[i] = Kurs(nameCourse, credits);
        }

        int weekClasses;
        cin >> weekClasses;

        Demonstrator d = Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);

        try {
            cout << "Broj na bodovi: " << d.getBodovi() << endl;
        } catch (NoCourseException &e) {
            e.print();
        }
    }

    //test case 5

    else if (testCase == 5) {
        cout << "-----TEST pecati -----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        char name[100];
        int numberKursevi;
        cin.ignore();
        cin >> name;
        cin >> numberKursevi;
        Kurs kursevi[numberKursevi];

        for (int i = 0; i < numberKursevi; i++) {
            char nameCourse[100];
            int credits;
            cin >> nameCourse;
            cin >> credits;
            kursevi[i] = Kurs(nameCourse, credits);
        }

        int weekClasses;
        cin >> weekClasses;

        Demonstrator d = Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);
        d.print();
    }

    //test case 6

    else if (testCase == 6) {
        cout << "-----TEST Student i Demonstrator-----" << endl;
        int index, numberGrades;
        cin >> index;
        cin >> numberGrades;
        int grades[numberGrades];

        for (int i = 0; i < numberGrades; i++) {
            cin >> grades[i];
        }

        char name[100];
        int numberKursevi;
        cin.ignore();
        cin >> name;
        cin >> numberKursevi;
        Kurs kursevi[numberKursevi];

        for (int i = 0; i < numberKursevi; i++) {
            char nameCourse[100];
            int credits;
            cin >> nameCourse;
            cin >> credits;
            kursevi[i] = Kurs(nameCourse, credits);
        }

        int weekClasses;
        cin >> weekClasses;

        Demonstrator d = Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);
        d.print();

        try {
            cout << "Broj na bodovi: " << d.getBodovi() << endl;
        } catch (NoCourseException &e) {
            e.print();
        }
    }

    //test case 7

    else if (testCase == 7) {
        cout << "-----TEST vratiNajdobroRangiran-----" << endl;
        int n;
        cin >> n;
        Student *studenti[n];

        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;

            if (type == 1) {
                int index, numberGrades;
                cin >> index;
                cin >> numberGrades;
                int grades[numberGrades];

                for (int j = 0; j < numberGrades; j++) {
                    cin >> grades[j];
                }

                studenti[i] = new Student(index, grades, numberGrades);
            } else {
                int index, numberGrades;
                cin >> index;
                cin >> numberGrades;
                int grades[numberGrades];

                for (int i = 0; i < numberGrades; i++) {
                    cin >> grades[i];
                }

                char name[100];
                int numberKursevi;
                cin.ignore();
                cin >> name;
                cin >> numberKursevi;
                Kurs kursevi[numberKursevi];

                for (int j = 0; j < numberKursevi; j++) {
                    char nameCourse[100];
                    int credits;
                    cin >> nameCourse;
                    cin >> credits;
                    kursevi[j] = Kurs(nameCourse, credits);
                }

                int weekClasses;
                cin >> weekClasses;

                studenti[i] = new Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);
            }
        }

        Student &best = vratiNajdobroRangiran(studenti, n);
        cout << "Najdobro rangiran:";
        best.print();

        for (int i = 0; i < n; i++) {
            delete studenti[i];
        }
    }

    //test case 8

    else if (testCase == 8) {
        cout << "-----TEST pecatiDemonstratoriKurs-----" << endl;
        int n;
        cin >> n;

        Student *studenti[n];

        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;

            if (type == 1) {
                int index, numberGrades;
                cin >> index;
                cin >> numberGrades;
                int grades[numberGrades];

                for (int j = 0; j < numberGrades; j++) {
                    cin >> grades[j];
                }

                studenti[i] = new Student(index, grades, numberGrades);
            } else {
                int index, numberGrades;
                cin >> index;
                cin >> numberGrades;
                int grades[numberGrades];

                for (int i = 0; i < numberGrades; i++) {
                    cin >> grades[i];
                }

                char name[100];
                int numberKursevi;
                cin.ignore();
                cin >> name;
                cin >> numberKursevi;
                Kurs kursevi[numberKursevi];

                for (int j = 0; j < numberKursevi; j++) {
                    char nameCourse[100];
                    int credits;
                    cin >> nameCourse;
                    cin >> credits;
                    kursevi[j] = Kurs(nameCourse, credits);
                }

                int weekClasses;
                cin >> weekClasses;

                studenti[i] = new Demonstrator(index, grades, numberGrades, name, kursevi, numberKursevi, weekClasses);
            }
        }

        char course[50];
        cin >> course;

        pecatiDemonstratoriKurs(course, studenti, n);

        for (int i = 0; i < n; i++) {
            delete studenti[i];
        }
    }
    return 0;
}
