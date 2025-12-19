// String-Funktionen: Strings kopieren, Zwischenräume reduzieren
// Zeichenweise Schleife
//
// Aufruf: strtrim text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char *strtrim(char *dest, const char *src)
{
  char *destP = dest;
  bool spaces = false;  // Hatten wir zuletzt Zwischenräume oder ein Wort?

  // Variante mit zeichenweiser Schleife
  for (const char *srcP = src; *srcP != '\0'; ++srcP) {
    if (isspace(*srcP)) {
      // merk dir, dass Zwischenräume da waren,
      // aber schreib nichts ins Ergebnis
      spaces = true;
    } else {
      // zu kopierender Text, kein Zwischenraum
      if (spaces) {
        // Wenn davor Zwischenräume waren:
        if (destP != dest) {
          // Wenn wir nicht am Anfang des Ergebnisses sind:
          // Speichere einen Zwischenraum ins Ergebnis
          *(destP++) = ' ';
        }
        spaces = false;  // Zwischenraum erledigt, wir sind mitten im Wort
      }
      *(destP++) = *srcP;   // Kopiere den Buchstaben
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
