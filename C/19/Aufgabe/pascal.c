//
// Created by maxro on 18/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Aufruf: %s reihen\n", argv[0]);
    }

    int zeilen = atoi(argv[1]);
    if (zeilen<=0) {
        printf("Bitte eine Zahl > 0 eingeben!");
        return 1;
    }
    int pascal[zeilen][zeilen];

    for (int i = 0; i < zeilen; ++i) {
        pascal[i][0] = 1;
    }
    for (int i = 1; i < zeilen; ++i) {
        pascal[0][i] = 0;
    }
    for (int i = 1; i < zeilen; ++i) {
        for (int j = 1; j < zeilen; ++j) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    for (int i = 0; i < zeilen; ++i) {
        int len = 1;
        int z = pascal[zeilen - 1][zeilen/2];
        for ( ; z > 0; ++len) {
            z /= 10;
        }
        if (len % 2  == 1) {
            ++len;
        }
        int amount = zeilen - i;
        for (int j = 0; j < amount * (len/2) + 1; ++j) {
            printf(" ");
        }
        for (int j = 0; j < zeilen; ++j) {
            int k = pascal[i][j];
            if (k != 0) {
                printf("%*d ", len - 1, k);
            }
        }
        printf("\n");
    }

    return 0;
}
