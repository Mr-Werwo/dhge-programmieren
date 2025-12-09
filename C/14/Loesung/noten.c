// Notenauswertung
//
// Aufruf: noten note1 note2 note3 ...
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// leicht änderbar machen, in der Schule gibt es z.B. 6 Noten
#define NOTEN 5

int main(int argc, const char *argv[])
{
  int anzahl[NOTEN + 1];  // Die Anzahl jeder Note:
                          // anzahl[0] lassen wir unbenutzt
                          // anzahl[1] ... Anzahl der Einser
                          // anzahl[2] ... Anzahl der Zweier usw.
  if (argc < 2) {
    printf("Aufruf: %s note1 note2 note3 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // zuerst in jedem Zähler 0 speichern
  for (int note = 1; note <= NOTEN; ++note) {
    anzahl[note] = 0;
  }

  // dann die Noten von der Befehlszeile zählen
  for (int i = 1; i < argc; ++i) {  // für alle Wörter auf der Befehlszeile
    int note = atoi(argv[i]);
    if ((note < 1) || (note > NOTEN)) {
      fprintf(stderr, "%s: Bitte Noten zwischen 1 und %d eingeben"
              " (%d. Note = %d)\n",
              argv[0], NOTEN, i, note);
      exit(EXIT_FAILURE);
    }
    ++(anzahl[note]);  // zähl zum Zähler Nummer note eins dazu
  }

  // und zum Schluss jeden Zähler ausgeben
  for (int note = 1; note <= NOTEN; ++note) {
    printf("%3d mal Note %d\n", anzahl[note], note);
  }
  
  exit(EXIT_SUCCESS);
}
