// Zeile in Worte zerlegen
//
// Aufruf: wordify
// 
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Maximale Länge der Eingabe-Zeile
#define LINE_LEN 4096

// Returnwert: Anfangsposition des nächsten Wortes ab Position pos in str
// Nebeneffekt: Erste Position nach dem Wort wird in *pos gespeichert
int wordify(const char str[], int *pos)
{
  int start, ende;
  
  // start: suche den ersten Buchstaben (oder Ziffer) ab pos
  for (start = *pos; !isalnum(str[start]); ++start) {
    if (str[start] == '\0') {
      // Ende des Strings erreicht, ohne dass ein Wort anfängt
      *pos = start; // Speichere die Position der Ende-Markierung im Aufrufer
      return -1;
    }
  }
  
  // ende: suche das erste Zeichen, das nicht Buchstabe oder Ziffer ist,
  // ab start+1
  for (ende = start + 1; isalnum(str[ende]); ++ende) {}
  *pos = ende; // speichere ende im Aufrufer
  
  return start;
}

int main(void)
{
  char zeile[LINE_LEN];

  while (fgets(zeile, sizeof(zeile), stdin)) {
    int suchPos = 0;  // beginne ganz vorne in der Zeile zu suchen
    for (;;) {    // Schleife pro Wort
      // ermittle den näcchsten Wortanfang
      // und stelle suchpos auf das Zeichen,
      // ab dem das nächste Wort gesucht werden soll
      int wortPos = wordify(zeile, &suchPos);
      if (wortPos == -1) break;  // kein Wort mehr ==> nächste Zeile lesen
      // gib das Wort ab wortPos bis vor suchPos zeichenweise aus
      for (int i = wortPos; i < suchPos; ++i) {
        putchar(zeile[i]);
      }
      putchar('\n');
    }
  }
  
  exit(EXIT_SUCCESS);
}
