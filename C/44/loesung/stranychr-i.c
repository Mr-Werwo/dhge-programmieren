// String-Funktionen: Ein Zeichen von mehreren suchen
// Version mit Index
//
// Aufruf: stranychr text zeichenliste
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

int stranychr(const char str[], const char chars[])
{
  for (int i = 0; str[i] != '\0'; ++i) {
    // vergleiche das Zeichen an Stelle i mit allen Zeichen in chars
    for (int j = 0; chars[j] != '\0'; ++j) {
      if (chars[j] == str[i]) return i;
    }
  }

  return -1;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text zeichenlist\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pos = stranychr(argv[1], argv[2]);
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
