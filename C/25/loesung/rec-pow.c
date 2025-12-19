// a hoch n, rekursiv und mit Unterscheidung gerade / ungerade 
//
// Aufruf: rec-pow a n
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

double hoch(double a, int n)
{
  if (n == 0) {
    return 1.0;                 // fertig: irgendwas^0 ist 1
  } else if (n < 0) {           // wenn n negativ ist:
    return 1 / hoch(a, -n);     // Ergebnis ist Kehrwert der positiven Potenz
  } else if ((n % 2) == 0) {    // wenn n gerade ist:
    return hoch(a * a, n / 2);  // a^n ist dasselbe wie (a^2)^(n/2)
  } else {                      // sonst:
    return a * hoch(a, n - 1);  // a^n ist dasselbe wie a*a^(n-1)
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s basis exponent\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  double basis = atof(argv[1]);
  int expon = atoi(argv[2]);
  printf("%g^%d = %g\n", basis, expon, hoch(basis, expon));

  exit(EXIT_SUCCESS);
}
