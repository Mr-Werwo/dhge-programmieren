// Dezimale Ausgabe mittels rekursiver Funktion
// 
// Aufruf: rec-dez n1 n2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

void writeDec(int n);

int main(int argc, const char *argv[])
{
  for (int i = 1; i < argc; ++i) {
    writeDec(atoi(argv[i]));
    putchar('\n');    // entspricht printf("\n");
  }  

  exit(EXIT_SUCCESS);
}

void writeDec(int n)
{
  if (n < 0) {
    putchar('-');    // entspricht printf("-");
    n = -n;
  }
  
  if (n >= 10) {
    // Wenn die Zahl mehr als eine Stelle hat:
    // Gib zuerst die vorderen Stellen (= die Zahl geteilt durch 10) aus ...
    writeDec(n / 10);
    // ... und kümmere dich nur um die letzte Stelle selbst
    n = n % 10;
  }
  
  // Gib am Ende die letzte bzw. einzige Stelle der Zahl aus.
  // n + '0' macht aus einer einstelligen Zahl n den ASCII-Wert der Ziffer n
  putchar(n + '0');    // entspricht printf("%d", n);
}
