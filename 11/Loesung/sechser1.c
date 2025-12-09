// Zwei Sechser würfeln
// Lösung mit Speichern des aktuellen und des vorigen Wurfes
//
// Aufruf: sechser1
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  // siehe Folie betr. rand():
  // rand soll bei jedem Programmlauf andere Werte liefern
  srand(time(NULL));

  // Aktueller Wurf
  // damit "alt" beim ersten Schleifendurchlauf einen sinnvollen Wert bekommt
  // und nicht z.B. ein zufälliger Speicherinhalt "6" in wurf
  // zu einem falschen Ergebnis führt: 0 setzen!
  int wurf = 0;
  int alt;     // Alter (voriger) Wurf
  int anz = 0; // Anzahl der Würfe

  do { // auch while oder for möglich, wir wollen ja in anz mitzählen
    alt = wurf;  // vorigen aktuellen Wurf als alten Wurf speichern
    wurf = rand() % 6 + 1;  // neuen Wurf berechnen: siehe Folie betr. rand()!
    ++anz;
    printf("%3d. Wurf: %d\n", anz, wurf);
  } while (!((alt == 6) && (wurf == 6)));
  // oder while ((alt != 6) || (wurf != 6));

  exit(EXIT_SUCCESS);
}
