// String-Funktionen: Strings kopieren ohne Zwischenräume
// Version mit Index
//
// Aufruf: strtextcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strtextcpy(char dest[], const char src[])
{
  int j = 0;  // i (unten) ist Index in src, j ist Index in dest

  // Für alle Zeichen in src: ...
  for (int i = 0; src[i] != '\0'; ++i) {
    if (!isspace(src[i])) {
      // Nur wenn kein Zwischenraum:
      // Kopieren und Zeiger in dest weiterschieben
      dest[j] = src[i];
      ++j;
    }
  }
  // Ende wird nicht mitkopiert ==> nachholen!
  dest[j] = '\0';

  return dest;
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s text\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char result[strlen(argv[1]) + 1];
  
  printf("\"%s\"\n", strtextcpy(result, argv[1]));

  exit(EXIT_SUCCESS);
}
