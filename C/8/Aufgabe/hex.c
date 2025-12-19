//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Aufruf: %s hexzahl(en)\n", argv[0]);
    }

    for (int i = 1; i < argc; ++i) {
        int ergebnis = 0;
        for (int pos = 0; argv[i][pos] != '\0'; ++pos) {
            char c = argv[i][pos];
            if (c >= '0' && c <= '9') {
                ergebnis = ergebnis * 16 + (c - '0');
            } else if (c >= 'A' && c <= 'F') {
                ergebnis = ergebnis * 16 + (c - 'A' + 10);
            } else if (c >= 'a' && c <= 'f') {
                ergebnis = ergebnis * 16 + (c - 'a' + 10);
            } else {
                printf("Falsche eingabe: %s hexzahl(en)\n", argv[0]);
            }
        }
        printf("%d\n", ergebnis);
    }

    return 0;
}