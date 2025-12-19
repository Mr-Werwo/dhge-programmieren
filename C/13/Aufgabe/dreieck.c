//
// Created by maxro on 12/12/2025.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Aufruf: %s Anzahl\n", argv[0]);
    }
    int abstand = 1;
    int ergebnisse = 0;
    int n = atoi(argv[1]);

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            for (int k = 1; k < n; ++k) {
                int a = i*i + j*j;
                int b = k*k;
                if (a==b) {
                    if ((i+j+k <= n) && (i < j) && (j < k)) {
                        ergebnisse++;
                        printf("Loesung: %d, %d, %d\n", i, j, k);
                    }
                }
            }
        }
    }
    printf("Anzahl der Loesungen:%d\n", ergebnisse);
    return 0;
}
