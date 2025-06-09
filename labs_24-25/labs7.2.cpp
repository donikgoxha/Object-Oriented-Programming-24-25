/*
Да се дефинира класа MovieActor за која ќе се чуваат:

    динамички алоцирана низа од карактери за името на актерот
    низа од максимум 40 карактери за државата од која потекнува
    просечна оцена на филмовите во кои глумел актерот годинава (double)
    вкупен број на филмови годинава (int)
    вкупна заработка од тие филмови во милиони долари (double)

За потребите на класата да се дефинираат:

    default конструктор и конструктор со аргументи
    copy constructor и оператор =
    деструктор
    метод rating() кој го враќа рејтингот на актерот пресметан како:

    (просечнаоценка * 0.4) + (бројнафилмови * 0.2) + (заработка * 0.4)

    метод print() кој ги печати податоците во следниот формат:

    [Име] - [држава]
    Average rating: [просечна оцена]
    Movies this year: [вкупен број]
    Total earnings: [вкупна заработка]
    Rating: [рејтинг]

Од MovieActor да се изведе класа OscarWinner за која дополнително ќе се чуваат:

    просечна оцена на филмовите по добиениот Оскар (double)
    број на филмови по добиениот Оскар (int)
    вкупна заработка од тие филмови (double)

За потребите на класата да се дефинираат:

    default конструктор
    конструктор кој прима објект од MovieActor и плус дополнителните информации
    конструктор кој ги прима сите аргументи (видете main)
    copy constructor, оператор =, деструктор
    метод oscarRating() кој го враќа рејтингот од пост-Оскар филмовите:

    (пост-оскарпросечнаоценка * 0.6) + (пост-оскарбројнафилмови * 0.1) + (пост-оскар_заработка * 0.3)

Да се препокријат методите:

    rating() кој враќа просек од основниот и oscar рејтинг
    print() кој покрај основните информации за актерот печати и:

    Oscar Rating: [рејтинг]
    New Rating: [просечниот]

Input
2
3
Leonardo_DiCaprio USA 8.5 3 150.0
9.2 4 200.0
Tom_Hanks USA 9.0 5 200.0
9.5 6 250.0
Meryl_Streep USA 9.5 4 120.0
9.8 7 300.0

Expected
MOVIE ACTORS:
=====================================
Leonardo_DiCaprio - USA
Average rating: 8.5
Movies this year: 3
Total earnings: 150
Rating: 64
-------------------------
Tom_Hanks - USA
Average rating: 9
Movies this year: 5
Total earnings: 200
Rating: 84.6
-------------------------
Meryl_Streep - USA
Average rating: 9.5
Movies this year: 4
Total earnings: 120
Rating: 52.6
-------------------------
OSCAR WINNERS:
=====================================
Leonardo_DiCaprio - USA
Average rating: 8.5
Movies this year: 3
Total earnings: 150
Rating: 64.96
Oscar Rating: 65.92
New Rating: 64.96
-------------------------
Tom_Hanks - USA
Average rating: 9
Movies this year: 5
Total earnings: 200
Rating: 82.95
Oscar Rating: 81.3
New Rating: 82.95
-------------------------
Meryl_Streep - USA
Average rating: 9.5
Movies this year: 4
Total earnings: 120
Rating: 74.59
Oscar Rating: 96.58
New Rating: 74.59
-------------------------
 */

#include <iostream>
#include <cstring>
using namespace std;

class MovieActor {
protected:
    char *name;
    char country[40];
    double avgRating;
    int movies;
    double earnings;

    void copy(const MovieActor &other) {
        this->name = new char [strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->country, other.country);
        this->avgRating = other.avgRating;
        this->movies = other.movies;
        this->earnings = other.earnings;
    }

public:
    MovieActor(const char *name = "", const char *country = "", double avgRating = 0.0, int movies = 0,
               double earnings = 0.0) {
        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->avgRating = avgRating;
        this->movies = movies;
        this->earnings = earnings;
    }

    MovieActor(const MovieActor &other) {
        copy(other);
    }

    MovieActor &operator=(const MovieActor &other) {
        if (this != &other) {
            delete []name;
            copy(other);
        }
        return *this;
    }

    virtual ~MovieActor() {
    }

    virtual double rating() const {
        return (avgRating * 0.4) + (movies * 0.2) + (earnings * 0.4);
    }

    virtual void print() const {
        cout << name << " - " << country << endl;
        cout << "Average rating: " << avgRating << endl;
        cout << "Movies this year: " << movies << endl;
        cout << "Total earnings: " << earnings << endl;
        cout << "Rating: " << rating() << endl;
    }
};


class OscarWinner : public MovieActor {
private:
    double postAvgRating;
    int postMovieCount;
    double postEarnings;

    void copy(const OscarWinner &other) {
        this->postAvgRating = other.postAvgRating;
        this->postMovieCount = other.postMovieCount;
        this->postEarnings = other.postEarnings;
    }

public:
    OscarWinner(const MovieActor &actor = MovieActor(), double postAvgRating = 0.0, int postMovieCount = 0,
                double postEarnings = 0.0)
        : MovieActor(actor) {
        this->postAvgRating = postAvgRating;
        this->postMovieCount = postMovieCount;
        this->postEarnings = postEarnings;
    }

    OscarWinner(const char *name = "", const char *country = "", double avgRating = 0.0, int movies = 0,
                double earnings = 0.0, double postAvgRating = 0.0, int postMovieCount = 0,
                double postEarnings = 0.0): MovieActor(name, country, avgRating, movies, earnings) {
        this->postAvgRating = postAvgRating;
        this->postMovieCount = postMovieCount;
        this->postEarnings = postEarnings;
    }

    OscarWinner(const OscarWinner &other) : MovieActor(other) {
        copy(other);
    }

    OscarWinner &operator=(const OscarWinner &other) {
        if (this != &other) {
            MovieActor::operator=(other);
            copy(other);
        }
        return *this;
    }

    ~OscarWinner() override {
    }

    double oscarRating() const {
        return (postAvgRating * 0.6) + (postMovieCount * 0.1) + (postEarnings * 0.3);
    }

    double rating() const override {
        return (MovieActor::rating() + oscarRating()) / 2.0;
    }

    void print() const override {
        MovieActor::print();
        cout << "Oscar Rating: " << oscarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
};

int main() {
    char name[100];
    char country[41];
    double avg_rating;
    int num_movies;
    double earnings;
    double post_avg_rating;
    int post_num_movies;
    double post_earnings;

    int n;
    cin >> n;

    if (n == 1) {
        // Test MovieActor basic functionality
        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        int numActors;
        cin >> numActors;

        MovieActor *actors = new MovieActor[numActors];

        for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
    } else if (n == 2) {
        // Test MovieActor and create OscarWinner from it
        int numActors;
        cin >> numActors;

        MovieActor *actors = new MovieActor[numActors];
        OscarWinner *oscarWinners = new OscarWinner[numActors];

        for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            oscarWinners[i] = OscarWinner(actors[i], post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
        delete[] oscarWinners;
    } else if (n == 3) {
        // Test OscarWinner with all arguments constructor
        int numWinners;
        cin >> numWinners;

        OscarWinner *oscarWinners = new OscarWinner[numWinners];

        for (int i = 0; i < numWinners; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            oscarWinners[i] = OscarWinner(name, country, avg_rating, num_movies, earnings,
                                          post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numWinners; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] oscarWinners;
    } else if (n == 4) {
        // Test copy constructor and operator= for MovieActor
        MovieActor actor1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        actor1 = MovieActor(name, country, avg_rating, num_movies, earnings);

        MovieActor actor2(actor1); // Using copy constructor
        MovieActor actor3;
        actor3 = actor1; // Using operator=

        cout << "ORIGINAL:" << endl;
        actor1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        actor2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        actor3.print();
        cout << "-------------------------" << endl;
    } else if (n == 5) {
        // Test copy constructor and operator= for OscarWinner
        OscarWinner winner1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        cin >> post_avg_rating >> post_num_movies >> post_earnings;

        winner1 = OscarWinner(name, country, avg_rating, num_movies, earnings,
                              post_avg_rating, post_num_movies, post_earnings);

        OscarWinner winner2(winner1); // Using copy constructor
        OscarWinner winner3;
        winner3 = winner1; // Using operator=

        cout << "ORIGINAL:" << endl;
        winner1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        winner2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        winner3.print();
        cout << "-------------------------" << endl;
    }

    return 0;
}
