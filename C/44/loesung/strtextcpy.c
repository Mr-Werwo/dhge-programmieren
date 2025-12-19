// String-Funktionen: Strings kopieren ohne Zwischenräume
//
// Aufruf: strtextcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strtextcpy(char *dest, const char *src)
{
  char *destP = dest;
  // Für alle Zeichen in src: ...
  for (const char *srcP = src; *srcP != '\0'; ++srcP) {
    if (!isspace(*srcP)) {
      // Nur wenn kein Zwischenraum:
      // Kopieren und Zeiger in dest weiterschieben
      *destP = *srcP;
      ++destP;
    }
  }
  // Ende wird nicht mitkopiert ==> nachholen!
  *destP = '\0';

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
