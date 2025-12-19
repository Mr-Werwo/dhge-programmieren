// Pascal'sches Dreieck (Binomialkoeffizient berechnen mit Fakultätsfunktion)
//
// Aufruf: binom-fact lines
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 80

int fac(int n);
int binom(int n, int k);

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s lines\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int lines = atoi(argv[1]);
  
  for (int i = 0; i < lines; ++i) {
    // zentriert ausgeben:
    // Die Anfangsposition ist die halbe Zeilenlänge minus der halben Textlänge
    // Textlänge: In der i-ten Zeile habe ich (i+1) Zahlen der Breite 5
    //            und i einzelne Zwischenräume dazwischen
    int textStart = LINELEN / 2 - ((i + 1) * 5 + i) / 2;
    // textStart viele ' ' ausgeben
    for (int j = 1; j < textStart; ++j) {
      putchar(' ');   
    }
    for (int j = 0; j <= i; ++j) {
      printf("%5d ", binom(i, j));
    }
    putchar('\n');
  }
  
  exit(EXIT_SUCCESS);
}

int binom(int n, int k)
{
  if ((n < 0) || (n > 12)) return -1;   // ab 13 kommt es zu Überläufen
  if ((k > n) || (k < 0)) return 0;

  // die Fälle k == 0 oder k == n werden vom "Normalfall" richtig berechnet,
  // weil fac(n) / (fac(0) * fac(n)) ist immer 1.
  return fac(n) / (fac(k) * fac(n - k));
}

int fac(int n)
{

  if (n < 0) return -1;

  int f = 1;
  // könnte man auch rekursiv statt mit for machen
  for (int i = 2; i <= n; ++i) {
    f *= i; 
  }
  // wenn man gleich mit n von n abwärts zählt anstatt aufwärts zu zählen,
  // spart man sich eine separate Hilfsvariable zum Zählen
  //for ( ; n > 1; --n) {
  //  f *= n;
  //}

  return f;
}
