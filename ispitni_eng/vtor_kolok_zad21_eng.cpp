#include <stdio.h>
#include <string.h>

#define MAX_LIFTS 20
#define MAX_NAME_LEN 20

typedef struct {
    char name[15];
    int max_users;
    int in_function;
} SkiLift;

typedef struct {
    char name[MAX_NAME_LEN];
    char country[MAX_NAME_LEN];
    SkiLift lifts[MAX_LIFTS];
    int num_lifts;
} SkiCenter;

int calculateCapacity(SkiCenter *sc) {
    int capacity = 0;
    for (int i = 0; i < sc->num_lifts; i++) {
        if (sc->lifts[i].in_function) {
            capacity += sc->lifts[i].max_users;
        }
    }
    return capacity;
}

void biggestCapacity(SkiCenter *sc, int n) {
    SkiCenter max_center;
    int max_capacity = 0;
    int max_lifts = 0;

    for (int i = 0; i < n; i++) {
        int current_capacity = calculateCapacity(&sc[i]);
        int current_lifts = sc[i].num_lifts;

        if (current_capacity > max_capacity ||
            (current_capacity == max_capacity && current_lifts > max_lifts)) {
            max_capacity = current_capacity;
            max_lifts = current_lifts;
            max_center = sc[i];
        }
    }

    printf("%s\n", max_center.name);
    printf("%s\n", max_center.country);
    printf("%d\n", max_capacity);
}

int main() {
    int n;
    scanf("%d", &n);

    SkiCenter ski_centers[n];

    for (int i = 0; i < n; i++) {
        scanf("%s", ski_centers[i].name);
        scanf("%s", ski_centers[i].country);
        scanf("%d", &ski_centers[i].num_lifts);

        for (int j = 0; j < ski_centers[i].num_lifts; j++) {
            scanf("%s", ski_centers[i].lifts[j].name);
            scanf("%d", &ski_centers[i].lifts[j].max_users);
            scanf("%d", &ski_centers[i].lifts[j].in_function);
        }
    }

    biggestCapacity(ski_centers, n);

    return 0;
}
