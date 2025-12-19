//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Aufruf: %s reihen kugeln\n", argv[0]);
    }

    int reihen = atoi(argv[1]);
    int kugeln = atoi(argv[2]);

    int n = 1;
    if (reihen > 1) {
        n = reihen +1;
    }
    srand(time(NULL));


    int anzahl[n];
    for (int i = 0; i < n; ++i) {
        anzahl[i] = 0;
    }
    for (int i = 0; i < kugeln; ++i) {
        int r = 0;
        for (int j = 0; j < reihen; ++j) {
            int zufallszahl = rand() % 2;
            if (zufallszahl == 0) {
                r += 1;
            }
        }
        anzahl[r]++;
    }
    for (int i = 0; i < n; ++i) {
        int amount = anzahl[i];
        int anteil = (amount / kugeln) * 10;
        printf("%d: ", i+1);
        for (int j = 0; j < anteil; ++j) {
            printf("|");
        }
        printf("\n");
    }
    return 0;
}
