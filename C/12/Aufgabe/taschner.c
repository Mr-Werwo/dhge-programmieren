//
// Created by maxro on 12/12/2025.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rest = (argc -1 ) %2;
    if (rest == 0 && argc > 2) {
        printf("Aufruf: %s rechnung\n", argv[0]);
        return 1;
    }
    double ergebnis = atof(argv[1]);
    for (int i = 2; i < argc; i+=2) {
        double b = atof(argv[i+1]);

        switch (argv[i][0]) {
            case '+':
                ergebnis += b;
                break;
            case '-':
                ergebnis -= b;
                break;
            case '/':
                ergebnis /= b;
                break;
            case '*':
                ergebnis *= b;
                break;
            case '^':
                ergebnis = pow(ergebnis, b);
                break;
            default:
                fprintf(stderr, "%s: %c: Falsches Rechnezeichen\n", argv[0], argv[i][0]);
        }
    }

    printf("%g\n", ergebnis);

    return 0;
}
