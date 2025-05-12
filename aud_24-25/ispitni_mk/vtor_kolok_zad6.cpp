#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame {
private:
    char msg[256];

public:
    ExistingGame(const char* msg_txt) {
        strncpy(msg, msg_txt, 255);
        msg[255] = '\0';
    }

    void message() const {
        cout << msg << endl;
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool on_sale;

public:
    Game() : price(0), on_sale(false) {
        name[0] = '\0';
    }

    Game(const char* n, float p, bool s = false) : price(p), on_sale(s) {
        strncpy(name, n, 99);
        name[99] = '\0';
    }

    virtual float get_price() const {
        return on_sale ? price * 0.3F : price;
    }

    bool operator==(const Game& g) const {
        return !strcmp(name, g.name);
    }

    friend ostream& operator<<(ostream& o, const Game& g);
    friend istream& operator>>(istream& i, Game& g);
};

class SubscriptionGame : public Game {
protected:
    float monthly_fee;
    int month, year;

public:
    SubscriptionGame() : monthly_fee(0), month(0), year(0) {
        name[0] = '\0';
    }

    SubscriptionGame(const char* n, float p, bool s, float mf, int m, int y)
        : Game(n, p, s), monthly_fee(mf), month(m), year(y) {}

    float get_price() const override {
        float base_price = Game::get_price();
        int months = 0;
        
        if (year < 2018) {
            months = (12 - month) + (2017 - year) * 12 + 5;
        } else {
            months = 5 - month;
        }

        return base_price + (months * monthly_fee);
    }

    friend ostream& operator<<(ostream& o, const SubscriptionGame& sg);
    friend istream& operator>>(istream& i, SubscriptionGame& g);
};

ostream& operator<<(ostream& o, const Game& g) {
    o << "Game: " << g.name << ", regular price: $" << g.price;
    if (g.on_sale) {
        o << ", bought on sale";
    }
    return o;
}

ostream& operator<<(ostream& o, const SubscriptionGame& sg) {
    o << static_cast<const Game&>(sg);
    o << ", monthly fee: $" << sg.monthly_fee
      << ", purchased: " << sg.month << "-" << sg.year;
    return o;
}

istream& operator>>(istream& is, Game& g) {
    is.get();
    is.getline(g.name, 100);
    is >> g.price >> g.on_sale;
    return is;
}

istream& operator>>(istream& is, SubscriptionGame& g) {
    is.get();
    is.getline(g.name, 100);
    is >> g.price >> g.on_sale;
    is >> g.monthly_fee >> g.month >> g.year;
    return is;
}

class User {
private:
    void obj_copy(const User* orig, User* cpy) {
        strncpy(cpy->username, orig->username, 99);
        cpy->username[99] = '\0';
        cpy->num_games = orig->num_games;
        cpy->games = new Game*[cpy->num_games];

        for (int i = 0; i < cpy->num_games; ++i) {
            const SubscriptionGame* sg = dynamic_cast<const SubscriptionGame*>(orig->games[i]);
            if (sg) {
                cpy->games[i] = new SubscriptionGame(*sg);
            } else {
                cpy->games[i] = new Game(*orig->games[i]);
            }
        }
    }

protected:
    char username[100];
    Game** games;
    int num_games;

public:
    User(const char* un = "") : num_games(0), games(nullptr) {
        strncpy(username, un, 99);
        username[99] = '\0';
    }

    User(const User& orig) : games(nullptr) {
        obj_copy(&orig, this);
    }

    ~User() {
        for (int i = 0; i < num_games; ++i) {
            delete games[i];
        }
        delete[] games;
    }

    User& operator=(const User& orig) {
        if (&orig != this) {
            for (int i = 0; i < num_games; ++i) {
                delete games[i];
            }
            delete[] games;
            obj_copy(&orig, this);
        }
        return *this;
    }

    User& operator+=(const Game& g) {
        for (int i = 0; i < num_games; ++i) {
            if (*games[i] == g) {
                throw ExistingGame("The game is already in the collection");
            }
        }

        Game** new_games = new Game*[num_games + 1];
        
        for (int i = 0; i < num_games; ++i) {
            new_games[i] = games[i];
        }

        const SubscriptionGame* sg = dynamic_cast<const SubscriptionGame*>(&g);
        if (sg) {
            new_games[num_games] = new SubscriptionGame(*sg);
        } else {
            new_games[num_games] = new Game(g);
        }

        delete[] games;
        games = new_games;
        num_games++;

        return *this;
    }

    const Game& get_game(int i) const {
        return *games[i];
    }

    float total_spent() const {
        float sum = 0.0f;
        for (int i = 0; i < num_games; ++i) {
            sum += games[i]->get_price();
        }
        return sum;
    }

    const char* get_username() const {
        return username;
    }

    int get_games_number() const {
        return num_games;
    }
};

ostream& operator<<(ostream& o, const User& u) {
    o << "\nUser: " << u.get_username() << "\n";
    
    for (int i = 0; i < u.get_games_number(); ++i) {
        const Game& g = u.get_game(i);
        const SubscriptionGame* sg = dynamic_cast<const SubscriptionGame*>(&g);
        
        o << "- ";
        if (sg) {
            o << *sg;
        } else {
            o << g;
        }
        o << "\n";
    }
    return o;
}

int main() {
    int test_case_num;
    cin >> test_case_num;

    char game_name[100];
    float game_price;
    bool game_on_sale;
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;
    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout << "Testing class Game and operator<< for Game" << endl;
        cin.get();
        cin.getline(game_name, 100);
        cin >> game_price >> game_on_sale;
        Game g(game_name, game_price, game_on_sale);
        cout << g;
    }
    else if (test_case_num == 2) {
        cout << "Testing class SubscriptionGame and operator<< for SubscritionGame" << endl;
        cin.get();
        cin.getline(game_name, 100);
        cin >> game_price >> game_on_sale;
        cin >> sub_game_monthly_fee;
        cin >> sub_game_month >> sub_game_year;
        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout << sg;
    }
    else if (test_case_num == 3) {
        cout << "Testing operator>> for Game" << endl;
        Game g;
        cin >> g;
        cout << g;
    }
    else if (test_case_num == 4) {
        cout << "Testing operator>> for SubscriptionGame" << endl;
        SubscriptionGame sg;
        cin >> sg;
        cout << sg;
    }
    else if (test_case_num == 5) {
        cout << "Testing class User and operator+= for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >> num_user_games;

        try {
            for (int i = 0; i < num_user_games; ++i) {
                cin >> game_type;
                Game* g;
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);
                    cin >> game_price >> game_on_sale;
                    cin >> sub_game_monthly_fee;
                    cin >> sub_game_month >> sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }
                u += (*g);
            }
        }
        catch(ExistingGame& ex) {
            ex.message();
        }
        cout << u;
    }
    else if (test_case_num == 6) {
        cout << "Testing exception ExistingGame for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {
            cin >> game_type;
            Game* g;
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }
            try {
                u += (*g);
            }
            catch(ExistingGame& ex) {
                ex.message();
            }
        }
        cout << u;
    }
    else if (test_case_num == 7) {
        cout << "Testing total_spent method() for User" << endl;
        cin.get();
        cin.getline(username, 100);
        User u(username);
        int num_user_games;
        int game_type;
        cin >> num_user_games;

        for (int i = 0; i < num_user_games; ++i) {
            cin >> game_type;
            Game* g;
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);
                cin >> game_price >> game_on_sale;
                cin >> sub_game_monthly_fee;
                cin >> sub_game_month >> sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }
            u += (*g);
        }
        cout << u << endl;
        cout << "Total money spent: $" << u.total_spent() << endl;
    }
}
