// 100000 Mal zwei Sechser würfeln, mit Mittelwert / Min / Max
// Lösung mit Speichern des aktuellen und des vorigen Wurfes
//
// Aufruf: sechser2
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <limits.h>

// Anzahl der Spiele, Zahl bitte nicht unten in der Schleife verstecken!
#define ANZAHL 100000

int main(void)
{
  srand(time(NULL));

  int summe_anz = 0;  // Gesamt-Anzahl aller Würfe, für den Mittelwert
  // min muss mit einer sehr großen Zahl beginnen ...
  int min_anz = 0x7FFFFFFF; // größter int-Wert, jede sehr große Zahl ist ok
  // oder min_anz = INT_MAX;     // größte darstellbare int-Zahl, aus limits.h
  // ... und max mit einer sehr kleinen
  int max_anz = 0;
  
  for (int i = 1; i <= ANZAHL; ++i) {
    // Versuche neu zählen
    int anz = 0;
    // nicht mit dem letzten 6-Wurf des vorigen Versuchs weiterrechnen!
    int wurf = 0;
    // Hilfsvariable für den vorigen Wurf
    int alt;  

    // 1 Spiel genau wie bisher
    do {
      alt = wurf;
      wurf = rand() % 6 + 1;
      ++anz;
    } while (!((alt == 6) && (wurf == 6)));

    summe_anz += anz;
    if (anz < min_anz) {
      min_anz = anz;
    }
    if (anz > max_anz) {
      max_anz = anz;
    }
  }

  printf("Im Schnitt %f Versuche (minimal %d, maximal %d)\n",
    // eine Seite der Division muss auf double umgewandelt werden,
    // damit exakt (als Komma-Division) dividiert wird und nicht ganzzahlig
    ((double) summe_anz) / ANZAHL, min_anz, max_anz);
    
  exit(EXIT_SUCCESS);
}
