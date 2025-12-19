// Kleinstes gemeinsames Vielfaches zweier ganzer Zahlen, ganz dumm gerechnet
//
// Aufruf: kgv a b
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

int kgv(int a, int b)
{  
  if ((a == 0) || (b == 0)) return 0;

  if (a < 0) a = -a;
  if (b < 0) b = -b;

  int va = a, vb = b; // Vielfaches von a und von b, beginnt mit a und b selbst
  while (va != vb) {
    if (va < vb) va += a;
    else vb += b;
  }
  
  return va;
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s a b\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  printf("kgV(%d, %d) = %d\n", a, b, kgv(a, b));

  exit(EXIT_SUCCESS);
}
