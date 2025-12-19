//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int anzahl = 0;
    int versuchen = 0;

    while (anzahl < 2) {
        srand(time(NULL));
        int wurf = ( rand() %6)+1 ;
        if (wurf == 6) {
            ++anzahl;
        }
        ++versuchen;
        printf("%d\n", wurf);
        printf("%d\n", versuchen);
    }

    return 0;
}
