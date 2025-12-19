//
// Created by maxro on 18/12/2025.
//

#include <stdbool.h>
#include <stdio.h>
#define MAX 100

int main() {
    bool stop = false;

    int array[MAX];
    for (int i = 0; i < MAX; ++i) {
        array[i] = 0;
    }

    while (!stop) {
        int a = 0;
        int n = 1;
        scanf("%d", &a);
        if (a == 0) {
            stop = true;
        } else {
            if (a<0) {
                a *= -1;
            }
            for (int i = 0; i < MAX; ++i) {
                int b = 0;
                int c = array[i];
                if (c == 0) {
                    n = 0;
                }
                if (c >= a || c == 0) {
                    b = array[i];
                    array[i] = a;
                    a = b;
                }
            }
            if (n != 0) {
                printf("Liste voll!");
                return 1;
            }
        }
        for (int i = 0; i < MAX; ++i) {
            int h = array[i];
            if (h != 0) {
                printf("%d ", h);
            }
        }
        printf("\n");
    }
    return 0;
}