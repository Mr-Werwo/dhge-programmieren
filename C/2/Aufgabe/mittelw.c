//
// Created by maxro on 09/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    float result = 0;

    for (int i = 0; i <= argc; i++) {
        float zahl1 = 0;
        zahl1 = atof(argv[i]);
        result += zahl1;
    }

    printf("%f", result);
    return EXIT_SUCCESS;
}
