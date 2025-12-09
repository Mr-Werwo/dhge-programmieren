// Notenauswertung nach Punkten
//
// Aufruf: punkte punkte1 punkte2 punkte3 ...
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
// für lround
#include <math.h>

int main(int argc, const char *argv[])
{
  int anzahl[6];  // Die Anzahl jeder Note, anzahl[0] lassen wir unbenutzt

  if (argc < 2) {
    fprintf(stderr, "Aufruf: %s punkte1 punkte2 punkte3 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Alle Zähler auf 0 setzen
  for (int note = 1; note <= 5; ++note) {
    anzahl[note] = 0;
  }

  int summe = 0; // Für die Summe aller Punkte (für den Mittelwert)
  for (int i = 1; i < argc; ++i) {
    int punkte = atoi(argv[i]);
    if ((punkte < 0) || (punkte > 100)) {
      fprintf(stderr, "%s: Bitte Punkte zwischen 0 und 100 eingeben"
              " (%d. Punkte = %d)\n",
              argv[0], i, punkte);
      exit(EXIT_FAILURE);
    }
    summe += punkte;
    int note;
    if (punkte < 50) {
      note = 5;
    } else {
      // damit es keine falschen Ergebnisse wegen int/int (abgeschnitten!) gibt:
      // 5.0 und 10.0 erzwingen jeweils eine Komma-Division!
      // lround macht aus einer Kommazahl durch kaufmännische Rundung einen int
      //
      // erster Schritt: Ermittle die Zehntelnote (int von 10 bis 40)
      note = lround(40 - 3 * ((punkte - 50) / 5.0));
      // zweiter Schritt: Runde die Zehntelnote kaufmännisch,
      // wobei x.5 noch abgerundet wird
      // (deshalb - 0.1, sonst würde x.5 aufgerundet)
      note = lround(note / 10.0 - 0.1);
    }
    ++anzahl[note];
  }
  
  for (int note = 1; note <= 5; ++note) {
    // %3d ... ganze Zahl, Feldbreite 3
    // %6.2f ... Kommazahl, Feldbreite 6, 2 Nachkomma-Stellen
    // %% ... Ausgabe eines %-Zeichens
    printf("%3d mal Note %d (%6.2f %%)\n", anzahl[note], note,
           // Prozent ausrechnen: 100 * Anteil / Gesamtzahl
           // wieder: double-Division, nicht int-Division ==> 100.0 statt 100
           (100.0 * anzahl[note]) / (argc - 1));
  }
  // und nochmal: aufpassen auf int/int
  printf("Mittlere Punkte-Anzahl: %.2f\n", ((double) summe) / (argc - 1));
  
  exit(EXIT_SUCCESS);
}
