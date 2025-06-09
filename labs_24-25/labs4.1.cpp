#include <iostream>
using namespace std;

class WorkoutSession {
private:
    int duration;
    char tip;

public:
    WorkoutSession() {
        duration = 30;
        tip = 'c';
    }

    int caloriesBurned() {
        if (tip == 'c') {
            return duration * 8;
        } else if (tip == 't') {
            return duration * 6;
        } else {
            return 0;
        }
    }

    void setDuration(int d) {
        duration = d;
    }

    void setTip(char t) {
        tip = t;
    }

    void printInfo() {
        cout << "Type of training: " << (tip == 'c' ? "Cardio" : "Tezinski") << endl;
        cout << "Duration: " << duration << " minuti" << endl;
        cout << "Calories burned: " << caloriesBurned() << endl;
    }
};

int main() {
    //main given by the quiz
    return 0;
}
