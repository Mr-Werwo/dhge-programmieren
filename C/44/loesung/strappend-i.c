// String-Funktionen: Strings zusammenhängen
// Version mit Index
//
// Aufruf: strappend text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// Maximale Länge des Ergebnisses
#define TEXT_LEN 4096

char *strappend(char dest[], const char src[])
{
  int j;  // i (unten) ist Index in src, j ist Index in dest

  // lass j auf das Ende von dest zeigen ...
  for (j = 0; dest[j] != '\0'; ++j) { }

  // ... und kopiere dann wie auf der Folie:
  // Die Zuweisung steckt in der Bedingung,
  // erst dann wird der zugewiesene Wert auf die Ende-Markierung geprüft
  // ==> '\0' wird auch noch kopiert, erst danach hört die Schleife auf.
  for (int i = 0; (dest[j] = src[i]) != '\0'; ++i, ++j) { }

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
