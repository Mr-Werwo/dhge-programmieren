// String-Funktionen: String umdrehen (Version mit Längenbegrenzung)
// Version mit Index
//
// Aufruf: strrev text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// Max. String-Länge incl. \0
#define LINE_LEN 32

char *strnrev(        // Returnwert: Ein char-Zeiger auf das Ergebnis dest
  char dest[],        // Ein Zeiger auf das Array,
                      // in das das Ergebnis gespeichert werden soll
  int size,           // neu: Größe von dest
  const char src[])   // Ein Zeiger auf das Array mit dem Eingabe-Text.
                      // Wird nur gelesen, also const.
{
  int i, j;

  // Wandere mit i Zeichen für Zeichen durch src, bis du am Ende bist
  for (i = 0; src[i] != '\0'; ++i) { }
  // Jetzt zeigt i auf die Ende-Markierung '\0',
  // wir brauchen sie aber am letzten Zeichen vor dem Ende
  --i;

  // Wandere mit j zeichenweise von links nach rechts durch dest,
  // und mit i zeichenweise von rechts nach links durch src,
  // bis i vor dem Anfang von src steht oder dest voll ist
  // Achtung: Wir müssen eins vor dem Ende von dest aufhören,
  // weil dann auf jeden Fall noch ein '\0' in dest Platz haben muss
  for (j = 0; (i >= 0) && (j < size - 1); --i, ++j) {
    // ... und kopiere das Zeichen, auf das i gerade zeigt,
    // an die Stelle, auf die j gerade zeigt
    dest[j] = src[i];
  }
  // j zeigt ein Zeichen hinter das letzte kopierte Zeichen,
  // und dort müssen wir noch eine Ende-Markierung speichern
  dest[j]= '\0';

  // Laut Angabe soll strrev einen Zeiger auf das Ergebnis-Array liefern
  return dest;
}

int main(int argc, const char *argv[])
{
  char result[LINE_LEN];

  // Alle Worte der Befehlszeile von hinten nach vorne durchgehen
  for (int i = argc - 1; i > 0; --i) {
    // strrev liefert einen Zeiger auf das Ergebnis als Returnwert,
    // und den geben wir gleich weiter in das printf zum Ausgeben
    printf("%s ", strnrev(result, LINE_LEN, argv[i]));
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}
