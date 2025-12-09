// Zwei Sechser würfeln
// Alternative Lösung durch Zählen der aufeinanderfolgenden Sechser
//
// Aufruf: sechser1b
//
// Klaus Kusche, 2013

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  // siehe Folie betr. rand():
  // rand soll bei jedem Programmlauf andere Werte liefern
  srand(time(NULL));

  int anz = 0;      // Anzahl der Würfe
  int sechser = 0;  // Anzahl der aufeinanderfolgenden Sechser

  while (sechser < 2) { // auch for möglich, wir wollen ja in anz mitzählen
    // neuen Wurf berechnen: siehe Folie betr. rand()!
    int wurf = rand() % 6 + 1;  
    if (wurf == 6) {
      ++sechser;
    } else {
      sechser = 0;
    }
    ++anz;
    printf("%3d. Wurf: %d\n", anz, wurf);
  }

  exit(EXIT_SUCCESS);
}
