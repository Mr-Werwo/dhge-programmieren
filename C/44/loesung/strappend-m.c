// String-Funktionen: Strings zusammenhängen
// malloc-Variante
//
// Aufruf: strappend text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strappend(const char *src1, const char *src2)
{
  const char *srcP;

  // Längen ermitteln
  for (srcP = src1; *srcP != '\0'; ++srcP) { }
  int len = srcP - src1;
  for (srcP = src2; *srcP != '\0'; ++srcP) { }
  len += srcP - src2;

  // Ergebnis-String anlegen
  char *dest = (char *)(malloc(len + 1));   // + 1 für Ende-Markierung
  if (dest == NULL) return NULL;            // Fehler im malloc?

  // Ersten String "normal" kopieren
  char *destP;
  for (srcP = src1, destP = dest; *srcP != '\0'; ++srcP, ++destP) {
    *destP = *srcP;
  }
  // Zweiten String wie auf der Folie kopieren:
  // Die Zuweisung steckt in der Bedingung,
  // erst dann wird der zugewiesene Wert auf die Ende-Markierung geprüft
  // ==> '\0' wird auch noch kopiert, erst danach hört die Schleife auf.
  for (srcP = src2; (*destP = *srcP) != '\0'; ++srcP, ++destP) { }

  return dest;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text1 text2\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strappend(argv[1], argv[2]));

  exit(EXIT_SUCCESS);
}
