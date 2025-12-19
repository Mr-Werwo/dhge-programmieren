// String-Funktionen: String suchen
//
// Aufruf: strsearch haystack needle
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strsearch(const char *haystack, const char *needle)
{
  // für jede Position in haystack:
  for ( ; *haystack != '\0'; ++haystack) {
    // wir müssen der Reihe nach alle Zeichen von needle
    // mit den Zeichen ab der aktuellen Position von haystack vergleichen
    for (const char *nP = needle, *hP = haystack; ; ++nP, ++hP) {
      if (*nP == '\0') {
        // alle Zeichen von needle erfolgreich verglichen ==> gefunden!
        // Die Typumwandlung entfernt das const vom haystack-Typ
        return (char *) haystack;
      }
      if (*nP != *hP) {
        // Zeichen passt nicht ==> nicht weiter vergleichen,
        // sondern gleich eins weiter in der haystack-Schleife
        break;
      }
    }
  }

  // nichts gefunden ...
  return NULL;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s haystack needle\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *pos = strsearch(argv[1], argv[2]);
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
