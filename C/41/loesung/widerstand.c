// Widerstands-Farbcode umrechnen
//
// Aufruf: widerstand farbe1 farbe2 farbe3
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Liefert den Wert (0 bis 9) von "farbe" als Returnwert.
int farbwert(const char *farbe)
{
  // Die Farben, Index der Farbe im Array = Wert der Farbe.
  // Es hat wenig Sinn, das Array bei jedem einzelnen Aufruf
  // frisch anzulegen und zu befüllen
  // ==> mit "static" geschieht das nur einmal bei Programmstart
  static const char *code[] = { "schwarz", "braun", "rot", "orange", "gelb",
                                "gruen", "blau", "lila", "grau", "weiss" };

  for (int i = 0; i < 10; ++i) {
    // strcmp liefert als Ergebnis 0, wenn die beiden Strings gleich sind.
    if (strcmp(farbe, code[i]) == 0) return i;
  }

  fprintf(stderr, "\"%s\" ist keine gültige Farbe!\n", farbe);
  exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "Aufruf: %s farbe1 farbe2 farbe3\n", argv[0]);
    fprintf(stderr, "farbe1 ... erste Ziffer\n"
            "farbe2 ... zweite Ziffer\n"
            "farbe3 ... Zehnerpotenz = Anzahl der Nullen\n"
            "keine Toleranz-Farbe, keine negativen Zehnerpotenzen, "
            "keine 3-Ziffern-Codes\n");
    exit(EXIT_FAILURE);
  }

  printf("%s %s %s = %.0f\n", argv[1], argv[2], argv[3],
        (10 * farbwert(argv[1]) + farbwert(argv[2])) *
        pow(10, farbwert(argv[3])));

  exit(EXIT_SUCCESS);
}
