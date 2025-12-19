// String-Funktionen: Ein Zeichen von mehreren suchen
//
// Aufruf: stranychr text zeichenliste
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *stranychr(const char *str, const char *chars)
{
  for ( ; *str != '\0'; ++str) {
    // vergleiche das Zeichen an Stelle *str mit allen Zeichen in chars
    for (const char *p = chars; *p != '\0'; ++p) {
      if (*p == *str) {
        // Diese Typumwandlung entfernt das "const" vom Typ von str
        return (char *) str;
      }
    }
  }

  return NULL;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text zeichenlist\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *pos = stranychr(argv[1], argv[2]);
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
