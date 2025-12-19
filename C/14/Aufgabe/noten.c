//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Aufruf: %s punkte1 punkte2 punkte3 ...\n", argv[0]);
    }

    int noten[5];
    double note = 1;

    for (int i = 0; i < 5; ++i) {
        noten[i] = 0;
    }

    for (int i = 1; i < argc; ++i) {
        int punkte = atoi(argv[i]);
        if (punkte < 1 || punkte > 100) {
            printf("Falsche Eingabe 1-100");
            return 1;
        }
        int index = 0;
        if (punkte <= 50) {
            index = 4;
        } else {
            note = lround(40 - 3 * ((punkte - 50) / 5));
            note = lround(note / 10 - 0.1);
            index = note - 1;
        }
        noten[index]++;
    }
     for (int i = 0; i < 5; ++i) {
         printf("%d: %d\n", i+1, noten[i]);
     }

    return 0;
}
