// Minimum und Maximum von Zahlen
// 
// Aufruf: minmax zahl1 zahl2 zahl3 ...
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {  // Wenn argc == 1 ist: Keine Zahlen auf der Befehlszeile
    fprintf(stderr, "Aufruf: %s zahl1 zahl2 zahl3 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // 2 Variablen für das Minimum und Maximum der bisher betrachteten Zahlen
  int min, max;  
  // Solange wir uns nur die erste Zahl angeschaut haben,
  // ist diese unser vorläufiges Minimum und Maximum.
  // C kann einen Wert in mehrere Variablen gleichzeitig speichern:
  // Das ganz rechts wird ausgerechnet und in min und max gespeichert
  // (man könnte auch 2 getrennte = machen: min = atoi(...); max = atoi(...);)
  min = max = atoi(argv[1]);

  // Und dann vergleichen wir unser vorläufiges Minimum und Maximum
  // der Reihe nach mit der 2., 3., ... Zahl auf der Befehlszeile,
  // bis zur Anzahl der Worte auf der Befehlszeile
  // Achtung: 5 Worte ==> Programmname = 0, dann Nummer 1 bis 4, nicht 5!
  for (int i = 2; i < argc; ++i) {
    int z = atoi(argv[i]); // i-tes Wort der Befehlszeile als Zahl in z speichern
    if (z < min) { // wenn die neue Zahl kleiner als unser bisheriges min ist
      min = z;     // dann speichern wir sie als neues Minimum
    }
    if (z > max) { // wenn die neue Zahl größer als unser bisheriges max ist
      max = z;     // dann speichern wir sie als neues Maximum
    }
  }

  printf("Minimum: %d, Maximum: %d\n", min, max);

  exit(EXIT_SUCCESS);
}
