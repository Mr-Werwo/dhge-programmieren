// String-Funktionen: Strings kopieren mit Längenbegrenzung
// Version mit Index
//
// Aufruf: strmaxcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strmaxcpy(char dest[], int size, const char src[])
{
  if (size > 0) {
    int i;

    // wir kopieren diesmal ohne das '\0' am Ende ...
    // ... bis dest fast voll oder src zu Ende ist ...
    for (i = 0; (i < size - 1) && (src[i] != '\0'); ++i) {
      dest[i] = src[i];
    }
    // ... und hängen das Ende-Zeichen nachher an.
    dest[i] = '\0';
  }

  return dest;
}

int main(int argc, const char *argv[])
{
  char result[10];
  
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s text\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strmaxcpy(result, sizeof(result), argv[1]));

  exit(EXIT_SUCCESS);
}
