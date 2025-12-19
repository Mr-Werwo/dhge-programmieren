// String-Funktionen: Strings kopieren ohne Zwischenräume
// malloc-Variante
//
// Aufruf: strtextcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *strtextcpy(const char *src)
{
  // zuerst Länge des Ergebnisses ermitteln
  int len = 0;
  for (const char *srcP = src; *srcP != '\0'; ++srcP) {
    if (!isspace(*srcP)) ++len;
  }
  // Ergebnis-String anlegen
  char *dest = (char *)(malloc(len + 1));   // + 1 für Ende-Markierung
  if (dest == NULL) return NULL;            // Fehler im malloc?
  
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

  printf("\"%s\"\n", strtextcpy(argv[1]));

  exit(EXIT_SUCCESS);
}
