// String-Funktionen: Ein Zeichen von hinten suchen
// Version mit Index
//
// Aufruf: strrevchr text zeichen
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

int strrevchr(const char str[], char c)
{
  int found = -1;  // die bisher letzte Fundstelle: Keine

  // geh bis zum Ende ...
  for (int i = 0; str[i] != '\0'; ++i) {
    // ... und merke dir die Fundstellen
    if (str[i] == c) found = i;
  }

  // die letzte Fundstelle oder -1, wenn es keine gab.
  return found;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text zeichen\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pos = strrevchr(argv[1], argv[2][0]);
  if (pos == -1) {
    printf("Nicht gefunden!\n");
  } else {
    printf("%s\n", argv[1]);
    // Zeige auf den richtigen Buchstaben im String:
    // Gib entsprechend viele ' ' aus.
    for (int i = pos; i > 0; --i) printf(" ");
    printf("^\n");
  }

  exit(EXIT_SUCCESS);
}
