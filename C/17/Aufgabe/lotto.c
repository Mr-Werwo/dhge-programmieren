//
// Created by maxro on 18/12/2025.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    bool ziehungen[49];
    int zahlen = 0;

    for (int i = 0; i < 49; i++) {
        ziehungen[i] = false;
    }

    srand(time(NULL));

    while (zahlen != 6) {
        int zahl = rand() % 49 + 1;
        if (!ziehungen[zahl]) {
            ziehungen[zahl] = true;
            zahlen++;
        }
    }

    for (int i = 0; i< 49; i++) {
        if (ziehungen[i]) {
            printf("%d ", i+1);
        }
    }

    return 0;
}
