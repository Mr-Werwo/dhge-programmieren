// String-Funktionen: Strings kopieren mit Längenbegrenzung
// malloc-Variante
//
// Aufruf: strmaxcpy text
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strmaxcpy(int size, const char *src)
{
  const char *srcP;

  // Länge von src ermitteln
  for (srcP = src; *srcP != '\0'; ++srcP) { }
  int len = srcP - src;
  
  if (len >= size) {  // len darf wegen '\0' maximal size - 1 sein
    len = size - 1;
  }
  if (len < 0) {  // malloc mit negativer Größe vermeiden!
    len = 0;
  }
  
  // Ergebnis-String anlegen
  char *dest = (char *)(malloc(len + 1));   // + 1 für Ende-Markierung
  if (dest == NULL) return NULL;            // Fehler im malloc?

  // Zeiger auf das Zeichen hinter len Zeichen = Schleifenende = Endemarkierung
  char *destEnd = dest + len;
  // wieder vorne in src anfangen, len Zeichen kopieren ...
  srcP = src;
  for (char *destP = dest; destP < destEnd; ++srcP, ++destP) {
    *destP = *srcP;
  }
  // ... und Ende-Markierung anhängen
  *destEnd = '\0';

  return dest;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s text laenge\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strmaxcpy(atoi(argv[2]), argv[1]));

  exit(EXIT_SUCCESS);
}
