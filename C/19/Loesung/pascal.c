// Pascal'sches Dreieck
//
// Aufruf: pascal zeilenanzahl
// 
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s zeilenanzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int zeilen = atoi(argv[1]);

  if (zeilen <= 0) {
    fprintf(stderr, "%s: Die Zeilenanzahl muss größer 0 sein!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pascal[zeilen][zeilen];  // Zweidimensionales Array
  // sowohl die Zeilennummern als auch die Spaltennummern
  // gehen von 0 bis (zeilen-1)

  // die 0. Spalte in allen Zeilen ist 1
  for (int z = 0; z < zeilen; ++z) {
    pascal[z][0] = 1;
  }
  // die 0. Zeile ab Spalte 1 (nicht 0) ist 0
  for (int s = 1; s < zeilen; ++s) {
    pascal[0][s] = 0;
  }
  // alle anderen Werte (alles außer Zeile 0 und Spalte 0) sind die Summe
  // des gleichen und des vorigen Wertes in der Zeile darüber
  for (int z = 1; z < zeilen; ++z) { // zeilenweise ausrechnen ab Zeile 1
    for (int s = 1; s < zeilen; ++s) { // in jeder Zeile von links ab 1 nach rechts
      pascal[z][s] = pascal[z - 1][s - 1] + pascal[z - 1][s];
    }
  }

  // alle Werte ausgeben, Zeile für Zeile und Spalte für Spalte
  for (int z = 0; z < zeilen; ++z) {
    // man braucht nur die Spalten Nummer 0 bis einschließlich z ausgeben:
    // ab Nummer z+1 enthalten die Spalten den Wert 0
    for (int s = 0; s <= z; ++s) {
      printf("%5d ", pascal[z][s]);
    }
    printf("\n");  // nach den Zahlen einer Zeile: Neue Zeile!
  }  
  
  exit(EXIT_SUCCESS);
}
