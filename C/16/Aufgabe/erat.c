//
// Created by maxro on 18/12/2025.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000000

bool liste[MAX];

int main(int argc, char *argv[]) {
    int i = 0;
    int zahl = atoi(argv[1]);

    if (argc != 2) {
        printf("Aufruf: %s zahl\n", argv[0]);
    }
    if (!(zahl <= MAX) || !(zahl > 1)) {
        printf("Bitte eine Zahl zwischen 1 und %d eingeben!", MAX);
        return 1;
    }
    for ( i = 0; i< MAX; i++) {
        liste[i] = true;
    }

    for (i = 2 ; i < zahl; i++) {
        if (liste[i]) {
            printf("%d ", i);
        }
        for (int j = i + i; j < zahl; j += i) {
            liste[j] = false;
        }
    }

    return 0;
}
