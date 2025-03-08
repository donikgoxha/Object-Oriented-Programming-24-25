#include <iostream>
#include <cstring>
using namespace std;
//zad10 ispitni/kolokviumski eng

class InvalidTeamName {
private:
    char *name;

public:
    InvalidTeamName(const char *name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    const char *what() {
        return name;
    }

    ~InvalidTeamName() {
        delete[] name;
    }
};

class Goal {
private:
    char *goalScorer;
    int timeOfGoal;
    char team[50];

    void copy(const Goal &g) {
        goalScorer = new char[strlen(g.goalScorer) + 1];
        strcpy(goalScorer, g.goalScorer);
        timeOfGoal = g.timeOfGoal;
        strcpy(team, g.team);
    }

public:
    Goal(const char *goalScorer = "", int timeOfGoal = 0, const char *team = "") {
        this->goalScorer = new char [strlen(goalScorer) + 1];
        strcpy(this->goalScorer, goalScorer);
        this->timeOfGoal = timeOfGoal;
        strcpy(this->team, team);
    }

    Goal(const Goal &g) {
        copy(g);
    }

    Goal &operator=(const Goal &g) {
        if (this != &g) {
            delete []goalScorer;
            copy(g);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Goal &g) {
        return out << g.timeOfGoal << " " << g.goalScorer;
    }

    Goal operator++(int) {
        Goal temp = *this;
        timeOfGoal++;
        return temp;
    }

    Goal &operator--() {
        --timeOfGoal;
        return *this;
    }

    const char *getTeam() const {
        return team;
    }

    ~Goal() {
        delete[] goalScorer;
    }
};

class Game {
private:
    Goal **goals;
    int numGoals;
    char team1[50];
    char team2[50];
    int capacity;

public:
    Game(const char *team1 = "", const char *team2 = "") {
        numGoals = 0;
        capacity = 10;
        this->goals = new Goal *[capacity];
        strcpy(this->team1, team1);
        strcpy(this->team2, team2);
    }

    ~Game() {
        for (int i = 0; i < numGoals; i++) {
            delete goals[i];
        }
        delete[] goals;
    }

    Game &operator+=(const Goal &g) {
        if (strcmp(g.getTeam(), team1) != 0 && strcmp(g.getTeam(), team2) != 0)
            throw InvalidTeamName(g.getTeam());

        if (numGoals == capacity) {
            capacity *= 2;
            Goal **temp = new Goal *[capacity];
            for (int i = 0; i < numGoals; i++)
                temp[i] = goals[i];
            delete[] goals;
            goals = temp;
        }

        goals[numGoals++] = new Goal(g);
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Game &game) {
        out << game.team1 << " - " << game.team2 << endl;
        for (int i = 0; i < game.numGoals; i++)
            out << *game.goals[i] << endl;
        return out;
    }
};


int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for (int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch (InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
