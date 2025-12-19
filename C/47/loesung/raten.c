// Buchstaben raten
//
// Aufruf: raten 
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Für tolower
#include <ctype.h>
#include <time.h>

// strcasecmp ist keine C-Standard-Funktion, sondern aus dem POSIX-Standard
// Sie kommt aus dem Header der Stringfunktionen vom früheren BSD-Unix-C
#include <strings.h>

// maximale Länge der Worte incl. '\0'
#define MAX_LEN 100

// Die Liste der zu erratenden Wörter:
// Array von Pointern auf die einzelnen Worte
// Achtung, keine Längenprüfung! Die Worte müssen kürzer sein als MAX_LEN!
// Es muss alles klein geschrieben werden: Wortliste und Eingabe.
// Großbuchstaben werden *nicht* in Kleinbuchstaben verwandelt,
// und die Groß/Kleinschreibung wird beim Vergleichen *nicht* ignoriert!
const char *liste[] = { "Suppe", "Rattenschwanz", "Dezember", "Esel",
  "Wurstsalat", "Donaudampfschiff", "Ypsilon", "Schlagzeug", "Misthaufen" };

int main(void)
{
  srand(time(NULL));  
  // wortNum: die zufällig gewählte Nummer des zu erratenden Wortes in der Liste
  // sizeof(liste) / sizeof(liste[0]) liefert die Anzahl der Worte in der Liste.
  // Die Zufallszahl soll ein Index in die Liste sein,
  // muss also zwischen 0 und Anzahl - 1 liegen.
  // Genau das kommt heraus, wenn man rand() % Anzahl rechnet.
  int wortNum = rand() % (sizeof(liste) / sizeof(liste[0]));
  // das zufällige, zu erratende Wort
  // nur zur kürzeren Schreibweise
  // sonst müssten wir bei jedem Zugriff aus das Wort "liste[wortNum]" schreiben
  const char *wort = liste[wortNum];  
  // die Länge des zu erratenden Wortes (ohne '\0')
  int wortLen = strlen(wort);

  // das angezeigte Wort (mit Sternchen)
  char ausgabe[MAX_LEN];   
  // ausgabe auf lauter Sternchen (wortLen viele) initialisieren
  for (int i = 0; i < wortLen; ++i) {
    ausgabe[i] = '*';
  }
  ausgabe[wortLen] = '\0';  // Ende-Markierung nicht vergessen!

  int versuche;
  for (versuche = 1; ; ++versuche) { // Bis zum "break;", es gibt 2 Ausgänge!
    char eingabe[MAX_LEN];   // vom Benuzer eingegebenes Wort oder Zeichen
    printf(
      "%s\n%d. Versuch: Errate das ganze Wort oder gib einen Buchstaben ein: ",
      ausgabe, versuche);
    scanf("%s", eingabe);  // Achtung, gefährlich, keine Längenprüfung!!!

    if (strlen(eingabe) == 1) {  // nur 1 Buchstabe eingegeben
      for (int i = 0; i < wortLen; ++i) {  // geh das Wort buchstabenweise durch
        // Test unabhängig von Groß- und Kleinschreibung,
        // indem beide Seiten als Kleinbuchstaben verglichen werden:
        // Wenn der eingegebene Buchstabe an Stelle i des gesuchten Wortes ist
        if (tolower(wort[i]) == tolower(eingabe[0])) {
          // ... dann ersetze in der Ausgabe den Stern an der Stelle i
          // durch den richtigen Buchstaben aus dem Wort
          ausgabe[i] = wort[i];
        }
      }
      // war das der letzte noch fehlende Buchstabe (keine '*' mehr im Wort)?
      if (strchr(ausgabe, '*') == NULL) break;
      // oder if (strcmp(ausgabe, wort) == 0) break;
    } else {   // ein ganzes Wort eingegeben ==> passt es?
      // strcasecmp vergleicht wie strcmp,
      // aber ignoriert Groß- und Kleinschreibung
      if (strcasecmp(eingabe, wort) == 0) break;
      else printf("Falsch!\n");
    }
  }

  printf("Gewonnen! \"%s\" erraten in %d Versuchen.\n",
         wort, versuche);
  
  exit(EXIT_SUCCESS);
}
