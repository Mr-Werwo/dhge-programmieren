//
// Created by maxro on 12/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Aufruf: %s zahl1 zahl2\n", argv[0]);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    printf("%d\n", a);
    return 0;
}
