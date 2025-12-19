// String-Funktionen: Strings kopieren mit Längenbegrenzung
//
// Aufruf: strmaxcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strmaxcpy(char *dest, int size, const char *src)
{
  if (size > 0) {
    // Zeiger auf das letzte Zeichen von dest = Schleifenende = Endemarkierung
    char *destEnd = dest + (size - 1);

    // wir kopieren diesmal ohne das '\0' am Ende ...
    const char *srcP;
    char *destP;
    for (srcP = src, destP = dest;
         // ... bis dest fast voll oder src zu Ende ist ...
         (destP < destEnd) && (*srcP != '\0');
         ++srcP, ++destP) {
      *destP = *srcP;
    }
    // ... und hängen das Ende-Zeichen nachher an.
    *destEnd = '\0';
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
