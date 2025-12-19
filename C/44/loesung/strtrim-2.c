// String-Funktionen: Strings kopieren, Zwischenräume reduzieren
// Wortweise Schleife
//
// Aufruf: strtrim text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strtrim(char *dest, const char *src)
{
  const char *srcP = src;
  char *destP = dest;

  for (;;) {  // Variante 2: Wortweise Schleife
    // überspringe alle aufeinanderfolgenden Zwischenräume
    for ( ; isspace(*srcP); ++srcP) { }
    // wenn nichts mehr kommt ==> fertig
    if (*srcP == '\0') {
      break;
    }
    // sonst: Schreib 1 Zwischenraum zwischen Wörtern,
    // außer wir sind noch ganz am Anfang
    if (destP != dest) {
      *(destP++) = ' ';
    }
    // kopiere das Wort, bis der Text aus ist oder ein Zwischenraum kommt
    for ( ; !((*srcP == '\0') || isspace(*srcP)); ++srcP, ++destP) {
      *destP = *srcP;
    }
  }

  // Das Ergebnis braucht noch eine Ende-Markierung
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
  
  printf("\"%s\"\n", strtrim(result, argv[1]));

  exit(EXIT_SUCCESS);
}
