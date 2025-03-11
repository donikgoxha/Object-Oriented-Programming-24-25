/*
Да се креира класа BasketballPlayer која ќе ги чува следните информации:
    име на кошаркарот (низа од знаци не подолга од 20 карактери)
    презиме на кошаркарот (низа од знаци не подолга од 20 карактери)
    број на дрес (цел број)
    поени од прв натпревар (цел број)
    поени од втор натпревар (цел број)
    поени од трет натпревар (цел број)
Да се направат потребните методи за класата, како и метод за печатење наинформации за кошаркарот
во следен формат "Player: name surname with number: number has avg_pts points on average".
Од стандарден влез се внесуваат име, презиме, број на дрес и поени за сите три натпревари за
еден кошаркар.
На стандарден излез се печатат информациите за кошаркарот.
 */

#include <iostream>
#include <cstring>
using namespace std;

class BasketballPlayer {
private:
    char name[100];
    char surname[100];
    int numJersey;
    int pointsFirst;
    int pointsSecond;
    int pointsThird;

public:
    BasketballPlayer(const char *namee = "", const char *surnamee = "", int numJerseyy = 0, int pointsFirstt = 0,
                     int pointsSecondd = 0, int pointsThirdd = 0) {
        strcpy(name, namee);
        strcpy(surname, surnamee);
        numJersey = numJerseyy;
        pointsFirst = pointsFirstt;
        pointsSecond = pointsSecondd;
        pointsThird = pointsThirdd;
    }

    //Player: name surname with number: number has avg_pts points on average

    double averagePoints() {
        return (pointsFirst + pointsSecond + pointsThird) / 3.0;
    }

    void print() {
        cout << "Player: " << name << " " << surname << " with number: " << numJersey << " has " << averagePoints() <<
                " points on average." << endl;
    }
};


int main() {
    char name[100];
    char surname[100];
    int number, p1, p2, p3;

    cin >> name >> surname >> number >> p1 >> p2 >> p3;
    BasketballPlayer player(name, surname, number, p1, p2, p3);
    player.print();
    return 0;
}
