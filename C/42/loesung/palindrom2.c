// Prüfung auf Palindrom, mit Ausgabe-Parametern für die Position
//
// Aufruf: palindrom2 "text"
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
       
  int links, rechts;  // werden von ist_palin befüllt
  if (ist_palin(argv[1], &links, &rechts)) {
    printf("\"%s\" ist ein Palindrom!\n", argv[1]);
  } else {
    printf("Das %d. und %d. Zeichen von \"%s\" (%c und %c) passen nicht.\n",
           links + 1, rechts + 1, argv[1], argv[1][links], argv[1][rechts]);
  }
  
  exit(EXIT_SUCCESS);
}
