//
// Created by maxro on 09/12/2025.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double result = 0;

    if (argc != 2) {
        fprintf(stderr, "Aufruf: %s x\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    double x = atof(argv[1]);
    double y = atof(argv[1]);
    for (int i = 0; i < 100; i++) {
        y = 0.5 * (y + x/y);
        if (!fabs(y * y - x) > x * 1e-10) {
            break;
        }
    }
    printf("%f\n", y);
    return 0;
}
