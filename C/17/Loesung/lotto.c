// Lottoziehung
//
// Aufruf: lotto
// 
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define KUGELN 49
#define ZAHLEN 6

int main(void)
{
  // wir rechnen intern mit 0-48
  // und zählen erst beim Ausgeben 1 dazu!
  bool gezogen[KUGELN];

  srand(time(NULL));

  for (int i = 0; i < KUGELN; ++i) {
    gezogen[i] = false;
  }

  for (int i = 1; i <= ZAHLEN; ++i) {
    int z;  // die gezogene Zahl
    do {
      z = rand() % KUGELN;
    } while (gezogen[z]);  // wiederhole, bis du eine nicht gezogene Zahl hast
    gezogen[z] = true;
  }

// Alternative Lösung:
//  for (int i = 1; i <= ZAHLEN; /* leer, weitergezählt wird unten! */ ) {
//    int z = rand() % KUGELN;
//    // speichere & zähle die Zahl nur, wenn sie bisher noch nicht gezogen wurde
//    if (!gezogen[z]) {     
//      gezogen[z] = true;
//      ++i;   // nur weiterzählen, wenn es eine noch nicht gezogene Zahl war!
//    }
//  }


  for (int i = 0; i < KUGELN; ++i) {
    if (gezogen[i]) {
      printf("%2d ", i + 1);
    }
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}
