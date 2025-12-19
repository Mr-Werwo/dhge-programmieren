// Prüfung auf Palindrom
//
// Aufruf: palindrom1 "text"
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// true wenn str ein Palindrom ist, false wenn nicht
bool ist_palin(const char str[])
{
  // i geht von vorne nach hinten und j geht vom letzten Zeichen nach vorne
  // solange i vor j ist und die jeweiligen Zeichen gleich sind
  for (int i = 0, j = strlen(str) - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) return false;
  }

  return true;  
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s \"text\"\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (ist_palin(argv[1])) {
    printf("\"%s\" ist ein Palindrom!\n", argv[1]);
  } else {
    printf("\"%s\" ist kein Palindrom!\n", argv[1]);
  }
  
  exit(EXIT_SUCCESS);
}
