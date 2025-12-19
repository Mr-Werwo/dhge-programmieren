// String-Funktionen: String umdrehen
//
// Aufruf: strrev text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strrev(         // Returnwert: Ein char-Zeiger auf das Ergebnis dest
  char *dest,         // Ein Zeiger auf das Array,
                      // in das das Ergebnis gespeichert werden soll
  const char *src)    // Ein Zeiger auf das Array mit dem Eingabe-Text.
                      // Wird nur gelesen, also const.
{
  const char *srcP;   // Ein Zeiger in das Array src
  // Wandere mit srcP Zeichen für Zeichen durch src, bis du am Ende bist
  for (srcP = src; *srcP != '\0'; ++srcP) { }
  // Jetzt zeigt srcP auf die Ende-Markierung '\0',
  // wir brauchen sie aber am letzten Zeichen vor dem Ende
  --srcP;

  char *destP;        // Ein Zeiger in das Array dest
  // Wandere mit destP zeichenweise von links nach rechts durch dest,
  // und mit srcP zeichenweise von rechts nach links durch src,
  // bis srcP vor dem Anfang von src steht ...
  for (destP = dest; srcP >= src; --srcP, ++destP) {
    // ... und kopiere das Zeichen, auf das srcP gerade zeigt,
    // an die Stelle, auf die despP gerade zeigt
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
  char result[4096];

  // Alle Worte der Befehlszeile von hinten nach vorne durchgehen
  for (int i = argc - 1; i > 0; --i) {
    // strrev liefert einen Zeiger auf das Ergebnis als Returnwert,
    // und den geben wir gleich weiter in das printf zum Ausgeben
    printf("%s ", strrev(result, argv[i]));
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}
