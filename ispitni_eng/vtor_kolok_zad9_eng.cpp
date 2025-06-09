#include <stdio.h>
#include <string.h>

struct Film {
    char name[100];
    int time;
    float price;
    int discount; // 1 - yes, 0 - no
};

struct FilmFestival {
    char name[100];
    char place[100];
    struct Film films[100];
    int no; // number of films
};

void print(struct FilmFestival ff) {
    printf("%s %s\n", ff.name, ff.place);
    for (int i = 0; i < ff.no; i++) {
        printf("%s %d %.2f\n", ff.films[i].name, ff.films[i].time, ff.films[i].price);
    }
}

void bestFestival(struct FilmFestival *festivals, int n) {
    int maxDiscounted = -1;
    int bestIndex = -1;
    int maxTotalDuration = -1;

    for (int i = 0; i < n; i++) {
        int discountedCount = 0;
        int totalDuration = 0;

        for (int j = 0; j < festivals[i].no; j++) {
            if (festivals[i].films[j].discount == 1) {
                discountedCount++;
            }
            totalDuration += festivals[i].films[j].time;
        }

        if (discountedCount > maxDiscounted ||
            (discountedCount == maxDiscounted && totalDuration > maxTotalDuration)) {
            maxDiscounted = discountedCount;
            maxTotalDuration = totalDuration;
            bestIndex = i;
        }
    }

    printf("Najdobar festival: %s %s\n", festivals[bestIndex].name, festivals[bestIndex].place);
}

int main() {
    int n;
    scanf("%d", &n);

    struct FilmFestival ff[50];

    for (int i = 0; i < n; i++) {
        scanf("%s", ff[i].name);
        scanf("%s", ff[i].place);
        scanf("%d", &ff[i].no);

        for (int j = 0; j < ff[i].no; j++) {
            scanf("%s", ff[i].films[j].name);
            scanf("%d", &ff[i].films[j].time);
            scanf("%f", &ff[i].films[j].price);
            scanf("%d", &ff[i].films[j].discount);
        }
    }

    for (int i = 0; i < n; i++) {
        print(ff[i]);
    }

    bestFestival(ff, n);

    return 0;
}
