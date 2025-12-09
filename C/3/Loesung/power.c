// Potenz zweier ganzer Zahlen (basis hoch expon)
//
// Aufruf: power basis expon
//
// Klaus Kusche, 2010/2011

#include <stdio.h>
// Für atoi brauchen wir laut Angabe stdlib.h
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  // hat der Aufrufer überhaupt genau zwei Zahlen angegeben?
  // (damit argv[1] und argv[2] nicht "ins Leere greift")
  if (argc != 3) {
    // Wenn nein: Fehlermeldung ausgeben, mit Fehlercode aufhören
    fprintf(stderr, "Aufruf: %s basis expon\n", argv[0]);
    exit(EXIT_FAILURE);  // oder "return 1;" : bewirkt dasselbe
  }

  // argv[1] und argv[2] mittels atoi von Text in Zahlen verwandeln
  // (den Text (einen "char *") steckt man in atoi hinein,
  // die Zahl (ein "int") kommt als Ergebnis zurück:
  // atoi ... "ascii to int")
  // und in zwei dafür angelegten Variablen speichern
  int basis = atoi(argv[1]);
  int expon = atoi(argv[2]);

  // "irgendwas hoch negative Zahl" können wir mit ganzen Zahlen nicht rechnen:
  // Wenn expon < 0 ist: Fehlermeldung und aufhören!
  // (und "0 hoch 0" sollte auch ausgeschlossen werden, aber das sparen wir uns)
  if (expon < 0) {
    fprintf(stderr, "%s: Negativer Exponent.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Wir brauchen eine Variable für das Ergebnis
  // im Ergebnis speichern wir als Anfangswert einmal 1,
  // damit wir weiter unten etwas dazumultiplizieren können
  int ergeb = 1;

  // und dann kommt eine Schleife,
  // die von 1 bis zur zweiten Eingabe expon (einschließlich) zählt
  for (int i = 1; i <= expon; ++i) {
    // in der Schleife multiplizieren wir jedesmal
    // die erste Eingabe zum Ergebnis dazu
    // und speichern das wieder im Ergebnis
    ergeb = ergeb * basis;
  }

  // nach der Schleife kommt noch die Ausgabe ...
  printf("%d hoch %d = %d\n", basis, expon, ergeb);

  // ... und das Programm-Ende
  exit(EXIT_SUCCESS);  // oder "return 0;" : bewirkt dasselbe
}
