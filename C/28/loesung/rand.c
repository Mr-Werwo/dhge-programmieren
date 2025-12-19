// Zufallszahlen
//
// Aufruf: rand
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>

#define ANZAHL 30

// Returnwert: Ganze Zufallszahl zwischen from und to (einschlieﬂlich).
unsigned int myRand(unsigned int from, unsigned int to)
{
  // Interner Wert muss zwischen den Aufrufen erhalten bleiben ==> static!
  static unsigned int val = 1;    
  
  val = val * 1103515245 + 12345;

  // Anzahl der Zahlen zwischen from und to (einschlieﬂlich): to - from + 1
  return val % (to - from + 1) + from;
}

int main(void)
{
  unsigned int summe = 0;
  for (int i = 0; i < ANZAHL; ++i) {
    unsigned int r = myRand(1, 6);
    summe += r;
    printf("%u ", r);
  }

  printf("\nMittelwert: %f\n", ((double) summe) / ANZAHL);

  exit(EXIT_SUCCESS);
}
