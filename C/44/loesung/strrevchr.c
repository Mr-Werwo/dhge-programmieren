// String-Funktionen: Ein Zeichen von hinten suchen
//
// Aufruf: strrevchr text zeichen
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strrevchr(const char *str, char c)
{
  const char *found = NULL;  // die bisher letzte Fundstelle: Keine

  // geh bis zum Ende ...
  for ( ; *str != '\0'; ++str) {
    // ... und merke dir die Fundstellen
    if (*str == c) found = str;
  }

  // die letzte Fundstelle oder NULL, wenn es keine gab.
  // Das ist wieder ein "const-weg-Typumwandlung"
  return (char *) found;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text zeichen\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *pos = strrevchr(argv[1], argv[2][0]);
  if (pos == NULL) {
    printf("Nicht gefunden!\n");
  } else {
    printf("%s\n", argv[1]);
    // Zeige auf den richtigen Buchstaben im String:
    // Gib entsprechend viele ' ' aus.
    for (int i = pos - argv[1]; i > 0; --i) printf(" ");
    printf("^\n");
  }

  exit(EXIT_SUCCESS);
}
