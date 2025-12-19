// Zeile in Worte zerlegen, mit Pointern statt Index
//
// Aufruf: wordify-ptr
// 
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Maximale Länge der Eingabe-Zeile
#define LINE_LEN 4096

// Returnwert:
//   Pointer auf den Anfang des nächsten Wortes ab Position pos
// Nebeneffekt:
//   Ein Pointer auf das erste Zeichen nach dem Wort wird in *pos gespeichert
// Ein "by Reference" übergebener Pointer ist ein Pointer auf einen Pointer,
//   also **
const char *wordify(const char **pos)
{
  const char *start, *ende;

  // start: suche den ersten Buchstaben (oder Ziffer) ab pos
  for (start = *pos; !isalnum(*start); ++start) {
    if (*start == '\0') {
      // Ende des Strings erreicht, ohne dass ein Wort anfängt
      *pos = start; // Speichere die Position der Ende-Markierung im Aufrufer
      return NULL;  // ... und gib den "Nichts-Pointer" als Returnwert zurück
    }
  }
  
  // ende: suche das erste Zeichen, das nicht Buchstabe oder Ziffer ist,
  // ab start+1
  for (ende = start + 1; isalnum(*ende); ++ende) {}
  *pos = ende; // speichere ende im Aufrufer
  
  return start;
}

int main(void)
{
  char zeile[LINE_LEN];

  while (fgets(zeile, sizeof(zeile), stdin)) {
    const char *suchPos = zeile;  // beginne ganz vorne in der Zeile zu suchen
    for (;;) {    // Schleife pro Wort
      // ermittle den näcchsten Wortanfang
      // und stelle suchpos auf das Zeichen,
      // ab dem das nächste Wort gesucht werden soll
      const char *wortPos = wordify(&suchPos);
      if (wortPos == NULL) break;  // kein Wort mehr ==> nächste Zeile lesen
      // gib das Wort ab wortPos bis vor suchPos zeichenweise aus
      for (const char *p = wortPos; p < suchPos; ++p) {
        putchar(*p);
      }
      putchar('\n');
    }
  }
  
  exit(EXIT_SUCCESS);
}
