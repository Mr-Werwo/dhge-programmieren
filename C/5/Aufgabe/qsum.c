//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int qsum = 0;
    if (argc < 2) {
        printf("Aufruf: %s zahl\n" , argv[0]);
    }
    int zahl = atoi(argv[1]);
    while (zahl > 0) {
        while (zahl >= 10 ) {
            qsum += zahl % 10;
            zahl /= 10;
        }
        zahl = qsum;
    }
    printf("%d\n", zahl);
    return 0;
}
