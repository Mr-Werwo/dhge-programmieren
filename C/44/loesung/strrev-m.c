// String-Funktionen: String umdrehen
// malloc-Variante
//
// Aufruf: strrev text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strrev(           // Returnwert: Ein char-Zeiger auf das Ergebnis
  const char *src)      // Ein Zeiger auf das Array mit dem Eingabe-Text.
                        // Wird nur gelesen, also const.
{
  const char *srcP;     // Ein Zeiger in das Array src
  // Wandere mit srcP Zeichen für Zeichen durch src, bis du am Ende bist
  for (srcP = src; *srcP != '\0'; ++srcP) { }

  // Jetzt zeigt srcP auf die Ende-Markierung '\0',
  // srcP - src liefert die Länge von src, + 1 als Platz für Ende-Markierung
  // Ergebnis-String dynamisch anlegen, dest darauf zeigen lassen
  char *dest = (char *)(malloc((srcP - src) + 1));
  if (dest == NULL) return NULL;               // Fehler im malloc?

  // srcP muss für die Schleife auf das letzte Zeichen vor dem Ende zeigen
  --srcP;

  char *destP;
  // Wandere mit destP zeichenweise von links nach rechts durch dest,
  // und mit srcP zeichenweise von rechts nach links durch src,
  // bis srcP vor dem Anfang von src steht ...
  for (destP = dest; srcP >= src; --srcP, ++destP) {
    // ... und kopiere das Zeichen, auf das srcP gerade zeigt,
    // an die Stelle, auf die destP gerade zeigt
    *destP = *srcP;
  }
  // destP zeigt ein Zeichen hinter das letzte kopierte Zeichen,
  // und dort müssen wir noch eine Ende-Markierung speichern
  *destP = '\0';

  // Laut Angabe soll strrev einen Zeiger auf das Ergebnis-Array liefern
  return dest;
}


int main(int argc, const char *argv[])
{
  // Befehlszeile von hinten nach vorne durchgehen
  for (int i = argc - 1; i > 0; --i) {
    char *rev = strrev(argv[i]);
    printf("%s ", rev);
    // wenn rev nicht mehr benötigt wird: Freigeben
    free(rev);
  }
  printf("\n");
  
  exit(EXIT_SUCCESS);
}
