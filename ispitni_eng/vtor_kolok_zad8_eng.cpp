#include <stdio.h>

typedef struct Driver {
    char name[100];
    int time;
} Driver;

typedef struct Race {
    char location[100];
    int n;
    Driver drivers[100];
} Race;

void top3(Race *race) {
    int i, j;
    for (i = 0; i < race->n; ++i) {
        for (j = 0; j < race->n - 1; ++j) {
            if (race->drivers[j].time > race->drivers[j + 1].time) {
                Driver tmp = race->drivers[j];
                race->drivers[j] = race->drivers[j + 1];
                race->drivers[j + 1] = tmp;
            }
        }
    }

    for (i = 0; i < 3; ++i) {
        Driver *d = &race->drivers[i];
        printf("%d. %s %2d:%02d\n", i + 1, d->name, d->time / 60, d->time % 60);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Race races[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", races[i].location);
        scanf("%d", &races[i].n);
        int j;
        for (j = 0; j < races[i].n; ++j) {
            scanf("%s", races[i].drivers[j].name);
            scanf("%d", &races[i].drivers[j].time);
        }
    }

    for (i = 0; i < n; ++i) {
        printf("%s (%d Drivers)\n", races[i].location, races[i].n);
        top3(&races[i]);
    }

    return 0;
}
