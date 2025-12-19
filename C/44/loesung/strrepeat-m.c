// String-Funktionen: Ein Zeichen wiederholen
// malloc-Variante
//
// Aufruf: strrepeat zeichen anzahl
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strrepeat(char c, int cnt)
{
  // Ergebnis-String anlegen
  char *dest = (char *)(malloc(cnt + 1));   // + 1 für Ende-Markierung
  if (dest == NULL) return NULL;            // Fehler im malloc?

  // Zeiger auf das Zeichen hinter cnt Zeichen = Schleifenende = Endemarkierung
  char *destEnd = dest + cnt;  
  for (char *destP = dest; destP < destEnd; ++destP) {
    *destP = c;
  }

  *destEnd = '\0';
  return dest;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s zeichen anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strrepeat(argv[1][0], atoi(argv[2])));

  exit(EXIT_SUCCESS);
}
