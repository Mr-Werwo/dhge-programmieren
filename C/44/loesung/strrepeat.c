// String-Funktionen: Ein Zeichen wiederholen
//
// Aufruf: strrepeat zeichen anzahl
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

char *strrepeat(char *dest, char c, int cnt)
{
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
  int anzahl = atoi(argv[2]);

  char result[anzahl + 1];
  
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s zeichen anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", strrepeat(result, argv[1][0], anzahl));

  exit(EXIT_SUCCESS);
}
