//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Aufruf: %s zahl1 zahl2 zahl3 ...\n", argv[0]);
    }
    int max = atoi(argv[1]);
    int min = atoi(argv[1]);
    int posMax = 1;
    int posMin = 1;
    if (argc >= 2) {
        for (int i = 2; i < argc; ++i) {
            int zahl = atoi(argv[i]);
            if (zahl > max) {
                max = zahl;
                posMax = i;
            } else if (zahl < min) {
                min = zahl;
                posMin = i;
            }
        }
        if (max == min) {
            printf("Alle Zahlen sind gleich %d\n", max);
            return 0;
        }
        printf("Maximalwert: %d, Position: %d\n", max, posMax);
        printf("Minimalwert: %d, Position: %d\n", min, posMin);
    }
    return 0;
}
