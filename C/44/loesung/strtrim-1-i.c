// String-Funktionen: Strings kopieren, Zwischenräume reduzieren
// Zeichenweise Schleife
// Version mit Index
//
// Aufruf: strtrim text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char *strtrim(char dest[], const char src[])
{
  bool spaces = false;  // Hatten wir zuletzt Zwischenräume oder ein Wort?

  // Variante mit zeichenweiser Schleife
  int j = 0;    // i ist Index in src, j ist Index in dest
  for (int i = 0; src[i] != '\0'; ++i) {
    if (isspace(src[i])) {
      // merk dir, dass Zwischenräume da waren,
      // aber schreib nichts ins Ergebnis
      spaces = true;
    } else {
      // zu kopierender Text, kein Zwischenraum
      if (spaces) {
        // Wenn davor Zwischenräume waren:
        if (j > 0) {
          // Wenn wir nicht am Anfang des Ergebnisses sind:
          // Speichere einen Zwischenraum ins Ergebnis
          dest[j++] = ' ';
        }
        spaces = false;  // Zwischenraum erledigt, wir sind mitten im Wort
      }
      dest[j++] = src[i];   // Kopiere den Buchstaben
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
