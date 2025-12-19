// Gespiegelte Zahlen (Zahl-Palindrome) suchen und zählen
//
// Aufruf: spiegeln limit
//
// Klaus Kusche, 2013

#include <stdio.h>
#include <stdlib.h>

int spiegeln(int n)
{  
  int ergeb = 0;

  while (n > 0) {
    ergeb = (ergeb * 10) + (n % 10);
    n = n / 10;
  }
  
  return ergeb;
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s limit\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int limit = atoi(argv[1]);

  int anz = 0;
  for (int i = 0; i <= limit; ++i) {
    if (i == spiegeln(i)) {
      printf("%d ", i);
      ++anz;
    }
  }

  printf("\nInsgesamt %d Spiegelzahlen\n", anz);

  exit(EXIT_SUCCESS);
}
