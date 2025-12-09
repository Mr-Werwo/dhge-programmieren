// Potenz zweier ganzer Zahlen (a hoch n)
// Programm-Skelett zur Angabe
//
// Aufruf: power a n
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
// Was steht in der Angabe zu atoi, was an dieser Stelle zu beachten ist?

int main(int argc, const char *argv[])
{
  int zahl2 = 0;
  int zahl1 = 0;
  int result = 1;

  if (argc > 3) {
    printf("bitte zwei zahlen mit angeben");
    return EXIT_FAILURE;
  }

  zahl1 = atoi(argv[1]);
  zahl2 = atoi(argv[2]);

  if (zahl2 && zahl1)

  if (zahl2 == 0) {
    printf("0 hoch x = 0");
    return EXIT_FAILURE;
  }

  for (int i = 1; i <= zahl2; ++i) {
    result *= zahl1;
  }

  printf("%d hoch %d = %d\n", zahl1, zahl2, result);
  return EXIT_SUCCESS;
  // hat der Aufrufer �berhaupt genau zwei Zahlen angegeben?
  // (damit argv[1] und argv[2] nicht "ins Leere greift")

    // Wenn nein: Fehlermeldung ausgeben, mit Fehlercode aufh�ren

  // argv[1] und argv[2] in Zahlen verwandeln
  // und in zwei daf�r angelegten Variablen speichern

  // jetzt sollten wir noch pr�fen,
  // ob wir es mit mathematisch sinnvollen Eingaben zu tun haben:
  // Bei ganzzahliger Rechnung k�nnen wir nur Exponenten >= 0 berechnen
  // Sonst: Fehlermeldung, aufh�ren!
  // (und "0 hoch 0" sollte auch ausgeschlossen werden, aber das sparen wir uns)

  // Wir brauchen eine Variable f�r das Ergebnis
  // im Ergebnis speichern wir als Anfangswert einmal 1,
  // damit wir weiter unten etwas dazumultiplizieren k�nnen

  // und dann kommt eine Schleife,
  // die von 1 bis zur zweiten Eingabe (einschlie�lich) z�hlt

    // in der Schleife multiplizieren wir jedesmal
    // die erste Eingabe zum Ergebnis dazu
    // und speichern das wieder im Ergebnis

  // nach der Schleife kommt noch die Ausgabe ...

  // ... und das Programm-Ende

}
