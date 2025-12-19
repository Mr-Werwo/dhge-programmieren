// Pascal'sches Dreieck (Binomialkoeffizient berechnen durch Multiplizieren)
//
// Aufruf: binom-mult lines
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 80

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
  // weil die Schleife dann 0 Durchläufe macht
  // Dann sind oben und unten beide 1, oben/unten daher auch.

  // Optimierung: Bei k und bei n-k kommt dasselbe raus ==> Symmetrie ausnutzen
  // ==> Bei k größer als n/2: Nimm das kleinere der beiden,
  //     es braucht weniger Multiplikationen!
  if (k + k > n) k = n - k;

  // Zähler & Nenner: Anfangswert für's Multiplizieren nicht vergessen!
  int oben = 1, unten = 1;  
  // Schleife mit k Durchläufen: i zählt von 1 hinauf, j von n herunter
  for (int i = 1, j = n; i <= k; ++i, --j) {
    oben *= j;  // Zähler: Produkt von k Zahlen von n abwärts
    unten *= i; // Nenner: Produkt von k Zahlen von 1 aufwärts
  }
  
  return oben / unten;  // Division geht sich immer aus
}
