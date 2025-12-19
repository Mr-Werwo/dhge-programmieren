// Zufallszahlen mit automatischer Initialisierung
//
// Aufruf: rand-seed
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ANZAHL 30

// Returnwert: Ganze Zufallszahl zwischen from und to (einschlieﬂlich).
unsigned int myRand(unsigned int from, unsigned int to)
{
  static unsigned int val;
  static bool called = false;  // Sind wir schon jemals aufgerufen worden?

  if (!called) {
    // Erster Aufruf: Internen Wert mit der aktuellen Zeit initialisieren!
    // (und merken, dass wir schon einmal aufgerufen wurden)
    val = time(NULL); 
    called = true;
  }
  
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
