// String-Funktionen: Strings kopieren, Zwischenräume reduzieren
// Wortweise Schleife
// Version mit Index
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
  int i, j;  // i ist Index in src, j ist Index in dest

  for (i = 0, j = 0; ; ) {  // Variante 2: Wortweise Schleife
    // überspringe alle aufeinanderfolgenden Zwischenräume
    for ( ; isspace(src[i]); ++i) { }
    // wenn nichts mehr kommt ==> fertig
    if (src[i] == '\0') {
      break;
    }
    // sonst: Schreib 1 Zwischenraum zwischen Wörtern,
    // außer wir sind noch ganz am Anfang
    if (j > 0) {
      dest[j++] = ' ';
    }
    // kopiere das Wort, bis der Text aus ist oder ein Zwischenraum kommt
    for ( ; !((src[i] == '\0') || isspace(src[i])); ++i, ++j) {
      dest[j] = src[i];
    }
  }

  // Das Ergebnis braucht noch eine Ende-Markierung
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
  
  printf("\"%s\"\n", strtrim(result, argv[1]));

  exit(EXIT_SUCCESS);
}
