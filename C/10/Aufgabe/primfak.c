//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Aufruf: %s zahl\n", argv[0]);
    }

    int zahl = atoi(argv[1]);
    if (zahl == 1) {
        printf("Primfaktoren: 1");
        return 0;
    } else if (zahl < 1) {
        printf("Bitte ien Zhal >= 1 eingeben!");
        return 1;
    }
    for (int teiler = 2; zahl > 1; ++teiler) {
        int anzhalTeiler = 0;
        for (anzhalTeiler = 0; zahl % teiler == 0; ++anzhalTeiler) {
            zahl = zahl / teiler;
        }
        if (anzhalTeiler == 0) {
            continue;
        }
        if (anzhalTeiler == 1) {
            printf("%d\n", teiler);
        } else {
            printf("%d^%d ", teiler, anzhalTeiler);
        }
    }

    return 0;
}
