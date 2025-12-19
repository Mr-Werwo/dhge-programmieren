// Zeile in Worte zerlegen, mit Pointern statt Index
// mit Separator-String und mit Einfügen einer Ende-Markierung
//
// Aufruf: wordify-end
// 
// Klaus Kusche, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximale Länge der Eingabe-Zeile
#define LINE_LEN 4096

// String mit allen Wort-Trennzeichen
// in unserem Fall: Nur "White Space", Klammern und ;,:.?!
#define SEPARATORS " \t\n()[]{};,:.?!"

// Returnwert:
//   Pointer auf den Anfang des nächsten Wortes ab Position pos
//   Dieses Wort wird durch Einfügen eines \0 in den Input-String
//   in einen sauber terminierten String verwandelt
// Nebeneffekt:
//   Ein Pointer auf das erste Zeichen nach dem Wort und seiner Ende-Markierung
//   wird in *pos gespeichert
// Ein "by Reference" übergebener Pointer ist ein Pointer auf einen Pointer,
//   also **
char *wordify(char **pos, const char *sepStr)
{
  char *start, *ende;

  // lass start auf den Beginn des nächsten Wortes ab pos zeigen
  for (start = *pos; ; ++start) {
    if (*start == '\0') {
      // Ende des Strings erreicht, ohne dass ein Wort anfängt
      *pos = start; // Speichere die Position der Ende-Markierung im Aufrufer
      return NULL;  // ... und gib den "Nichts-Pointer" als Returnwert zurück
    }
    if (strchr(sepStr, *start) == NULL) {
      // das Zeichen an Position start kommt nicht im Trennzeichen-String vor
      // ==> Anfang des Wortes gefunden
      break;
    }
  }
  
  // lass ende auf das erste Zeichen hinter dem Wort zeigen
  // suche das Ende ab start+1
  for (ende = start + 1; ; ++ende) {
    if (*ende == '\0') {
      // Ende des Strings erreicht
      // ==> Das aktuelle Wort ist schon richtig '\0'-terminiert,
      // und es gibt kein nächstes Wort mehr
      *pos = ende;
      return start;
    }
    if (strchr(sepStr, *ende) != NULL) {
      // das Zeichen an Position ende kommt im Trennzeichen-String vor
      // ==> ende zeigt auf das erste Zeichen nach dem Wort!
      break;
    }
  }

  // terminiere das Wort
  *ende = '\0';
  // speichere einen Pointer hinter diese Ende-Markierung im Aufrufer
  // damit der nächste Aufruf ab dort weitersucht
  *pos = ende + 1;
  
  return start;
}

int main(void)
{
  char zeile[LINE_LEN];

  while (fgets(zeile, sizeof(zeile), stdin)) {
    char *suchPos = zeile;  // beginne ganz vorne in der Zeile zu suchen
    for (;;) {    // Schleife pro Wort
      // ermittle den näcchsten Wortanfang
      // und stelle suchpos auf das Zeichen,
      // ab dem das nächste Wort gesucht werden soll
      const char *wortPos = wordify(&suchPos, SEPARATORS);
      if (wortPos == NULL) break;  // kein Wort mehr ==> nächste Zeile lesen
      // gib das Wort aus
      puts(wortPos);
    }
  }
  
  exit(EXIT_SUCCESS);
}
