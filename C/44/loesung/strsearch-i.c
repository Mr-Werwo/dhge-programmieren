// String-Funktionen: String suchen
// Version mit Index
//
// Aufruf: strsearch haystack needle
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

int strsearch(const char haystack[], const char needle[])
{
  // für jede Position in haystack:
  for (int i = 0; haystack[i] != '\0'; ++i) {
    // wir müssen der Reihe nach alle Zeichen von needle
    // mit den Zeichen ab der aktuellen Position von haystack vergleichen
    for (int j = 0; ; ++j) {
      if (needle[j] == '\0') {
        // alle Zeichen von needle erfolgreich verglichen ==> gefunden!
        return i;
      }
      if (needle[j] != haystack[i + j]) {
        // Zeichen passt nicht ==> nicht weiter vergleichen,
        // sondern gleich eins weiter in der haystack-Schleife
        break;
      }
    }
  }

  // nichts gefunden ...
  return -1;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s haystack needle\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pos = strsearch(argv[1], argv[2]);
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
