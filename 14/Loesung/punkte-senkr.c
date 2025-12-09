// Notenauswertung nach Punkten, mit senkrechtem Balkendiagramm
//
// Aufruf: punkte punkte1 punkte2 punkte3 ...
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
// für lround
#include <math.h>

// Höhe der Balken in Zeilen
const int ZEILEN = 18;

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

  // Berechne das Maximum von anzahl[1] bis anzahl[5]
  int max = anzahl[1];
  for (int note = 2; note <= 5; ++note) {
    if (anzahl[note] > max) {
      max = anzahl[note];
    }
  }
  // Eine Zeile Balkenhöhe entspricht einer Anzahl von "faktor",
  // der Balken mit Anzahl max ist daher ZEILEN Zeilen hoch.
  double faktor = ((double) max) / ZEILEN;
  
  printf("\n");
  // zeilenweise Ausgabe, zeile = Nummer der aktuellen Zeile:
  // Die hohen Werte sind oben, die niedrigen unten ==> wir zählen abwärts
  for (int zeile = ZEILEN; zeile >= 1; --zeile) {
    // von links nach rechts die Balken für jede Note zeichnen
    for (int note = 1; note <= 5; ++note) {
      // wenn die Anzahl der zu zeichnenden Note geringer ist
      // als der aktuellen Zeile entspricht,
      // gib "     " aus, sonst gib " #### " aus
      printf((anzahl[note] < zeile * faktor) ? "          " : " ######## ");
    }
    printf("\n");
  }

  // von links nach rechts:
  // Unter jeden Balken die Note & Anzahl und den Prozent-Anteil schreiben
  for (int note = 1; note <= 5; ++note) {
    printf("  %d: %3d  ", note, anzahl[note]);
  }
  printf("\n");
  for (int note = 1; note <= 5; ++note) {
    printf(" %6.2f %% ", (100.0 * anzahl[note]) / (argc - 1));
  }
  printf("\n");
  // und nochmal: aufpassen auf int/int
  printf("Mittlere Punkte-Anzahl: %.2f\n", ((double) summe) / (argc - 1));
  
  exit(EXIT_SUCCESS);
}
