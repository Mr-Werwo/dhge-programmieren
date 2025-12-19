// Prüfung auf Palindrom, mit Umkopieren ohne Zwischenräume
//
// Aufruf: palindrom3 "text"
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXLEN 64

// quelle nach ziel kopieren
// dabei nur die Buchstaben kopieren und alles in Kleinschreibung verwandeln
char *kleinschr(char ziel[], int maxLen, const char quelle[])
{
  int nach = 0;  // aktuelle Position in ziel
  for (int von = 0; quelle[von] != '\0'; ++von) {
    if (isalpha(quelle[von])) {
      if (nach == maxLen - 1) {
        // maxLen-1 ist der hinterste Platz in ziel,
        // dort muss noch eine Ende-Markierung hinpassen!
        printf("%s: Die Eingabe ist zu lang!\n", quelle);
        break;
      }
      ziel[nach] = tolower(quelle[von]);
      ++nach;
    }
  }
  // Endemarkierung nicht vergessen
  ziel[nach] = '\0';

  return ziel;
}

// true wenn str ein Palindrom ist, false wenn nicht
// bei false:
// In links und rechts werden die Positionen der falschen Zeichen gespeichert
bool ist_palin(const char str[], int *links, int *rechts)
{
  // i geht von vorne nach hinten und j geht vom letzten Zeichen nach vorne
  // solange i vor j ist und die jeweiligen Zeichen gleich sind
  for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      *links = i;
      *rechts = j;
      return false;
    }
  }

  return true;  
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s \"text\"\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char txt[MAXLEN];
  kleinschr(txt, MAXLEN, argv[1]);     

  int links, rechts;  // werden von ist_palin befüllt
  if (ist_palin(txt, &links, &rechts)) {
    printf("\"%s\" ist ein Palindrom!\n", txt);
  } else {
    printf("Das %d. und %d. Zeichen von \"%s\" (%c und %c) passen nicht.\n",
           links + 1, rechts + 1, txt, txt[links], txt[rechts]);
  }
  
  exit(EXIT_SUCCESS);
}
