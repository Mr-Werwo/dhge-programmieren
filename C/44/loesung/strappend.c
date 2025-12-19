// String-Funktionen: Strings zusammenhängen
//
// Aufruf: strappend text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// Maximale Länge des Ergebnisses
#define TEXT_LEN 4096

char *strappend(char *dest, const char *src)
{
  // lass destP auf das Ende von dest zeigen ...
  char *destP;
  for (destP = dest; *destP != '\0'; ++destP) { }

  // ... und kopiere dann wie auf der Folie:
  // Die Zuweisung steckt in der Bedingung,
  // erst dann wird der zugewiesene Wert auf die Ende-Markierung geprüft
  // ==> '\0' wird auch noch kopiert, erst danach hört die Schleife auf.
  for (const char *srcP = src; (*destP = *srcP) != '\0'; ++srcP, ++destP) { }

  return dest;
}

int main(int argc, const char *argv[])
{
  char result[TEXT_LEN] = "Angehängter Text ==> ";
  
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s text\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strappend(result, argv[1]));

  exit(EXIT_SUCCESS);
}
