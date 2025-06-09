#include <iostream>

using namespace std;

class Course {
protected:
    string code;
    int credits;

public:
    Course(string code = "CS101", int credits = 6) : code(code), credits(credits) {
    }

    void display() {
        cout << code << " " << credits << " ";
    }

    ~Course() {
    }
};

class OnlineCourse : public Course {
private:
    int bonus;

public:
    OnlineCourse(string code = "CS101", int credits = 6, int bonus = 1) : Course(code, credits) {
        if (bonus > 0 && bonus < 3) this->bonus = bonus;
        else this->bonus = 1;
    }

    int calculateMaxCourseCredits() {
        return bonus + credits;
    }

    void display() {
        Course::display();
        cout << bonus << " " << endl;
    }
};


OnlineCourse *createOnlineCourses(int n) {
    OnlineCourse *onlineCourses = new OnlineCourse[n];
    string code;
    int credits, bonusCredits;
    for (int i = 0; i < n; i++) {
        cin >> code >> credits >> bonusCredits;
        onlineCourses[i] = OnlineCourse(code, credits, bonusCredits);
    }
    return onlineCourses;
}

int main() {
    int testCase;
    cin >> testCase;

    switch (testCase) {
        case 1: {
            OnlineCourse onlineCourse;
            onlineCourse.display();
            break;
        }
        case 2: {
            OnlineCourse onlineCourse("CS101", 6, 1);
            onlineCourse.display();
            OnlineCourse onlineCourse1("CS102", 4, 2);
            onlineCourse1.display();
            break;
        }
        case 3: {
            OnlineCourse onlineCourse("CS101", 5, 5);
            onlineCourse.display();
            OnlineCourse onlineCourse1("CS102", 6, 0);
            onlineCourse1.display();
            break;
        }
        case 4: {
            OnlineCourse onlineCourse("CS101", 7, 2);
            cout << onlineCourse.calculateMaxCourseCredits();
            break;
        }
        case 5: {
            int n;
            cin >> n;
            OnlineCourse *onlineCourses = createOnlineCourses(n);
            for (int i = 0; i < n; i++) {
                onlineCourses[i].display();
            }
            delete [] onlineCourses;
            break;
        }
        default: {
            int n;
            cin >> n;

            OnlineCourse *onlineCourses = createOnlineCourses(n);
            for (int i = 0; i < n; i++) {
                onlineCourses[i].display();
            }
            for (int i = 0; i < n; i++) {
                cout << onlineCourses[i].calculateMaxCourseCredits() << endl;
            }
            delete [] onlineCourses;
            break;
        }
    }
}
